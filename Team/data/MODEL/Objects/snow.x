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
 94;
 -15.94387;169.24671;365.56255;,
 -6.83235;117.02505;556.48204;,
 171.61077;69.91369;550.80011;,
 171.61209;99.16909;340.60171;,
 -15.94387;69.91369;-275.40000;,
 -15.94387;79.27689;-52.74420;,
 171.61077;69.91369;0.00005;,
 149.76311;58.05144;-275.40000;,
 156.21917;87.32285;-550.80001;,
 -15.94387;107.12300;-550.80001;,
 317.83848;1.53374;-84.73673;,
 346.06880;1.53373;-266.21465;,
 328.76343;1.53374;102.21859;,
 317.83848;1.53374;-84.73673;,
 -15.94387;106.32998;159.76801;,
 336.28807;1.53374;-464.97340;,
 338.60469;1.53374;-567.53170;,
 332.34283;-19.35043;565.86021;,
 301.56631;1.53374;283.76590;,
 301.56631;1.53374;283.76590;,
 -189.71048;79.12883;556.48204;,
 -15.94387;169.24671;365.56255;,
 -215.46468;112.06089;365.56255;,
 -178.03470;82.24158;-550.80001;,
 -183.38421;42.98998;-275.40000;,
 -15.94387;69.91369;-275.40000;,
 -15.94387;107.12300;-550.80001;,
 -197.40403;96.20103;117.54075;,
 -15.94387;79.27689;-52.74420;,
 -197.40403;96.20103;117.54075;,
 -15.94387;106.32998;159.76801;,
 -197.40403;96.20103;117.54075;,
 338.60469;1.53374;-567.53170;,
 403.56929;-102.51140;-659.13146;,
 218.02554;-102.51140;-880.24513;,
 185.19555;1.53369;-740.62052;,
 201.02929;-19.35043;734.64181;,
 232.66206;-123.39558;878.57374;,
 393.93443;-123.39558;657.45997;,
 332.34283;-19.35043;565.86021;,
 346.06880;1.53373;-266.21465;,
 317.83848;1.53374;-84.73673;,
 379.45125;-102.51140;-98.41322;,
 412.23795;-102.51140;-309.18169;,
 400.87857;-102.51140;-540.02032;,
 336.28807;1.53374;-464.97340;,
 328.76343;1.53374;102.21859;,
 390.33082;-102.51240;119.48924;,
 392.41216;-102.51140;0.00005;,
 317.83848;1.53374;-84.73673;,
 332.34283;-19.35043;565.86021;,
 385.39788;-102.51240;494.34835;,
 360.55469;-102.51344;329.56578;,
 301.56631;1.53374;283.76590;,
 403.56929;-102.51140;-659.13146;,
 338.60469;1.53374;-567.53170;,
 301.56631;1.53374;283.76590;,
 378.25218;-102.51284;237.53670;,
 -339.75784;1.53375;-567.53170;,
 -178.03470;82.24158;-550.80001;,
 -157.14011;1.53373;-740.62047;,
 -219.29351;-102.51140;-880.24513;,
 -413.84976;-102.51140;-659.13146;,
 -157.14011;1.53373;-740.62047;,
 -15.94387;107.12300;-550.80001;,
 156.21917;87.32285;-550.80001;,
 -181.37089;-0.64316;745.02262;,
 -189.71048;79.12883;556.48204;,
 -341.65569;1.53375;567.53180;,
 -413.84976;-102.51140;659.13155;,
 -219.29351;-102.51140;880.24533;,
 -346.92784;1.53375;376.66741;,
 -413.84976;-102.51344;437.46158;,
 -413.84976;-102.51140;659.13155;,
 -341.65569;1.53375;567.53180;,
 -339.75784;1.53375;-567.53170;,
 -413.84976;-102.51140;-659.13146;,
 -413.84976;-102.51140;-329.56573;,
 -325.53545;1.53374;-283.76585;,
 -413.84976;-102.51140;0.00005;,
 -343.82571;1.53376;9.98761;,
 -346.92784;1.53375;376.66741;,
 -343.82571;1.53376;9.98761;,
 174.03627;1.53376;745.24630;,
 171.61077;69.91369;550.80011;,
 -6.83235;117.02505;556.48204;,
 -168.33650;-0.64309;750.92823;,
 -157.14011;1.53373;-740.62047;,
 338.60469;1.53374;-567.53170;,
 332.34283;-19.35043;565.86021;,
 301.56631;1.53374;283.76590;,
 332.34283;-19.35043;565.86021;,
 393.93443;-123.39558;657.45997;,
 317.83848;1.53374;-84.73673;;
 
 56;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;4,7,8,9;,
 3;10,11,7;,
 3;10,7,6;,
 3;12,13,6;,
 3;12,6,3;,
 3;14,6,5;,
 3;14,0,3;,
 3;14,3,6;,
 3;15,7,11;,
 3;15,16,8;,
 3;15,8,7;,
 3;17,18,3;,
 3;17,3,2;,
 3;19,12,3;,
 4;20,1,21,22;,
 4;23,24,25,26;,
 4;24,27,28,25;,
 4;29,22,21,30;,
 3;31,30,28;,
 4;32,33,34,35;,
 4;36,37,38,39;,
 4;40,41,42,43;,
 4;40,43,44,45;,
 4;46,47,48,49;,
 4;50,51,52,53;,
 4;45,44,54,55;,
 4;56,57,47,46;,
 3;58,59,60;,
 4;58,60,61,62;,
 3;63,64,65;,
 3;63,65,35;,
 4;63,35,34,61;,
 3;66,67,68;,
 4;66,68,69,70;,
 4;71,72,73,74;,
 4;71,74,20,22;,
 4;75,76,77,78;,
 4;75,78,24,23;,
 4;78,77,79,80;,
 4;78,80,27,24;,
 4;81,82,79,72;,
 3;83,37,36;,
 4;83,36,84,85;,
 3;66,70,86;,
 4;66,86,85,67;,
 3;83,85,86;,
 4;83,86,70,37;,
 3;87,59,64;,
 3;88,35,65;,
 3;89,84,36;,
 3;90,52,57;,
 3;91,92,51;,
 3;93,48,42;,
 4;82,81,22,29;;
 
 MeshMaterialList {
  1;
  56;
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
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\MODEL\\Objects\\Texture\\snow.jpg";
   }
  }
 }
 MeshNormals {
  53;
  -0.027638;0.983102;-0.180957;,
  -0.652836;0.724887;-0.219873;,
  0.572683;0.795676;-0.197315;,
  0.720171;0.656874;-0.223319;,
  0.729557;0.644552;0.228688;,
  -0.689673;0.684048;0.237548;,
  0.007306;0.995283;-0.096734;,
  -0.815985;0.577887;-0.014646;,
  0.642142;0.766542;-0.008223;,
  0.848011;0.526058;-0.064342;,
  0.241897;0.952738;-0.183786;,
  0.267527;0.797220;-0.541174;,
  0.423382;0.875295;0.233679;,
  0.432276;0.752701;0.496567;,
  0.255762;0.964036;-0.072247;,
  0.849153;0.527032;0.034294;,
  0.060846;0.998091;-0.010624;,
  -0.831765;0.555114;0.004010;,
  0.421557;0.906772;-0.007325;,
  -0.023054;0.999264;0.030668;,
  -0.794567;0.607168;-0.003227;,
  0.604210;0.796152;0.032743;,
  0.851494;0.522292;0.046563;,
  0.250482;0.967830;0.023736;,
  0.654184;0.756150;0.016784;,
  0.861037;0.508421;0.011124;,
  0.843293;0.535621;0.044350;,
  0.066483;0.984751;-0.160765;,
  0.585677;0.810367;0.016990;,
  0.846010;0.533056;-0.010896;,
  0.656240;0.741518;0.139643;,
  0.855859;0.516070;-0.034322;,
  0.763446;0.643681;0.053150;,
  0.832862;0.537450;0.132243;,
  -0.270403;0.950530;-0.152886;,
  -0.233715;0.812505;-0.534054;,
  -0.345748;0.894573;0.283190;,
  -0.244399;0.791126;0.560704;,
  -0.255989;0.960805;-0.106408;,
  -0.394192;0.918494;0.031330;,
  -0.251852;0.967697;0.011524;,
  0.076275;0.937643;0.339129;,
  -0.524418;0.828828;-0.195011;,
  -0.586513;0.772323;0.243965;,
  -0.669571;0.741659;-0.040209;,
  0.230490;0.856289;-0.462216;,
  0.530690;0.772264;0.349252;,
  0.302578;0.824857;0.477554;,
  -0.605646;0.795732;-0.001725;,
  -0.149259;0.866688;-0.475998;,
  -0.333709;0.832800;0.441681;,
  -0.101684;0.839725;0.533407;,
  -0.713976;0.699928;0.018427;;
  56;
  4;16,41,12,18;,
  4;19,6,14,23;,
  4;19,23,10,0;,
  3;8,21,23;,
  3;8,23,14;,
  3;24,8,14;,
  3;24,14,18;,
  3;27,14,6;,
  3;27,16,18;,
  3;27,18,14;,
  3;28,23,21;,
  3;28,2,10;,
  3;28,10,23;,
  3;30,32,18;,
  3;30,18,12;,
  3;32,24,18;,
  4;36,41,16,39;,
  4;34,40,19,0;,
  4;40,38,6,19;,
  4;38,39,16,27;,
  3;38,27,6;,
  4;2,3,11,45;,
  4;46,13,4,30;,
  4;21,8,25,22;,
  4;21,22,29,28;,
  4;24,26,9,8;,
  4;30,31,15,32;,
  4;28,29,3,2;,
  4;32,33,26,24;,
  3;42,34,49;,
  4;42,49,35,1;,
  3;49,0,10;,
  3;49,10,45;,
  4;49,45,11,35;,
  3;50,36,43;,
  4;50,43,5,37;,
  4;52,17,5,43;,
  4;52,43,36,39;,
  4;42,1,20,48;,
  4;42,48,40,34;,
  4;48,20,7,44;,
  4;48,44,38,40;,
  4;52,44,7,17;,
  3;47,13,46;,
  4;47,46,12,41;,
  3;50,37,51;,
  4;50,51,41,36;,
  3;47,41,51;,
  4;47,51,37,13;,
  3;49,34,0;,
  3;2,45,10;,
  3;30,12,46;,
  3;32,15,33;,
  3;30,4,31;,
  3;8,9,25;,
  4;44,52,39,38;;
 }
 MeshTextureCoords {
  94;
  0.000000;0.213890;,
  0.000000;0.000000;,
  0.429250;0.000000;,
  0.429250;0.213890;,
  0.000000;0.790220;,
  0.000000;0.529310;,
  0.429250;0.529310;,
  0.429250;0.790220;,
  0.429250;1.000000;,
  0.000000;1.000000;,
  1.000000;0.659770;,
  1.000000;0.790220;,
  1.000000;0.371600;,
  1.000000;0.529310;,
  0.000000;0.371600;,
  1.000000;0.895110;,
  1.000000;1.000000;,
  1.000000;0.106950;,
  1.000000;0.213890;,
  1.000000;0.292750;,
  0.000000;0.385430;,
  0.213890;0.000000;,
  0.213890;0.385430;,
  1.000000;0.385430;,
  0.790220;0.385430;,
  0.790220;0.000000;,
  1.000000;0.000000;,
  0.529310;0.385430;,
  0.529310;0.000000;,
  0.310810;0.385430;,
  0.371600;0.000000;,
  0.480850;0.385430;,
  1.000000;0.629811;,
  1.000000;1.000000;,
  0.429250;1.000000;,
  0.429250;0.909150;,
  0.570750;0.886527;,
  0.570750;1.000000;,
  0.000000;1.000000;,
  0.000000;0.629810;,
  0.209780;0.629811;,
  0.340230;0.629811;,
  0.340230;1.000000;,
  0.209780;1.000000;,
  0.104890;1.000000;,
  0.104890;0.629811;,
  0.628400;0.629771;,
  0.628400;1.000000;,
  0.470690;1.000000;,
  0.470690;0.629810;,
  0.893050;0.629771;,
  0.893050;1.000000;,
  0.786110;1.000000;,
  0.786110;0.629730;,
  0.000000;1.000000;,
  0.000000;0.629811;,
  0.707250;0.629751;,
  0.707250;1.000000;,
  0.000000;0.940717;,
  0.000000;0.385430;,
  0.105343;0.940716;,
  0.116590;1.000000;,
  0.000000;1.000000;,
  0.144995;0.909150;,
  0.000000;0.000000;,
  0.429250;0.000000;,
  0.894786;0.940035;,
  1.000000;0.385430;,
  1.000000;0.940034;,
  1.000000;1.000000;,
  0.883410;1.000000;,
  0.213890;0.956483;,
  0.213890;1.000000;,
  0.000000;1.000000;,
  0.000000;0.940034;,
  1.000000;0.940717;,
  1.000000;1.000000;,
  0.790220;1.000000;,
  0.790220;0.886588;,
  0.529310;1.000000;,
  0.529310;0.949319;,
  0.226898;0.949309;,
  0.516304;0.949319;,
  0.585034;0.946273;,
  0.570750;0.000000;,
  0.785380;0.192720;,
  0.876886;0.946273;,
  0.125169;0.924933;,
  1.000000;0.314905;,
  0.000000;0.314905;,
  0.746680;0.629740;,
  0.946525;0.629790;,
  1.000000;1.000000;,
  0.405460;0.629811;;
 }
}
