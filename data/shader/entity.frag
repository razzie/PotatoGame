#version 150
in vec3 frag_position;
in vec3 frag_normal;
in vec4 frag_color;
out vec4 out_color;
uniform vec3 light_source;

void main()
{
	float light_dot = clamp(dot(normalize(frag_normal), normalize(light_source - frag_position)), 0.25, 1.0);
	float light = light_dot * 2.0 - 1.0;
	if (light > 0.0)
		out_color = mix(frag_color, vec4(1.0, 1.0, 1.0, 1.0), light * 0.5);
	else
		out_color = mix(frag_color, vec4(0.0, 0.0, 0.0, 1.0), -light * 0.5);
}
