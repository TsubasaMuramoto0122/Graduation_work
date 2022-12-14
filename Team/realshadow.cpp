//=============================================================================
//
// リアルな影 [realshadow.h]
// Author : 三上航世
//
//=============================================================================
#include "realshadow.h"
#include "manager.h"
#include "renderer.h"

// コンストラクタ
CRealShadow::CRealShadow()
{
}


// デストラクタ
CRealShadow::~CRealShadow()
{
}


// 初期化メソッド
bool CRealShadow::Init()
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = CManager::GetRenderer()->GetDevice();     //デバイスを取得する

	// リソースにある深度バッファシャドウシェーダプログラムを読み込む
//#if _DEBUG
	if (FAILED(D3DXCreateEffectFromFile(pDevice, "data/FILES/DepthBufShadowEffect.fx", NULL, NULL, 0, NULL, &m_pEffect, NULL)))
	{
		return false;
	}
//#else
//	if (FAILED(D3DXCreateEffectFromResource(
//		cpDev.GetPtr(),
//		NULL,
//		MAKEINTRESOURCE(FXID_DEPTHBUFSHADOW),
//		NULL,
//		NULL,
//		0,
//		NULL,
//		m_cpEffect.ToCreator(),
//		NULL)))
//		return false;
//#endif

	m_hWorldMat = m_pEffect->GetParameterByName(NULL, "matWorld");
	m_hCameraViewMat = m_pEffect->GetParameterByName(NULL, "matCameraView");
	m_hCameraProjMat = m_pEffect->GetParameterByName(NULL, "matCameraProj");
	m_hLightViewMat = m_pEffect->GetParameterByName(NULL, "matLightView");
	m_hLightProjMat = m_pEffect->GetParameterByName(NULL, "matLightProj");
	m_hShadowMapTex = m_pEffect->GetParameterByName(NULL, "texShadowMap");
	m_hTechnique = m_pEffect->GetTechniqueByName("DepthBufShadowTec");

	if (m_hWorldMat == NULL || m_hCameraViewMat == NULL || m_hCameraProjMat == NULL
		|| m_hLightViewMat == NULL || m_hLightProjMat == NULL || m_hShadowMapTex == NULL || m_hTechnique == NULL)
	{
		return false;
	}
	return true;
}

CRealShadow *CRealShadow::Create()
{
	CRealShadow *pRealShadow;
	pRealShadow = new CRealShadow;
	if (pRealShadow != NULL)
	{
		pRealShadow->Init();
	}
	return pRealShadow;
}

// シャドウマップを設定
bool CRealShadow::SetShadowMap(IDirect3DTexture9 *pShadowMap)
{
	m_pShadowMapTex = pShadowMap;
	return true;
}


// 描画対象オブジェクトのワールド変換行列を設定
void CRealShadow::SetWorldMatrix(D3DXMATRIX pMat)
{
	m_matWorld = pMat;
}

// カメラのビュー行列を設定
void CRealShadow::SetCameraViewMatrix(D3DXMATRIX pMat)
{
	m_matCameraView = pMat;
}

// カメラの射影変換行列を設定
void CRealShadow::SetCameraProjMatrix(D3DXMATRIX pMat)
{
	m_matCameraProj = pMat;
}

// ライトのビュー行列を設定
void CRealShadow::SetLightViewMatrix(D3DXMATRIX pMat)
{
	m_matLightView = pMat;
}

// ライトの射影変換行列を設定
void CRealShadow::SetLightProjMatrix(D3DXMATRIX pMat)
{
	m_matLightProj = pMat;
}

// 描画の開始を宣言する
HRESULT CRealShadow::Begin()
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = CManager::GetRenderer()->GetDevice();     //デバイスを取得する

	// バックバッファ＆Ｚバッファのクリア
	pDevice->Clear(0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 160, 0), 1.0f, 0); //背景の色を変えれる

	// プログラマブルシェーダに切り替え
	m_pEffect->SetTechnique(m_hTechnique);

	// 開始宣言
	UINT Pass;
	m_pEffect->Begin(&Pass, 0);

	return S_OK;
}

// 描画の終了を宣言する
HRESULT CRealShadow::End()
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = CManager::GetRenderer()->GetDevice();     //デバイスを取得する

	m_pEffect->End();

	// 固定機能に戻す
	pDevice->SetVertexShader(NULL);
	pDevice->SetPixelShader(NULL);
	
	return S_OK;
}

// パスの開始を宣言する
HRESULT CRealShadow::BeginPass()
{
	m_pEffect->BeginPass(0);	// パスは1つのみ
	return S_OK;
}

// パスの終了を宣言する
HRESULT CRealShadow::EndPass()
{
	m_pEffect->EndPass();
	return S_OK;
}


// 登録されているパラメータ情報をエフェクトにセット
bool CRealShadow::SetParamToEffect()
{
	m_pEffect->SetMatrix(m_hWorldMat, &m_matWorld);
	m_pEffect->SetMatrix(m_hCameraViewMat, &m_matCameraView);
	m_pEffect->SetMatrix(m_hCameraProjMat, &m_matCameraProj);
	m_pEffect->SetMatrix(m_hLightViewMat, &m_matLightView);
	m_pEffect->SetMatrix(m_hLightProjMat, &m_matLightProj);

	m_pEffect->SetTexture(m_hShadowMapTex, m_pShadowMapTex);
	return true;
}