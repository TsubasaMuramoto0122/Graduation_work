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
	//�Q�[���p�b�h�̃{�^��
	typedef enum
	{
		DIP_X = 0,
		DIP_Y,
		DIP_A,
		DIP_B,
		DIP_L1,
		DIP_R1,
		DIP_L2,
		DIP_R2,
		DIP_LS,
		DIP_RS,
		DIP_BACK,
		DIP_START,
		DIP_GUIDE,
		DIP_MAX
	} PadButton;

	CGamePad();
	~CGamePad();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit();
	void Update();
	bool GetPress(PadButton Button, int nUser);		//������Ă��邩
	bool GetAnyButton(int nUser);					//����������Ă��邩
	bool GetTrigger(PadButton Button, int nUser);	//�g���K�[����
	bool GetRelease(PadButton Button, int nUser);	//���ꂽ���̏���
	bool GetButton(PadButton Button, int nUser);	//�����ꂽ����
	float LeftStickX(int nUser);					//���X�e�B�b�N���E
	float LeftStickY(int nUser);					//���X�e�B�b�N�㉺
	float TriggerCrossKey(int nUser);				//�����ꂽ�\���L�[
	float PressCrossKey(int nUser);					//������Ă�\���L�[
	float RightStickX(int nUser);					//�E�X�e�B�b�N���E
	float RightStickY(int nUser);					//�E�X�e�B�b�N�㉺
	bool GetGamePad(int nUser);						//�Q�[���p�b�h���q�����Ă邩

private:
	bool m_bConnect[XUSER_MAX_COUNT];				//�q�����Ă��邩�ǂ���
	DIJOYSTATE m_aPadState[XUSER_MAX_COUNT];		//�Q�[���p�b�h�̓��͏��(�v���X���)
	DIJOYSTATE m_aPadStateTrigger[XUSER_MAX_COUNT];	//�Q�[���p�b�h�̓��͏��(�g���K�[���)
	DIJOYSTATE m_aPadStateRelease[XUSER_MAX_COUNT];	//�Q�[���p�b�h�̓��͏��(�������)
};
#endif