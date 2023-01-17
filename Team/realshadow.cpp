//=============================================================================
//
// ���A���ȉe [realshadow.h]
// Author : �O��q��
//
//=============================================================================
#include "realshadow.h"
#include "manager.h"
#include "renderer.h"

// �R���X�g���N�^
CRealShadow::CRealShadow()
{
}


// �f�X�g���N�^
CRealShadow::~CRealShadow()
{
}


// ���������\�b�h
bool CRealShadow::Init()
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice();     //�f�o�C�X���擾����

	// ���\�[�X�ɂ���[�x�o�b�t�@�V���h�E�V�F�[�_�v���O������ǂݍ���
//#if _DEBUG
	if (FAILED(D3DXCreateEffectFromFile(pDevice, "data/FILES/DepthBufShadowEffect.fx", NULL, NULL, 0, NULL, &m_pEffect, NULL)))
	{
		return false;
	}
//#else
//	if (FAILED(D3DXCreateEffectFromResource(
//		cpDev.GetPtr(),
//		NULL,
//		MAKEINTRESOURCE(FXID_DEPTHBUFSHADOW),
//		NULL,
//		NULL,
//		0,
//		NULL,
//		m_cpEffect.ToCreator(),
//		NULL)))
//		return false;
//#endif

	m_hWorldMat = m_pEffect->GetParameterByName(NULL, "matWorld");
	m_hCameraViewMat = m_pEffect->GetParameterByName(NULL, "matCameraView");
	m_hCameraProjMat = m_pEffect->GetParameterByName(NULL, "matCameraProj");
	m_hLightViewMat = m_pEffect->GetParameterByName(NULL, "matLightView");
	m_hLightProjMat = m_pEffect->GetParameterByName(NULL, "matLightProj");
	m_hShadowMapTex = m_pEffect->GetParameterByName(NULL, "texShadowMap");
	m_hTechnique = m_pEffect->GetTechniqueByName("DepthBufShadowTec");

	if (m_hWorldMat == NULL || m_hCameraViewMat == NULL || m_hCameraProjMat == NULL
		|| m_hLightViewMat == NULL || m_hLightProjMat == NULL || m_hShadowMapTex == NULL || m_hTechnique == NULL)
	{
		return false;
	}
	return true;
}

CRealShadow *CRealShadow::Create()
{
	CRealShadow *pRealShadow;
	pRealShadow = new CRealShadow;
	if (pRealShadow != NULL)
	{
		pRealShadow->Init();
	}
	return pRealShadow;
}

// �V���h�E�}�b�v��ݒ�
bool CRealShadow::SetShadowMap(IDirect3DTexture9 *pShadowMap)
{
	m_pShadowMapTex = pShadowMap;
	return true;
}


// �`��ΏۃI�u�W�F�N�g�̃��[���h�ϊ��s���ݒ�
void CRealShadow::SetWorldMatrix(D3DXMATRIX pMat)
{
	m_matWorld = pMat;
}

// �J�����̃r���[�s���ݒ�
void CRealShadow::SetCameraViewMatrix(D3DXMATRIX pMat)
{
	m_matCameraView = pMat;
}

// �J�����̎ˉe�ϊ��s���ݒ�
void CRealShadow::SetCameraProjMatrix(D3DXMATRIX pMat)
{
	m_matCameraProj = pMat;
}

// ���C�g�̃r���[�s���ݒ�
void CRealShadow::SetLightViewMatrix(D3DXMATRIX pMat)
{
	m_matLightView = pMat;
}

// ���C�g�̎ˉe�ϊ��s���ݒ�
void CRealShadow::SetLightProjMatrix(D3DXMATRIX pMat)
{
	m_matLightProj = pMat;
}

// �`��̊J�n��錾����
HRESULT CRealShadow::Begin()
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice();     //�f�o�C�X���擾����

	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	pDevice->Clear(0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 160, 0), 1.0f, 0); //�w�i�̐F��ς����

	// �v���O���}�u���V�F�[�_�ɐ؂�ւ�
	m_pEffect->SetTechnique(m_hTechnique);

	// �J�n�錾
	UINT Pass;
	m_pEffect->Begin(&Pass, 0);

	return S_OK;
}

// �`��̏I����錾����
HRESULT CRealShadow::End()
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice();     //�f�o�C�X���擾����

	m_pEffect->End();

	// �Œ�@�\�ɖ߂�
	pDevice->SetVertexShader(NULL);
	pDevice->SetPixelShader(NULL);
	
	return S_OK;
}

// �p�X�̊J�n��錾����
HRESULT CRealShadow::BeginPass()
{
	m_pEffect->BeginPass(0);	// �p�X��1�̂�
	return S_OK;
}

// �p�X�̏I����錾����
HRESULT CRealShadow::EndPass()
{
	m_pEffect->EndPass();
	return S_OK;
}


// �o�^����Ă���p�����[�^�����G�t�F�N�g�ɃZ�b�g
bool CRealShadow::SetParamToEffect()
{
	m_pEffect->SetMatrix(m_hWorldMat, &m_matWorld);
	m_pEffect->SetMatrix(m_hCameraViewMat, &m_matCameraView);
	m_pEffect->SetMatrix(m_hCameraProjMat, &m_matCameraProj);
	m_pEffect->SetMatrix(m_hLightViewMat, &m_matLightView);
	m_pEffect->SetMatrix(m_hLightProjMat, &m_matLightProj);

	m_pEffect->SetTexture(m_hShadowMapTex, m_pShadowMapTex);
	return true;
}