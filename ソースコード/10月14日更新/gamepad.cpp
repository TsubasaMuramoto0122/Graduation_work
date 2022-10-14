//=============================================================================
//
// �Q�[���p�b�h���͏��� [gamepad.h]
// Author : �O��q��
//
//=============================================================================
#include "gamepad.h"

BOOL CALLBACK DeviceFindCallBack(LPCDIDEVICEINSTANCE ipddi, LPVOID pvRef);

CGamePad::CGamePad()
{
	m_pDevice = NULL;;

	for (int nCntPad = 0; nCntPad < XUSER_MAX_COUNT; nCntPad++)
	{
		// �ϐ��̃N���A
		ZeroMemory(&m_aPadState[nCntPad], sizeof(XINPUT_STATE));			// ���͏��(�v���X)
		ZeroMemory(&m_aPadStateTrigger, sizeof(XINPUT_STATE));				// ���͏��(�g���K�[)
		ZeroMemory(&m_aPadStateRelease[nCntPad], sizeof(XINPUT_VIBRATION));	// ���͏��(�����[�X)
		m_bConnect[nCntPad] = false;
	}
}

CGamePad::~CGamePad()
{

}

HRESULT CGamePad::Init(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInit�I�u�W�F�N�g�̐���
	CInput::Init(hInstance, hWnd);

	// �ϐ��̏�����
	for (int nCntPad = 0; nCntPad < XUSER_MAX_COUNT; nCntPad++)
	{
		m_bConnect[nCntPad] = false;
	}

	//�ڑ�����Ă�Q�[���p�b�h�̗�
	if (FAILED(m_pInput->EnumDevices(DI8DEVCLASS_GAMECTRL, DeviceFindCallBack, NULL, DIEDFL_ATTACHEDONLY)))
	{
		return E_FAIL;
	}
	//���̓f�o�C�X�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_Joystick, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIJoystick)))
	{
		return E_FAIL;
	}
	// �����[�h���Βl���[�h�Ƃ��Đݒ�
	DIPROPDWORD diprop;
	ZeroMemory(&diprop, sizeof(diprop));
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.diph.dwObj = 0;
	diprop.dwData = DIPROPAXISMODE_ABS;

	// �����[�h��ύX
	if (FAILED(m_pDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		return E_FAIL;
	}

	// X���̒l�͈̔͐ݒ�
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

	// Y���̒l�͈̔͐ݒ�
	diprg.diph.dwObj = DIJOFS_Y;
	if (FAILED(m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	// �Q�[���p�b�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	m_pDevice->Acquire();
	//�����𓯊�������
	m_pDevice->Poll();

	// �R���g���[���[���ڑ�����Ă��邩�m�F����
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
			// �R���g���[���[�͐ڑ����Ă�����
			m_bConnect[nCntPad] = true;
		}
		else
		{
			// �R���g���[���[�͐ڑ�����Ă��Ȃ����
			m_bConnect[nCntPad] = false;
		}
	}

	return S_OK;
}

void CGamePad::Uninit()
{
	// ���͏����j���[�g�����ɂ���
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

		// �R���g���[���[���ڑ�����Ă��邩�m�F����
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
	// �ő�l���Ԃ��
	for (int nCntXUser = 0; nCntXUser < XUSER_MAX_COUNT; nCntXUser++)
	{
		//���̓f�o�C�X����f�[�^���擾����
		if (m_bConnect[nCntXUser] == true && m_pDevice->GetDeviceState(sizeof(aPadState), &aPadState) == ERROR_SUCCESS)
		{
			for (nCntPad = 0; nCntPad < DIP_MAX; nCntPad++)
			{
				m_aPadStateTrigger[nCntXUser].rgbButtons[nCntPad] = m_aPadState[nCntXUser].rgbButtons[nCntPad] ^ aPadState.rgbButtons[nCntPad] & aPadState.rgbButtons[nCntPad];
				m_aPadStateRelease[nCntXUser].rgbButtons[nCntPad] = (m_aPadState[nCntXUser].rgbButtons[nCntPad] ^ aPadState.rgbButtons[nCntPad]) & m_aPadState[nCntXUser].rgbButtons[nCntPad];
				m_aPadState[nCntXUser].rgbButtons[nCntPad] = aPadState.rgbButtons[nCntPad]; //�p�b�h�̓��͏��ۑ�
			}
			m_aPadState[nCntXUser].lX = aPadState.lX;
			m_aPadState[nCntXUser].lY = aPadState.lY;
			m_aPadState[nCntXUser].lZ = aPadState.lZ;
			m_aPadState[nCntXUser].lRz = aPadState.lRz;
			m_aPadStateTrigger[nCntXUser].rgdwPOV[nCntXUser] = m_aPadState[nCntXUser].rgdwPOV[nCntXUser];
			m_aPadState[nCntXUser].rgdwPOV[nCntXUser] = aPadState.rgdwPOV[nCntXUser];
		}
		// �ڑ�����Ă���R���g���[���[�̂ݎ擾����
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
	// �ڑ����Ă��Ȃ��R���g���[���\��false��Ԃ��ď������I��������
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

	//�\���L�[�����͂���Ă邩
	if (m_aPadState[nUser].rgdwPOV[0] != 0xFFFFFFFF)
	{
		//���O�ɉ����ꂽ�����ƈႤ���i�����������疳������j
		if (m_aPadStateTrigger[nUser].rgdwPOV[nUser] != m_aPadState[nUser].rgdwPOV[nUser])
		{
			return (float)m_aPadState[nUser].rgdwPOV[nUser];
		}
	}
	return 10.0f; //����������ĂȂ������Ƃ��p
}

float CGamePad::PressCrossKey(int nUser)
{
	if (GetGamePad(nUser) == false)
	{
		return false;
	}

	//�\���L�[�����͂���Ă邩
	if (m_aPadState[nUser].rgdwPOV[nUser] != 0xFFFFFFFF)
	{
		return (float)m_aPadState[nUser].rgdwPOV[nUser];
	}
	return 10.0f; //����������ĂȂ������Ƃ��p
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
		LeftX = (float)m_aPadState[nUser].lX / length; //���̓}�C�i�X�A�E�̓v���X
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
		LeftY = (float)m_aPadState[nUser].lY / length; //��̓}�C�i�X�A���̓v���X
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
		RightX = (float)(m_aPadState[nUser].lZ - length) / length; //���̓}�C�i�X�A�E�̓v���X
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
		RightY = (float)(m_aPadState[nUser].lRz - length) / length; //��̓}�C�i�X�A���̓v���X
	}
	return RightY;
}

bool CGamePad::GetGamePad(int nUser)
{
	return m_bConnect[nUser];
}