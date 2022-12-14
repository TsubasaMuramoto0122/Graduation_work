//---------------------------
//Author:三上航世
//毒爆弾処理(poisonbomb.cpp)
//---------------------------
#include "poisonbomb.h"
#include "manager.h"
#include "renderer.h"

CPoisonBomb::CPoisonBomb(PRIORITY Priority) : CBomb(Priority)
{

}

CPoisonBomb::~CPoisonBomb()
{

}

//初期化処理
HRESULT CPoisonBomb::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CBomb::Init(pos, rot, BOMB_POISON);
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
	
}

//描画処理
void CPoisonBomb::Draw()
{
	CBomb::Draw();
}

CPoisonBomb *CPoisonBomb::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CPoisonBomb *pPoisonBomb;
	pPoisonBomb = new CPoisonBomb(PRIORITY_OBJECT);
	if (pPoisonBomb != NULL)
	{
		pPoisonBomb->Init(pos, rot);
	}
	return pPoisonBomb;
}