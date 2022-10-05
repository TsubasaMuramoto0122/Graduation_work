//---------------------------
//Author:ŽOãq¢
//“Å”š’eˆ—(poisonbomb.cpp)
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

//‰Šú‰»ˆ—
HRESULT CPoisonBomb::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CBomb::Init(pos, rot, BOMB_ICE);
	return S_OK;
}

//I—¹ˆ—
void CPoisonBomb::Uninit()
{
	CBomb::Uninit();
}

//XVˆ—
void CPoisonBomb::Update()
{
	
}

//•`‰æˆ—
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