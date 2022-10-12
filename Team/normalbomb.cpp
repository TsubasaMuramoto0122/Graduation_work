//=============================================================================
//
// 普通爆弾処理 [normalbomb.h]
// Author : 三上航世
//
//=============================================================================
#include "normalbomb.h"
#include "manager.h"
#include "collision_sphere.h"
//#include "renderer.h"

CNormalBomb::CNormalBomb(PRIORITY Priority) : CBomb(Priority)
{

}

CNormalBomb::~CNormalBomb()
{

}

//初期化処理
HRESULT CNormalBomb::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move)
{
	CBomb::Init(pos, rot, move, BOMB_NORMAL);
	m_pCollisionSphere = CCollisionSphere::Create(pos, 200.0f, 16, 16, CCollisionSphere::COLLISION_S_TYPE_EXPLOSION, 1.0f);
	return S_OK;
}

//終了処理
void CNormalBomb::Uninit()
{
	if (m_pCollisionSphere != NULL)
	{
		m_pCollisionSphere->SetDeath(true);
		m_pCollisionSphere = NULL;
	}
	CBomb::Uninit();
}

//更新処理
void CNormalBomb::Update()
{
	if (CManager::GetPause() == false)
	{
		CBomb::Update();
	}
}

//描画処理
void CNormalBomb::Draw()
{
	CBomb::Draw();
}

CNormalBomb *CNormalBomb::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move)
{
	CNormalBomb *pNormalBomb;
	pNormalBomb = new CNormalBomb(PRIORITY_OBJECT);
	if (pNormalBomb != NULL)
	{
		pNormalBomb->Init(pos, rot, move);
	}
	return pNormalBomb;
}

void CNormalBomb::Explosion()
{
	//m_pCollisionSphere = CCollisionSphere::Create(GetPos(), D3DXVECTOR3(400.0f, 400.0f, 400.0f), 16, 16, CCollisionSphere::COLLISION_S_TYPE_EXPLOSION, 1.0f);
}