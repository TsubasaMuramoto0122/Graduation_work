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
 204;
 -0.05615;91.43351;0.00000;,
 4.47730;87.67488;-4.48846;,
 -0.05615;87.67488;-6.34764;,
 -0.05615;91.43351;0.00000;,
 6.35513;87.67488;0.00000;,
 -0.05615;91.43351;0.00000;,
 4.47730;87.67488;4.48846;,
 -0.05615;91.43351;0.00000;,
 -0.05615;87.67488;6.34764;,
 -0.05615;91.43351;0.00000;,
 -4.58961;87.67488;4.48846;,
 -0.05615;91.43351;0.00000;,
 -6.46744;87.67488;0.00000;,
 -0.05615;91.43351;0.00000;,
 -4.58961;87.67488;-4.48846;,
 -0.05615;91.43351;0.00000;,
 -0.05615;87.67488;-6.34764;,
 7.27914;83.78160;-7.26248;,
 -0.05615;83.78160;-10.27071;,
 10.31752;83.78160;0.00000;,
 7.27914;83.78160;7.26248;,
 -0.05615;83.78160;10.27071;,
 -7.39145;83.78160;7.26248;,
 -10.42983;83.78160;0.00000;,
 -7.39145;83.78160;-7.26248;,
 -0.05615;83.78160;-10.27071;,
 6.54972;42.24190;6.25321;,
 9.28596;42.24190;0.00000;,
 -9.39827;42.24190;0.00000;,
 -6.66203;42.24190;6.25321;,
 -0.05616;42.24190;-8.84337;,
 -6.66203;42.24190;-6.25321;,
 4.90313;-0.26492;4.69453;,
 6.95733;-0.26492;-0.00000;,
 -7.06964;-0.26492;0.00000;,
 -5.01544;-0.26492;4.69453;,
 -0.05616;-0.26492;-6.63906;,
 -5.01544;-0.26492;-4.69453;,
 9.88730;83.78160;-1.02831;,
 8.81012;42.24190;-1.08746;,
 -10.17827;83.78160;-0.60125;,
 -9.08174;42.24190;-0.72337;,
 6.46293;-0.26492;-1.12985;,
 -6.69240;-0.26492;-0.86213;,
 6.40864;83.78160;7.61948;,
 5.62915;42.24190;6.61416;,
 3.99145;-0.26492;5.05200;,
 -7.59143;83.78160;-6.78446;,
 -6.89962;42.24190;-5.71021;,
 -5.28666;-0.26492;-4.07472;,
 0.80883;83.78160;-9.91596;,
 6.54972;42.24190;-6.25321;,
 0.65244;42.24190;-8.56554;,
 -0.05616;42.24190;-8.84337;,
 4.90313;-0.26492;-4.69453;,
 0.43446;-0.26492;-6.44668;,
 -0.05616;-0.26492;-6.63906;,
 0.87809;83.78160;9.88757;,
 -0.05616;42.24190;8.84337;,
 0.71503;42.24190;8.54099;,
 -0.05616;-0.26492;6.63906;,
 0.48159;-0.26492;6.42821;,
 -5.73230;83.78160;7.94290;,
 -5.16366;42.24190;6.84072;,
 -3.81136;-0.26492;5.16664;,
 6.89003;42.24190;-5.47547;,
 7.65499;83.78160;-6.36410;,
 5.19243;-0.26492;-4.03335;,
 26.60282;75.76808;0.00000;,
 28.34413;73.59730;-1.83811;,
 26.36198;74.19995;-2.59949;,
 26.60282;75.76808;0.00000;,
 29.16513;73.34768;0.00000;,
 26.60282;75.76808;0.00000;,
 28.34413;73.59730;1.83811;,
 26.60282;75.76808;0.00000;,
 26.36198;74.19995;2.59949;,
 26.60282;75.76808;0.00000;,
 24.37993;74.80258;1.83811;,
 26.60282;75.76808;0.00000;,
 23.55891;75.05219;0.00000;,
 26.60282;75.76808;0.00000;,
 24.37993;74.80258;-1.83811;,
 26.60282;75.76808;0.00000;,
 26.36198;74.19995;-2.59949;,
 29.31971;71.60056;-2.97413;,
 26.11259;72.57568;-4.20606;,
 30.64817;71.19668;0.00000;,
 29.31971;71.60056;2.97413;,
 26.11259;72.57568;4.20606;,
 22.90550;73.55074;2.97413;,
 21.57704;73.95466;0.00000;,
 22.90550;73.55074;-2.97413;,
 26.11259;72.57568;-4.20606;,
 16.25140;47.88657;2.34093;,
 16.66803;46.73272;0.00000;,
 13.82308;54.61164;0.00000;,
 14.23970;53.45779;2.34093;,
 15.24557;50.67219;-3.31057;,
 14.23970;53.45779;-2.34093;,
 5.82540;42.42632;2.15619;,
 6.20914;41.36356;0.00000;,
 3.58872;48.62063;0.00000;,
 3.97248;47.55788;2.15619;,
 4.89894;44.99210;-3.04931;,
 3.97248;47.55788;-2.15619;,
 30.46007;71.25386;-0.42111;,
 16.59557;46.93340;-0.40710;,
 21.68704;73.92123;-0.24623;,
 13.87128;54.47816;-0.27080;,
 6.11679;41.61933;-0.51894;,
 3.65920;48.42545;-0.39597;,
 28.93909;71.71631;3.12033;,
 16.11121;48.27477;2.47606;,
 5.65507;42.89799;2.32037;,
 22.81804;73.57735;-2.77837;,
 14.20354;53.55800;-2.13766;,
 3.92180;47.69817;-1.87151;,
 26.49082;72.46065;-4.06079;,
 16.25140;47.88657;-2.34093;,
 15.35345;50.37344;-3.20657;,
 15.24557;50.67219;-3.31057;,
 5.82540;42.42632;-2.15619;,
 4.99060;44.73827;-2.96095;,
 4.89894;44.99210;-3.04931;,
 26.52109;72.45145;4.04915;,
 15.24557;50.67219;3.31057;,
 15.36299;50.34699;3.19738;,
 4.89894;44.99210;3.04931;,
 4.99938;44.71387;2.95246;,
 23.63090;73.33019;3.25278;,
 14.46785;52.82595;2.56087;,
 4.19741;46.93489;2.37303;,
 16.30320;47.74306;-2.04978;,
 29.48402;71.55064;-2.60623;,
 5.87944;42.27664;-1.85251;,
 -25.81820;56.11297;0.00000;,
 -25.61127;54.69737;-2.08728;,
 -27.15308;54.26708;-1.47593;,
 -25.81820;56.11297;0.00000;,
 -27.79174;54.08887;0.00000;,
 -25.81820;56.11297;0.00000;,
 -27.15308;54.26708;1.47593;,
 -25.81820;56.11297;0.00000;,
 -25.61127;54.69737;2.08728;,
 -25.81820;56.11297;0.00000;,
 -24.06939;55.12764;1.47593;,
 -25.81820;56.11297;0.00000;,
 -23.43076;55.30587;0.00000;,
 -25.81820;56.11297;0.00000;,
 -24.06939;55.12764;-1.47593;,
 -25.81820;56.11297;0.00000;,
 -25.61127;54.69737;-2.08728;,
 -25.39685;53.23107;-3.37729;,
 -27.89162;52.53479;-2.38810;,
 -28.92500;52.24647;0.00000;,
 -27.89162;52.53479;2.38810;,
 -25.39685;53.23107;3.37729;,
 -22.90213;53.92713;2.38810;,
 -21.86873;54.21558;0.00000;,
 -22.90213;53.92713;-2.38810;,
 -25.39685;53.23107;-3.37729;,
 -23.52210;43.29425;0.00000;,
 -22.88992;43.98755;2.08723;,
 -19.83752;47.33524;2.08723;,
 -19.20535;48.02858;0.00000;,
 -19.83752;47.33524;-2.08723;,
 -21.36373;45.66140;-2.95178;,
 -6.00768;30.58827;0.00000;,
 -5.85405;31.60280;1.92251;,
 -5.11226;36.50177;1.92251;,
 -4.95863;37.51638;0.00000;,
 -5.11226;36.50177;-1.92251;,
 -5.48315;34.05231;-2.71883;,
 -28.77867;52.28727;-0.33814;,
 -23.41217;43.41480;-0.36298;,
 -21.95430;54.19167;-0.19771;,
 -19.27847;47.94832;-0.24145;,
 -5.97071;30.83240;-0.46270;,
 -4.98682;37.33004;-0.35306;,
 -27.59557;52.61745;2.50549;,
 -22.67722;44.22084;2.20771;,
 -5.78587;32.05314;2.06890;,
 -22.83410;53.94625;-2.23092;,
 -19.78263;47.39545;-1.90598;,
 -5.09195;36.63572;-1.66868;,
 -25.69106;53.14887;-3.26065;,
 -21.52743;45.48187;-2.85904;,
 -22.88992;43.98755;-2.08723;,
 -21.36373;45.66140;-2.95178;,
 -5.51985;33.80998;-2.64004;,
 -5.85405;31.60280;-1.92251;,
 -5.48315;34.05231;-2.71883;,
 -25.71461;53.14229;3.25130;,
 -21.54189;45.46602;2.85085;,
 -21.36373;45.66140;2.95178;,
 -5.52336;33.78671;2.63248;,
 -5.48315;34.05231;2.71883;,
 -23.46641;53.76968;2.61184;,
 -20.18371;46.95556;2.28333;,
 -5.20230;35.90707;2.11584;,
 -22.96853;43.90133;-1.82763;,
 -28.01943;52.49912;-2.09269;,
 -5.87569;31.45996;-1.65174;;
 
 144;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,12;,
 3;15,16,14;,
 4;2,1,17,18;,
 4;1,4,19,17;,
 4;4,6,20,19;,
 4;6,8,21,20;,
 4;8,10,22,21;,
 4;10,12,23,22;,
 4;12,14,24,23;,
 4;14,16,25,24;,
 4;19,20,26,27;,
 4;22,23,28,29;,
 4;24,25,30,31;,
 4;27,26,32,33;,
 4;29,28,34,35;,
 4;31,30,36,37;,
 4;38,19,27,39;,
 4;40,41,28,23;,
 4;39,27,33,42;,
 4;41,43,34,28;,
 4;44,45,26,20;,
 4;45,46,32,26;,
 4;47,24,31,48;,
 4;47,48,41,40;,
 4;48,31,37,49;,
 4;48,49,43,41;,
 4;50,17,51,52;,
 4;50,52,53,18;,
 4;52,51,54,55;,
 4;52,55,56,53;,
 4;57,21,58,59;,
 4;57,59,45,44;,
 4;59,58,60,61;,
 4;59,61,46,45;,
 4;62,22,29,63;,
 4;62,63,58,21;,
 4;63,29,35,64;,
 4;63,64,60,58;,
 4;65,51,17,66;,
 4;65,66,38,39;,
 4;67,54,51,65;,
 4;67,65,39,42;,
 3;68,69,70;,
 3;71,72,69;,
 3;73,74,72;,
 3;75,76,74;,
 3;77,78,76;,
 3;79,80,78;,
 3;81,82,80;,
 3;83,84,82;,
 4;70,69,85,86;,
 4;69,72,87,85;,
 4;72,74,88,87;,
 4;74,76,89,88;,
 4;76,78,90,89;,
 4;78,80,91,90;,
 4;80,82,92,91;,
 4;82,84,93,92;,
 4;87,88,94,95;,
 4;90,91,96,97;,
 4;92,93,98,99;,
 4;95,94,100,101;,
 4;97,96,102,103;,
 4;99,98,104,105;,
 4;106,87,95,107;,
 4;108,109,96,91;,
 4;107,95,101,110;,
 4;109,111,102,96;,
 4;112,113,94,88;,
 4;113,114,100,94;,
 4;115,92,99,116;,
 4;115,116,109,108;,
 4;116,99,105,117;,
 4;116,117,111,109;,
 4;118,85,119,120;,
 4;118,120,121,86;,
 4;120,119,122,123;,
 4;120,123,124,121;,
 4;125,89,126,127;,
 4;125,127,113,112;,
 4;127,126,128,129;,
 4;127,129,114,113;,
 4;130,90,97,131;,
 4;130,131,126,89;,
 4;131,97,103,132;,
 4;131,132,128,126;,
 4;133,119,85,134;,
 4;133,134,106,107;,
 4;135,122,119,133;,
 4;135,133,107,110;,
 3;136,137,138;,
 3;139,138,140;,
 3;141,140,142;,
 3;143,142,144;,
 3;145,144,146;,
 3;147,146,148;,
 3;149,148,150;,
 3;151,150,152;,
 4;137,153,154,138;,
 4;138,154,155,140;,
 4;140,155,156,142;,
 4;142,156,157,144;,
 4;144,157,158,146;,
 4;146,158,159,148;,
 4;148,159,160,150;,
 4;150,160,161,152;,
 4;155,162,163,156;,
 4;158,164,165,159;,
 4;160,166,167,161;,
 4;162,168,169,163;,
 4;164,170,171,165;,
 4;166,172,173,167;,
 4;174,175,162,155;,
 4;176,159,165,177;,
 4;175,178,168,162;,
 4;177,165,171,179;,
 4;180,156,163,181;,
 4;181,163,169,182;,
 4;183,184,166,160;,
 4;183,176,177,184;,
 4;184,185,172,166;,
 4;184,177,179,185;,
 4;186,187,188,154;,
 4;186,153,189,187;,
 4;187,190,191,188;,
 4;187,189,192,190;,
 4;193,194,195,157;,
 4;193,180,181,194;,
 4;194,196,197,195;,
 4;194,181,182,196;,
 4;198,199,164,158;,
 4;198,157,195,199;,
 4;199,200,170,164;,
 4;199,195,197,200;,
 4;201,202,154,188;,
 4;201,175,174,202;,
 4;203,201,188,191;,
 4;203,178,175,201;;
 
 MeshMaterialList {
  3;
  144;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  1,
  2,
  1,
  1,
  2,
  1,
  2,
  2,
  1,
  2,
  1,
  2,
  1,
  2,
  1,
  2,
  1,
  2,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  1,
  2,
  1,
  1,
  2,
  1,
  2,
  2,
  1,
  2,
  1,
  2,
  1,
  2,
  1,
  2,
  1,
  2,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  1,
  2,
  1,
  1,
  2,
  1,
  2,
  2,
  1,
  2,
  1,
  2,
  1,
  2,
  1,
  2,
  1,
  2,
  1;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.094400;0.408000;0.147200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.555200;0.586400;0.248000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  175;
  0.000000;1.000000;-0.000000;,
  0.000000;0.791865;-0.610696;,
  0.428630;0.793297;-0.432385;,
  0.606959;0.794734;0.000000;,
  0.428630;0.793297;0.432385;,
  0.000000;0.791865;0.610696;,
  -0.428630;0.793297;0.432385;,
  -0.606958;0.794734;0.000000;,
  -0.428630;0.793297;-0.432385;,
  -0.000004;0.375915;-0.926654;,
  0.648738;0.379375;-0.659707;,
  0.923550;0.383477;-0.000004;,
  0.648572;0.379949;0.659540;,
  -0.000003;0.375837;0.926686;,
  -0.648583;0.379912;0.659550;,
  -0.923541;0.383500;-0.000007;,
  -0.648757;0.379319;-0.659721;,
  -0.000003;-0.042636;-0.999091;,
  0.695515;-0.041694;-0.717301;,
  0.999193;-0.040165;-0.000004;,
  0.695529;-0.041060;0.717323;,
  -0.000004;-0.042722;0.999087;,
  -0.695528;-0.041101;0.717322;,
  -0.999194;-0.040140;-0.000006;,
  -0.695513;-0.041756;-0.717299;,
  0.000000;-0.051788;-0.998658;,
  0.692267;-0.053206;-0.719677;,
  0.998503;-0.054701;-0.000001;,
  0.692262;-0.053206;0.719682;,
  -0.000002;-0.051788;0.998658;,
  -0.692261;-0.053206;0.719683;,
  -0.998503;-0.054700;0.000001;,
  -0.692264;-0.053206;-0.719680;,
  0.919099;-0.023625;-0.393318;,
  -0.919098;-0.023560;-0.393324;,
  0.917128;-0.036879;-0.396884;,
  -0.917128;-0.036846;-0.396886;,
  0.914980;-0.050125;-0.400373;,
  -0.914981;-0.050125;-0.400371;,
  0.372084;-0.029839;0.927720;,
  -0.919075;-0.024881;-0.393297;,
  0.368368;-0.039033;0.928860;,
  -0.917109;-0.037506;-0.396868;,
  0.364616;-0.048223;0.929909;,
  -0.914982;-0.050125;-0.400370;,
  0.372071;-0.030978;-0.927687;,
  0.372070;-0.031053;0.927685;,
  0.368360;-0.039602;-0.928839;,
  0.368359;-0.039640;0.928838;,
  0.364616;-0.048223;-0.929908;,
  0.364615;-0.048223;0.929909;,
  -0.372081;-0.030070;0.927713;,
  0.917109;-0.037494;-0.396869;,
  -0.368366;-0.039149;0.928856;,
  -0.364616;-0.048223;0.929909;,
  0.919073;-0.024856;-0.393303;,
  0.914983;-0.050125;-0.400366;,
  0.273628;0.961836;0.000000;,
  0.223360;0.753252;-0.618645;,
  0.601006;0.675618;-0.427004;,
  0.758515;0.651655;0.000000;,
  0.601006;0.675618;0.427004;,
  0.223360;0.753252;0.618645;,
  -0.176923;0.869289;0.461557;,
  -0.358389;0.933572;0.000000;,
  -0.176923;0.869289;-0.461557;,
  0.095397;0.358926;-0.928478;,
  0.710128;0.149405;-0.688038;,
  0.823290;0.567622;0.000000;,
  0.591490;0.362062;0.720452;,
  0.095494;0.359252;0.928342;,
  -0.493722;0.571556;0.655410;,
  -0.745522;0.666481;0.000643;,
  -0.490877;0.573629;-0.655736;,
  -0.024398;-0.019058;-0.999521;,
  0.455316;-0.474530;-0.753332;,
  0.695407;-0.718616;0.000039;,
  0.454647;-0.475228;0.753296;,
  -0.024298;-0.018704;0.999530;,
  -0.512681;0.421346;0.748082;,
  -0.760683;0.649123;0.000657;,
  -0.510055;0.423591;-0.748608;,
  -0.020899;-0.007916;-0.999750;,
  0.289803;-0.579141;-0.761977;,
  0.456697;-0.889622;-0.000006;,
  0.289800;-0.579136;0.761982;,
  -0.020904;-0.007907;0.999750;,
  -0.334720;0.558729;0.758805;,
  -0.505189;0.863009;-0.000009;,
  -0.334721;0.558731;-0.758803;,
  0.799173;-0.455149;-0.392635;,
  -0.858083;0.348427;-0.377216;,
  0.623747;-0.644519;-0.442192;,
  -0.684117;0.583852;-0.437150;,
  0.405227;-0.789359;-0.461198;,
  -0.449075;0.767148;-0.458056;,
  0.313523;-0.196615;0.929003;,
  -0.855420;0.353789;-0.378273;,
  0.223656;-0.241152;0.944364;,
  -0.682090;0.586114;-0.437292;,
  0.131485;-0.283206;0.950003;,
  -0.449077;0.767152;-0.458047;,
  0.314710;-0.195562;-0.928823;,
  0.314828;-0.195515;0.928794;,
  0.224272;-0.240646;-0.944347;,
  0.224331;-0.240620;0.944340;,
  0.131491;-0.283214;-0.950000;,
  0.131486;-0.283208;0.950003;,
  -0.371055;0.137496;0.918375;,
  0.624552;-0.643769;-0.442150;,
  -0.273097;0.204329;0.940036;,
  -0.171171;0.268192;0.948037;,
  0.800367;-0.453327;-0.392311;,
  0.405230;-0.789364;-0.461187;,
  -0.249459;0.968385;0.000000;,
  -0.196151;0.723597;-0.661764;,
  -0.615222;0.642655;-0.456613;,
  -0.788029;0.615638;0.000000;,
  -0.615222;0.642655;0.456613;,
  -0.196151;0.723597;0.661764;,
  0.249049;0.834858;0.490903;,
  0.449197;0.893433;0.000000;,
  0.249049;0.834858;-0.490903;,
  -0.079666;0.325088;-0.942322;,
  -0.705043;0.112402;-0.700200;,
  -0.851769;0.523918;0.000000;,
  -0.593784;0.324068;0.736479;,
  -0.079784;0.325460;0.942184;,
  0.515042;0.539610;0.665998;,
  0.771623;0.636080;0.000193;,
  0.513259;0.541480;-0.665856;,
  0.018489;-0.025073;-0.999515;,
  -0.496586;-0.466567;-0.731927;,
  -0.736879;-0.676025;0.000016;,
  -0.497094;-0.465967;0.731965;,
  0.018405;-0.024717;0.999525;,
  0.537252;0.413046;0.735359;,
  0.783551;0.621328;0.000115;,
  0.535982;0.414816;-0.735290;,
  0.010425;-0.004951;-0.999933;,
  -0.394618;-0.553582;-0.733365;,
  -0.586583;-0.809889;0.000007;,
  -0.395534;-0.552929;0.733363;,
  0.010498;-0.005018;0.999932;,
  0.408697;0.545307;0.731852;,
  0.594371;0.804191;-0.000158;,
  0.409469;0.544849;-0.731761;,
  -0.786039;-0.474266;-0.396503;,
  0.843253;0.366331;-0.393352;,
  -0.670671;-0.615296;-0.414261;,
  0.712038;0.564658;-0.417328;,
  -0.532825;-0.735704;-0.418135;,
  0.540148;0.730729;-0.417463;,
  -0.303492;-0.211248;0.929121;,
  0.841288;0.370493;-0.393662;,
  -0.251334;-0.249355;0.935229;,
  0.711005;0.566099;-0.417138;,
  -0.198117;-0.286411;0.937400;,
  0.541057;0.730124;-0.417345;,
  -0.302785;-0.212351;-0.929101;,
  -0.302736;-0.212406;0.929104;,
  -0.250469;-0.250172;-0.935243;,
  -0.250400;-0.250207;0.935252;,
  -0.197100;-0.286941;-0.937452;,
  -0.197011;-0.286956;0.937466;,
  0.353269;0.127496;0.926793;,
  -0.670378;-0.615563;-0.414336;,
  0.285946;0.203744;0.936335;,
  0.215639;0.277865;0.936104;,
  -0.786131;-0.474124;-0.396490;,
  -0.532019;-0.736245;-0.418210;,
  0.868925;-0.494943;0.000080;,
  0.799547;-0.454371;0.392773;,
  -0.856219;-0.516613;0.000023;,
  -0.786071;-0.474199;0.396520;;
  144;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,1,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,8,16,15;,
  4;8,1,9,16;,
  4;11,12,20,19;,
  4;14,15,23,22;,
  4;16,9,17,24;,
  4;19,20,28,27;,
  4;22,23,31,30;,
  4;24,17,25,32;,
  4;33,11,19,35;,
  4;34,36,23,15;,
  4;35,19,27,37;,
  4;36,38,31,23;,
  4;39,41,20,12;,
  4;41,43,28,20;,
  4;40,16,24,42;,
  4;40,42,36,34;,
  4;42,24,32,44;,
  4;42,44,38,36;,
  4;45,10,18,47;,
  4;45,47,17,9;,
  4;47,18,26,49;,
  4;47,49,25,17;,
  4;46,13,21,48;,
  4;46,48,41,39;,
  4;48,21,29,50;,
  4;48,50,43,41;,
  4;51,14,22,53;,
  4;51,53,21,13;,
  4;53,22,30,54;,
  4;53,54,29,21;,
  4;52,18,10,55;,
  4;52,55,33,35;,
  4;56,26,18,52;,
  4;56,52,35,37;,
  3;57,59,58;,
  3;57,60,59;,
  3;57,61,60;,
  3;57,62,61;,
  3;57,63,62;,
  3;57,64,63;,
  3;57,65,64;,
  3;57,58,65;,
  4;58,59,67,66;,
  4;59,60,68,67;,
  4;60,61,69,68;,
  4;61,62,70,69;,
  4;62,63,71,70;,
  4;63,64,72,71;,
  4;64,65,73,72;,
  4;65,58,66,73;,
  4;171,172,77,76;,
  4;71,72,80,79;,
  4;73,66,74,81;,
  4;76,77,85,84;,
  4;79,80,88,87;,
  4;81,74,82,89;,
  4;90,171,76,92;,
  4;91,93,80,72;,
  4;92,76,84,94;,
  4;93,95,88,80;,
  4;96,98,77,69;,
  4;98,100,85,77;,
  4;97,73,81,99;,
  4;97,99,93,91;,
  4;99,81,89,101;,
  4;99,101,95,93;,
  4;102,67,75,104;,
  4;102,104,74,66;,
  4;104,75,83,106;,
  4;104,106,82,74;,
  4;103,70,78,105;,
  4;103,105,98,96;,
  4;105,78,86,107;,
  4;105,107,100,98;,
  4;108,71,79,110;,
  4;108,110,78,70;,
  4;110,79,87,111;,
  4;110,111,86,78;,
  4;109,75,67,112;,
  4;109,112,90,92;,
  4;113,83,75,109;,
  4;113,109,92,94;,
  3;114,115,116;,
  3;114,116,117;,
  3;114,117,118;,
  3;114,118,119;,
  3;114,119,120;,
  3;114,120,121;,
  3;114,121,122;,
  3;114,122,115;,
  4;115,123,124,116;,
  4;116,124,125,117;,
  4;117,125,126,118;,
  4;118,126,127,119;,
  4;119,127,128,120;,
  4;120,128,129,121;,
  4;121,129,130,122;,
  4;122,130,123,115;,
  4;173,133,134,174;,
  4;128,136,137,129;,
  4;130,138,131,123;,
  4;133,141,142,134;,
  4;136,144,145,137;,
  4;138,146,139,131;,
  4;147,149,133,173;,
  4;148,129,137,150;,
  4;149,151,141,133;,
  4;150,137,145,152;,
  4;153,126,134,155;,
  4;155,134,142,157;,
  4;154,156,138,130;,
  4;154,148,150,156;,
  4;156,158,146,138;,
  4;156,150,152,158;,
  4;159,161,132,124;,
  4;159,123,131,161;,
  4;161,163,140,132;,
  4;161,131,139,163;,
  4;160,162,135,127;,
  4;160,153,155,162;,
  4;162,164,143,135;,
  4;162,155,157,164;,
  4;165,167,136,128;,
  4;165,127,135,167;,
  4;167,168,144,136;,
  4;167,135,143,168;,
  4;166,169,124,132;,
  4;166,149,147,169;,
  4;170,166,132,140;,
  4;170,151,149,166;;
 }
 MeshTextureCoords {
  204;
  0.062500;0.000000;,
  0.125000;0.200000;,
  0.000000;0.200000;,
  0.187500;0.000000;,
  0.250000;0.200000;,
  0.312500;0.000000;,
  0.375000;0.200000;,
  0.437500;0.000000;,
  0.500000;0.200000;,
  0.562500;0.000000;,
  0.625000;0.200000;,
  0.687500;0.000000;,
  0.750000;0.200000;,
  0.812500;0.000000;,
  0.875000;0.200000;,
  0.937500;0.000000;,
  1.000000;0.200000;,
  0.125000;0.400000;,
  0.000000;0.400000;,
  0.250000;0.400000;,
  0.375000;0.400000;,
  0.500000;0.400000;,
  0.625000;0.400000;,
  0.750000;0.400000;,
  0.875000;0.400000;,
  1.000000;0.400000;,
  0.375000;0.600000;,
  0.250000;0.600000;,
  0.750000;0.600000;,
  0.625000;0.600000;,
  1.000000;0.600000;,
  0.875000;0.600000;,
  0.375000;0.800000;,
  0.250000;0.800000;,
  0.750000;0.800000;,
  0.625000;0.800000;,
  1.000000;0.800000;,
  0.875000;0.800000;,
  0.232300;0.400000;,
  0.228260;0.600000;,
  0.760350;0.400000;,
  0.764460;0.600000;,
  0.219920;0.800000;,
  0.772960;0.800000;,
  0.389830;0.400000;,
  0.392420;0.600000;,
  0.397980;0.800000;,
  0.866770;0.400000;,
  0.864150;0.600000;,
  0.858500;0.800000;,
  0.014740;0.400000;,
  0.125000;0.600000;,
  0.013410;0.600000;,
  0.000000;0.600000;,
  0.125000;0.800000;,
  0.012370;0.800000;,
  0.000000;0.800000;,
  0.484080;0.400000;,
  0.500000;0.600000;,
  0.485410;0.600000;,
  0.500000;0.800000;,
  0.486450;0.800000;,
  0.596730;0.400000;,
  0.596650;0.600000;,
  0.594650;0.800000;,
  0.140550;0.600000;,
  0.140460;0.400000;,
  0.142600;0.800000;,
  0.062500;0.000000;,
  0.125000;0.200000;,
  0.000000;0.200000;,
  0.187500;0.000000;,
  0.250000;0.200000;,
  0.312500;0.000000;,
  0.375000;0.200000;,
  0.437500;0.000000;,
  0.500000;0.200000;,
  0.562500;0.000000;,
  0.625000;0.200000;,
  0.687500;0.000000;,
  0.750000;0.200000;,
  0.812500;0.000000;,
  0.875000;0.200000;,
  0.937500;0.000000;,
  1.000000;0.200000;,
  0.125000;0.400000;,
  0.000000;0.400000;,
  0.250000;0.400000;,
  0.375000;0.400000;,
  0.500000;0.400000;,
  0.625000;0.400000;,
  0.750000;0.400000;,
  0.875000;0.400000;,
  1.000000;0.400000;,
  0.375000;0.600000;,
  0.250000;0.600000;,
  0.750000;0.600000;,
  0.625000;0.600000;,
  1.000000;0.600000;,
  0.875000;0.600000;,
  0.375000;0.800000;,
  0.250000;0.800000;,
  0.750000;0.800000;,
  0.625000;0.800000;,
  1.000000;0.800000;,
  0.875000;0.800000;,
  0.232300;0.400000;,
  0.228260;0.600000;,
  0.760350;0.400000;,
  0.764460;0.600000;,
  0.219920;0.800000;,
  0.772960;0.800000;,
  0.389830;0.400000;,
  0.392420;0.600000;,
  0.397980;0.800000;,
  0.866770;0.400000;,
  0.864150;0.600000;,
  0.858500;0.800000;,
  0.014740;0.400000;,
  0.125000;0.600000;,
  0.013410;0.600000;,
  0.000000;0.600000;,
  0.125000;0.800000;,
  0.012370;0.800000;,
  0.000000;0.800000;,
  0.484080;0.400000;,
  0.500000;0.600000;,
  0.485410;0.600000;,
  0.500000;0.800000;,
  0.486450;0.800000;,
  0.596730;0.400000;,
  0.596650;0.600000;,
  0.594650;0.800000;,
  0.140550;0.600000;,
  0.140460;0.400000;,
  0.142600;0.800000;,
  0.062500;0.000000;,
  0.000000;0.200000;,
  0.125000;0.200000;,
  0.187500;0.000000;,
  0.250000;0.200000;,
  0.312500;0.000000;,
  0.375000;0.200000;,
  0.437500;0.000000;,
  0.500000;0.200000;,
  0.562500;0.000000;,
  0.625000;0.200000;,
  0.687500;0.000000;,
  0.750000;0.200000;,
  0.812500;0.000000;,
  0.875000;0.200000;,
  0.937500;0.000000;,
  1.000000;0.200000;,
  0.000000;0.400000;,
  0.125000;0.400000;,
  0.250000;0.400000;,
  0.375000;0.400000;,
  0.500000;0.400000;,
  0.625000;0.400000;,
  0.750000;0.400000;,
  0.875000;0.400000;,
  1.000000;0.400000;,
  0.250000;0.600000;,
  0.375000;0.600000;,
  0.625000;0.600000;,
  0.750000;0.600000;,
  0.875000;0.600000;,
  1.000000;0.600000;,
  0.250000;0.800000;,
  0.375000;0.800000;,
  0.625000;0.800000;,
  0.750000;0.800000;,
  0.875000;0.800000;,
  1.000000;0.800000;,
  0.232300;0.400000;,
  0.228260;0.600000;,
  0.760350;0.400000;,
  0.764460;0.600000;,
  0.219920;0.800000;,
  0.772960;0.800000;,
  0.389830;0.400000;,
  0.392420;0.600000;,
  0.397980;0.800000;,
  0.866770;0.400000;,
  0.864150;0.600000;,
  0.858500;0.800000;,
  0.014740;0.400000;,
  0.013410;0.600000;,
  0.125000;0.600000;,
  0.000000;0.600000;,
  0.012370;0.800000;,
  0.125000;0.800000;,
  0.000000;0.800000;,
  0.484080;0.400000;,
  0.485410;0.600000;,
  0.500000;0.600000;,
  0.486450;0.800000;,
  0.500000;0.800000;,
  0.596730;0.400000;,
  0.596650;0.600000;,
  0.594650;0.800000;,
  0.140550;0.600000;,
  0.140460;0.400000;,
  0.142600;0.800000;;
 }
}
