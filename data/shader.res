 k\�\�
a��    �   �#version 150
in vec3 frag_posi
��tl;2normal�4�colorTout�$Zunif�N  �light_sourcep
void main()
{
@ (�	float
dot = clamp(0(�ize(b#), ) �& -.3)�0.25, 1.0);.�* 2.0���	if IC}�N >0)L	�8�mix(B,�@(�J^��*5J else]  �q 0^�-�5);
}
     k\�\�
Wa\)    )   �#version 150
in vec3 positX;�n  ��ormalZ4 color@out�frag_�n�4��u �nif� mat4 world_,vN� screen��dif��fuse�
void�in()
{
	

N =�(J.r R�� / 255.0,�;.gvbvaV)�	*Eq(�6 *NV, 1����).xyzZ�;�^>��6 2R*�@	gl_P%�N�� 0);
}   �
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
a��  L  �L   �#version 150
in vec4 frag_posi�tl;
outN$_colorTuniformF3 ligh �t_source"float timF
void FAST3 ��2_hash_3D(�gridcell,
 �  lowz�0U�?Y 1?Y 2?Y 3�+ hM/i "� "� "3)
{�consJ2 OFF  0�SET =�(50.0, 161.0);&rDOMAIN�69 �.0*JSOMELARGEFLOATSN4(635.29868   �1, 682.357502068.926525, 588.2500�5119.
ZINCV48.500388�411�3.934�599�279683F�V�.xyz!�-�6or(j* (	 /y*�R<))H�R'*�_inc1astep,
	(�L- 1.5�Z +m;��P0^)�:P�9�#,nH)�n4xy%P *= PZ0.xzxF3P�޿.yyww�b�;w�N<(2q�+MzM�d
)l���� 7�^ "�a}c����t(P��3�� n�)�C/�b y�b n��Cf�b F@�b n����b w���b  ��}���Interpola_C2�x) { return xkk��(Z6--5�ƿ0� �`Cubist+P
�2 range�&�_clamp;��i�-
�P)��Pf��Pi�_min�k��0��F<V Әxyz_valueRx1R	z1f	1c�Pi,7 c8grp�*�ad_x��Nu0.49;�	y�	y�& z�	z�& x1�1�r �	y�& z$P��	z�& resultsJ�in�esqrt(V@*�B+�;yzzq��%
q
�Pf.x,ֈ.x)\j�	y�	y�xyy*�#��� 1�� 1�V�ͷ1�1yzz1/9 19 �	*3b�:d(b��p5);J��DzC"1�D ��3�*� blend	s�Pf*`F+mix(.%,2,�.z�
2+���JU=s��)-��V�final�dot(F!2.��ww2�#O�((�}��-K��f5�	^}3xmain(B	�L+��;�	/2@	�2d�F2A��ance(	,SF	if (�>��P� 	3LC*�-R0N0	}a{?�elseN!v�300�(Z4J�3\����k-2R�3\�Q�
+-Z��9�f.5.		v�vR)�-�f�02�-�7�� �f
	}
}   �
     z�a�M�k
Wa\�   �    ��   �#version 150
in vec4 positX;
 �outfrag_buniform mat4 screen_0� $�h
voiddin()
{
	j =f	gl_P�� *  ��	on;
}
     zډ
a��  �  ��   �#version 150
in vec3 frag_posi
��tl;2normal�4�colorTout�$Zunif�N @�light_source"float timF
void F @ �AST32_hash_3D(�gridcell,
 �  loT��wz�0?Y 1?Y 2?Y 3�+ hM/i "� "� "3)
{�consJ2  � OFFSET =�(50.0, 161.0);&rDOMAI� ��N�69.0*JSOMELARGEFLOATSN4(635.2  �98681, 682.357502068.926525, 58 C �8.255119.
ZINCV48.500388�411�3��a�.934599�279683F�V�.xyz!�-�6or(j* ���(	 /R<))H�R'*�_inc1astep,
	(�L- 1.5Ӷ��Z +P0^)�:P�9�#,nH)�n4xy%P *= PZ0.xn��zxF3P.yyww�b�;w�N<(2q�+MzM�d
)l���� 7�^ ����"�aqct(P��3�� n�)�C/�b y�b n��Cf�b F@�b n����b � "�w���b �}���InterpolaJ_C2�x) { retu���rn x(Z6--5�ƿ0� �`Cubist+P
�2 r l2�ange_clamp;��i�-
�P)��Pf��Pi�_min�k�m2��0��F<xyz_valueRx1R	z1f	1c�Pi,���7 c8grad_x��Nu0.49;�	y�	y�& z�	z�& x1�1�r U@��	y�& z�	z�& resultsJ�in�esqrt(V@*�B+�;yuW�zz%
q
�Pf.x,ֈ.x)\j�	y�	y�xyy*�#��� j���1�� 1�1�1yzz1/9 19 �	*3b�:d(b��p5);J��DzC"̡�1�D ��3 blend	s�Pf*`F+mix(.%,2,�.z�
2߃0�+���JU�)-��V�final�dot(F!2.��ww2�� �#O�((�-K��f5�	^+��	etHorizonTex]e(O^-�	
P+S)	N0dq0ance(�,S�	if (�>��P����F	3CC!�+R0.	}elseN!v�3'0�(��.
�3\���z�ٵh��h-2RA	3\�O�
+9�f.5.		vҌvR)�-�f�02�-	�����l�6�� 15dmain�`N7R�҉�ize(C�)�^�
�n
��؟����

/@5;N�4 *h;
.rgbO^5R{*.y~�O�|+=�vjJ復
  �,�,�7.y);
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