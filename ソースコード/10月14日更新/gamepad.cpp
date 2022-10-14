//=============================================================================
//
// ゲームパッド入力処理 [gamepad.h]
// Author : 三上航世
//
//=============================================================================
#include "gamepad.h"

BOOL CALLBACK DeviceFindCallBack(LPCDIDEVICEINSTANCE ipddi, LPVOID pvRef);

CGamePad::CGamePad()
{
	m_pDevice = NULL;;

	for (int nCntPad = 0; nCntPad < XUSER_MAX_COUNT; nCntPad++)
	{
		// 変数のクリア
		ZeroMemory(&m_aPadState[nCntPad], sizeof(XINPUT_STATE));			// 入力情報(プレス)
		ZeroMemory(&m_aPadStateTrigger, sizeof(XINPUT_STATE));				// 入力情報(トリガー)
		ZeroMemory(&m_aPadStateRelease[nCntPad], sizeof(XINPUT_VIBRATION));	// 入力情報(リリース)
		m_bConnect[nCntPad] = false;
	}
}

CGamePad::~CGamePad()
{

}

HRESULT CGamePad::Init(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInitオブジェクトの生成
	CInput::Init(hInstance, hWnd);

	// 変数の初期化
	for (int nCntPad = 0; nCntPad < XUSER_MAX_COUNT; nCntPad++)
	{
		m_bConnect[nCntPad] = false;
	}

	//接続されてるゲームパッドの列挙
	if (FAILED(m_pInput->EnumDevices(DI8DEVCLASS_GAMECTRL, DeviceFindCallBack, NULL, DIEDFL_ATTACHEDONLY)))
	{
		return E_FAIL;
	}
	//入力デバイスの生成
	if (FAILED(m_pInput->CreateDevice(GUID_Joystick, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	// データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIJoystick)))
	{
		return E_FAIL;
	}
	// 軸モードを絶対値モードとして設定
	DIPROPDWORD diprop;
	ZeroMemory(&diprop, sizeof(diprop));
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.diph.dwObj = 0;
	diprop.dwData = DIPROPAXISMODE_ABS;

	// 軸モードを変更
	if (FAILED(m_pDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		return E_FAIL;
	}

	// X軸の値の範囲設定
	DIPROPRANGE diprg;
	ZeroMemory(&diprg, sizeof(diprg));
	diprg.diph.dwSize = sizeof(diprg);
	diprg.diph.dwHeaderSize = sizeof(diprg.diph);
	diprg.diph.dwHow = DIPH_BYOFFSET;
	diprg.diph.dwObj = DIJOFS_X;
	diprg.lMin = -1000;
	diprg.lMax = 1000;
	
	if (FAILED(m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph)))
	{
		return E_FAIL;
	}

	// Y軸の値の範囲設定
	diprg.diph.dwObj = DIJOFS_Y;
	if (FAILED(m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph)))
	{
		return E_FAIL;
	}

	// 協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	// ゲームパッドへのアクセス権を獲得(入力制御開始)
	m_pDevice->Acquire();
	//処理を同期させる
	m_pDevice->Poll();

	// コントローラーが接続されているか確認する
	XINPUT_STATE state[XUSER_MAX_COUNT];

	for (int nCntPad = 0; nCntPad < XUSER_MAX_COUNT; nCntPad++)
	{
		ZeroMemory(&state[nCntPad], sizeof(XINPUT_STATE));
	}

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

void CGamePad::Uninit()
{
	// 入力情報をニュートラルにする
	XInputEnable(false);

	CInput::Uninit();
}

void CGamePad::Update()
{
	XINPUT_STATE state[XUSER_MAX_COUNT];
	for (int nCntPad = 0; nCntPad < XUSER_MAX_COUNT; nCntPad++)
	{
		ZeroMemory(&state[nCntPad], sizeof(XINPUT_STATE));
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

	DIJOYSTATE aPadState;
	int nCntPad;
	// 最大人数ぶん回す
	for (int nCntXUser = 0; nCntXUser < XUSER_MAX_COUNT; nCntXUser++)
	{
		//入力デバイスからデータを取得する
		if (m_bConnect[nCntXUser] == true && m_pDevice->GetDeviceState(sizeof(aPadState), &aPadState) == ERROR_SUCCESS)
		{
			for (nCntPad = 0; nCntPad < DIP_MAX; nCntPad++)
			{
				m_aPadStateTrigger[nCntXUser].rgbButtons[nCntPad] = m_aPadState[nCntXUser].rgbButtons[nCntPad] ^ aPadState.rgbButtons[nCntPad] & aPadState.rgbButtons[nCntPad];
				m_aPadStateRelease[nCntXUser].rgbButtons[nCntPad] = (m_aPadState[nCntXUser].rgbButtons[nCntPad] ^ aPadState.rgbButtons[nCntPad]) & m_aPadState[nCntXUser].rgbButtons[nCntPad];
				m_aPadState[nCntXUser].rgbButtons[nCntPad] = aPadState.rgbButtons[nCntPad]; //パッドの入力情報保存
			}
			m_aPadState[nCntXUser].lX = aPadState.lX;
			m_aPadState[nCntXUser].lY = aPadState.lY;
			m_aPadState[nCntXUser].lZ = aPadState.lZ;
			m_aPadState[nCntXUser].lRz = aPadState.lRz;
			m_aPadStateTrigger[nCntXUser].rgdwPOV[nCntXUser] = m_aPadState[nCntXUser].rgdwPOV[nCntXUser];
			m_aPadState[nCntXUser].rgdwPOV[nCntXUser] = aPadState.rgdwPOV[nCntXUser];
		}
		// 接続されているコントローラーのみ取得する
		else if(m_bConnect[nCntXUser] == true)
		{
			m_pDevice->Acquire();
		}
	}
}

BOOL CALLBACK DeviceFindCallBack(LPCDIDEVICEINSTANCE ipddi, LPVOID pvRef)
{
	ipddi; pvRef;
	return DIENUM_CONTINUE;
}

bool CGamePad::GetAnyButton(int nUser)
{
	// 接続していないコントローラ―はfalseを返して処理を終了させる
	if (GetGamePad(nUser) == false)
	{
		return false;
	}

	int nCntPad;
	for (nCntPad = 0; nCntPad < DIP_MAX; nCntPad++)
	{
		if ((m_aPadStateTrigger[nUser].rgbButtons[nCntPad] & 0x80) != 0 && (m_aPadStateRelease[nUser].rgbButtons[nCntPad] & 0x80) == 0)
		{
			return true;
		}
	}
	return false;
}

bool CGamePad::GetButton(CGamePad::PadButton Button, int nUser)
{
	if (GetGamePad(nUser) == false)
	{
		return false;
	}

	if ((m_aPadStateTrigger[nUser].rgbButtons[Button] & 0x80) != 0 && (m_aPadStateRelease[nUser].rgbButtons[Button] & 0x80) == 0)
	{
		return true;
	}
	return false;
}

bool CGamePad::GetPress(CGamePad::PadButton Button, int nUser)
{
	if (GetGamePad(nUser) == false)
	{
		return false;
	}

	return (m_aPadState[nUser].rgbButtons[Button] & 0x80) ? true : false;
}

bool CGamePad::GetRelease(CGamePad::PadButton Button, int nUser)
{
	if (GetGamePad(nUser) == false)
	{
		return false;
	}

	return (m_aPadStateRelease[nUser].rgbButtons[Button] & 0x80) ? true : false;
}

bool CGamePad::GetTrigger(CGamePad::PadButton Button, int nUser)
{
	if (GetGamePad(nUser) == false)
	{
		return false;
	}

	return (m_aPadStateTrigger[nUser].rgbButtons[Button] & 0x80) ? true : false;
}

float CGamePad::TriggerCrossKey(int nUser)
{
	if (GetGamePad(nUser) == false)
	{
		return false;
	}

	//十字キーが入力されてるか
	if (m_aPadState[nUser].rgdwPOV[0] != 0xFFFFFFFF)
	{
		//直前に押された方向と違うか（同じだったら無視する）
		if (m_aPadStateTrigger[nUser].rgdwPOV[nUser] != m_aPadState[nUser].rgdwPOV[nUser])
		{
			return (float)m_aPadState[nUser].rgdwPOV[nUser];
		}
	}
	return 10.0f; //何も押されてなかったとき用
}

float CGamePad::PressCrossKey(int nUser)
{
	if (GetGamePad(nUser) == false)
	{
		return false;
	}

	//十字キーが入力されてるか
	if (m_aPadState[nUser].rgdwPOV[nUser] != 0xFFFFFFFF)
	{
		return (float)m_aPadState[nUser].rgdwPOV[nUser];
	}
	return 10.0f; //何も押されてなかったとき用
}

float CGamePad::LeftStickX(int nUser)
{
	if (GetGamePad(nUser) == false)
	{
		return false;
	}

	float length = 1000.0f;
	float LeftX = 0.0f;
	if (m_aPadState[nUser].lX != 0)
	{
		LeftX = (float)m_aPadState[nUser].lX / length; //左はマイナス、右はプラス
	}
	return LeftX;
}

float CGamePad::LeftStickY(int nUser)
{
	if (GetGamePad(nUser) == false)
	{
		return false;
	}

	float length = 1000.0f;
	float LeftY = 0.0f;
	if (m_aPadState[nUser].lY != 0)
	{
		LeftY = (float)m_aPadState[nUser].lY / length; //上はマイナス、下はプラス
	}
	return LeftY;
}

float CGamePad::RightStickX(int nUser)
{
	if (GetGamePad(nUser) == false)
	{
		return false;
	}

	float length = 32767.0f;
	float RightX = 0.0f;
	if (m_aPadState[nUser].lZ != 32767)
	{
		RightX = (float)(m_aPadState[nUser].lZ - length) / length; //左はマイナス、右はプラス
	}
	return RightX;
}

float CGamePad::RightStickY(int nUser)
{
	if (GetGamePad(nUser) == false)
	{
		return false;
	}

	float length = 32767.0f;
	float RightY = 0.0f;
	if (m_aPadState[nUser].lRz != 32767)
	{
		RightY = (float)(m_aPadState[nUser].lRz - length) / length; //上はマイナス、下はプラス
	}
	return RightY;
}

bool CGamePad::GetGamePad(int nUser)
{
	return m_bConnect[nUser];
}