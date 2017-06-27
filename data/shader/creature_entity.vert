#version 150

uniform mat4 world_mat;
uniform mat4 normal_mat;
uniform mat4 wvp_mat;
uniform vec4 diffuse_color;
uniform float time;

in vec3 position;
in vec3 normal;
in vec4 color;

out vec3 frag_position;
out vec3 frag_local_position;
out vec3 frag_normal;
out vec4 frag_color;

void main()
{
	float color_mul = 1.0 / 255.0;
	vec3 pos = position;
	pos.y += sin(color.r + time * 2.0) * 0.1;
	frag_position = (world_mat * vec4(pos, 1.0)).xyz;
	frag_local_position = position;
	frag_normal = (normal_mat * vec4(normal, 1.0)).xyz;
	frag_color = vec4(color.r * color_mul, color.g * color_mul, color.b * color_mul, color.a * color_mul) * diffuse_color;
	gl_Position = wvp_mat * vec4(pos, 1.0);
}
