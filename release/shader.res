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
a��  =  �=   �#version 150

uniform sampler ��2D color_tex;� n<al� posit}�! depth ��float timezrender_distanc&vec3�0� cameraX
in�2 frag_�!�out�4 $_�7  ��void FAST32_hash_3D(Jgridcell,�
 � �lowz�0?Y 1?Y 2?Y 3�+ high/i "� "� "3)� �
{�consJ2 OFFSET =�(50.0, 161.0��);&��DOMAIN�69.0*JSOMELARGEFLOAT  �SN4(635.298681, 682.357502068.9  ��26525, 588.255119.
ZINCV48.5003� ��88�411�3.934599�279683F�V�.xyz!E$��-�6or(j* (	 /R<))H�R'*�_inc1astep
�m�,
	(�L- 1.5�Z +P0^)�:P�9�#,nH)�n4xy%P`�� *= PZ0.xzxF3P.yyww�b�;w�N<(2q�+Mz���M�d
)l���� 7�^ "�a�ct(P��3�� n�)�C/�b y�b n�����Cf�b F@�b n����b w���b �}���InterpolawC2�x���) {�turn x(Z6--5�ƿ0� �`Cub�+P�Ʉ
�2 range_clA;��i�-
�P)��Pf��Pi�_min�ȴ�k��0��F<xyz_valueRx1R	z1f	1c�P��i,7 c8grad_x��Nu0.49;�	y�	y�& z�	z�& x1�V	�1�r �	y�& z�	z�& resultsJ�inX	esqrt(V@*�B+�;�A\�yzz%
q
�Pf.x,ֈ.x)\j�	y�	y�xyy*�#���~��� 1�� 1�1�1yzz1/9 19 �	*3b�:d(b��p5);J��DΡ�zC"1�D ��3 bl�*	s�Pf*`F+mix(.%,2,�.z�
2߃0�+���JU�)-��V�final�dot(F!2.��ww2��_Ч#O�((�-K��f5�	^}3xmain(B	�$Mm0�e(3),����[�y;�if � <�1)P	�0card"��3��rgb;�_�����;��#yz��K�< ZAl�t�Y�gNiz����,*$u
�Y�|��	=*�NV.y�F`FbR!horiz
130E,%�7J�3\0��]����J{)�-2R~�3\Ɔ�
+9F#�)ƿ�R, vQJ,� .
�	�}fO+%M�
gth�3F//R�og_"ck�=N��V>�FO//	3\^4�=��4N�f�E�

^h�-���
else~v"z�<v7��ϙ �/�F �*  �~*z0);
}
     f��\R
Wa\�   �    ��   �#version 150

in vec2 posit`; �Fout�frag_�void main()
{
	� = � (+
(1.0, )) / 2.0;�gl_P��4�,  � 0N0);
}
    