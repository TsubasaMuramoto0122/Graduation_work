//=============================================================================
//
// 読み込み処理 [load.h]
// Author : 三上航世
//
//=============================================================================
#include "load.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "light.h"
#include "fade.h"
#include "camera.h"
#include "scene.h"
//#include "wall.h"
#include "player.h"
#include "sky.h"
#include "sound.h"
#include "object.h"
#include "bomb.h"
#include "plane.h"
#include "mesh_field.h"
#include "mesh_wall.h"
#include "battery.h"
#include "entry.h"

CLoad::CLoad()
{

}

CLoad::~CLoad(void)
{

}

void CLoad::StageLoad(const char *aFileName, CPlayer *pPlayer[4], int *pTime, int *pSnowTime)
{
	FILE *pFile;
	pFile = fopen(aFileName, "r");
	char aFile[256];
	int nNumModel;
	int nCntModel = 0;
	bool bField = false;
	bool bWall = false;
	bool bModel = false;
	bool bLight = false;
	bool bPlayer = false;
	bool bPlayerSet = false;
	bool bBattery = false;
	bool bTime = false;
	int nTime = 0;
	int nStartTime = 0;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	int nTex;
	int nDraw;
	D3DXVECTOR3 size;
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	int nType;
	int nCntLight = 0;
	int nRow;
	int nLine;
	int nSound;
	int nCntPlayer = 0;
	D3DXCOLOR col;
	D3DXVECTOR3 vec;
	D3DXVECTOR2 Tex;
	D3DXVECTOR3 posV;
	D3DXVECTOR3 posR;
	bool bSky = false;
	bool bDraw = true;
	float fSpeed;
	float fHeight;
	float fScroll;
	float fFriction = 1.0f;
	float fMaxSpeed = 1.0f;
	float fGravity = 0.3f;
	D3DXVECTOR3 PlayerPos[4];
	D3DXVECTOR3 PlayerRot[4];
	if (pFile != NULL)
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]); //fscanfを繰り返してファイルを読み取っていく
			if (strcmp(&aFile[0], "NUM_MODEL") == 0) //モデル数
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &nNumModel);
			}
			if (strcmp(&aFile[0], "SOUND") == 0) //流す曲（soundファイルと連動してる）
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &nSound);
				if (nSound != -1)
				{
					CSound::Play(nSound);
				}
			}
			if (strcmp(&aFile[0], "MODEL_FILENAME") == 0) //モデル名
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%s", &aFile[0]);
				CObject::Load(nCntModel, &aFile[0]);
				nCntModel++;
			}
			if (strcmp(&aFile[0], "FRICTION") == 0) //摩擦力
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%f", &fFriction);
			}
			if (strcmp(&aFile[0], "MAX_SPEED") == 0) //最大速度
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%f", &fMaxSpeed);
			}
			if (strcmp(&aFile[0], "GRAVITY") == 0) //重力
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%f", &fGravity);
			}
			if (strcmp(&aFile[0], "SNOW_TIME") == 0) //雪降らせる間隔
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &nTime);
				*pSnowTime = nTime;
			}
			if (strcmp(&aFile[0], "TIMESET") == 0) //時間
			{
				bTime = true;
			}
			if (strcmp(&aFile[0], "END_TIMESET") == 0) //時間
			{
				bTime = false;
			}
			if (strcmp(&aFile[0], "FIELDSET") == 0) //地面
			{
				bField = true;
			}
			if (strcmp(&aFile[0], "END_FIELDSET") == 0) //地面
			{
				CMeshField::Create(pos, size, rot, nRow, nLine, nTex, bDraw);
				bField = false;
			}
			if (strcmp(&aFile[0], "WALLSET") == 0) //壁
			{
				bWall = true;
			}
			if (strcmp(&aFile[0], "END_WALLSET") == 0) //壁
			{
				CMeshWall::Create(pos, size, rot, nRow, nLine, nTex, bDraw);
				bWall = false;
			}
			if (strcmp(&aFile[0], "MODELSET") == 0) //オブジェクト
			{
				bModel = true;
			}
			if (strcmp(&aFile[0], "END_MODELSET") == 0) //オブジェクト
			{
				CObject::Create(pos, rot, nType);
				bModel = false;
			}
			if (strcmp(&aFile[0], "BATTERYSET") == 0) //オブジェクト
			{
				bBattery = true;
			}
			if (strcmp(&aFile[0], "END_BATTERYSET") == 0) //オブジェクト
			{
				CBattery::Create(pos, rot, nTime, fSpeed, fHeight, fFriction, fMaxSpeed, fGravity, nStartTime);
				bBattery = false;
			}
			if (strcmp(&aFile[0], "LIGHTSET") == 0) //ライト
			{
				bLight = true;
			}
			if (strcmp(&aFile[0], "END_LIGHTSET") == 0) //ライト
			{
				CLight::Create(col, vec, nCntLight);
				nCntLight++;
				bLight = false;
			}
			if (strcmp(&aFile[0], "PLAYER") == 0) //プレイヤー
			{
				bPlayer = true;
			}
			if (strcmp(&aFile[0], "END_PLAYER") == 0) //プレイヤー
			{
				// プレイヤーのスタート位置をランダムで設定
				for (nCntPlayer = 0; nCntPlayer < 4; nCntPlayer++)
				{
					int nRandom = rand() % 4;
					D3DXVECTOR3 posSave = PlayerPos[nCntPlayer];
					PlayerPos[nCntPlayer] = PlayerPos[nRandom];
					PlayerPos[nRandom] = posSave;

					D3DXVECTOR3 rotSave = PlayerRot[nCntPlayer];
					PlayerRot[nCntPlayer] = PlayerRot[nRandom];
					PlayerRot[nRandom] = rotSave;
				}

				//プレイヤーの生成
				for (nCntPlayer = 0; nCntPlayer < 4; nCntPlayer++)
				{
					pPlayer[nCntPlayer] = CPlayer::Create(PlayerPos[nCntPlayer], PlayerRot[nCntPlayer], 
					(CPlayer::PLAYER_TYPE)nCntPlayer, CEntry::GetStandby(nCntPlayer), fFriction, fMaxSpeed, fGravity, false);
				}
				bPlayer = false;
			}
			if (strcmp(&aFile[0], "SKYSET") == 0) //空
			{
				bSky = true;
			}
			if (strcmp(&aFile[0], "END_SKYSET") == 0) //空
			{
				//CSky::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.00002f, CPlane::GetTexture(0));
				bSky = false;
			}
			if (bTime == true)
			{
				if (strcmp(&aFile[0], "TIME") == 0) //時間の設定
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nTime);
					*pTime = nTime;
				}
			}
			if (bField == true)
			{
				if (strcmp(&aFile[0], "POS") == 0) //場所
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
				}
				if (strcmp(&aFile[0], "ROT") == 0) //角度
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &rot.x, &rot.y, &rot.z);
					rot.x = rot.x / 180.0f * D3DX_PI;
					rot.y = rot.y / 180.0f * D3DX_PI;
					rot.z = rot.z / 180.0f * D3DX_PI;
				}
				if (strcmp(&aFile[0], "SIZE") == 0) //大きさ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &size.x, &size.y, &size.z);
				}
				if (strcmp(&aFile[0], "BLOCK") == 0) //分割数
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d %d", &nRow, &nLine);
				}
				if (strcmp(&aFile[0], "TEXTYPE") == 0) //テクスチャ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nTex);
				}
				if (strcmp(&aFile[0], "DRAW") == 0) //描画するか(-1だと描画しないそれ以外だと描画する)
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nDraw);
					if (nDraw == -1)
					{
						bDraw = false;
					}
					else
					{
						bDraw = true;
					}
				}
			}
			if (bWall == true)
			{
				if (strcmp(&aFile[0], "POS") == 0) //場所
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
				}
				if (strcmp(&aFile[0], "ROT") == 0) //回転
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &rot.x, &rot.y, &rot.z);
					rot.x = rot.x / 180.0f * D3DX_PI;
					rot.y = rot.y / 180.0f * D3DX_PI;
					rot.z = rot.z / 180.0f * D3DX_PI;

				}
				if (strcmp(&aFile[0], "SIZE") == 0) //大きさ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &size.x, &size.y, &size.z);
				}
				//if (strcmp(&aFile[0], "ROW") == 0) //縦の分割数
				//{
				//	fscanf(pFile, "%s", &aFile[0]);
				//	fscanf(pFile, "%d", &nRow);
				//}
				//if (strcmp(&aFile[0], "LINE") == 0) //横の分割数
				//{
				//	fscanf(pFile, "%s", &aFile[0]);
				//	fscanf(pFile, "%d", &nLine);
				//}
				if (strcmp(&aFile[0], "BLOCK") == 0) //分割数
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d %d", &nRow, &nLine);
				}
				if (strcmp(&aFile[0], "TEXTYPE") == 0) //テクスチャ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nTex);
				}
				if (strcmp(&aFile[0], "DRAW") == 0) //描画するか(-1だと描画しないそれ以外だと描画する)
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nDraw);
					if (nDraw == -1)
					{
						bDraw = false;
					}
					else
					{
						bDraw = true;
					}
				}
			}
			if (bModel == true)
			{
				if (strcmp(&aFile[0], "TYPE") == 0) //モデルの種類
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nType);
				}
				if (strcmp(&aFile[0], "POS") == 0) //モデルの場所
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
				}
				if (strcmp(&aFile[0], "ROT") == 0) //モデルの方向
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &rot.x, &rot.y, &rot.z);
					rot.x = rot.x / 180.0f * D3DX_PI;
					rot.y = rot.y / 180.0f * D3DX_PI;
					rot.z = rot.z / 180.0f * D3DX_PI;
				}
			}
			if (bBattery == true)
			{
				if (strcmp(&aFile[0], "POS") == 0) //モデルの場所
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
				}
				if (strcmp(&aFile[0], "ROT") == 0) //モデルの方向
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &rot.x, &rot.y, &rot.z);
					rot.x = rot.x / 180.0f * D3DX_PI;
					rot.y = rot.y / 180.0f * D3DX_PI;
					rot.z = rot.z / 180.0f * D3DX_PI;
				}
				if (strcmp(&aFile[0], "START_TIME") == 0) //最初発射するまでのカウント
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nStartTime);
				}
				if (strcmp(&aFile[0], "TIME") == 0) //発射間隔
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nTime);
				}
				if (strcmp(&aFile[0], "SPEED") == 0) //打ち出す爆弾の水平方向の速さ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &fSpeed);
				}
				if (strcmp(&aFile[0], "HEIGHT") == 0) //打ち出す爆弾の高さ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &fHeight);
				}
			}
			if (bLight == true)
			{
				if (strcmp(&aFile[0], "DIRECTION") == 0) //光の方向
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &vec.x, &vec.y, &vec.z);
				}
				if (strcmp(&aFile[0], "DIFFUSE") == 0) //光の色
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &col.r, &col.g, &col.b);
					col.a = 1.0f;
				}
			}
			if (bSky == true)
			{
				if (strcmp(&aFile[0], "TEXTYPE") == 0) //テクスチャ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nTex);
				}
				if (strcmp(&aFile[0], "MOVE") == 0) //動き
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &fScroll);
				}
			}
			if (bPlayer == true)
			{
				if (strcmp(&aFile[0], "PLAYERSET") == 0) //プレイヤー
				{
					bPlayerSet = true;
				}
				if (strcmp(&aFile[0], "END_PLAYERSET") == 0) //プレイヤー
				{
					nCntPlayer++;
					bPlayerSet = false;
				}
				if (bPlayerSet == true)
				{
					if (strcmp(&aFile[0], "POS") == 0) //モデルの場所
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f", &PlayerPos[nCntPlayer].x, &PlayerPos[nCntPlayer].y, &PlayerPos[nCntPlayer].z);
					}
					if (strcmp(&aFile[0], "ROT") == 0) //モデルの方向
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f", &PlayerRot[nCntPlayer].x, &PlayerRot[nCntPlayer].y, &PlayerRot[nCntPlayer].z);
						PlayerRot[nCntPlayer].x = PlayerRot[nCntPlayer].x / 180.0f * D3DX_PI;
						PlayerRot[nCntPlayer].y = PlayerRot[nCntPlayer].y / 180.0f * D3DX_PI;
						PlayerRot[nCntPlayer].z = PlayerRot[nCntPlayer].z / 180.0f * D3DX_PI;
					}
				}
			}
			if (strcmp(&aFile[0], "END_SCRIPT") == 0) //終わり
			{
				break;
			}
		}
		fclose(pFile);
	}
}

void CLoad::TutorialStageLoad(const char *aFileName, CPlayer *pPlayer[4])
{
	FILE *pFile;
	pFile = fopen(aFileName, "r");
	char aFile[256];
	int nNumModel;
	int nCntModel = 0;
	bool bField = false;
	bool bWall = false;
	bool bModel = false;
	bool bLight = false;
	bool bPlayer = false;
	bool bPlayerSet = false;
	bool bBattery = false;
	bool bTime = false;
	int nTime = 0;
	int nStartTime = 0;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	int nTex;
	int nDraw;
	D3DXVECTOR3 size;
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	int nType;
	int nCntLight = 0;
	int nRow;
	int nLine;
	int nSound;
	int nCntPlayer = 0;
	D3DXCOLOR col;
	D3DXVECTOR3 vec;
	D3DXVECTOR2 Tex;
	D3DXVECTOR3 posV;
	D3DXVECTOR3 posR;
	bool bSky = false;
	bool bDraw = true;
	float fSpeed;
	float fHeight;
	float fScroll;
	float fFriction = 1.0f;
	float fMaxSpeed = 1.0f;
	float fGravity = 0.3f;
	D3DXVECTOR3 PlayerPos[4];
	D3DXVECTOR3 PlayerRot[4];
	if (pFile != NULL)
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]); //fscanfを繰り返してファイルを読み取っていく
			if (strcmp(&aFile[0], "NUM_MODEL") == 0) //モデル数
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &nNumModel);
			}
			if (strcmp(&aFile[0], "SOUND") == 0) //流す曲（soundファイルと連動してる）
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &nSound);
				if (nSound != -1)
				{
					CSound::Play(nSound);
				}
			}
			if (strcmp(&aFile[0], "MODEL_FILENAME") == 0) //モデル名
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%s", &aFile[0]);
				CObject::Load(nCntModel, &aFile[0]);
				nCntModel++;
			}
			if (strcmp(&aFile[0], "FRICTION") == 0) //摩擦力
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%f", &fFriction);
			}
			if (strcmp(&aFile[0], "MAX_SPEED") == 0) //最大速度
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%f", &fMaxSpeed);
			}
			if (strcmp(&aFile[0], "GRAVITY") == 0) //重力
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%f", &fGravity);
			}
			if (strcmp(&aFile[0], "FIELDSET") == 0) //地面
			{
				bField = true;
			}
			if (strcmp(&aFile[0], "END_FIELDSET") == 0) //地面
			{
				CMeshField::Create(pos, size, rot, nRow, nLine, nTex, bDraw);
				bField = false;
			}
			if (strcmp(&aFile[0], "WALLSET") == 0) //壁
			{
				bWall = true;
			}
			if (strcmp(&aFile[0], "END_WALLSET") == 0) //壁
			{
				CMeshWall::Create(pos, size, rot, nRow, nLine, nTex, bDraw);
				bWall = false;
			}
			if (strcmp(&aFile[0], "MODELSET") == 0) //オブジェクト
			{
				bModel = true;
			}
			if (strcmp(&aFile[0], "END_MODELSET") == 0) //オブジェクト
			{
				CObject::Create(pos, rot, nType);
				bModel = false;
			}
			if (strcmp(&aFile[0], "BATTERYSET") == 0) //オブジェクト
			{
				bBattery = true;
			}
			if (strcmp(&aFile[0], "END_BATTERYSET") == 0) //オブジェクト
			{
				CBattery::Create(pos, rot, nTime, fSpeed, fHeight, fFriction, fMaxSpeed, fGravity, nStartTime);
				bBattery = false;
			}
			if (strcmp(&aFile[0], "LIGHTSET") == 0) //ライト
			{
				bLight = true;
			}
			if (strcmp(&aFile[0], "END_LIGHTSET") == 0) //ライト
			{
				CLight::Create(col, vec, nCntLight);
				nCntLight++;
				bLight = false;
			}
			if (strcmp(&aFile[0], "PLAYER") == 0) //プレイヤー
			{
				bPlayer = true;
			}
			if (strcmp(&aFile[0], "END_PLAYER") == 0) //プレイヤー
			{
				// プレイヤーのスタート位置をランダムで設定
				for (nCntPlayer = 0; nCntPlayer < 4; nCntPlayer++)
				{
					int nRandom = rand() % 4;
					D3DXVECTOR3 posSave = PlayerPos[nCntPlayer];
					PlayerPos[nCntPlayer] = PlayerPos[nRandom];
					PlayerPos[nRandom] = posSave;

					D3DXVECTOR3 rotSave = PlayerRot[nCntPlayer];
					PlayerRot[nCntPlayer] = PlayerRot[nRandom];
					PlayerRot[nRandom] = rotSave;
				}

				//プレイヤーの生成
				for (nCntPlayer = 0; nCntPlayer < 4; nCntPlayer++)
				{
					pPlayer[nCntPlayer] = CPlayer::Create(PlayerPos[nCntPlayer], PlayerRot[nCntPlayer],
						(CPlayer::PLAYER_TYPE)nCntPlayer, true, fFriction, fMaxSpeed, fGravity, true);
				}
				bPlayer = false;
			}
			if (strcmp(&aFile[0], "SKYSET") == 0) //空
			{
				bSky = true;
			}
			if (strcmp(&aFile[0], "END_SKYSET") == 0) //空
			{
				//CSky::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.00002f, CPlane::GetTexture(0));
				bSky = false;
			}
			if (bField == true)
			{
				if (strcmp(&aFile[0], "POS") == 0) //場所
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
				}
				if (strcmp(&aFile[0], "ROT") == 0) //角度
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &rot.x, &rot.y, &rot.z);
					rot.x = rot.x / 180.0f * D3DX_PI;
					rot.y = rot.y / 180.0f * D3DX_PI;
					rot.z = rot.z / 180.0f * D3DX_PI;
				}
				if (strcmp(&aFile[0], "SIZE") == 0) //大きさ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &size.x, &size.y, &size.z);
				}
				if (strcmp(&aFile[0], "BLOCK") == 0) //分割数
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d %d", &nRow, &nLine);
				}
				if (strcmp(&aFile[0], "TEXTYPE") == 0) //テクスチャ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nTex);
				}
				if (strcmp(&aFile[0], "DRAW") == 0) //描画するか(-1だと描画しないそれ以外だと描画する)
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nDraw);
					if (nDraw == -1)
					{
						bDraw = false;
					}
					else
					{
						bDraw = true;
					}
				}
			}
			if (bWall == true)
			{
				if (strcmp(&aFile[0], "POS") == 0) //場所
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
				}
				if (strcmp(&aFile[0], "ROT") == 0) //回転
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &rot.x, &rot.y, &rot.z);
					rot.x = rot.x / 180.0f * D3DX_PI;
					rot.y = rot.y / 180.0f * D3DX_PI;
					rot.z = rot.z / 180.0f * D3DX_PI;

				}
				if (strcmp(&aFile[0], "SIZE") == 0) //大きさ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &size.x, &size.y, &size.z);
				}
				if (strcmp(&aFile[0], "BLOCK") == 0) //分割数
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d %d", &nRow, &nLine);
				}
				if (strcmp(&aFile[0], "TEXTYPE") == 0) //テクスチャ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nTex);
				}
				if (strcmp(&aFile[0], "DRAW") == 0) //描画するか(-1だと描画しないそれ以外だと描画する)
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nDraw);
					if (nDraw == -1)
					{
						bDraw = false;
					}
					else
					{
						bDraw = true;
					}
				}
			}
			if (bModel == true)
			{
				if (strcmp(&aFile[0], "TYPE") == 0) //モデルの種類
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nType);
				}
				if (strcmp(&aFile[0], "POS") == 0) //モデルの場所
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
				}
				if (strcmp(&aFile[0], "ROT") == 0) //モデルの方向
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &rot.x, &rot.y, &rot.z);
					rot.x = rot.x / 180.0f * D3DX_PI;
					rot.y = rot.y / 180.0f * D3DX_PI;
					rot.z = rot.z / 180.0f * D3DX_PI;
				}
			}
			if (bBattery == true)
			{
				if (strcmp(&aFile[0], "POS") == 0) //モデルの場所
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
				}
				if (strcmp(&aFile[0], "ROT") == 0) //モデルの方向
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &rot.x, &rot.y, &rot.z);
					rot.x = rot.x / 180.0f * D3DX_PI;
					rot.y = rot.y / 180.0f * D3DX_PI;
					rot.z = rot.z / 180.0f * D3DX_PI;
				}
				if (strcmp(&aFile[0], "START_TIME") == 0) //最初発射するまでのカウント
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nStartTime);
				}
				if (strcmp(&aFile[0], "TIME") == 0) //発射間隔
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nTime);
				}
				if (strcmp(&aFile[0], "SPEED") == 0) //打ち出す爆弾の水平方向の速さ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &fSpeed);
				}
				if (strcmp(&aFile[0], "HEIGHT") == 0) //打ち出す爆弾の高さ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &fHeight);
				}
			}
			if (bLight == true)
			{
				if (strcmp(&aFile[0], "DIRECTION") == 0) //光の方向
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &vec.x, &vec.y, &vec.z);
				}
				if (strcmp(&aFile[0], "DIFFUSE") == 0) //光の色
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &col.r, &col.g, &col.b);
					col.a = 1.0f;
				}
			}
			if (bSky == true)
			{
				if (strcmp(&aFile[0], "TEXTYPE") == 0) //テクスチャ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nTex);
				}
				if (strcmp(&aFile[0], "MOVE") == 0) //動き
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &fScroll);
				}
			}
			if (bPlayer == true)
			{
				if (strcmp(&aFile[0], "PLAYERSET") == 0) //プレイヤー
				{
					bPlayerSet = true;
				}
				if (strcmp(&aFile[0], "END_PLAYERSET") == 0) //プレイヤー
				{
					nCntPlayer++;
					bPlayerSet = false;
				}
				if (bPlayerSet == true)
				{
					if (strcmp(&aFile[0], "POS") == 0) //モデルの場所
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f", &PlayerPos[nCntPlayer].x, &PlayerPos[nCntPlayer].y, &PlayerPos[nCntPlayer].z);
					}
					if (strcmp(&aFile[0], "ROT") == 0) //モデルの方向
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f", &PlayerRot[nCntPlayer].x, &PlayerRot[nCntPlayer].y, &PlayerRot[nCntPlayer].z);
						PlayerRot[nCntPlayer].x = PlayerRot[nCntPlayer].x / 180.0f * D3DX_PI;
						PlayerRot[nCntPlayer].y = PlayerRot[nCntPlayer].y / 180.0f * D3DX_PI;
						PlayerRot[nCntPlayer].z = PlayerRot[nCntPlayer].z / 180.0f * D3DX_PI;
					}
				}
			}
			if (strcmp(&aFile[0], "END_SCRIPT") == 0) //終わり
			{
				break;
			}
		}
		fclose(pFile);
	}
}

void CLoad::SoundLoad(const char *aFileName)
{
	FILE *pFile;
	pFile = fopen(aFileName, "r");
	char aFile[256];
	char aSoundName[64];
	int nLoop;
	int nCntSound = 0;
	int nSound = 0;
	bool bSet = false;
	if (pFile != NULL)
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]); //fscanfを繰り返してファイルを読み取っていく
			if (strcmp(&aFile[0], "NUM_SOUND") == 0) //いくつ音があるか
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &nSound);
				CSound::SetSoundNum(nSound);
			}
			if (strcmp(&aFile[0], "SOUND_SET") == 0)
			{
				bSet = true;
			}
			if (strcmp(&aFile[0], "END_SOUND_SET") == 0)
			{
				CSound::SetParamData(&aSoundName[0], nLoop, nCntSound);
				bSet = false;
				nCntSound++;
			}
			if (bSet == true)
			{
				if (strcmp(&aFile[0], "NAME") == 0) //名前
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%s", &aSoundName[0]);
				}
				if (strcmp(&aFile[0], "LOOP") == 0) //ループするかしないか
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nLoop);
				}
			}
			if (strcmp(&aFile[0], "END_SCRIPT") == 0) //終わり
			{
				break;
			}
		}
		fclose(pFile);
	}
}

void CLoad::BombsLoad(const char *aFileName)
{
	FILE *pFile;
	pFile = fopen(aFileName, "r");
	char aFile[256];
	int nCntModel = 0;
	int nSound;
	bool bBomb = false;
	if (pFile != NULL)
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]); //fscanfを繰り返してファイルを読み取っていく
			if (strcmp(&aFile[0], "BOMB_SET") == 0)
			{
				bBomb = true;
			}
			if (strcmp(&aFile[0], "END_BOMB_SET") == 0)
			{
				nCntModel++;
				bBomb = false;
			}
			if (bBomb == true)
			{
				if (strcmp(&aFile[0], "FILENAME") == 0) //モデル名
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%s", &aFile[0]);
					CBomb::LoadModel(nCntModel, &aFile[0]);
				}
				if (strcmp(&aFile[0], "SOUND") == 0) //音声番号
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nSound);
					CBomb::LoadSound(nCntModel, nSound);
				}
			}
			if (strcmp(&aFile[0], "END_SCRIPT") == 0) //終わり
			{
				break;
			}
		}
		fclose(pFile);
	}
}