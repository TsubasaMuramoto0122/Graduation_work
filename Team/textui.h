//=============================================================================
//
// UI処理 [tutorialui.h]
// Author : 三上航世
//
//=============================================================================
#ifndef _TUTORIALUI_H_
#define _TUTORIALUI_H_
#ifdef _DEBUG
#include "main.h"
#include "scene.h"

//マクロ定義
#define MAX_BYTE (1024)

class CScene2D;

class CTextUi
{
public:
	CTextUi();
	~CTextUi();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTextUi *Create(void);

private:
	char m_aText[MAX_BYTE];

	LPD3DXFONT m_pFont;
};

#endif
#endif