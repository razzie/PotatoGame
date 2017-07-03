#version 150

uniform vec3 light_source;
uniform float time;

in vec4 frag_position;

out vec3 out_color;
out vec3 out_normal;
out vec3 out_position;

void main()
{
	out_color = vec3(1.0, 1.0, 1.0);
	out_normal = vec3(0.0, 1.0, 0.0);
	out_position = frag_position.xyz / frag_position.w;
}
