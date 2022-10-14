//=============================================================================
//
// ���͏��� [gamepad.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _GAMEPAD_H_
#define _GAMEPAD_H_
#include "main.h"
#include "input.h"

class CGamePad : CInput
{
public:
	typedef enum
	{
		PAD_INPUTTYPE_LSTICK_UP = 0,
		PAD_INPUTTYPE_LSTICK_DOWN,
		PAD_INPUTTYPE_LSTICK_LEFT,
		PAD_INPUTTYPE_LSTICK_RIGHT,
		PAD_INPUTTYPE_RSTICK_UP,
		PAD_INPUTTYPE_RSTICK_DOWN,
		PAD_INPUTTYPE_RSTICK_LEFT,
		PAD_INPUTTYPE_RSTICK_RIGHT,
		PAD_INPUTTYPE_LEFT,
		PAD_INPUTTYPE_RIGHT,
		PAD_INPUTTYPE_MAX
	} PAD_INPUTTYPE;

	CGamePad();										// �R���X�g���N�^
	~CGamePad();									// �f�X�g���N�^
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// ����������
	void Uninit(void);								// �I������
	void Update(void);								// �X�V����
	bool GetPress(int nInput, int nNum);			// ���͏�Ԃ̎擾����(�v���X)
	bool GetTrigger(int nInput, int nNum);			// ���͏�Ԃ̎擾����(�g���K�[)
	bool GetButtonPress(int nButton, int nNum);		// �{�^�����͏�Ԃ̎擾����(�v���X)
	bool GetButtonTrigger(int nButton, int nNum);	// �{�^�����͏�Ԃ̎擾����(�g���K�[)
	bool GetConnect(int nNum);						// �R���g���[���\���ڑ�����Ă��邩�ǂ����̎擾����

private:
	// �ő�l����4(XUSER_MAX_COUNT)
	XINPUT_STATE m_aState[XUSER_MAX_COUNT];			// ���͂̏��
	XINPUT_STATE m_aStateTrigger[XUSER_MAX_COUNT];	// ���͂̏��(�g���K�[)
	XINPUT_VIBRATION m_aVibration[XUSER_MAX_COUNT];	// �o�C�u���[�V����
	int m_CntVibration[XUSER_MAX_COUNT];
	bool m_bConnect[XUSER_MAX_COUNT];				// �ڑ����Ă��邩�ǂ���
	bool m_bVibration[XUSER_MAX_COUNT];
};
#endif