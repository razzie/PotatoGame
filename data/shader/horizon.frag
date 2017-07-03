#version 150

uniform vec3 light_source;
uniform float time;

in vec4 frag_position;

out vec4 out_color;
out vec4 out_normal;
out vec4 out_position;

void main()
{
	out_color = vec4(1.0);
	out_normal = vec4(0.0, 1.0, 0.0, 1.0);
	out_position = vec4(vec3(frag_position.xyz / frag_position.w), 1.0);
}
