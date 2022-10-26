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

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CScene;
class CPlayer;
class CCollisionSphere;
class CPauseUI;

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
	void Sliding(CPlayer *pPlayer);			// �X���C�f�B���O(���)����
	void Attack(CPlayer *pPlayer);			// �U������
	void TakeDamage(CPlayer *pPlayer);		// ��_���[�W����
	void Defeat(CPlayer *pPlayer);			// �s�k����

	void Pause(CPlayer *pPlayer);			// �|�[�Y����
	void PauseChange(int nAdd);
	void PauseSelect();
	//void Jump(CPlayer *pPlayer);			// �W�����v����

	void MoveInteria(CPlayer *pPlayer);		// �ړ��̊����ɂ��Ă̏���
	void Rotate(CPlayer *pPlayer);			// ��]����
	bool SetMove(float fRotCamera, float fRot);

	D3DXVECTOR3 m_rot;						// ����
	float m_fObjectiveRot;					// �ړI�̌���
	float m_fNumRot;						// ������ς����
	float m_fSpeed;							// �ړ��ʂɉ����鑬��
	bool m_bRotate;							// ��]���Ă��邩�ǂ���
	bool m_bAttack;							// �U�����Ă��邩�ǂ���
	bool m_bDamage;							// �_���[�W���󂯂����ǂ���
	bool m_bStan;							// �X�^�������ǂ���
	bool m_bSliding;						// �X���C�f�B���O(���)���Ă��邩�ǂ���
	bool m_bDefeat;							// �s�k�������ǂ���
	bool m_bMove;							// �ړ����Ă��邩
	int m_nSlidingCount;					// �X���C�f�B���O(���)���̃J�E���g
	int m_nSlidingCoolTime;					// �X���C�f�B���O(���)�̃N�[���^�C��
	int m_nAttackCount;						// �U�����̃J�E���g
	int m_nAttackCoolTime;					// �U���̃N�[���^�C��
	int m_nStanCount;						// �X�^�����̃J�E���g
	CCollisionSphere *m_pCollision;			// ���̃R���W�����̃|�C���^

	static int m_nPause;					// �N���|�[�Y������
	static int m_nSelectPause;				// �|�[�Y�̑I��ԍ�
	static CPauseUI *m_pUI[3];					// �|�[�YUI
};
#endif	//_CONTROL_PLAYER_H_