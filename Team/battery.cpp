//=============================================================================
//
// 砲台処理 [battery.h]
// Author : 三上航世
//
//=============================================================================
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
//マクロ
//=============================================================================
#define BOMB_SPEED (10.0f)
#define BOMB_HEIGHT (7.0f)

CBattery::CBattery(PRIORITY nPriority) : CObject(nPriority)
{

}

CBattery::~CBattery()
{

}

//初期化処理
HRESULT CBattery::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, int nTime)
{
	CObject::Init(pos, rot, move, 0);
	m_nTime = nTime;
	m_nMaxTime = nTime;
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
	if (CManager::GetPause() == false)
	{
		D3DXVECTOR3 pos = GetPos();
		D3DXVECTOR3 posOld = pos;
		D3DXVECTOR3 rot = GetRot();
		rot.y += 0.05f;
		if (m_nTime > 0)
		{
			m_nTime--;
		}
		else
		{
			m_nTime = m_nMaxTime;
			//CNormalBomb::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(sinf(rot.y) * BOMB_SPEED, BOMB_HEIGHT, cosf(rot.y) * BOMB_SPEED));
			RandomBomb(pos, rot);
		}
		SetRot(rot);
	}
}

//描画処理
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
	//生成する爆弾にランダム性を持たせる
	int nRand = rand() % CBomb::MAX_BOMB;

	D3DXVECTOR3 BombPos = D3DXVECTOR3(pos.x, pos.y + 0.1f, pos.z);

	//向いてる方向に撃てるようにする
	D3DXVECTOR3 move = D3DXVECTOR3(sinf(rot.y) * BOMB_SPEED, BOMB_HEIGHT, cosf(rot.y) * BOMB_SPEED);
	switch (nRand)
	{
	case CBomb::BOMB_NORMAL:
		CNormalBomb::Create(BombPos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), move);
		break;
	case CBomb::BOMB_ICE:
		CIceBomb::Create(BombPos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), move);
		break;
	case CBomb::BOMB_FIRE:
		CFireBomb::Create(BombPos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), move);
		break;
	case CBomb::BOMB_POISON:
		CPoisonBomb::Create(BombPos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), move);
		break;
	case CBomb::BOMB_CONFUSION:
		CConfusionBomb::Create(BombPos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), move);
		break;
	default:
		//CNormalBomb::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), move);
		break;
	}
	m_nTime = m_nMaxTime;
}