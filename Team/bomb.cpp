//=============================================================================
//
// 爆弾処理 [bomb.h]
// Author : 三上航世
//
//=============================================================================
#include "bomb.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "danger.h"
#include "sound.h"
#include "ui.h"
#include "mesh_field.h"
#include "mesh_wall.h"
#include "presetdelayset.h"
#include "collision_sphere.h"
#include "cpu.h"

//=============================================================================
//静的
//=============================================================================
CModel *CBomb::m_paModel[MAX_BOMB] = {};
int CBomb::m_nSound[MAX_BOMB] = {};

//=============================================================================
//マクロ
//=============================================================================
#define REFLECT (-0.4f)			//反射
#define GRAVITY (0.3f)			//重力
#define EXPLOSION_TIME (250)	//爆発するまでの時間
#define FLASH_TIME (90)			//点滅し始めの時間
#define CLEAR_TIME (5)			//明るくなったり暗くなるまでの時間
#define FRICTION (0.2f)			//摩擦力。低くなればなるほど滑らない。1より大きくすると加速していく
#define KNOCKBACK_JUMP (3.0f)	//吹き飛ばされたときのジャンプ
#define KNOCKBACK_CLASH (6.0f)	//吹き飛ばされたときの水平吹き飛ばし力

CBomb::CBomb(PRIORITY Priority) : CScene3D::CScene3D(Priority)
{

}

CBomb::~CBomb()
{

}

//初期化処理
HRESULT CBomb::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, BOMBTYPE BombType, float fFriction)
{
	D3DXVECTOR3 VtxMax, VtxMin;

	//対応したモデルにする
	m_pModel = new CModel;
	m_pModel->Copy(m_paModel[BombType]);

	m_nPlaySound = m_nSound[BombType];

	//モデルのそれぞれの方向の最大値、最小値を求める
	VtxMax = m_pModel->GetMaxSize();
	VtxMin = m_pModel->GetMinSize();

	//一番大きい半径を求める
	m_fRadius = (VtxMax.x - VtxMin.x) / 2.0f;
	if (m_fRadius < (VtxMax.y - VtxMin.y) / 2.0f)
	{
		m_fRadius = (VtxMax.y - VtxMin.y) / 2.0f;
	}
	if (m_fRadius < (VtxMax.z - VtxMin.z) / 2.0f)
	{
		m_fRadius = (VtxMax.z - VtxMin.z) / 2.0f;
	}

	m_move = move;
	m_nTime = EXPLOSION_TIME;
	m_nFlash = CLEAR_TIME * 2;
	m_fClear = 1.0f;
	m_pDanger = CDanger::Create(D3DXVECTOR3(75.0f, 0.0f, 75.0f), Predict(pos));
	SetRot(rot);
	SetPos(pos);
	SetPosOld(pos);
	m_bHit = false;
	m_bBound = false;
	m_bLand = false;
	m_fFriction = fFriction;

	//コリジョンを持たせる
	m_pCollision = CCollisionSphere::Create(pos, m_fRadius * 2.0f, 16, 16, CCollisionSphere::COLLISION_S_TYPE::COLLISION_S_TYPE_PLAYER, -1.0f, 0.0f);

	return S_OK;
}

//終了処理
void CBomb::Uninit()
{
	if (m_pModel != NULL)
	{
		//m_pModel->Uninit();
		m_pModel = NULL;
	}
	if (m_pDanger != NULL)
	{
		m_pDanger = NULL;
	}
	if (m_pCollision != NULL)
	{
		m_pCollision->SetDeath(true);
		m_pCollision = NULL;
	}
	if (m_pCPU != NULL)
	{
		m_pCPU = NULL;
	}
	CScene3D::Uninit();
}

//更新処理
void CBomb::Update()
{
	//ポーズ中でないなら
	if (CManager::GetPause() == false && CManager::GetCountdown() == false && CManager::GetGameEnd() == false)
	{
		D3DXVECTOR3 pos = GetPos();
		D3DXVECTOR3 rot = GetRot();
		SetPosOld(pos);
		MoveDown();
		pos += m_move;

		SetPos(pos);

		//地面とのバウンド
		pos = Bound(pos);

		SetPos(pos);

		//攻撃との当たり判定
		Clash();

		// 壁との当たり判定
		WallReflect();

		//バウンドした後、またはプレイヤーの攻撃が当たったとき
		if (m_bBound == true || m_bHit == true)
		{
			//爆発範囲が移動する
			m_pDanger->Move(pos);
		}

		//コリジョンの追従
		m_pCollision->SetPosCollision(D3DXVECTOR3(pos.x, pos.y + m_fRadius, pos.z));

		//時間経過
		TimeDec(pos);
	}
}

//描画処理
void CBomb::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;   //デバイスのポインタ
	pDevice = CManager::GetRenderer()->GetDevice();		 //デバイスを取得する

	D3DXMATRIX mtxPlayer;
	mtxPlayer = CScene3D::GetMatrix();

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxPlayer);
	m_pModel->Draw();
}

void CBomb::ZTexDraw()
{
	LPDIRECT3DDEVICE9 pDevice;   //デバイスのポインタ
	D3DXMATRIX mtxPlayer, mtxRot, mtxTrans;
	pDevice = CManager::GetRenderer()->GetDevice();		 //デバイスを取得する

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxPlayer);
	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, GetRot().y, GetRot().x, GetRot().z);
	D3DXMatrixMultiply(&mtxPlayer, &mtxPlayer, &mtxRot);
	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);
	D3DXMatrixMultiply(&mtxPlayer, &mtxPlayer, &mtxTrans);
	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxPlayer);
	SetMatrix(mtxPlayer);
	m_pModel->ZTexDraw();
}

//モデルの破棄
void CBomb::UnLoad()
{
	int nCntModel;
	for (nCntModel = 0; nCntModel < MAX_BOMB; nCntModel++)
	{
		if (m_paModel[nCntModel] != NULL)
		{
			m_paModel[nCntModel]->Uninit();
			m_paModel[nCntModel] = NULL;
		}
	}
}

//危険区域の点滅
void CBomb::Flash()
{
	m_nFlash--;
	if (m_nFlash >= CLEAR_TIME)
	{
		m_fClear -= 1.0f / (float)CLEAR_TIME;
	}
	else
	{
		if (m_nFlash <= 0)
		{
			m_nFlash = CLEAR_TIME * 2;
		}
		m_fClear += 1.0f / (float)CLEAR_TIME;
	}
	m_pDanger->ChangeColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, m_fClear));
}

//時間減少
void CBomb::TimeDec(D3DXVECTOR3 pos)
{
	//寿命がまだある
	if (m_nTime > 0)
	{
		m_nTime--;
		if (m_nTime < FLASH_TIME)
		{
			Flash();
		}
	}
	//寿命切れ
	else
	{
		if (m_pCPU != NULL)
		{
			if (m_pCPU->GetBomb() != NULL)
			{
				m_pCPU->BombClear();

			}
			m_pCPU = NULL;
		}
		Explosion(pos);
		CSound::Play(m_nPlaySound);
		m_pDanger->SetDeath(true);
		SetDeath(true);
	}
}

//地面に着地
D3DXVECTOR3 CBomb::Bound(D3DXVECTOR3 pos)
{
	D3DXVECTOR3 ReturnPos = pos;
	//地面に着地した
	if (m_bLand == true)
	{
		//１回跳ねてる
		if (m_bBound == true)
		{
			ReturnPos.y = 0.0f;
			m_move.y *= REFLECT;
			if (m_move.y < 0.2f)
			{
				m_move.y = 0.0f;
			}
		}
		//まだ跳ねてない
		else
		{
			ReturnPos.y = 0.1f;
			m_move.y *= REFLECT;
			m_bBound = true;
			m_bLand = false;
		}
	}
	else
	{
		//地面との当たり判定
		m_bLand = CMeshField::Collision(this);
	}
	return ReturnPos;
}

//重力または地面との摩擦による移動量の低下
void CBomb::MoveDown()
{
	//着地してないため、重力が働く
	if (m_bLand == false)
	{
		m_move.y -= GRAVITY;
	}
	//着地してるため、摩擦が働く
	else
	{
		m_move.x -= m_move.x * FRICTION * m_fFriction;
		m_move.z -= m_move.z * FRICTION * m_fFriction;
	}
}

//着弾点の予測
D3DXVECTOR3 CBomb::Predict(D3DXVECTOR3 pos)
{
	int nTime = (fabsf(m_move.y) / GRAVITY) * 2;
	D3DXVECTOR3 PredictPos = D3DXVECTOR3(pos.x + m_move.x * (float)nTime, 0.0f, pos.z + m_move.z * (float)nTime);
	return PredictPos;
}

//壁との反射
void CBomb::WallReflect()
{
	//壁と当たっているか確認
	D3DXVECTOR3 Vec = CMeshWall::Collision(this);

	//角度が正常か確認(異常な場合、壁に当たってない)
	if (-D3DX_PI <= Vec.x && Vec.x <= D3DX_PI)
	{
		D3DXVECTOR3 out;
		//壁の法線ベクトルと移動速度とを計算し、反射をする
		//D3DXVec3Normalize(&out, &(m_move - 2.0f * D3DXVec3Dot(&m_move, &Vec) * Vec));
		out = m_move - 2.0f * D3DXVec3Dot(&m_move, &Vec) * Vec;
		m_move.x = out.x;
		m_move.z = out.z;
	}
}

//プレイヤーの攻撃との当たり判定
void CBomb::Clash()
{
	if (m_pCollision->GetTouchCollision(CCollisionSphere::COLLISION_S_TYPE_ATTACK) == true)
	{
		if (m_bHit == false)
		{
			m_bHit = true;
		}
		m_bLand = false;

		// 移動させる
		float fRot = m_pCollision->GetPlayerRot() + D3DX_PI;
		if (D3DX_PI < fRot)
		{
			fRot -= D3DX_PI * 2.0f;
		}
		m_move = D3DXVECTOR3(KNOCKBACK_CLASH * sinf(fRot), KNOCKBACK_JUMP, KNOCKBACK_CLASH * cosf(fRot));
	}
}

//================================================
// 一番近い爆弾探す(CPU用)
//================================================
CBomb *CBomb::SearchBomb(D3DXVECTOR3 pos, CCPU *pCPU)
{
	//オブジェクト情報を入れるポインタ
	CScene *pObject = NULL;
	//オブジェクト情報を保存するポインタ変数
	CScene *pSaveObject = NULL;

	float fShortDistance = 300.0f;
	CBomb *pSaveBomb = NULL;

	//先頭のポインタを代入
	pObject = pObject->GetTopObj(CScene::PRIORITY_BOMB);

	while (pObject != NULL)
	{
		//現在のオブジェクトのポインタを保存
		pSaveObject = pObject;

		//オブジェクトタイプが爆弾の場合
		if (pObject->GetObjType() == CScene::OBJECTTYPE_BOMB)
		{
			CBomb *pBomb = (CBomb*)pObject;

			if (pBomb->GetDeath() == false)
			{
				D3DXVECTOR3 Bombpos = pBomb->GetPos();		//爆弾の位置

				//距離の計算
				float fDistance = sqrtf(powf(Bombpos.x - pos.x, 2.0f) + powf(Bombpos.z - pos.z, 2.0f));

				//セーブしてる爆弾よりも距離が近い、かつ爆発するまで4フレームよりかかる、かつ予測範囲がNULLじゃない
				if (fShortDistance > fDistance && pBomb->m_nTime > 4 && pBomb->GetDanger() != NULL)
				{
					pSaveBomb = pBomb;
					fShortDistance = fDistance;
				}
			}
		}
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}
	if (pSaveBomb != NULL)
	{
		pSaveBomb->m_pCPU = pCPU;
	}
	return pSaveBomb;
}