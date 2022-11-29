//=============================================================================
//
// 炎爆弾処理 [firebomb.h]
// Author : 三上航世
//
//=============================================================================
#include "firebomb.h"
#include "collision_sphere.h"
#include "manager.h"
#include "sound.h"
#include "presetdelayset.h"
//#include "renderer.h"

CFireBomb::CFireBomb(PRIORITY Priority) : CBomb(Priority)
{

}

CFireBomb::~CFireBomb()
{

}

//初期化処理
HRESULT CFireBomb::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move)
{
	CBomb::Init(pos, rot, move, BOMB_FIRE);
	return S_OK;
}

//終了処理
void CFireBomb::Uninit()
{
	CBomb::Uninit();
}

//更新処理
void CFireBomb::Update()
{
	if (CManager::GetPause() == false && CManager::GetCountdown() == false && CManager::GetGameEnd() == false)
	{
		CBomb::Update();
	}
}

//描画処理
void CFireBomb::Draw()
{
	CBomb::Draw();
}

void CFireBomb::ZTexDraw()
{
	CBomb::ZTexDraw();
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
	CPresetDelaySet::Create("FIRE", pos);

	//現状、爆発と火柱のダメージ量は変わらない
	CCollisionSphere::Create(pos, 150.0f, 16, 16, CCollisionSphere::COLLISION_S_TYPE::COLLISION_S_TYPE_EXPLOSION, 100.0f, 0.0f);
}