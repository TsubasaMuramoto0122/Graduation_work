//=============================================================================
// 3D�G�t�F�N�g���� [BillEffect.cpp]
// Author : �����G��
//=============================================================================
#include "billEffect.h"
#include "manager.h"
#include "renderer.h"

#include "control.h"
//=============================================================================
// �}�N
//=============================================================================
#define MAX_COLOR (255)


//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBillEffect::CBillEffect(PRIORITY nPriority) : CEffect_base::CEffect_base(nPriority)
{
	m_Color = {};
	m_MinColor = {};
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBillEffect::~CBillEffect()
{

}

//=============================================================================
// ������
//=============================================================================
HRESULT CBillEffect::Init(D3DXVECTOR3 Size,
	D3DXVECTOR3 MinSize,
	D3DCOLORVALUE color,
	D3DCOLORVALUE Mincolor,
	int nTex, int nLife,
	D3DXVECTOR2 TexNum,
	D3DXVECTOR2 TexMove,
	int nAnimCounter,
	D3DXVECTOR2 nSplit,
	ANIMPATTERN AnimPattern)
{
	CEffect_base::Init(Size, D3DXVECTOR3(0.0f, 0.0f, 0.0f), TexNum);
	SetTexture(nTex);


	m_Size = Size;			//�傫��
	m_MinSize = MinSize;	//�傫���ϓ�

	m_TexSize = TexMove;

	//�J���[
	m_Color = color;

	m_MaxSplit = nSplit;
	m_PatternSize = D3DXVECTOR2(1.0f / m_MaxSplit.x, 1.0f / m_MaxSplit.y);
	m_nAnimCount = nAnimCounter;
	m_nSetAnimCnt = nAnimCounter;
	m_AnimPattern = AnimPattern;

	if (m_MaxSplit.x <= 0)
	{
		m_MaxSplit.x = 1;
	}
	if (m_MaxSplit.y <= 0)
	{
		m_MaxSplit.y = 1;
	}

	float SplitU = float(rand() % (int)m_MaxSplit.x) + 1;
	float SplitV = float(rand() % (int)m_MaxSplit.y) + 1;


	if (m_AnimPattern == ANIMPATTERN_RAND)
	{
		m_nSplit.x = SplitU;
		m_nSplit.y = SplitV;
	}


	//�J���[�ϓ�
	m_MinColor = Mincolor;

	m_nLife = nLife;
	m_bUninit = false;

	CEffect_base::ColorChange(m_Color);
	CEffect_base::TexturMove(m_TexSize);
	CEffect_base::SetTexAnim(m_nSplit, m_PatternSize);

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CBillEffect::Uninit()
{
	CEffect_base::Uninit();
}

//=============================================================================
// �X�V
//=============================================================================
void CBillEffect::Update()
{

	//�J���[�ύX
	m_Color.r += m_MinColor.r;
	m_Color.g += m_MinColor.g;
	m_Color.b += m_MinColor.b;
	m_Color.a += m_MinColor.a;


	//�J���[�l��0������肻��
	if (m_Color.r <= 0)
	{
		m_Color.r = 0;
	}
	if (m_Color.g <= 0)
	{
		m_Color.g = 0;
	}
	if (m_Color.b <= 0)
	{
		m_Color.b = 0;
	}
	if (m_Color.a <= 0)
	{
		m_Color.a = 0;
	}



	//�J���[�l��MAX_COLOR�����肻��
	if (m_Color.r >= MAX_COLOR)
	{
		m_Color.r = MAX_COLOR;
	}
	if (m_Color.g >= MAX_COLOR)
	{
		m_Color.g = MAX_COLOR;
	}
	if (m_Color.b >= MAX_COLOR)
	{
		m_Color.b = MAX_COLOR;
	}
	if (m_Color.a >= MAX_COLOR)
	{
		m_Color.a = MAX_COLOR;
	}

	switch (m_AnimPattern)
	{
	case(ANIMPATTERN_NOMAL):
		//�e�N�X�`���A�j���[�V����
		if (m_nAnimCount >= 0)
		{
			m_nAnimCount--;
			if (m_nAnimCount < 0)
			{
				m_nAnimCount = m_nSetAnimCnt;
				m_nSplit.x++;
				m_nSplit.y++;
			}
			if (m_MaxSplit > m_MaxSplit)
			{
				m_nSplit.x = 0;
				m_nSplit.y = 0;
			}
		}
		break;
	case(ANIMPATTERN_RAND):
		////�e�N�X�`���A�j���[�V����
		//if (m_nAnimCount >= 0)
		//{
		//	m_nAnimCount--;
		//	if (m_nAnimCount < 0)
		//	{
		//		m_nAnimCount = m_nSetAnimCnt;
		//		m_nSplit.x++;
		//		m_nSplit.y++;
		//	}
		//	if (m_MaxSplit > m_MaxSplit)
		//	{
		//		m_nSplit.x = 0;
		//		m_nSplit.y = 0;
		//	}
		//}

		break;
	default:
		//�e�N�X�`���A�j���[�V����
		if (m_nAnimCount >= 0)
		{
			m_nAnimCount--;
			if (m_nAnimCount < 0)
			{
				m_nAnimCount = m_nSetAnimCnt;
				m_nSplit.x++;
				m_nSplit.y++;
			}
			if (m_MaxSplit > m_MaxSplit)
			{
				m_nSplit.x = 0;
				m_nSplit.y = 0;
			}
		}
		break;
	}

	//���ꂼ��K��
	CEffect_base::ColorChange(m_Color);
	CEffect_base::TexturMove(m_TexSize);
	CEffect_base::SetTexAnim(m_nSplit, m_PatternSize);

	//��������
	m_nLife--;
	if (m_nLife <= 0)
	{
		m_bUninit = true;
	}

	//����
	if (m_bUninit == true)
	{
		Uninit();
	}
}

//=============================================================================
// �`��
//=============================================================================
void CBillEffect::Draw()
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxView;
	D3DXMATRIX mtxTrans, mtxWorld; //�v�Z�p�}�g���b�N�X
	pDevice = CManager::GetRenderer()->GetDevice();     //�f�o�C�X���擾����


	// Z�e�X�g�֌W
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	// �A���t�@�e�X�g�֌W
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	if (m_nSynthenic == 0)
	{
		// ���Z�����֌W
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}
	else if (m_nSynthenic == 1)
	{
		// ���Z�����̐ݒ�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}
	else if (m_nSynthenic == 2)
	{
		// �����g�p����
	}
	// ����ȊO�̐��l�͉��Z������
	else
	{
		// ���Z�����֌W
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}
	// ���C���e�B���O�𖳎�����
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// �r���[�}�g���b�N�X���擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	// �|���S�����J�����ɑ΂��Đ��ʂɌ�����
	D3DXMatrixInverse(&mtxWorld, NULL, &mtxView); //�t�s������߂�

	mtxWorld._41 = 0.0f;
	mtxWorld._42 = 0.0f;
	mtxWorld._43 = 0.0f;

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	SetMatrix(mtxWorld);
	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, GetVtx(), 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->SetTexture(0, m_pTexture[m_nTexType]);    //�e�N�X�`���̐ݒ�

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,  // �J�n����n�_�̃C���f�b�N�X
		2); // �`�悷��v���~�e�B�u��

	// Z�e�X�g�֌W
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// �A���t�@�e�X�g�֌W
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);

	// �ʏ퍇���ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// ���C���e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// �ʒu�ɂ���Ă͉f��Ȃ��悤�ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

}

//=============================================================================
// �|���S���e�N�X�`���Z�b�g
//=============================================================================
void CBillEffect::SetTexture(int nTex)
{
	m_nTexType = nTex;
}
