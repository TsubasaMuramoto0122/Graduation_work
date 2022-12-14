//=============================================================================
//
// 普通爆弾処理 [normalbomb.h]
// Author : 三上航世
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

//初期化処理
HRESULT CNormalBomb::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, float fFriction)
{
	CBomb::Init(pos, rot, move, BOMB_NORMAL, fFriction);
	return S_OK;
}

//終了処理
void CNormalBomb::Uninit()
{
	CBomb::Uninit();
}

//更新処理
void CNormalBomb::Update()
{
	if (CManager::GetPause() == false && CManager::GetCountdown() == false && CManager::GetGameEnd() == false)
	{
		CBomb::Update();
	}
}

//描画処理
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
	CPresetDelaySet::Create("NORMAL", pos);
	CCollisionSphere::Create(pos, 150.0f, 16, 16, CCollisionSphere::COLLISION_S_TYPE::COLLISION_S_TYPE_EXPLOSION, 10.0f, 0.0f);
}