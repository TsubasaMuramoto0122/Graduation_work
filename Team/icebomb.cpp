//=============================================================================
//
// 氷爆弾処理 [icebomb.h]
// Author : 三上航世
//
//=============================================================================
#include "icebomb.h"
#include "collision_sphere.h"
#include "manager.h"
#include "sound.h"
#include "presetdelayset.h"
//#include "renderer.h"

CIceBomb::CIceBomb(PRIORITY Priority) : CBomb(Priority)
{

}

CIceBomb::~CIceBomb()
{

}

//初期化処理
HRESULT CIceBomb::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, float fFriction)
{
	CBomb::Init(pos, rot, move, BOMB_ICE, fFriction);
	return S_OK;
}

//終了処理
void CIceBomb::Uninit()
{
	CBomb::Uninit();
}

//更新処理
void CIceBomb::Update()
{
	if (CManager::GetPause() == false && CManager::GetCountdown() == false && CManager::GetGameEnd() == false)
	{
		CBomb::Update();
	}
}

//描画処理
void CIceBomb::Draw()
{
	CBomb::Draw();
}

void CIceBomb::ZTexDraw()
{
	CBomb::ZTexDraw();
}

CIceBomb *CIceBomb::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, float fFriction)
{
	CIceBomb *pIceBomb;
	pIceBomb = new CIceBomb(PRIORITY_BOMB);
	if (pIceBomb != NULL)
	{
		pIceBomb->Init(pos, rot, move, fFriction);
	}
	return pIceBomb;
}

void CIceBomb::Explosion(D3DXVECTOR3 pos)
{
	CPresetDelaySet::Create("ICE", pos);
	CCollisionSphere::Create(pos, 150.0f, 16, 16, CCollisionSphere::COLLISION_S_TYPE::COLLISION_S_TYPE_ICE, 10.0f, 0.0f);
}