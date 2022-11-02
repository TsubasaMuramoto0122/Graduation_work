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
#include "motion.h"
#include "camera.h"
#include "sound.h"
#include "model.h"
#include "player.h"
#include "renderer.h"
#include "collision_sphere.h"
#include "pauseui.h"
#include "fade.h"

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
int CControlPlayer::m_nPause = 0;
int CControlPlayer::m_nSelectPause = 0;
CPauseUI *CControlPlayer::m_pUI[3] = {};

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
	//m_bJump = false;
	m_bAttack = false;
	m_bDamage = false;
	m_bSliding = false;
	m_bDefeat = false;
	m_nSlidingCount = 0;
	m_nSlidingCoolTime = 0;
	m_nAttackCount = 0;
	m_nAttackCoolTime = 0;
	m_nStanCount = 0;
	m_pCollision = NULL;

	m_bMove = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CControlPlayer::~CControlPlayer()
{
	if (m_pCollision != NULL)
	{
		m_pCollision = NULL;
	}
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
	//m_bJump = false;
	m_bAttack = false;
	m_bDamage = false;
	m_bSliding = false;
	m_bDefeat = false;
	m_nSlidingCount = 0;
	m_nSlidingCoolTime = PLAYER_SLIDING_COOLTIME;
	m_nAttackCount = 0;
	m_nAttackCoolTime = PLAYER_ATTACK_COOLTIME;
	m_nStanCount = 0;
	m_pCollision = NULL;

	m_bMove = false;

	if (m_pUI[0] == NULL)
	{
		m_pUI[0] = CPauseUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f - 160.0f, 0.0f), D3DXVECTOR2(280.0f, 50.0f), 1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pUI[1] = CPauseUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5, 0.0f), D3DXVECTOR2(280.0f, 50.0f), 2, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));
		m_pUI[2] = CPauseUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f + 160.0f, 0.0f), D3DXVECTOR2(280.0f, 50.0f), 3, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));
	}
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CControlPlayer::Uninit(void)
{
	int nCntUI;
	for (nCntUI = 0; nCntUI < 3; nCntUI++)
	{
		if (m_pUI[nCntUI] != NULL)
		{
			m_pUI[nCntUI] = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CControlPlayer::Update(CScene *pScene)
{
	// �����̃|�C���^���v���C���[�N���X�̃|�C���^�ɃL���X�g
	CPlayer *pPlayer = NULL;
	pPlayer = (CPlayer*)pScene;

	// �L�[�{�[�h�擾����
	CKeyboard *pKeyboard = NULL;
	pKeyboard = CManager::GetKeyboard();

	// �Q�[���p�b�h�擾����
	CGamePad *pGamePad = NULL;
	pGamePad = CManager::GetGamepad();
	
	// ���[�V�����擾����
	CMotion *pMotion = NULL;
	pMotion = pPlayer->GetMotion();

	// �ړ��ʂ�ݒ�
	m_move = pPlayer->GetMove();

	//---------------------------------------------------
	// �d��
	//---------------------------------------------------
	if (pPlayer->GetState() != CPlayer::PLAYER_STATE_DEFEAT &&m_bDamage == true && pPlayer->GetLand() == false)
	{
		m_move.y -= PLAYER_GRAVITY_DAMAGE;
	}
	else if (pPlayer->GetState() == CPlayer::PLAYER_STATE_DEFEAT)
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
	if (pPlayer->GetState() != CPlayer::PLAYER_STATE_DEFEAT)
	{
		if (CManager::GetPause() == false && CManager::GetCountdown() == false && CManager::GetGameEnd() == false)
		{
			// ��_���[�W����
			TakeDamage(pPlayer);

			//---------------------------------------------------
			// ��{�A�N�V����
			//---------------------------------------------------
			// �X�̏�Ԉُ킶��Ȃ��Ȃ�
			if (pPlayer->GetBadState() != CPlayer::PLAYER_BAD_STATE_ICE)
			{
				// ��_���[�W��Ԃ���Ȃ��Ȃ�
				if (m_bDamage == false)
				{
					// �U�����Ă��Ȃ��Ȃ�
					if (m_bAttack == false)
					{
						// �X���C�f�B���O(���)����
						Sliding(pPlayer);
					}

					// �X���C�f�B���O(���)���Ă��Ȃ��Ȃ�
					if (m_bSliding == false)
					{
						// �U������
						Attack(pPlayer);
					}

					// �U���ƃX���C�f�B���O(���)�̗��������Ă��Ȃ��Ȃ�
					if (m_bAttack == false && m_bSliding == false)
					{
						// �ړ�����
						Move(pPlayer);
					}
				}
				// �X�̏�Ԉُ킾������
				else if (pPlayer->GetBadState() == CPlayer::PLAYER_BAD_STATE_ICE)
				{
					// �A�N�V�����Ɏg���ϐ��̏�Ԃ����Z�b�g
					m_nAttackCoolTime = PLAYER_ATTACK_COOLTIME;
					m_bAttack = false;
					m_nSlidingCoolTime = PLAYER_SLIDING_COOLTIME;
					m_bSliding = false;
				}
			}
		}
		if (CManager::GetCountdown() == false && CManager::GetGameEnd() == false)
		{
			//�|�[�Y����
			Pause(pPlayer);
		}
	}
	// �s�k���̏���
	Defeat(pPlayer);

	//---------------------------------------------------
	// ���[�V�����J��
	//---------------------------------------------------
	// �ړ��ʂ�0���A���[�V�������Ȃ��Ă��Ȃ����A�ړ����[�V������������
	if ((m_move.x == 0 && m_move.z == 0) && pMotion->GetConnect() == false && pMotion->GetMotion() == 1)
	{
		// �j���[�g�������[�V�����ɐݒ�
		pMotion->SetMotion(0);
	}

	//---------------------------------------------------
	// ����
	//---------------------------------------------------
	// �ړ��̊���(�ڂ��������͊֐��̒�)
	MoveInteria(pPlayer);

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
	m_bMove = false;

	// �L�[�{�[�h�擾����
	CKeyboard *pKeyboard = CManager::GetKeyboard();
	
	// �Q�[���p�b�h�擾����
	CGamePad *pGamePad = CManager::GetGamepad();
	
	// ���[�V�����擾����
	CMotion *pMotion = pPlayer->GetMotion();
	
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

	if (pPlayer->GetBadState() == CPlayer::PLAYER_BAD_STATE_CONFUSION)
	{
		rotCamera += D3DX_PI;
		// ������3.14����-3.14�̒l�͈͓̔��Ɏ��߂�
		if (rotCamera > D3DX_PI)
		{
			rotCamera -= D3DX_PI * 2.0f;
		}
		else if (rotCamera < -D3DX_PI)
		{
			rotCamera += D3DX_PI * 2.0f;
		}
	}

	//***********************************************************************
	// �ړ� (�L�[�{�[�h�v/�`/�r/�c �܂��� �p�b�h���X�e�B�b�N)
	//***********************************************************************
	//���ړ�
	if (pKeyboard->GetPress(nLeft) == true ||
		pGamePad->GetPress(CGamePad::PAD_INPUTTYPE_LSTICK_LEFT, nPlayerNum) == true)
	{
		// ���[�V�������Ȃ��Ă��Ȃ����A�j���[�g�������[�V������������
		if (pMotion->GetConnect() == false && pMotion->GetMotion() == 0)
		{
			// �ړ����[�V�����ɂ���
			pMotion->SetMotion(1);
		}

		//�����ړ�
		if (pKeyboard->GetPress(nUp) == true ||
			pGamePad->GetPress(CGamePad::PAD_INPUTTYPE_LSTICK_UP, nPlayerNum) == true)
		{
			//�ړ��ʂ̉��Z����іړI�̌����̐ݒ�
			m_bMove = SetMove(rotCamera, 0.75f);
		}
		//����O�ړ�
		else if (pKeyboard->GetPress(nDown) == true ||
			pGamePad->GetPress(CGamePad::PAD_INPUTTYPE_LSTICK_DOWN, nPlayerNum) == true)
		{
			//�ړ��ʂ̉��Z����іړI�̌����̐ݒ�
			m_bMove = SetMove(rotCamera, 0.25f);
		}
		else
		{
			//�ړ��ʂ̉��Z����іړI�̌����̐ݒ�
			m_bMove = SetMove(rotCamera, 0.5f);
		}
	}
	//�E�ړ�
	else if (pKeyboard->GetPress(nRight) == true ||
		pGamePad->GetPress(CGamePad::PAD_INPUTTYPE_LSTICK_RIGHT, nPlayerNum) == true)
	{
		// ���[�V�������Ȃ��Ă��Ȃ����A�j���[�g�������[�V������������
		if (pMotion->GetConnect() == false && pMotion->GetMotion() == 0)
		{
			// �ړ����[�V�����ɂ���
			pMotion->SetMotion(1);
		}

		//�E���ړ�
		if (pKeyboard->GetPress(nUp) == true ||
			pGamePad->GetPress(CGamePad::PAD_INPUTTYPE_LSTICK_UP, nPlayerNum) == true)
		{
			//�ړ��ʂ̉��Z����іړI�̌����̐ݒ�
			m_bMove = SetMove(rotCamera, -0.75f);
		}
		//�E��O�ړ�
		else if (pKeyboard->GetPress(nDown) == true ||
			pGamePad->GetPress(CGamePad::PAD_INPUTTYPE_LSTICK_DOWN, nPlayerNum) == true)
		{
			//�ړ��ʂ̉��Z����іړI�̌����̐ݒ�
			m_bMove = SetMove(rotCamera, -0.25f);
		}
		else
		{
			//�ړ��ʉ��Z
			m_move.x -= (sinf(rotCamera - D3DX_PI * 0.5f) * MAX_MOVE + m_move.x) * 0.1f;
			m_move.z -= (cosf(rotCamera - D3DX_PI * 0.5f) * MAX_MOVE + m_move.z) * 0.1f;

			//�ړ��ʂ̉��Z����іړI�̌����̐ݒ�
			m_bMove = SetMove(rotCamera, -0.5f);
		}
	}
	//���ړ�
	else if (pKeyboard->GetPress(nUp) == true ||
		pGamePad->GetPress(CGamePad::PAD_INPUTTYPE_LSTICK_UP, nPlayerNum) == true)
	{
		// ���[�V�������Ȃ��Ă��Ȃ����A�j���[�g�������[�V������������
		if (pMotion->GetConnect() == false && pMotion->GetMotion() == 0)
		{
			// �ړ����[�V�����ɂ���
			pMotion->SetMotion(1);
		}

		//�ړ��ʂ̉��Z����іړI�̌����̐ݒ�
		m_bMove = SetMove(rotCamera, 1.0f);
	}
	//��O�ړ�
	else if (pKeyboard->GetPress(nDown) == true ||
		pGamePad->GetPress(CGamePad::PAD_INPUTTYPE_LSTICK_DOWN, nPlayerNum) == true)
	{
		// ���[�V�������Ȃ��Ă��Ȃ����A�j���[�g�������[�V������������
		if (pMotion->GetConnect() == false && pMotion->GetMotion() == 0)
		{
			// �ړ����[�V�����ɂ���
			pMotion->SetMotion(1);
		}

		//�ړ��ʂ̉��Z����іړI�̌����̐ݒ�
		m_bMove = SetMove(rotCamera, 0.0f);
	}
}

//=============================================================================
// �X���C�f�B���O(���)����
//=============================================================================
void CControlPlayer::Sliding(CPlayer *pPlayer)
{
	// �L�[�{�[�h�擾����
	CKeyboard *pKeyboard = CManager::GetKeyboard();

	// �Q�[���p�b�h�擾����
	CGamePad *pGamePad = CManager::GetGamepad();
	
	// ���[�V�����擾����
	CMotion *pMotion = pPlayer->GetMotion();

	// ���͏��𕪂���
	int nSlide = 0, nPlayerNum = 0;
	switch (pPlayer->GetType())
	{
	case CPlayer::PLAYER_TYPE_1P:
		nSlide = DIK_LSHIFT;
		nPlayerNum = 0;
		break;
	case CPlayer::PLAYER_TYPE_2P:
		nSlide = DIK_RCONTROL;
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
	if (m_bSliding == false)
	{
		// �N�[���^�C���̃J�E���g�𑝂₷
		m_nSlidingCoolTime++;

		// �N�[���^�C�����߂��Ă���Ȃ�
		if (m_nSlidingCoolTime >= PLAYER_SLIDING_COOLTIME)
		{
			//***********************************************************************
			// �X���C�f�B���O(���) (�L�[�{�[�h���V�t�g�L�[ �܂��� �p�b�hA�{�^��)
			//***********************************************************************
			if (pKeyboard->GetKey(nSlide) == true ||
				pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_A, nPlayerNum) == true)
			{
				// ������Ă����Ԃɐݒ�
				m_bSliding = true;

				// �X���C�f�B���O���[�V�����ɂ���
				pMotion->SetMotion(2);
			}
		}
	}
	// ���
	else if (m_bSliding == true)
	{
		pPlayer->SetInvSliding(true);

		// �N�[���^�C�������Z�b�g
		m_nSlidingCoolTime = 0;

		// �J�E���g�𑝂₷
		m_nSlidingCount++;

		// ������Ԃ̊ԂȂ�
		if (m_nSlidingCount <= PLAYER_SLIDING_TIME)
		{
			// �v���C���[�̌������擾���A���i������
			D3DXVECTOR3 rot = pPlayer->GetRot();
			m_move.x -= (sinf(rot.y) * MAX_SLIDE + m_move.x) * 0.1f;
			m_move.z -= (cosf(rot.y) * MAX_SLIDE + m_move.z) * 0.1f;
		}

		// �����A�d�����Ԃ��߂�����
		if (m_nSlidingCount > PLAYER_SLIDING_TIME)
		{
			pPlayer->SetInvSliding(false);

			// �����̌��Z
			m_move.x *= PLAYER_INTERIA_SUBTRACTION;
			m_move.z *= PLAYER_INTERIA_SUBTRACTION;
		}

		if (m_nSlidingCount > PLAYER_SLIDING_TIME + PLAYER_SLIDING_WAITTIME)
		{
			// ������Ă��Ȃ���Ԃɂ���
			m_bSliding = false;
			m_nSlidingCount = 0;
		}
	}
}

//=============================================================================
// �U������
//=============================================================================
void CControlPlayer::Attack(CPlayer *pPlayer)
{
	// �L�[�{�[�h�擾����
	CKeyboard *pKeyboard = CManager::GetKeyboard();

	// �Q�[���p�b�h�擾����
	CGamePad *pGamePad = CManager::GetGamepad();

	// ���[�V�����擾����
	CMotion *pMotion = pPlayer->GetMotion();

	// ���͏��𕪂���
	int nAttack = 0, nPlayerNum = 0;
	switch (pPlayer->GetType())
	{
	case CPlayer::PLAYER_TYPE_1P:
		nAttack = DIK_SPACE;
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

	// �U��������Ȃ��Ȃ�
	if (m_bAttack == false)
	{
		// �N�[���^�C���̃J�E���g�𑝂₷
		m_nAttackCoolTime++;

		// �N�[���^�C�����߂��Ă���Ȃ�
		if (m_nAttackCoolTime >= PLAYER_ATTACK_COOLTIME)
		{
			//***********************************************************************
			// �U�� (�L�[�{�[�h�X�y�[�X�L�[ �܂��� �p�b�hB�{�^��)
			//***********************************************************************
			if (pKeyboard->GetKey(nAttack) == true ||
				pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_B, nPlayerNum) == true)
			{
				// �U�����Ă����Ԃɐݒ�
				m_bAttack = true;

				// �U�����[�V�����ɂ���
				pMotion->SetMotion(3);
			}
		}
	}
	// �U����
	else if (m_bAttack == true)
	{
		// �N�[���^�C�������Z�b�g
		m_nAttackCoolTime = 0;

		// �U�����͓������~�߂�
		m_move.x = 0.0f;
		m_move.z = 0.0f;

		// ���̃J�E���g�ɂȂ�����
		if (m_nAttackCount == 15)
		{
			// �����蔻��𔭐�������
			D3DXVECTOR3 pos = pPlayer->GetPos();
			m_pCollision = CCollisionSphere::Create(D3DXVECTOR3(pos.x, pos.y + pPlayer->GetRadius(), pos.z), pPlayer->GetRadius() * 3.0f,
				16, 16, CCollisionSphere::COLLISION_S_TYPE::COLLISION_S_TYPE_ATTACK, PLAYER_ATTACK_TIME);
			// �ǂ̃v���C���[�̍U�����ݒ�
			m_pCollision->SetNumPlayer(pPlayer->GetType());
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
// �W�����v����
//=============================================================================
//void CControlPlayer::Jump(CPlayer *pPlayer)
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
//	/*CMotionPlayer *pMotionPlayer = NULL;
//	pMotionPlayer = pPlayer->GetMotionPlayer();*/
//
//	// ���͏��𕪂���
//	int nJump = 0, nPlayerNum = 0;
//	switch (pPlayer->GetType())
//	{
//	case CPlayer::PLAYER_TYPE_1P:
//		nJump = DIK_SPACE;
//		nPlayerNum = 0;
//		break;
//	case CPlayer::PLAYER_TYPE_2P:
//		nJump = DIK_RCONTROL;
//		nPlayerNum = 1;
//		break;
//	case CPlayer::PLAYER_TYPE_3P:
//		nPlayerNum = 2;
//		break;
//	case CPlayer::PLAYER_TYPE_4P:
//		nPlayerNum = 3;
//		break;
//	default:
//		break;
//	}
//
//	// �v���C���[�����n���Ă���Ȃ�
//	if (pPlayer->GetLand() == true)
//	{
//		//***********************************************************************
//		// �W�����v (�L�[�{�[�hSpace �܂��� �p�b�hA�{�^��)
//		//***********************************************************************
//		if (pKeyboard->GetTrigger(nJump) == true ||
//			pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_A, nPlayerNum) == true)
//		{
//			// Y�����̈ړ��ʂ�0��
//			m_move.y = 0.0f;
//
//			// �ړ��ʂ��W�����v�͂Ԃ���Z
//			m_move.y = PLAYER_JUMP;
//
//			// �W�����v�������A���n���Ă��Ȃ��ɐݒ�
//			m_bJump = true;
//			pPlayer->SetLand(false);
//
//			m_bJump = true;
//		}
//		else
//		{
//			// ���n������܂��W�����v���\�ɂ���
//			m_bJump = false;
//		}
//	}
//}

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

		m_bMove = false;
		m_bSliding = false;
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
	// �v���C���[�̏�Ԃ�<�s�k>�ɂȂ������A�s�k���Ă��Ȃ�������
	if (pPlayer->GetState() == CPlayer::PLAYER_STATE_DEFEAT && m_bDefeat == false)
	{
		// ���n���Ă��Ȃ���Ԃɂ���
		pPlayer->SetLand(false);
		m_bDefeat = true;

		// �ړI�̌�����ݒ�
		D3DXVECTOR3 rot = pPlayer->GetRot();
		m_fObjectiveRot = rot.y;
	}

	// �s�k
	if (m_bDefeat == true)
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
// �|�[�Y����
//=============================================================================
void CControlPlayer::Pause(CPlayer *pPlayer)
{
	// �L�[�{�[�h�擾����
	CKeyboard *pKeyboard;
	pKeyboard = CManager::GetKeyboard();

	// �Q�[���p�b�h�擾����
	CGamePad *pGamePad;
	pGamePad = CManager::GetGamepad();

	// ���͏��𕪂���
	int nPause = 0, nUp = 0, nDown = 0, nSelect = 0, nPlayerNum = 0;
	switch (pPlayer->GetType())
	{
	case CPlayer::PLAYER_TYPE_1P:
		nPause = DIK_ESCAPE;
		nUp = DIK_W;
		nDown = DIK_S;
		nSelect = DIK_RETURN;
		nPlayerNum = 0;
		break;
	case CPlayer::PLAYER_TYPE_2P:
		nPause = DIK_DELETE;
		nUp = DIK_UP;
		nDown = DIK_DOWN;
		nSelect = DIK_RETURN;
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

	if (CManager::GetPause() == false)
	{
		if (pKeyboard->GetKey(nPause) == true || 
			pGamePad->GetTrigger(XINPUT_GAMEPAD_START,nPlayerNum) == true)
		{
			m_nPause = nPlayerNum;
			CManager::SetPause(true);
		}
	}
	else
	{
		if ((pKeyboard->GetKey(nPause) == true ||
			pGamePad->GetTrigger(XINPUT_GAMEPAD_START, nPlayerNum) == true) &&
			nPlayerNum == m_nPause)
		{
			CManager::SetPause(false);
		}
		if ((pKeyboard->GetKey(nUp) == true ||
			pGamePad->GetTrigger(XINPUT_GAMEPAD_DPAD_UP, nPlayerNum) == true ||
			pGamePad->GetTrigger(CGamePad::PAD_INPUTTYPE_LSTICK_UP, nPlayerNum) == true) &&
			nPlayerNum == m_nPause)
		{
			PauseChange(-1);
		}
		if ((pKeyboard->GetKey(nDown) == true ||
			pGamePad->GetTrigger(XINPUT_GAMEPAD_DPAD_DOWN, nPlayerNum) == true ||
			pGamePad->GetTrigger(CGamePad::PAD_INPUTTYPE_LSTICK_DOWN, nPlayerNum) == true) &&
			nPlayerNum == m_nPause)
		{
			PauseChange(1);
		}
		if ((pKeyboard->GetKey(nPause) == true ||
			pGamePad->GetTrigger(XINPUT_GAMEPAD_START, nPlayerNum) == true) &&
			nPlayerNum == m_nPause)
		{
			CManager::SetPause(false);
		}
		if ((pKeyboard->GetKey(nSelect) == true ||
			pGamePad->GetTrigger(XINPUT_GAMEPAD_B, nPlayerNum) == true) &&
			nPlayerNum == m_nPause)
		{
			PauseSelect();
		}
	}
}

void CControlPlayer::PauseChange(int nAdd)
{
	m_pUI[m_nSelectPause]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));
	m_nSelectPause += nAdd;
	if (m_nSelectPause < 0)
	{
		m_nSelectPause = 2;
	}
	else if (2 < m_nSelectPause)
	{
		m_nSelectPause = 0;
	}
	m_pUI[m_nSelectPause]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

void CControlPlayer::PauseSelect()
{
	switch (m_nSelectPause)
	{
	case 0:
		CManager::SetPause(false);
		break;
	case 1:
		CFade::SetFade(CManager::MODE_GAME);
		break;
	case 2:
		CFade::SetFade(CManager::MODE_TITLE);
	default:
		break;
	}
}

//=============================================================================
// �ړ��̊����ɂ��Ă̏���
//=============================================================================
void CControlPlayer::MoveInteria(CPlayer *pPlayer)
{
	if (pPlayer->GetLand() == true && m_bMove == false && m_bSliding == false)
	{
		// �����̌��Z
		m_move.x *= PLAYER_INTERIA_SUBTRACTION;
		m_move.z *= PLAYER_INTERIA_SUBTRACTION;
	}

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

bool CControlPlayer::SetMove(float fRotCamera, float fRot)
{
	//�ړ��ʉ��Z
	m_move.x -= (sinf(fRotCamera + D3DX_PI * fRot) * MAX_MOVE + m_move.x) * 0.1f;
	m_move.z -= (cosf(fRotCamera + D3DX_PI * fRot) * MAX_MOVE + m_move.z) * 0.1f;

	//�ړI�̌�����ݒ肵�A��]�̊������I���ɂ���
	m_fObjectiveRot = fRotCamera + D3DX_PI * fRot;
	m_bRotate = true;

	return true;
}