//=============================================================================
//
// ¬—”š’eˆ— [confusionbomb.h]
// Author : ŽOãq¢
//
//=============================================================================
#include "confusionbomb.h"
#include "collision_sphere.h"
#include "manager.h"
#include "sound.h"
#include "presetdelayset.h"
//#include "renderer.h"

CConfusionBomb::CConfusionBomb(PRIORITY Priority) : CBomb(Priority)
{

}

CConfusionBomb::~CConfusionBomb()
{

}

//‰Šú‰»ˆ—
HRESULT CConfusionBomb::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move)
{
	CBomb::Init(pos, rot, move, BOMB_CONFUSION);
	return S_OK;
}

//I—¹ˆ—
void CConfusionBomb::Uninit()
{
	CBomb::Uninit();
}

//XVˆ—
void CConfusionBomb::Update()
{
	if (CManager::GetPause() == false && CManager::GetCountdown() == false && CManager::GetGameEnd() == false)
	{
		CBomb::Update();
	}
}

//•`‰æˆ—
void CConfusionBomb::Draw()
{
	CBomb::Draw();
}

CConfusionBomb *CConfusionBomb::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move)
{
	CConfusionBomb *pConfusionBomb;
	pConfusionBomb = new CConfusionBomb(PRIORITY_BOMB);
	if (pConfusionBomb != NULL)
	{
		pConfusionBomb->Init(pos, rot, move);
	}
	return pConfusionBomb;
}

void CConfusionBomb::Explosion(D3DXVECTOR3 pos)
{
	CPresetDelaySet::Create("EXPLOSION", pos);
	CCollisionSphere::Create(pos, 150.0f, 16, 16, CCollisionSphere::COLLISION_S_TYPE::COLLISION_S_TYPE_CONFUSION, 10.0f, 0.0f);

}