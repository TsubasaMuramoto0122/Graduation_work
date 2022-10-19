//=============================================================================
// �`���[�g���A���Ǘ� [tutorial.cpp]
// Author : Kusakari Kakeru
//=============================================================================
//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#if 1
#include "tutorial.h"
#include "player.h"
#include "ui.h"
#include "keyboard.h"
#include "gamepad.h"
#include "sky.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"
#include "battery.h"
#include "light.h"
#include "load.h"
#include "mesh_field.h"
#include "mesh_wall.h"
#include "collision_sphere.h"
#include "sound.h"
#include "fade.h"
#endif

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define STAGE_SIZE (600.0f)

#if 1
//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CTutorial::CTutorial(PRIORITY Priority) : CScene::CScene(Priority)
{
	// �ϐ��̃N���A
	m_pKeyboard = NULL;
	memset(&m_pMeshField, NULL, sizeof(m_pMeshField));
	memset(&m_pMeshWall, NULL, sizeof(m_pMeshWall));

}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CTutorial::~CTutorial()
{

}
#endif

//*****************************************************************************
// ����������
//***************************************************************************** 
HRESULT CTutorial::Init(D3DXVECTOR3 /*pos*/)
{
	CLight::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.2f, 0.5f, -0.6f), 0);
	CLight::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(-0.6f, -0.3f, 0.3f), 1);

	//+------------------+
	//| �v���C���[�̐��� |
	//+------------------+
	CPlayer::Create(D3DXVECTOR3(-200.0f, 0.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CPlayer::PLAYER_TYPE_1P);
	CPlayer::Create(D3DXVECTOR3(200.0f, 0.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CPlayer::PLAYER_TYPE_2P);
	CPlayer::Create(D3DXVECTOR3(-200.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CPlayer::PLAYER_TYPE_3P);
	CPlayer::Create(D3DXVECTOR3(200.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CPlayer::PLAYER_TYPE_4P);

	//+----------------+
	//| �X�e�[�W�̐��� |
	//+----------------+
	m_pMeshField[0] = CMeshField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2000.0f, 0.0f, 2000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 4, 4);
	m_pMeshField[0]->SetColor(D3DCOLOR_RGBA(120, 240, 255, 255));
	m_pMeshField[1] = CMeshField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(STAGE_SIZE, 0.0f, STAGE_SIZE), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 4, 4);
	m_pMeshField[1]->SetColor(D3DCOLOR_RGBA(255, 160, 50, 255));

	m_pMeshWall[0] = CMeshWall::Create(D3DXVECTOR3(0.0f, 0.0f, STAGE_SIZE / 2), D3DXVECTOR3(STAGE_SIZE, 1000.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1, 1);
	m_pMeshWall[0]->SetColor(D3DCOLOR_RGBA(255, 155, 130, 0));
	m_pMeshWall[1] = CMeshWall::Create(D3DXVECTOR3(0.0f, 0.0f, -STAGE_SIZE / 2), D3DXVECTOR3(STAGE_SIZE, 1000.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), 1, 1);
	m_pMeshWall[1]->SetColor(D3DCOLOR_RGBA(255, 155, 130, 0));
	m_pMeshWall[2] = CMeshWall::Create(D3DXVECTOR3(STAGE_SIZE / 2, 0.0f, 0.0f), D3DXVECTOR3(STAGE_SIZE, 1000.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), 1, 1);
	m_pMeshWall[2]->SetColor(D3DCOLOR_RGBA(255, 155, 130, 0));
	m_pMeshWall[3] = CMeshWall::Create(D3DXVECTOR3(-STAGE_SIZE / 2, 0.0f, 0.0f), D3DXVECTOR3(STAGE_SIZE, 1000.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), 1, 1);
	m_pMeshWall[3]->SetColor(D3DCOLOR_RGBA(255, 155, 130, 0));



	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CTutorial::Uninit()
{
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard = NULL;
	}
	Release();
}

//*****************************************************************************
// �X�V����
//***************************************************************************** 
void CTutorial::Update()
{
#ifdef _DEBUG
	CKeyboard *pKeyboard;
	pKeyboard = CManager::GetKeyboard();

	if (pKeyboard != NULL)
	{
		if (pKeyboard->GetKey(DIK_RETURN) == true)
		{
			CFade::SetFade(CManager::MODE_TITLE);
		}

		if (pKeyboard->GetKey(DIK_F1) == true)
		{
			CCollisionSphere::SetVisual(false);
		}
		else if (pKeyboard->GetKey(DIK_F2) == true)
		{
			CCollisionSphere::SetVisual(true);
		}
	}
#endif
}

//*****************************************************************************
// �`�揈��
//***************************************************************************** 
void CTutorial::Draw()
{

}

//*****************************************************************************
// �쐬����
//*****************************************************************************
CTutorial *CTutorial::Create()
{
	CTutorial *pTutorial = NULL;
	pTutorial = new CTutorial(PRIORITY_ORBIT);		//�������m��
	//NULL�`�F�b�N
	if (pTutorial != NULL)
	{
		pTutorial->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	return pTutorial;
}