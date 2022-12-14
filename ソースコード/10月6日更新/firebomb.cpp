//---------------------------
//Author:三上航世
//炎爆弾処理(firebomb.cpp)
//---------------------------
#include "firebomb.h"
#include "manager.h"
#include "renderer.h"

CFireBomb::CFireBomb(PRIORITY Priority) : CBomb(Priority)
{

}

CFireBomb::~CFireBomb()
{

}

//初期化処理
HRESULT CFireBomb::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CBomb::Init(pos, rot, BOMB_FIRE);
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

}

//描画処理
void CFireBomb::Draw()
{
	CBomb::Draw();
}

CFireBomb *CFireBomb::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CFireBomb *pFireBomb;
	pFireBomb = new CFireBomb(PRIORITY_OBJECT);
	if (pFireBomb != NULL)
	{
		pFireBomb->Init(pos, rot);
	}
	return pFireBomb;
}