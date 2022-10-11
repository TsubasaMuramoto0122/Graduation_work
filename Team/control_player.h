//=============================================================================
// �v���C���[���쏈�� [control_player.h]
// Author : Kusakari Kakeru
//=============================================================================
#ifndef _CONTROL_PLAYER_H_
#define _CONTROL_PLAYER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "control.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PLAYER_GRAVITY				(0.6f)	// �d�͂̑傫��
#define PLAYER_GRAVITY_DAMAGE		(2.4f)	// ��_���[�W���̏d�͂̑傫��
#define PLAYER_MAX_GRAVITY			(26.0f)	// �d�͂̍ő�l
#define PLAYER_MOVE_SPEED			(2.6f)	// �ړ��ʂ̊�l
#define PLAYER_INTERIA_SUBTRACTION	(0.86f)	// �n��ł̊����̌��Z�l
#define PLAYER_MOVE_STOP_COUNT		(0.02f)	// �v���C���[�̈ړ��ʂ�0�ɂ��鎞�̈ړ��ʂ̒l
#define PLAYER_DODGE				(3.5f)	// ����̈ړ��ʂ̊�l
#define PLAYER_DODGE_TIME			(20)	// �������
#define PLAYER_DODGE_WAITTIME		(5)		// �����̍d������
#define PLAYER_DODGE_COOLTIME		(120)	// �����A�Ăщ�����g����܂ł̎���
#define PLAYER_ATTACK_TIME			(15)	// �U������
#define PLAYER_ATTACK_WAITTIME		(10)	// �U����̍d������
#define PLAYER_ATTACK_COOLTIME		(1)		// �U����A�ĂэU���ł���܂ł̎���
#define PLAYER_KNOCKBACK			(8.0f)	// �m�b�N�o�b�N�̑傫��
#define PLAYER_KNOCKBACK_TIME		(7)		// �m�b�N�o�b�N�̎���
#define PLAYER_KNOCKBACK_JUMP		(6.0f)	// �m�b�N�o�b�N�̃W�����v��
#define PLAYER_KNOCKBACK_STAN		(6)		// �m�b�N�o�b�N��̃X�^���̎���

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CScene;
class CPlayer;
class CCollisionSphere;

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CControlPlayer : public CControl
{
public:
	CControlPlayer();						// �R���X�g���N�^
	~CControlPlayer();						// �f�X�g���N�^
	HRESULT Init(void);						// ����������
	void Uninit(void);						// �I������
	void Update(CScene *pScene);			// �X�V����
	static CControlPlayer *Create(void);	// ��������

private:
	void Move(CPlayer *pPlayer);			// �ړ�����
	void Dodge(CPlayer *pPlayer);			// �������
	void Attack(CPlayer *pPlayer);			// �U������
	void TakeDamage(CPlayer *pPlayer);		// ��_���[�W����
	void MoveInteria(void);					// �ړ��̊����ɂ��Ă̏���
	void Rotate(CPlayer *pPlayer);			// ��]����

	D3DXVECTOR3 m_rot;						// ����
	D3DXVECTOR3 m_moveOld;					// 1�t���[���O�̈ړ���
	float m_fObjectiveRot;					// �ړI�̌���
	float m_fNumRot;						// ������ς����
	float m_fSpeed;							// �ړ��ʂɉ����鑬��
	bool m_bRotate;							// ��]���Ă��邩�ǂ���
	bool m_bDodge;							// ������Ă��邩�ǂ���
	bool m_bAttack;							// �U�����Ă��邩�ǂ���
	bool m_bDamage;							// �_���[�W���󂯂����ǂ���
	bool m_bStan;							// �X�^�������ǂ���
	int m_nDodgeCount;						// ��𒆂̃J�E���g
	int m_nDodgeCoolTime;					// ����̃N�[���^�C��
	int m_nAttackCount;						// �U�����̃J�E���g
	int m_nAttackCoolTime;					// �U���̃N�[���^�C��
	int m_nKnockBackCount;					// �m�b�N�o�b�N���̃J�E���g
	int m_nStanCount;						// �X�^�����̃J�E���g
	CCollisionSphere *m_pCollision;			// ���̃R���W�����̃|�C���^
};
#endif	//_CONTROL_PLAYER_H_