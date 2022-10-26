//=============================================================================
//
// ‰Š”š’eˆ— [firebomb.h]
// Author : ŽOãq¢
//
//=============================================================================
#include "firebomb.h"
#include "collision_sphere.h"
#include "manager.h"
#include "sound.h"
//#include "renderer.h"

CFireBomb::CFireBomb(PRIORITY Priority) : CBomb(Priority)
{

}

CFireBomb::~CFireBomb()
{

}

//‰Šú‰»ˆ—
HRESULT CFireBomb::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move)
{
	CBomb::Init(pos, rot, move, BOMB_FIRE);
	return S_OK;
}

//I—¹ˆ—
void CFireBomb::Uninit()
{
	CBomb::Uninit();
}

//XVˆ—
void CFireBomb::Update()
{
	if (CManager::GetPause() == false && CManager::GetCountdown() == false && CManager::GetGameEnd() == false)
	{
		CBomb::Update();
	}
}

//•`‰æˆ—
void CFireBomb::Draw()
{
	CBomb::Draw();
}

CFireBomb *CFireBomb::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move)
{
	CFireBomb *pFireBomb;
	pFireBomb = new CFireBomb(PRIORITY_BOMB);
	if (pFireBomb != NULL)
	{
		pFireBomb->Init(pos, rot, move);
	}
	return pFireBomb;
}

void CFireBomb::Explosion(D3DXVECTOR3 pos)
{
<<<<<<< HEAD
	CPresetDelaySet::Create("FIRE", pos);
	CCollisionSphere::Create(pos, 150.0f, 16, 16, CCollisionSphere::COLLISION_S_TYPE::COLLISION_S_TYPE_EXPLOSION, 20.0f);
=======
	CCollisionSphere::Create(pos, 150.0f, 16, 16, CCollisionSphere::COLLISION_S_TYPE::COLLISION_S_TYPE_EXPLOSION, 10.0f);
>>>>>>> 3325abbc0704e6eb8e3c7ae592ebfb8f703983d6
}