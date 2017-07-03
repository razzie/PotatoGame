#version 150

uniform float time;

in vec3 frag_position;
in vec3 frag_local_position;
in vec3 frag_normal;
in vec4 frag_color;

out vec4 out_color;
out vec4 out_normal;
out vec4 out_position;

float Noise3D(in vec3 coord, in float wavelength);

void main()
{
	if (frag_local_position.y < 0.5)
	{
		float noise = Noise3D(frag_local_position + vec3(0.0, time * 0.1, 0.0), 0.1);
		if (noise > frag_local_position.y * 2.0)
			discard;
	}

	out_color = frag_color;
	out_normal = vec4(vec3(normalize(frag_normal)), 1.0);
	out_position = vec4(frag_position, 1.0);
}

float rand3D(in vec3 co)
{
    return fract(sin(dot(co.xyz ,vec3(12.9898,78.233,144.7272))) * 43758.5453);
}

float simple_interpolate(in float a, in float b, in float x)
{
   return a + smoothstep(0.0,1.0,x) * (b-a);
}

float interpolatedNoise3D(in float x, in float y, in float z)
{
    float integer_x = x - fract(x);
    float fractional_x = x - integer_x;

    float integer_y = y - fract(y);
    float fractional_y = y - integer_y;

    float integer_z = z - fract(z);
    float fractional_z = z - integer_z;

    float v1 = rand3D(vec3(integer_x, integer_y, integer_z));
    float v2 = rand3D(vec3(integer_x+1.0, integer_y, integer_z));
    float v3 = rand3D(vec3(integer_x, integer_y+1.0, integer_z));
    float v4 = rand3D(vec3(integer_x+1.0, integer_y +1.0, integer_z));

    float v5 = rand3D(vec3(integer_x, integer_y, integer_z+1.0));
    float v6 = rand3D(vec3(integer_x+1.0, integer_y, integer_z+1.0));
    float v7 = rand3D(vec3(integer_x, integer_y+1.0, integer_z+1.0));
    float v8 = rand3D(vec3(integer_x+1.0, integer_y +1.0, integer_z+1.0));

    float i1 = simple_interpolate(v1,v5, fractional_z);
    float i2 = simple_interpolate(v2,v6, fractional_z);
    float i3 = simple_interpolate(v3,v7, fractional_z);
    float i4 = simple_interpolate(v4,v8, fractional_z);

    float ii1 = simple_interpolate(i1,i2,fractional_x);
    float ii2 = simple_interpolate(i3,i4,fractional_x);

    return simple_interpolate(ii1 , ii2 , fractional_y);
}

float Noise3D(in vec3 coord, in float wavelength)
{
   return interpolatedNoise3D(coord.x/wavelength, coord.y/wavelength, coord.z/wavelength);
}
