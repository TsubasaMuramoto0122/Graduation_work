//=============================================================================
//
// �Q�[���p�b�h���͏��� [gamepad.h]
// Author : �O��q��
//
//=============================================================================
#include "gamepad.h"

CGamePad::CGamePad()
{
	m_pDevice = NULL;;

	for (int nCntPad = 0; nCntPad < XUSER_MAX_COUNT; nCntPad++)
	{
		// �ϐ��̃N���A
		ZeroMemory(&m_aState[nCntPad], sizeof(XINPUT_STATE));			// ���͏��(�v���X)
		ZeroMemory(&m_aStateTrigger, sizeof(XINPUT_STATE));				// ���͏��(�g���K�[)
		m_bConnect[nCntPad] = false;
	}
}

CGamePad::~CGamePad()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CGamePad::Init(HINSTANCE hInstance, HWND hWnd)
{
	// ��{�N���X�̏���������
	CInput::Init(hInstance, hWnd);

	// �ϐ��̏�����
	for (int nCntPad = 0; nCntPad < XUSER_MAX_COUNT; nCntPad++)
	{
		m_bConnect[nCntPad] = false;
	}

	XINPUT_STATE state[XUSER_MAX_COUNT];
	for (int nCntPad = 0; nCntPad < XUSER_MAX_COUNT; nCntPad++)
	{
		ZeroMemory(&state[nCntPad], sizeof(XINPUT_STATE));
	}

	// �R���g���[���[���ڑ�����Ă��邩�m�F����
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

//=============================================================================
// �I������
//=============================================================================
void CGamePad::Uninit(void)
{
	// ���͏����j���[�g�����ɂ���
	XInputEnable(false);

	// ��{�N���X�̏I������
	CInput::Uninit();
}

//=============================================================================
// �X�V����
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

	for (int nCntPad = 0; nCntPad < XUSER_MAX_COUNT; nCntPad++)
	{
		if (XInputGetState(nCntPad, &state[nCntPad]) == ERROR_SUCCESS)
		{
			// ���X�e�B�b�N�̃f�b�h�]�[���̐ݒ�
			if ((m_aState[nCntPad].Gamepad.sThumbLX <= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
				m_aState[nCntPad].Gamepad.sThumbLX >= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
				(m_aState[nCntPad].Gamepad.sThumbLY <= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
					m_aState[nCntPad].Gamepad.sThumbLY >= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
			{
				m_aState[nCntPad].Gamepad.sThumbLX = 0;
				m_aState[nCntPad].Gamepad.sThumbLY = 0;
			}

			// �E�X�e�B�b�N�̃f�b�h�]�[���̐ݒ�
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
// ���͏�Ԃ̎擾����(�v���X)
//=============================================================================
bool CGamePad::GetPress(int nInput, int nNum)
{
	// �ڑ����Ă��Ȃ��ꍇ��false��Ԃ��ď������I��������
	//�����ꂪ�Ȃ��Ə���ɓ��͂��ꑱ����
	if (m_bConnect[nNum] == false)
	{
		return false;
	}

	switch (nInput)
	{
	case PAD_INPUTTYPE_LSTICK_UP:	// ���X�e�B�b�N�F��
		return m_aState[nNum].Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ? true : false;
		break;
	case PAD_INPUTTYPE_LSTICK_DOWN:	// ���X�e�B�b�N�F��
		return m_aState[nNum].Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ? true : false;
		break;
	case PAD_INPUTTYPE_LSTICK_LEFT:	// ���X�e�B�b�N�F��
		return m_aState[nNum].Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ? true : false;
		break;
	case PAD_INPUTTYPE_LSTICK_RIGHT:// ���X�e�B�b�N�F�E
		return m_aState[nNum].Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ? true : false;
		break;
	case PAD_INPUTTYPE_RSTICK_UP:	// �E�X�e�B�b�N�F��
		return m_aState[nNum].Gamepad.sThumbRY > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ? true : false;
		break;
	case PAD_INPUTTYPE_RSTICK_DOWN:	// �E�X�e�B�b�N�F��
		return m_aState[nNum].Gamepad.sThumbRY < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ? true : false;
		break;
	case PAD_INPUTTYPE_RSTICK_LEFT:	// �E�X�e�B�b�N�F��
		return m_aState[nNum].Gamepad.sThumbRX < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ? true : false;
		break;
	case PAD_INPUTTYPE_RSTICK_RIGHT:// �E�X�e�B�b�N�F�E
		return m_aState[nNum].Gamepad.sThumbRX > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ? true : false;
		break;
	case PAD_INPUTTYPE_LEFT:		// �g���K�[�F��
		return m_aState[nNum].Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD ? true : false;
		break;
	case PAD_INPUTTYPE_RIGHT:		// �g���K�[�F�E
		return m_aState[nNum].Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD ? true : false;
		break;
	default:
		return false;
		break;
	}
}

//=============================================================================
// ���͏�Ԃ̎擾����(�g���K�[)
//=============================================================================
bool CGamePad::GetTrigger(int nInput, int nNum)
{
	if (m_bConnect[nNum] == false)
	{
		return false;
	}

	switch (nInput)
	{
	case PAD_INPUTTYPE_LSTICK_UP:	// ���X�e�B�b�N�F��
		return (((m_aStateTrigger[nNum].Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) == false) && (m_aState[nNum].Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;
	case PAD_INPUTTYPE_LSTICK_DOWN:	// ���X�e�B�b�N�F��
		return (((m_aStateTrigger[nNum].Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) == false) && (m_aState[nNum].Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;
	case PAD_INPUTTYPE_LSTICK_LEFT:	// ���X�e�B�b�N�F��
		return (((m_aStateTrigger[nNum].Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) == false) && (m_aState[nNum].Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;
	case PAD_INPUTTYPE_LSTICK_RIGHT:// ���X�e�B�b�N�F�E
		return (((m_aStateTrigger[nNum].Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) == false) && (m_aState[nNum].Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;
	case PAD_INPUTTYPE_RSTICK_UP:	// �E�X�e�B�b�N�F��
		return (((m_aStateTrigger[nNum].Gamepad.sThumbRY > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) == false) && (m_aState[nNum].Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;
	case PAD_INPUTTYPE_RSTICK_DOWN:	// �E�X�e�B�b�N�F��
		return (((m_aStateTrigger[nNum].Gamepad.sThumbRY < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) == false) && (m_aState[nNum].Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;
	case PAD_INPUTTYPE_RSTICK_LEFT:	// �E�X�e�B�b�N�F��
		return (((m_aStateTrigger[nNum].Gamepad.sThumbRX < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) == false) && (m_aState[nNum].Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;
	case PAD_INPUTTYPE_RSTICK_RIGHT:// �E�X�e�B�b�N�F�E
		return (((m_aStateTrigger[nNum].Gamepad.sThumbRX > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) == false) && (m_aState[nNum].Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;
	case PAD_INPUTTYPE_LEFT:	// �g���K�[�F��
		return (((m_aStateTrigger[nNum].Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) == false) && (m_aState[nNum].Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)) ? true : false;
		break;
	case PAD_INPUTTYPE_RIGHT:	// �g���K�[�F�E
		return (((m_aStateTrigger[nNum].Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) == false) && (m_aState[nNum].Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)) ? true : false;
		break;
	default:
		return false;
		break;
	}
}

//=============================================================================
// �{�^�����͏�Ԃ̎擾����(�v���X)
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
// �{�^�����͏�Ԃ̎擾����(�g���K�[)
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
// �o�C�u���[�V�����ݒ�
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
// �R���g���[���\���ڑ�����Ă��邩�ǂ����̎擾����
//=============================================================================
bool CGamePad::GetConnect(int nNum)
{
	return m_bConnect[nNum];
}