//---------------------------
//Author:ŽOãq¢
//¬—”š’eˆ—(confusionbomb.cpp)
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

//‰Šú‰»ˆ—
HRESULT CConfusionBomb::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CBomb::Init(pos, rot, BOMB_ICE);
	return S_OK;
}

//I—¹ˆ—
void CConfusionBomb::Uninit()
{
	CBomb::Uninit();
}

//XVˆ—
void CConfusionBomb::Update()
{

}

//•`‰æˆ—
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