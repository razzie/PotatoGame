#version 150
in vec3 position;
in vec3 normal;
in vec4 color;
out vec3 frag_position;
out vec3 frag_normal;
out vec4 frag_color;
uniform mat4 world_mat;
uniform mat4 normal_mat;
uniform mat4 screen_mat;
uniform vec4 diffuse_color;

void main()
{
	vec4 _color = vec4(color.r / 255.0, color.g / 255.0, color.b / 255.0, color.a / 255.0);
	vec4 _diffuse_color = vec4(diffuse_color.r / 255.0, diffuse_color.g / 255.0, diffuse_color.b / 255.0, diffuse_color.a / 255.0);

	frag_position = (world_mat * vec4(position, 1.0)).xyz;
	frag_normal = (normal_mat * vec4(normal, 1.0)).xyz;
	frag_color = _color * _diffuse_color;
	gl_Position = screen_mat * vec4(position, 1.0);
}
