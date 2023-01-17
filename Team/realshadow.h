//=============================================================================
//
// リアルな影 [realshadow.h]
// Author : 三上航世
//
//=============================================================================
#include "main.h"

class CRealShadow
{
public:
	CRealShadow();
	~CRealShadow();

	//初期化
	bool Init();

	// シャドウマップを設定
	bool SetShadowMap(IDirect3DTexture9 *pShadowMap);

	// 描画対象オブジェクトのワールド変換行列を設定
	void SetWorldMatrix(D3DXMATRIX pMat);

	// カメラのビュー行列を設定
	void SetCameraViewMatrix(D3DXMATRIX pMat);

	// カメラの射影変換行列を設定
	void SetCameraProjMatrix(D3DXMATRIX pMat);

	// ライトのビュー行列を設定
	void SetLightViewMatrix(D3DXMATRIX pMat);

	// ライトの射影変換行列を設定
	void SetLightProjMatrix(D3DXMATRIX pMat);

	// 描画の開始を宣言する
	HRESULT Begin();

	// 描画の終了を宣言する
	HRESULT End();

	// パスの開始を宣言する
	HRESULT BeginPass();

	// パスの終了を宣言する
	HRESULT EndPass();

	// 登録されているパラメータ情報をエフェクトにセット
	bool SetParamToEffect();

	static CRealShadow *Create();					// 生成処理

private:
	IDirect3DTexture9 *m_pShadowMapTex;			// シャドウマップテクスチャ
	ID3DXEffect *m_pEffect;						// 深度バッファシャドウエフェクト
	D3DXMATRIX m_matWorld;						// ワールド変換行列
	D3DXMATRIX m_matCameraView;					// カメラのビュー変換行列
	D3DXMATRIX m_matCameraProj;					// カメラの射影変換行列
	D3DXMATRIX m_matLightView;					// ライトのビュー変換行列
	D3DXMATRIX m_matLightProj;					// ライトの射影変換行列
	D3DXHANDLE m_hWorldMat;						// ワールド変換行列ハンドル
	D3DXHANDLE m_hCameraViewMat;				// ビュー変換行列ハンドル
	D3DXHANDLE m_hCameraProjMat;				// 射影変換行列ハンドル
	D3DXHANDLE m_hLightViewMat;					// ビュー変換行列ハンドル
	D3DXHANDLE m_hLightProjMat;					// 射影変換行列ハンドル
	D3DXHANDLE m_hShadowMapTex;					// シャドウマップテクスチャハンドル
	D3DXHANDLE m_hTechnique;					// テクニックへのハンドル
};