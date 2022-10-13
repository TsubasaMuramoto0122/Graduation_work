//=============================================================================
//
// �e�L�X�g���� [textui.h]
// Author : �O��q��
//
//=============================================================================
#ifdef _DEBUG
#include "textui.h"
#include "manager.h"
#include "renderer.h"
#include "scene2d.h"
#include "fade.h"

//�}�N����`
#define TEXTFILENAME "data/FILES/tutorial.txt"

//�ÓI�����o�ϐ�
//LPD3DXFONT CTextUi::m_pFont = NULL;

CTextUi::CTextUi()
{

}

CTextUi::~CTextUi(void)
{

}

HRESULT CTextUi::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	m_pFont = NULL;

	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);

	char aText[32][128];
	char aFile[128];
	int nLine = -1;

	//�`���[�g���A���t�@�C�����[�h
	FILE *pFile;
	int nCount;
	pFile = fopen(TEXTFILENAME, "r");
	if (pFile != NULL)
	{
		for (nCount = 0; nCount < 32; nCount++)
		{
			//�t�@�C���̕������1�s���ǂݍ���
			fscanf(pFile, "%s", &aFile[0]);
			if (strcmp(&aFile[0], "END_SCRIPT") == 0)
			{
				nLine = nCount;
				fclose(pFile);
				break;
			}
			else
			{
				memset(&aText[nCount][0], 0, sizeof(aText[nCount]));
				memcpy(&aText[nCount][0], &aFile[0], strlen(aFile));
			}
		}
		if (nLine == -1)
		{
			nLine = nCount;
			fclose(pFile);
		}
	}

	memset(&m_aText[0], 0, sizeof(m_aText));
	for (nCount = 0; nCount < nLine; nCount++)
	{
		memcpy(&m_aText[strlen(m_aText)], &aText[nCount][0], strlen(aText[nCount]));
		wsprintf(&m_aText[strlen(m_aText)], "\n");
	}

	return S_OK;
}

void CTextUi::Uninit(void)
{
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}
	delete this;
}

void CTextUi::Update(void)
{
	
}

void CTextUi::Draw(void)
{
	RECT rect = { 0, 18, SCREEN_WIDTH, SCREEN_HEIGHT };

	// �e�L�X�g�`��
	m_pFont->DrawText(NULL, &m_aText[0], -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}

CTextUi *CTextUi::Create(void)
{
	CTextUi *pTextUi;
	pTextUi = new CTextUi;
	if (pTextUi != NULL)
	{
		pTextUi->Init();
	}
	return pTextUi;
}
#endif