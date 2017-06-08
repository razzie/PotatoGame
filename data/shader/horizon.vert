#version 150

uniform mat4 wvp_mat;

in vec4 position;

out vec4 frag_position;

void main()
{
	frag_position = position;
	gl_Position = wvp_mat * position;
}
