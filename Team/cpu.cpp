//=============================================================================
// AI���쏈�� [cpu.cpp]
// Author : �O��@�q��
//=============================================================================
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "cpu.h"
#include "manager.h"
#include "player.h"
#include "camera.h"
#include "sound.h"
#include "model.h"
#include "player.h"
#include "renderer.h"
#include "collision_sphere.h"
#include "bomb.h"
#include "danger.h"
#include "PresetDelaySet.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CPU_MOVE_TIME				(40)	// �Œ���̈ړ�����
#define CPU_THINK_TIME				(10)	// �Œ���̎v�l����

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCPU::CCPU()
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
	m_pBomb = NULL;
	m_pPlayer = NULL;

	m_bMove = false;
	m_nMoveTime = 0;
	m_thinkType = THINK_NONE;
	m_nThinkTime = CPU_THINK_TIME;
	m_bNextAttack = false;
	m_bNextSliding = false;
	m_bWall = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCPU::~CCPU()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CCPU::Init(void)
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
	m_nMoveTime = 0;
	m_thinkType = THINK_NONE;
	m_nThinkTime = CPU_THINK_TIME;
	m_bNextAttack = false;
	m_bNextSliding = false;
	m_bWall = false;
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CCPU::Uninit(void)
{
	if (m_pCollision != NULL)
	{
		m_pCollision = NULL;
	}
	if (m_pBomb != NULL)
	{
		m_pBomb = NULL;
	}
	if (m_pPlayer != NULL)
	{
		m_pPlayer = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CCPU::Update(CScene *pScene)
{
	// �����̃|�C���^���v���C���[�N���X�̃|�C���^�ɃL���X�g
	CPlayer *pPlayer = NULL;
	pPlayer = (CPlayer*)pScene;

	// �T�E���h�擾����

	// �ړ��ʂ�ݒ�
	m_move = pPlayer->GetMove();

	//---------------------------------------------------
	// �d��
	//---------------------------------------------------
	if (pPlayer->GetState() != CPlayer::PLAYER_STATE_DEFEAT && m_bDamage == true && pPlayer->GetLand() == false)
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

			if (m_thinkType == THINK_NONE)
			{
				if (m_nThinkTime <= 0)
				{
					Search(pPlayer);
				}
				else
				{
					m_nThinkTime--;
				}
			}

			//---------------------------------------------------
			// ��{�A�N�V����
			//---------------------------------------------------
			// �X�̏�Ԉُ킶��Ȃ��Ȃ�
			if (pPlayer->GetBadState() != CPlayer::PLAYER_BAD_STATE_ICE)
			{
				// ��_���[�W��Ԃ���Ȃ��Ȃ�
				if (m_bDamage == false)
				{
					// �U���ƃX���C�f�B���O(���)�̗��������Ă��Ȃ��Ȃ�
					if (m_bAttack == false && m_bSliding == false)
					{
						// �ړ�����
						Move(pPlayer);
					}

					if (m_bSliding == false)
					{
						Attack(pPlayer);
					}

					if (m_bAttack == false)
					{
						Sliding(pPlayer);
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
					m_nThinkTime = CPU_THINK_TIME;
					m_thinkType = THINK_NONE;
				}
			}
		}
	}
	else
	{
		// �s�k���̏���
		Defeat(pPlayer);
	}
	//---------------------------------------------------
	// ���[�V�����J��
	//---------------------------------------------------

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
CCPU *CCPU::Create(void)
{
	// �C���X�^���X�̐���
	CCPU *pCPU = NULL;

	// �k���`�F�b�N
	if (pCPU == NULL)
	{
		// �N���X�̐���
		pCPU = new CCPU;
		if (pCPU != NULL)
		{
			// ����������
			pCPU->Init();
		}
	}

	return pCPU;
}

//=============================================================================
// �ړ�����
//=============================================================================
void CCPU::Move(CPlayer *pPlayer)
{
	if (m_bMove == false)
	{
		if (m_thinkType != THINK_NONE)
		{
			//***********************************************************************
			// �ړ�
			//***********************************************************************
			if (m_thinkType == THINK_MOVE)
			{
				m_bMove = SetMove();
			}
			else
			{
				m_bMove = true;
			}
		}
	}
	else
	{
		D3DXVECTOR3 pos = pPlayer->GetPos();
		
		switch (m_thinkType)
		{
		case THINK_BOMB:
			if (m_pBomb != NULL)
			{
				if (m_pBomb->GetDeath() == false)
				{
					//���e�̈ʒu
					D3DXVECTOR3 BombPos = m_pBomb->GetPos();

					//�Ώۂ̔��e�Ƃ̋���
					float fDistance = sqrtf(powf(pos.x - BombPos.x, 2.0f) + powf(pos.z - BombPos.z, 2.0f));
					
					//���e�Ƌ������߂��ꍇ
					if (fDistance < (pPlayer->GetRadius() + m_pBomb->GetDanger()->GetRadius()) * 2.0f || m_bWall == true)
					{
						//��]�̊������I���ɂ���
						m_bRotate = true;
						
						//���e�̕����Ɍ���
						m_fObjectiveRot = atan2f(BombPos.x - pos.x, BombPos.z - pos.z) - D3DX_PI;
						//�p�x������Ȃ��悤�ɂ���
						if (m_fObjectiveRot < -D3DX_PI)
						{
							m_fObjectiveRot += D3DX_PI * 2.0f;
						}

						//����������������ꍇ
						if (m_pBomb->GetTime() < 10)
						{
							//�������
							if (m_nSlidingCoolTime >= PLAYER_SLIDING_COOLTIME && m_bSliding == false && m_bAttack == false)
							{
								m_fObjectiveRot += D3DX_PI;
								//�p�x������Ȃ��悤�ɂ���
								if (D3DX_PI < m_fObjectiveRot)
								{
									m_fObjectiveRot -= D3DX_PI * 2.0f;
								}
								m_bNextSliding = true;
								m_bMove = false;
								m_thinkType = THINK_SLIDING;
								m_nThinkTime = CPU_THINK_TIME;
								m_bWall = false;
							}
						}

						//���e�Ǝ��ߋ����ȏꍇ
						if (fDistance < pPlayer->GetRadius() + m_pBomb->GetRadius() + 2.0f)
						{
							//�U������
							if (m_nAttackCoolTime >= PLAYER_ATTACK_COOLTIME)
							{
								m_bNextAttack = true;
								m_bMove = false;
								m_thinkType = THINK_NONE;
								m_nThinkTime = CPU_THINK_TIME;
								m_bWall = false;
							}
						}
					}
					else
					{
						//��]�̊������I���ɂ���
						m_bRotate = true;
						
						//���e�Ƃ͐����΂̕���������
						m_fObjectiveRot = atan2f(BombPos.x - pos.x, BombPos.z - pos.z);

						if (pPlayer->GetHitWall() == true)
						{
							m_bWall = true;
						}

						//����������������ꍇ
						if (m_pBomb->GetTime() < 5)
						{
							if (m_nSlidingCoolTime >= PLAYER_SLIDING_COOLTIME && m_bSliding == false && m_bAttack == false)
							{
								m_bNextSliding = true;
								m_bMove = false;
								m_thinkType = THINK_SLIDING;
								m_nThinkTime = CPU_THINK_TIME;
							}
						}

						//�\���������󂢂���
						if (fDistance > (pPlayer->GetRadius() + m_pBomb->GetDanger()->GetRadius()) * 2.5f)
						{
							//�ړ�����߂�
							m_bMove = false;
							m_thinkType = THINK_NONE;
							m_nThinkTime = CPU_THINK_TIME;
						}
					}
				}
				else
				{
					m_pBomb = NULL;
					m_bWall = false;
					m_bMove = false;
					m_thinkType = THINK_NONE;
					m_nThinkTime = CPU_THINK_TIME;
				}
			}
			break;
		case THINK_PLAYER:
			if (m_pPlayer != NULL)
			{
				if (m_pPlayer->GetDeath() == false)
				{
					//�v���C���[�̈ʒu�擾
					D3DXVECTOR3 PlayerPos = m_pPlayer->GetPos();

					//��]�̊������I���ɂ���
					m_bRotate = true;

					//�v���C���[�̕���������
					m_fObjectiveRot = atan2f(PlayerPos.x - pos.x, PlayerPos.z - pos.z) - D3DX_PI;
					if (m_fObjectiveRot < -D3DX_PI)
					{
						m_fObjectiveRot += D3DX_PI * 2.0f;
					}

					//�v���C���[�Ƃ̋����v�Z
					float fDistance = sqrtf(powf(pos.x - PlayerPos.x, 2.0f) + powf(pos.z - PlayerPos.z, 2.0f));
					
					//�v���C���[�Ƌ������߂��ꍇ
					if (fDistance < pPlayer->GetRadius() + m_pPlayer->GetRadius() + 2.0f)
					{
						//�U������
						if (m_nAttackCoolTime >= PLAYER_ATTACK_COOLTIME)
						{
							m_bNextAttack = true;
							m_bMove = false;
							m_thinkType = THINK_NONE;
							m_nThinkTime = CPU_THINK_TIME;
						}
					}
				}
				else
				{
					m_pPlayer = NULL;
					m_bMove = false;
					m_thinkType = THINK_NONE;
					m_nThinkTime = CPU_THINK_TIME;
				}
			}
			break;
		case THINK_MOVE:
			m_nMoveTime--;
			if (m_nMoveTime <= 0)
			{
				m_thinkType = THINK_NONE;
				m_bMove = false;
			}
			break;
		default:
			break;
		}
		m_move.x -= (sinf(m_fObjectiveRot) * MAX_MOVE + m_move.x) * 0.1f;
		m_move.z -= (cosf(m_fObjectiveRot) * MAX_MOVE + m_move.z) * 0.1f;
	}
}

//=============================================================================
// �������
//=============================================================================
void CCPU::Sliding(CPlayer *pPlayer)
{
	// ���[�V�����擾����
	//CMotionPlayer *pMotionPlayer = NULL;
	//pMotionPlayer = pPlayer->GetMotionPlayer();

	// ��𒆂���Ȃ��Ȃ�
	if (m_bSliding == false)
	{
		// �N�[���^�C���̃J�E���g�𑝂₷
		m_nSlidingCoolTime++;

		// �N�[���^�C�����߂��Ă���Ȃ�
		if (m_nSlidingCoolTime >= PLAYER_SLIDING_COOLTIME && m_bNextSliding == true)
		{
			if (m_thinkType == THINK_SLIDING)
			{
				//�������
				m_nThinkTime = CPU_THINK_TIME * 4;
				m_bSliding = true;
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
		if (m_nSlidingCount > PLAYER_SLIDING_WAITTIME + PLAYER_SLIDING_TIME)
		{
			pPlayer->SetInvSliding(false);

			// ������Ă��Ȃ���Ԃɂ���
			m_bSliding = false;
			m_nSlidingCount = 0;

			m_bNextSliding = false;
		}
	}
}

//=============================================================================
// �U������
//=============================================================================
void CCPU::Attack(CPlayer *pPlayer)
{
	// ���[�V�����擾����
	//CMotionPlayer *pMotionPlayer = NULL;
	//pMotionPlayer = pPlayer->GetMotionPlayer();

	// �U��������Ȃ��Ȃ�
	if (m_bAttack == false)
	{
		// �N�[���^�C���̃J�E���g�𑝂₷
		m_nAttackCoolTime++;

		// �N�[���^�C�����߂��Ă���Ȃ�
		if (m_nAttackCoolTime >= PLAYER_ATTACK_COOLTIME && m_bNextAttack == true)
		{
			//***********************************************************************
			// �U��
			//***********************************************************************
			CPresetDelaySet::Create("ATTACK", pPlayer->GetPos());
			m_bAttack = true;
			m_nThinkTime = CPU_THINK_TIME + (rand() % 3) * 20;
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
			// �U�����Ă��Ȃ���Ԃɂ���
			m_bAttack = false;
			m_nAttackCount = 0;

			m_bNextAttack = false;
		}
	}
}

//=============================================================================
// ��_���[�W����
//=============================================================================
void CCPU::TakeDamage(CPlayer *pPlayer)
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

		m_nThinkTime = CPU_THINK_TIME;

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

				m_thinkType = THINK_NONE;
			}
		}
	}
}

//=============================================================================
// �s�k����
//=============================================================================
void CCPU::Defeat(CPlayer *pPlayer)
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
// �ړ��̊����ɂ��Ă̏���
//=============================================================================
void CCPU::MoveInteria(CPlayer *pPlayer)
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
void CCPU::Rotate(CPlayer *pPlayer)
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

bool CCPU::SetMove()
{
	m_nMoveTime = CPU_MOVE_TIME + (rand() % 5) * 30;
	m_nThinkTime = CPU_THINK_TIME;
	m_fObjectiveRot = D3DX_PI * (float)((rand() % 361) / 180.0f) - D3DX_PI;

	//��]�̊������I���ɂ���
	m_bRotate = true;
	return true;
}

void CCPU::Search(CPlayer *pPlayer)
{
	m_pBomb = CBomb::SearchBomb(pPlayer);
	m_pPlayer = CPlayer::SearchPlayer(pPlayer);
	D3DXVECTOR3 pos = pPlayer->GetPos();

	//�ǂ��������݂��Ă�
	if (m_pBomb != NULL && m_pPlayer != NULL)
	{
		D3DXVECTOR3 BombPos = m_pBomb->GetPos();
		D3DXVECTOR3 PlayerPos = m_pPlayer->GetPos();
		float fBombDistance;
		float fPlayerDistance;
		fBombDistance = sqrtf(powf(pos.x - BombPos.x, 2.0f) + powf(pos.z - BombPos.z, 2.0f));
		fPlayerDistance = sqrtf(powf(pos.x - PlayerPos.x, 2.0f) + powf(pos.z - PlayerPos.z, 2.0f));

		//���e�ƃv���C���[�̋������r�A�v���C���[�̕����߂�
		if (fBombDistance > fPlayerDistance * 3.0f)
		{
			m_thinkType = THINK_PLAYER;
		}
		else
		{
			m_thinkType = THINK_BOMB;
		}
	}
	else if (m_pBomb != NULL && m_pPlayer == NULL)
	{
		m_thinkType = THINK_BOMB;
	}
	else if (m_pBomb == NULL && m_pPlayer != NULL)
	{
		m_thinkType = THINK_PLAYER;
	}
	else if (m_pBomb == NULL && m_pPlayer == NULL)
	{
		m_thinkType = THINK_NONE;
		m_nThinkTime = CPU_MOVE_TIME * 3;
	}
}