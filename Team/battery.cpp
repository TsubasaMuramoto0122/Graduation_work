//=============================================================================
//
// 砲台処理 [battery.h]
// Author : 三上航世
//
//=============================================================================
#include "battery.h"
#include "manager.h"
#include "sound.h"
#include "motion.h"
#include "renderer.h"

#include "bomb.h"
#include "icebomb.h"
#include "normalbomb.h"
#include "confusionbomb.h"
#include "poisonbomb.h"
#include "firebomb.h"

//=============================================================================
//マクロ
//=============================================================================
//#define BOMB_SPEED (6.0f)
//#define BOMB_HEIGHT (5.0f)

//静的メンバ変数
CModel *CBattery::m_pOriModel[MAX_BATTERY] = {};

CBattery::CBattery(PRIORITY nPriority) : CObject(nPriority)
{

}

CBattery::~CBattery()
{

}

//初期化処理
HRESULT CBattery::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nTime, float fSpeed, float fHeight)
{
	SetPos(pos);
	SetRot(rot);
	m_nTime = nTime;
	m_nMaxTime = nTime;
	m_fSpeed = fSpeed;
	m_fHeight = fHeight;
	int nCnt;
	for (nCnt = 0; nCnt < MAX_BATTERY; nCnt++)
	{
		if (m_pOriModel[nCnt] != NULL)
		{
			m_pModel[nCnt] = new CModel;
			m_pModel[nCnt]->Copy(m_pOriModel[nCnt]);

			if (m_pOriModel[nCnt]->GetIdxParent() == -1)
			{
				m_pModel[nCnt]->SetParent(NULL);
			}
			else
			{
				m_pModel[nCnt]->SetParent(m_pModel[m_pOriModel[nCnt]->GetIdxParent()]);
			}
		}
	}
	m_pMotion = CMotion::Create(this, CMotion::MOTION_TYPE_BATTERY);
	m_pMotion->SetStop(true);
	m_pMotion->Update(this);

	return S_OK;
}

//終了処理
void CBattery::Uninit()
{
	int nCnt;
	for (nCnt = 0; nCnt < MAX_BATTERY; nCnt++)
	{
		if (m_pModel[nCnt] != NULL)
		{
			m_pModel[nCnt]->Uninit();
			m_pModel[nCnt] = NULL;
		}
	}
	CObject::Uninit();
}

//更新処理
void CBattery::Update()
{
	if (CManager::GetPause() == false && CManager::GetCountdown() == false && CManager::GetGameEnd() == false)
	{
		D3DXVECTOR3 pos = GetPos();
		D3DXVECTOR3 posOld = pos;
		D3DXVECTOR3 rot = GetRot();
		rot.y += 0.07f;
		if (m_nTime > 0)
		{
			m_nTime--;
		}
		else
		{
			RandomBomb(pos, rot);
		}
		SetRot(rot);

		// モーション
		m_pMotion->Update(this);
	}
}

//描画処理
void CBattery::Draw()
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//pos、rotの取得
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	int nCnt;
	for (nCnt = 0; nCnt < MAX_BATTERY; nCnt++)
	{
		if (m_pModel[nCnt] != NULL)
		{
			m_pModel[nCnt]->Draw();
		}
	}
}

CBattery *CBattery::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nTime, float fSpeed, float fHeight)
{
	CBattery *pBattery;
	pBattery = new CBattery(CScene::PRIORITY_OBJECT);
	if (pBattery != NULL)
	{
		pBattery->Init(pos, rot, nTime, fSpeed, fHeight);
	}
	return pBattery;
}

void CBattery::RandomBomb(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//生成する爆弾にランダム性を持たせる
	int nRand = rand() % CBomb::MAX_BOMB;

	D3DXVECTOR3 BombPos = D3DXVECTOR3(pos.x, pos.y + 20.0f, pos.z);

	nRand = 3;

	//向いてる方向に撃てるようにする
	D3DXVECTOR3 move = D3DXVECTOR3(-sinf(rot.y) * m_fSpeed, m_fHeight, -cosf(rot.y) * m_fSpeed);
	switch (nRand)
	{
	case CBomb::BOMB_NORMAL:
		CNormalBomb::Create(BombPos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), move);
		break;
	case CBomb::BOMB_ICE:
		CIceBomb::Create(BombPos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), move);
		break;
	case CBomb::BOMB_FIRE:
		CFireBomb::Create(BombPos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), move);
		break;
	case CBomb::BOMB_POISON:
		CPoisonBomb::Create(BombPos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), move);
		break;
	case CBomb::BOMB_CONFUSION:
		CConfusionBomb::Create(BombPos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), move);
		break;
	default:
		break;
	}
	m_pMotion->SetMotion(0);
	m_nTime = m_nMaxTime;
	CSound::Play(11);
}

//モデルの読み込み
void CBattery::BatteryLoad()
{
	// テキストファイルの読み込み
	char cString[256];
	FILE *pFile = NULL;

	pFile = fopen(MOTION_BATTERY_FILE, "r");

	if (pFile != NULL)
	{
		int nCntModel = 0;
		char cFileName[MAX_BATTERY][256];

		while (1)
		{
			fscanf(pFile, "%s", &cString[0]);

			// モデルのパスを取得
			if (strcmp(&cString[0], "MODEL_FILENAME") == 0)
			{
				fscanf(pFile, "%s", &cString[0]);
				fscanf(pFile, "%s", &cFileName[nCntModel][0]);
				nCntModel++;
			}

			// モデルが最大数になったらパスの読み込みを終了
			if (nCntModel >= MAX_BATTERY)
			{
				nCntModel = 0;
				break;
			}
		}

		int nIdx = 0, nParents = 0;
		D3DXVECTOR3 pos, rot;

		while (1)
		{
			fscanf(pFile, "%s", &cString[0]);

			if (strcmp(&cString[0], "PARTSSET") == 0)	//PARTSSETの文字列
			{
				// モデルのパーツ数だけ回す
				while (1)
				{
					fscanf(pFile, "%s", &cString[0]);

					if (strcmp(&cString[0], "INDEX") == 0) //インデックス番号
					{
						fscanf(pFile, "%s", &cString[0]);
						fscanf(pFile, "%d", &nIdx);
					}
					if (strcmp(&cString[0], "PARENT") == 0) //親のモデル
					{
						fscanf(pFile, "%s", &cString[0]);
						fscanf(pFile, "%d", &nParents);
					}
					if (strcmp(&cString[0], "POS") == 0) //位置
					{
						// 位置を取得する
						fscanf(pFile, "%s", &cString[0]);
						fscanf(pFile, "%f%f%f", &pos.x, &pos.y, &pos.z);
					}
					if (strcmp(&cString[0], "ROT") == 0) //向き
					{
						// 向きを取得する
						fscanf(pFile, "%s", &cString[0]);
						fscanf(pFile, "%f%f%f", &rot.x, &rot.y, &rot.z);
					}
					if (strcmp(&cString[0], "END_PARTSSET") == 0)
					{
						break;
					}
				}

				// モデルを生成し、向きと位置を設定
				m_pOriModel[nCntModel] = CModel::Create(&cFileName[nCntModel][0]);
				m_pOriModel[nCntModel]->SetOriRot(rot);
				m_pOriModel[nCntModel]->SetOriPos(pos);

				// 親モデルを設定
				m_pOriModel[nCntModel]->SetIdxParent(nParents);

				nCntModel++;
			}

			// モデルが最大数になったら配置を終了
			if (nCntModel >= MAX_BATTERY)
			{
				break;
			}
		}
		fclose(pFile);
	}
}

void CBattery::BatteryUnLoad()
{
	int nCntModel;
	for (nCntModel = 0; nCntModel < MAX_BATTERY; nCntModel++)
	{
		if (m_pOriModel[nCntModel] != NULL)
		{
			m_pOriModel[nCntModel]->Uninit();
			m_pOriModel[nCntModel] = NULL;
		}
	}
}