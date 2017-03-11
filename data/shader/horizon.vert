#version 150
in vec4 position;
out vec4 frag_position;
uniform mat4 screen_mat;

void main()
{
	frag_position = position;
	gl_Position = screen_mat * position;
}
