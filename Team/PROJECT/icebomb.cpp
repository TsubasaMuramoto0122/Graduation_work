//---------------------------
//Author:ŽOãq¢
//•X”š’eˆ—(icebomb.cpp)
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

//‰Šú‰»ˆ—
HRESULT CIceBomb::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CBomb::Init(pos, rot, BOMB_ICE);
	return S_OK;
}

//I—¹ˆ—
void CIceBomb::Uninit()
{
	CBomb::Uninit();
}

//XVˆ—
void CIceBomb::Update()
{

}

//•`‰æˆ—
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