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
#include "presetdelayset.h"
#include "motion.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CPU_MOVE_TIME				(90)	// �Œ���̈ړ�����
#define CPU_THINK_TIME				(10)	// �Œ���̎v�l����
#define CPU_ATTACK_TIME				(240)	// �Œ���̎��U������܂ł̎���
#define CPU_SLIDING_TIME			(15)	// �������t���[���O�ɂȂ����������邩
#define CPU_CONFUSION_TIME			(12)	// ���������牽�t���[���ړ������΂ɂȂ邩

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
	m_nConfusion = 0;
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
	m_nConfusion = 0;
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
	if (m_pNearCollision != NULL)
	{
		m_pNearCollision = NULL;
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

	// ���[�V�����擾����
	CMotion *pMotion = NULL;
	pMotion = pPlayer->GetMotion();

	// �T�E���h�擾����

	// �ړ��ʂ�ݒ�
	m_move = pPlayer->GetMove();

	//---------------------------------------------------
	// �d��
	//---------------------------------------------------
	if (pPlayer->GetState() != CPlayer::PLAYER_STATE_DEFEAT && m_bDamage == true && pPlayer->GetLand() == false)
	{
		m_move.y -= m_fGravity;
	}
	else if (pPlayer->GetState() == CPlayer::PLAYER_STATE_DEFEAT)
	{
		m_move.y -= PLAYER_GRAVITY_DEFEAT;
	}
	else
	{
		m_move.y -= m_fGravity;
	}

	// �d�͂������Ȃ肷������d�͂̍ő�l�ŌŒ肵�Ă���
	if (m_move.y <= -PLAYER_MAX_GRAVITY)
	{
		m_move.y = -PLAYER_MAX_GRAVITY;
	}

	// �s�k���Ă��Ȃ�������
	if (pPlayer->GetState() != CPlayer::PLAYER_STATE_DEFEAT)
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

		if (m_nThinkTime < -50)
		{
			m_thinkType = THINK_NONE;
			m_nThinkTime = CPU_THINK_TIME;
		}
		else if (m_nMoveTime < -50)
		{
			m_thinkType = THINK_NONE;
			m_nThinkTime = CPU_THINK_TIME;
		}
		if (m_nAfterAttack > 0)
		{
			m_nAfterAttack--;
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
				m_pBomb = NULL;
				m_pPlayer = NULL;
				m_pNearCollision = NULL;
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
	// �ړ��ʂ�0���A���[�V�������Ȃ��Ă��Ȃ����A�ړ����[�V������������
	if ((m_move.x == 0 && m_move.z == 0) && pMotion->GetConnect() == false && pMotion->GetMotion() == 1)
	{
		// �j���[�g�������[�V�����ɐݒ�
		pMotion->SetMotion(0);
	}

	// �ړ��ʂ�0����Ȃ����A���[�V�������Ȃ��Ă��Ȃ����A�j���[�g�������[�V������������
	if ((m_move.x != 0 && m_move.z != 0) && pMotion->GetConnect() == false && pMotion->GetMotion() == 0)
	{
		// �ړ����[�V�����ɂ���
		pMotion->SetMotion(1);
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
CCPU *CCPU::Create(float fFriction, float fMaxSpeed, float fGravity)
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

			if (fFriction < MIN_FRICTION)
			{
				pCPU->m_fFriction = MIN_FRICTION;
			}
			else
			{
				pCPU->m_fFriction = fFriction;
			}
			pCPU->m_fMaxSpeed = fMaxSpeed;
			pCPU->m_fGravity = fGravity;
		}
	}

	return pCPU;
}

//=============================================================================
// �ړ�����
//=============================================================================
void CCPU::Move(CPlayer *pPlayer)
{
	bool bControl = false;
	if (CManager::GetPause() == false && CManager::GetCountdown() == false && CManager::GetGameEnd() == false)
	{
		bControl = true;
	}

	if (bControl == true)
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
					//�܂������Ȃ�
					if (m_pBomb->GetDeath() == false && m_pBomb->GetTime() > 2 && m_pBomb->GetDanger() != NULL)
					{
						//���e�̈ʒu
						D3DXVECTOR3 BombPos = m_pBomb->GetPos();

						//�Ώۂ̔��e�Ƃ̋���
						float fDistance = sqrtf(powf(pos.x - BombPos.x, 2.0f) + powf(pos.z - BombPos.z, 2.0f));

						//���e�Ƌ������߂��ꍇ�A�܂��͓����Ă��ĕǂ̓���������
						if (fDistance < (pPlayer->GetRadius() + m_pBomb->GetDanger()->GetRadius()) * 1.4f || m_bWall == true)
						{
							//��]�̊������I���ɂ���
							m_bRotate = true;

							//���e�̕����Ɍ���
							m_fObjectiveRot = atan2f(BombPos.x - pos.x, BombPos.z - pos.z) - D3DX_PI;

							//�����̃J�E���g��
							if (m_nConfusion > 0)
							{
								//�����������]
								m_fObjectiveRot += D3DX_PI;
							}

							//�p�x������Ȃ��悤�ɂ���
							if (m_fObjectiveRot < -D3DX_PI)
							{
								m_fObjectiveRot += D3DX_PI * 2.0f;
							}

							//����������������ꍇ
							if (m_pBomb->GetTime() < CPU_SLIDING_TIME)
							{
								//�������
								if (m_nSlidingCoolTime >= PLAYER_SLIDING_COOLTIME && m_bSliding == false && m_bAttack == false)
								{
									if (m_pBomb->GetDanger()->GetRadius() * 0.7f < fDistance && fDistance < (m_pBomb->GetDanger()->GetRadius() + pPlayer->GetRadius()) 
										&& m_nSlidingCoolTime >= PLAYER_SLIDING_COOLTIME && m_bSliding == false && m_bAttack == false)
									{
										//�����̃J�E���g������Ȃ�
										if (m_nConfusion <= 0)
										{
											//�����������]
											m_fObjectiveRot += D3DX_PI;

											//�p�x������Ȃ��悤�ɂ���
											if (D3DX_PI < m_fObjectiveRot)
											{
												m_fObjectiveRot -= D3DX_PI * 2.0f;
											}
										}
									}
									m_bNextSliding = true;
									m_bMove = false;
									m_thinkType = THINK_NONE;
									m_nThinkTime = CPU_THINK_TIME;
									m_bWall = false;
								}
							}

							if (m_nConfusion <= 0)
							{
								//�v���C���[�̌����Ă����
								float fRotY = pPlayer->GetRot().y;
								//���e�Ƌ߂������e�̕����Ƃقڈ�v���Ă���ꍇ�A�܂��͔��e�Ǝ��ߋ����ȏꍇ
								if (fDistance < pPlayer->GetRadius() + m_pBomb->GetRadius() * 0.5f && fabsf(fabsf(m_fObjectiveRot) - fabsf(fRotY)) < 0.4f || fDistance < m_pBomb->GetRadius())
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
						}
						//�������������ǂɓ������ĂȂ�
						else
						{
							//�ǂɓ������Ă����炩�����̎��Ԃ��߂��Ă�����
							if (pPlayer->GetHitWall() == true && m_nConfusion <= 0)
							{
								//�ǂɓ�������
								m_bWall = true;
							}
							//�ǂɓ������Ă��Ȃ��܂��͍�����
							else
							{
								//��]�̊������I���ɂ���
								m_bRotate = true;

								//���e�Ƃ͐����΂̕���������
								m_fObjectiveRot = atan2f(BombPos.x - pos.x, BombPos.z - pos.z);

								//�����̃J�E���g��(�I���ɂ���ƁA�����ŉ��x���U��Ԃ�)
								//if (m_nConfusion > 0)
								//{
								//	//�����������]
								//	m_fObjectiveRot += D3DX_PI;

								//	//�p�x������Ȃ��悤�ɂ���
								//	if (D3DX_PI < m_fObjectiveRot)
								//	{
								//		m_fObjectiveRot -= D3DX_PI * 2.0f;
								//	}
								//}

								//����������������ꍇ
								if (m_pBomb->GetTime() < CPU_SLIDING_TIME)
								{
									//���e�Ƌ߂��A�X���C�f�B���O�̃N�[���^�C�����߂��Ă�A�X���C�f�B���O���łȂ��A�U�����łȂ�
									if (fDistance < pPlayer->GetRadius() + m_pBomb->GetDanger()->GetRadius() &&
										m_nSlidingCoolTime >= PLAYER_SLIDING_COOLTIME && m_bSliding == false && m_bAttack == false)
									{
										m_bNextSliding = true;
										m_bMove = false;
										m_thinkType = THINK_NONE;
										m_nThinkTime = CPU_THINK_TIME;

										//�������]
										m_fObjectiveRot += D3DX_PI;

										//�p�x������Ȃ��悤�ɂ���
										if (D3DX_PI < m_fObjectiveRot)
										{
											m_fObjectiveRot -= D3DX_PI * 2.0f;
										}
									}
									else
									{
										//�ړ�����߂�
										m_bMove = false;
										m_thinkType = THINK_NONE;
										m_nThinkTime = CPU_THINK_TIME;
									}
								}

								//�\���������󂢂���
								if (fDistance > (pPlayer->GetRadius() + m_pBomb->GetDanger()->GetRadius()) * 2.2f)
								{
									//�ړ�����߂�
									m_bMove = false;
									m_thinkType = THINK_NONE;
									m_nThinkTime = CPU_THINK_TIME;
								}
							}
						}
					}
					else
					{
						//���e��NULL�ɂ��A�l����
						BombClear();
					}
				}
				else
				{
					//�l����
					m_bWall = false;
					m_bMove = false;
					m_thinkType = THINK_NONE;
					m_nThinkTime = CPU_THINK_TIME;
				}
				break;
			case THINK_PLAYER:
				if (m_pPlayer != NULL)
				{
					if (m_pPlayer->GetDeath() == false && m_pPlayer->GetState() != CPlayer::PLAYER_STATE_DEFEAT)
					{
						//�v���C���[�̈ʒu�擾
						D3DXVECTOR3 PlayerPos = m_pPlayer->GetPos();

						//��]�̊������I���ɂ���
						m_bRotate = true;

						//�v���C���[�̕���������
						m_fObjectiveRot = atan2f(PlayerPos.x - pos.x, PlayerPos.z - pos.z) - D3DX_PI;

						//�����̃J�E���g��
						if (m_nConfusion > 0)
						{
							//�����������]
							m_fObjectiveRot += D3DX_PI;
						}

						//�p�x������Ȃ��悤�ɂ���
						if (m_fObjectiveRot < -D3DX_PI)
						{
							m_fObjectiveRot += D3DX_PI * 2.0f;
						}

						if (m_nConfusion <= 0)
						{
							//�v���C���[�Ƃ̋����v�Z�A�����̌����Ă����
							float fDistance = sqrtf(powf(pos.x - PlayerPos.x, 2.0f) + powf(pos.z - PlayerPos.z, 2.0f));
							float fRotY = pPlayer->GetRot().y;

							//�v���C���[�Ƌ������߂�����������̈�v���Ă�ꍇ
							if (fDistance < pPlayer->GetRadius() + m_pPlayer->GetRadius() * 0.6f && fabsf(fabsf(m_fObjectiveRot) - fabsf(fRotY)) < 0.4f)
							{
								//�N�[���^�C�����I����Ă�����
								if (m_nAttackCoolTime >= PLAYER_ATTACK_COOLTIME)
								{
									//�U������
									m_bNextAttack = true;
									m_bMove = false;
									m_thinkType = THINK_NONE;
									m_nThinkTime = CPU_THINK_TIME;
								}
							}
						}
					}
					else
					{
						//�v���C���[��NULL�ɂ��A�܂��V���ɍl����
						m_pPlayer = NULL;
						m_bMove = false;
						m_thinkType = THINK_NONE;
						m_nThinkTime = CPU_THINK_TIME;
					}
				}
				else
				{
					m_bMove = false;
					m_thinkType = THINK_NONE;
					m_nThinkTime = CPU_THINK_TIME;
				}
				break;
			case THINK_MOVE:
				m_nMoveTime--;
				//�ǂɓ������Ă�����
				if (pPlayer->GetHitWall() == true)
				{
					if (m_bWall == false)
					{
						//�ǂɓ�������
						m_bWall = true;
						
						////��]�̊������I���ɂ���
						//m_bRotate = true;

						//D3DXVECTOR3 Vec = pPlayer->GetWall();
						//D3DXVECTOR3 out = D3DXVECTOR3(m_move.x, 0.0f, m_move.z);

						////�ǂ̖@���x�N�g���ƈړ����x�Ƃ��v�Z���A�i�s������ς���
						///*m_fObjectiveRot = atan2f(Vec.x, Vec.z);
						//Vec.x = 0.0f;*/
						//float fLength1 = powf((Vec.x * Vec.x) + (Vec.y * Vec.y) + (Vec.z * Vec.z), 0.5f);
						//float fLength2 = powf((out.x * out.x) + (out.y * out.y) + (out.z * out.z), 0.5f);
						//float f1 = ((Vec.x * out.x) + (Vec.y * out.y) + (Vec.z * out.z)) / (fLength1 * fLength2);
						//float sita = acosf(f1);
						//m_fObjectiveRot += sita;
						m_nMoveTime = 0;
					}
				}
				if (m_nMoveTime <= 0)
				{
					m_thinkType = THINK_NONE;
					m_nThinkTime = CPU_THINK_TIME;
					m_bMove = false;
					m_bWall = false;

					m_pNearCollision = NULL;
					m_pBomb = NULL;
					m_pPlayer = NULL;
				}
				break;
			default:
				break;
			}

			//��ԋ߂��̓����蔻�肪����Ƃ�
			if (m_pNearCollision != NULL)
			{
				//�܂������Ȃ�
				if (m_pNearCollision->GetDeath() == false && m_pNearCollision->GetTime() > 2.0f)
				{
					D3DXVECTOR3 ColPos = m_pNearCollision->GetPos();

					//�Ώۂ̃R���W�����Ƃ̋���
					float fDistance = sqrtf(powf(pos.x - ColPos.x, 2.0f) + powf(pos.z - ColPos.z, 2.0f));
					float fColRotY = atan2f(ColPos.x - pos.x, ColPos.z - pos.z) - D3DX_PI;
					if (fColRotY < -D3DX_PI)
					{
						fColRotY += D3DX_PI * 2.0f;
					}
					if (m_thinkType != THINK_MOVE)
					{
						//�߂��ꍇ
						if (fDistance < m_pNearCollision->GetRadius() * 2.0f + pPlayer->GetRadius())
						{
							//��]�̊������I���ɂ���
							m_bRotate = true;

							//�����蔻��Ɛ����΂̕���������
							m_fObjectiveRot = fColRotY + D3DX_PI;
							if (D3DX_PI < m_fObjectiveRot)
							{
								m_fObjectiveRot -= D3DX_PI * 2.0f;
							}

							m_thinkType = THINK_MOVE;
							m_nMoveTime = CPU_MOVE_TIME;
						}
						//�߂����ړI�̕����Ɠ����蔻��̕�������̈�v���Ă���ꍇ
						else if (fDistance < pPlayer->GetRadius() * 1.6f + m_pNearCollision->GetRadius() &&
							fabsf(fabsf(m_fObjectiveRot) - fabsf(fColRotY)) < D3DX_PI * 0.5f)
						{
							m_nThinkTime = CPU_THINK_TIME;
							m_thinkType = THINK_NONE;
							m_bMove = false;

							m_pNearCollision = NULL;
							m_pBomb = NULL;
							m_pPlayer = NULL;
						}
					}
				}
				else
				{
					m_nThinkTime = CPU_THINK_TIME;
					m_thinkType = THINK_NONE;
					m_bMove = false;

					m_pNearCollision = NULL;
					m_pBomb = NULL;
					m_pPlayer = NULL;
				}
			}

			m_move.x -= (sinf(m_fObjectiveRot) * MAX_MOVE * m_fMaxSpeed + m_move.x) * 0.1f * m_fFriction;
			m_move.z -= (cosf(m_fObjectiveRot) * MAX_MOVE * m_fMaxSpeed + m_move.z) * 0.1f * m_fFriction;

			//�������Ă鎞�Ԃ�0���傫��
			if (m_nConfusion > 0)
			{
				//��������������
				if (pPlayer->GetBadState() == CPlayer::PLAYER_BAD_STATE_CONFUSION)
				{
					m_nConfusion--;
				}
				else
				{
					m_nConfusion = 0;
				}
			}
		}
	}
	else
	{
		m_bMove = false;
	}
}

//=============================================================================
// �������
//=============================================================================
void CCPU::Sliding(CPlayer *pPlayer)
{
	bool bControl = false;
	if (CManager::GetPause() == false && CManager::GetCountdown() == false && CManager::GetGameEnd() == false)
	{
		bControl = true;
	}

	// ��𒆂���Ȃ��Ȃ�
	if (m_bSliding == false)
	{
		// �N�[���^�C���̃J�E���g�𑝂₷
		m_nSlidingCoolTime++;

		// �N�[���^�C�����߂��Ă���Ȃ�
		if (m_nSlidingCoolTime >= PLAYER_SLIDING_COOLTIME && m_bNextSliding == true && bControl == true)
		{
			// ���[�V�����擾����
			CMotion *pMotion = pPlayer->GetMotion();

			// �X���C�f�B���O���[�V�����ɂ���
			pMotion->SetMotion(2);

			//�������
			m_nThinkTime = CPU_THINK_TIME;
			m_bSliding = true;

			CSound::Play(20);
		}
	}
	// ���
	else if (m_bSliding == true)
	{
		pPlayer->SetInvSliding(true);

		// �N�[���^�C�������Z�b�g
		m_nSlidingCoolTime = 0;

		if (pPlayer->GetBadState() != CPlayer::PLAYER_BAD_STATE_ICE)
		{
			// �J�E���g�𑝂₷
			m_nSlidingCount++;
		}

		// ������Ԃ̊ԂȂ�
		if (m_nSlidingCount <= PLAYER_SLIDING_TIME)
		{
			// �v���C���[�̌������擾���A���i������
			D3DXVECTOR3 rot = pPlayer->GetRot();
			m_move.x = -sinf(rot.y) * MAX_SLIDE * m_fMaxSpeed;
			m_move.z = -cosf(rot.y) * MAX_SLIDE * m_fMaxSpeed;
		}

		// �����A�d�����Ԃ��߂�����
		if (m_nSlidingCount > PLAYER_SLIDING_TIME)
		{
			pPlayer->SetInvSliding(false);

			// �����̌��Z
			m_move.x -= m_move.x * PLAYER_INTERIA_SUBTRACTION * m_fFriction;
			m_move.z -= m_move.z * PLAYER_INTERIA_SUBTRACTION * m_fFriction;
		}

		if (m_nSlidingCount > PLAYER_SLIDING_TIME + PLAYER_SLIDING_WAITTIME)
		{
			// ������Ă��Ȃ���Ԃɂ���
			m_bSliding = false;
			m_nSlidingCount = 0;

			m_thinkType = THINK_NONE;

			//�����s�������Z�b�g����
			m_bNextSliding = false;
			m_bNextAttack = false;
		}
	}
}

//=============================================================================
// �U������
//=============================================================================
void CCPU::Attack(CPlayer *pPlayer)
{
	bool bControl = false;
	if (CManager::GetPause() == false && CManager::GetCountdown() == false && CManager::GetGameEnd() == false)
	{
		bControl = true;
	}

	// �U��������Ȃ��Ȃ�
	if (m_bAttack == false)
	{
		// �N�[���^�C���̃J�E���g�𑝂₷
		m_nAttackCoolTime++;

		// �N�[���^�C�����߂��Ă���Ȃ�
		if (m_nAttackCoolTime >= PLAYER_ATTACK_COOLTIME && m_bNextAttack == true && bControl == true)
		{
			//***********************************************************************
			// �U��
			//***********************************************************************
			m_bAttack = true;
			m_nThinkTime = CPU_THINK_TIME;
			m_nAfterAttack = CPU_ATTACK_TIME;

			// ���[�V�����擾����
			CMotion *pMotion = pPlayer->GetMotion();

			// �U�����[�V�����ɂ���
			pMotion->SetMotion(3);
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
		if (m_nAttackCount == ATTACK_LAG)
		{
			// �O���ɓ����蔻��𔭐�������
			D3DXVECTOR3 pos = pPlayer->GetPos();
			D3DXVECTOR3 rot = pPlayer->GetRot();
			pos.x -= sinf(rot.y) * 20.0f;
			pos.z -= cosf(rot.y) * 20.0f;
			m_pCollision = CCollisionSphere::Create(D3DXVECTOR3(pos.x, pos.y + pPlayer->GetRadius(), pos.z),
				pPlayer->GetRadius() * 2.5f, 16, 16, CCollisionSphere::COLLISION_S_TYPE::COLLISION_S_TYPE_ATTACK, PLAYER_ATTACK_TIME, rot.y);
			// �ǂ̃v���C���[�̍U�����ݒ�
			m_pCollision->SetNumPlayer(pPlayer->GetType());

			//�G�t�F�N�g�o��
			CPresetDelaySet::Create("ATTACK", pos);

			CSound::Play(16);
			m_nAttackCount++;
		}

		if (pPlayer->GetBadState() != CPlayer::PLAYER_BAD_STATE_ICE)
		{
			// �J�E���g�𑝂₷
			m_nAttackCount++;
		}

		// �U����A�d�����Ԃ��߂�����
		if (m_nAttackCount > PLAYER_ATTACK_WAITTIME + PLAYER_ATTACK_TIME)
		{
			// �U�����Ă��Ȃ���Ԃɂ���
			m_bAttack = false;
			m_nAttackCount = 0;
			m_thinkType = THINK_NONE;

			//���U������̂����Z�b�g����
			m_bNextAttack = false;
			m_bNextSliding = false;
		}
	}
}

//=============================================================================
// ��_���[�W����
//=============================================================================
void CCPU::TakeDamage(CPlayer *pPlayer)
{
	// ���[�V�����擾����
	CMotion *pMotion = pPlayer->GetMotion();

	// �v���C���[�̏�Ԃ�<�������>�ɂȂ������A�_���[�W���󂯂Ă��Ȃ�������
	if (pPlayer->GetState() == CPlayer::PLAYER_STATE_BLOWAWAY && m_bDamage == false)
	{
		// �X���C�f�B���O�ƍU����Ԃ̉����A�X�^�����Ԃ̃��Z�b�g
		m_bSliding = false;
		m_nSlidingCount = 0;
		m_bAttack = false;
		m_nAttackCount = 0;
		m_bNextAttack = false;
		m_bNextSliding = false;

		// �_���[�W���󂯂���Ԃɂ��A���n���Ă��Ȃ���Ԃɂ���
		m_bDamage = true;
		pPlayer->SetLand(false);

		// �ړI�̌�����ݒ�
		D3DXVECTOR3 rot = pPlayer->GetRot();
		m_fObjectiveRot = rot.y;

		m_nThinkTime = CPU_THINK_TIME;
		m_thinkType = THINK_NONE;

		m_bMove = false;
		m_bSliding = false;

		CSound::Play(17);
	}

	// �_���[�W��
	if (m_bDamage == true)
	{
		// ���n���Ă��Ȃ��Ȃ�
		if (pPlayer->GetLand() == false)
		{
			m_nStanCount = 0;

			// �v���C���[�̐��ʂ���t�����֌�ނ�����
			D3DXVECTOR3 rot = pPlayer->GetRot();
			m_move.x = sinf(rot.y) * PLAYER_KNOCKBACK;
			m_move.z = cosf(rot.y) * PLAYER_KNOCKBACK;
		}
		// ���n���Ă���Ȃ�
		else if (pPlayer->GetLand() == true)
		{
			// ���[�V�������Ȃ��Ă��Ȃ����A�_���[�W���[�V����(5)����Ȃ����A�N���オ�鎞�ԑO��������
			if (pMotion->GetConnect() == false && pMotion->GetMotion() != 5 && m_nStanCount < PLAYER_GETUP_TIME)
			{
				// �_���[�W���[�V����(5)�ɂ���
				pMotion->SetMotion(5);
			}

			if (pPlayer->GetBadState() != CPlayer::PLAYER_BAD_STATE_ICE)
			{
				// �J�E���g��i�߂�
				m_nStanCount++;
			}

			// ���[�V�������Ȃ��Ă��Ȃ����A�_���[�W���[�V����(6)����Ȃ������A�A�N���オ�鎞�Ԃ�������
			if (pMotion->GetConnect() == false && pMotion->GetMotion() != 6 && m_nStanCount >= PLAYER_GETUP_TIME)
			{
				// �N���オ�胂�[�V�����ɂ���
				pMotion->SetMotion(6);
			}

			if (m_nStanCount > PLAYER_KNOCKBACK_STAN)
			{
				m_bDamage = false;
				m_nStanCount = 0;

				// �v���C���[�̏�Ԃ�<�ʏ�>�ɖ߂�
				pPlayer->SetState(CPlayer::PLAYER_STATE_NORMAL);
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

		CSound::Play(18);
	}

	// �s�k
	if (m_bDefeat == true)
	{
		// ���n���Ă��Ȃ��Ȃ�
		if (pPlayer->GetLand() == false)
		{
			// �v���C���[����ނ�����
			D3DXVECTOR3 rot = pPlayer->GetRot();
			m_move.x = sinf(rot.y) * PLAYER_DEFEAT_KNOCKBACK;
			m_move.z = cosf(rot.y) * PLAYER_DEFEAT_KNOCKBACK;
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
		m_move.x -= m_move.x * PLAYER_INTERIA_SUBTRACTION * m_fFriction;
		m_move.z -= m_move.z * PLAYER_INTERIA_SUBTRACTION * m_fFriction;
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
	m_nMoveTime = CPU_MOVE_TIME + (rand() % 3) * 30;
	m_nThinkTime = CPU_THINK_TIME;
	m_fObjectiveRot = D3DX_PI * (float)((rand() % 361) / 180.0f) - D3DX_PI;

	//��]�̊������I���ɂ���
	m_bRotate = true;
	return true;
}

//�����蔻��A�v���C���[�A���e��S���Q��
void CCPU::Search(CPlayer *pPlayer)
{
	m_bWall = false;
	m_pBomb = CBomb::SearchBomb(pPlayer->GetPos(), this);
	if (m_nAfterAttack <= 0)
	{
		m_pPlayer = CPlayer::SearchPlayer(pPlayer);
	}
	else
	{
		m_pPlayer = NULL;
	}
	m_pNearCollision = CCollisionSphere::SearchCollision(pPlayer->GetPos());
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
		m_nThinkTime = CPU_THINK_TIME * 3;
	}

	if (pPlayer->GetBadState() == CPlayer::PLAYER_BAD_STATE_CONFUSION)
	{
		m_nConfusion = CPU_CONFUSION_TIME;
	}
}

// ���e�̏�������(�_���Ă锚�e����������ۂɎg��)
void CCPU::BombClear()
{
	m_pBomb = NULL;
	m_thinkType = THINK_NONE;
	m_nThinkTime = CPU_THINK_TIME;
	m_bWall = false;
	m_bMove = false;
}