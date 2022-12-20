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
 14;
 -7.15395;15.35169;0.72193;,
 -13.63779;9.43199;8.24760;,
 -9.22219;20.83874;12.56052;,
 -2.07766;23.26617;8.38700;,
 7.39860;9.52777;-1.50311;,
 4.07691;19.82752;17.07028;,
 9.66128;12.99937;14.03033;,
 -3.86100;20.98135;16.41593;,
 -3.03719;0.92667;-5.83535;,
 -12.99247;4.91454;-0.66407;,
 -2.06442;9.51621;17.62225;,
 11.68476;2.03919;9.08753;,
 -4.04693;-3.00142;13.40812;,
 6.48020;-0.89351;-1.95353;;
 
 18;
 4;0,1,2,3;,
 3;3,4,0;,
 4;3,5,6,4;,
 3;5,3,7;,
 3;7,3,2;,
 3;8,9,0;,
 3;9,1,0;,
 3;6,10,11;,
 3;5,10,6;,
 3;7,10,5;,
 4;10,7,2,12;,
 3;1,12,2;,
 3;12,1,9;,
 3;10,12,11;,
 4;13,12,9,8;,
 3;12,13,11;,
 4;0,4,13,8;,
 4;4,6,11,13;;
 
 MeshMaterialList {
  1;
  18;
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
   0.185098;0.577255;0.800000;0.530000;;
   5.000000;
   0.670000;0.670000;0.670000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  24;
  0.583047;0.476699;-0.657886;,
  -0.345152;0.532284;-0.773010;,
  -0.065918;0.275818;-0.958947;,
  0.023901;-0.997980;-0.058857;,
  0.866513;0.406570;-0.289579;,
  0.391916;-0.607293;0.691084;,
  -0.749538;0.556751;-0.358079;,
  -0.483187;0.870206;-0.096290;,
  -0.291288;0.881871;-0.370750;,
  0.449607;0.892713;0.030286;,
  -0.038860;0.963326;0.265506;,
  -0.623388;0.435004;-0.649738;,
  0.073399;-0.175804;0.981685;,
  -0.723416;-0.250109;0.643518;,
  0.348279;-0.237262;0.906867;,
  0.134196;-0.026900;0.990590;,
  -0.376069;0.014350;0.926481;,
  -0.604175;-0.079870;0.792839;,
  -0.750197;-0.344417;0.564430;,
  -0.596424;-0.802657;0.004519;,
  0.388090;-0.737669;0.552477;,
  -0.282447;-0.936889;-0.206064;,
  0.664111;0.186064;-0.724111;,
  0.945158;0.102305;-0.310178;;
  18;
  4;1,6,7,8;,
  3;8,0,1;,
  4;9,9,4,0;,
  3;9,9,10;,
  3;10,8,7;,
  3;2,11,1;,
  3;11,6,1;,
  3;14,12,5;,
  3;15,12,14;,
  3;16,12,15;,
  4;12,16,17,13;,
  3;18,13,17;,
  3;13,18,19;,
  3;12,20,5;,
  4;3,21,19,21;,
  3;20,3,5;,
  4;1,0,22,2;,
  4;0,4,23,22;;
 }
 MeshTextureCoords {
  14;
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
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
