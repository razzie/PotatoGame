 
a��  
  �
   �#version 150

uniform sampler  ��2D color_tex;�bool blurP
in ve `��c2 frag_positE�out�4 $_J�L3 dof� ��(��,�uvRres, float rad)��fxaa�9 � � �Coordolu#,
 b �v_rgbNW,�E, �* S�
  �S�* M)9oid main()
{
	2% =�.tureSi�B��ze(�Y, 0F	if (FY)0�	�Q�C(Q�j`,f@ 0.@aI�5), 1.N}elseVR^x2(� /".�%Vy^0
=����y�An-
o��  *�,�o			.-� ���+��: +�: +�: �N
/  �/ 	si
yfied ��of Dave Hoskins
ɧ� �� ��const�GA2.399; �mat�otl�ys(GA��� �s�	J-��f�%accr3(�w�pixel�x.002�g.y�y������YangleZ�,V�,d1.�N� (int jL0;< 8����++)�{ b��+ad��N*=�<;�e	��(�Xuv=�2�R�* (-M)4JN�A��.xyz�renJH/�1�~**
 ��Basic FXAA F�ementa
�basA$theMde  �geeks3d.com withF
modificth� !�02DLod stuff was�moveHince it's ��support`by WebGL.
--
From:
  �https://g�ub /mitsuhiko/webgl-m  �eIraft
Copyright (c) 2011�Arm� ��Ronacher�Some 

�%sera\Redistrib�@`��and us�n sour��binary F�
Ca��Di	rP` �e pe�t�8provid$�Jfollowing�ndJ�sF!H�y�et:��* .&s�R$�gmu��Jab�l�B�notice,��~�is li�!�nd2%�claim
M�� �bD�"�du}�#!Z%q ��U��^% <docuޯ�/EohrQerials_�V� &4�9Tdna,���me
[�n�	orsYy0 be��o endh�rV�mote��`� C�	d)�fd�=softwƈ�� spec��i�rƏnN�ss� �*THIS SOFTWARE 0PROVIDED BY THE  @� COPYRIGHT HOLDERS ANDXNTRIBUTO� �RS
"AS�"�ANY EXPRESS OR IMPLI9  �}RANTIES, INCLUDING, 	 NOT
LIM� �IT�TO,�> OF MERCH<ABILITYJFITNF   �FOR
A PARTICULAR PURPOSE �6DISC� �LAIMED.� EVENT SHALLn:
OWNER�/�9 l� BE LIABLE�
:DIRECTF4�C��L�SPECI(�0��AE=ARY,RSEQU�t DAMAGy(�eCUREM�-- � �SUBSTITUTE GOODJ[SERVICES; LO�_F �U�&
DATA���0BUSIJNINTERRUPTION)mڙWi�A��sD ON�;�EORY�B�`, WHE`RFU�KA�A�P�S�CT�	�M: NEGLIGENCE�O�WISE)�IS�/��FIJ�U�=Fja��,
t IF ADVI�.�	SIҋ�MCH �]�*/�#ifndef�_REDUCE_MIN��#hinev'9�h()/ 128A(�if�M UL�M ULR_�L SPAN_MAX�J 4��J���	optimm-;�	�mobil�w��ep�� �#z	a� ɢds cau�3ttleneck7d  {3�	4 +xFmumpNi�el�n�FeVP+�	Nc[�:yC'
3 �0;v	2D(�C7)#Q	�E�/ E�/ S�^ S�^ ���S�^ S�4�	C#��2 Mv:M �
J6luma3J.29987�11���4�F�Mdot(���& E�	E�& S"S�L S"S�L �9�	M, �& � �.���1i1�,���3I,	&%)�P ax�x,�.R�P ��di�(.F����-(Rm0�Y0F�y� �
���f8�'�	�86 �� *��n ��>p8�5�%cQyc��� rcpDirNp��Jnabs(�H�y))M�/�DR7S�rm��,[�),62F@�-2-�9 �*�/m*;�*:V�0��7^��3��N=NH3����-DE +�y 2�O khB��/*�/+2�) -��� V:��B;/B[T�ʺBC�ހ�?#5) ||N�B >��))&S��A,;s���3 B�3 #�color;   �
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