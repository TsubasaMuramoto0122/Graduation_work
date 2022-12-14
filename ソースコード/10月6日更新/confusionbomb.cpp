//---------------------------
//Author:三上航世
//混乱爆弾処理(confusionbomb.cpp)
//---------------------------
#include "confusionbomb.h"
#include "manager.h"
#include "renderer.h"

CConfusionBomb::CConfusionBomb(PRIORITY Priority) : CBomb(Priority)
{

}

CConfusionBomb::~CConfusionBomb()
{

}

//初期化処理
HRESULT CConfusionBomb::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CBomb::Init(pos, rot, BOMB_CONFUSION);
	return S_OK;
}

//終了処理
void CConfusionBomb::Uninit()
{
	CBomb::Uninit();
}

//更新処理
void CConfusionBomb::Update()
{

}

//描画処理
void CConfusionBomb::Draw()
{
	CBomb::Draw();
}

CConfusionBomb *CConfusionBomb::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CConfusionBomb *pConfusionBomb;
	pConfusionBomb = new CConfusionBomb(PRIORITY_OBJECT);
	if (pConfusionBomb != NULL)
	{
		pConfusionBomb->Init(pos, rot);
	}
	return pConfusionBomb;
}