xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 137;
 0.00001;18.30095;-0.02282;,
 4.07858;16.96641;-1.90315;,
 0.00001;17.22381;-3.85725;,
 0.00001;18.30095;-0.02282;,
 4.07858;16.97293;2.00152;,
 0.00001;18.30095;-0.02282;,
 0.00001;17.04127;4.93952;,
 0.00001;18.30095;-0.02282;,
 -4.07856;16.97293;2.00152;,
 0.00001;18.30095;-0.02282;,
 -4.07856;16.96641;-1.90315;,
 0.00001;18.30095;-0.02282;,
 0.00001;17.22381;-3.85725;,
 6.31078;14.19077;-3.98742;,
 0.00001;14.12857;-7.37861;,
 6.31078;14.19077;4.16972;,
 0.00001;14.12857;7.79548;,
 -6.31100;14.19034;4.17000;,
 -6.31100;14.19034;-3.98700;,
 0.00001;14.12857;-7.37861;,
 7.47898;9.41906;-4.73235;,
 0.00001;9.41906;-9.11492;,
 7.28282;9.41906;4.68671;,
 0.00001;9.41906;8.65631;,
 -7.32637;9.41906;4.68671;,
 -7.47869;9.41906;-4.73235;,
 0.00001;9.41906;-9.11492;,
 6.31078;4.77168;-3.98742;,
 0.00001;4.70953;-7.37861;,
 6.31078;4.77168;4.16972;,
 0.00001;4.70953;7.68283;,
 -6.31100;4.77134;4.17000;,
 -6.31100;4.77134;-3.98700;,
 0.00001;4.70953;-7.37861;,
 4.07858;1.26192;-2.37758;,
 0.00001;1.26192;-4.73235;,
 4.07858;1.26192;2.33195;,
 0.00001;1.26192;4.68671;,
 -4.07856;1.26192;2.33195;,
 -4.07856;1.26192;-2.37758;,
 0.00001;1.26192;-4.73235;,
 0.00001;0.00000;-0.02282;,
 0.00001;0.00000;-0.02282;,
 0.00001;0.00000;-0.02282;,
 0.00001;0.00000;-0.02282;,
 0.00001;0.00000;-0.02282;,
 0.00001;0.00000;-0.02282;,
 -0.00073;6.16376;-7.23059;,
 -0.00073;5.78518;-8.30395;,
 -5.82382;9.26895;-5.84303;,
 -5.11349;9.02292;-5.83606;,
 -0.00073;4.70625;-7.94145;,
 -6.47538;8.55441;-5.30283;,
 -0.00073;5.08485;-6.86809;,
 -5.76505;8.30842;-5.29585;,
 -0.00073;6.16376;-7.23059;,
 -5.11349;9.02292;-5.83606;,
 5.11851;9.02292;-5.83606;,
 5.72435;9.19587;-6.01282;,
 -0.00073;5.78518;-8.30395;,
 -0.00073;6.16376;-7.23059;,
 6.36945;8.48134;-5.47262;,
 -0.00073;4.70625;-7.94145;,
 5.76360;8.30842;-5.29585;,
 -0.00073;5.08485;-6.86809;,
 5.11851;9.02292;-5.83606;,
 -0.00073;6.16376;-7.23059;,
 -2.56792;13.62175;-7.45175;,
 -2.53251;14.90071;-7.35446;,
 -1.13143;14.28312;-7.86441;,
 -2.01666;13.37877;-7.65240;,
 -0.55108;12.79210;-8.07565;,
 -1.78832;12.79210;-7.73551;,
 -1.13143;11.30109;-7.86441;,
 -2.01666;12.20546;-7.65240;,
 -2.53251;10.68351;-7.35446;,
 -2.56792;11.96246;-7.45175;,
 -3.93360;11.30109;-6.84451;,
 -3.11919;12.20546;-7.25111;,
 -4.51395;12.79210;-6.63328;,
 -3.34753;12.79210;-7.16800;,
 -3.93360;14.28312;-6.84451;,
 -3.11919;13.37877;-7.25111;,
 -2.53251;14.90071;-7.35446;,
 -2.56792;13.62175;-7.45175;,
 -1.61024;12.79210;-4.82055;,
 -1.61024;12.79210;-4.82055;,
 -1.61024;12.79210;-4.82055;,
 -1.61024;12.79210;-4.82055;,
 -1.61024;12.79210;-4.82055;,
 -1.61024;12.79210;-4.82055;,
 -1.61024;12.79210;-4.82055;,
 -1.61024;12.79210;-4.82055;,
 -2.56387;12.79210;-7.44063;,
 -2.56792;13.62175;-7.45175;,
 -2.01666;13.37877;-7.65240;,
 -1.78832;12.79210;-7.73551;,
 -2.01666;12.20546;-7.65240;,
 -2.56792;11.96246;-7.45175;,
 -3.11919;12.20546;-7.25111;,
 -3.34753;12.79210;-7.16800;,
 -3.11919;13.37877;-7.25111;,
 2.56792;13.62175;-7.45175;,
 2.53251;14.90071;-7.35446;,
 3.93360;14.28312;-6.84451;,
 3.11919;13.37877;-7.25111;,
 4.51395;12.79210;-6.63328;,
 3.34753;12.79210;-7.16800;,
 3.93360;11.30109;-6.84451;,
 3.11919;12.20546;-7.25111;,
 2.53251;10.68351;-7.35446;,
 2.56792;11.96246;-7.45175;,
 1.13142;11.30109;-7.86441;,
 2.01666;12.20546;-7.65240;,
 0.55108;12.79210;-8.07565;,
 1.78832;12.79210;-7.73551;,
 1.13142;14.28312;-7.86441;,
 2.01666;13.37877;-7.65240;,
 2.53251;14.90071;-7.35446;,
 2.56792;13.62175;-7.45175;,
 1.61024;12.79210;-4.82055;,
 1.61024;12.79210;-4.82055;,
 1.61024;12.79210;-4.82055;,
 1.61024;12.79210;-4.82055;,
 1.61024;12.79210;-4.82055;,
 1.61024;12.79210;-4.82055;,
 1.61024;12.79210;-4.82055;,
 1.61024;12.79210;-4.82055;,
 2.56387;12.79210;-7.44063;,
 2.56792;13.62175;-7.45175;,
 3.11919;13.37877;-7.25111;,
 3.34753;12.79210;-7.16800;,
 3.11919;12.20546;-7.25111;,
 2.56792;11.96246;-7.45175;,
 2.01666;12.20546;-7.65240;,
 1.78832;12.79210;-7.73551;,
 2.01666;13.37877;-7.65240;;
 
 92;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 4;2,1,13,14;,
 4;1,4,15,13;,
 4;4,6,16,15;,
 4;6,8,17,16;,
 4;8,10,18,17;,
 4;10,12,19,18;,
 4;14,13,20,21;,
 4;13,15,22,20;,
 4;15,16,23,22;,
 4;16,17,24,23;,
 4;17,18,25,24;,
 4;18,19,26,25;,
 4;21,20,27,28;,
 4;20,22,29,27;,
 4;22,23,30,29;,
 4;23,24,31,30;,
 4;24,25,32,31;,
 4;25,26,33,32;,
 4;28,27,34,35;,
 4;27,29,36,34;,
 4;29,30,37,36;,
 4;30,31,38,37;,
 4;31,32,39,38;,
 4;32,33,40,39;,
 3;35,34,41;,
 3;34,36,42;,
 3;36,37,43;,
 3;37,38,44;,
 3;38,39,45;,
 3;39,40,46;,
 4;47,48,49,50;,
 4;48,51,52,49;,
 4;51,53,54,52;,
 4;53,55,56,54;,
 4;57,58,59,60;,
 4;58,61,62,59;,
 4;61,63,64,62;,
 4;63,65,66,64;,
 4;67,68,69,70;,
 4;70,69,71,72;,
 4;72,71,73,74;,
 4;74,73,75,76;,
 4;76,75,77,78;,
 4;78,77,79,80;,
 4;80,79,81,82;,
 4;82,81,83,84;,
 3;68,85,69;,
 3;69,86,71;,
 3;71,87,73;,
 3;73,88,75;,
 3;75,89,77;,
 3;77,90,79;,
 3;79,91,81;,
 3;81,92,83;,
 3;93,94,95;,
 3;93,95,96;,
 3;93,96,97;,
 3;93,97,98;,
 3;93,98,99;,
 3;93,99,100;,
 3;93,100,101;,
 3;93,101,94;,
 4;102,103,104,105;,
 4;105,104,106,107;,
 4;107,106,108,109;,
 4;109,108,110,111;,
 4;111,110,112,113;,
 4;113,112,114,115;,
 4;115,114,116,117;,
 4;117,116,118,119;,
 3;103,120,104;,
 3;104,121,106;,
 3;106,122,108;,
 3;108,123,110;,
 3;110,124,112;,
 3;112,125,114;,
 3;114,126,116;,
 3;116,127,118;,
 3;128,129,130;,
 3;128,130,131;,
 3;128,131,132;,
 3;128,132,133;,
 3;128,133,134;,
 3;128,134,135;,
 3;128,135,136;,
 3;128,136,129;;
 
 MeshMaterialList {
  8;
  92;
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.768800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.021600;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.445600;0.000000;0.605600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.160000;0.160000;0.160000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.630400;0.542400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.181600;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  98;
  0.000000;0.999959;-0.009023;,
  -0.000014;0.883858;-0.467756;,
  0.432067;0.870182;-0.236859;,
  0.447454;0.865336;0.225785;,
  -0.000001;0.890202;0.455566;,
  -0.447595;0.865258;0.225803;,
  -0.432222;0.870098;-0.236885;,
  -0.000022;0.563355;-0.826215;,
  0.738519;0.529875;-0.416920;,
  0.757884;0.494971;0.424989;,
  0.000366;0.511857;0.859071;,
  -0.757194;0.496581;0.424340;,
  -0.737794;0.530624;-0.417251;,
  -0.000012;-0.001983;-0.999998;,
  0.867766;-0.002658;-0.496967;,
  0.857924;-0.005432;0.513747;,
  0.000733;-0.007492;0.999972;,
  -0.858078;-0.005469;0.513490;,
  -0.867034;-0.002673;-0.498241;,
  -0.000005;-0.479179;-0.877717;,
  0.770240;-0.460038;-0.441696;,
  0.773662;-0.446861;0.449180;,
  0.000380;-0.455776;0.890094;,
  -0.772916;-0.448753;0.448578;,
  -0.769418;-0.461077;-0.442045;,
  -0.000000;-0.843300;-0.537443;,
  0.470163;-0.840047;-0.270679;,
  0.465405;-0.845478;0.261850;,
  0.000014;-0.855435;0.517911;,
  -0.465370;-0.845500;0.261841;,
  -0.470144;-0.840059;-0.270675;,
  -0.000000;-1.000000;0.000000;,
  -0.016241;0.917722;-0.396891;,
  -0.006607;-0.279747;-0.960051;,
  0.016738;-0.916494;0.399699;,
  0.347550;0.850212;-0.395409;,
  -0.490941;-0.240352;-0.837382;,
  -0.347032;-0.848601;0.399305;,
  -0.377808;0.859593;-0.344038;,
  0.479387;-0.248875;-0.841575;,
  0.378216;-0.858883;0.345360;,
  -0.341832;0.033238;-0.939173;,
  -0.319752;0.023504;-0.947210;,
  -0.310602;0.000000;-0.950540;,
  -0.319752;-0.023505;-0.947210;,
  -0.341831;-0.033239;-0.939173;,
  -0.363911;-0.023501;-0.931137;,
  -0.373061;-0.000000;-0.927807;,
  -0.363911;0.023501;-0.931137;,
  -0.340904;0.080690;-0.936629;,
  -0.287292;0.057059;-0.956142;,
  -0.265081;0.000000;-0.964226;,
  -0.287291;-0.057061;-0.956142;,
  -0.340903;-0.080692;-0.936629;,
  -0.394516;-0.057055;-0.917116;,
  -0.416727;-0.000000;-0.909032;,
  -0.394516;0.057055;-0.917116;,
  0.874508;0.284766;0.392611;,
  -0.342022;0.000000;-0.939692;,
  0.341831;0.033238;-0.939173;,
  0.363911;0.023501;-0.931137;,
  0.373061;-0.000000;-0.927807;,
  0.363911;-0.023501;-0.931137;,
  0.341831;-0.033240;-0.939174;,
  0.319752;-0.023505;-0.947210;,
  0.310603;-0.000000;-0.950540;,
  0.319752;0.023504;-0.947210;,
  0.340904;0.080691;-0.936629;,
  0.394516;0.057055;-0.917116;,
  0.416727;-0.000000;-0.909032;,
  0.394516;-0.057055;-0.917116;,
  0.340903;-0.080693;-0.936629;,
  0.287290;-0.057062;-0.956142;,
  0.265081;-0.000000;-0.964226;,
  0.287292;0.057059;-0.956142;,
  0.417545;0.284766;0.862882;,
  0.342022;0.000000;-0.939692;,
  -0.000144;0.319158;0.947701;,
  0.400173;0.291880;0.868716;,
  -0.400437;0.293061;0.868197;,
  0.210683;0.787749;0.578847;,
  0.734114;0.557022;0.388333;,
  0.950926;-0.000001;0.309417;,
  0.734113;-0.557024;0.388332;,
  -0.039112;-0.687488;0.725142;,
  0.210682;-0.787751;0.578845;,
  -0.312747;-0.557024;0.769359;,
  -0.529560;-0.000001;0.848272;,
  -0.312748;0.557022;0.769360;,
  -0.210681;0.787749;0.578848;,
  0.312748;0.557022;0.769360;,
  0.529560;-0.000001;0.848272;,
  0.312747;-0.557024;0.769359;,
  -0.496074;-0.687486;0.530351;,
  -0.210681;-0.787751;0.578845;,
  -0.734114;-0.557022;0.388334;,
  -0.950926;-0.000001;0.309417;,
  -0.734115;0.557020;0.388334;;
  92;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,1,6;,
  4;1,2,8,7;,
  4;2,3,9,8;,
  4;3,4,10,9;,
  4;4,5,11,10;,
  4;5,6,12,11;,
  4;6,1,7,12;,
  4;7,8,14,13;,
  4;8,9,15,14;,
  4;9,10,16,15;,
  4;10,11,17,16;,
  4;11,12,18,17;,
  4;12,7,13,18;,
  4;13,14,20,19;,
  4;14,15,21,20;,
  4;15,16,22,21;,
  4;16,17,23,22;,
  4;17,18,24,23;,
  4;18,13,19,24;,
  4;19,20,26,25;,
  4;20,21,27,26;,
  4;21,22,28,27;,
  4;22,23,29,28;,
  4;23,24,30,29;,
  4;24,19,25,30;,
  3;25,26,31;,
  3;26,27,31;,
  3;27,28,31;,
  3;28,29,31;,
  3;29,30,31;,
  3;30,25,31;,
  4;32,32,35,35;,
  4;33,33,36,36;,
  4;34,34,37,37;,
  4;77,77,78,78;,
  4;38,38,32,32;,
  4;39,39,33,33;,
  4;40,40,34,34;,
  4;79,79,77,77;,
  4;41,49,50,42;,
  4;42,50,51,43;,
  4;43,51,52,44;,
  4;44,52,53,45;,
  4;45,53,54,46;,
  4;46,54,55,47;,
  4;47,55,56,48;,
  4;48,56,49,41;,
  3;80,57,81;,
  3;81,57,82;,
  3;82,57,83;,
  3;83,84,85;,
  3;85,84,86;,
  3;86,84,87;,
  3;87,88,88;,
  3;88,88,80;,
  3;58,41,42;,
  3;58,42,43;,
  3;58,43,44;,
  3;58,44,45;,
  3;58,45,46;,
  3;58,46,47;,
  3;58,47,48;,
  3;58,48,41;,
  4;59,67,68,60;,
  4;60,68,69,61;,
  4;61,69,70,62;,
  4;62,70,71,63;,
  4;63,71,72,64;,
  4;64,72,73,65;,
  4;65,73,74,66;,
  4;66,74,67,59;,
  3;89,75,90;,
  3;90,75,91;,
  3;91,75,92;,
  3;92,93,94;,
  3;94,93,95;,
  3;95,93,96;,
  3;96,97,97;,
  3;97,97,89;,
  3;76,59,60;,
  3;76,60,61;,
  3;76,61,62;,
  3;76,62,63;,
  3;76,63,64;,
  3;76,64,65;,
  3;76,65,66;,
  3;76,66,59;;
 }
 MeshTextureCoords {
  137;
  0.083330;0.000000;,
  0.166670;0.166670;,
  0.000000;0.166670;,
  0.250000;0.000000;,
  0.333330;0.166670;,
  0.416670;0.000000;,
  0.500000;0.166670;,
  0.583330;0.000000;,
  0.666670;0.166670;,
  0.750000;0.000000;,
  0.833330;0.166670;,
  0.916670;0.000000;,
  1.000000;0.166670;,
  0.166670;0.333330;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.500000;0.333330;,
  0.666670;0.333330;,
  0.833330;0.333330;,
  1.000000;0.333330;,
  0.166670;0.500000;,
  0.000000;0.500000;,
  0.333330;0.500000;,
  0.500000;0.500000;,
  0.666670;0.500000;,
  0.833330;0.500000;,
  1.000000;0.500000;,
  0.166670;0.666670;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.500000;0.666670;,
  0.666670;0.666670;,
  0.833330;0.666670;,
  1.000000;0.666670;,
  0.166670;0.833330;,
  0.000000;0.833330;,
  0.333330;0.833330;,
  0.500000;0.833330;,
  0.666670;0.833330;,
  0.833330;0.833330;,
  1.000000;0.833330;,
  0.083330;1.000000;,
  0.250000;1.000000;,
  0.416670;1.000000;,
  0.583330;1.000000;,
  0.750000;1.000000;,
  0.916670;1.000000;,
  0.000000;0.000000;,
  0.000000;0.250000;,
  0.166670;0.250000;,
  0.166670;0.000000;,
  0.000000;0.500000;,
  0.166670;0.500000;,
  0.000000;0.750000;,
  0.166670;0.750000;,
  0.000000;1.000000;,
  0.166670;1.000000;,
  0.833330;0.000000;,
  0.833330;0.250000;,
  1.000000;0.250000;,
  1.000000;0.000000;,
  0.833330;0.500000;,
  1.000000;0.500000;,
  0.833330;0.750000;,
  1.000000;0.750000;,
  0.833330;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.500000;,
  0.125000;0.500000;,
  0.125000;1.000000;,
  0.250000;0.500000;,
  0.250000;1.000000;,
  0.375000;0.500000;,
  0.375000;1.000000;,
  0.500000;0.500000;,
  0.500000;1.000000;,
  0.625000;0.500000;,
  0.625000;1.000000;,
  0.750000;0.500000;,
  0.750000;1.000000;,
  0.875000;0.500000;,
  0.875000;1.000000;,
  1.000000;0.500000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;0.000000;,
  0.187500;0.000000;,
  0.250000;0.000000;,
  0.312500;0.000000;,
  0.375000;0.000000;,
  0.437500;0.000000;,
  0.500000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.000000;0.500000;,
  0.125000;0.500000;,
  0.125000;1.000000;,
  0.250000;0.500000;,
  0.250000;1.000000;,
  0.375000;0.500000;,
  0.375000;1.000000;,
  0.500000;0.500000;,
  0.500000;1.000000;,
  0.625000;0.500000;,
  0.625000;1.000000;,
  0.750000;0.500000;,
  0.750000;1.000000;,
  0.875000;0.500000;,
  0.875000;1.000000;,
  1.000000;0.500000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;0.000000;,
  0.187500;0.000000;,
  0.250000;0.000000;,
  0.312500;0.000000;,
  0.375000;0.000000;,
  0.437500;0.000000;,
  0.500000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}
