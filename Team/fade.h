//=============================================================================
//
// フェード処理 [fade.h]
// Author : 三上航世
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_
#include "main.h"
#include "manager.h"

class CFade
{
public:
	typedef enum
	{
		FADE_NONE = 0,
		FADE_IN,
		FADE_OUT,
		FADE_MAX
	} FADE;

	CFade();
	~CFade();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static FADE GetFade(void) { return m_fade; }
	static void SetFade(CManager::MODE modenext);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;	//頂点バッファへのポインタ
	D3DXCOLOR m_FadeColor;						//フェードの色
	static CManager::MODE m_mode;				//モード(タイトル、ゲーム、リザルトetc...)
	static FADE m_fade;							//フェードのモード(明るくなるか、暗くなるか、何もしないか)

};
#endif