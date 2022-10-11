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
	bool GetPress(PadButton Button);	//������Ă��邩
	bool GetAnyButton();				//����������Ă��邩
	bool GetTrigger(PadButton Button);	//�g���K�[����
	bool GetRelease(PadButton Button);	//���ꂽ���̏���
	bool GetButton(PadButton Button);	//�����ꂽ����
	float LeftStickX();					//���X�e�B�b�N���E
	float LeftStickY();					//���X�e�B�b�N�㉺
	float TriggerCrossKey();			//�����ꂽ�\���L�[
	float PressCrossKey();				//������Ă�\���L�[
	float RightStickX();				//�E�X�e�B�b�N���E
	float RightStickY();				//�E�X�e�B�b�N�㉺
	static bool GetGamePad();			//�Q�[���p�b�h���q�����Ă邩

private:
	static bool m_bGamePad;
	DIJOYSTATE m_aPadState;              //�Q�[���p�b�h�̓��͏��(�v���X���)
	DIJOYSTATE m_aPadStateTrigger;       //�Q�[���p�b�h�̓��͏��(�g���K�[���)
	DIJOYSTATE m_aPadStateRelease;       //�Q�[���p�b�h�̓��͏��(�������)
};
#endif