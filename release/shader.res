 
a�a  	  a	   �#version 150

uniform sampler  �2D color_tex;� posit�! depth�floa  �t render_distance"vec3 camera�i�0�nt blurL
in�	2 frag_V!�out�4 $_J//����(!ad)|N�maskn�fxaa()�oid ma @P�in()
{
	if ( == 0P	F	� =�	}����else f1ZN!�$0.5�jmix(N,f6,�j�� ���
// 	siyfied ��of Dave Hoskin��s��\NH�jres�%tureSize(��,�;
uvFL�u	coH@��nstҎGA�2.399; �mat�ot�F,}s(GA1s�=X��J-�Nt3 acc��(�# J$pixel�2(.002 <�*F3.y /
��Yangle�
0,V��,d1.�99 (��jLD���0;< 8++)�{  N�+ad��N*=�<;�
ci�C�[&Zu+R4* (�-e)4�N��B��.xyzV�re5��4(�/y�?��.,��
�gn�al�d��(Rv҃
�)3)�)).rR�3c�	Kq�
����)R��L���-�^R�Vlength�p)Juk��7�%5 Nι0. 	V� ��a]�hO� smoothstep(.25�7�)��Z�V�/**
 ��Basic FXAA 'ementar bas�$thede��geeks3d.com wi�
t
modificthu ����2DLod stuff was)moveHi� it'ss@  �upport`by WebGL.
--
From:
ht� �tps://g�ub /mitsuhiko/webgl-meI   �raft
Copyright (c) 2011�Arm�Ro@0&�nacher�Some 

�%sera\RePribuJ4and �u�n sour��binary �s,C�m�D�	re pe���t�8provid$�Jfollowing�nd
�sF!et:��t��* .&s�R$�gmuE	�MJab�l�B�notice,�is lg��F�!�nd2%�claim
M�� �bD�"�du}�#!Z%q �^% <do���cuޯ�/Eohrcerials_�V� &4�9TdnE
[�n�	os��rsYy0 be��o �h�rV�mote C�	Qi�fd�=`�J�softwƈ�� spec��i�rƏnN�ss*THIS SOF@  �TWARE 0PROVIDED BY THE COPYRIGH   �T HOLDERS ANDXNTRIBUTORS
"AS�" `��ANY EXPRESS OR IMPLI9}RANTIES,  � INCLUDING, 	 NOT
LIMIT�TO,�>  !�OF MERCH<ABILITYJFITNFFOR
A PA  �RTICULAR PURPOSE �6DISCLAIMED.� 0� EVENT SHALLn:
OWNER�/�9 BE LIABL6a�E�
:DIRECTF4�C��L,}PECI(AE=ARY,RSh0�EQU�t DAMAGy(�eCUREM�--SUBSTITUT@ �E GOODJ[SERVICES; LO�_F USE%DATA�@���0BUSIJNINTERRUPTION)�Wi�A��sD ��ON�;�EORY�B�`, WHE`RFU�KA�AS�CT�	�M: (H� NEGLIGENCE�O�WISE)�ISFIJ�U�=Fja��č�,
t IF ADVI�.�	SIҋ�MCH]�*/�#if�#��f�_REDUCE_MIN��#hinevh(1.0/ 128.%9���#�if�M UL�M ULR_�L SPAN_MAX�J �J���opt4�im!3��mobil�w��ep�	�"�#z	adsI(u bot��4�t�(eckK;��	3�Coorduol,;�3x	v_rgbNW,�+d��E�* S�
S�* M) {3�	4 +FmumpNin�FeVP+�	Nc�-�	e���:yC3 �0;�
2D(�C7+��E�/ E�/ S�^ S�^ S�^ S�4�	C#�2 r!�Mv:M �
J6luma3B.299�/.587�114�
F�Mdo\U��t(���& E�	E�& S"S�L S"S�L �9�	M, �& � �n(�,����g��3I,	&%)�P ax�x,�.R�P ��di�(.F-(R�0��0����F�y� �
���f8�'�	�86 �� *��n ��5�%cQyc��� ����rcpDirNp��Jnabs(�H�y))M�/�DR7S�,[�),62F@�����-2-�9 �*�/m*;�*:V�A�FJ(^��3��N=NH3-�)E ڪ��+�y 2�O khB��/*�/+2�) -��� VL��B;/B[T�ʺB@#5) D޻�||N�B >��))&+�j�A,;s���3 B�3 #�+}3E[�#�'a� x3�����k@0.*yEzy#��+
'�S3�+a[m�D�
-����+�~+�9 +�9    �n);
}
     
Wa\�   �    ��   �#version 150

in vec2 posit`; �Fout�frag_�void main()
{
	� = � (+
(1.0, )) / 2.0;�gl_P��4�,  � 0N0);
}
     a\�ak\�\�
a��    �   �#version 150

uniform float t ��ime;�in vec3 frag_posit�;2local� ��� n]al�4�color�out�$�j��"
�-Nois0 �e3D( coord, <wavelength)�void   �main()
{
	if (�� .y < 0.5�	�		�n� I�� =��:  +�"(0.0,�U *%1,0)�1�"	J�>�T��* 2�	discardF}�1	�N5�W.rgb;��P|Niz���e(bg)�	�-=�|}�Yrand�Y�O returnFct(sed  �ot(co.xyz ,�B12.9898,78.233,144.� �7272)))�43758.5453)�simple_inte ��rpolate(�ua�xb"x�%�%a9smoothstep
e1®A�x�(b-a2bd��Rby"zC�ger_xQx -�Fx^	J�z����
��>y�yy�P 
�P z�zz�P 
2v1���J|Z2,�v��!�z)�v2�? +k 3 ��4'1  �H �5_y v#6� �G 7� �G 8�P��� ������v1,v5,*��!i2�9 2,v6�9 3�9 3,v7�9 4�9 48p��,v8~��� i1,i2,��2�� i3,i4zS��6 !,J*,yc�G9: cb� ��3�.x/�,�.y� zh);
}
     a\�ak\�\�
Wa\�  [  �[   �#version 150

uniform mat4 woP� �rld_,;rn(al� wvp�vec4 diffuse_co@�lorbfloat timeT
in�3 positY;��	��Z4 �
out	frag_"nloc�� Z�4��void ��in()
{
	N/J_mul = 1.0 / 255.0]���	3h�	0.y += s1�.r +�A * 2.0)0.�
��1�4!(e��)(t,F)).xyz�;� b<�sV��X 
,��	V/J�*�A,�.g� b� af�>v�	gl_P^2Ҙ2@0);
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
     f�a\pk\�\�
a�O  �  O�   �#version 150

uniform float t ��ime;�in vec3 frag_posit�;2local��r��
outN$_color;rn�al�j#Noise3D( ��coord, <wavelength)�void main e��()
{
	�	n� =��4 -
(0.0,J? * 0.25R���,0)�1F	if (>\75�(1.0	(�.y�5)诰))�	discard
*	�FY���G� -=�e}�MrandjMNC � �returnFct(s�dot(co.xyz ,�12.98  �98,78.233,144.7272943758.5453) P��simple_interpolate(Ziablb"x�%�%a + ��� smoothstepJd1x�(b-a2bdb�Rby"zC���W�ger_xQx)�Fx^	J�y
Jt>y�yy�P 
�P z�z=oҮz�P 
2v1���J|Z2,!�z)�v2�? +k 3 ��4'1  ��É�H �5_y v#6� �G 7� �G 8�� ������v1,v�&��!i2�9 2,v
��6�9 3�9 3,v7�9 4�9 4,v8~��� i1,i2,��2�� i3,i�>J�4zS��6 !,J*,yc�G�8 cb�3�.x/�,�.y� zh);
}   �
     f�a\pk\�\�
Wa\.  �   .�    �#version 150

uniform mat4 woP �rld_,;vvp�
in vec3 posit)Jout�`�frag_�nlocal�
void�in()
{
	���� = (�% *�4(V, 1.0)).xyz;V��b	gl_  �P�R5�V 0);
}
     f��\R
a��$  �  �$�   �#version 150

uniform sampler ��2D color_tex;� n<al� posit}�! depth ��float timezrender_distanc&vec3�0� cameraX
in�2 frag_�!�out�4 $_�7��Jwater(Juv,Rdir)�� GetEdgeWeigh �t()�oid main()
{
	�fog� =
�3(���1.0), ��	��A�%ture(�E,n0).F+	if � =�1{�=
P	�41 �	reeF@	})3�obt�xyz;���zH��< (VZ�>;gb;N+�I�}�length(N| -Z$)�am_$t`���3�-  /jlFw�dot(,�K
�1mix�0��xN*0.75��a�)��lin�2�Q>��*=F�0.y <j��>horizJg������xz
#35,�G
*4�N6�)b�J��d<��)��F��RNJZ�,�w/:�P  �else��}��
// "Wind Waker Ocean"   ��by @Polyflare (29/1/15)�License   �: Creative Commons AttribuJ�4�In���9n�onalRSour�code=r the�� gen�	��i � �s available at:�https://github.  l�com/lmurray/circle��-O
  JUsysetti(��ngs30MDo���ort�3J�V5J
1�Apply l	�JtB @�o�6 #def�DISTORT_WATER 1�is�GpaEla�@сx eff�
s�ChangeJh�� of�w�= VPARALL��AX�z Antialias�� Fa�+ �FAST_CIRCLESVg C��^�3_COL�0.9y�4453�730��2�0J
0418� �6758�FOAM^q�M_2PI 6.283185307�6�l18.84955592�k�,�c,#�sJ c�abs���(��c�m��B�#Y�_��,��s ? -F:�0�a0 ��smoothstep(�F002, sqrt(s)��Z))���u�Jndif#�		Foamq
t@3'��c�tructed��ae�1��ries
sVM
lay;�^Juv�Dod(�b �Cl�%F�[0.�Y�.1]�
+N	t��T+=Nf#�2�37378�?277169)�B26  �8181)�: 0317477F540372193742�< 430A�044882218�32337�; 64103
�695106�17864� 14639�;079134R2994I� 871�394C
"���8908� 90�6J;78141�466�: 31�9
;866m���;�9�; 92861Jg19598�I52!�'�50N,%53Z�60�< �@�30��,1949�,080610�349922F449714�2JS�6�d0�55
-95341h312�*�76�v5e	0��15127� P�C�5635NY29�v9%�; 693,=	VJ9811	 8�
��2�3�74�� 56929�,62w13240�29834�7109�1�"b�44�dN��7aY0�719�509�376�21615�11Af�9673�198Ҕ12462�e62�
Y954+�873�3435��f�΅66278�����v9�6�g8Q	�96F��5�J634�: 5h`f�148Nv8V�623523�< -57�e51��v68��E0�g76"9�93T156�7488Nv41332�11a�c636�,8y1+�36TNF�20�� 9y8�73R;&43�� 64y�5431!1�w 6�����#����87�� 4�2
�3824օ1Q�115��6256ұi	55�� 
U/�4y8,4162�4)0�; 3�8�v�)�50�894�J6579����J6�"�*52A!
�572�Rh417�n43iNh113	2]3�658��21�,9-+m��#�~a��326ֲ7068�249
528-I	h4��665�x 0%
47236
3U2�� 932H	�4�4��u �2
4432
�
��xو�490+,�#��!9�33+7)+508� 040�)�v�3�
P�w 6&r;��8N�46�R;%2�f�4Γ!+m
05�"�T�7N�14�04��M!:�,F�c�4Z�E672�99#Z583�J��� �879ʰ89�g67�(�� ���8�v682��;��wA18��2+�4593��Y,�=93���� 8�"�x��vY#55VJ�0���854�370V,396�cy-e97Vv�*4��	�+�ӕ-;�
8�0�	37�(��5!3]"+�6��= 5��-5311+.�*01��0�J���};+���1�	ʣ818��85��09u1���=775�88��7�#!��9463�	4754��! 03��2�;�	M�< 184}�
3�Y.E��815�E���+\25��	mJ�5;�839��2Y*��
+m�97�G	"�q03�60���y��#��hx(,�);;(ProceduRcEZS9�Ka�7�l,[�"�.��+G#iC�gtwoPr�Uv�JatZs��XLfeA_;g%K.�J,a��
��I�e5�L-�/�y;�!off�ZK�h�s�Ouv.x +.�H�,��k��UVZ@�a�h?V4�1l
-#�02�y��J +��SS�CT�r^Qf2�}��d13��2�,S�R
2R
�
JuM1.36�0�07�d12e�;�&5�2;"gF+ ҍ�	�Ld1����J2Ni�	cos�	J�	�	)[r����~��nZ�(3#�X3,C�,K-�n�-r)��N
�+�j
"Mu-NyxfG\���S�GPUQoms Upg 443-�<�F362��s[9]RA[](I���#�2(FP, 5,Zs,yb�
v�* 1�T R�T r-1� P#��7Pix�w��elSiz+�/+�K[ D�Q3�N���	or(i�iR;< 9����++K2"SeY�\i]�
(�d���]�	�#j
KJ�
�}C4Ult�U�as1+ N1],�;2�3�4]+��2�5�
6�7�8]�U�Z����-�	0�^N	��	Jv4��F�u�,&�
in�
��#tL��^Res8���ultF��* 25���"�:��kZ��;1Qj
2�) zn
3�) wn
4W���v
[�)5�T 2�)6�) �)7�) �)8�� �7z�ο�k�,y�v6
Ƅ*,*~�C�r
�  �j)25;
}
     f��\R
Wa\�   �    ��   �#version 150

in vec2 posit`; �Fout�frag_�void main()
{
	� = � (+
(1.0, )) / 2.0;�gl_P��4�,  � 0N0);
}
    