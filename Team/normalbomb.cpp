//=============================================================================
//
// •’Ê”š’eˆ— [normalbomb.h]
// Author : ŽOãq¢
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

//‰Šú‰»ˆ—
HRESULT CNormalBomb::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move)
{
	CBomb::Init(pos, rot, move, BOMB_NORMAL);
	//m_pCollisionSphere = CCollisionSphere::Create(GetPos(), GetRadius() * 6.0f, 16, 16, CCollisionSphere::COLLISION_S_TYPE_EXPLOSION, 1000.0f);
	return S_OK;
}

//I—¹ˆ—
void CNormalBomb::Uninit()
{
	if (m_pCollisionSphere != NULL)
	{
		m_pCollisionSphere->SetDeath(true);
		m_pCollisionSphere = NULL;
	}
	CBomb::Uninit();
}

//XVˆ—
void CNormalBomb::Update()
{
	if (CManager::GetPause() == false)
	{
		CBomb::Update();
		//m_pCollisionSphere->SetPosCollision(GetPos());
	}
}

//•`‰æˆ—
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

void CNormalBomb::Explosion(D3DXVECTOR3 pos)
{
	CCollisionSphere::Create(pos, 150.0f, 16, 16, CCollisionSphere::COLLISION_S_TYPE::COLLISION_S_TYPE_EXPLOSION, 8.0f);
}