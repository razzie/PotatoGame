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
a�M%  �  M%�   �#version 150

uniform sampler ��2D color_tex;� n<al� posit}�! depth ��float timezrender_distanc&vec3� D� camera�bool horiz!turF
in�2 f0ҁ�rag_�)�out�4 $_J?�
water(Juv,dir �)�N(GetEdgeWeight()�oid main()
`�{
	�fog� =
�3(1.0), ��	��I��0(�M,	q��n0).F+	if � ==
P	�41 �	reeF@	})3�w��x�b�{�xyz;�����< (V�>;gb;N+�I���length(��� -Z$)�am_$t`3�-  /jlFw�dot(,�K
�1mi^0�x�0��xN*0.75)��lin�2�Qsqrt(r�b*=��#<ѯƀ2� &&�6.y <��*+���	xz�'35,bL)4�4��/ʞb<6�)���v��J�R�Gڦ,u/:�else��}F�
// "Wind Wa  @�ker Ocean" by @Polyflay(29/1/15  �)�License: Creative Commons AttP
!�ribuʷ4qIn�n�onalRSour�code=r th�  �e� gen�	�is available at:�https:   �//github.com/lmurray/circle��-O
  	PƋJUsysettings30MDoqN�ort�3J�V5J
1�App�� �ly l��Jto�6 #def��DISTORT_WATER 1I@���is�GpaElax eff
s�ChangeJh
� of�w`��= VPARALLAX�z Antialias�� Fa�+ �FAST_��CIRCLESVg 
&replace��4_COL,�2�d F���OAMJ	cu��aluebFZ�0.9�4453�730F˪
��2�0J
0418�6758�"31�M_2PI 6.28318P |�5307�6l18.849555929F��u,�c,#?s� ��}�c�abs(�}cN�m��y�#]&p4,��s ? -u �F:�0���smoothstep(�F002,�s)+�Z))���	�Jndif#��Foamut�3hΟc�truct%�UairؘX�iesKsVM
lay;�^Juv�Dod(�� �Cl'��[0..�,�1]�
+�	t��T+=Nf#6	2�37378�?277169)�B268�181)�: 0317477F540372193742�< 4300� �44882218�32337�; 64103
�695106�17a�864� 14639�;079134R2994I� 871�394�!��8908� 90�6J;78141�466�: 31�9
;866m;AΤ�9�; 92861Jg19598�I52!�'�50N,%53Z�60�< 3�@ �0��,1949�,080610�349922F449714�26%����d0�55
-95341h312�*�76�v5e	0��15127� 5�ơ�635NY29�v9%�; 693,=	VJ9811	 8�
��2�37���4�� 56929�,62w13240�29834�7109�14n1�4�dN��7aY0�719�509�376�21615�119� 3�673�198Ҕ12462�e62�
Y954+�873�3435΅�W��66278�����v9�6�g8Q	�96F��5�J634�: 51403�48Nv8V�623523�< -57�e51��v68��E0�g769���3T156�7488Nv41332�11a�c636�,8y1+�362*'��0�� 9y8�73R;&43�� 64y�5431!1�w 6����S����87�� 4�2
�3824օ1Q�115��6256ұi	55�� 4���y8,4162�4)0�; 3�8�v�)�50�894�J6579�Jf�L�6�"�*52A!
�572�Rh417�n43iNh113	2]3�6582�G��1�,9-+m��#�~a��326ֲ7068�249
528-I	64�65�x 0%
47236
3U2�� 932H	�4�4��u �2
4432
�
��4�lį90+,�#��!9�33+7)+508� 040�)�v�3�
P�w 6&8��K�N�46�R;%2�f�4Γ!+m
05�"�T�7N�14�04��M!:�,4#�1�Z�E672�99#Z583�J��� �879ʰ89�g67�(�� 8�Yx��v682��;��wA18��2+�4593��Y,�=93���� 8�"�vyD<�Y#55VJ�0���854�370V,396�cy-e97Vv�*4��	��-�ۆ�;�
8�0�	37�(��5!3]"+�6��= 5��-5311+.�*01��0��o%��};+���1�	ʣ818��85��09u1���=775�88��7�#!9����463�	4754��! 03��2�;�	M�< 184}�
3�Y.E��815�����+\25��	mJ�5;�839��2Y*��
+m�97�G	"�q03�60yg�����#��ix(,�);;(ProEPu�c��S9��K�a�7�l,[W�"+�#�C ѥ���twoPr�VMv�JatZs1�YLfeE`|g%K.�J,a�I�e5�X���L-�/�y;�!off�[K�h�s�Ouv.x +��H�,�UVZ@u-�αa�h?V4�1l
-#�02�y��J +��SSCT�r^Qf2d13����Ԋ2�,S�R
2R
�
JuM1.36�007�d12&5�ly��2;"gF+ ҍ�	�Ld1����J2Ni�	cos�	J�	�	)[r~�ǻ�_�nZ�(3#���A,K-�n�	s)��N
�+�j
"Mu-Nyxf��S�GP"�B�U�yms Upg 443-�<�}3m2��s[9]RA[]	J(FP,��|� 5,Zs,yb�
v�* 1�T R�T r-1� P#!�7PixelSiz�;T�+0/+�KB[WD$Q3N���	or(i�iR;< 9++3Q#"Ͽ��vK�Y�\i]�
(l�d���]�	�#j
K��
}C4Ultas1+V N����1],�;2�3�4]+�2�5�
6�7�8]�U�Z�-�	0�^�7�N	��	Jv4��F�u�,&�
in�
��#tL��^ResultF��Uݞ* 25���"�:� kZ��;1Qj
2�) zn
3�) wn
4v
[�)5�T ���2�)6�) �)7�) �)8�� �7z�ο�k�,y�v6
Ƅ*,*~�C�r
�j)2   �5;
}
     f��\R
Wa\�   �    ��   �#version 150

in vec2 posit`; �Fout�frag_�void main()
{
	� = � (+
(1.0, )) / 2.0;�gl_P��4�,  � 0N0);
}
     f��\R 
a�  3  3   �#version 150

uniform sampler  �2D color_tex;� posit�! depth�floa  �t render_distance"vec3 camera�i  �nt blur_mod�bool enable_antiali ��asing�
in�2 frag_V+�out�4 $_J9�'Ř��V%(Juv)p�minZ2ad�
(�,�:�_
B�( �fxaa( @І@oid main()
{
	if (�? == 0d	�����	�0 =�	}else �1��;'�^6�KJ�
< 0.35�_pt��z �:
=�,�Q0.25)�,�� �0.5V
}í^L�	ture2D(�Rj�,�.r
B.�1re�n8; Vlength"f��xyz -ҫ)|� /��
+ �.
2res�RSize(��,�J�	const�GA����2.399; �mat-otl�s(GA), �N-��J�X� �acc��(� �'pixel�2(.002 *�,.yJ@s.��t?��Yangle�
0,�	��':0��D�c� (�
j
	< 1��++)�{  N�+�!ad��� *=FB
�R�F��� +7* ��z�(�-��4
;�4%^�>=�w	N�	V+�w�v���	++�H�}������(/�R,�+�sO y 4�y ��?� �}��40jwˏG, ;��aw �! 0�(�%��: �,J@)�w�Vt/**
B�"c FXAA iF�mentaJbas� �ed $the�)0geeks3d.com wi�t
�if�  �icth3�Lod stuff was�moveHiU i �t's[	support`by WebGL.
--
From � �:
https://g�ub /mitsuhiko/webg  �l-meIraft
Copyright (c) 2011�AƄrA Ronacher�Some 

�%sera\Re�IribuA`��J4and u�n sour��binary 

C-!�DA	rP`��e pe�t�8provid$�Jfollow)��FsF!et:	�<�Ώ* .&s ofV$�gmu��'Jab�l�BV�notice,�i8���s l�!�nd2%�claim
M�� �bD�"�du}�#!Z%q �^% a�n�<docuޯ�/EohrDer�.s_�V� &4�9Tdn�%
[�n�	(��orsYy0 be��o]0dh�rV�mote C�	�&i�fd�`���=softwƈ�� spec��i�rƏnN�ss*THIS SO�  �FTWARE 0PROVIDED BY THE COPYRIG @ �HT HOLDERS ANDXNTRIBUTORS
"AS� ��"�ANY EXPRESS OR IMPLI9}RANTIES   �, INCLUDING, 	 NOT
LIMIT�TO,�> B� OF MERCH<ABILITYJFITNFFOR
A P  �ARTICULAR PURPOSE �6DISCLAIMED. `�� EVENT SHALLn:
OWNER�/�9 BE LIABl��LE�
:DIRECTF4�C��L,}PECI(AE=ARY,R0�`�SEQU�t DAMAGy(�eCUREM�--SUBSTITU� �TE GOODJ[SERVICES; LO�_F USE%DATA�����0BUSIJNINTERRUPTION)�Wi�A��sDZ� ON�;�EORY�B�`, WHE`RFU�KA�AS�CT�	�MP��: NEGLIGENCE�O�WISE)�ISFIJ�U�=Fj/���a��,
t IF ADVI�.�	SIҋ�MCH]�*/�#if@1�	4f�_REDUCE_MIN��#hinevh(1.0/ 128Jr��.�#�if�M UL�M ULRQ�L SPAN_MAX�J �J���/o�A��ptim%%d +<umobil�w��ep!"�#z	ads�8u�Ӏ�Btt�9eckK�;;�	3�Coorduol,;�3X	v_rgbNW��E�,�E�* S�
S�* M) {3�	4 +5FmumpNin�FeVP+�	Nc����-�	:yC�3 �0;�
�=�C7+.�E�/ E�/ S�^ S�^ S�^ S�4�	C#��2 r!�Mv:M �
J6luma3".299�..587�114hF�Mdo\U��t(���& E�	E�& S"S�L S"S�L �9�	M, �& � i�,���3I.�Y�,	&%)�P ax�x,�.R�P ��di�(.F-(R50�!0���F�y� �
���f8�'�	�86 �� *��n ��%cQyc��� rcp8��DirNp��Jnabs(�H�y))M�/�DR7S�,[�),62F@�-2����-�9 �*�/m*;�*:V�#�^��3��N=NH3-�)H+�y 2�O khV}ݐB��/*�/+2�) -��� V-��B;/B[T_ʺBy?#5) ||N�B ����>��))&+IR�A,;s���3 B�3 #�+;y;���3�c��3�x3=ka0.�{o�ny^E�y#�+��/��*K�[��R.-J���+��: +�: +�: �OR6�)   �;
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