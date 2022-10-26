//=============================================================================
//
// �Ŕ��e���� [poisonbomb.h]
// Author : �O��q��
//
//=============================================================================
#include "poisonbomb.h"
#include "collision_sphere.h"
#include "manager.h"
#include "sound.h"
#include "PresetDelaySet.h"
//#include "renderer.h"

CPoisonBomb::CPoisonBomb(PRIORITY Priority) : CBomb(Priority)
{

}

CPoisonBomb::~CPoisonBomb()
{

}

//����������
HRESULT CPoisonBomb::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move)
{
	CBomb::Init(pos, rot, move, BOMB_POISON);
	return S_OK;
}

//�I������
void CPoisonBomb::Uninit()
{
	CBomb::Uninit();
}

//�X�V����
void CPoisonBomb::Update()
{
	if (CManager::GetPause() == false && CManager::GetCountdown() == false && CManager::GetGameEnd() == false)
	{
		CBomb::Update();
	}
}

//�`�揈��
void CPoisonBomb::Draw()
{
	CBomb::Draw();
}

CPoisonBomb *CPoisonBomb::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move)
{
	CPoisonBomb *pPoisonBomb;
	pPoisonBomb = new CPoisonBomb(PRIORITY_BOMB);
	if (pPoisonBomb != NULL)
	{
		pPoisonBomb->Init(pos, rot, move);
	}
	return pPoisonBomb;
}

void CPoisonBomb::Explosion(D3DXVECTOR3 pos)
{
	CPresetDelaySet::Create("POISON", pos);
	CCollisionSphere::Create(pos, 150.0f, 16, 16, CCollisionSphere::COLLISION_S_TYPE::COLLISION_S_TYPE_POISON, 20.0f);
}