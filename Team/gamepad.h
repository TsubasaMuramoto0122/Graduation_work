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

	CGamePad();										// コンストラクタ
	~CGamePad();									// デストラクタ
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// 初期化処理
	void Uninit(void);								// 終了処理
	void Update(void);								// 更新処理
	bool GetPress(int nInput, int nNum);			// 入力状態の取得処理(プレス)
	bool GetTrigger(int nInput, int nNum);			// 入力状態の取得処理(トリガー)
	bool GetButtonPress(int nButton, int nNum);		// ボタン入力状態の取得処理(プレス)
	bool GetButtonTrigger(int nButton, int nNum);	// ボタン入力状態の取得処理(トリガー)
	bool GetConnect(int nNum);						// コントローラ―が接続されているかどうかの取得処理

private:
	// 最大人数は4(XUSER_MAX_COUNT)
	XINPUT_STATE m_aState[XUSER_MAX_COUNT];			// 入力の状態
	XINPUT_STATE m_aStateTrigger[XUSER_MAX_COUNT];	// 入力の状態(トリガー)
	XINPUT_VIBRATION m_aVibration[XUSER_MAX_COUNT];	// バイブレーション
	int m_CntVibration[XUSER_MAX_COUNT];
	bool m_bConnect[XUSER_MAX_COUNT];				// 接続しているかどうか
	bool m_bVibration[XUSER_MAX_COUNT];
};
#endif