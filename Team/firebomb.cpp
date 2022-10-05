//---------------------------
//Author:�O��q��
//�����e����(firebomb.cpp)
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

//����������
HRESULT CFireBomb::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CBomb::Init(pos, rot, BOMB_ICE);
	return S_OK;
}

//�I������
void CFireBomb::Uninit()
{
	CBomb::Uninit();
}

//�X�V����
void CFireBomb::Update()
{

}

//�`�揈��
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