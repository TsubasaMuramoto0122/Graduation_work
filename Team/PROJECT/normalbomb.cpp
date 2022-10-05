//---------------------------
//Author:ŽOãq¢
//•’Ê”š’eˆ—(normalbomb.cpp)
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

//‰Šú‰»ˆ—
HRESULT CNormalBomb::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CBomb::Init(pos, rot, BOMB_NORMAL);
	return S_OK;
}

//I—¹ˆ—
void CNormalBomb::Uninit()
{
	CBomb::Uninit();
}

//XVˆ—
void CNormalBomb::Update()
{
	
}

//•`‰æˆ—
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