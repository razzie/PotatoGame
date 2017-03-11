#version 150
in vec4 frag_position;
out vec4 out_color;
uniform vec3 light_source;
uniform float time;

void main()
{
	vec4 normal = vec4(0.0, 1.0, 0.0, 1.0);
	float light_dot = dot(normal, normalize(vec4(light_source, 1.0) - frag_position));
	float light = clamp(light_dot, 0.0, 1.0) * 0.5 + 0.5;
	vec3 color = vec3(1.0, 0.5, 0.5);
	out_color = vec4(color * light, 1.0);
}
