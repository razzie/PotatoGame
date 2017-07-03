#version 150

in vec3 frag_position;
in vec3 frag_normal;
in vec4 frag_color;

out vec4 out_color;
out vec4 out_normal;
out vec4 out_position;

void main()
{
	out_color = frag_color;
	out_normal = vec4(vec3(normalize(frag_normal)), 1.0);
	out_position = vec4(frag_position, 1.0);
}
