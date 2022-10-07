//---------------------------
//Author:ŽOãq¢
//–C‘ä(battery.cpp)
//---------------------------
#include "battery.h"
#include "manager.h"
//#include "renderer.h"

#include "bomb.h"
#include "icebomb.h"
#include "normalbomb.h"
#include "confusionbomb.h"
#include "poisonbomb.h"
#include "firebomb.h"

//=============================================================================
//ƒ}ƒNƒ
//=============================================================================
#define BOMB_SPEED (4.0f)
#define BOMB_HEIGHT (7.0f)

CBattery::CBattery(PRIORITY nPriority) : CObject(nPriority)
{

}

CBattery::~CBattery()
{

}

//‰Šú‰»ˆ—
HRESULT CBattery::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, int nTime)
{
	CObject::Init(pos, rot, move, 0);
	m_nTime = nTime;
	m_nMaxTime = nTime;
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
		//rot.y += 0.05f;
		if (m_nTime > 0)
		{
			m_nTime--;
		}
		else
		{
			m_nTime = m_nMaxTime;
			CNormalBomb::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(sinf(rot.y) * BOMB_SPEED, BOMB_HEIGHT, cosf(rot.y) * BOMB_SPEED));
			//RandomBomb(pos, rot);
		}
		SetRot(rot);
	}
}

//•`‰æˆ—
void CBattery::Draw()
{
	CObject::Draw();
}

CBattery *CBattery::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, int nTime)
{
	CBattery *pBattery;
	pBattery = new CBattery(CScene::PRIORITY_OBJECT);
	if (pBattery != NULL)
	{
		pBattery->Init(pos, rot, move, nTime);
	}
	return pBattery;
}

void CBattery::RandomBomb(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int nRand = rand() % CBomb::MAX_BOMB;
	D3DXVECTOR3 move = D3DXVECTOR3(sinf(rot.y) * BOMB_SPEED, BOMB_HEIGHT, cosf(rot.y) * BOMB_SPEED);
	switch (nRand)
	{
	case CBomb::BOMB_NORMAL:
		CNormalBomb::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), move);
		break;
	case CBomb::BOMB_ICE:
		CIceBomb::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), move);
		break;
	case CBomb::BOMB_FIRE:
		CFireBomb::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), move);
		break;
	case CBomb::BOMB_POISON:
		CPoisonBomb::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), move);
		break;
	case CBomb::BOMB_CONFUSION:
		CConfusionBomb::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), move);
		break;
	default:
		break;
	}
	m_nTime = m_nMaxTime;
}