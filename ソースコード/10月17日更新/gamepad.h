//=============================================================================
// �Q�[���p�b�h���͏��� [gamepad.h]
// Author : Kusakari Kakeru
//=============================================================================
#ifndef _GAMEPAD_H_
#define _GAMEPAD_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "input.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CGamePad : CInput
{
public:
	typedef enum
	{
		PAD_INPUTTYPE_LSTICK_UP = 0,	// ���X�e�B�b�N�F��
		PAD_INPUTTYPE_LSTICK_DOWN,		// ���X�e�B�b�N�F��
		PAD_INPUTTYPE_LSTICK_LEFT,		// ���X�e�B�b�N�F��
		PAD_INPUTTYPE_LSTICK_RIGHT,		// ���X�e�B�b�N�F�E
		PAD_INPUTTYPE_RSTICK_UP,		// �E�X�e�B�b�N�F��
		PAD_INPUTTYPE_RSTICK_DOWN,		// �E�X�e�B�b�N�F��
		PAD_INPUTTYPE_RSTICK_LEFT,		// �E�X�e�B�b�N�F��
		PAD_INPUTTYPE_RSTICK_RIGHT,		// �E�X�e�B�b�N�F�E
		PAD_INPUTTYPE_LEFT_TRIGGER,		// ���g���K�[
		PAD_INPUTTYPE_RIGHT_TRIGGER,	// �E�g���K�[
		PAD_INPUTTYPE_MAX
	} PAD_INPUTTYPE;

	CGamePad();									// �R���X�g���N�^
	~CGamePad();									// �f�X�g���N�^
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// ����������
	void Uninit(void);								// �I������
	void Update(void);								// �X�V����
	bool GetPress(int nInput, int nNum);			// ���͏�Ԃ̎擾����(�v���X)
	bool GetTrigger(int nInput, int nNum);			// ���͏�Ԃ̎擾����(�g���K�[)
	bool GetRelease(int nInput, int nNum);			// ���͏�Ԃ̎擾����(�����[�X)
	bool GetButtonPress(int nButton, int nNum);		// �{�^�����͏�Ԃ̎擾����(�v���X)
	bool GetButtonTrigger(int nButton, int nNum);	// �{�^�����͏�Ԃ̎擾����(�g���K�[)
	bool GetButtonRelease(int nButton, int nNum);	// �{�^�����͏�Ԃ̎擾����(�����[�X)
	bool GetConnect(int nNum);						// �R���g���[���\���ڑ�����Ă��邩�ǂ����̎擾����

private:
	// �ő�l����4(XUSER_MAX_COUNT)
	XINPUT_STATE m_aState[XUSER_MAX_COUNT];			// ���͂̏��
	XINPUT_STATE m_aStateTrigger[XUSER_MAX_COUNT];	// ���͂̏��(�g���K�[)
	XINPUT_STATE m_aStateRelease[XUSER_MAX_COUNT];	// ���͂̏��(�����[�X)
	bool m_bConnect[XUSER_MAX_COUNT];				// �ڑ����Ă��邩�ǂ���
};
#endif