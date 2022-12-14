// ZTexCreator.cpp (2007. 2. 28)

// Z�l�e�N�X�`�������N���X������

//

#include "ztex.h"
#include "manager.h"
#include "renderer.h"
#include "resource.h"

// �R���X�g���N�^
CZTex::CZTex()
{
	
}

// �f�X�g���N�^
CZTex::~CZTex()
{
	
}


// ���������\�b�h
bool CZTex::Init(UINT ZTexWidth, UINT ZTexHeight, D3DFORMAT ZTexFormat)
{
	if (ZTexWidth == 0 || ZTexHeight == 0)
	{
		return false;
	}

	HRESULT hr;

	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice();     //�f�o�C�X���擾����

	if (FAILED(D3DXCreateEffectFromFile(pDevice, "data/FILES/ZTexCreator.fx", NULL, NULL, 0, NULL, &m_pEffect, NULL)))
	{
		return false;
	}

	// �G�t�F�N�g���̊e��p�����[�^�n���h�����擾
	m_hWorldMat = m_pEffect->GetParameterByName(NULL, "matWorld");
	m_hViewMat = m_pEffect->GetParameterByName(NULL, "matView");
	m_hProjMat = m_pEffect->GetParameterByName(NULL, "matProj");
	m_hTechnique = m_pEffect->GetTechniqueByName("ZValuePlotTec");
	if (m_hWorldMat == NULL || m_hViewMat == NULL || m_hProjMat == NULL || m_hTechnique == NULL)
	{
		return false;
	}
	// �w���Z�l�e�N�X�`���𐶐�
	hr = D3DXCreateTexture(pDevice, ZTexWidth, ZTexHeight, 1, D3DUSAGE_RENDERTARGET, ZTexFormat, D3DPOOL_DEFAULT, &m_pZTex);
	if (FAILED(hr))
	{
		return false;
	}

	m_pZTex->GetSurfaceLevel(0, &m_pZTexSurf);	// �T�[�t�F�C�X�擾

	// �`��f�o�C�X�ɒ�`����Ă���o�b�t�@�̔\�͂��擾
	IDirect3DSurface9 *pSurf;
	pDevice->GetDepthStencilSurface(&pSurf);
	D3DSURFACE_DESC Desc;
	pSurf->GetDesc(&Desc);
	pSurf->Release();

	// �Ǝ��[�x�o�b�t�@���쐬
	hr = pDevice->CreateDepthStencilSurface(ZTexWidth, ZTexHeight, Desc.Format, Desc.MultiSampleType, Desc.MultiSampleQuality, FALSE, &m_pDepthBuff, NULL);
	if (FAILED(hr))
	{
		return false;
	}
	return true;
}

CZTex *CZTex::Create(UINT ZTexWidth, UINT ZTexHeight, D3DFORMAT ZTexFormat)
{
	CZTex *pZTex;
	pZTex = new CZTex;
	if (pZTex != NULL)
	{
		pZTex->Init(ZTexWidth, ZTexHeight, ZTexFormat);
	}
	return pZTex;
}


// �`��ΏۃI�u�W�F�N�g�̃��[���h�ϊ��s���ݒ�
void CZTex::SetWorldMatrix(D3DXMATRIX *pMat)
{
	m_matWorld = *pMat;
}


// �r���[�s���ݒ�
void CZTex::SetViewMatrix(D3DXMATRIX *pMat)
{
	m_matView = *pMat;
}


// �ˉe�ϊ��s���ݒ�
void CZTex::SetProjMatrix(D3DXMATRIX *pMat)
{
	m_matProj = *pMat;
}


// �`��̊J�n��錾����
HRESULT CZTex::Begin()
{
	// ���������������s���Ă��邩�`�F�b�N
	if (m_pDepthBuff == NULL || m_pZTexSurf == NULL)
	{
		return E_FAIL;
	}

	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice();     //�f�o�C�X���擾����

	// �f�o�C�X�������Ă���o�b�t�@���ꎞ�ۑ�
	pDevice->GetRenderTarget(0, &m_pDevBuffer);
	pDevice->GetDepthStencilSurface(&m_pDevDepth);

	// �f�o�C�X��Z�l�e�N�X�`���T�[�t�F�C�X�Ɛ[�x�o�b�t�@��ݒ�
	pDevice->SetRenderTarget(0, m_pZTexSurf);
	pDevice->SetDepthStencilSurface(m_pDepthBuff);

	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	pDevice->Clear(0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 160, 0), 1.0f, 0); //�w�i�̐F��ς����

	// �v���O���}�u���V�F�[�_�̃e�N�j�b�N��ݒ�
	m_pEffect->SetTechnique(m_hTechnique);

	// �V�F�[�_�̊J�n��錾
	UINT Tmp;
	m_pEffect->Begin(&Tmp, 0);

	return S_OK;
}

// �p�X�̊J�n��錾����
HRESULT CZTex::BeginPass()
{
	m_pEffect->BeginPass(0);	// Z�l�v�Z��1�p�X
	return S_OK;
}

// �o�^����Ă���p�����[�^�����G�t�F�N�g�ɃZ�b�g
bool CZTex::SetParamToEffect()
{
	if (m_pEffect == NULL)
	{
		return false;
	}

	m_pEffect->SetMatrix(m_hWorldMat, &m_matWorld);
	m_pEffect->SetMatrix(m_hViewMat, &m_matView);
	m_pEffect->SetMatrix(m_hProjMat, &m_matProj);

	return true;
}

// �p�X�̏I����錾����
HRESULT CZTex::EndPass()
{
	m_pEffect->EndPass();
	return S_OK;
}

// �`��̏I����錾����
HRESULT CZTex::End()
{
	m_pEffect->End();

	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice();     //�f�o�C�X���擾����

	// �f�o�C�X�Ɍ��̃T�[�t�F�C�X��߂�
	pDevice->SetRenderTarget(0, m_pDevBuffer);
	pDevice->SetDepthStencilSurface(m_pDevDepth);

	m_pDevBuffer = NULL;
	m_pDevDepth = NULL;

	// �Œ�@�\�ɖ߂�
	pDevice->SetVertexShader(NULL);
	pDevice->SetPixelShader(NULL);

	return S_OK;
}