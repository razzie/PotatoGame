#version 150
in vec3 position;
in vec4 color;
out vec4 frag_color;
uniform mat4 screen_mat;

void main()
{
	frag_color = vec4(color.r / 255.0, color.g / 255.0, color.b / 255.0, color.a / 255.0);
	gl_Position = screen_mat * vec4(position, 1.0);
}
