//---------------------------
//Author:三上航世
//砲台(battery.cpp)
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

//初期化処理
HRESULT CBattery::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move)
{

	return S_OK;
}

//終了処理
void CBattery::Uninit()
{
	CObject::Uninit();
}

//更新処理
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

//描画処理
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