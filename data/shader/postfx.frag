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

float Noise3D(in vec3 coord, in float wavelength);
float GetEdgeWeight();

void main()
{
	vec4 fog_color = vec4(vec3(1.0), 1.0);

	float depth = texture(depth_tex, frag_position).r;
	if (depth == 1.0)
	{
		out_color = fog_color;
		return;
	}
	
	vec3 normal = texture(normal_tex, frag_position).xyz;
	vec3 position = texture(position_tex, frag_position).xyz;
	vec3 color = texture(color_tex, frag_position).rgb * 0.8 + normal * 0.1 + normalize(position) * 0.1;
	
	float light = dot(normalize(camera - position), normal);
	color = mix(color, vec3(1.0), light * light * 0.5);
	
	float outline = 1.0 - GetEdgeWeight();
	color *= outline;
	
	if (position.y < 1.0)
	{
		float horizon = smoothstep(0.4, 0.6, Noise3D(position + vec3(time, time, 0.0), 4.0)) * 0.05;
		horizon += smoothstep(0.4, 0.6, Noise3D(position + vec3(time, time * 0.5, 0.0), 2.0)) * 0.05;
		horizon += 0.9;
		color = mix(vec3(horizon), color, position.y);
	}
	
	float distance = length(camera - position);
	if (distance < render_distance)
		out_color = mix(vec4(color, 1.0), fog_color, distance / render_distance);
	else
		out_color = fog_color;
}

float rand3D(in vec3 co)
{
    return fract(sin(dot(co.xyz ,vec3(12.9898,78.233,144.7272))) * 43758.5453);
}

float simple_interpolate(in float a, in float b, in float x)
{
   return a + smoothstep(0.0,1.0,x) * (b-a);
}

float interpolatedNoise3D(in float x, in float y, in float z)
{
    float integer_x = x - fract(x);
    float fractional_x = x - integer_x;

    float integer_y = y - fract(y);
    float fractional_y = y - integer_y;

    float integer_z = z - fract(z);
    float fractional_z = z - integer_z;

    float v1 = rand3D(vec3(integer_x, integer_y, integer_z));
    float v2 = rand3D(vec3(integer_x+1.0, integer_y, integer_z));
    float v3 = rand3D(vec3(integer_x, integer_y+1.0, integer_z));
    float v4 = rand3D(vec3(integer_x+1.0, integer_y +1.0, integer_z));

    float v5 = rand3D(vec3(integer_x, integer_y, integer_z+1.0));
    float v6 = rand3D(vec3(integer_x+1.0, integer_y, integer_z+1.0));
    float v7 = rand3D(vec3(integer_x, integer_y+1.0, integer_z+1.0));
    float v8 = rand3D(vec3(integer_x+1.0, integer_y +1.0, integer_z+1.0));

    float i1 = simple_interpolate(v1,v5, fractional_z);
    float i2 = simple_interpolate(v2,v6, fractional_z);
    float i3 = simple_interpolate(v3,v7, fractional_z);
    float i4 = simple_interpolate(v4,v8, fractional_z);

    float ii1 = simple_interpolate(i1,i2,fractional_x);
    float ii2 = simple_interpolate(i3,i4,fractional_x);

    return simple_interpolate(ii1 , ii2 , fractional_y);
}

float Noise3D(in vec3 coord, in float wavelength)
{
   return interpolatedNoise3D(coord.x/wavelength, coord.y/wavelength, coord.z/wavelength);
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
