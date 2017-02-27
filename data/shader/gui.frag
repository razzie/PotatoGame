#version 150
in vec4 frag_color;
in vec2 frag_tcoords;
out vec4 out_color;
uniform sampler2D texture;
uniform int use_texture;

void main()
{
	if (bool(use_texture))
		out_color = texture2D(texture, frag_tcoords) * frag_color;
	else
		out_color = frag_color;
}
