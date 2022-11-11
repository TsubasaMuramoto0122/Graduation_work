//=============================================================================
//
// ç¨óêîöíeèàóù [confusionbomb.h]
// Author : éOè„çqê¢
//
//=============================================================================
#include "confusionbomb.h"
#include "collision_sphere.h"
#include "manager.h"
#include "sound.h"
<<<<<<< HEAD
#include "PresetDelaySet.h"
=======
#include "presetdelayset.h"
>>>>>>> edf369e2fe44aed194aa4aed39d2958e583283af
//#include "renderer.h"

CConfusionBomb::CConfusionBomb(PRIORITY Priority) : CBomb(Priority)
{

}

CConfusionBomb::~CConfusionBomb()
{

}

//èâä˙âªèàóù
HRESULT CConfusionBomb::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move)
{
	CBomb::Init(pos, rot, move, BOMB_CONFUSION);
	return S_OK;
}

//èIóπèàóù
void CConfusionBomb::Uninit()
{
	CBomb::Uninit();
}

//çXêVèàóù
void CConfusionBomb::Update()
{
	if (CManager::GetPause() == false && CManager::GetCountdown() == false && CManager::GetGameEnd() == false)
	{
		CBomb::Update();
	}
}

//ï`âÊèàóù
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
<<<<<<< HEAD
	CPresetDelaySet::Create("EXPLOSION", pos);
	CCollisionSphere::Create(pos, 150.0f, 16, 16, CCollisionSphere::COLLISION_S_TYPE::COLLISION_S_TYPE_CONFUSION, 10.0f);
=======
	CPresetDelaySet::Create("CONFUSION", pos);
	CCollisionSphere::Create(pos, 150.0f, 16, 16, CCollisionSphere::COLLISION_S_TYPE::COLLISION_S_TYPE_CONFUSION, 10.0f, 0.0f);
>>>>>>> edf369e2fe44aed194aa4aed39d2958e583283af
}