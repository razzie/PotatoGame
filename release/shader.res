 
a��  �  ��   �#version 150

uniform sampler   �2D color_tex;in vec2 frag_posiF �t�out�4 $_J�/**
Basic FXAA i  �menta� based $the�degeeks3d.co@ a�m withF
modificthat
eture2DLo  �d stuff was removeHince it's7su   �pport`by WebGL.
--
From:
htt@ �ps://g�ub /mitsuhiko/webgl-meIr  ��aft
Copyright (c) 2011�Arm�Ron �acher�Some 

�%sera\RedistribuJ4an��d us�n sour��binary �ds,Cor
��D, @��are pe�t�8provid$�Jfollowing�nd�nsS��F!et� * .&s ofV$�gmusttaimab�l�B� �3�  notice,�is li�!�nd2%�claim
M�� �bD�V��"�du}�#!Z%q �^% <docuޯ�/Eohr materi��E�als_�V� &4�9Tdname
[�n�	orsYy0 be��o��6� endh�rV�mote C�	d)�fd�=softwƈ�� sX% �pec��i�rƏnN�ss*THIS SOFTWARE 0PR   �OVIDED BY THE COPYRIGHT HOLDERS P� ANDXNTRIBUTORS
"AS�"�ANY EXPR 0 �ESS OR IMPLI9}RANTIES, INCLUDIN��G, 	 NOT
LIMIT�TO,�> OF MERCH<� �ABILITYJFITNFFOR
A PARTICULAR  0�PURPOSE �6DISCLAIMED.� EVENT SH��ALLn:
OWNER�/�9 BE LIABLE�
:DIRECT���F4�C��L,}PECI(AE=ARY,RSEQU�t DAM4 �AGy(�eCUREM�--SUBSTITUTE GOODJ[SE ��RVICES; LO�_F USE%DATA���0BUSIJN ��INTERRUPTION)�Wi�A��sD ON�;�EORY��V>�B�`, WHE`RFU�KA�AS�CT�	�M: NEGLIGEN���CE�O�WISE)�ISFIJ�U�=Fja��,
t IF pf�ADVI�.�	SIҋ�MCH]�*/�#ifndef�_REDU@1 �CE_MIN��#hinevh(1.0/ 128.0)�if�M $��UL�M ULR / �L SPAN_MAX�J �J���/optimi4;�z�+� mobil�w��ep�� �#z	ads cau  ,�bottleneck
fxaa(;P�,;DCoorduol�
�,+�N �v_rgbNW,�E�* S�
S�* M) {�++�Fmu$���mpNin�FeVP =JRc�-.e:y)�3 �03�(�C7).��Z�xyz�E�/ E�/ S�^ S�^ S�^ S�4�	CG�2 Mv:M �
J6lum �aR3(0.299, 0.587�114flo�"F�Mdot(W�1����& E�	E�& S"S�L S"S�L �9�	M, �& � = e((�,���3]�g�I,	&%)�P axax,�.R�P ��di�(.F-(R +�x�� - F�y� �
���f8�'�	�86 �� *��n ��5�%cQǯyc��� rcpDirNp��Jnabs(�Hy))M�/�DR7S�,[�)���,62F@�-2-�9 �*�/m*;�*:V�A��(^��3��N=NH3-�����)E +�y 2�O khB��/*�/+2�) -��� V�*��B;/B[Tif��~�B <+5) ||N�B >��))&c#��	'3s�else�3 B�3 �7(���urn3}F2voidA
!�	c�;S%!(39Q��uvx�@0.*��ފy`�]�3s�o"S���;f[r		�
-
 ���+�~+�9 +�9 n);   �
}
     
Wa\�   �    ��   �#version 150

in vec2 posit`; �Fout�frag_�void main()
{
	� = � (+
(1.0, )) / 2.0;�gl_P��4�,  � 0N0);
}
     k\�\�
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
a�  �  �   �#version 150

uniform sampler ��2D color_tex;� n<al� posit}�! depth ��float timezrender_distanc&vec3�0� cameraX
in�2 frag_�!�out�4 $_�7��NNoise3D(�Ioord, <wavelength) ��GetEdgeWeight(
void main() R��
{
	�fog� =� ((1.0), ��	��F�qtu(!�re(�J,.5).0	if � ==
P	�91 �	reeE	����})3|"�>gb;���^�:xyz��&��< �Il]�dot�Y��iz�
� -����X	�8mix�7, bb�*0.5)*Ilix�ne 
Z�>��*=Fi�$.y <jjNhoriz
Dsmooth �]�step(0.4,!6,�N+�.��,
�F
�14)�/05�0.9����5�}f?���C�()b��������lڣ<6�)v�R#4�c�bګ,/:�P�a�else��}��randj�N� N�Ɯct(s���coF� ,��2.   �9898,78.233,144.7272)�Z43758.545$ ��3)�si�_interpolate(3QaC]b"x�%�%a�0v��,1x�(b-a2bdC�Rby"zC�g�xAx��Fx^	J�z����
�>y�yy�P 
�P z�zz�P 
2v1���J|Z2,�v��!�z)�v2�? +k 3 ��4'1  �H �5_y v#6� �G 7� �G 8�P��� ������v1,v5,*��!i2�9 2,v6�9 3�9 3,v7�9 4�9 48p��,v8~��� i1,i2,��2�� i3,i4zS��6 !,J*,yc�GN cb�4��3�.x/�,�.y� z"�%// GPU� ms 3yg 4430 ��-444�@
30
2 offsets[9]1
2[](��(�, �Z~��-ʭ�b�
v�* 1�T R�T r-1� P#�
�7PixelS�&#K	/+
Ky
�I"�[D�
Q3E
N�	��	or� i]0;< 9++3k	�uv%K_
���+��\i]](9	�d��uv#�	�#j
K�
;}C4Ultas1+N1]*Te�,�;2�3�4]);�2�5�
6�7�8]�U�abs�-�	0M�^N	��	Jv4�3x��	ax�,&�
in�
@��
1&�^Res8�o�ultF	�* 25���"�:.x#3kZ��;1�.j
2�) zn
3�) wn
����4v
[�)5�T 2�)6�) �)7�) �)8�� �7z�ο�k��R6
Ƅ*,*~�#�;  �Z
�j#25;
}
     f��\R
Wa\�   �    ��   �#version 150

in vec2 posit`; �Fout�frag_�void main()
{
	� = � (+
(1.0, )) / 2.0;�gl_P��4�,  � 0N0);
}
    