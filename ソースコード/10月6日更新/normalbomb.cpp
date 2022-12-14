//---------------------------
//Author:三上航世
//普通爆弾処理(normalbomb.cpp)
//---------------------------
#include "normalbomb.h"
#include "manager.h"
#include "renderer.h"

CNormalBomb::CNormalBomb(PRIORITY Priority) : CBomb(Priority)
{

}

CNormalBomb::~CNormalBomb()
{

}

//初期化処理
HRESULT CNormalBomb::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CBomb::Init(pos, rot, BOMB_NORMAL);
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
	
}

//描画処理
void CNormalBomb::Draw()
{
	CBomb::Draw();
}

CNormalBomb *CNormalBomb::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CNormalBomb *pNormalBomb;
	pNormalBomb = new CNormalBomb(PRIORITY_OBJECT);
	if (pNormalBomb != NULL)
	{
		pNormalBomb->Init(pos, rot);
	}
	return pNormalBomb;
}