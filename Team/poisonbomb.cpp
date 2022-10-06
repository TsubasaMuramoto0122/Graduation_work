//---------------------------
//Author:�O��q��
//�Ŕ��e����(poisonbomb.cpp)
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

//����������
HRESULT CPoisonBomb::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CBomb::Init(pos, rot, BOMB_POISON);
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
	
}

//�`�揈��
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