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

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CScene;
class CPlayer;
class CBomb;
class CCollisionSphere;

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CCPU : public CControl
{
	//�l����
	typedef enum
	{
		THINK_NONE,		// �������Ȃ�
		THINK_BOMB,		// ���e�ɍU��
		THINK_PLAYER,	// �v���C���[�ɍU��
		THINK_MOVE,		// �ǂ����ɓ���
		THINK_SLIDING,	// �X���C�f�B���O
		MAX_THINK
	} THINKTYPE;

public:
	CCPU();										// �R���X�g���N�^
	~CCPU();									// �f�X�g���N�^
	HRESULT Init(void);							// ����������
	void Uninit(void);							// �I������
	void Update(CScene *pScene);				// �X�V����
	static CCPU *Create(void);					// ��������

private:
	void Move(CPlayer *pPlayer);					// �ړ�����
	void Sliding(CPlayer *pPlayer);				// �X���C�f�B���O(���)����
	void Attack(CPlayer *pPlayer);				// �U������
	void TakeDamage(CPlayer *pPlayer);			// ��_���[�W����
	void Defeat(CPlayer *pPlayer);				// �s�k����

	void MoveInteria(CPlayer *pPlayer);			// �ړ��̊����ɂ��Ă̏���
	void Rotate(CPlayer *pPlayer);				// ��]����
	bool SetMove();								// �ړ��ʂ̉��Z����іړI�̌����̐ݒ�
	void Search(CPlayer *pPlayer);				// ��ԋ߂��v���C���[�Ɣ��e��T��

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
	CPlayer *m_pPlayer;							// ��ԋ߂��v���C���[
	CBomb *m_pBomb;								// ��ԋ߂����e

	bool m_bMove;								// �ړ����Ă��邩�ǂ���
	int m_nMoveTime;							// �ړ����鎞��
	int m_nThinkTime;							// �v�l����
	float m_fMoveRot;							// �ړ��������
	THINKTYPE m_thinkType;						// �����悤�Ƃ��Ă邩
	bool m_bNextAttack;							// ���U������
	bool m_bNextSliding;						// ���������
	bool m_bWall;								// �ǂɓ���������
};
#endif	//_CONTROL_PLAYER_H_