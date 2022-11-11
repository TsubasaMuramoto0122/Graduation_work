//=============================================================================
//
// ïÅí îöíeèàóù [normalbomb.h]
// Author : éOè„çqê¢
//
//=============================================================================
#include "normalbomb.h"
#include "manager.h"
#include "collision_sphere.h"
#include "sound.h"
<<<<<<< HEAD
#include "PresetDelaySet.h"
=======
#include "presetdelayset.h"
>>>>>>> edf369e2fe44aed194aa4aed39d2958e583283af
//#include "renderer.h"

CNormalBomb::CNormalBomb(PRIORITY Priority) : CBomb(Priority)
{

}

CNormalBomb::~CNormalBomb()
{

}

//èâä˙âªèàóù
HRESULT CNormalBomb::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move)
{
	CBomb::Init(pos, rot, move, BOMB_NORMAL);
	return S_OK;
}

//èIóπèàóù
void CNormalBomb::Uninit()
{
	CBomb::Uninit();
}

//çXêVèàóù
void CNormalBomb::Update()
{
	if (CManager::GetPause() == false && CManager::GetCountdown() == false && CManager::GetGameEnd() == false)
	{
		CBomb::Update();
	}
}

//ï`âÊèàóù
void CNormalBomb::Draw()
{
	CBomb::Draw();
}

CNormalBomb *CNormalBomb::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move)
{
	CNormalBomb *pNormalBomb;
	pNormalBomb = new CNormalBomb(PRIORITY_BOMB);
	if (pNormalBomb != NULL)
	{
		pNormalBomb->Init(pos, rot, move);
	}
	return pNormalBomb;
}

void CNormalBomb::Explosion(D3DXVECTOR3 pos)
{
<<<<<<< HEAD
	CPresetDelaySet::Create("EXPLOSION", pos);
	CCollisionSphere::Create(pos, 150.0f, 16, 16, CCollisionSphere::COLLISION_S_TYPE::COLLISION_S_TYPE_EXPLOSION, 10.0f);
=======
	CPresetDelaySet::Create("NORMAL", pos);
	CCollisionSphere::Create(pos, 150.0f, 16, 16, CCollisionSphere::COLLISION_S_TYPE::COLLISION_S_TYPE_EXPLOSION, 10.0f, 0.0f);
>>>>>>> edf369e2fe44aed194aa4aed39d2958e583283af
}