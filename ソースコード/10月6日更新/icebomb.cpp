//---------------------------
//Author:三上航世
//普通爆弾処理(normalbomb.cpp)
//---------------------------
#include "icebomb.h"
#include "manager.h"
#include "renderer.h"

CIceBomb::CIceBomb(PRIORITY Priority) : CBomb(Priority)
{

}

CIceBomb::~CIceBomb()
{

}

//初期化処理
HRESULT CIceBomb::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CBomb::Init(pos, rot, BOMB_ICE);
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

}

//描画処理
void CIceBomb::Draw()
{
	CBomb::Draw();
}

CIceBomb *CIceBomb::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CIceBomb *pIceBomb;
	pIceBomb = new CIceBomb(PRIORITY_OBJECT);
	if (pIceBomb != NULL)
	{
		pIceBomb->Init(pos, rot);
	}
	return pIceBomb;
}