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

vec3 water(vec2 uv, vec3 cdir);
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
	vec3 color = texture(color_tex, frag_position).rgb;
	
	float distance = length(camera - position);
	vec3 cam_vector = vec3(camera - position) / distance;
	
	float light = dot(cam_vector, normal);
	color = mix(color, vec3(1.0), light * light * 0.75);
	
	float outline = 1.0 - GetEdgeWeight();
	color *= outline;
	
	if (position.y < 1.0)
	{
		vec3 horizon = water(position.xz * 0.35, cam_vector);
		color = mix(horizon, color, position.y);
	}
	
	if (distance < render_distance)
		out_color = mix(vec4(color, 1.0), fog_color, distance / render_distance);
	else
		out_color = fog_color;
}


// "Wind Waker Ocean" by @Polyflare (29/1/15)
// License: Creative Commons Attribution 4.0 International

// Source code for the texture generator is available at:
// https://github.com/lmurray/circleator

//-----------------------------------------------------------------------------
// User settings

// 0 = Do not distort the water texture
// 1 = Apply lateral distortion to the water texture
#define DISTORT_WATER 1

// 0 = Disable parallax effects
// 1 = Change the height of the water with parallax effects
#define PARALLAX_WATER 1

// 0 = Antialias the water texture
// 1 = Do not antialias the water texture
#define FAST_CIRCLES 1

//-----------------------------------------------------------------------------

#define WATER_COL vec3(0.95, 0.954453, 0.957305)
#define WATER2_COL vec3(0.90, 0.904180, 0.906758)
#define FOAM_COL vec3(1.0)

#define M_2PI 6.283185307
#define M_6PI 18.84955592

float circ(vec2 pos, vec2 c, float s)
{
    c = abs(pos - c);
    c = min(c, 1.0 - c);
#if FAST_CIRCLES
    return dot(c, c) < s ? -1.0 : 0.0;
#else
    return smoothstep(0.0, 0.002, sqrt(s) - sqrt(dot(c, c))) * -1.0;
#endif
}

// Foam pattern for the water constructed out of a series of circles
float waterlayer(vec2 uv)
{
    uv = mod(uv, 1.0); // Clamp to [0..1]
    float ret = 1.0;
    ret += circ(uv, vec2(0.37378, 0.277169), 0.0268181);
    ret += circ(uv, vec2(0.0317477, 0.540372), 0.0193742);
    ret += circ(uv, vec2(0.430044, 0.882218), 0.0232337);
    ret += circ(uv, vec2(0.641033, 0.695106), 0.0117864);
    ret += circ(uv, vec2(0.0146398, 0.0791346), 0.0299458);
    ret += circ(uv, vec2(0.43871, 0.394445), 0.0289087);
    ret += circ(uv, vec2(0.909446, 0.878141), 0.028466);
    ret += circ(uv, vec2(0.310149, 0.686637), 0.0128496);
    ret += circ(uv, vec2(0.928617, 0.195986), 0.0152041);
    ret += circ(uv, vec2(0.0438506, 0.868153), 0.0268601);
    ret += circ(uv, vec2(0.308619, 0.194937), 0.00806102);
    ret += circ(uv, vec2(0.349922, 0.449714), 0.00928667);
    ret += circ(uv, vec2(0.0449556, 0.953415), 0.023126);
    ret += circ(uv, vec2(0.117761, 0.503309), 0.0151272);
    ret += circ(uv, vec2(0.563517, 0.244991), 0.0292322);
    ret += circ(uv, vec2(0.566936, 0.954457), 0.00981141);
    ret += circ(uv, vec2(0.0489944, 0.200931), 0.0178746);
    ret += circ(uv, vec2(0.569297, 0.624893), 0.0132408);
    ret += circ(uv, vec2(0.298347, 0.710972), 0.0114426);
    ret += circ(uv, vec2(0.878141, 0.771279), 0.00322719);
    ret += circ(uv, vec2(0.150995, 0.376221), 0.00216157);
    ret += circ(uv, vec2(0.119673, 0.541984), 0.0124621);
    ret += circ(uv, vec2(0.629598, 0.295629), 0.0198736);
    ret += circ(uv, vec2(0.334357, 0.266278), 0.0187145);
    ret += circ(uv, vec2(0.918044, 0.968163), 0.0182928);
    ret += circ(uv, vec2(0.965445, 0.505026), 0.006348);
    ret += circ(uv, vec2(0.514847, 0.865444), 0.00623523);
    ret += circ(uv, vec2(0.710575, 0.0415131), 0.00322689);
    ret += circ(uv, vec2(0.71403, 0.576945), 0.0215641);
    ret += circ(uv, vec2(0.748873, 0.413325), 0.0110795);
    ret += circ(uv, vec2(0.0623365, 0.896713), 0.0236203);
    ret += circ(uv, vec2(0.980482, 0.473849), 0.00573439);
    ret += circ(uv, vec2(0.647463, 0.654349), 0.0188713);
    ret += circ(uv, vec2(0.651406, 0.981297), 0.00710875);
    ret += circ(uv, vec2(0.428928, 0.382426), 0.0298806);
    ret += circ(uv, vec2(0.811545, 0.62568), 0.00265539);
    ret += circ(uv, vec2(0.400787, 0.74162), 0.00486609);
    ret += circ(uv, vec2(0.331283, 0.418536), 0.00598028);
    ret += circ(uv, vec2(0.894762, 0.0657997), 0.00760375);
    ret += circ(uv, vec2(0.525104, 0.572233), 0.0141796);
    ret += circ(uv, vec2(0.431526, 0.911372), 0.0213234);
    ret += circ(uv, vec2(0.658212, 0.910553), 0.000741023);
    ret += circ(uv, vec2(0.514523, 0.243263), 0.0270685);
    ret += circ(uv, vec2(0.0249494, 0.252872), 0.00876653);
    ret += circ(uv, vec2(0.502214, 0.47269), 0.0234534);
    ret += circ(uv, vec2(0.693271, 0.431469), 0.0246533);
    ret += circ(uv, vec2(0.415, 0.884418), 0.0271696);
    ret += circ(uv, vec2(0.149073, 0.41204), 0.00497198);
    ret += circ(uv, vec2(0.533816, 0.897634), 0.00650833);
    ret += circ(uv, vec2(0.0409132, 0.83406), 0.0191398);
    ret += circ(uv, vec2(0.638585, 0.646019), 0.0206129);
    ret += circ(uv, vec2(0.660342, 0.966541), 0.0053511);
    ret += circ(uv, vec2(0.513783, 0.142233), 0.00471653);
    ret += circ(uv, vec2(0.124305, 0.644263), 0.00116724);
    ret += circ(uv, vec2(0.99871, 0.583864), 0.0107329);
    ret += circ(uv, vec2(0.894879, 0.233289), 0.00667092);
    ret += circ(uv, vec2(0.246286, 0.682766), 0.00411623);
    ret += circ(uv, vec2(0.0761895, 0.16327), 0.0145935);
    ret += circ(uv, vec2(0.949386, 0.802936), 0.0100873);
    ret += circ(uv, vec2(0.480122, 0.196554), 0.0110185);
    ret += circ(uv, vec2(0.896854, 0.803707), 0.013969);
    ret += circ(uv, vec2(0.292865, 0.762973), 0.00566413);
    ret += circ(uv, vec2(0.0995585, 0.117457), 0.00869407);
    ret += circ(uv, vec2(0.377713, 0.00335442), 0.0063147);
    ret += circ(uv, vec2(0.506365, 0.531118), 0.0144016);
    ret += circ(uv, vec2(0.408806, 0.894771), 0.0243923);
    ret += circ(uv, vec2(0.143579, 0.85138), 0.00418529);
    ret += circ(uv, vec2(0.0902811, 0.181775), 0.0108896);
    ret += circ(uv, vec2(0.780695, 0.394644), 0.00475475);
    ret += circ(uv, vec2(0.298036, 0.625531), 0.00325285);
    ret += circ(uv, vec2(0.218423, 0.714537), 0.00157212);
    ret += circ(uv, vec2(0.658836, 0.159556), 0.00225897);
    ret += circ(uv, vec2(0.987324, 0.146545), 0.0288391);
    ret += circ(uv, vec2(0.222646, 0.251694), 0.00092276);
    ret += circ(uv, vec2(0.159826, 0.528063), 0.00605293);
	return max(ret, 0.0);
}

// Procedural texture generation for the water
vec3 water(vec2 uv, vec3 cdir)
{
    uv *= vec2(0.25);
    
#if PARALLAX_WATER
    // Parallax height distortion with two directional waves at
    // slightly different angles.
    vec2 a = 0.025 * cdir.xz / cdir.y; // Parallax offset
    float h = sin(uv.x + time); // Height at UV
    uv += a * h;
    h = sin(0.841471 * uv.x - 0.540302 * uv.y + time);
    uv += a * h;
#endif
    
#if DISTORT_WATER
    // Texture distortion
    float d1 = mod(uv.x + uv.y, M_2PI);
    float d2 = mod((uv.x + uv.y + 0.25) * 1.3, M_6PI);
    d1 = time * 0.07 + d1;
    d2 = time * 0.5 + d2;
    vec2 dist = vec2(
    	sin(d1) * 0.15 + sin(d2) * 0.05,
    	cos(d1) * 0.15 + cos(d2) * 0.05
    );
#else
    const vec2 dist = vec2(0.0);
#endif
    
    vec3 ret = mix(WATER_COL, WATER2_COL, waterlayer(uv + dist.xy));
    ret = mix(ret, FOAM_COL, waterlayer(vec2(1.0) - uv - dist.yx));
    return ret;
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
