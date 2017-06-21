#version 150

uniform sampler2D color_tex;
uniform float threshold = 0.06;

in vec2 frag_position;

out vec4 out_color;


void main()
{
	vec2 uv0 = 1.0 / textureSize(color_tex, 0);
	vec3 color = texture(color_tex, frag_position).rgb;
	float grey = length(color);
	
	bool aaH = (dFdx(grey) > threshold);
	bool aaV = (dFdy(grey) > threshold);
	
	if (aaH)
	{
		vec2 uv_delta = vec2(uv0.x, 0.0);
		vec3 color_prev = texture(color_tex, frag_position - uv_delta).rgb;
		vec3 color_next = texture(color_tex, frag_position + uv_delta).rgb;
		color = (color_prev + color + color_next) / 3.0;
	}
	
	if (aaV)
	{
		vec2 uv_delta = vec2(0.0, uv0.y);
		vec3 color_prev = texture(color_tex, frag_position - uv_delta).rgb;
		vec3 color_next = texture(color_tex, frag_position + uv_delta).rgb;
		color = (color_prev + color + color_next) / 3.0;
	}
	
	out_color = vec4(color, 1.0);
}
