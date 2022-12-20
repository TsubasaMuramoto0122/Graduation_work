// ZTexCreator.h (2007. 2. 28)

// Z値テクスチャ生成クラス宣言部
//  生成者 ： IKD



#include "main.h"

///////////////////////////////////////////////
// CZTexCreatorクラス
//
//   Z値テクスチャを作成するヘルパークラス
//////////////////////////////
class CZTex
{
public:
	CZTex();
	~CZTex();

	// 初期化メソッド
	bool Init(UINT ZTexWidth, UINT ZTexHeight, D3DFORMAT ZTexFormat = D3DFMT_A8R8G8B8);

	// 描画対象オブジェクトのワールド変換行列を設定
	void SetWorldMatrix(D3DXMATRIX *pMat);

	// ビュー行列を設定
	void SetViewMatrix(D3DXMATRIX *pMat);

	// 射影変換行列を設定
	void SetProjMatrix(D3DXMATRIX *pMat);

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

	// Z値テクスチャを取得する
	IDirect3DTexture9 *GetZTex(){ return m_pZTex; }

	static CZTex *Create(UINT ZTexWidth, UINT ZTexHeight, D3DFORMAT ZTexFormat);

private:
	IDirect3DTexture9 *m_pZTex;		// Z値テクスチャ
	IDirect3DSurface9 *m_pZTexSurf;	// Z値テクスチャサーフェイス
	IDirect3DSurface9 *m_pDepthBuff;	// 深度バッファ
	IDirect3DSurface9 *m_pDevBuffer;	// デバイスバックバッファ
	IDirect3DSurface9 *m_pDevDepth;	// デバイス深度バッファ
	ID3DXEffect *m_pEffect;			// Z値プロットエフェクト
	D3DXMATRIX m_matWorld;						// ワールド変換行列
	D3DXMATRIX m_matView;						// ビュー変換行列
	D3DXMATRIX m_matProj;						// 射影変換行列
	D3DXHANDLE m_hWorldMat;						// ワールド変換行列ハンドル
	D3DXHANDLE m_hViewMat;						// ビュー変換行列ハンドル
	D3DXHANDLE m_hProjMat;						// 射影変換行列ハンドル
	D3DXHANDLE m_hTechnique;					// テクニックへのハンドル
};