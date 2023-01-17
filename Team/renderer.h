//=============================================================================
//
// �����_�����O���� [renderer.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_
#include "main.h"

class CCamera;
class CFade;
class CTextUi;
class CRealShadow;
class CZTex;

class CRenderer
{
public:
	CRenderer();
	~CRenderer();

	HRESULT Init(HWND hWnd, bool bWindow);
	void Uninit();
	void Update();
	void Draw();
	LPDIRECT3DDEVICE9 GetDevice() { return m_pD3DDevice; }
	CCamera *GetCamera() { return m_pCamera; }
	CRealShadow *GetRealShadow() { return m_pRealShadow; }
	CZTex *GetZTex() { return m_pZTex; }

#ifdef _DEBUG
	void DrawFPS();
#endif

private:
	LPDIRECT3D9				m_pD3D = NULL;			// Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9		m_pD3DDevice = NULL;	// Device�I�u�W�F�N�g(�`��ɕK�v)
	LPD3DXFONT				m_pFont = NULL;			// �t�H���g�ւ̃|�C���^
	IDirect3DTexture9 *m_pTex;
	CRealShadow *m_pRealShadow;
	CZTex *m_pZTex;
	ID3DXSprite *m_pSprite;
	static CCamera *m_pCamera;
	static CFade *m_pFade;
	static CTextUi *m_pTextUi;
};

#endif