//---------------------------
//Author:ŽOãq¢
//‰Š”š’eˆ—(firebomb.cpp)
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

//‰Šú‰»ˆ—
HRESULT CFireBomb::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CBomb::Init(pos, rot, BOMB_ICE);
	return S_OK;
}

//I—¹ˆ—
void CFireBomb::Uninit()
{
	CBomb::Uninit();
}

//XVˆ—
void CFireBomb::Update()
{

}

//•`‰æˆ—
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