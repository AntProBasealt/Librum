#ifndef _psheader_cpp_
#define _psheader_cpp_

/*
 *   DO NOT EDIT THIS FILE!
 *   It was created by squeeze.c from another file (see the Makefile).
 */

#ifndef _Xconst
    #if __STDC__
        #define _Xconst const
    #else
        #define _Xconst
    #endif
#endif

_Xconst char psheader[] = "\
/TeXDict 300 dict def TeXDict begin/N{def}def/B{bind def}N/S{exch}N/X{S\n\
N}B/A{dup}B/TR{translate}N/isls false N/vsize 11 72 mul N/hsize 8.5 72\n\
mul N/landplus90{false}def/@rigin{isls{[0 landplus90{1 -1}{-1 1}ifelse 0\n\
0 0]concat}if 72 Resolution div 72 VResolution div neg scale isls{\n\
landplus90{VResolution 72 div vsize mul 0 exch}{Resolution -72 div hsize\n\
mul 0}ifelse TR}if Resolution VResolution vsize -72 div 1 add mul TR[\n\
matrix currentmatrix{A A round sub abs 0.00001 lt{round}if}forall round\n\
exch round exch]setmatrix}N/@landscape{/isls true N}B/@manualfeed{\n\
statusdict/manualfeed true put}B/@copies{/#copies X}B/FMat[1 0 0 -1 0 0]\n\
N/FBB[0 0 0 0]N/nn 0 N/IEn 0 N/ctr 0 N/df-tail{/nn 8 dict N nn begin\n\
/FontType 3 N/FontMatrix fntrx N/FontBBox FBB N string/base X array\n\
/BitMaps X/BuildChar{CharBuilder}N/Encoding IEn N end A{/foo setfont}2\n\
array copy cvx N load 0 nn put/ctr 0 N[}B/sf 0 N/df{/sf 1 N/fntrx FMat N\n\
df-tail}B/dfs{div/sf X/fntrx[sf 0 0 sf neg 0 0]N df-tail}B/E{pop nn A\n\
definefont setfont}B/Cw{Cd A length 5 sub get}B/Ch{Cd A length 4 sub get\n\
}B/Cx{128 Cd A length 3 sub get sub}B/Cy{Cd A length 2 sub get 127 sub}\n\
B/Cdx{Cd A length 1 sub get}B/Ci{Cd A type/stringtype ne{ctr get/ctr ctr\n\
1 add N}if}B/id 0 N/rw 0 N/rc 0 N/gp 0 N/cp 0 N/G 0 N/CharBuilder{save 3\n\
1 roll S A/base get 2 index get S/BitMaps get S get/Cd X pop/ctr 0 N Cdx\n\
0 Cx Cy Ch sub Cx Cw add Cy setcachedevice Cw Ch true[1 0 0 -1 -.1 Cx\n\
sub Cy .1 sub]/id Ci N/rw Cw 7 add 8 idiv string N/rc 0 N/gp 0 N/cp 0 N{\n\
rc 0 ne{rc 1 sub/rc X rw}{G}ifelse}imagemask restore}B/G{{id gp get/gp\n\
gp 1 add N A 18 mod S 18 idiv pl S get exec}loop}B/adv{cp add/cp X}B\n\
/chg{rw cp id gp 4 index getinterval putinterval A gp add/gp X adv}B/nd{\n\
/cp 0 N rw exit}B/lsh{rw cp 2 copy get A 0 eq{pop 1}{A 255 eq{pop 254}{\n\
A A add 255 and S 1 and or}ifelse}ifelse put 1 adv}B/rsh{rw cp 2 copy\n\
get A 0 eq{pop 128}{A 255 eq{pop 127}{A 2 idiv S 128 and or}ifelse}\n\
ifelse put 1 adv}B/clr{rw cp 2 index string putinterval adv}B/set{rw cp\n\
fillstr 0 4 index getinterval putinterval adv}B/fillstr 18 string 0 1 17\n\
{2 copy 255 put pop}for N/pl[{adv 1 chg}{adv 1 chg nd}{1 add chg}{1 add\n\
chg nd}{adv lsh}{adv lsh nd}{adv rsh}{adv rsh nd}{1 add adv}{/rc X nd}{\n\
1 add set}{1 add clr}{adv 2 chg}{adv 2 chg nd}{pop nd}]A{bind pop}\n\
forall N/D{/cc X A type/stringtype ne{]}if nn/base get cc ctr put nn\n\
/BitMaps get S ctr S sf 1 ne{A A length 1 sub A 2 index S get sf div put\n\
}if put/ctr ctr 1 add N}B/I{cc 1 add D}B/bop{userdict/bop-hook known{\n\
bop-hook}if/SI save N @rigin 0 0 moveto/V matrix currentmatrix A 1 get A\n\
mul exch 0 get A mul add .99 lt{/QV}{/RV}ifelse load def pop pop}N/eop{\n\
SI restore userdict/eop-hook known{eop-hook}if showpage}N/@start{\n\
userdict/start-hook known{start-hook}if pop/VResolution X/Resolution X\n\
1000 div/DVImag X/IEn 256 array N 2 string 0 1 255{IEn S A 360 add 36 4\n\
index cvrs cvn put}for pop 65781.76 div/vsize X 65781.76 div/hsize X}N\n\
/p{show}N/RMat[1 0 0 -1 0 0]N/BDot 260 string N/Rx 0 N/Ry 0 N/V{}B/RV/v{\n\
/Ry X/Rx X V}B statusdict begin/product where{pop false[(Display)(NeXT)\n\
(LaserWriter 16/600)]{A length product length le{A length product exch 0\n\
exch getinterval eq{pop true exit}if}{pop}ifelse}forall}{false}ifelse\n\
end{{gsave TR -.1 .1 TR 1 1 scale Rx Ry false RMat{BDot}imagemask\n\
grestore}}{{gsave TR -.1 .1 TR Rx Ry scale 1 1 false RMat{BDot}\n\
imagemask grestore}}ifelse B/QV{gsave newpath transform round exch round\n\
exch itransform moveto Rx 0 rlineto 0 Ry neg rlineto Rx neg 0 rlineto\n\
fill grestore}B/a{moveto}B/delta 0 N/tail{A/delta X 0 rmoveto}B/M{S p\n\
delta add tail}B/b{S p tail}B/c{-4 M}B/d{-3 M}B/e{-2 M}B/f{-1 M}B/g{0 M}\n\
B/h{1 M}B/i{2 M}B/j{3 M}B/k{4 M}B/w{0 rmoveto}B/l{p -4 w}B/m{p -3 w}B/n{\n\
p -2 w}B/o{p -1 w}B/q{p 1 w}B/r{p 2 w}B/s{p 3 w}B/t{p 4 w}B/x{0 S\n\
rmoveto}B/y{3 2 roll p a}B/bos{/SS save N}B/eos{SS restore}B end TeXDict\n\
begin/SDict 200 dict N SDict begin/@SpecialDefaults{/hs 612 N /vs 792\n\
N/ho 0 N/vo 0 N/hsc 1 N/vsc 1 N/ang 0 N/CLIP 0 N/rwiSeen false N\n\
/rhiSeen false N/letter{}N/note{}N/a4{}N/legal{}N}B/@scaleunit 100 N\n\
/@hscale{@scaleunit div/hsc X}B/@vscale{@scaleunit div/vsc X}B/@hsize{\n\
/hs X/CLIP 1 N}B/@vsize{/vs X/CLIP 1 N}B/@clip{/CLIP 2 N}B/@hoffset{/ho\n\
X}B/@voffset{/vo X}B/@angle{/ang X}B/@rwi{10 div/rwi X/rwiSeen true N}B\n\
/@rhi{10 div/rhi X/rhiSeen true N}B/@llx{/llx X}B/@lly{/lly X}B/@urx{\n\
/urx X}B/@ury{/ury X}B/magscale true def end/@MacSetUp{userdict/md known\n\
{userdict/md get type/dicttype eq{userdict begin md length 10 add md\n\
maxlength ge{/md md dup length 20 add dict copy def}if end md begin\n\
/letter{}N/note{}N/legal{}N/od{txpose 1 0 mtx defaultmatrix dtransform S\n\
atan/pa X newpath clippath mark{transform{itransform moveto}}{transform{\n\
itransform lineto}}{6 -2 roll transform 6 -2 roll transform 6 -2 roll\n\
transform{itransform 6 2 roll itransform 6 2 roll itransform 6 2 roll\n\
curveto}}{{closepath}}pathforall newpath counttomark array astore/gc xdf\n\
pop ct 39 0 put 10 fz 0 fs 2 F/|______Courier fnt invertflag{PaintBlack}\n\
if}N/txpose{pxs pys scale ppr aload pop por{noflips{pop S neg S TR pop 1\n\
-1 scale}if xflip yflip and{pop S neg S TR 180 rotate 1 -1 scale ppr 3\n\
get ppr 1 get neg sub neg ppr 2 get ppr 0 get neg sub neg TR}if xflip\n\
yflip not and{pop S neg S TR pop 180 rotate ppr 3 get ppr 1 get neg sub\n\
neg 0 TR}if yflip xflip not and{ppr 1 get neg ppr 0 get neg TR}if}{\n\
noflips{TR pop pop 270 rotate 1 -1 scale}if xflip yflip and{TR pop pop\n\
90 rotate 1 -1 scale ppr 3 get ppr 1 get neg sub neg ppr 2 get ppr 0 get\n\
neg sub neg TR}if xflip yflip not and{TR pop pop 90 rotate ppr 3 get ppr\n\
1 get neg sub neg 0 TR}if yflip xflip not and{TR pop pop 270 rotate ppr\n\
2 get ppr 0 get neg sub neg 0 S TR}if}ifelse scaleby96{ppr aload pop 4\n\
-1 roll add 2 div 3 1 roll add 2 div 2 copy TR .96 dup scale neg S neg S\n\
TR}if}N/cp{pop pop showpage pm restore}N end}if}if}N/normalscale{\n\
Resolution 72 div VResolution 72 div neg scale magscale{DVImag dup scale\n\
}if 0 setgray}N/psfts{S 65781.76 div N}N/startTexFig{/psf$SavedState\n\
save N userdict maxlength dict begin/magscale true def normalscale\n\
currentpoint TR/psf$ury psfts/psf$urx psfts/psf$lly psfts/psf$llx psfts\n\
/psf$y psfts/psf$x psfts currentpoint/psf$cy X/psf$cx X/psf$sx psf$x\n\
psf$urx psf$llx sub div N/psf$sy psf$y psf$ury psf$lly sub div N psf$sx\n\
psf$sy scale psf$cx psf$sx div psf$llx sub psf$cy psf$sy div psf$ury sub\n\
TR/showpage{}N/erasepage{}N/copypage{}N/p 3 def @MacSetUp}N/doclip{\n\
psf$llx psf$lly psf$urx psf$ury currentpoint 6 2 roll newpath 4 copy 4 2\n\
roll moveto 6 -1 roll S lineto S lineto S lineto closepath clip newpath\n\
moveto}N/endTexFig{end psf$SavedState restore}N/@beginspecial{SDict\n\
begin/SpecialSave save N gsave normalscale currentpoint TR\n\
@SpecialDefaults count/ocount X/dcount countdictstack N}N/@setspecial{\n\
CLIP 1 eq{newpath 0 0 moveto hs 0 rlineto 0 vs rlineto hs neg 0 rlineto\n\
closepath clip}if ho vo TR hsc vsc scale ang rotate rwiSeen{rwi urx llx\n\
sub div rhiSeen{rhi ury lly sub div}{dup}ifelse scale llx neg lly neg TR\n\
}{rhiSeen{rhi ury lly sub div dup scale llx neg lly neg TR}if}ifelse\n\
CLIP 2 eq{newpath llx lly moveto urx lly lineto urx ury lineto llx ury\n\
lineto closepath clip}if/showpage{}N/erasepage{}N/copypage{}N newpath}N\n\
/@endspecial{count ocount sub{pop}repeat countdictstack dcount sub{end}\n\
repeat grestore SpecialSave restore end}N/@defspecial{SDict begin}N\n\
/@fedspecial{end}B/li{lineto}B/rl{rlineto}B/rc{rcurveto}B/np{/SaveX\n\
currentpoint/SaveY X N 1 setlinecap newpath}N/st{stroke SaveX SaveY\n\
moveto}N/fil{fill SaveX SaveY moveto}N/ellipse{/endangle X/startangle X\n\
/yrad X/xrad X/savematrix matrix currentmatrix N TR xrad yrad scale 0 0\n\
1 startangle endangle arc savematrix setmatrix}N end\n";

// int	psheaderlen	= 7620;
#endif
