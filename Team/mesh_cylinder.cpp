//=============================================================================
// メッシュ(円柱)処理 [mesh_cylinder.cpp]
// Authore : 草刈 翔
//=============================================================================
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "mesh_cylinder.h"
#include "manager.h"
#include "renderer.h"
#include "scene3D.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CMeshCylinder::CMeshCylinder(PRIORITY  nPriority) :CScene3D(nPriority)
{
	// 変数のクリア
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_pIdxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nSide = 0;
	m_nVertical = 0;
	m_bOutSide = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CMeshCylinder::~CMeshCylinder()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMeshCylinder::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// 変数の初期化
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = pos;
	m_size = size;

	// 頂点バッファの生成
	//※(縦の分割数＋１)×(横の分割数＋１)の値の頂点を生成する
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * ((m_nVertical + 1) * (m_nSide + 1)),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// 頂点バッファへのポインタ
	VERTEX_3D *pVtx;

	// 頂点バッファをロックし、頂点データのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	int nCntVtx = 0;
	float fAngle = 0;

	for (int nCntVertical = 0; nCntVertical < m_nVertical + 1; nCntVertical++)
	{
		for (int nCntSide = 0; nCntSide < m_nSide + 1; nCntSide++, nCntVtx++)
		{
			// 頂点座標の設定
			pVtx[nCntVtx].pos = D3DXVECTOR3(-m_size.x * cosf(fAngle),
				m_size.y - (nCntVertical * (m_size.y / m_nVertical)),
				-m_size.z * sinf(fAngle));

			// 頂点が重複する場合、角度は加えない
			if (nCntSide != m_nSide)
			{
				if (m_bOutSide == false)
				{
					// シリンダーの内側に描画
					fAngle -= (D3DX_PI / (m_nSide / 2.0f));
				}
				else
				{
					// シリンダーの外側に描画
					fAngle += (D3DX_PI / (m_nSide / 2.0f));
				}
			}

			// 法線
			pVtx[nCntVtx].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

			// カラー
			pVtx[nCntVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ
			pVtx[nCntVtx].tex = D3DXVECTOR2(0.0f + (1.0f / m_nSide * nCntSide), 0.0f + (1.0f / m_nVertical * nCntVertical));
		}
	}

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	// インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * (((m_nSide + 1) * (m_nVertical + 1)) + ((m_nSide + 3) * (m_nVertical - 1))),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	// インデックス情報へのポインタ
	WORD *pIdx;

	// インデックスバッファをロックし、番号データへのポインタを取得
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	// 番号データの設定
	for (int nCntVertical = 0; nCntVertical < m_nVertical; nCntVertical++)
	{
		for (int nCntSide = 0; nCntSide < m_nSide + 1; nCntSide++)
		{
			// 横の列は2つずつ設定する
			pIdx[(m_nSide * 2 + 4) * nCntVertical + 0 + (nCntSide * 2)] = (WORD)(nCntSide + (m_nSide + 1) + (m_nSide + 1) * nCntVertical);
			pIdx[(m_nSide * 2 + 4) * nCntVertical + 1 + (nCntSide * 2)] = (WORD)(nCntSide + 0 + (m_nSide + 1) * nCntVertical);
		}
	}
	// ポリゴンを描画させない部分の番号データの設定
	for (int nCntVertical = 0; nCntVertical < m_nVertical - 1; nCntVertical++)
	{
		// pIdx[(基準の位置)＋(ずらす数)] = (横の分割数)/(横の分割数+2＋ずらす数)＋(横の分割数+1×現在の奥の分割数)
		pIdx[(m_nSide * 2 + 2) + 0 + nCntVertical * (m_nSide * 2 + 4)] = (WORD)(m_nSide + (m_nSide + 1) * nCntVertical);
		pIdx[(m_nSide * 2 + 2) + 1 + nCntVertical * (m_nSide * 2 + 4)] = (WORD)((m_nSide * 2 + 2) + (m_nSide + 1) * nCntVertical);
	}

	//インデックスバッファをアンロックする
	m_pIdxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CMeshCylinder::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// インデックスバッファの破棄
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

	if (m_pTexture != NULL)
	{
		m_pTexture = NULL;
	}

	// オブジェクトの破棄
	CScene3D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CMeshCylinder::Update(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void CMeshCylinder::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// ライティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdxBuff);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
		0,
		0,
		((m_nSide + 1) * (m_nVertical + 1)),					// 頂点の数
		0,														// 開始する頂点のインデックス
		(m_nSide * m_nVertical * 2) + (m_nVertical * 4) - 4);	// 描画するプリミティブ数

	//ライティングを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=============================================================================
// 生成処理
//=============================================================================
CMeshCylinder* CMeshCylinder::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nVertical, int nSide, bool bOutSide, int nTex)
{
	// インスタンスの生成
	CMeshCylinder *pMeshCylinder = NULL;

	// ヌルチェック
	if (pMeshCylinder == NULL)
	{
		// クラスの生成
		pMeshCylinder = new CMeshCylinder;
		if (pMeshCylinder != NULL)
		{
			// 変数の初期化
			pMeshCylinder->m_nVertical = nVertical;
			pMeshCylinder->m_nSide = nSide;
			pMeshCylinder->m_bOutSide = bOutSide;

			if (0 <= nTex)
			{
				pMeshCylinder->m_pTexture = *CScene3D::GetTexture(nTex);
			}

			// 初期化処理
			pMeshCylinder->Init(pos, size);
		}
	}

	return pMeshCylinder;
}