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
	bool GetPress(PadButton Button, int nUser);		//押されているか
	bool GetAnyButton(int nUser);					//何か押されているか
	bool GetTrigger(PadButton Button, int nUser);	//トリガー処理
	bool GetRelease(PadButton Button, int nUser);	//離れたかの処理
	bool GetButton(PadButton Button, int nUser);	//押された処理
	float LeftStickX(int nUser);					//左スティック左右
	float LeftStickY(int nUser);					//左スティック上下
	float TriggerCrossKey(int nUser);				//押された十字キー
	float PressCrossKey(int nUser);					//押されてる十字キー
	float RightStickX(int nUser);					//右スティック左右
	float RightStickY(int nUser);					//右スティック上下
	bool GetGamePad(int nUser);						//ゲームパッドが繋がってるか

private:
	bool m_bConnect[XUSER_MAX_COUNT];				//繋がっているかどうか
	DIJOYSTATE m_aPadState[XUSER_MAX_COUNT];		//ゲームパッドの入力情報(プレス情報)
	DIJOYSTATE m_aPadStateTrigger[XUSER_MAX_COUNT];	//ゲームパッドの入力情報(トリガー情報)
	DIJOYSTATE m_aPadStateRelease[XUSER_MAX_COUNT];	//ゲームパッドの入力情報(離す情報)
};
#endif