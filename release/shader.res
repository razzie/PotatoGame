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
a��    �   �#version 150

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
2߃0�+���JU�)-��V�final�dot(F!2.��ww2��? �#O�((�-K��f5�	^_// GPU Gems 3, pg �� 443-444+zGetEdgeWe�t(g	~offsets�M~�[9]#%
[](pJ(��),Z-1F�b�
v�* 1�T R�T r-1� ���P�W�7PixelSizey���4�e(3�Q�#
SQP3 N�����	Mint �0;< 9++ {& uvw;>��\i]�	[ŧ�(�	�d=�)(3�,9).r

�#j
;F�
gb}C4Ultas1�BU�V�N1],�;2�3�4]);�2�5�
6�7�8]�U�abs�����-�	0�^N	��	Jv4 max��ax�,&�
in�
@�
�v8�1&�^R0+ �* 25���"�:.x#kZ��;un
2�) zn
3�) wn
����4v
[�)5�T 2�)6�) �)7�) �)8�� �7z�ο�k�!y�v6
Ƅ*,*~�#��+��G�r+, j0�;3Yma�	#~i
��S8��if � ==�)Gca����rd+���C��'��6�T2�63��K��< ZAl�������Z,�(ʑ�G���8�
#��*j*Elin+-k"��=a�$]<b�Nhor��Y�iz
D3��!C�+�0.1l�,o-2R��3ڔ1�0.9&A����R, vQRI�.J9}fE+M�"gth��ڡ<kRJ�3�'4j�h��,/�  �:�else6�0);
}
     f��\R
Wa\�   �    ��   �#version 150

in vec2 posit`; �Fout�frag_�void main()
{
	� = � (+
(1.0, )) / 2.0;�gl_P��4�,  � 0N0);
}
    