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
 168;
 0.00001;37.87118;-554.56305;,
 392.13602;37.87118;-392.13602;,
 343.39131;4.34324;-343.39131;,
 0.00001;4.34324;-485.62823;,
 554.56305;37.87118;0.00003;,
 485.62823;4.34324;0.00003;,
 392.13602;37.87118;392.13602;,
 343.39131;4.34324;343.39131;,
 -0.00004;37.87118;554.56305;,
 -0.00003;4.34324;485.62823;,
 -392.13602;37.87118;392.13514;,
 -343.39131;4.34324;343.39131;,
 -554.56305;37.87118;-0.00001;,
 -485.62823;4.34324;-0.00001;,
 -392.13602;37.87118;-392.13514;,
 -343.39131;4.34324;-343.39131;,
 0.00001;37.87118;-554.56305;,
 0.00001;4.34324;-485.62823;,
 -114.38523;215.67476;-641.19176;,
 0.00001;268.41919;-560.12227;,
 0.00001;147.98664;-600.25514;,
 0.00001;268.41919;-560.12227;,
 -114.38523;215.67476;-641.19176;,
 -240.28289;249.03477;-580.09366;,
 -114.38523;120.83684;-641.19176;,
 -260.04297;154.19733;-627.79962;,
 -240.28289;249.03477;-580.09366;,
 -372.50818;215.67451;-534.27310;,
 -372.50818;120.83684;-534.27310;,
 -240.28289;59.35981;-580.09366;,
 -424.44400;147.98664;-424.44390;,
 -396.06649;268.41919;-396.06649;,
 114.38523;120.83684;-641.19176;,
 0.00001;147.98664;-600.25514;,
 240.28289;59.35981;-580.09366;,
 114.38523;215.67476;-641.19176;,
 260.04297;154.19733;-627.79962;,
 372.50818;120.83684;-534.27310;,
 372.50818;215.67476;-534.27310;,
 240.28289;249.03477;-580.09366;,
 424.44400;147.98664;-424.44400;,
 396.06649;268.41919;-396.06649;,
 641.19176;215.67476;-114.38522;,
 560.12227;268.41919;0.00003;,
 600.25514;147.98664;0.00003;,
 580.09366;249.03477;-240.28289;,
 641.19176;120.83684;-114.38522;,
 627.79962;154.19733;-260.04297;,
 534.27310;215.67451;-372.50818;,
 534.27310;120.83684;-372.50818;,
 580.09366;59.35981;-240.28289;,
 641.19176;120.83684;114.38526;,
 580.09366;59.35981;240.28289;,
 641.19176;215.67476;114.38526;,
 627.79962;154.19733;260.04297;,
 534.27310;120.83684;372.50818;,
 534.27310;215.67476;372.50818;,
 580.09366;249.03477;240.28289;,
 424.44400;147.98664;424.44400;,
 396.06649;268.41919;396.06649;,
 114.38522;215.67476;641.19176;,
 -0.00004;268.41919;560.12227;,
 -0.00005;147.98664;600.25514;,
 240.28289;249.03477;580.09366;,
 114.38522;120.83684;641.19176;,
 260.04297;154.19733;627.79962;,
 372.50818;215.67451;534.27310;,
 372.50818;120.83684;534.27310;,
 240.28289;59.35981;580.09366;,
 -372.50818;215.67476;534.27310;,
 -396.06649;268.41919;396.06649;,
 -424.44400;147.98664;424.44390;,
 -240.28289;249.03477;580.09366;,
 -372.50818;120.83684;534.27310;,
 -260.04297;154.19733;627.79962;,
 -114.38526;215.67476;641.19176;,
 -114.38526;120.83684;641.19176;,
 -240.28289;59.35981;580.09366;,
 -641.19176;215.67476;114.38518;,
 -560.12227;268.41919;-0.00001;,
 -600.25514;147.98664;-0.00001;,
 -580.09366;249.03477;240.28279;,
 -641.19176;120.83684;114.38518;,
 -627.79962;154.19733;260.04278;,
 -534.27310;215.67476;372.50818;,
 -534.27310;120.83684;372.50818;,
 -580.09366;59.35981;240.28279;,
 -641.19176;120.83684;-114.38518;,
 -580.09366;59.35981;-240.28279;,
 -641.19176;215.67476;-114.38518;,
 -627.79962;154.19733;-260.04278;,
 -534.27310;120.83684;-372.50818;,
 -534.27310;215.67476;-372.50818;,
 -580.09366;249.03477;-240.28279;,
 234.63035;268.41919;-234.63035;,
 0.00000;268.41919;-280.06114;,
 0.00000;268.41919;0.00000;,
 280.06114;268.41919;0.00001;,
 234.63035;268.41919;234.63035;,
 -0.00002;268.41919;280.06114;,
 -234.63035;268.41919;234.63035;,
 -280.06114;268.41919;0.00000;,
 -234.63035;268.41919;-234.63035;,
 -0.00002;268.41919;309.89485;,
 -0.00002;268.41919;280.06114;,
 -234.63035;268.41919;234.63035;,
 -259.62449;268.41919;259.62449;,
 -234.63035;268.41919;234.63035;,
 -280.06114;268.41919;0.00000;,
 -309.89485;268.41919;0.00000;,
 -259.62449;268.41919;259.62449;,
 -234.63035;268.41919;-234.63035;,
 -259.62449;268.41919;-259.62449;,
 -309.89485;268.41919;0.00000;,
 -280.06114;268.41919;0.00000;,
 0.00000;268.41919;-280.06114;,
 0.00000;268.41919;-309.89485;,
 -259.62449;268.41919;-259.62449;,
 -234.63035;268.41919;-234.63035;,
 234.63035;268.41919;-234.63035;,
 259.62449;268.41919;-259.62449;,
 0.00000;268.41919;-309.89485;,
 0.00000;268.41919;-280.06114;,
 259.62449;268.41919;-259.62449;,
 234.63035;268.41919;-234.63035;,
 280.06114;268.41919;0.00001;,
 309.89485;268.41919;0.00001;,
 234.63035;268.41919;234.63035;,
 259.62449;268.41919;259.62449;,
 309.89485;268.41919;0.00001;,
 280.06114;268.41919;0.00001;,
 -0.00002;268.41919;280.06114;,
 -0.00002;268.41919;309.89485;,
 259.62449;268.41919;259.62449;,
 234.63035;268.41919;234.63035;,
 -435.00797;328.04529;0.00000;,
 -396.06649;268.41919;-396.06649;,
 -560.12227;268.41919;-0.00001;,
 -435.00797;328.04529;0.00000;,
 -396.06649;268.41919;396.06649;,
 0.00000;309.24822;-435.00797;,
 396.06649;268.41919;-396.06649;,
 0.00001;268.41919;-560.12227;,
 435.00884;328.04529;0.00073;,
 396.06649;268.41919;396.06649;,
 560.12227;268.41919;0.00003;,
 0.00000;309.24822;-435.00797;,
 0.00001;268.41919;-560.12227;,
 435.00884;328.04529;0.00073;,
 -236.98255;294.85237;478.09473;,
 -0.00004;268.41919;560.12227;,
 -0.00004;294.84642;441.84219;,
 -157.68532;329.10276;347.31678;,
 157.68532;329.10276;347.31678;,
 259.62449;268.41919;259.62449;,
 236.98245;294.85237;478.09473;,
 -0.00004;294.84642;441.84219;,
 -0.00004;294.84642;441.84219;,
 -0.00004;294.84642;441.84219;,
 -236.98255;294.85237;478.09473;,
 236.98245;294.85237;478.09473;,
 -259.62449;268.41919;-259.62449;,
 -259.62449;268.41919;-259.62449;,
 259.62449;268.41919;-259.62449;,
 259.62449;268.41919;-259.62449;,
 259.62449;268.41919;259.62449;,
 -259.62449;268.41919;259.62449;,
 -259.62449;268.41919;259.62449;;
 
 200;
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
 3;97,94,96;,
 3;98,97,96;,
 3;99,98,96;,
 3;100,99,96;,
 3;101,100,96;,
 3;102,96,95;,
 3;102,101,96;,
 4;103,104,105,106;,
 4;107,108,109,110;,
 4;111,112,113,114;,
 4;115,116,117,118;,
 4;119,120,121,122;,
 4;123,124,125,126;,
 4;127,128,129,130;,
 4;131,132,133,134;,
 3;135,136,137;,
 3;135,113,112;,
 3;138,110,109;,
 3;138,137,139;,
 3;140,141,142;,
 3;140,121,120;,
 3;143,144,145;,
 3;143,129,128;,
 3;117,116,146;,
 3;136,146,147;,
 3;148,123,126;,
 3;148,145,141;,
 3;149,150,151;,
 3;152,149,151;,
 3;152,103,106;,
 3;153,133,132;,
 3;153,144,154;,
 3;155,156,150;,
 3;155,153,156;,
 3;155,144,153;,
 3;157,103,152;,
 3;158,153,132;,
 3;159,72,61;,
 3;159,70,72;,
 3;160,63,59;,
 3;160,61,63;,
 3;161,136,135;,
 3;162,146,136;,
 3;163,148,141;,
 3;164,141,140;,
 3;165,144,143;,
 3;166,138,139;,
 3;152,167,139;,
 3;152,139,149;;
 
 MeshMaterialList {
  2;
  200;
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
  105;
  0.000000;1.000000;0.000000;,
  -0.000000;0.858818;-0.512281;,
  0.299177;0.905517;-0.300887;,
  0.542482;0.840068;0.000000;,
  0.363632;0.887712;0.282381;,
  0.000000;0.835737;0.549130;,
  -0.363631;0.887712;0.282380;,
  -0.542481;0.840068;0.000000;,
  -0.299177;0.905517;-0.300887;,
  -0.000000;-0.027890;-0.999611;,
  0.706832;-0.027888;-0.706832;,
  0.999611;-0.027890;-0.000000;,
  0.706832;-0.027888;0.706832;,
  0.000000;-0.027890;0.999611;,
  -0.706832;-0.027890;0.706832;,
  -0.999611;-0.027890;0.000000;,
  -0.706831;-0.027890;-0.706832;,
  -0.000000;-0.806979;-0.590581;,
  0.417606;-0.806976;-0.417606;,
  0.590581;-0.806979;-0.000000;,
  0.417606;-0.806976;0.417606;,
  -0.000000;-0.806979;0.590581;,
  -0.417606;-0.806977;0.417606;,
  -0.590581;-0.806979;0.000000;,
  -0.417606;-0.806977;-0.417606;,
  -0.000001;-0.899276;-0.437382;,
  0.309275;-0.899277;-0.309275;,
  0.437381;-0.899276;0.000000;,
  0.309275;-0.899277;0.309275;,
  -0.000001;-0.899276;0.437382;,
  -0.309276;-0.899276;0.309276;,
  -0.437382;-0.899276;-0.000000;,
  -0.309276;-0.899276;-0.309276;,
  -0.382685;0.001842;-0.923877;,
  0.382685;0.001842;-0.923877;,
  0.923877;0.001842;-0.382685;,
  0.923877;0.001842;0.382685;,
  0.382685;0.001842;0.923877;,
  -0.382685;0.001842;0.923877;,
  -0.923877;0.001842;0.382684;,
  -0.923877;0.001842;-0.382684;,
  0.091547;0.361924;-0.927701;,
  -0.720720;0.361921;-0.591250;,
  -0.238425;0.782196;-0.575606;,
  -0.732924;-0.332368;-0.593594;,
  0.098519;-0.332372;-0.937989;,
  -0.264020;-0.723890;-0.637398;,
  -0.098519;-0.332372;-0.937989;,
  0.732924;-0.332367;-0.593595;,
  0.264020;-0.723890;-0.637399;,
  0.720719;0.361922;-0.591250;,
  -0.091547;0.361924;-0.927701;,
  0.238425;0.782197;-0.575606;,
  0.927701;0.361924;0.091547;,
  0.591250;0.361921;-0.720719;,
  0.575606;0.782196;-0.238425;,
  0.593595;-0.332367;-0.732924;,
  0.937989;-0.332372;0.098519;,
  0.637399;-0.723890;-0.264020;,
  0.937989;-0.332372;-0.098519;,
  0.593595;-0.332367;0.732924;,
  0.637399;-0.723890;0.264020;,
  0.591250;0.361922;0.720719;,
  0.927701;0.361924;-0.091547;,
  0.575606;0.782197;0.238425;,
  -0.091547;0.361924;0.927701;,
  0.720719;0.361921;0.591250;,
  0.248943;0.776373;0.579028;,
  0.732924;-0.332367;0.593595;,
  -0.098519;-0.332372;0.937989;,
  0.264020;-0.723890;0.637399;,
  -0.720719;0.361922;0.591250;,
  0.091547;0.361924;0.927701;,
  -0.248943;0.776373;0.579027;,
  0.098519;-0.332372;0.937989;,
  -0.732924;-0.332368;0.593594;,
  -0.264020;-0.723890;0.637398;,
  -0.927701;0.361924;-0.091547;,
  -0.591250;0.361922;0.720719;,
  -0.575606;0.782197;0.238425;,
  -0.593594;-0.332369;0.732924;,
  -0.937989;-0.332372;-0.098519;,
  -0.637398;-0.723890;0.264020;,
  -0.937989;-0.332372;0.098519;,
  -0.593594;-0.332369;-0.732924;,
  -0.637398;-0.723890;-0.264020;,
  -0.591250;0.361922;-0.720719;,
  -0.927701;0.361924;0.091547;,
  -0.575606;0.782197;-0.238425;,
  0.000000;0.953204;-0.302327;,
  -0.220157;0.975464;0.000000;,
  0.000000;0.987610;0.156926;,
  0.220158;0.975464;0.000000;,
  0.050388;0.998730;0.000000;,
  0.090539;0.994086;0.059965;,
  0.071125;0.984507;-0.160272;,
  0.000000;0.999457;0.032938;,
  -0.090539;0.994086;0.059965;,
  -0.050386;0.998730;0.000000;,
  -0.071125;0.984507;-0.160272;,
  -0.106600;0.952620;0.284870;,
  -0.006404;0.986687;-0.162503;,
  0.006404;0.986687;-0.162503;,
  0.106600;0.952620;0.284870;,
  0.000000;0.994254;0.107047;;
  200;
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
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  4;89,0,0,95;,
  4;0,0,92,95;,
  4;0,94,92,0;,
  4;0,91,94,0;,
  4;0,97,91,0;,
  4;97,0,0,90;,
  4;0,99,90,0;,
  4;0,89,99,0;,
  3;93,8,7;,
  3;93,92,94;,
  3;93,95,92;,
  3;93,7,6;,
  3;96,2,1;,
  3;96,91,97;,
  3;98,4,3;,
  3;98,90,99;,
  3;94,91,96;,
  3;8,96,1;,
  3;98,97,90;,
  3;98,3,2;,
  3;100,5,104;,
  3;101,100,104;,
  3;101,89,95;,
  3;102,99,89;,
  3;102,4,99;,
  3;103,104,5;,
  3;103,102,104;,
  3;103,4,102;,
  3;104,89,101;,
  3;104,102,89;,
  3;100,73,5;,
  3;100,6,73;,
  3;103,67,4;,
  3;103,5,67;,
  3;94,8,93;,
  3;94,96,8;,
  3;97,98,2;,
  3;97,2,96;,
  3;99,4,98;,
  3;95,93,6;,
  3;101,95,6;,
  3;101,6,100;;
 }
 MeshTextureCoords {
  168;
  0.000000;0.478296;,
  0.125000;0.478296;,
  0.125000;0.497153;,
  0.000000;0.497153;,
  0.250000;0.478296;,
  0.250000;0.497153;,
  0.375000;0.478296;,
  0.375000;0.497153;,
  0.500000;0.478296;,
  0.500000;0.497153;,
  0.625000;0.478296;,
  0.625000;0.497153;,
  0.750000;0.478296;,
  0.750000;0.497153;,
  0.875000;0.478296;,
  0.875000;0.497153;,
  1.000000;0.478296;,
  1.000000;0.497153;,
  0.971903;0.398213;,
  1.000000;0.357753;,
  1.000000;0.423058;,
  0.000000;0.357753;,
  -0.028097;0.398213;,
  -0.062500;0.379809;,
  0.971903;0.441609;,
  0.937500;0.428972;,
  0.937500;0.379809;,
  0.903097;0.398213;,
  0.903097;0.441609;,
  0.937500;0.469997;,
  0.875000;0.423058;,
  0.875000;0.357753;,
  0.028097;0.441609;,
  0.000000;0.423058;,
  0.062500;0.469997;,
  0.028097;0.398213;,
  0.062500;0.428972;,
  0.096903;0.441609;,
  0.096903;0.398213;,
  0.062500;0.379809;,
  0.125000;0.423058;,
  0.125000;0.357753;,
  0.221903;0.398213;,
  0.250000;0.357753;,
  0.250000;0.423058;,
  0.187500;0.379809;,
  0.221903;0.441609;,
  0.187500;0.428972;,
  0.153097;0.398213;,
  0.153097;0.441609;,
  0.187500;0.469997;,
  0.278097;0.441609;,
  0.312500;0.469997;,
  0.278097;0.398213;,
  0.312500;0.428972;,
  0.346903;0.441609;,
  0.346903;0.398213;,
  0.312500;0.379809;,
  0.375000;0.423058;,
  0.375000;0.357753;,
  0.471903;0.398213;,
  0.500000;0.357753;,
  0.500000;0.423058;,
  0.437500;0.379809;,
  0.471903;0.441609;,
  0.437500;0.428972;,
  0.403097;0.398213;,
  0.403097;0.441609;,
  0.437500;0.469997;,
  0.596903;0.398213;,
  0.625000;0.357753;,
  0.625000;0.423058;,
  0.562500;0.379809;,
  0.596903;0.441609;,
  0.562500;0.428972;,
  0.528097;0.398213;,
  0.528097;0.441609;,
  0.562500;0.469997;,
  0.721903;0.398213;,
  0.750000;0.357753;,
  0.750000;0.423058;,
  0.687500;0.379809;,
  0.721903;0.441609;,
  0.687500;0.428972;,
  0.653097;0.398213;,
  0.653097;0.441609;,
  0.687500;0.469997;,
  0.778097;0.441609;,
  0.812500;0.469997;,
  0.778097;0.398213;,
  0.812500;0.428972;,
  0.846903;0.441609;,
  0.846903;0.398213;,
  0.812500;0.379809;,
  0.176900;0.451540;,
  0.134030;0.459840;,
  0.134030;0.408660;,
  0.185210;0.408660;,
  0.176900;0.365790;,
  0.134030;0.357490;,
  0.091160;0.365790;,
  0.082860;0.408660;,
  0.091160;0.451540;,
  0.515620;0.218750;,
  0.531250;0.187500;,
  0.593750;0.187500;,
  0.609380;0.218750;,
  0.656250;0.187500;,
  0.718750;0.187500;,
  0.734380;0.218750;,
  0.640620;0.218750;,
  0.843750;0.187500;,
  0.859380;0.218750;,
  0.765620;0.218750;,
  0.781250;0.187500;,
  0.968750;0.187500;,
  0.984380;0.218750;,
  0.890620;0.218750;,
  0.906250;0.187500;,
  0.093750;0.187500;,
  0.109380;0.218750;,
  0.015620;0.218750;,
  0.031250;0.187500;,
  0.140620;0.218750;,
  0.156250;0.187500;,
  0.218750;0.187500;,
  0.234380;0.218750;,
  0.343750;0.187500;,
  0.359370;0.218750;,
  0.265620;0.218750;,
  0.281250;0.187500;,
  0.468750;0.187500;,
  0.484370;0.218750;,
  0.390630;0.218750;,
  0.406250;0.187500;,
  0.757810;0.234380;,
  0.875000;0.250000;,
  0.750000;0.250000;,
  0.742190;0.234380;,
  0.625000;0.250000;,
  0.007810;0.234380;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.257810;0.234380;,
  0.375000;0.250000;,
  0.250000;0.250000;,
  0.992190;0.234380;,
  1.000000;0.250000;,
  0.242190;0.234380;,
  0.566410;0.242190;,
  0.500000;0.250000;,
  0.507810;0.234380;,
  0.558590;0.226560;,
  0.441410;0.226560;,
  0.382810;0.234380;,
  0.433590;0.242190;,
  0.492190;0.234380;,
  0.511720;0.226560;,
  0.488280;0.226560;,
  0.573241;0.339314;,
  0.426759;0.339314;,
  0.863280;0.226560;,
  0.886720;0.226560;,
  0.136720;0.226560;,
  0.113280;0.226560;,
  0.363280;0.226560;,
  0.636720;0.226560;,
  0.617190;0.234380;;
 }
}
