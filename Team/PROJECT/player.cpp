//=============================================================================
// プレイヤー処理 [player.cpp]
// Authore : Kusakari Kakeru
//=============================================================================
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "player.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
//#include "model_single.h"
//#include "model_load.h"
#include "camera.h"
//#include "motion_player.h"
#include "control_player.h"
#include "shadow.h"
#include "sound.h"
//#include "collision_sphere.h"
//#include "life.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CPlayer::CPlayer(PRIORITY Priority) : CScene3D::CScene3D(Priority)
{
	// 変数のクリア
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	for (int nCntModel = 0; nCntModel < MAX_PLAYER_MODEL; nCntModel++)
	{
		m_apModel[nCntModel] = NULL;
	}
	m_pParent = NULL;
	//m_pMotionPlayer = NULL;
	m_pControl = NULL;
	m_bLand = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CPlayer::~CPlayer()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos)
{
	// 変数の初期化
	m_pos = pos;
	m_posOld = pos;
	//m_move = m_pControl->GetMove();
	m_bLand = false;

	// モデル生成処理
	ModelCreate();

	//// 位置の設定
	//SetPos(m_pos);
	//SetPosOld(m_posOld);

	//// 頭のパーツのサイズを取得
	//m_size = m_apModel[0]->GetSize();

	//// サイズの設定
	//SetSize(m_size);

	// モーションの生成
	//m_pMotionPlayer = CMotionPlayer::Create(this);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPlayer::Uninit(void)
{
	// オブジェクトの破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CPlayer::Update(void)
{
	if (this != NULL)
	{
		// 1フレーム前の位置を設定
		m_posOld = m_pos;

		// 移動処理
		Move();

		// 移動量反映
		m_pos += m_move;

		// モーション
		//m_pMotionPlayer->Update(this);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CPlayer::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// モデルの描画
	for (int nCntModel = 0; nCntModel < MAX_PLAYER_MODEL; nCntModel++)
	{
		m_apModel[nCntModel]->Draw();
	}

}

//=============================================================================
// 生成処理
//=============================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// インスタンスの生成
	CPlayer *pPlayer = NULL;

	// ヌルチェック
	if (pPlayer == NULL)
	{
		// クラスの生成
		pPlayer = new CPlayer;
		if (pPlayer != NULL)
		{
			// プレイヤー操作のクラスを生成
			pPlayer->m_pControl = CControlPlayer::Create();

			// 変数の初期化
			pPlayer->m_rot = rot;

			// 初期化処理
			pPlayer->Init(pos);
		}
	}

	return pPlayer;
}

//=============================================================================
// モデル生成処理
//=============================================================================
void CPlayer::ModelCreate(void)
{
	//// テキスト保存用の変数
	//char cString[256];

	//// テキストファイルの読み込み
	//FILE *pFile = fopen("data/TEXT/motion_player.txt", "r");

	//if (pFile != NULL)
	//{
	//	// モデルの種類
	//	int nModelType = (int)CModelLoad::MODEL_TYPE_PLAYER_WAIST;

	//	// 配置情報の読み込み
	//	for (int nCntMotion = 0; nCntMotion < MAX_PLAYER_MODEL; nCntMotion++, nModelType++)
	//	{
	//		// テキストファイルの最後(NULL)まで読み込む
	//		while (fgets(cString, 256, pFile) != NULL)
	//		{
	//			// 文字列を保存
	//			fscanf(pFile, "%s", cString);

	//			// 文字列の中に"PARTSSET"があったら
	//			if (strncmp("PARTSSET", cString, 9) == 0)
	//			{
	//				break;
	//			}
	//		}

	//		while (fgets(cString, 256, pFile) != NULL)
	//		{
	//			// 文字列を保存
	//			fscanf(pFile, "%s", cString);

	//			// 文字列の中に"INDEX"があったら
	//			if (strncmp("INDEX", cString, 6) == 0)
	//			{
	//				int nIdx, nParents;
	//				D3DXVECTOR3 pos, rot;

	//				//インデックス番号と親子付けの番号を取得
	//				fscanf(pFile, "%s%d%*s%*s", cString, &nIdx);
	//				fscanf(pFile, "%s%*s%d%*s%*s%*s", cString, &nParents);

	//				//位置・回転情報を取得
	//				fscanf(pFile, "%s%f%f%f", cString, &pos.x, &pos.y, &pos.z);
	//				fscanf(pFile, "%s%*s%f%f%f", cString, &rot.x, &rot.y, &rot.z);

	//				// モデルの生成
	//				m_apModel[nCntMotion] = CModel::Create(NULL);

	//				// 親の設定(-1が指定されていた場合、親子付けは無いとしてNULLで設定しておく)
	//				if (nParents == -1)
	//				{
	//					m_apModel[nCntMotion]->SetParent(NULL);
	//				}
	//				else
	//				{
	//					m_apModel[nCntMotion]->SetParent(m_apModel[nParents]);
	//				}

	//				break;
	//			}
	//		}

	//		while (fgets(cString, 256, pFile) != NULL)
	//		{
	//			// 文字列を保存
	//			fscanf(pFile, "%s", cString);

	//			// 文字列の中に"END_PARTSSET"があったらそこで終了
	//			if (strncmp("END_PARTSSET", cString, 13) == 0)
	//			{
	//				break;
	//			}
	//		}
	//	}
	//	// ファイルを閉じる
	//	fclose(pFile);
	//}

	// モデルの生成
	m_apModel[0] = CModel::Create("data/MODEL/kirby.x");
}

//=============================================================================
// 移動処理
//=============================================================================
void CPlayer::Move(void)
{
	// ヌルチェック
	if (m_pControl != NULL)
	{
		// プレイヤー操作のクラスにプレイヤーのポインタを入れ、移動量を取得
		m_pControl->Update(this);
		m_move = m_pControl->GetMove();
	}
}

//=============================================================================
// 1フレーム前の位置取得処理
//=============================================================================
D3DXVECTOR3 CPlayer::GetPosOld(void)
{
	return m_posOld;
}


//=============================================================================
// 着地設定処理
//=============================================================================
void CPlayer::SetLand(bool bLand)
{
	m_bLand = bLand;
}

//=============================================================================
// 着地取得処理
//=============================================================================
bool CPlayer::GetLand(void)
{
	return m_bLand;
}

//=============================================================================
// モデル毎の位置設定処理
//=============================================================================
void CPlayer::SetModelPos(int nCntModel, D3DXVECTOR3 pos)
{
	m_apModel[nCntModel]->SetPos(pos);
}

//=============================================================================
// モデル毎の位置取得処理
//=============================================================================
D3DXVECTOR3 CPlayer::GetModelPos(int nCntModel)
{
	return m_apModel[nCntModel]->GetPos();
}

//=============================================================================
// モデル毎の向き設定処理
//=============================================================================
void CPlayer::SetModelRot(int nCntModel, D3DXVECTOR3 rot)
{
	m_apModel[nCntModel]->SetRot(rot);
}

//=============================================================================
// モデル毎の向き取得処理
//=============================================================================
D3DXVECTOR3 CPlayer::GetModelRot(int nCntModel)
{
	return m_apModel[nCntModel]->GetRot();
}

////=============================================================================
//// プレイヤーのモーション取得処理
////=============================================================================
//CMotionPlayer *CPlayer::GetMotionPlayer(void)
//{
//	return m_pMotionPlayer;
//}
//
////=============================================================================
//// プレイヤーのモデル取得処理
////=============================================================================
//CModel *CPlayer::GetModel(int nCntModel)
//{
//	return m_apModel[nCntModel];
//}