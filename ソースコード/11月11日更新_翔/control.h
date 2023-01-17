//=============================================================================
// �R���g���[������ [control.h]
// Author : Kusakari Kakeru
//=============================================================================
#ifndef _CONTROL_H_
#define _CONTROL_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PLAYER_GRAVITY				(0.5f)	// �d�͂̑傫��
#define PLAYER_GRAVITY_DAMAGE		(1.1f)	// ��_���[�W���̏d�͂̑傫��
#define PLAYER_GRAVITY_DEFEAT		(0.2f)	// �s�k���̏d�͂̑傫��
#define PLAYER_MOVE_SPEED			(0.4f)	// �ړ��ʂ̊�l
#define PLAYER_INTERIA_SUBTRACTION	(0.86f)	// �n��ł̊����̌��Z�l
#define PLAYER_MOVE_STOP_COUNT		(0.02f)	// �v���C���[�̈ړ��ʂ�0�ɂ��鎞�̈ړ��ʂ̒l
#define PLAYER_MAX_GRAVITY			(26.0f)	// �d�͂̍ő�l
#define PLAYER_ATTACK_TIME			(15)	// �U������
#define PLAYER_ATTACK_WAITTIME		(13)	// �U����̍d������
#define PLAYER_ATTACK_COOLTIME		(10)	// �U����A�ĂэU���ł���܂ł̎���
//#define PLAYER_SLIDING_MOVE		(1.2f)	// �X���C�f�B���O(���)�̈ړ��ʂ̊�l
#define PLAYER_SLIDING_TIME			(30)	// �X���C�f�B���O(���)����
#define PLAYER_SLIDING_WAITTIME		(14)	// �X���C�f�B���O(���)��̍d������
#define PLAYER_SLIDING_COOLTIME		(30)	// �X���C�f�B���O(���)��A�Ăщ�����g����܂ł̎���
//#define PLAYER_JUMP				(8.0f)	// �W�����v��
#define PLAYER_KNOCKBACK			(7.0f)	// �m�b�N�o�b�N�̑傫��
//#define PLAYER_KNOCKBACK_TIME		(4)		// �m�b�N�o�b�N�̎���
#define PLAYER_KNOCKBACK_STAN		(74)	// �m�b�N�o�b�N��̃X�^���̎���
#define PLAYER_GETUP_TIME			(20)	// �X�^�����A�N���オ�鎞��
#define PLAYER_DEFEAT_KNOCKBACK		(19.0f)	// �s�k���̃m�b�N�o�b�N�̑傫��
#define MAX_MOVE					(3.6f)	// ���E�̈ړ���
#define MAX_SLIDE					(6.0f)	// ���E�̃X���C�h��
#define PLAYER_KNOCKBACK_JUMP		(8.0f)	// �m�b�N�o�b�N�̃W�����v��
#define PLAYER_DEFEATKNOCKBACK_JUMP	(12.0f)	// �s�k���̃m�b�N�o�b�N�̃W�����v��

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CScene;

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CControl
{
public:
	CControl();									// �R���X�g���N�^
	virtual ~CControl();						// �f�X�g���N�^
	virtual HRESULT Init(void) = 0;				// ����������
	virtual void Uninit(void) = 0;				// �I������
	virtual void Update(CScene *pScene) = 0;	// �X�V����
	D3DXVECTOR3 GetMove(void);					// �ړ��ʂ̎擾����

protected:
	D3DXVECTOR3 m_move;							// �ړ���
};

#endif	// _CONTROL_H_