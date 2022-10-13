//=============================================================================
//
// ���͏��� [keyboard.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_
#include "main.h"
#include "input.h"

//�}�N����`
#define NUM_KEY_MAX (256) //�L�[�̍ő吔

class CKeyboard : CInput
{
public:
	CKeyboard();
	~CKeyboard();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit();
	void Update();
	bool GetPress(int nKey);	//����̃L�[��������Ă��邩
	bool GetAnyKey();			//�����L�[�������ꂽ��
	bool GetTrigger(int nKey);	//����̃L�[�������ꂽ�A�܂��͗��ꂽ��
	bool GetRelease(int nKey);	//����̃L�[�������ꂽ��
	bool GetKey(int nKey);		//����̃L�[�������ꂽ��

private:
	BYTE m_aKeyState[NUM_KEY_MAX];			//�L�[�{�[�h�̓��͏��(�v���X���)
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];	//�L�[�{�[�h�̓��͏��(�g���K�[���)
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];	//�L�[�{�[�h�̓��͏��(�����[�X���)
};
#endif