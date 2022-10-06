//---------------------------
//Author:ŽOãq¢
//–C‘ä(battery.cpp)
//---------------------------
#include "battery.h"
#include "manager.h"
#include "renderer.h"

CBattery::CBattery(PRIORITY nPriority) : CObject(nPriority)
{

}

CBattery::~CBattery()
{

}

//‰Šú‰»ˆ—
HRESULT CBattery::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move)
{

	return S_OK;
}

//I—¹ˆ—
void CBattery::Uninit()
{
	CObject::Uninit();
}

//XVˆ—
void CBattery::Update()
{
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 posOld = pos;
	D3DXVECTOR3 rot = GetRot();
	bool bPause = CManager::GetPause();

	if (bPause == false)
	{

	}
}

//•`‰æˆ—
void CBattery::Draw()
{
	CObject::Draw();
}

CBattery *CBattery::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move)
{
	CBattery *pBattery;
	pBattery = new CBattery(CScene::PRIORITY_OBJECT);
	if (pBattery != NULL)
	{
		pBattery->Init(pos, rot, move);
	}
	return pBattery;
}