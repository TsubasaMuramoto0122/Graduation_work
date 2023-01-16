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
 111;
 0.00001;40.14465;-660.33487;,
 466.92720;40.14465;-466.92720;,
 408.88597;0.22219;-408.88597;,
 0.00001;0.22219;-578.25211;,
 660.33487;40.14465;0.00003;,
 578.25211;0.22219;0.00003;,
 466.92720;40.14465;466.92720;,
 408.88597;0.22219;408.88597;,
 -0.00005;40.14465;660.33487;,
 -0.00004;0.22219;578.25211;,
 -466.92720;40.14465;466.92672;,
 -408.88597;0.22219;408.88597;,
 -660.33487;40.14465;-0.00001;,
 -578.25211;0.22219;-0.00001;,
 -466.92720;40.14465;-466.92672;,
 -408.88597;0.22219;-408.88597;,
 0.00001;40.14465;-660.33487;,
 0.00001;0.22219;-578.25211;,
 -136.20177;251.86050;-763.48575;,
 0.00001;314.66565;-666.95411;,
 0.00001;171.26258;-714.74166;,
 0.00001;314.66565;-666.95411;,
 -136.20177;251.86050;-763.48575;,
 -286.11180;291.58367;-690.73424;,
 -136.20177;138.93469;-763.48575;,
 -309.64078;178.65813;-747.53849;,
 -286.11180;291.58367;-690.73424;,
 -443.55616;251.86045;-636.17496;,
 -443.55616;138.93469;-636.17496;,
 -286.11180;65.73245;-690.73424;,
 -505.39801;171.26258;-505.39786;,
 -471.60767;314.66565;-471.60767;,
 136.20180;138.93469;-763.48575;,
 0.00001;171.26258;-714.74166;,
 286.11177;65.73245;-690.73424;,
 136.20180;251.86050;-763.48575;,
 309.64078;178.65813;-747.53849;,
 443.55616;138.93469;-636.17511;,
 443.55616;251.86050;-636.17501;,
 286.11180;291.58367;-690.73424;,
 505.39801;171.26258;-505.39801;,
 471.60767;314.66565;-471.60767;,
 763.48575;251.86050;-136.20174;,
 666.95411;314.66565;0.00003;,
 714.74166;171.26258;0.00003;,
 690.73424;291.58367;-286.11177;,
 763.48575;138.93469;-136.20174;,
 747.53849;178.65813;-309.64078;,
 636.17511;251.86045;-443.55616;,
 636.17511;138.93469;-443.55616;,
 690.73424;65.73245;-286.11177;,
 763.48575;138.93469;136.20189;,
 690.73424;65.73245;286.11180;,
 763.48575;251.86050;136.20189;,
 747.53849;178.65813;309.64078;,
 636.17501;138.93469;443.55616;,
 636.17501;251.86050;443.55616;,
 690.73424;291.58367;286.11180;,
 505.39801;171.26258;505.39801;,
 471.60767;314.66565;471.60767;,
 136.20175;251.86050;763.48575;,
 -0.00005;314.66565;666.95411;,
 -0.00006;171.26258;714.74166;,
 286.11177;291.58367;690.73424;,
 136.20175;138.93469;763.48575;,
 309.64078;178.65813;747.53849;,
 443.55616;251.86045;636.17511;,
 443.55616;138.93469;636.17511;,
 286.11177;65.73245;690.73424;,
 -443.55616;251.86050;636.17496;,
 -471.60767;314.66565;471.60767;,
 -505.39801;171.26258;505.39786;,
 -286.11180;291.58367;690.73424;,
 -443.55616;138.93469;636.17496;,
 -309.64078;178.65813;747.53849;,
 -136.20188;251.86050;763.48575;,
 -136.20188;138.93469;763.48575;,
 -286.11180;65.73245;690.73424;,
 -763.48575;251.86050;136.20169;,
 -666.95411;314.66565;-0.00001;,
 -714.74166;171.26258;-0.00001;,
 -690.73424;291.58367;286.11155;,
 -763.48575;138.93469;136.20169;,
 -747.53849;178.65813;309.64063;,
 -636.17511;251.86050;443.55611;,
 -636.17511;138.93469;443.55611;,
 -690.73424;65.73245;286.11155;,
 -763.48575;138.93469;-136.20169;,
 -690.73424;65.73245;-286.11155;,
 -763.48575;251.86050;-136.20169;,
 -747.53849;178.65813;-309.64063;,
 -636.17511;138.93469;-443.55611;,
 -636.17511;251.86050;-443.55611;,
 -690.73424;291.58367;-286.11155;,
 0.00000;314.66565;0.00000;,
 471.60767;314.66565;-471.60767;,
 0.00001;314.66565;-666.95411;,
 0.00000;314.66565;0.00000;,
 666.95411;314.66565;0.00003;,
 0.00000;314.66565;0.00000;,
 471.60767;314.66565;471.60767;,
 0.00000;314.66565;0.00000;,
 -0.00005;314.66565;666.95411;,
 0.00000;314.66565;0.00000;,
 -471.60767;314.66565;471.60767;,
 0.00000;314.66565;0.00000;,
 -666.95411;314.66565;-0.00001;,
 0.00000;314.66565;0.00000;,
 -471.60767;314.66565;-471.60767;,
 0.00000;314.66565;0.00000;,
 0.00001;314.66565;-666.95411;;
 
 160;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 3;18,19,20;,
 3;21,22,23;,
 3;24,18,20;,
 3;25,26,18;,
 3;25,27,26;,
 3;25,28,27;,
 3;25,29,28;,
 3;25,24,29;,
 3;25,18,24;,
 3;27,30,31;,
 3;30,27,28;,
 3;26,27,31;,
 3;26,31,19;,
 3;28,14,30;,
 3;14,28,29;,
 3;24,20,16;,
 3;29,24,16;,
 3;29,16,14;,
 3;32,0,33;,
 3;0,32,34;,
 3;35,32,33;,
 3;36,34,32;,
 3;36,37,34;,
 3;36,38,37;,
 3;36,39,38;,
 3;36,35,39;,
 3;36,32,35;,
 3;37,40,1;,
 3;40,37,38;,
 3;34,37,1;,
 3;34,1,0;,
 3;38,41,40;,
 3;41,38,39;,
 3;35,33,21;,
 3;39,35,21;,
 3;39,21,41;,
 3;42,43,44;,
 3;43,42,45;,
 3;46,42,44;,
 3;47,45,42;,
 3;47,48,45;,
 3;47,49,48;,
 3;47,50,49;,
 3;47,46,50;,
 3;47,42,46;,
 3;48,40,41;,
 3;40,48,49;,
 3;45,48,41;,
 3;45,41,43;,
 3;49,1,40;,
 3;1,49,50;,
 3;46,44,4;,
 3;50,46,4;,
 3;50,4,1;,
 3;51,4,44;,
 3;4,51,52;,
 3;53,51,44;,
 3;54,52,51;,
 3;54,55,52;,
 3;54,56,55;,
 3;54,57,56;,
 3;54,53,57;,
 3;54,51,53;,
 3;55,58,6;,
 3;58,55,56;,
 3;52,55,6;,
 3;52,6,4;,
 3;56,59,58;,
 3;59,56,57;,
 3;53,44,43;,
 3;57,53,43;,
 3;57,43,59;,
 3;60,61,62;,
 3;61,60,63;,
 3;64,60,62;,
 3;65,63,60;,
 3;65,66,63;,
 3;65,67,66;,
 3;65,68,67;,
 3;65,64,68;,
 3;65,60,64;,
 3;66,58,59;,
 3;58,66,67;,
 3;63,66,59;,
 3;63,59,61;,
 3;67,6,58;,
 3;6,67,68;,
 3;64,62,8;,
 3;68,64,8;,
 3;68,8,6;,
 3;69,70,71;,
 3;70,69,72;,
 3;73,69,71;,
 3;74,72,69;,
 3;74,75,72;,
 3;74,76,75;,
 3;74,77,76;,
 3;74,73,77;,
 3;74,69,73;,
 3;75,62,61;,
 3;62,75,76;,
 3;72,75,61;,
 3;72,61,70;,
 3;76,8,62;,
 3;8,76,77;,
 3;73,71,10;,
 3;77,73,10;,
 3;77,10,8;,
 3;78,79,80;,
 3;79,78,81;,
 3;82,78,80;,
 3;83,81,78;,
 3;83,84,81;,
 3;83,85,84;,
 3;83,86,85;,
 3;83,82,86;,
 3;83,78,82;,
 3;84,71,70;,
 3;71,84,85;,
 3;81,84,70;,
 3;81,70,79;,
 3;85,10,71;,
 3;10,85,86;,
 3;82,80,12;,
 3;86,82,12;,
 3;86,12,10;,
 3;87,12,80;,
 3;12,87,88;,
 3;89,87,80;,
 3;90,88,87;,
 3;90,91,88;,
 3;90,92,91;,
 3;90,93,92;,
 3;90,89,93;,
 3;90,87,89;,
 3;91,30,14;,
 3;30,91,92;,
 3;88,91,14;,
 3;88,14,12;,
 3;92,31,30;,
 3;31,92,93;,
 3;89,80,79;,
 3;93,89,79;,
 3;93,79,31;,
 3;94,95,96;,
 3;97,98,95;,
 3;99,100,98;,
 3;101,102,100;,
 3;103,104,102;,
 3;105,106,104;,
 3;107,108,106;,
 3;109,110,108;;
 
 MeshMaterialList {
  2;
  160;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\MODEL\\Objects\\Texture\\cloud.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\MODEL\\Objects\\Texture\\cloud.jpg";
   }
  }
 }
 MeshNormals {
  89;
  0.000000;1.000000;0.000000;,
  0.000000;0.899082;-0.437780;,
  0.309559;0.899081;-0.309559;,
  0.437780;0.899082;0.000000;,
  0.309559;0.899081;0.309559;,
  -0.000000;0.899082;0.437780;,
  -0.309559;0.899081;0.309559;,
  -0.437780;0.899082;0.000000;,
  -0.309559;0.899081;-0.309559;,
  0.000000;-0.027890;-0.999611;,
  0.706832;-0.027889;-0.706832;,
  0.999611;-0.027890;0.000000;,
  0.706832;-0.027889;0.706832;,
  -0.000000;-0.027890;0.999611;,
  -0.706831;-0.027890;0.706832;,
  -0.999611;-0.027890;0.000000;,
  -0.706831;-0.027890;-0.706832;,
  -0.000000;-0.806978;-0.590582;,
  0.417606;-0.806977;-0.417606;,
  0.590582;-0.806978;0.000000;,
  0.417606;-0.806977;0.417606;,
  -0.000000;-0.806978;0.590582;,
  -0.417605;-0.806977;0.417605;,
  -0.590582;-0.806978;0.000000;,
  -0.417605;-0.806977;-0.417605;,
  -0.000000;-0.899276;-0.437380;,
  0.309274;-0.899277;-0.309274;,
  0.437380;-0.899277;0.000000;,
  0.309274;-0.899277;0.309274;,
  -0.000000;-0.899277;0.437380;,
  -0.309275;-0.899276;0.309275;,
  -0.437380;-0.899277;-0.000000;,
  -0.309275;-0.899276;-0.309275;,
  -0.382684;0.001841;-0.923877;,
  0.382684;0.001842;-0.923877;,
  0.923877;0.001841;-0.382684;,
  0.923877;0.001841;0.382684;,
  0.382684;0.001841;0.923877;,
  -0.382684;0.001841;0.923877;,
  -0.923877;0.001841;0.382684;,
  -0.923877;0.001841;-0.382684;,
  0.091545;0.361923;-0.927702;,
  -0.720718;0.361921;-0.591252;,
  -0.238426;0.782194;-0.575608;,
  -0.732922;-0.332369;-0.593596;,
  0.098516;-0.332371;-0.937990;,
  -0.264021;-0.723889;-0.637400;,
  -0.098516;-0.332371;-0.937990;,
  0.732922;-0.332369;-0.593596;,
  0.264021;-0.723888;-0.637400;,
  0.720718;0.361921;-0.591252;,
  -0.091545;0.361923;-0.927702;,
  0.238426;0.782194;-0.575608;,
  0.927702;0.361923;0.091545;,
  0.591252;0.361921;-0.720718;,
  0.575608;0.782194;-0.238426;,
  0.593596;-0.332369;-0.732922;,
  0.937990;-0.332371;0.098516;,
  0.637400;-0.723888;-0.264021;,
  0.937990;-0.332371;-0.098516;,
  0.593596;-0.332369;0.732922;,
  0.637400;-0.723888;0.264021;,
  0.591252;0.361921;0.720718;,
  0.927702;0.361923;-0.091545;,
  0.575608;0.782194;0.238426;,
  -0.091545;0.361923;0.927702;,
  0.720718;0.361921;0.591252;,
  0.238426;0.782194;0.575608;,
  0.732922;-0.332369;0.593596;,
  -0.098516;-0.332371;0.937990;,
  0.264021;-0.723888;0.637400;,
  -0.720718;0.361921;0.591252;,
  0.091545;0.361923;0.927702;,
  -0.238426;0.782194;0.575608;,
  0.098516;-0.332371;0.937990;,
  -0.732922;-0.332369;0.593596;,
  -0.264021;-0.723889;0.637400;,
  -0.927702;0.361923;-0.091545;,
  -0.591252;0.361921;0.720718;,
  -0.575608;0.782195;0.238425;,
  -0.593596;-0.332370;0.732922;,
  -0.937990;-0.332371;-0.098516;,
  -0.637400;-0.723889;0.264021;,
  -0.937990;-0.332371;0.098516;,
  -0.593596;-0.332370;-0.732922;,
  -0.637400;-0.723889;-0.264021;,
  -0.591252;0.361921;-0.720718;,
  -0.927702;0.361923;0.091545;,
  -0.575608;0.782195;-0.238425;;
  160;
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,17,25,32;,
  3;41,1,9;,
  3;1,41,43;,
  3;45,41,9;,
  3;33,43,41;,
  3;33,42,43;,
  3;33,44,42;,
  3;33,46,44;,
  3;33,45,46;,
  3;33,41,45;,
  3;42,16,8;,
  3;16,42,44;,
  3;43,42,8;,
  3;43,8,1;,
  3;44,24,16;,
  3;24,44,46;,
  3;45,9,17;,
  3;46,45,17;,
  3;46,17,24;,
  3;47,17,9;,
  3;17,47,49;,
  3;51,47,9;,
  3;34,49,47;,
  3;34,48,49;,
  3;34,50,48;,
  3;34,52,50;,
  3;34,51,52;,
  3;34,47,51;,
  3;48,10,18;,
  3;10,48,50;,
  3;49,48,18;,
  3;49,18,17;,
  3;50,2,10;,
  3;2,50,52;,
  3;51,9,1;,
  3;52,51,1;,
  3;52,1,2;,
  3;53,3,11;,
  3;3,53,55;,
  3;57,53,11;,
  3;35,55,53;,
  3;35,54,55;,
  3;35,56,54;,
  3;35,58,56;,
  3;35,57,58;,
  3;35,53,57;,
  3;54,10,2;,
  3;10,54,56;,
  3;55,54,2;,
  3;55,2,3;,
  3;56,18,10;,
  3;18,56,58;,
  3;57,11,19;,
  3;58,57,19;,
  3;58,19,18;,
  3;59,19,11;,
  3;19,59,61;,
  3;63,59,11;,
  3;36,61,59;,
  3;36,60,61;,
  3;36,62,60;,
  3;36,64,62;,
  3;36,63,64;,
  3;36,59,63;,
  3;60,12,20;,
  3;12,60,62;,
  3;61,60,20;,
  3;61,20,19;,
  3;62,4,12;,
  3;4,62,64;,
  3;63,11,3;,
  3;64,63,3;,
  3;64,3,4;,
  3;65,5,13;,
  3;5,65,67;,
  3;69,65,13;,
  3;37,67,65;,
  3;37,66,67;,
  3;37,68,66;,
  3;37,70,68;,
  3;37,69,70;,
  3;37,65,69;,
  3;66,12,4;,
  3;12,66,68;,
  3;67,66,4;,
  3;67,4,5;,
  3;68,20,12;,
  3;20,68,70;,
  3;69,13,21;,
  3;70,69,21;,
  3;70,21,20;,
  3;71,6,14;,
  3;6,71,73;,
  3;75,71,14;,
  3;38,73,71;,
  3;38,72,73;,
  3;38,74,72;,
  3;38,76,74;,
  3;38,75,76;,
  3;38,71,75;,
  3;72,13,5;,
  3;13,72,74;,
  3;73,72,5;,
  3;73,5,6;,
  3;74,21,13;,
  3;21,74,76;,
  3;75,14,22;,
  3;76,75,22;,
  3;76,22,21;,
  3;77,7,15;,
  3;7,77,79;,
  3;81,77,15;,
  3;39,79,77;,
  3;39,78,79;,
  3;39,80,78;,
  3;39,82,80;,
  3;39,81,82;,
  3;39,77,81;,
  3;78,14,6;,
  3;14,78,80;,
  3;79,78,6;,
  3;79,6,7;,
  3;80,22,14;,
  3;22,80,82;,
  3;81,15,23;,
  3;82,81,23;,
  3;82,23,22;,
  3;83,23,15;,
  3;23,83,85;,
  3;87,83,15;,
  3;40,85,83;,
  3;40,84,85;,
  3;40,86,84;,
  3;40,88,86;,
  3;40,87,88;,
  3;40,83,87;,
  3;84,16,24;,
  3;16,84,86;,
  3;85,84,24;,
  3;85,24,23;,
  3;86,8,16;,
  3;8,86,88;,
  3;87,15,7;,
  3;88,87,7;,
  3;88,7,8;,
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,1,8;;
 }
 MeshTextureCoords {
  111;
  0.000000;0.480672;,
  0.125000;0.480672;,
  0.125000;0.499878;,
  0.000000;0.499878;,
  0.250000;0.480672;,
  0.250000;0.499878;,
  0.375000;0.480672;,
  0.375000;0.499878;,
  0.500000;0.480672;,
  0.500000;0.499878;,
  0.625000;0.480672;,
  0.625000;0.499878;,
  0.750000;0.480672;,
  0.750000;0.499878;,
  0.875000;0.480672;,
  0.875000;0.499878;,
  1.000000;0.480672;,
  1.000000;0.499878;,
  0.971903;0.400047;,
  1.000000;0.359679;,
  1.000000;0.425140;,
  0.000000;0.359679;,
  -0.028097;0.400047;,
  -0.062500;0.381634;,
  0.971903;0.443575;,
  0.937500;0.430826;,
  0.937500;0.381634;,
  0.903097;0.400047;,
  0.903097;0.443575;,
  0.937500;0.472086;,
  0.875000;0.425140;,
  0.875000;0.359679;,
  0.028097;0.443575;,
  0.000000;0.425140;,
  0.062500;0.472086;,
  0.028097;0.400047;,
  0.062500;0.430826;,
  0.096903;0.443575;,
  0.096903;0.400047;,
  0.062500;0.381634;,
  0.125000;0.425140;,
  0.125000;0.359679;,
  0.221903;0.400047;,
  0.250000;0.359679;,
  0.250000;0.425140;,
  0.187500;0.381634;,
  0.221903;0.443575;,
  0.187500;0.430826;,
  0.153097;0.400047;,
  0.153097;0.443575;,
  0.187500;0.472086;,
  0.278097;0.443575;,
  0.312500;0.472086;,
  0.278097;0.400047;,
  0.312500;0.430826;,
  0.346903;0.443575;,
  0.346903;0.400047;,
  0.312500;0.381634;,
  0.375000;0.425140;,
  0.375000;0.359679;,
  0.471903;0.400047;,
  0.500000;0.359679;,
  0.500000;0.425140;,
  0.437500;0.381634;,
  0.471903;0.443575;,
  0.437500;0.430826;,
  0.403097;0.400047;,
  0.403097;0.443575;,
  0.437500;0.472086;,
  0.596903;0.400047;,
  0.625000;0.359679;,
  0.625000;0.425140;,
  0.562500;0.381634;,
  0.596903;0.443575;,
  0.562500;0.430826;,
  0.528097;0.400047;,
  0.528097;0.443575;,
  0.562500;0.472086;,
  0.721903;0.400047;,
  0.750000;0.359679;,
  0.750000;0.425140;,
  0.687500;0.381634;,
  0.721903;0.443575;,
  0.687500;0.430826;,
  0.653097;0.400047;,
  0.653097;0.443575;,
  0.687500;0.472086;,
  0.778097;0.443575;,
  0.812500;0.472086;,
  0.778097;0.400047;,
  0.812500;0.430826;,
  0.846903;0.443575;,
  0.846903;0.400047;,
  0.812500;0.381634;,
  0.062500;0.125000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.187500;0.125000;,
  0.250000;0.250000;,
  0.312500;0.125000;,
  0.375000;0.250000;,
  0.437500;0.125000;,
  0.500000;0.250000;,
  0.562500;0.125000;,
  0.625000;0.250000;,
  0.687500;0.125000;,
  0.750000;0.250000;,
  0.812500;0.125000;,
  0.875000;0.250000;,
  0.937500;0.125000;,
  1.000000;0.250000;;
 }
}
