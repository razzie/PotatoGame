#version 150

in vec3 frag_position;
in vec3 frag_normal;
in vec4 frag_color;

out vec3 out_color;
out vec3 out_normal;
out vec3 out_position;

void main()
{
	out_color = frag_color.rgb;
	out_normal = frag_normal;
	out_position = frag_position;
}
