//---------------------------
//Author:�O��q��
//�X���e����(icebomb.cpp)
//---------------------------
#include "icebomb.h"
#include "manager.h"
#include "renderer.h"

CIceBomb::CIceBomb(PRIORITY Priority) : CBomb(Priority)
{

}

CIceBomb::~CIceBomb()
{

}

//����������
HRESULT CIceBomb::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CBomb::Init(pos, rot, BOMB_ICE);
	return S_OK;
}

//�I������
void CIceBomb::Uninit()
{
	CBomb::Uninit();
}

//�X�V����
void CIceBomb::Update()
{

}

//�`�揈��
void CIceBomb::Draw()
{
	CBomb::Draw();
}

CIceBomb *CIceBomb::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CIceBomb *pIceBomb;
	pIceBomb = new CIceBomb(PRIORITY_OBJECT);
	if (pIceBomb != NULL)
	{
		pIceBomb->Init(pos, rot);
	}
	return pIceBomb;
}