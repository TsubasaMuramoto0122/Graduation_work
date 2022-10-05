//---------------------------
// Author:�O��q��
// �{�����ӂ̊댯���(danger.cpp)
//---------------------------
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

}

//�`�揈��
void CDanger::Draw()
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice();     //�f�o�C�X���擾����
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
	pDanger = new CDanger(PRIORITY_EFFECT);
	if (pDanger != NULL)
	{
		pDanger->Init(size, pos);
		pDanger->SetTexture(1);
	}
	return pDanger;
}

void CDanger::MoveY(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_fPosY = pos.y + 0.1f;
	SetPos(D3DXVECTOR3(pos.x, m_fPosY, pos.z));
	SetRot(D3DXVECTOR3(rot.x, 0.0f, rot.z));
}