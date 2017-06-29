#version 150

uniform mat4 world_mat;
uniform mat4 wvp_mat;

in vec3 position;

out vec3 frag_position;
out vec3 frag_local_position;

void main()
{
	frag_position = (world_mat * vec4(position, 1.0)).xyz;
	frag_local_position = position;
	gl_Position = wvp_mat * vec4(position, 1.0);
}
