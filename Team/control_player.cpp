//=============================================================================
// �v���C���[���쏈�� [control_player.cpp]
// Author : Kusakari Kakeru
//=============================================================================
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "control_player.h"
#include "manager.h"
#include "keyboard.h"
#include "gamepad.h"
#include "player.h"
//#include "motion_player.h"
#include "camera.h"
#include "sound.h"
#include "model.h"
#include "player.h"
#include "renderer.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CControlPlayer::CControlPlayer()
{
	// �ϐ��̃N���A
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_moveOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fObjectiveRot = 0.0f;
	m_fNumRot = 0.0f;
	m_fSpeed = 0.0f;
	m_bRotate = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CControlPlayer::~CControlPlayer()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CControlPlayer::Init(void)
{
	// �ϐ��̏�����
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_moveOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fObjectiveRot = 0.0f;
	m_fNumRot = 0.0f;
	m_fSpeed = PLAYER_MOVE_SPEED;
	m_bRotate = false;

	//// �e�L�X�g�ۑ��p�̕ϐ�
	//char cString[MAX_STRING];
	//// �e�L�X�g�t�@�C���̓ǂݍ���
	//FILE *pFile = fopen("data/TEXT/motion_player.txt", "r");
	//if (pFile != NULL)
	//{
	//	while (fgets(cString, MAX_STRING, pFile) != NULL)
	//	{
	//		// �������ۑ�
	//		fscanf(pFile, "%s", cString);
	//		// ������̒���"CHARACTERSET"����������
	//		if (strncmp("CHARACTERSET", cString, 12) == 0)
	//		{
	//			break;
	//		}
	//	}
	//	while (fgets(cString, MAX_STRING, pFile) != NULL)
	//	{
	//		// �������ۑ�
	//		fscanf(pFile, "%s", cString);
	//		// ������̒���"MOVE"����������
	//		if (strncmp("MOVE", cString, 5) == 0)
	//		{
	//			// �ړ��̑������擾����
	//			fscanf(pFile, "%s%f%*s%*s", cString, &m_fSpeed);
	//			// ��{�̑������ݒ肵�Ă���
	//			m_fBasicSpeed = m_fSpeed;
	//			// �W�����v�͂��擾
	//			fscanf(pFile, "%s%*s%f%*s%*s%*s", cString, &m_fJump);
	//			break;
	//		}
	//	}
	//	while (fgets(cString, MAX_STRING, pFile) != NULL)
	//	{
	//		// �������ۑ�
	//		fscanf(pFile, "%s", cString);
	//		// ������̒���"END_CHARACTERSET"���������炻���ŏI��
	//		if (strncmp("END_CHARACTERSET", cString, 17) == 0)
	//		{
	//			break;
	//		}
	//	}
	//	// �t�@�C�������
	//	fclose(pFile);
	//}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CControlPlayer::Uninit(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void CControlPlayer::Update(CScene *pScene)
{
	// �����̃|�C���^���v���C���[�N���X�̃|�C���^�ɃL���X�g
	CPlayer *pPlayer = NULL;
	pPlayer = (CPlayer*)pScene;

	// �T�E���h�擾����

	// �L�[�{�[�h�擾����
	CKeyboard *pKeyboard;
	pKeyboard = CManager::GetKeyboard();

	// �Q�[���p�b�h�擾����
	CGamePad *pGamePad;
	pGamePad = CManager::GetGamepad();

	// �ړ��ʂ�ݒ�
	m_move = pPlayer->GetMove();
	m_moveOld = m_move;

	//---------------------------------------------------
	// �d��
	//---------------------------------------------------
	//m_move.y -= PLAYER_GRAVITY;

	//// �d�͂������Ȃ肷������d�͂̍ő�l�ŌŒ肵�Ă���
	//if (m_move.y <= -PLAYER_MAX_GRAVITY)
	//{
	//	m_move.y = -PLAYER_MAX_GRAVITY;
	//}

	//---------------------------------------------------
	// ��{�A�N�V����
	//---------------------------------------------------
	// �ړ�����(�ڂ��������͊֐��̒�)
	Move();

	//---------------------------------------------------
	// ���[�V�����J��
	//---------------------------------------------------

	//---------------------------------------------------
	// ����
	//---------------------------------------------------
	// �ړ��̊���(�ڂ��������͊֐��̒�)
	MoveInteria();

	// ��]�̊���(�ڂ��������͊֐��̒�)
	Rotate(pPlayer);

}

//=============================================================================
// ��������
//=============================================================================
CControlPlayer *CControlPlayer::Create(void)
{
	// �C���X�^���X�̐���
	CControlPlayer *pControlPlayer = NULL;

	// �k���`�F�b�N
	if (pControlPlayer == NULL)
	{
		// �N���X�̐���
		pControlPlayer = new CControlPlayer;
		if (pControlPlayer != NULL)
		{
			// ����������
			pControlPlayer->Init();
		}
	}

	return pControlPlayer;
}

//=============================================================================
// �ړ�����
//=============================================================================
void CControlPlayer::Move(void)
{
	// �L�[�{�[�h�擾����
	CKeyboard *pKeyboard;
	pKeyboard = CManager::GetKeyboard();

	// �Q�[���p�b�h�擾����
	CGamePad *pGamePad;
	pGamePad = CManager::GetGamepad();

	// �J�����̎擾
	CCamera *pCamera = CManager::GetRenderer()->GetCamera();
	float rotCamera = 0.0f;

	if (pCamera != NULL)
	{
		// �J�����̌����擾
		rotCamera = pCamera->GetRotY();
	}

	//***********************************************************************
	// �ړ� (�L�[�{�[�h�v/�`/�r/�c �܂��� �p�b�h���X�e�B�b�N)
	//***********************************************************************
	//���ړ�
	if (pKeyboard->GetPress(DIK_A) == true /*||
										   pGamePad->LeftStickX() > 0*/)
	{
		//�����ړ�
		if (pKeyboard->GetPress(DIK_W) == true /*||
											   pGamePad->LeftStickY() > 0*/)
		{
			//�ړ��ʉ��Z
			m_move.x += -cosf(rotCamera + D3DX_PI / 4.0f) * m_fSpeed;
			m_move.z += +sinf(rotCamera + D3DX_PI / 4.0f) * m_fSpeed;

			//�ړI�̌�����ݒ�
			m_fObjectiveRot = rotCamera + D3DX_PI / 1.5f;
			//��]�̊������I���ɂ���
			m_bRotate = true;
		}
		//����O�ړ�
		else if (pKeyboard->GetPress(DIK_S) == true /*||
													pGamePad->LeftStickY() < 0*/)
		{
			//�ړ��ʉ��Z
			m_move.x += -cosf(rotCamera - D3DX_PI / 4.0f) * m_fSpeed;
			m_move.z += +sinf(rotCamera - D3DX_PI / 4.0f) * m_fSpeed;

			//�ړI�̌�����ݒ�
			m_fObjectiveRot = rotCamera + D3DX_PI / 4.0f;
			//��]�̊������I���ɂ���
			m_bRotate = true;
		}
		else
		{
			//�ړ��ʉ��Z
			m_move.x += -cosf(rotCamera) * m_fSpeed;
			m_move.z += +sinf(rotCamera) * m_fSpeed;

			//�ړI�̌�����ݒ�
			m_fObjectiveRot = rotCamera + D3DX_PI / 2.0f;
			//��]�̊������I���ɂ���
			m_bRotate = true;
		}
	}
	//�E�ړ�
	else if (pKeyboard->GetPress(DIK_D) == true /*||
												pGamePad->LeftStickX() < 0*/)
	{
		//�E���ړ�
		if (pKeyboard->GetPress(DIK_W) == true /*||
											   pGamePad->LeftStickY() > 0*/)
		{
			//�ړ��ʉ��Z
			m_move.x += +cosf(rotCamera - D3DX_PI / 4.0f) * m_fSpeed;
			m_move.z += -sinf(rotCamera - D3DX_PI / 4.0f) * m_fSpeed;

			//�ړI�̌�����ݒ�
			m_fObjectiveRot = rotCamera - (D3DX_PI / 4.0f) * 3.0f;
			//��]�̊������I���ɂ���
			m_bRotate = true;
		}
		//�E��O�ړ�
		else if (pKeyboard->GetPress(DIK_S) == true /*||
													pGamePad->LeftStickY() < 0*/)
		{
			//�ړ��ʉ��Z
			m_move.x += +cosf(rotCamera + D3DX_PI / 4.0f) * m_fSpeed;
			m_move.z += -sinf(rotCamera + D3DX_PI / 4.0f) * m_fSpeed;

			//�ړI�̌�����ݒ�
			m_fObjectiveRot = rotCamera - D3DX_PI / 4.0f;
			//��]�̊������I���ɂ���
			m_bRotate = true;
		}
		else
		{
			//�ړ��ʉ��Z
			m_move.x += +cosf(rotCamera) * m_fSpeed;
			m_move.z += -sinf(rotCamera) * m_fSpeed;

			//�ړI�̌�����ݒ�
			m_fObjectiveRot = rotCamera - D3DX_PI / 2.0f;
			//��]�̊������I���ɂ���
			m_bRotate = true;
		}
	}
	//���ړ�
	else if (pKeyboard->GetPress(DIK_W) == true /*||
												pGamePad->LeftStickY() > 0*/)
	{
		//�ړ��ʉ��Z
		m_move.z += +cosf(rotCamera) * m_fSpeed;
		m_move.x += +sinf(rotCamera) * m_fSpeed;

		//�ړI�̌�����ݒ�
		m_fObjectiveRot = rotCamera + D3DX_PI;
		//��]�̊������I���ɂ���
		m_bRotate = true;
	}
	//��O�ړ�
	else if (pKeyboard->GetPress(DIK_S) == true /*||
												pGamePad->LeftStickY() < 0*/)
	{
		//�ړ��ʉ��Z
		m_move.z += -cosf(rotCamera) * m_fSpeed;
		m_move.x += -sinf(rotCamera) * m_fSpeed;

		//�ړI�̌�����ݒ�
		m_fObjectiveRot = rotCamera;
		//��]�̊������I���ɂ���
		m_bRotate = true;
	}
}

//=============================================================================
// �������
//=============================================================================
void CControlPlayer::Dodge(void)
{

}

//=============================================================================
// �ړ��̊����ɂ��Ă̏���
//=============================================================================
void CControlPlayer::MoveInteria(void)
{
	// �����̌��Z
	m_move.z *= PLAYER_INTERIA_SUBTRACTION;
	m_move.x *= PLAYER_INTERIA_SUBTRACTION;

	// �ړ��ʂ�����̒l�ɂȂ�����0�ɂ���
	if (m_move.x <= PLAYER_MOVE_STOP_COUNT && m_move.x >= -PLAYER_MOVE_STOP_COUNT)
	{
		m_move.x = 0.0f;
	}
	if (m_move.z <= PLAYER_MOVE_STOP_COUNT && m_move.z >= -PLAYER_MOVE_STOP_COUNT)
	{
		m_move.z = 0.0f;
	}
}

//=============================================================================
// ��]����
//=============================================================================
void CControlPlayer::Rotate(CPlayer *pPlayer)
{
	// �v���C���[�̌������擾
	D3DXVECTOR3 rotPlayer = pPlayer->GetRot();

	// ��]�������ԂȂ�
	if (m_bRotate == true)
	{
		// �ړI�̌������v�Z
		if (m_fObjectiveRot > D3DX_PI)
		{
			m_fObjectiveRot = -D3DX_PI - (D3DX_PI - m_fObjectiveRot);
		}
		else if (m_fObjectiveRot < -D3DX_PI)
		{
			m_fObjectiveRot = D3DX_PI - (-D3DX_PI - m_fObjectiveRot);
		}

		// �v���C���[�̌��݂̌������Ƃɂ��ꂼ�������ς���ʂ��v�Z
		if (rotPlayer.y < 0.0f && -rotPlayer.y + m_fObjectiveRot > D3DX_PI)
		{
			m_fNumRot = (-D3DX_PI - rotPlayer.y) + -(D3DX_PI - m_fObjectiveRot);
		}
		else if (rotPlayer.y >= D3DX_PI / 2.0f && rotPlayer.y - m_fObjectiveRot > D3DX_PI)
		{
			m_fNumRot = (D3DX_PI - rotPlayer.y) - (-D3DX_PI - m_fObjectiveRot);
		}
		else
		{
			m_fNumRot = (m_fObjectiveRot - rotPlayer.y);
		}

		// �v���C���[�̌����ɉ��Z
		rotPlayer.y += m_fNumRot * 0.2f;

		// ����̒l�ɒB�������]����߂�
		if (rotPlayer.y - m_fObjectiveRot < 0.001f && rotPlayer.y - m_fObjectiveRot > -0.001f)
		{
			m_bRotate = false;
		}
	}

	// ������3.14����-3.14�̒l�͈͓̔��Ɏ��߂�
	if (rotPlayer.y > D3DX_PI)
	{
		rotPlayer.y -= D3DX_PI * 2.0f;
	}
	else if (rotPlayer.y < -D3DX_PI)
	{
		rotPlayer.y += D3DX_PI * 2.0f;
	}

	// �����𔽉f
	pPlayer->SetRot(rotPlayer);
}