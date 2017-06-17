#version 150

uniform sampler2D color_tex;
uniform sampler2D normal_tex;
uniform sampler2D position_tex;
uniform sampler2D depth_tex;
uniform float time;
uniform float render_distance;
uniform vec3 camera;

in vec2 frag_position;

out vec4 out_color;

void FAST32_hash_3D(vec3 gridcell,
                    out vec4 lowz_hash_0,
                    out vec4 lowz_hash_1,
                    out vec4 lowz_hash_2,
                    out vec4 lowz_hash_3,
                    out vec4 highz_hash_0,
                    out vec4 highz_hash_1,
                    out vec4 highz_hash_2,
                    out vec4 highz_hash_3)
{
    const vec2 OFFSET = vec2(50.0, 161.0);
    const float DOMAIN = 69.0;
    const vec4 SOMELARGEFLOATS = vec4(635.298681, 682.357502, 668.926525, 588.255119);
    const vec4 ZINC = vec4(48.500388, 65.294118, 63.934599, 63.279683);

    gridcell.xyz = gridcell.xyz - floor(gridcell.xyz * (1.0 / DOMAIN)) * DOMAIN;
    vec3 gridcell_inc1 = step(gridcell, vec3(DOMAIN - 1.5)) * (gridcell + 1.0);

    vec4 P = vec4(gridcell.xy, gridcell_inc1.xy) + OFFSET.xyxy;
    P *= P;
    P = P.xzxz * P.yyww;
    lowz_hash_3.xyzw = vec4(1.0 / (SOMELARGEFLOATS.xyzw + gridcell.zzzz * ZINC.xyzw));
    highz_hash_3.xyzw = vec4(1.0 / (SOMELARGEFLOATS.xyzw + gridcell_inc1.zzzz * ZINC.xyzw));
    lowz_hash_0 = fract(P * lowz_hash_3.xxxx);
    highz_hash_0 = fract(P * highz_hash_3.xxxx);
    lowz_hash_1 = fract(P * lowz_hash_3.yyyy);
    highz_hash_1 = fract(P * highz_hash_3.yyyy);
    lowz_hash_2 = fract(P * lowz_hash_3.zzzz);
    highz_hash_2 = fract(P * highz_hash_3.zzzz);
    lowz_hash_3 = fract(P * lowz_hash_3.wwww);
    highz_hash_3 = fract(P * highz_hash_3.wwww);
}

vec3 Interpolation_C2(vec3 x) { return x * x * x * (x * (x * 6.0 - 15.0) + 10.0); }

float Cubist3D(vec3 P, vec2 range_clamp)
{
    vec3 Pi = floor(P);
    vec3 Pf = P - Pi;
    vec3 Pf_min1 = Pf - 1.0;

    vec4 hashx0, hashy0, hashz0, hash_value0, hashx1, hashy1, hashz1, hash_value1;
    FAST32_hash_3D(Pi, hashx0, hashy0, hashz0, hash_value0, hashx1, hashy1, hashz1, hash_value1);

    vec4 grad_x0 = hashx0 - 0.49999;
    vec4 grad_y0 = hashy0 - 0.49999;
    vec4 grad_z0 = hashz0 - 0.49999;
    vec4 grad_x1 = hashx1 - 0.49999;
    vec4 grad_y1 = hashy1 - 0.49999;
    vec4 grad_z1 = hashz1 - 0.49999;
    vec4 grad_results_0 = inversesqrt(grad_x0 * grad_x0 + grad_y0 * grad_y0 + grad_z0 * grad_z0) * (vec2(Pf.x, Pf_min1.x).xyxy * grad_x0 + vec2(Pf.y, Pf_min1.y).xxyy * grad_y0 + Pf.zzzz * grad_z0);
    vec4 grad_results_1 = inversesqrt(grad_x1 * grad_x1 + grad_y1 * grad_y1 + grad_z1 * grad_z1) * (vec2(Pf.x, Pf_min1.x).xyxy * grad_x1 + vec2(Pf.y, Pf_min1.y).xxyy * grad_y1 + Pf_min1.zzzz * grad_z1);

    grad_results_0 = (hash_value0 - 0.5) * (1.0 / grad_results_0);
    grad_results_1 = (hash_value1 - 0.5) * (1.0 / grad_results_1);

    vec3 blend = Interpolation_C2(Pf);
    vec4 res0 = mix(grad_results_0, grad_results_1, blend.z);
    vec4 blend2 = vec4(blend.xy, vec2(1.0 - blend.xy));
    float final = dot(res0, blend2.zxzx * blend2.wwyy);

    return clamp((final - range_clamp.x) * range_clamp.y, 0.0, 1.0);
}

// GPU Gems 3, pg 443-444
float GetEdgeWeight()
{
	vec2 offsets[9] = vec2[](
		vec2( 0.0,  0.0),
		vec2(-1.0, -1.0),
		vec2( 0.0, -1.0),
		vec2( 1.0, -1.0),
		vec2( 1.0,  0.0),
		vec2( 1.0,  1.0),
		vec2( 0.0,  1.0),
		vec2(-1.0,  1.0),
		vec2(-1.0,  0.0)
	);

	vec2 PixelSize = 1.0 / textureSize(color_tex, 0);

	float Depth[9];
	vec3 Normal[9];

	for(int i = 0; i < 9; i++)
	{
		vec2 uv = frag_position + offsets[i] * PixelSize;
		Depth[i] = texture(depth_tex, uv).r;
		Normal[i] = texture(normal_tex, uv).rgb;
	}

	vec4 Deltas1 = vec4(Depth[1], Depth[2], Depth[3], Depth[4]);
	vec4 Deltas2 = vec4(Depth[5], Depth[6], Depth[7], Depth[8]);

	Deltas1 = abs(Deltas1 - Depth[0]);
	Deltas2 = abs(Depth[0] - Deltas2);

	vec4 maxDeltas = max(Deltas1, Deltas2);
	vec4 minDeltas = max(min(Deltas1, Deltas2), 0.00001);

	vec4 depthResults = step(minDeltas * 25.0, maxDeltas);

	Deltas1.x = dot(Normal[1], Normal[0]);
	Deltas1.y = dot(Normal[2], Normal[0]);
	Deltas1.z = dot(Normal[3], Normal[0]);
	Deltas1.w = dot(Normal[4], Normal[0]);

	Deltas2.x = dot(Normal[5], Normal[0]);
	Deltas2.y = dot(Normal[6], Normal[0]);
	Deltas2.z = dot(Normal[7], Normal[0]);
	Deltas2.w = dot(Normal[8], Normal[0]);

	Deltas1 = abs(Deltas1 - Deltas2);

	vec4 normalResults = step(0.4, Deltas1);

	normalResults = max(normalResults, depthResults);

	return dot(normalResults, vec4(1.0, 1.0, 1.0, 1.0)) * 0.25;
}

void main()
{
	float depth = texture(depth_tex, frag_position).r;
	if (depth == 1.0)
		discard;
	
	vec3 color = texture(color_tex, frag_position).rgb;
	vec3 normal = texture(normal_tex, frag_position).xyz;
	vec3 position = texture(position_tex, frag_position).xyz;
	
	float light = dot(normalize(camera - position), normal);
	color = mix(color, vec3(1.0, 1.0, 1.0), light * light * 0.5);
	
	color *= 1.0 - GetEdgeWeight();
	
	if (position.y < 1.0)
	{
		float horizon = Cubist3D(0.25 * position + vec3(0.0, 0.1 * time, 0.0), vec2(-2.0, 1.0 / 3.0)) * 0.1 + 0.9;
		color = mix(vec3(horizon, horizon, horizon), color, position.y);
	}
	
	float distance = length(camera - position);
	if (distance < render_distance)
		out_color = mix(vec4(color, 1.0), vec4(1.0, 1.0, 1.0, 1.0), distance / render_distance);
	else
		out_color = vec4(1.0, 1.0, 1.0, 1.0);
}
