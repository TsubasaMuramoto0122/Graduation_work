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
#include "collision_sphere.h"

//=============================================================================
//静的
//=============================================================================
CModel *CBomb::m_paModel[MAX_BOMB] = {};

//=============================================================================
//マクロ
//=============================================================================
#define REFLECT (-0.4f)			//反射
#define GRAVITY (0.3f)			//重力
#define EXPLOSION_TIME (250)	//爆発するまでの時間
#define FLASH_TIME (150)		//点滅し始めの時間
#define CLEAR_TIME (5)			//明るくなったり暗くなるまでの時間
#define FRICTION (0.8f)			//摩擦力。低くなればなるほど滑らない

CBomb::CBomb(PRIORITY Priority) : CScene3D::CScene3D(Priority)
{

}

CBomb::~CBomb()
{

}

//初期化処理
HRESULT CBomb::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, BOMBTYPE BombType)
{
	D3DXVECTOR3 VtxMax, VtxMin;

	//対応したモデルにする
	m_pModel = new CModel;
	m_pModel->Copy(m_paModel[BombType]);

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
	m_pDanger = CDanger::Create(D3DXVECTOR3(m_fRadius * 3.0f, 0.0f, m_fRadius * 3.0f), Predict(pos));
	SetRot(rot);
	SetPos(pos);
	m_bBound = false;
	m_bLand = false;

	//コリジョンを持たせる
	m_pCollision = CCollisionSphere::Create(pos, m_fRadius * 2.0f, 16, 16, CCollisionSphere::COLLISION_S_TYPE::COLLISION_S_TYPE_PLAYER, -1.0f);

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
		m_pDanger->SetDeath(true);
		m_pDanger = NULL;
	}
	if (m_pCollision != NULL)
	{
		m_pCollision->SetDeath(true);
		m_pCollision = NULL;
	}
	CScene3D::Uninit();
}

//更新処理
void CBomb::Update()
{
	//ポーズ中でないなら
	if (CManager::GetPause() == false)
	{
		D3DXVECTOR3 pos = GetPos();
		D3DXVECTOR3 rot = GetRot();
		MoveDown();
		pos += m_move;
		pos = Bound(pos);
		SetPos(pos);
		// 壁との当たり判定
		CMeshWall::Collision(this) == true;
		if (m_bBound == true)
		{
			m_pDanger->Move(pos);
		}
		m_pCollision->SetPosCollision(pos);
		TimeDec(pos);
	}
}

//描画処理
void CBomb::Draw()
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
	m_pModel->Draw();
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
		Explosion(pos);
		CSound::Play(4);
		SetDeath(true);
	}
}

//地面に着地
D3DXVECTOR3 CBomb::Bound(D3DXVECTOR3 pos)
{
	//地面に着地した
	if (m_bLand == true)
	{
		//１回跳ねてる
		if (m_bBound == true)
		{
			pos.y = 0.0f;
			m_move.y = 0.0f;
		}
		//まだ跳ねてない
		else
		{
			/*Explosion(pos);
			CSound::Play(4);
			SetDeath(true);*/
			pos.y = 0.1f;
			m_move.y *= REFLECT;
			m_bBound = true;
			m_bLand = false;
		}
	}
	return pos;
}

//重力または地面との摩擦による移動量の低下
void CBomb::MoveDown()
{
	//着地してないため、重力が働く
	if (m_bLand == false)
	{
		m_move.y -= GRAVITY;
		m_bLand = CMeshField::Collision(this);
	}
	//着地してるため、摩擦が働く
	else
	{
		m_move.x *= FRICTION;
		m_move.z *= FRICTION;
	}
}

//着弾点の予測
D3DXVECTOR3 CBomb::Predict(D3DXVECTOR3 pos)
{
	int nTime = (fabsf(m_move.y) / GRAVITY) * 2;
	D3DXVECTOR3 PredictPos = D3DXVECTOR3(pos.x + m_move.x * (float)nTime, 0.0f, pos.z + m_move.z * (float)nTime);
	return PredictPos;
}