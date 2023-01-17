// ZTexCreator.cpp (2007. 2. 28)

// Z値テクスチャ生成クラス実装部

//

#include "ztex.h"
#include "manager.h"
#include "renderer.h"
#include "resource.h"

// コンストラクタ
CZTex::CZTex()
{
	
}

// デストラクタ
CZTex::~CZTex()
{
	
}


// 初期化メソッド
bool CZTex::Init(UINT ZTexWidth, UINT ZTexHeight, D3DFORMAT ZTexFormat)
{
	if (ZTexWidth == 0 || ZTexHeight == 0)
	{
		return false;
	}

	HRESULT hr;

	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = CManager::GetRenderer()->GetDevice();     //デバイスを取得する

	if (FAILED(D3DXCreateEffectFromFile(pDevice, "data/FILES/ZTexCreator.fx", NULL, NULL, 0, NULL, &m_pEffect, NULL)))
	{
		return false;
	}

	// エフェクト内の各種パラメータハンドルを取得
	m_hWorldMat = m_pEffect->GetParameterByName(NULL, "matWorld");
	m_hViewMat = m_pEffect->GetParameterByName(NULL, "matView");
	m_hProjMat = m_pEffect->GetParameterByName(NULL, "matProj");
	m_hTechnique = m_pEffect->GetTechniqueByName("ZValuePlotTec");
	if (m_hWorldMat == NULL || m_hViewMat == NULL || m_hProjMat == NULL || m_hTechnique == NULL)
	{
		return false;
	}
	// 指定のZ値テクスチャを生成
	hr = D3DXCreateTexture(pDevice, ZTexWidth, ZTexHeight, 1, D3DUSAGE_RENDERTARGET, ZTexFormat, D3DPOOL_DEFAULT, &m_pZTex);
	if (FAILED(hr))
	{
		return false;
	}

	m_pZTex->GetSurfaceLevel(0, &m_pZTexSurf);	// サーフェイス取得

	// 描画デバイスに定義されているバッファの能力を取得
	IDirect3DSurface9 *pSurf;
	pDevice->GetDepthStencilSurface(&pSurf);
	D3DSURFACE_DESC Desc;
	pSurf->GetDesc(&Desc);
	pSurf->Release();

	// 独自深度バッファを作成
	hr = pDevice->CreateDepthStencilSurface(ZTexWidth, ZTexHeight, Desc.Format, Desc.MultiSampleType, Desc.MultiSampleQuality, FALSE, &m_pDepthBuff, NULL);
	if (FAILED(hr))
	{
		return false;
	}
	return true;
}

CZTex *CZTex::Create(UINT ZTexWidth, UINT ZTexHeight, D3DFORMAT ZTexFormat)
{
	CZTex *pZTex;
	pZTex = new CZTex;
	if (pZTex != NULL)
	{
		pZTex->Init(ZTexWidth, ZTexHeight, ZTexFormat);
	}
	return pZTex;
}


// 描画対象オブジェクトのワールド変換行列を設定
void CZTex::SetWorldMatrix(D3DXMATRIX *pMat)
{
	m_matWorld = *pMat;
}


// ビュー行列を設定
void CZTex::SetViewMatrix(D3DXMATRIX *pMat)
{
	m_matView = *pMat;
}


// 射影変換行列を設定
void CZTex::SetProjMatrix(D3DXMATRIX *pMat)
{
	m_matProj = *pMat;
}


// 描画の開始を宣言する
HRESULT CZTex::Begin()
{
	// 初期化が正しく行われているかチェック
	if (m_pDepthBuff == NULL || m_pZTexSurf == NULL)
	{
		return E_FAIL;
	}

	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = CManager::GetRenderer()->GetDevice();     //デバイスを取得する

	// デバイスが持っているバッファを一時保存
	pDevice->GetRenderTarget(0, &m_pDevBuffer);
	pDevice->GetDepthStencilSurface(&m_pDevDepth);

	// デバイスにZ値テクスチャサーフェイスと深度バッファを設定
	pDevice->SetRenderTarget(0, m_pZTexSurf);
	pDevice->SetDepthStencilSurface(m_pDepthBuff);

	// バックバッファ＆Ｚバッファのクリア
	pDevice->Clear(0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 160, 0), 1.0f, 0); //背景の色を変えれる

	// プログラマブルシェーダのテクニックを設定
	m_pEffect->SetTechnique(m_hTechnique);

	// シェーダの開始を宣言
	UINT Tmp;
	m_pEffect->Begin(&Tmp, 0);

	return S_OK;
}

// パスの開始を宣言する
HRESULT CZTex::BeginPass()
{
	m_pEffect->BeginPass(0);	// Z値計算は1パス
	return S_OK;
}

// 登録されているパラメータ情報をエフェクトにセット
bool CZTex::SetParamToEffect()
{
	if (m_pEffect == NULL)
	{
		return false;
	}

	m_pEffect->SetMatrix(m_hWorldMat, &m_matWorld);
	m_pEffect->SetMatrix(m_hViewMat, &m_matView);
	m_pEffect->SetMatrix(m_hProjMat, &m_matProj);

	return true;
}

// パスの終了を宣言する
HRESULT CZTex::EndPass()
{
	m_pEffect->EndPass();
	return S_OK;
}

// 描画の終了を宣言する
HRESULT CZTex::End()
{
	m_pEffect->End();

	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = CManager::GetRenderer()->GetDevice();     //デバイスを取得する

	// デバイスに元のサーフェイスを戻す
	pDevice->SetRenderTarget(0, m_pDevBuffer);
	pDevice->SetDepthStencilSurface(m_pDevDepth);

	m_pDevBuffer = NULL;
	m_pDevDepth = NULL;

	// 固定機能に戻す
	pDevice->SetVertexShader(NULL);
	pDevice->SetPixelShader(NULL);

	return S_OK;
}