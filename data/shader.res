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
Wa\�  &  �&   �#version 150
in vec3 positX;�n  ��ormalZ4 color@out�frag_�n�4��u �nif� mat4 world_,vN� screen��dif��fuse�
void�in()
{
	

N =�(J.r R�� / 255.0,�;.gvbvaV);�� �j�ng� b� � ���*f�(�W *�"V, 1�).xyz;V�\�^_��6 �:R*2A
g8  �l_P^%p�� 0);
}
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