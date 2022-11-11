//=============================================================================
// ロードさせる処理 [Load.cpp]
// Author : 佐藤秀亮
//=============================================================================
//*****************************************************************************
// インクルードファイル
//***************************************************************************** 
#include "LoadEffect.h"
#include "PresetSetEffect.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define PRESETCALL_TEXT ("data/FILES/PresetCall.txt")

//=============================================================================
// 静的
//=============================================================================
int CLoadEffect::m_Total3d = 0;
int CLoadEffect::m_Total2d = 0;

int CLoadEffect::m_OrderTotal = 0;
int CLoadEffect::m_FullOrder = 0;

//CLoadEffect::CALL_PRESET CLoadEffect::m_CallPreset[MAX_PRESET] = {};
std::vector<CLoadEffect::CALL_PRESET> CLoadEffect::m_vCallPreset;

std::map<std::string, int> CLoadEffect::m_Name;

//=============================================================================
// コンストラクタ
//=============================================================================
CLoadEffect::CLoadEffect()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CLoadEffect::~CLoadEffect()
{

}

//=============================================================================
// エフェクト情報の読み込み
//=============================================================================
void CLoadEffect::EffectStateLoad(const char *aFileName)
{
	FILE *pFile;
	pFile = fopen(aFileName, "r");
	char aFile[256];

	//変数定義
#if 1
	m_Total3d = 0;
	m_Total2d = 0;

	bool bEffectState2D = false;
	bool bEffectState3D = false;

	int nPattern = 0;
	D3DXVECTOR2 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR2 Addmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	int Diffusion = 1;
	int Destroyvec = 0;
	float fSize = 0;
	float fAddSize = 0;
	float fSizeY = 0;
	float fAddSizeY = 0;
	float fRotate = 0;
	D3DCOLORVALUE col;
	D3DCOLORVALUE ChangeColor;
	int nLife = 0;
	int Density = 1;
	int bRandColR = 0;
	int bRandColG = 0;
	int bRandColB = 0;
	int nSynthetic = 0;
	int nTexture = 0;

	float move3d = 0.0f;
	float Addmove3d = 0.0f;
	float MaxSize = 100.0f;
	float ParticleSize = 0.0f;
	float ParticleAddSize = 0.0f;
	int Active = 0;
	D3DCOLORVALUE Secondcol;
	D3DCOLORVALUE SecondChangeColor;
	int SecondSynthetic = 0;
	int TrajectTop = 0;
	int TrajectCur = 0;
	D3DXVECTOR3 Move3D = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	int RandMove = 1;
	int Distance = 1;
	int ParticleTime = 1;
	float fActiveAddSize = 0.0f;
	int FieldTime = 0;
	int FieldCreate = 0;
	int CreatePreset = 0;
	int nSecondTime = 0;
	int nVtx = 0;
	int nType = 0;
	D3DXVECTOR2 TexMove = D3DXVECTOR2(0.0f, 0.0f);
	D3DXVECTOR2 TexNum = D3DXVECTOR2(1.0f, 1.0f);
	int nSecondType = 0;
	D3DXVECTOR2 TexSplit = D3DXVECTOR2(1.0f, 1.0f);
	int nAnimCont = -1;
	float fHigth = 30.0f;
	int AnimPatternType = 0;
	D3DXVECTOR3 ControlBezier = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DCOLORVALUE Therdcol;
	D3DCOLORVALUE TherdChangeColor;
	int SecondTex = 0;
#endif

	if (pFile != NULL)
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]); //fscanfを繰り返してファイルを読み取っていく

			if (bEffectState2D == true)
			{
				if (strcmp(&aFile[0], "PATTERN") == 0)	//動きのパターン
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nPattern);
				}
				if (strcmp(&aFile[0], "ROTATE") == 0)	//回転
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &fRotate);
				}
				if (strcmp(&aFile[0], "MOVE") == 0)	//移動量
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f", &move.x, &move.y);
				}
				if (strcmp(&aFile[0], "ADDMOVE") == 0)	//動き加算
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f", &Addmove.x, &Addmove.y);
				}
				if (strcmp(&aFile[0], "DIFFUSION") == 0)	//拡散率
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &Diffusion);
				}
				if (strcmp(&aFile[0], "DESTROYVEC") == 0)	//消えるベクトル
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &Destroyvec);
				}
				if (strcmp(&aFile[0], "SIZE") == 0)	//大きさ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &fSize);
				}
				if (strcmp(&aFile[0], "ADDSIZE") == 0)	//大きさ加算
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &fAddSize);
				}
				if (strcmp(&aFile[0], "COLOR") == 0)	//カラー
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f %f", &col.r, &col.g, &col.b, &col.a);
				}
				if (strcmp(&aFile[0], "CHANGECOLOR") == 0)	//カラー変動
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f %f", &ChangeColor.r, &ChangeColor.g, &ChangeColor.b, &ChangeColor.a);
				}
				if (strcmp(&aFile[0], "LIFE") == 0)	//寿命
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nLife);
				}
				if (strcmp(&aFile[0], "DENSITY") == 0)	//密度
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &Density);
				}
				if (strcmp(&aFile[0], "COLORRANDR") == 0)	//カラーランダム赤
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &bRandColR);
				}
				if (strcmp(&aFile[0], "COLORRANDG") == 0)	//カラーランダム緑
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &bRandColG);
				}
				if (strcmp(&aFile[0], "COLORRANDB") == 0)	//カラーランダム青
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &bRandColB);
				}
				if (strcmp(&aFile[0], "SYNTHETIC") == 0)		//合成
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nSynthetic);
				}
				if (strcmp(&aFile[0], "TEXTURE") == 0)		//テクスチャ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nTexture);
				}
				if (strcmp(&aFile[0], "DISTANCE") == 0)		//発生距離
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &Distance);
				}
				if (strcmp(&aFile[0], "TYPE") == 0)	//タイプ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nType);
				}
				if (strcmp(&aFile[0], "HIGTH") == 0)	//高さ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &fHigth);
				}
				if (strcmp(&aFile[0], "PARTICLESIZE") == 0)	//最大の大きさ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &ParticleSize);
				}
				if (strcmp(&aFile[0], "SECONDCOLOR") == 0)	//２番カラー
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f %f", &Secondcol.r, &Secondcol.g, &Secondcol.b, &Secondcol.a);
				}
				if (strcmp(&aFile[0], "SECONDADDCOLOR") == 0)	//２番カラー変動
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f %f", &SecondChangeColor.r, &SecondChangeColor.g, &SecondChangeColor.b, &SecondChangeColor.a);
				}
				if (strcmp(&aFile[0], "TEXMOVE") == 0)	//テクスチャ移動量
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f", &TexMove.x, &TexMove.y);
				}
				if (strcmp(&aFile[0], "TEXNUM") == 0)	//テクスチャ移動量
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f", &TexNum.x, &TexNum.y);
				}
				if (strcmp(&aFile[0], "TEXSPLIT") == 0)	//テクスチャ移動量
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f", &TexSplit.x, &TexSplit.y);
				}
				if (strcmp(&aFile[0], "TEXANIMCOUNT") == 0)	//頂点数
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nAnimCont);
				}
				if (strcmp(&aFile[0], "HIGTH") == 0)	//高さ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &fHigth);
				}
				if (strcmp(&aFile[0], "ANIMPATTERNTYPE") == 0)	//アニメーションパターンタイプ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &AnimPatternType);
				}

			}

			if (bEffectState3D == true)
			{
				if (strcmp(&aFile[0], "PATTERN") == 0)	//動きのパターン
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nPattern);
				}
				if (strcmp(&aFile[0], "ROTATE") == 0)	//回転
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &fRotate);
				}
				if (strcmp(&aFile[0], "MOVE") == 0)	//移動量
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &move3d);
				}
				if (strcmp(&aFile[0], "ADDMOVE") == 0)	//動き加算
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &Addmove3d);
				}
				if (strcmp(&aFile[0], "DIFFUSION") == 0)	//拡散率
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &Diffusion);
				}
				if (strcmp(&aFile[0], "SIZE") == 0)	//大きさ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &fSize);
				}
				if (strcmp(&aFile[0], "ADDSIZE") == 0)	//大きさ加算
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &fAddSize);
				}
				if (strcmp(&aFile[0], "SIZEY") == 0)	//大きさ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &fSizeY);
				}
				if (strcmp(&aFile[0], "ADDSIZEY") == 0)	//大きさ加算
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &fAddSizeY);
				}

				if (strcmp(&aFile[0], "MAXSIZE") == 0)	//最大の大きさ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &MaxSize);
				}
				if (strcmp(&aFile[0], "PARTICLESIZE") == 0)	//最大の大きさ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &ParticleSize);
				}
				if (strcmp(&aFile[0], "PARTICLEADDSIZE") == 0)	//最大の大きさ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &ParticleAddSize);
				}
				if (strcmp(&aFile[0], "ACTIVE") == 0)	//稼働時間
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &Active);
				}
				if (strcmp(&aFile[0], "COLOR") == 0)	//カラー
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f %f", &col.r, &col.g, &col.b, &col.a);
				}
				if (strcmp(&aFile[0], "CHANGECOLOR") == 0)	//カラー変動
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f %f", &ChangeColor.r, &ChangeColor.g, &ChangeColor.b, &ChangeColor.a);
				}
				if (strcmp(&aFile[0], "SECONDCOLOR") == 0)	//２番カラー
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f %f", &Secondcol.r, &Secondcol.g, &Secondcol.b, &Secondcol.a);
				}
				if (strcmp(&aFile[0], "SECONDADDCOLOR") == 0)	//２番カラー変動
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f %f", &SecondChangeColor.r, &SecondChangeColor.g, &SecondChangeColor.b, &SecondChangeColor.a);
				}
				if (strcmp(&aFile[0], "SECONDSYNTHETIC") == 0)		//合成
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &SecondSynthetic);
				}
				if (strcmp(&aFile[0], "LIFE") == 0)	//寿命
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nLife);
				}
				if (strcmp(&aFile[0], "DENSITY") == 0)	//密度
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &Density);
				}
				if (strcmp(&aFile[0], "TRAJECTTOP") == 0)	//モデル１
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &TrajectTop);
				}
				if (strcmp(&aFile[0], "TRAJECTCUR") == 0)	//モデル２
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &TrajectTop);
				}
				if (strcmp(&aFile[0], "TRAJECTCUR") == 0)	//モデル２
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &TrajectTop);
				}
				if (strcmp(&aFile[0], "MOVE3D") == 0)	//３ｄ移動量
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &Move3D.x, &Move3D.y, &Move3D.z);
				}
				if (strcmp(&aFile[0], "RANDMOVE") == 0)	//ランダム移動
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &RandMove);
				}
				if (strcmp(&aFile[0], "COLORRANDR") == 0)	//カラーランダム赤
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &bRandColR);
				}
				if (strcmp(&aFile[0], "COLORRANDG") == 0)	//カラーランダム緑
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &bRandColG);
				}
				if (strcmp(&aFile[0], "COLORRANDB") == 0)	//カラーランダム青
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &bRandColB);
				}
				if (strcmp(&aFile[0], "SYNTHETIC") == 0)		//合成
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nSynthetic);
				}
				if (strcmp(&aFile[0], "TEXTURE") == 0)		//テクスチャ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nTexture);
				}
				if (strcmp(&aFile[0], "DISTANCE") == 0)		//発生距離
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &Distance);
				}
				if (strcmp(&aFile[0], "PARTICLETIME") == 0)		//発生間隔
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &ParticleTime);
				}
				if (strcmp(&aFile[0], "ACTIVEADDSIZE") == 0)	//大きさ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &fActiveAddSize);
				}
				if (strcmp(&aFile[0], "FIELDTIME") == 0)		//発生距離
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &FieldTime);
				}
				if (strcmp(&aFile[0], "FIELDCREATE") == 0)	//カラーランダム緑
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &FieldCreate);
				}
				if (strcmp(&aFile[0], "CREATEPRESET") == 0)	//大きさ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &CreatePreset);
				}
				if (strcmp(&aFile[0], "SECONDTIME") == 0)	//2番目の時間
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nSecondTime);
				}
				if (strcmp(&aFile[0], "VTX") == 0)	//頂点数
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nVtx);
				}
				if (strcmp(&aFile[0], "TYPE") == 0)	//頂点数
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nType);
				}
				if (strcmp(&aFile[0], "TEXMOVE") == 0)	//テクスチャ移動量
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f", &TexMove.x, &TexMove.y);
				}
				if (strcmp(&aFile[0], "TEXNUM") == 0)	//テクスチャ移動量
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f", &TexNum.x, &TexNum.y);
				}
				if (strcmp(&aFile[0], "SECONDTYPE") == 0)	//頂点数
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nSecondType);
				}
				if (strcmp(&aFile[0], "TEXSPLIT") == 0)	//テクスチャ移動量
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f", &TexSplit.x, &TexSplit.y);
				}
				if (strcmp(&aFile[0], "TEXANIMCOUNT") == 0)	//頂点数
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nAnimCont);
				}
				if (strcmp(&aFile[0], "HIGTH") == 0)	//高さ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &fHigth);
				}
				if (strcmp(&aFile[0], "ANIMPATTERNTYPE") == 0)	//アニメーションパターンタイプ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &AnimPatternType);
				}
				if (strcmp(&aFile[0], "THERDCOLOR") == 0)	//パーティクルカラー
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f %f", &Therdcol.r, &Therdcol.g, &Therdcol.b, &Therdcol.a);
				}
				if (strcmp(&aFile[0], "THERDADDCOLOR") == 0)	//パーティクルカラー
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f %f", &TherdChangeColor.r, &TherdChangeColor.g, &TherdChangeColor.b, &TherdChangeColor.a);
				}
				if (strcmp(&aFile[0], "SECONDTEX") == 0)	//パーティクルカラー
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &SecondTex);
				}
				if (strcmp(&aFile[0], "CONTROLBEZIER") == 0)	//パーティクルカラー
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &ControlBezier.x, &ControlBezier.y, &ControlBezier.z);
				}

			}
			//エフェクト情報セット
			if (strcmp(&aFile[0], "EFFECTSTATE2D") == 0)
			{
				bEffectState2D = true;
			}
			if (strcmp(&aFile[0], "END_EFFECTSTATE2D") == 0)
			{
				bEffectState2D = false;
				//CPresetEffect::SetEffectState2D(nPattern, fRotate, move, Addmove, Diffusion, Destroyvec, fSize, fAddSize, col, ChangeColor, nLife, Density,
				//	(bool)bRandColR, (bool)bRandColG, (bool)bRandColB, nSynthetic, nTexture, (float)Distance,
				//	TexMove, TexNum, AnimPatternType, TexSplit,
				//	nAnimCont, nType, fHigth,ParticleSize, Secondcol, SecondChangeColor);

				m_Total2d++;

			}

			//3Dエフェクト情報セット
			if (strcmp(&aFile[0], "EFFECTSTATE3D") == 0)
			{
				bEffectState3D = true;
			}
			if (strcmp(&aFile[0], "END_EFFECTSTATE3D") == 0)
			{
				bEffectState3D = false;
				CPresetEffect::SetEffectState3D
				(
					nPattern,			// エフェクトパターン
					fRotate,			// 回転量
					move3d,				// 移動量
					Addmove3d,			// 移動加算量
					Diffusion,			// 拡散率
					fSize,				// 大きさＸ
					fAddSize,			// 大きさ加算量Ｘ
					fSizeY,			    // 大きさＹ
					fAddSizeY,		    // 大きさ加算量Ｙ
					MaxSize, 		    // 最大大きさ
					ParticleSize,	    // パーティクルの大きさ
					ParticleAddSize,    // パーティクルの大きさ加算量
					Active,			    // 移動時間
					col,			    // カラー
					ChangeColor,	    // カラー変更量
					Secondcol, 		    // ２番目のカラー
					SecondChangeColor,  // ２番目のカラー変更量
					SecondSynthetic,    // ２番目のエフェクト描画合成方法
					nLife, 			    // エフェクト寿命
					Density, 		    // 密度(一度に出すエフェクト量)
					TrajectTop,		    // モデル1
					TrajectCur,		    // モデル2
					Move3D, 		    // ３Ｄ移動量
					RandMove,		    // 移動ランダム
					(bool)bRandColR,    // ランダムカラーＲ
					(bool)bRandColG,    // ランダムカラーＧ
					(bool)bRandColB,    // ランダムカラーＢ
					nSynthetic, 	    // エフェクト合成方法
					nTexture, 		    // テクスチャ番号
					Distance, 		    // 出現位置の範囲
					ParticleTime, 	    // パーティクル発生間隔
					fActiveAddSize,	    // アクティブ時の大きさ加算量
					FieldTime, 		    // フィールドの寿命
					(bool)FieldCreate,  // フィールド生成判定
					CreatePreset,	    // プリセット生成判定
					nSecondTime,	    // フィールドが消えるまでの時間
					nVtx, 			    // 頂点数(球体エフェクトに使う)
					nType, 			    // エフェクトタイプ
					TexMove,		    // テクスチャ移動量ＵＶ
					TexNum, 		    // テクスチャの枚数ＵＶ
					nSecondType, 	    // 移動のパターン決め
					TexSplit,		    // テクスチャ分割数
					nAnimCont, 		    // アニメーションカウント
					fHigth, 		    // 高さ
					AnimPatternType,    // アニメーションのパターンタイプ
					ControlBezier,	    // ？
					Therdcol,		    // 3番目カラー
					TherdChangeColor,   // 3番目カラー変更料
					SecondTex		    // 2番目テクスチャ
				);

				// 変数を初期化
				nPattern			= 0;
				fRotate				= 0.0f;
				move3d				= 0.0f;
				Addmove3d			= 0.0f;
				Diffusion			= 0;
				fSize				= 0.0f;
				fAddSize			= 0.0f;
				fSizeY				= 0.0f;
				fAddSizeY			= 0.0f;
				MaxSize				= 0.0f;
				ParticleSize		= 0.0f;
				ParticleAddSize		= 0.0f;
				Active				= 0;
				col					= {};
				ChangeColor			= {};
				Secondcol			= {};
				SecondChangeColor	= {};
				SecondSynthetic		= 0;
				nLife				= 0;
				Density				= 0;
				TrajectTop			= 0;
				TrajectCur			= 0;
				Move3D				= {};
				RandMove			= 0;
				bRandColR			= 0;
				bRandColG			= 0;
				bRandColB			= 0;
				nSynthetic			= 0;
				nTexture			= 0;
				Distance			= 0;
				ParticleTime		= 0;
				fActiveAddSize		= 0.0f;
				FieldTime			= 0;
				FieldCreate			= 0;
				CreatePreset		= 0;
				nSecondTime			= 0;
				nVtx				= 0;
				nType				= 0;
				TexMove				= {};
				TexNum				= {};
				nSecondType			= 0;
				TexSplit			= {};
				nAnimCont			= 0;
				fHigth				= 0.0f;
				AnimPatternType		= 0;
				ControlBezier		= {};
				Therdcol			= {};
				TherdChangeColor	= {};
				SecondTex			= 0;

				m_Total3d++;
			}

			//終わり
			if (strcmp(&aFile[0], "END_SCRIPT") == 0)
			{
				break;
			}
		}
		fclose(pFile);
	}
	CPresetEffect::ResetPattern();
	PresetCallLoad(PRESETCALL_TEXT);
}

//=============================================================================
// プリセット呼び出しテキストの読み込み Author:村元翼
//=============================================================================
void CLoadEffect::PresetCallLoad(const char *aFileName)
{
	FILE *pFile;
	pFile = fopen(aFileName, "r");

	char aData[128];

	int nDelay = 0;
	int nPresetNum = 0;
	int nType = 0;
	int nTypeArray = 0;
	int nArray = 0;
	char aName[128];
	D3DXVECTOR3 offset = {};

	//--------------------------------------------------
	// メモリ解放
	//--------------------------------------------------
	if(!m_vCallPreset.empty())
	{
		for (int nCnt = 0; nCnt < m_vCallPreset.size(); nCnt++)
		{
			if (!m_vCallPreset[nCnt].m_nDelay.empty())
			{
				m_vCallPreset[nCnt].m_nDelay.clear();				// サイズを0にする
				m_vCallPreset[nCnt].m_nDelay.shrink_to_fit();		// メモリをサイズ分まで縮める(メモリ開放)
			}

			if (!m_vCallPreset[nCnt].m_nPresetNum.empty())
			{
				m_vCallPreset[nCnt].m_nPresetNum.clear();
				m_vCallPreset[nCnt].m_nPresetNum.shrink_to_fit();
			}

			if (m_vCallPreset[nCnt].m_CallMax != NULL)
			{
				m_vCallPreset[nCnt].m_CallMax = NULL;
			}

			if (!m_vCallPreset[nCnt].m_nType.empty())
			{
				for (int nCnt2 = 0; nCnt2 < m_vCallPreset[nCnt].m_nType.size(); nCnt2++)
				{
					if (!m_vCallPreset[nCnt].m_nType[nCnt2].empty())
					{
						m_vCallPreset[nCnt].m_nType[nCnt2].clear();
						m_vCallPreset[nCnt].m_nType[nCnt2].shrink_to_fit();
					}
				}

				m_vCallPreset[nCnt].m_nType.clear();
				m_vCallPreset[nCnt].m_nType.shrink_to_fit();
			}

			if (!m_vCallPreset[nCnt].m_Offset.empty())
			{
				// mapはclear関数のみでメモリが解放される
				m_vCallPreset[nCnt].m_Offset.clear();
			}
		}

		m_vCallPreset.clear();
		m_vCallPreset.shrink_to_fit();	// 配列を空にする
	}

	if (!m_Name.empty())
	{
		m_Name.clear();
	}

	//--------------------------------------------------
	// ファイルの読み込み
	//--------------------------------------------------
	if (pFile)
	{
		while (fgets(aData, 128, pFile))					// 一行ずつ読み込む
		{
			fscanf(pFile, "%s", aData);						// 一単語保存
															// パターン生成開始
			if (strncmp(aData, "PRESETCALL", 11) == 0)
			{
				m_vCallPreset.emplace_back();						// 配列を追加

				while (fgets(aData, 128, pFile))					// 一行ずつ読み込む
				{
					fscanf(pFile, "%s", aData);						// 一単語保存

					if (strncmp(aData, "NAME", 5) == 0)
					{
						fscanf(pFile, "%*s%s", aName);			// 
						m_Name[aName] = nArray;					// 名前と番号を結びつける
					}

					if (strncmp(aData, "CALLSET", 8) == 0)
					{
						while (fgets(aData, 128, pFile))					// 一行ずつ読み込む
						{
							fscanf(pFile, "%s", aData);						// 一単語保存

							// 呼び出してから何フレーム後に生成するか
							if (strncmp(aData, "DELEY", 6) == 0)
							{
								fscanf(pFile, "%*s%d", &nDelay);
								m_vCallPreset[nArray].m_nDelay.emplace_back(nDelay);
							}

							// いくつエフェクトを呼び出すか
							else if (strncmp(aData, "PRESETNUM", 6) == 0)
							{
								fscanf(pFile, "%*s%d", &nPresetNum);
								m_vCallPreset[nArray].m_nPresetNum.emplace_back(nPresetNum);
							}

							// エフェクトのタイプ
							else if (strncmp(aData, "TYPE", 6) == 0)
							{
								fscanf(pFile, "%*s");

								// 空のデータを追加する
								m_vCallPreset[nArray].m_nType.emplace_back();

								// 呼び出す数だけループする
								for (int nCnt = 0; nCnt < nPresetNum; nCnt++)
								{
									fscanf(pFile, "%d", &nType);
									m_vCallPreset[nArray].m_nType[nTypeArray].emplace_back(nType);
								}
							}

							// ずらす座標
							else if (strncmp(aData, "OFFSET", 4) == 0)
							{
								fscanf(pFile, "%*s%f%f%f", &offset.x, &offset.y, &offset.z);
								m_vCallPreset[nArray].m_Offset[m_vCallPreset[nArray].m_CallMax] = offset;
							}

							if (strncmp(aData, "END_CALLSET", 12) == 0)
							{
								nTypeArray++;
								m_vCallPreset[nArray].m_CallMax++;	// 呼び出し最大数カウント
								break;
							}
						}
					}

					if (strncmp(aData, "END_PRESETCALL", 8) == 0)
					{
						nArray++;		// 配列を進める
						nTypeArray = 0;	// エフェクトタイプの配列を初期化
						break;
					}
				}
			}

			// 読み込み終了
			if (strncmp(aData, "END_SCRIPT", 11) == 0)
			{
				break;
			}
		}
	}

	else
	{
		printf("読み込めませんでした。");
	}

	// ファイルを閉じる
	fclose(pFile);
}

//封印
#if 0
//=============================================================================
// エフェクトオーダー
//=============================================================================
void CLoadEffect::EffectOrder(const char *aFileName)	//エフェクトオーダー
{
	FILE *pFile;
	pFile = fopen(aFileName, "r");
	char aFile[256];

	m_OrderTotal = 0;
	m_FullOrder = 0;

	int nDeley = {};
	int nPatternNum = {};
	int nOrder[MAX_ORDER_3D] = {};

	for (int i2 = 0; i2 < MAX_ORDER_3D; i2++)
	{
		nOrder[i2] = -1;
		nDeley = -1;
		nPatternNum = -1;
	}

	bool bLodeOrder = false;
	bool bLodeFull = false;

	if (pFile != NULL)
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]); //fscanfを繰り返してファイルを読み取っていく
			if (bLodeFull == true)
			{
				if (bLodeOrder == true)
				{
					if (strcmp(&aFile[0], "DELEY") == 0)		//発生ディレイ
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &nDeley);
					}
					if (strcmp(&aFile[0], "PRESETNUM") == 0)		//発生プリセット
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &nPatternNum);
					}
					if (strcmp(&aFile[0], "ORDER") == 0)		//発生プリセット
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &nOrder[0], &nOrder[1], &nOrder[2], &nOrder[3], &nOrder[4], &nOrder[5], &nOrder[6], &nOrder[7],
							&nOrder[8], &nOrder[9], &nOrder[10], &nOrder[11], &nOrder[12], &nOrder[13], &nOrder[14], nOrder[15]);
					}
				}
				//オーダー情報
				if (strcmp(&aFile[0], "ORDERSET") == 0)
				{
					bLodeOrder = true;
				}
				if (strcmp(&aFile[0], "END_ORDERSET") == 0)
				{
					bLodeOrder = false;
					CPresetEffect::CreateOrderMenu(nDeley, nPatternNum, nOrder);

					m_OrderTotal++;
				}
			}
			//オーダー情報
			if (strcmp(&aFile[0], "ORDERMENU") == 0)
			{
				bLodeFull = true;
			}

			if (strcmp(&aFile[0], "END_ORDERMENU") == 0)
			{
				bLodeFull = false;


				for (int i = 0; i < 8; i++)
				{
					nOrder[i] = -1;
				}

				m_FullOrder++;
			}


			//終わり
			if (strcmp(&aFile[0], "END_SCRIPT") == 0)
			{
				break;
			}
		}
	}
	fclose(pFile);
	CPresetEffect::ResetOrder();
}

#endif