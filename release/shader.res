 k\�\�
a�  �   �    �#version 150

in vec3 frag_po(P�sitt;2normal�4�colorT
out�$�j�  ��"
void main()
{
	Z =b.rgb�	� ��|Nize(",)�	�on;
}
     k\�\�
Wa\B    B   �#version 150

uniform mat4 woP� �rld_,;rn(al� wvp�vec4 diffuse_co��lort
in�3 posit;��Z4 �out	fra�! �g_"n��4�void�in()
{
	floatN_  Z�mul = 1.0 / 255.0�	j|(ZG *�(V,�)��,�).xyzZN$��N��6 �#��	J.rؚ),�.g� b� af)4� �vf	gl_P�9�s�� 0);
}
     ���
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
a�2  �   2�    �#version 150

uniform vec3 li  �ght_source;float timF
in�4 fr c@�ag_positA�outN$_color;rnAal�jvo ��id main()
{
	Z =�(1.0, V)�	�	z  �0	0"	V��/.xyz /..w;
}
     z�a�M�k
Wa\�   �    ��   �#version 150

uniform mat4 wv ��p_$;Fin vec4 posit�Jout�frag_�v@��oidin()
{
	� =f	gl_P�� *	on;   �
}
     f��\R
a��  8  �8   �#version 150

uniform sampler ��2D color_tex;� n<al� posit}�! depthT��float timebvec2 dPn�+s�max_Jh
#�inNfrag_V!�out�4 $_
7�void FAST32  �_hash_3D(�3 gridcell,
 � �lowz�����0?Y 1?Y 2?Y 3�+ high/i "� "� "3)
{�cmJ2 OF@ `�FSET =�(50.0, 161.0);&�DOMAIN�6 �9.0*JSOMELARGEFLOATSN4(635.2986 @ �81, 682.357502068.926525, 588.2``�55119.
ZINCV48.500388�411�3.938,�4599�279683F�V�.xyz!�-�6or(j* (	 � T�/R<))H�R'*�_inc1astep,
	(�L- 1.5�Z �v�+P0^)�:P�9�#,nH)�n4xy%P *= PZ0.xzxF3�m��P.yyww�b�;w�N<(2q�+MzM�d
)l���� 7�^ "�a�����ct(P��3�� n�)�C/�b y�b n��Cf�b F@�b n����b w��@��b �}���InterpolauC2�x) { return xkk��(Z6--5�ƿ0� �`Cubist+P
�2 range�Ʉ�_cl9;��i�-
�P)��Pf��Pi�_min�k��0��F<x�4�yz_valueRx1R	z1f	1c�Pi,7 c8grad�J�_x��Nu0.49;�	y�	y�& z�	z�& x1�1�r �	y�& z�	z	���& resultsJ�inV	esqrt(V@*�B+�;yzz%
q
A\���Pf.x,ֈ.x)\j�	y�	y�xyy*�#��� 1�� 1�1�1�~�yzz1/9 19 �	*3b�:d(b��p5);J��DzC"1�D ��3 b0�ʾlend	s�Pf*`F+mix(.%,2,�.z�
2+���JU�)-���V�final�dot(F!2.��ww2�#O�((�-A��K��f5�	^}3xmain(B	//N%vE3v0&5+�Ί3\0��ݟ���.�)�<-2�}3\F#�
+���7�2Qe(3�,[@).r�	� �Ju:"3&>gb�3o�hJ�(0);
}
     f��\R
Wa\�   �    ��   �#version 150

in vec2 posit`; �Fout�frag_�void main()
{
	� = � (+
(1.0, )) / 2.0;�gl_P��4�,  � 0N0);
}
    