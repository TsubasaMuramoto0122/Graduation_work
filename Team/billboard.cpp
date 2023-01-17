//=============================================================================
// ビルボード処理 [Billboard.cpp]
// Author : 三上航世
//=============================================================================
#include "billboard.h"
#include "manager.h"
#include "renderer.h"
//=============================================================================
// マクロ
//=============================================================================


//=============================================================================
// コンストラクタ
//=============================================================================
CBillboard::CBillboard(PRIORITY nPriority) : CScene3D::CScene3D(nPriority)
{
	
}

//=============================================================================
// デストラクタ
//=============================================================================
CBillboard::~CBillboard()
{

}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CBillboard::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 Size, int nTex, D3DXCOLOR col, int nLife)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	m_pTexture = *GetTexture(nTex);
	m_move = move;

	// 変数の初期化
	SetPos(pos);

	m_nLife = nLife;

	// 頂点バッファの生成
	//※(縦の分割数＋１)×(横の分割数＋１)の値の頂点を生成する
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// 頂点バッファへのポインタ
	VERTEX_3D *pVtx;

	// 頂点バッファをロックし、頂点データのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-Size.x / 2.0f , Size.y / 2.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(Size.x / 2.0f, Size.y / 2.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-Size.x / 2.0f, -Size.y / 2.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(Size.x / 2.0f, -Size.y / 2.0f, 0.0f);
	// 法線
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	// カラーの設定
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;
	// テクスチャ
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CBillboard::Uninit()
{
	CScene3D::Uninit();
}

//=============================================================================
// 更新
//=============================================================================
void CBillboard::Update()
{
	if (CManager::GetPause() == false)
	{
		D3DXVECTOR3 pos = GetPos();
		pos += m_move;
		SetPos(pos);
		m_nLife--;

		if (pos.y <= -10.0f || m_nLife <= 0)
		{
			SetDeath(true);
		}
	}
}

//=============================================================================
// 描画
//=============================================================================
void CBillboard::Draw()
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	D3DXMATRIX mtxView;
	D3DXMATRIX mtxTrans, mtxWorld; //計算用マトリックス
	pDevice = CManager::GetRenderer()->GetDevice();     //デバイスを取得する


	//Zテスト関係
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	//アルファテスト関係
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//ラインティングを無視する
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//ビューマトリックスを取得
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//ポリゴンをカメラに対して正面に向ける
	D3DXMatrixInverse(&mtxWorld, NULL, &mtxView); //逆行列を求める

	mtxWorld._41 = 0.0f;
	mtxWorld._42 = 0.0f;
	mtxWorld._43 = 0.0f;

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	SetMatrix(mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->SetTexture(0, m_pTexture);    //テクスチャの設定

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,  //開始する始点のインデックス
		2); //描画するプリミティブ数

	//Zテスト関係
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//アルファテスト関係
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);

	//ラインティングを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//位置によっては映らないようにする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

}

//=============================================================================
// 描画
//=============================================================================
void CBillboard::ZTexDraw()
{

}

//=============================================================================
// 作成
//=============================================================================
CBillboard *CBillboard::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 Size, int nTex, D3DXCOLOR col, int nLife)
{
	CBillboard *pBillboard;
	pBillboard = new CBillboard(PRIORITY_EFFECT);
	if (pBillboard != NULL)
	{
		pBillboard->Init(pos, move, Size, nTex, col, nLife);
	}
	return pBillboard;
}