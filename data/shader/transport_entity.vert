#version 150

uniform mat4 world_mat;
uniform mat4 normal_mat;
uniform mat4 wvp_mat;
uniform vec4 diffuse_color;
uniform float time;
uniform vec3 start_pos;
uniform vec3 end_pos;

in vec3 position;
in vec3 normal;
in vec4 color;

out vec3 frag_position;
out vec3 frag_normal;
out vec4 frag_color;

void main()
{
	float dist = min(length(position - start_pos), length(position - end_pos));
	float swing = 0.125 * sqrt(dist) * sin(start_pos.x + time * 2.0);
	vec3 pos = position + swing * vec3(1.0, 0.0, 0.5);

	float color_mul = 1.0 / 255.0;
	frag_position = (world_mat * vec4(pos, 1.0)).xyz;
	frag_normal = (normal_mat * vec4(normal, 1.0)).xyz;
	frag_color = vec4(color.r * color_mul, color.g * color_mul, color.b * color_mul, color.a * color_mul) * diffuse_color;
	gl_Position = wvp_mat * vec4(pos, 1.0);
}
