//=============================================================================
//
// �����͈͏��� [danger.h]
// Author : �O��q��
//
//=============================================================================
#include "danger.h"
#include "manager.h"
#include "renderer.h"

CDanger::CDanger(PRIORITY Priority) : CPlane::CPlane(Priority)
{

}

CDanger::~CDanger()
{

}

//����������
HRESULT CDanger::Init(D3DXVECTOR3 size, D3DXVECTOR3 pos)
{
	CPlane::Init(size, pos, D3DXVECTOR2(1.0f, 1.0f), false);
	ChangeColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	m_size = size;
	return S_OK;
}

//�I������
void CDanger::Uninit()
{
	CPlane::Uninit();
}

//�X�V����
void CDanger::Update()
{
	if (CManager::GetPause() == false && CManager::GetCountdown() == false && CManager::GetGameEnd() == false)
	{

	}
}

//�`�揈��
void CDanger::Draw()
{
	//LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	//pDevice = CManager::GetRenderer()->GetDevice();     //�f�o�C�X���擾����
	////���Z�����̐ݒ�
	//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	//CPlane::Draw();
	////�ʏ퍇���ɖ߂�
	//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	CPlane::Draw();
}

CDanger *CDanger::Create(D3DXVECTOR3 size, D3DXVECTOR3 pos)
{
	CDanger *pDanger;
	pDanger = new CDanger(PRIORITY_CHARA);
	if (pDanger != NULL)
	{
		pDanger->Init(size, pos);
		pDanger->SetTexture(1);
	}
	return pDanger;
}

void CDanger::Move(D3DXVECTOR3 pos)
{
	SetPos(D3DXVECTOR3(pos.x, 0.1f, pos.z));
}