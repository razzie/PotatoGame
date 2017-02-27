#version 150
in vec3 frag_position;
in vec3 frag_normal;
in vec4 frag_color;
out vec4 out_color;
uniform vec3 light_source;

void main()
{
	float light_dot = dot(normalize(frag_normal), normalize(light_source - frag_position));
	float light = clamp(light_dot, 0.0, 1.0) * 0.2 + 0.8;
	out_color = vec4(frag_color.rgb * light, 1.0);
}
