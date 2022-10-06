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
// �O���錾
//*****************************************************************************
class CScene;
class CPlayer;

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PLAYER_GRAVITY				(0.6f)	// �d�͂̑傫��
#define PLAYER_MAX_GRAVITY			(15.0f)	// �d�͂̍ő�l
#define PLAYER_MOVE_SPEED			(1.8f)	// �ړ��ʂ̊�l
#define PLAYER_INTERIA_SUBTRACTION	(0.86f)	// �n��ł̊����̌��Z�l
#define PLAYER_MOVE_STOP_COUNT		(0.02f)	// �v���C���[�̈ړ��ʂ�0�ɂ��鎞�̈ړ��ʂ̒l

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
	void Move(void);						// �ړ�����
	void Dodge(void);						// �������
	void MoveInteria(void);					// �ړ��̊����ɂ��Ă̏���
	void Rotate(CPlayer *pPlayer);			// ��]����

	D3DXVECTOR3 m_rot;						// ����
	D3DXVECTOR3 m_moveOld;					// 1�t���[���O�̈ړ���
	float m_fObjectiveRot;					// �ړI�̌���
	float m_fNumRot;						// ������ς����
	float m_fSpeed;							// �ړ��ʂɉ����鑬��
	bool m_bDodge;							// ������Ă��邩�ǂ���
	bool m_bRotate;							// ��]���Ă��邩�ǂ���
};

#endif	//_CONTROL_PLAYER_H_