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
 22;
 0.00000;-0.07586;-0.00000;,
 -0.93210;-1.77108;-1.30963;,
 -0.93210;0.55027;-1.97469;,
 0.00000;-0.07586;-0.00000;,
 -0.93210;-1.74973;1.34148;,
 0.00000;-0.07586;-0.00000;,
 -0.93210;0.58485;1.90813;,
 0.00000;-0.07586;-0.00000;,
 -0.93210;1.77107;-0.01968;,
 0.00000;-0.07586;-0.00000;,
 -0.93210;0.55027;-1.97469;,
 -4.31315;-2.04669;-1.50826;,
 -4.31315;0.63592;-2.27682;,
 -4.31315;-2.02202;1.55542;,
 -4.31315;0.67587;2.21026;,
 -4.31315;2.04669;-0.01756;,
 -4.31315;0.63592;-2.27682;,
 -5.96700;-0.08815;0.00000;,
 -5.96700;-0.08815;0.00000;,
 -5.96700;-0.08815;0.00000;,
 -5.96700;-0.08815;0.00000;,
 -5.96700;-0.08815;0.00000;;
 
 15;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 4;2,1,11,12;,
 4;1,4,13,11;,
 4;4,6,14,13;,
 4;6,8,15,14;,
 4;8,10,16,15;,
 3;12,11,17;,
 3;11,13,18;,
 3;13,14,19;,
 3;14,15,20;,
 3;15,16,21;;
 
 MeshMaterialList {
  12;
  15;
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
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
   0.112800;0.442400;0.496000;1.000000;;
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
  Material {
   0.800000;0.445600;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.768800;0.091200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.740000;0.520800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.483200;0.272800;0.106400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  19;
  0.999482;0.032021;0.003115;,
  0.911376;0.157438;-0.380271;,
  0.916919;-0.321335;-0.236652;,
  0.917151;-0.312897;0.246837;,
  0.907426;0.168786;0.384824;,
  0.892754;0.450545;-0.000543;,
  -0.388710;-0.253758;-0.885726;,
  -0.382775;-0.923812;0.007439;,
  -0.385512;-0.217641;0.896668;,
  -0.564168;0.798938;0.208355;,
  -0.831092;-0.447070;-0.330778;,
  0.078682;-0.274563;-0.958345;,
  0.080776;-0.996700;0.008026;,
  0.080228;-0.235113;0.968651;,
  0.069588;0.849618;0.522787;,
  -0.371166;0.790844;0.486622;,
  0.068653;0.846209;-0.528409;,
  -0.373014;0.786992;-0.491430;,
  -0.886301;0.392388;0.245973;;
  15;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,1,5;,
  4;11,11,6,6;,
  4;12,12,7,7;,
  4;13,13,8,8;,
  4;14,14,9,15;,
  4;16,16,17,16;,
  3;6,6,10;,
  3;7,7,10;,
  3;8,8,18;,
  3;15,9,18;,
  3;9,17,18;;
 }
 MeshTextureCoords {
  22;
  0.100000;0.000000;,
  0.200000;0.333330;,
  0.000000;0.333330;,
  0.300000;0.000000;,
  0.400000;0.333330;,
  0.500000;0.000000;,
  0.600000;0.333330;,
  0.700000;0.000000;,
  0.800000;0.333330;,
  0.900000;0.000000;,
  1.000000;0.333330;,
  0.200000;0.666670;,
  0.000000;0.666670;,
  0.400000;0.666670;,
  0.600000;0.666670;,
  0.800000;0.666670;,
  1.000000;0.666670;,
  0.100000;1.000000;,
  0.300000;1.000000;,
  0.500000;1.000000;,
  0.700000;1.000000;,
  0.900000;1.000000;;
 }
}
