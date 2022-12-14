//=============================================================================
//
// 炎爆弾処理 [firebomb.h]
// Author : 三上航世
//
//=============================================================================
#include "firebomb.h"
#include "collision_sphere.h"
#include "manager.h"
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
	if (CManager::GetPause() == false)
	{
		CBomb::Update();
	}
}

//描画処理
void CFireBomb::Draw()
{
	CBomb::Draw();
}

CFireBomb *CFireBomb::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move)
{
	CFireBomb *pFireBomb;
	pFireBomb = new CFireBomb(PRIORITY_OBJECT);
	if (pFireBomb != NULL)
	{
		pFireBomb->Init(pos, rot, move);
	}
	return pFireBomb;
}

void CFireBomb::Explosion(D3DXVECTOR3 pos)
{
	CCollisionSphere::Create(pos, 150.0f, 16, 16, CCollisionSphere::COLLISION_S_TYPE::COLLISION_S_TYPE_EXPLOSION, 8.0f);
}