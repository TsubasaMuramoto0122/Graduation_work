//=============================================================================
//
// 入力処理 [gamepad.h]
// Author : 三上航世
//
//=============================================================================
#ifndef _GAMEPAD_H_
#define _GAMEPAD_H_
#include "main.h"
#include "input.h"

class CGamePad : CInput
{
public:
	//ゲームパッドのボタン
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
	bool GetPress(PadButton Button);	//押されているか
	bool GetAnyButton();				//何か押されているか
	bool GetTrigger(PadButton Button);	//トリガー処理
	bool GetRelease(PadButton Button);	//離れたかの処理
	bool GetButton(PadButton Button);	//押された処理
	float LeftStickX();					//左スティック左右
	float LeftStickY();					//左スティック上下
	float TriggerCrossKey();			//押された十字キー
	float PressCrossKey();				//押されてる十字キー
	float RightStickX();				//右スティック左右
	float RightStickY();				//右スティック上下
	static bool GetGamePad();			//ゲームパッドが繋がってるか

private:
	static bool m_bGamePad;
	DIJOYSTATE m_aPadState;              //ゲームパッドの入力情報(プレス情報)
	DIJOYSTATE m_aPadStateTrigger;       //ゲームパッドの入力情報(トリガー情報)
	DIJOYSTATE m_aPadStateRelease;       //ゲームパッドの入力情報(離す情報)
};
#endif