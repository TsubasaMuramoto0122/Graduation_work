//=============================================================================
// AI���쏈�� [cpu.h]
// Author : �O��@�q��
//=============================================================================
#ifndef _CPU_H_
#define _CPU_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "control.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PLAYER_KNOCKBACK_JUMP		(6.5f)	// �m�b�N�o�b�N�̃W�����v��
#define PLAYER_DEFEATKNOCKBACK_JUMP	(11.0f)	// �s�k���̃m�b�N�o�b�N�̃W�����v��

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CScene;
class CPlayer;
class CCollisionSphere;

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CCPU : public CControl
{
public:
	CCPU();										// �R���X�g���N�^
	~CCPU();									// �f�X�g���N�^
	HRESULT Init(void);							// ����������
	void Uninit(void);							// �I������
	void Update(CScene *pScene);				// �X�V����
	static CCPU *Create(void);					// ��������

private:
	void Move();				// �ړ�����
	void Sliding(CPlayer *pPlayer);				// �X���C�f�B���O(���)����
	void Attack(CPlayer *pPlayer);				// �U������
	void TakeDamage(CPlayer *pPlayer);			// ��_���[�W����
	void Defeat(CPlayer *pPlayer);				// �s�k����

	void MoveInteria(void);						// �ړ��̊����ɂ��Ă̏���
	void Rotate(CPlayer *pPlayer);				// ��]����
	bool SetMove();	// �ړ��ʂ̉��Z����іړI�̌����̐ݒ�

	D3DXVECTOR3 m_rot;							// ����
	float m_fObjectiveRot;						// �ړI�̌���
	float m_fNumRot;							// ������ς����
	float m_fSpeed;								// �ړ��ʂɉ����鑬��
	bool m_bRotate;								// ��]���Ă��邩�ǂ���
	bool m_bAttack;								// �U�����Ă��邩�ǂ���
	bool m_bDamage;								// �_���[�W���󂯂����ǂ���
	bool m_bStan;								// �X�^�������ǂ���
	bool m_bSliding;							// �X���C�f�B���O(���)���Ă��邩�ǂ���
	bool m_bDefeat;								// �s�k�������ǂ���
	int m_nSlidingCount;						// �X���C�f�B���O(���)���̃J�E���g
	int m_nSlidingCoolTime;						// �X���C�f�B���O(���)�̃N�[���^�C��
	int m_nAttackCount;							// �U�����̃J�E���g
	int m_nAttackCoolTime;						// �U���̃N�[���^�C��
	int m_nStanCount;							// �X�^�����̃J�E���g
	CCollisionSphere *m_pCollision;				// ���̃R���W�����̃|�C���^

	bool m_bMove;								// �ړ����Ă��邩�ǂ���
	bool m_bThink;								// �l���Ă��邩
	int m_nMoveTime;							// �ړ����鎞��
	int m_nThinkTime;							// �v�l����
	float m_fMoveRot;							// �ړ��������
};
#endif	//_CONTROL_PLAYER_H_