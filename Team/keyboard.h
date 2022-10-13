//=============================================================================
//
// 入力処理 [keyboard.h]
// Author : 三上航世
//
//=============================================================================
#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_
#include "main.h"
#include "input.h"

//マクロ定義
#define NUM_KEY_MAX (256) //キーの最大数

class CKeyboard : CInput
{
public:
	CKeyboard();
	~CKeyboard();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit();
	void Update();
	bool GetPress(int nKey);	//特定のキーが押されているか
	bool GetAnyKey();			//何かキーが押されたか
	bool GetTrigger(int nKey);	//特定のキーが押された、または離れたか
	bool GetRelease(int nKey);	//特定のキーが離されたか
	bool GetKey(int nKey);		//特定のキーが押されたか

private:
	BYTE m_aKeyState[NUM_KEY_MAX];			//キーボードの入力情報(プレス情報)
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];	//キーボードの入力情報(トリガー情報)
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];	//キーボードの入力情報(リリース情報)
};
#endif