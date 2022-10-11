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
	m_bDodge = false;
	m_bAttack = false;
	m_nDodgeCount = 0;
	m_nDodgeCoolTime = 0;
	m_nAttackCount = 0;
	m_nAttackCoolTime = 0;
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
	m_bDodge = false;
	m_bRotate = false;
	m_bDodge = false;
	m_bAttack = false;
	m_nDodgeCount = 0;
	m_nDodgeCoolTime = PLAYER_DODGE_COOLTIME;
	m_nAttackCount = 0;
	m_nAttackCoolTime = PLAYER_ATTACK_COOLTIME;

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
	// �U�����Ă��Ȃ��Ȃ�
	if (m_bAttack == false)
	{
		// �������
		Dodge(pPlayer);
	}

	// ����E�U���̗��������Ă��Ȃ��Ȃ�
	if (m_bDodge == false && m_bAttack == false)
	{
		// �ړ�����
		Move();
	}

	// ������Ă��Ȃ��Ȃ�
	if (m_bDodge == false)
	{
		// �U������
		Attack(pPlayer);
	}

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
void CControlPlayer::Dodge(CPlayer *pPlayer)
{
	// �L�[�{�[�h�擾����
	CKeyboard *pKeyboard;
	pKeyboard = CManager::GetKeyboard();

	// �Q�[���p�b�h�擾����
	CGamePad *pGamePad;
	pGamePad = CManager::GetGamepad();

	// ���[�V�����擾����
	//CMotionPlayer *pMotionPlayer = NULL;
	//pMotionPlayer = pPlayer->GetMotionPlayer();

	// ��𒆂���Ȃ��Ȃ�
	if (m_bDodge == false)
	{
		// �N�[���^�C���̃J�E���g�𑝂₷
		m_nDodgeCoolTime++;

		// �N�[���^�C�����߂��Ă���Ȃ�
		if (m_nDodgeCoolTime >= PLAYER_DODGE_COOLTIME)
		{
			//***********************************************************************
			// ��� (�L�[�{�[�hShift �܂��� �p�b�hX�{�^��)
			//***********************************************************************
			if (pKeyboard->GetTrigger(DIK_LSHIFT) == true/* ||
														 pGamePad->GetTrigger(CGamePad::DIP_X) == true*/)
			{
				// ������Ă����Ԃɐݒ�
				m_bDodge = true;
			}
		}
	}
	// ���
	else if (m_bDodge == true)
	{
		// �N�[���^�C�������Z�b�g
		m_nDodgeCoolTime = 0;

		// �J�E���g�𑝂₷
		m_nDodgeCount++;

		// ������Ԃ̊ԂȂ�
		if (m_nDodgeCount <= PLAYER_DODGE_TIME)
		{
			// �v���C���[�̌������擾���A���i������
			D3DXVECTOR3 rot = pPlayer->GetRot();
			m_move.x += -sinf(rot.y) * PLAYER_DODGE;
			m_move.z += -cosf(rot.y) * PLAYER_DODGE;
		}
	
		// �����A�d�����Ԃ��߂�����
		if (m_nDodgeCount > PLAYER_DODGE_WAITTIME + PLAYER_DODGE_TIME)
		{
			// ������Ă��Ȃ���Ԃɂ���
			m_bDodge = false;
			m_nDodgeCount = 0;
		}
	}
}

//=============================================================================
// �U������
//=============================================================================
void CControlPlayer::Attack(CPlayer *pPlayer)
{
	// �L�[�{�[�h�擾����
	CKeyboard *pKeyboard;
	pKeyboard = CManager::GetKeyboard();

	// �Q�[���p�b�h�擾����
	CGamePad *pGamePad;
	pGamePad = CManager::GetGamepad();

	// ���[�V�����擾����
	//CMotionPlayer *pMotionPlayer = NULL;
	//pMotionPlayer = pPlayer->GetMotionPlayer();

	// ��𒆂���Ȃ��Ȃ�
	if (m_bAttack == false)
	{
		// �N�[���^�C���̃J�E���g�𑝂₷
		m_nAttackCoolTime++;

		// �N�[���^�C�����߂��Ă���Ȃ�
		if (m_nAttackCoolTime >= PLAYER_ATTACK_COOLTIME)
		{
			//***********************************************************************
			// �U�� (�L�[�{�[�hSpace�L�[ �܂��� �p�b�hA�{�^��)
			//***********************************************************************
			if (pKeyboard->GetTrigger(DIK_SPACE) == true/* ||
														 pGamePad->GetTrigger(CGamePad::DIP_A) == true*/)
			{
				// �U�����Ă����Ԃɐݒ�
 				m_bAttack = true;
			}
		}
	}
	// ���
	else if (m_bAttack == true)
	{
		// �N�[���^�C�������Z�b�g
		m_nAttackCoolTime = 0;

		// �J�E���g�𑝂₷
		m_nAttackCount++;

		// �U�����͓������~�߂�
		m_move.x += 0.0f;
		m_move.z += 0.0f;

		// �U�����Ԃ̊ԂȂ�
		if (m_nAttackCount <= PLAYER_ATTACK_TIME)
		{
			// �����蔻��𔭐�������

		}

		// �U����A�d�����Ԃ��߂�����
		if (m_nAttackCount > PLAYER_ATTACK_WAITTIME + PLAYER_ATTACK_TIME)
		{
			// ������Ă��Ȃ���Ԃɂ���
			m_bAttack = false;
			m_nAttackCount = 0;
		}
	}
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