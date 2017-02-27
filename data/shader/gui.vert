#version 150
in vec2 position;
in vec4 color;
in vec2 tcoords;
out vec4 frag_color;
out vec2 frag_tcoords;
uniform mat4 transform;

void main()
{
	frag_color = vec4(color.r / 255.0, color.g / 255.0, color.b / 255.0, color.a / 255.0);
	frag_tcoords = tcoords;
	gl_Position = transform * vec4(position, 0.0, 1.0);
}
