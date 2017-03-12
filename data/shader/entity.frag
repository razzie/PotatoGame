#version 150
in vec3 frag_position;
in vec3 frag_normal;
in vec4 frag_color;
out vec4 out_color;
uniform vec3 light_source;

void main()
{
	float dist = distance(frag_position, light_source);

	if (dist > 100.0)
	{
		out_color = vec4(1.0, 1.0, 1.0, 0.0);
	}
	else
	{
		float light_dot = clamp(dot(normalize(frag_normal), normalize(light_source - frag_position)), 0.25, 1.0);
		float light = light_dot * 2.0 - 1.0;
		vec4 color;
		
		if (light > 0.0)
			color = mix(frag_color, vec4(1.0, 1.0, 1.0, 1.0), light * 0.5);
		else
			color = mix(frag_color, vec4(0.0, 0.0, 0.0, 1.0), -light * 0.5);
		
		if (dist > 50.0)
			color = mix(color, vec4(1.0, 1.0, 1.0, 1.0), (dist - 50.f) * 0.02);
		
		out_color = color;
	}
}
