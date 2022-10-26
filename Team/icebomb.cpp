//=============================================================================
//
// •X”š’eˆ— [icebomb.h]
// Author : ŽOãq¢
//
//=============================================================================
#include "icebomb.h"
#include "collision_sphere.h"
#include "manager.h"
#include "sound.h"
//#include "renderer.h"

CIceBomb::CIceBomb(PRIORITY Priority) : CBomb(Priority)
{

}

CIceBomb::~CIceBomb()
{

}

//‰Šú‰»ˆ—
HRESULT CIceBomb::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move)
{
	CBomb::Init(pos, rot, move, BOMB_ICE);
	return S_OK;
}

//I—¹ˆ—
void CIceBomb::Uninit()
{
	CBomb::Uninit();
}

//XVˆ—
void CIceBomb::Update()
{
	if (CManager::GetPause() == false && CManager::GetCountdown() == false && CManager::GetGameEnd() == false)
	{
		CBomb::Update();
	}
}

//•`‰æˆ—
void CIceBomb::Draw()
{
	CBomb::Draw();
}

CIceBomb *CIceBomb::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move)
{
	CIceBomb *pIceBomb;
	pIceBomb = new CIceBomb(PRIORITY_BOMB);
	if (pIceBomb != NULL)
	{
		pIceBomb->Init(pos, rot, move);
	}
	return pIceBomb;
}

void CIceBomb::Explosion(D3DXVECTOR3 pos)
{
<<<<<<< HEAD
	CPresetDelaySet::Create("ICE", pos);
	CCollisionSphere::Create(pos, 150.0f, 16, 16, CCollisionSphere::COLLISION_S_TYPE::COLLISION_S_TYPE_ICE, 20.0f);
=======
	CCollisionSphere::Create(pos, 150.0f, 16, 16, CCollisionSphere::COLLISION_S_TYPE::COLLISION_S_TYPE_ICE, 10.0f);
>>>>>>> 3325abbc0704e6eb8e3c7ae592ebfb8f703983d6
}