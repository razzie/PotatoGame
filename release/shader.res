 a\�ak\�\�
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

uniform sampler ��2D color_tex;� n<al� posit}�! depth ��float timezrender_distanc&vec3� � camera�bool horizon\
in�
2 fra�t �g_�'�out�4 $_J=�
water(Juv,dir)� �N&GetEdgeWeight()�oid main()
{D؃
	�fog� =
�3(1.0), ��	��G��ture(%�=�K,n0).F+	if � ==
P	�41 �	reeF@	})��3�ub�y�xyz;�����< (V�>;gb;N+�I���lengthRT6�(� -Z$)�am_$t`3�-  /jlFw�dot(,�K
�1x���mix�0��xN*0.75)��lin�2�Q>��*=F�� �'��&&Z3.y <��'��	xz
$35,�H)4N1�,J��^<��)���ʻ�P �RNDZ�,�q/:�else��}��
// "Wind Waker   � Ocean" by @Polyflare (29/1/15)  ��License: Creative Commons Attr(��ibuJ�49In�n�onalRSour�code=r thea ���� gene	��is available at:�https:/   �/github.com/lmurray/circle��-O
  J(�Usysettings30MDo9��ort�3J�V5J
1�ApplxB �y l��Jto�6 #def�DISTORT_WATER 1�$�@�is�GpaElax eff
s�ChangeJh�� of�w���= VPARALLAX�z Antialias�� Fa�+ �FAST_C�C�IRCLESVg ^�3_COLh0.9	�4453�730��2���0J
0418�6758�FOAM^N�M_2PI 6.283@�185307�6l18.84955592��Sq,�c,#�s���2 c�abs(�Ac�mm�*�#Y�_��,��s ?�0� -F:�0�a�smoothstep(�F002, sqrt8���(s)��Z))�Jndif#�		Foamq
t@3'��c�tru��1�cted��aeries
sVM
lay;�^Juv�Dod(�J �Y��Cl�%F�[0..1]�
+M	th�T+=Nf#�2�37378�?27   �7169)�B268181)�: 0317477F54037219�3742�< 430044882218�32337�; 64103
�@�695106�17864� 14639�;079134R2994IC
�� 871�394��8908� 90�6J;78141�466�: 3���1�9
;866m;�9�; 92861Jg19598�I52!�'�50���N,%53Z�60�< 30��,1949�,080610�349922F�J�449714�26�d0�55
-95341h312�*�76�v5e	�P��0��15127� 5635NY29�v9%�; 693,=	VJ9811	 ��8�
��2�374�� 56929�,62w13240�2983B�"�4�7109�144�dN��7aY0�719�509�376� A�21615�119673�198Ҕ12462�e62�
Y954+����873�3435΅66278�����v9�6�g8Q	�96F��Fh`�5�J634�: 5148Nv8V�623523�< -57�e51��v,"�68��E0�g7693T156�7488Nv41332�11a�c63*TN�6�,8y1+�3620�� 9y8�73R;&43�� 64y�543�£1!1�w 6������87�� 4�2
�3824օ1Q�115��6�
U�256ұi	55�� 4y8,4162�4)0�; 3�8�v�)�50�8��94�J6579�J6�"�*52A!
�572�Rh417�n43iNh11�3	2]3�65821�,9-+m��#�~a��326ֲ7068�24�h4�9
528-I	665�x 0%
47236
3U2�� 932H	�4�4��xو�u �2
4432
�
��490+,�#��!9�33+7)+508� 040�r;��)�v�3�
P�w 6&8N�46�R;%2�f�4Γ!+m
05�"�T�7N�14�F���04��M!:�,4Z�E672�99#Z583�J��� �879ʰ���89�g67�(�� 8�v682��;��wA18��2+�4593��Y,����=93���� 8�"�vY#55VJ�0���854�370V,396�cy-e�+��97Vv�*4��	��-;�
8�0�	37�(��5!3]"+�6��= 5��-531��J�1+.�*01��0��};+���1�	ʣ818��85��09u1���=77���5�88��7�#!9463�	4754��! 03��2�;�	M�< 184}�
/�E�3�Y.E��815�+\25��	mJ�5;�839��2Y*��
+m�97/���G	"�q03�60y��#oUhx(,�);;(ProceduRcEZS9���.�K�`�7�l,[�"+G#iC�gtwoPr�Uv�JatZs��XLfek�ĊA_;g%K.�J,a�I�e5�L-�/�y;�!off�ZK�h�s�Ouv.جk�x +-�H�,�UVZ@�a�h?V4�1l
-#�02�y��J ��}�+��SS�CT�r^Qf2d13��2�,S�R
2R
�
JuM1.36�0Ie˻�07�d12&5�2;"gF+ ҍ�	�Ld1����J2Ni�	c����os�	J�	�	)[r~��nZ�(3#�X3,C�,K-�n��q)��N
�+�j
"�G�Mu-Nyxf��S�GPU�nms Upg 443-�<�.32���J��s[9]RA[]	J(FP, 5,Zs,yb�
v�* 1�T R�T r-1�w�� P#��7PixelSiz+�/+�K�[D�Q3�Nr��	or(i����iR;< 9++3#"5KMY�\i]�
(�d���]w	�#j
K2+�Պ
�}C4Ultas1+ N1],�;2�3�4]+��2�5�
6�����7�8]�U�Z�-�	0�^N	��	Jv4��F�u�,&�
in�
�8���#tL��^ResultF��* 25���"�:��kZ��;1Qj
2UW���) zn
3�) wn
4v
[�)5�T 2�)6�) �)7�) �)8�� �7z�ο�k�,y�v6
� �Ƅ*,*~�C�r
�j)25;
}
     f��\R
Wa\�   �    ��   �#version 150

in vec2 posit`; �Fout�frag_�void main()
{
	� = � (+
(1.0, )) / 2.0;�gl_P��4�,  � 0N0);
}
     f��\R 
a��  .  �.   �#version 150

uniform sampler  �2D color_tex;� posit�! depth�floa  �t render_distance"vec3 camera�i� @�nt blur�bool antialiasd
in�2 f0��rag_�'�out�4 $_�5��(R'ad)|N�mask �n�fxaa()�oid main()
{
	if ( PIЇ== 0P	F	� =�	}else f1ZN!�$0.25C����mix(�,�6J,J��� ���
// 	si�yfie <�d V�of Dave Hoskins��^�H
kres��ture�2��Size(Z�,�;
uv�Lzv	const��GA�2.399; �C{��mat�otG,}s(GA1s�J-��t3 acc��(���# J$pixel�2(.002 *F3.y /
��Yangl�L��e�
0,֐�,d1.�9Y (F�jL0;< 8++)�{  ��/�N�+ad��N*=�<;�
ci[&Zu+R4* (�-e)4���Ǝ��B��.xyzV�re5
�4(�/�.,��
�gn��zed������(Rv҃
4�)3D�)).rR�3~�	K��
)���L��-�;�lengܟ>�th!�)�uk�"8�(= N�0. 	��a]�iO smoothstel �p(��7�)򼚻V�/**
Basic FXAA (eme#�ntar bas�$thedegeeks3d.com wi���
t
modificthu��2DLod stuff waBA@�s)moveHi� it's%support`by WebGL  ��.
--
From:
https://g�ub /mit � �suhiko/webgl-meIraft
Copyright "@� (c) 2011�Arm�Ronacher�Some 

�%sL�era\RePribuJ4and u�n sour��binar��y �s,C�q�D�	re pe�t�8provid$�Jfoll �t�owing�nd
�sF!et:��* .&s�R$�gmuE	�YJabg�l�B�notice,�is lF�!�nd2%�claim
M�� ��/��bD�"�du}�#!Z%q �^% <docuޯ�/Eohrcer�%s_[���V� &4�9TdnE
[�n�	orsYy0 be��o �h�rV�5��mote C�	Qi�fd�=softwƈ�� spec��i�r% �ƏnN�ss*THIS SOFTWARE 0PROVIDED B   �Y THE COPYRIGHT HOLDERS ANDXNTR P �IBUTORS
"AS�"�ANY EXPRESS OR I0  �MPLI9}RANTIES, INCLUDING, 	 NOT�@�
LIMIT�TO,�> OF MERCH<ABILITYJ  �FITNFFOR
A PARTICULAR PURPOSE 0 ��6DISCLAIMED.� EVENT SHALLn:
OW���NER�/�9 BE LIABLE�
:DIRECTF4�C��L,}��PECI(AE=ARY,RSEQU�t DAMAGy(�eCU �REM�--SUBSTITUTE GOODJ[SERVICES; �C�LO�_F USE%DATA���0BUSIJNINTERRUP���TION)�Wi�A��sD ON�;�EORY�B�`, WHE`V> �RFU�KA�AS�CT�	�M: NEGLIGENCE�O�WIS���E)�ISFIJ�U�=Fja��,
t IF ADVI�.�	Sf� �Iҋ�MCH]�*/�#if�#f�_REDUCE_MIN��#hi@I�nevh(1.0/ 128.�#�if�M UL�M ULR_�L SPA��N_MAX�J �J���optim!3��mobil�w��ep�	�'̭"�#z	adsI(u:tt�(eckK; �	3�Coorduol�B�,;�3x	v_rgbNW,�E�* S�
S�* M) {3�	4 +	Fmum_ƫpNin�FeVP+�	Nc�-�	:yC 3 �0;�
2D(�C7+��E�/ E�/ SU-���^ S�^ S�^ S�4�	C#�2 Mv:M �
J6luma3C.299�/.5��U�87�114�
F�Mdot(���& E�	E�& S"S�L S"S�L �9�	8�K�M, �& � �n(�,���3I,	&%)�P ax�x,�.R�P ��,���di�(.F-(R�0��0F�y� �
���f8�'�	�86 ���� *��n ��%cQyc��� rcpDirNp��Jnabs(�H�y))M_����/�DR7S�,[�),62F@�-2-�9 �*�/m*;�*:V�A�FJ(^��3���V��N=NH3-�)E +�y 2�O khB��/*�/+2�) -��� VL��!��B;/B[T�ʺB@#5) ||N�B >��))&+�k�A,;s���3 B�3 �w��#�+}3G;�3m3�c���+�x3*kW0.ny^eE�y#�+�J-�SL�+z[����	!E*-J���+��: +�: +�: ��R6��6
	}
}
     f��\R 
Wa\�   �    ��   �#version 150

in vec2 posit`; �Fout�frag_�void main()
{
	� = � (+
(1.0, )) / 2.0;�gl_P��4�,  � 0N0);
}
     \ak�f�a\k\�\�
a�  �   �    �#version 150

in vec3 frag_po(P�sitt;2normal�4�colorT
out�$�j�  ��"
void main()
{
	Z =b.rgb�	� ��|Nize(",)�	�on;
}
     \ak�f�a\k\�\�
Wa\F  �  F�   �#version 150

uniform mat4 woP� �rld_,;rn(al� wvp�vec4 diffuse_co@ �lorbfloat time�3 start_posvend�0� �
in@it;��(Z4 �
out	frag_"n��� �4�void�in()
{
	�3dist = m`len�A�gth(� -�5), �7));�swing=0.125 * ��x�sqrt(�)F��.x +�Rd2.0
�G�+*
;(1.0v��,yJ5F��:_mul�� / 255.0
'�N|(ڊ�4�5,���Y�)).xyzNU�����6 �"��	J.r�Z(,�.g� b� af�R� ���	gl_P^8��70);
}
    