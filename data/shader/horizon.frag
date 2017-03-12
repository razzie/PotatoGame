#version 150
in vec4 frag_position;
out vec4 out_color;
uniform vec3 light_source;
uniform float time;

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

void main()
{
	vec3 position = frag_position.xyz / frag_position.w;
	float dist = distance(position, light_source);
	
	if (dist > 100.0)
	{
		out_color = vec4(1.0, 1.0, 1.0, 0.0);
	}
	else
	{
		float v = Cubist3D(0.25 * position + vec3(0.0, 0.1 * time, 0.0), vec2(-2.0, 1.0 / 3.0)) * 0.1 + 0.9;
		if (dist > 50.0)
			v = mix(v, 1.0, (dist - 50.f) * 0.02);
		out_color = vec4(v, v, v, 1.0);
	}
}
