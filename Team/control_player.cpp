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
#include "collision_sphere.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CControlPlayer::CControlPlayer()
{
	// �ϐ��̃N���A
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fObjectiveRot = 0.0f;
	m_fNumRot = 0.0f;
	m_fSpeed = 0.0f;
	m_bRotate = false;
	m_bJump = false;
	m_bAttack = false;
	m_bDamage = false;
	//m_bDodge = false;
	m_nAttackCount = 0;
	m_nAttackCoolTime = 0;
	m_nStanCount = 0;
	//m_nDodgeCount = 0;
	//m_nDodgeCoolTime = 0;
	m_pCollision = NULL;
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
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fObjectiveRot = 0.0f;
	m_fNumRot = 0.0f;
	m_fSpeed = PLAYER_MOVE_SPEED;
	m_bRotate = false;
	m_bJump = false;
	m_bAttack = false;
	m_bDamage = false;
	//m_bDodge = false;
	m_nAttackCount = 0;
	m_nAttackCoolTime = PLAYER_ATTACK_COOLTIME;
	m_nStanCount = 0;
	//m_nDodgeCount = 0;
	//m_nDodgeCoolTime = PLAYER_DODGE_COOLTIME;
	m_pCollision = NULL;

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

	//---------------------------------------------------
	// �d��
	//---------------------------------------------------
	if (m_bDamage == true && pPlayer->GetLand() == false)
	{
		m_move.y -= PLAYER_GRAVITY_DAMAGE;
	}
	else if (pPlayer->GetDefeat() == true)
	{
		m_move.y -= PLAYER_GRAVITY_DEFEAT;
	}
	else
	{
		m_move.y -= PLAYER_GRAVITY;
	}

	// �d�͂������Ȃ肷������d�͂̍ő�l�ŌŒ肵�Ă���
	if (m_move.y <= -PLAYER_MAX_GRAVITY)
	{
		m_move.y = -PLAYER_MAX_GRAVITY;
	}

	// �s�k���Ă��Ȃ�������
	if (pPlayer->GetDefeat() == false)
	{
		// ��_���[�W����
		TakeDamage(pPlayer);

		//---------------------------------------------------
		// ��{�A�N�V����
		//---------------------------------------------------
		// ��_���[�W��Ԃ���Ȃ��Ȃ�
		if (m_bDamage == false)
		{
			// �U�����Ă��Ȃ��Ȃ�
			if (m_bAttack == false)
			{
				// �ړ�����
				Move(pPlayer);

				// �W�����v����
				Jump(pPlayer);
			}

			// �U������
			Attack(pPlayer);
		}
	}

	// �������
	//Dodge(pPlayer);

	// �s�k���̏���
	Defeat(pPlayer);

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
void CControlPlayer::Move(CPlayer *pPlayer)
{
	// �L�[�{�[�h�擾����
	CKeyboard *pKeyboard;
	pKeyboard = CManager::GetKeyboard();

	// �Q�[���p�b�h�擾����
	CGamePad *pGamePad;
	pGamePad = CManager::GetGamepad();

	// �J�����̌������擾
	CCamera *pCamera = CManager::GetRenderer()->GetCamera();
	float rotCamera = pCamera->GetRotY();

	// ���͏��𕪂���
	int nLeft = 0, nRight = 0, nUp = 0, nDown = 0, nPlayerNum = 0;
	nPlayerNum = (int)pPlayer->GetType();
	switch (pPlayer->GetType())
	{
	case CPlayer::PLAYER_TYPE_1P:
		nLeft = DIK_A;
		nRight = DIK_D;
		nUp = DIK_W;
		nDown = DIK_S;
		break;
	case CPlayer::PLAYER_TYPE_2P:
		nLeft = DIK_LEFT;
		nRight = DIK_RIGHT;
		nUp = DIK_UP;
		nDown = DIK_DOWN;
		break;
	case CPlayer::PLAYER_TYPE_3P:
		break;
	case CPlayer::PLAYER_TYPE_4P:
		break;
	default:
		break;
	}

	//***********************************************************************
	// �ړ� (�L�[�{�[�h�v/�`/�r/�c �܂��� �p�b�h���X�e�B�b�N)
	//***********************************************************************
	//���ړ�
	if (pKeyboard->GetPress(nLeft) == true ||
		pGamePad->GetPress(CGamePad::PAD_INPUTTYPE_LSTICK_LEFT, nPlayerNum) == true)
	{
		//�����ړ�
		if (pKeyboard->GetPress(nUp) == true ||
			pGamePad->GetPress(CGamePad::PAD_INPUTTYPE_LSTICK_UP, nPlayerNum) == true)
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
		else if (pKeyboard->GetPress(nDown) == true ||
			pGamePad->GetPress(CGamePad::PAD_INPUTTYPE_LSTICK_DOWN, nPlayerNum) == true)
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
	else if (pKeyboard->GetPress(nRight) == true ||
		pGamePad->GetPress(CGamePad::PAD_INPUTTYPE_LSTICK_RIGHT, nPlayerNum) == true)
	{
		//�E���ړ�
		if (pKeyboard->GetPress(nUp) == true ||
			pGamePad->GetPress(CGamePad::PAD_INPUTTYPE_LSTICK_UP, nPlayerNum) == true)
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
		else if (pKeyboard->GetPress(nDown) == true ||
			pGamePad->GetPress(CGamePad::PAD_INPUTTYPE_LSTICK_DOWN, nPlayerNum) == true)
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
	else if (pKeyboard->GetPress(nUp) == true ||
		pGamePad->GetPress(CGamePad::PAD_INPUTTYPE_LSTICK_UP, nPlayerNum) == true)
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
	else if (pKeyboard->GetPress(nDown) == true ||
		pGamePad->GetPress(CGamePad::PAD_INPUTTYPE_LSTICK_DOWN, nPlayerNum) == true)
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
// �W�����v����
//=============================================================================
void CControlPlayer::Jump(CPlayer *pPlayer)
{
	// �L�[�{�[�h�擾����
	CKeyboard *pKeyboard;
	pKeyboard = CManager::GetKeyboard();

	// �Q�[���p�b�h�擾����
	CGamePad *pGamePad;
	pGamePad = CManager::GetGamepad();

	// ���[�V�����擾����
	/*CMotionPlayer *pMotionPlayer = NULL;
	pMotionPlayer = pPlayer->GetMotionPlayer();*/

	// ���͏��𕪂���
	int nJump = 0, nPlayerNum = 0;
	switch (pPlayer->GetType())
	{
	case CPlayer::PLAYER_TYPE_1P:
		nJump = DIK_SPACE;
		nPlayerNum = 0;
		break;
	case CPlayer::PLAYER_TYPE_2P:
		nJump = DIK_RCONTROL;
		nPlayerNum = 1;
		break;
	case CPlayer::PLAYER_TYPE_3P:
		nPlayerNum = 2;
		break;
	case CPlayer::PLAYER_TYPE_4P:
		nPlayerNum = 3;
		break;
	default:
		break;
	}

	// �v���C���[�����n���Ă���Ȃ�
	if (pPlayer->GetLand() == true)
	{
		//***********************************************************************
		// �W�����v (�L�[�{�[�hSpace �܂��� �p�b�hA�{�^��)
		//***********************************************************************
		if (pKeyboard->GetTrigger(nJump) == true ||
			pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_A, nPlayerNum) == true)
		{
			// Y�����̈ړ��ʂ�0��
			m_move.y = 0.0f;

			// �ړ��ʂ��W�����v�͂Ԃ���Z
			m_move.y = PLAYER_JUMP;

			// �W�����v�������A���n���Ă��Ȃ��ɐݒ�
			m_bJump = true;
			pPlayer->SetLand(false);

			m_bJump = true;
		}
		else
		{
			// ���n������܂��W�����v���\�ɂ���
			m_bJump = false;
		}
	}
}

//=============================================================================
// �������
//=============================================================================
//void CControlPlayer::Dodge(CPlayer *pPlayer)
//{
//	// �L�[�{�[�h�擾����
//	CKeyboard *pKeyboard;
//	pKeyboard = CManager::GetKeyboard();
//
//	// �Q�[���p�b�h�擾����
//	CGamePad *pGamePad;
//	pGamePad = CManager::GetGamepad();
//
//	// ���[�V�����擾����
//	//CMotionPlayer *pMotionPlayer = NULL;
//	//pMotionPlayer = pPlayer->GetMotionPlayer();
//
//	// ��𒆂���Ȃ��Ȃ�
//	if (m_bDodge == false)
//	{
//		// �N�[���^�C���̃J�E���g�𑝂₷
//		m_nDodgeCoolTime++;
//
//		// �N�[���^�C�����߂��Ă���Ȃ�
//		if (m_nDodgeCoolTime >= PLAYER_DODGE_COOLTIME)
//		{
//			//***********************************************************************
//			// ��� 
//			//***********************************************************************
//			if (pKeyboard->GetTrigger(DIK_LSHIFT) == true/* ||
//														 pGamePad->GetTrigger(CGamePad::DIP_X) == true*/)
//			{
//				// ������Ă����Ԃɐݒ�
//				m_bDodge = true;
//			}
//		}
//	}
//	// ���
//	else if (m_bDodge == true)
//	{
//		// �N�[���^�C�������Z�b�g
//		m_nDodgeCoolTime = 0;
//
//		// �J�E���g�𑝂₷
//		m_nDodgeCount++;
//
//		// ������Ԃ̊ԂȂ�
//		if (m_nDodgeCount <= PLAYER_DODGE_TIME)
//		{
//			// �v���C���[�̌������擾���A���i������
//			D3DXVECTOR3 rot = pPlayer->GetRot();
//			m_move.x += -sinf(rot.y) * PLAYER_DODGE;
//			m_move.z += -cosf(rot.y) * PLAYER_DODGE;
//		}
//
//		// �����A�d�����Ԃ��߂�����
//		if (m_nDodgeCount > PLAYER_DODGE_WAITTIME + PLAYER_DODGE_TIME)
//		{
//			// ������Ă��Ȃ���Ԃɂ���
//			m_bDodge = false;
//			m_nDodgeCount = 0;
//		}
//	}
//}

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

	// ���͏��𕪂���
	int nAttack = 0, nPlayerNum = 0;
	switch (pPlayer->GetType())
	{
	case CPlayer::PLAYER_TYPE_1P:
		nAttack = DIK_LSHIFT;
		nPlayerNum = 0;
		break;
	case CPlayer::PLAYER_TYPE_2P:
		nAttack = DIK_RSHIFT;
		nPlayerNum = 1;
		break;
	case CPlayer::PLAYER_TYPE_3P:
		nPlayerNum = 2;
		break;
	case CPlayer::PLAYER_TYPE_4P:
		nPlayerNum = 3;
		break;
	default:
		break;
	}

	// ��𒆂���Ȃ��Ȃ�
	if (m_bAttack == false)
	{
		// �N�[���^�C���̃J�E���g�𑝂₷
		m_nAttackCoolTime++;

		// �N�[���^�C�����߂��Ă���Ȃ�
		if (m_nAttackCoolTime >= PLAYER_ATTACK_COOLTIME)
		{
			//***********************************************************************
			// �U�� (�L�[�{�[�hSpace�L�[ �܂��� �p�b�hB�{�^��)
			//***********************************************************************
			if (pKeyboard->GetTrigger(nAttack) == true ||
				pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_B, nPlayerNum) == true)
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

		// �U�����͓������~�߂�
		m_move.x = 0.0f;
		m_move.z = 0.0f;

		// �U�����Ԃ̊ԂȂ�
		if (m_nAttackCount <= PLAYER_ATTACK_TIME)
		{
			if (m_nAttackCount == 0)
			{
				// �����蔻��𔭐�������
				D3DXVECTOR3 pos = pPlayer->GetPos();
				m_pCollision = CCollisionSphere::Create(D3DXVECTOR3(pos.x, pos.y + pPlayer->GetRadius(), pos.z), pPlayer->GetRadius() * 3.0f,
					16, 16, CCollisionSphere::COLLISION_S_TYPE::COLLISION_S_TYPE_ATTACK, PLAYER_ATTACK_TIME);
				// �ǂ̃v���C���[�̍U�����ݒ�
				m_pCollision->SetNumPlayer(pPlayer->GetType());
			}
		}

		// �J�E���g�𑝂₷
		m_nAttackCount++;

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
// ��_���[�W����
//=============================================================================
void CControlPlayer::TakeDamage(CPlayer *pPlayer)
{
	// �v���C���[�̏�Ԃ�<�������>�ɂȂ������A�_���[�W���󂯂Ă��Ȃ�������
	if (pPlayer->GetState() == CPlayer::PLAYER_STATE_BLOWAWAY && m_bDamage == false)
	{
		// �_���[�W���󂯂���Ԃɂ��A���n���Ă��Ȃ���Ԃɂ���
		m_bDamage = true;
		pPlayer->SetLand(false);

		// �ړI�̌�����ݒ�
		D3DXVECTOR3 rot = pPlayer->GetRot();
		m_fObjectiveRot = rot.y;
	}

	// �_���[�W��
	if (m_bDamage == true)
	{
		// ���n���Ă��Ȃ��Ȃ�
		if (pPlayer->GetLand() == false)
		{
			// �v���C���[�̐��ʂ���t�����֌�ނ�����
			D3DXVECTOR3 rot = pPlayer->GetRot();
			m_move.x = sinf(rot.y) * PLAYER_KNOCKBACK;
			m_move.z = cosf(rot.y) * PLAYER_KNOCKBACK;
		}
		// ���n���Ă���Ȃ�
		else if (pPlayer->GetLand() == true)
		{
			// �J�E���g��i�߂�
			m_nStanCount++;

			if (m_nStanCount > PLAYER_KNOCKBACK_STAN)
			{
				m_bDamage = false;
				m_nStanCount = 0;
			}
		}
	}
}

//=============================================================================
// �s�k����
//=============================================================================
void CControlPlayer::Defeat(CPlayer *pPlayer)
{
	// �v���C���[�̏�Ԃ�<�������>�ɂȂ������A�s�k������
	if (pPlayer->GetState() == CPlayer::PLAYER_STATE_BLOWAWAY && pPlayer->GetDefeat() == true)
	{
		// ���n���Ă��Ȃ���Ԃɂ���
		pPlayer->SetLand(false);

		// �ړI�̌�����ݒ�
		D3DXVECTOR3 rot = pPlayer->GetRot();
		m_fObjectiveRot = rot.y;
	}

	// �s�k
	if (pPlayer->GetDefeat() == true)
	{
		// ���n���Ă��Ȃ��Ȃ�
		if (pPlayer->GetLand() == false)
		{
			// �v���C���[�̐��ʂ��璼�i������
			D3DXVECTOR3 rot = pPlayer->GetRot();
			m_move.x = -sinf(rot.y) * PLAYER_DEFEAT_KNOCKBACK;
			m_move.z = -cosf(rot.y) * PLAYER_DEFEAT_KNOCKBACK;
		}

		// �ʒu���擾���AY�����ɂ�����0���牺�̈ʒu�ɍs���Ȃ��悤�ɂ���
		D3DXVECTOR3 pos = pPlayer->GetPos();
		if (pos.y <= 0)
		{
			pos.y = 0.0f;
			m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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