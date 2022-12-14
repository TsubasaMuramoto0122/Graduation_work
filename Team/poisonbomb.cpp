//=============================================================================
//
// 毒爆弾処理 [poisonbomb.h]
// Author : 三上航世
//
//=============================================================================
#include "poisonbomb.h"
#include "collision_sphere.h"
#include "manager.h"
#include "sound.h"
#include "presetdelayset.h"
//#include "renderer.h"

CPoisonBomb::CPoisonBomb(PRIORITY Priority) : CBomb(Priority)
{

}

CPoisonBomb::~CPoisonBomb()
{

}

//初期化処理
HRESULT CPoisonBomb::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, float fFriction)
{
	CBomb::Init(pos, rot, move, BOMB_POISON, fFriction);
	return S_OK;
}

//終了処理
void CPoisonBomb::Uninit()
{
	CBomb::Uninit();
}

//更新処理
void CPoisonBomb::Update()
{
	if (CManager::GetPause() == false && CManager::GetCountdown() == false && CManager::GetGameEnd() == false)
	{
		CBomb::Update();
	}
}

//描画処理
void CPoisonBomb::Draw()
{
	CBomb::Draw();
}

void CPoisonBomb::ZTexDraw()
{
	CBomb::ZTexDraw();
}

CPoisonBomb *CPoisonBomb::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, float fFriction)
{
	CPoisonBomb *pPoisonBomb;
	pPoisonBomb = new CPoisonBomb(PRIORITY_BOMB);
	if (pPoisonBomb != NULL)
	{
		pPoisonBomb->Init(pos, rot, move, fFriction);
	}
	return pPoisonBomb;
}

void CPoisonBomb::Explosion(D3DXVECTOR3 pos)
{
	CPresetDelaySet::Create("POISON", pos);
	CCollisionSphere::Create(pos, 150.0f, 16, 16, CCollisionSphere::COLLISION_S_TYPE::COLLISION_S_TYPE_POISON, 10.0f, 0.0f);
	CCollisionSphere::Create(pos, 150.0f, 16, 16, CCollisionSphere::COLLISION_S_TYPE::COLLISION_S_TYPE_POISON_FIELD, 130.0f, 0.0f);
}