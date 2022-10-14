//=============================================================================
//
// ゲームパッド入力処理 [gamepad.h]
// Author : 三上航世
//
//=============================================================================
#include "gamepad.h"

CGamePad::CGamePad()
{
	m_pDevice = NULL;;

	for (int nCntPad = 0; nCntPad < XUSER_MAX_COUNT; nCntPad++)
	{
		// 変数のクリア
		ZeroMemory(&m_aState[nCntPad], sizeof(XINPUT_STATE));			// 入力情報(プレス)
		ZeroMemory(&m_aStateTrigger, sizeof(XINPUT_STATE));				// 入力情報(トリガー)
		m_bConnect[nCntPad] = false;
	}
}

CGamePad::~CGamePad()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CGamePad::Init(HINSTANCE hInstance, HWND hWnd)
{
	// 基本クラスの初期化処理
	CInput::Init(hInstance, hWnd);

	// 変数の初期化
	for (int nCntPad = 0; nCntPad < XUSER_MAX_COUNT; nCntPad++)
	{
		m_bConnect[nCntPad] = false;
	}

	XINPUT_STATE state[XUSER_MAX_COUNT];
	for (int nCntPad = 0; nCntPad < XUSER_MAX_COUNT; nCntPad++)
	{
		ZeroMemory(&state[nCntPad], sizeof(XINPUT_STATE));
	}

	// コントローラーが接続されているか確認する
	for (int nCntPad = 0; nCntPad < XUSER_MAX_COUNT; nCntPad++)
	{
		DWORD dwResult = XInputGetState(nCntPad, &state[nCntPad]);

		if (dwResult == ERROR_SUCCESS)
		{
			// コントローラーは接続している状態
			m_bConnect[nCntPad] = true;
		}
		else
		{
			// コントローラーは接続されていない状態
			m_bConnect[nCntPad] = false;
		}
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CGamePad::Uninit(void)
{
	// 入力情報をニュートラルにする
	XInputEnable(false);

	// 基本クラスの終了処理
	CInput::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CGamePad::Update(void)
{
	XINPUT_STATE state[XUSER_MAX_COUNT];

	for (int nCntPad = 0; nCntPad < XUSER_MAX_COUNT; nCntPad++)
	{
		ZeroMemory(&state[nCntPad], sizeof(XINPUT_STATE));
	}

	for (int nCntPad = 0; nCntPad < XUSER_MAX_COUNT; nCntPad++)
	{
		DWORD dwResult = XInputGetState(nCntPad, &state[nCntPad]);

		// コントローラーが接続されているか確認する
		if (dwResult == ERROR_SUCCESS)
		{
			m_bConnect[nCntPad] = true;
		}
		else
		{
			m_bConnect[nCntPad] = false;
		}
	}

	for (int nCntPad = 0; nCntPad < XUSER_MAX_COUNT; nCntPad++)
	{
		if (XInputGetState(nCntPad, &state[nCntPad]) == ERROR_SUCCESS)
		{
			// 左スティックのデッドゾーンの設定
			if ((m_aState[nCntPad].Gamepad.sThumbLX <= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
				m_aState[nCntPad].Gamepad.sThumbLX >= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
				(m_aState[nCntPad].Gamepad.sThumbLY <= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
					m_aState[nCntPad].Gamepad.sThumbLY >= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
			{
				m_aState[nCntPad].Gamepad.sThumbLX = 0;
				m_aState[nCntPad].Gamepad.sThumbLY = 0;
			}

			// 右スティックのデッドゾーンの設定
			if ((m_aState[nCntPad].Gamepad.sThumbRX <= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
				m_aState[nCntPad].Gamepad.sThumbRX >= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) &&
				(m_aState[nCntPad].Gamepad.sThumbRY <= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
					m_aState[nCntPad].Gamepad.sThumbRY >= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE))
			{
				m_aState[nCntPad].Gamepad.sThumbRX = 0;
				m_aState[nCntPad].Gamepad.sThumbRY = 0;
			}

			m_aStateTrigger[nCntPad] = m_aState[nCntPad];
			m_aState[nCntPad] = state[nCntPad];
		}
	}
}

//=============================================================================
// 入力状態の取得処理(プレス)
//=============================================================================
bool CGamePad::GetPress(int nInput, int nNum)
{
	// 接続していない場合はfalseを返して処理を終了させる
	//※これがないと勝手に入力され続ける
	if (m_bConnect[nNum] == false)
	{
		return false;
	}

	switch (nInput)
	{
	case PAD_INPUTTYPE_LSTICK_UP:	// 左スティック：上
		return m_aState[nNum].Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ? true : false;
		break;
	case PAD_INPUTTYPE_LSTICK_DOWN:	// 左スティック：下
		return m_aState[nNum].Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ? true : false;
		break;
	case PAD_INPUTTYPE_LSTICK_LEFT:	// 左スティック：左
		return m_aState[nNum].Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ? true : false;
		break;
	case PAD_INPUTTYPE_LSTICK_RIGHT:// 左スティック：右
		return m_aState[nNum].Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ? true : false;
		break;
	case PAD_INPUTTYPE_RSTICK_UP:	// 右スティック：上
		return m_aState[nNum].Gamepad.sThumbRY > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ? true : false;
		break;
	case PAD_INPUTTYPE_RSTICK_DOWN:	// 右スティック：下
		return m_aState[nNum].Gamepad.sThumbRY < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ? true : false;
		break;
	case PAD_INPUTTYPE_RSTICK_LEFT:	// 右スティック：左
		return m_aState[nNum].Gamepad.sThumbRX < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ? true : false;
		break;
	case PAD_INPUTTYPE_RSTICK_RIGHT:// 右スティック：右
		return m_aState[nNum].Gamepad.sThumbRX > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ? true : false;
		break;
	case PAD_INPUTTYPE_LEFT:		// トリガー：左
		return m_aState[nNum].Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD ? true : false;
		break;
	case PAD_INPUTTYPE_RIGHT:		// トリガー：右
		return m_aState[nNum].Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD ? true : false;
		break;
	default:
		return false;
		break;
	}
}

//=============================================================================
// 入力状態の取得処理(トリガー)
//=============================================================================
bool CGamePad::GetTrigger(int nInput, int nNum)
{
	if (m_bConnect[nNum] == false)
	{
		return false;
	}

	switch (nInput)
	{
	case PAD_INPUTTYPE_LSTICK_UP:	// 左スティック：上
		return (((m_aStateTrigger[nNum].Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) == false) && (m_aState[nNum].Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;
	case PAD_INPUTTYPE_LSTICK_DOWN:	// 左スティック：下
		return (((m_aStateTrigger[nNum].Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) == false) && (m_aState[nNum].Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;
	case PAD_INPUTTYPE_LSTICK_LEFT:	// 左スティック：左
		return (((m_aStateTrigger[nNum].Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) == false) && (m_aState[nNum].Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;
	case PAD_INPUTTYPE_LSTICK_RIGHT:// 左スティック：右
		return (((m_aStateTrigger[nNum].Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) == false) && (m_aState[nNum].Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;
	case PAD_INPUTTYPE_RSTICK_UP:	// 右スティック：上
		return (((m_aStateTrigger[nNum].Gamepad.sThumbRY > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) == false) && (m_aState[nNum].Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;
	case PAD_INPUTTYPE_RSTICK_DOWN:	// 右スティック：下
		return (((m_aStateTrigger[nNum].Gamepad.sThumbRY < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) == false) && (m_aState[nNum].Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;
	case PAD_INPUTTYPE_RSTICK_LEFT:	// 右スティック：左
		return (((m_aStateTrigger[nNum].Gamepad.sThumbRX < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) == false) && (m_aState[nNum].Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;
	case PAD_INPUTTYPE_RSTICK_RIGHT:// 右スティック：右
		return (((m_aStateTrigger[nNum].Gamepad.sThumbRX > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) == false) && (m_aState[nNum].Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;
	case PAD_INPUTTYPE_LEFT:	// トリガー：左
		return (((m_aStateTrigger[nNum].Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) == false) && (m_aState[nNum].Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)) ? true : false;
		break;
	case PAD_INPUTTYPE_RIGHT:	// トリガー：右
		return (((m_aStateTrigger[nNum].Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) == false) && (m_aState[nNum].Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)) ? true : false;
		break;
	default:
		return false;
		break;
	}
}

//=============================================================================
// ボタン入力状態の取得処理(プレス)
//=============================================================================
bool CGamePad::GetButtonPress(int nButton, int nNum)
{
	if (m_bConnect[nNum] == false)
	{
		return false;
	}

	return m_aState[nNum].Gamepad.wButtons & nButton ? true : false;
}

//=============================================================================
// ボタン入力状態の取得処理(トリガー)
//=============================================================================
bool CGamePad::GetButtonTrigger(int nButton, int nNum)
{
	if (m_bConnect[nNum] == false)
	{
		return false;
	}

	return (((m_aStateTrigger[nNum].Gamepad.wButtons & nButton) == false) && (m_aState[nNum].Gamepad.wButtons & nButton)) ? true : false;
}

//=======================================================================
// バイブレーション設定
//= ======================================================================
//void CInputPad::SetVibration(int nLeftSpeed, int nRightSpeed, int nCntEnd, int nCntPad)
//{
//	m_avibration[nCntPad].wLeftMotorSpeed = nLeftSpeed;
//	m_avibration[nCntPad].wRightMotorSpeed = nRightSpeed;
//	XInputSetState(nCntPad, &m_avibration[nCntPad]);
//	m_aCntVibration[nCntPad] = nCntEnd;
//	m_aVibration[nCntPad] = true;
//}

//=============================================================================
// コントローラ―が接続されているかどうかの取得処理
//=============================================================================
bool CGamePad::GetConnect(int nNum)
{
	return m_bConnect[nNum];
}