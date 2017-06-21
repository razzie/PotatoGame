#version 150

in vec2 position;

out vec2 frag_position;

void main()
{
	frag_position = (position + vec2(1.0, 1.0)) / 2.0;
	gl_Position = vec4(position, 0.0, 1.0);
}
