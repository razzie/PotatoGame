 ���
a�  �   �    �#version 150
in vec4 frag_colo�r;V2Ntcoords\outN$uniform samp  @�ler2D texture"int use_�
void m  P�ain()
{
	if (bool(�
)p		� =V2D�` �(�,�)) *�2	elsev�or;
}
     ���
Wa\H  �   H�    �#version 150
in vec2 positX;�4@ � color2 tcoordsHout�frag_
�2��  �uniform mat4 trans�d
void`in()@
��
{
	^ =�(J.r / 255.0,�%.gvbvaV<8#�);V%m�'	gl_PR?F( * VF, 01.0);
}   �
     z�a�M�k
a��  �   ��    �#version 150
in vec4 frag_posi�tl;
outN$_colorTuniformF3 ligh �t_source"float timF
void main(�B��)
{
	Jn�al =�(0.0, 1F�)�	��doV8�t�(�,�ize(
�#� -n5)vEclampub  *0(�7�5 +�;�-3 
B�-3(R,5J
�JV6N*�0);
}
     z�a�M�k
Wa\�   �    ��   �#version 150
in vec4 positX;
 �outfrag_buniform mat4 screen_0� $�h
voiddin()
{
	j =f	gl_P�� *  ��	on;
}
     zډ
a�Z  �   Z�    �#version 150
in vec3 frag_posi
��tl;2normal�4�colorTout�$Zunif�N  �light_sourcep
void main()
{
@��	float
dot = (ize(�!), � -�1))��;�Yclamp��, 0.0, 1.0) *05 +�Z3؅ ��7(=.rgb��F0);
}
     zډ
Wa\)    )   �#version 150
in vec3 positX;�n  ��ormalZ4 color@out�frag_�n�4��u �nif� mat4 world_,vN� screen��dif��fuse�
void�in()
{
	

N =�(J.r R�� / 255.0,�;.gvbvaV)�	*Eq(�6 *NV, 1����).xyzZ�;�^>��6 2R*�@	gl_P%�N�� 0);
}   �
     ���fp
a�g   _    g_   �#version 150
in vec4 frag_colo� �r;
out�$Z
void main()
{
	�   �=Zor;
}
     ���fp
Wa\  �   �    �#version 150
in vec3 positX;�4@� color@outNfrag_�uniform mat4 s�@ �creen_0h
voiddin()
{
	� =
(J H�.r / 255.0,�.gvbvaV)�	gl_P�.i�! *  ���5, 1.0);
}
    