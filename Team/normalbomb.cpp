//=============================================================================
//
// •’Ê”š’eˆ— [normalbomb.h]
// Author : ŽOãq¢
//
//=============================================================================
#include "normalbomb.h"
#include "manager.h"
#include "collision_sphere.h"
#include "sound.h"
#include "presetdelayset.h"
//#include "renderer.h"

CNormalBomb::CNormalBomb(PRIORITY Priority) : CBomb(Priority)
{

}

CNormalBomb::~CNormalBomb()
{

}

//‰Šú‰»ˆ—
HRESULT CNormalBomb::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, float fFriction)
{
	CBomb::Init(pos, rot, move, BOMB_NORMAL, fFriction);
	return S_OK;
}

//I—¹ˆ—
void CNormalBomb::Uninit()
{
	CBomb::Uninit();
}

//XVˆ—
void CNormalBomb::Update()
{
	if (CManager::GetPause() == false && CManager::GetCountdown() == false && CManager::GetGameEnd() == false)
	{
		CBomb::Update();
	}
}

//•`‰æˆ—
void CNormalBomb::Draw()
{
	CBomb::Draw();
}

void CNormalBomb::ZTexDraw()
{
	CBomb::ZTexDraw();
}

CNormalBomb *CNormalBomb::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, float fFriction)
{
	CNormalBomb *pNormalBomb;
	pNormalBomb = new CNormalBomb(PRIORITY_BOMB);
	if (pNormalBomb != NULL)
	{
		pNormalBomb->Init(pos, rot, move, fFriction);
	}
	return pNormalBomb;
}

void CNormalBomb::Explosion(D3DXVECTOR3 pos)
{

	CPresetDelaySet::Create("EXPLOSION", pos);

	CPresetDelaySet::Create("NORMAL", pos);

	CCollisionSphere::Create(pos, 150.0f, 16, 16, CCollisionSphere::COLLISION_S_TYPE::COLLISION_S_TYPE_EXPLOSION, 10.0f, 0.0f);
}