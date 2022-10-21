//=============================================================================
// メッシュ(ウォール)処理 [mesh_wall.cpp]
// Author : Kusakari Kakeru
//=============================================================================
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "mesh_wall.h"
#include "manager.h"
#include "renderer.h"
#include "scene3D.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CMeshWall::CMeshWall(PRIORITY nPriority) :CScene3D(nPriority)
{
	// 変数のクリア
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_pIdxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nRow = 0;
	m_nLine = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CMeshWall::~CMeshWall()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMeshWall::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// 変数の初期化
	m_pos = pos;
	m_size = size;

	// 位置の設定
	SetPos(m_pos);

	// 頂点バッファの生成
	//※(縦の分割数＋１)×(横の分割数＋１)の値の頂点を生成する
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * (m_nLine + 1) * (m_nRow + 1),
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

	// 頂点座標の設定
	for (int nCntVertical = 0; nCntVertical < m_nLine + 1; nCntVertical++)
	{
		for (int nCntRow = 0; nCntRow < m_nRow + 1; nCntRow++, nCntVtx++)
		{
			pVtx[nCntVtx].pos = D3DXVECTOR3((-m_size.x / 2.0f) + (nCntRow * (m_size.x / m_nRow)),
				(m_size.y / 2.0f) + (m_size.y / 2.0f) - (nCntVertical * (m_size.y / m_nLine)),
				m_size.z);

			// 法線
			pVtx[nCntVtx].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

			// カラーの設定
			pVtx[nCntVtx].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// テクスチャ
			pVtx[nCntVtx].tex = D3DXVECTOR2(0.0f + (nCntRow * 1.0f), 0.0f + (nCntVertical * 1.0f));
		}
	}

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	// インデックスバッファの生成
	//※(頂点の合計)+(重複して置かれた頂点)の値を生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * (((m_nRow + 1) * (m_nLine + 1)) + ((m_nRow + 3) * (m_nLine - 1))),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	// インデックス情報へのポインタ
	WORD *pIdx;

	// インデックスバッファをロックし、番号データへのポインタを取得
	m_pIdxBuff->Lock(0, 0, (void **)&pIdx, 0);

	// 番号データの設定
	for (int nCntVertical = 0; nCntVertical < m_nLine; nCntVertical++)
	{
		for (int nCntRow = 0; nCntRow < m_nRow + 1; nCntRow++)
		{
			// 横の列は2つずつ設定する
			// pIdx[(基準の位置)×(現在の奥の分割数)＋(ずらす数)] = (ずらす数)＋(基準の位置)＋(横の分割数+1×現在の縦の分割数)
			pIdx[(m_nRow * 2 + 4) * nCntVertical + 0 + (nCntRow * 2)] = (WORD)(nCntRow + (m_nRow + 1) + (m_nRow + 1) * nCntVertical);
			pIdx[(m_nRow * 2 + 4) * nCntVertical + 1 + (nCntRow * 2)] = (WORD)(nCntRow + 0 + (m_nRow + 1) * nCntVertical);
		}
	}
	// ポリゴンを描画させない部分の番号データの設定
	for (int nCntVertical = 0; nCntVertical < m_nLine - 1; nCntVertical++)
	{
		// pIdx[(基準の位置)＋(ずらす数)] = (横の分割数)/(横の分割数+2＋ずらす数)＋(横の分割数+1×現在の縦の分割数)
		pIdx[(m_nRow * 2 + 2) + 0 + nCntVertical * (m_nRow * 2 + 4)] = (WORD)(m_nRow + (m_nRow + 1) * nCntVertical);
		pIdx[(m_nRow * 2 + 2) + 1 + nCntVertical * (m_nRow * 2 + 4)] = (WORD)((m_nRow * 2 + 2) + (m_nRow + 1) * nCntVertical);
	}

	// インデックスバッファをアンロックする
	m_pIdxBuff->Unlock();

	return S_OK;
}

//================================================
// 終了処理
//================================================
void CMeshWall::Uninit(void)
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

	// オブジェクトの破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CMeshWall::Update(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void CMeshWall::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//アルファテストを有効に
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//アルファテスト
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	//アルファ値の参照値
	pDevice->SetRenderState(D3DRS_ALPHAREF, 100);

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

	// カリングを行う
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdxBuff);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	if (m_pTexture != NULL)
	{
		// テクスチャの設定
		pDevice->SetTexture(0, m_pTexture);
	}
	else
	{
		pDevice->SetTexture(0, NULL);
	}

	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,	// プリミティブの種類
		0,
		0,
		((m_nRow + 1) * (m_nLine + 1)),					// 頂点の数
		0,												// 開始する頂点のインデックス
		(m_nRow * m_nLine * 2) + (m_nLine * 4) - 4);	// 描画するプリミティブ数

														//アルファテストを無効に
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	//アルファテスト
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	//アルファ値の参照値
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
}

//=============================================================================
// 生成処理
//=============================================================================
CMeshWall* CMeshWall::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, int nRow, int nLine, int nTex)
{
	// インスタンスの生成
	CMeshWall *pMeshWall = NULL;

	// ヌルチェック
	if (pMeshWall == NULL)
	{
		// クラスの生成
		pMeshWall = new CMeshWall;
		if (pMeshWall != NULL)
		{
			// 変数の初期化
			pMeshWall->m_rot = rot;
			pMeshWall->m_nRow = nRow;
			pMeshWall->m_nLine = nLine;

			pMeshWall->m_pTexture = *CScene3D::GetTexture(nTex);

			// 初期化処理
			pMeshWall->Init(pos, size);
		}
	}

	return pMeshWall;
}

//=============================================================================
// カラー設定処理
//=============================================================================
void CMeshWall::SetColor(D3DXCOLOR col)
{
	// 頂点バッファへのポインタ
	VERTEX_3D *pVtx;

	// 頂点バッファをロックし、頂点データのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	int nCntVtx = 0;

	// 頂点座標の設定
	for (int nCntVertical = 0; nCntVertical < m_nLine + 1; nCntVertical++)
	{
		for (int nCntRow = 0; nCntRow < m_nRow + 1; nCntRow++, nCntVtx++)
		{
			// カラーの設定
			pVtx[nCntVtx].col = col;
		}
	}

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
// テクスチャ設定処理
//=============================================================================
//void CMeshWall::BindTexture(const char *aTextureName)
//{
//	// 頂点情報を設定
//	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//デバイスの取得
//
//	D3DXCreateTextureFromFile(pDevice, aTextureName, &m_pTexture);
//}

//================================================
// 当たり判定処理
//================================================
D3DXVECTOR3 CMeshWall::Collision(CScene *pScene)
{
	D3DXVECTOR3 Vec = D3DXVECTOR3(99.0f, 99.0f, 99.0f);

	//オブジェクト情報を入れるポインタ
	CScene *pObject = NULL;
	//オブジェクト情報を保存するポインタ変数
	CScene *pSaveObject = NULL;

	//先頭のポインタを代入
	pObject = pObject->GetTopObj(CScene::PRIORITY_OBJECT);

	while (pObject != NULL)
	{
		//現在のオブジェクトのポインタを保存
		pSaveObject = pObject;

		if (pObject->GetObjType() == CScene::OBJECTTYPE_WALL)
		{
			// メッシュウォールにキャスト
			CMeshWall *pMeshWall = NULL;
			pMeshWall = (CMeshWall*)pObject;

			D3DXVECTOR3 posWall = pMeshWall->GetPos();		//壁の位置
			D3DXVECTOR3 sizeWall = pMeshWall->GetSize();	//壁のサイズ
			D3DXVECTOR3 rotWall = pMeshWall->m_rot;			//壁の向き
			D3DXVECTOR3 pos = pScene->GetPos();				//対象の位置
			float fSize = pScene->GetRadius();				//対象の半径のサイズ
			D3DXVECTOR3 posOld = pScene->GetPosOld();		//対象の1フレーム前の位置

			////※回転した壁の当たり判定の処理ができていないため、特定の向きの時に当たり判定をさせている(旧やり方)
			//if (rotWall.y <= 1.58f && rotWall.y >= 1.56f)
			//{
			//	//壁に右から当たった時
			//	if (pos.y + fSize	> posWall.y &&
			//		posOld.y		< posWall.y + sizeWall.y &&
			//		pos.z + fSize	> posWall.z - sizeWall.x / 2.0f &&
			//		pos.z - fSize	< posWall.z + sizeWall.x / 2.0f &&
			//		pos.x >= posWall.x - fSize &&
			//		posOld.x <= posWall.x - fSize)
			//	{
			//		//位置を設定
			//		pos.x = posWall.x - fSize;
			//		pScene->SetPos(pos);
			//		bContact = true;
			//	}
			//}

			//if (rotWall.y >= -1.58f && rotWall.y <= -1.56f)
			//{
			//	//壁に左から当たった時
			//	if (pos.y + fSize	> posWall.y &&
			//		posOld.y		< posWall.y + sizeWall.y &&
			//		pos.z + fSize	> posWall.z - sizeWall.x / 2.0f &&
			//		pos.z - fSize	< posWall.z + sizeWall.x / 2.0f &&
			//		pos.x <= posWall.x + fSize &&
			//		posOld.x >= posWall.x + fSize)
			//	{
			//		//位置を設定
			//		pos.x = posWall.x + fSize;
			//		pScene->SetPos(pos);
			//		bContact = true;
			//	}
			//}

			//if ((rotWall.y <= 0.1f && rotWall.y >= -0.1f) ||
			//	(rotWall.y >= -3.15f && rotWall.y <= -3.13f))
			//{
			//	//壁に手前から当たった時
			//	if (pos.y + fSize	> posWall.y &&
			//		posOld.y		< posWall.y + sizeWall.y &&
			//		pos.x + fSize	> posWall.x - sizeWall.x / 2.0f &&
			//		pos.x - fSize	< posWall.x + sizeWall.x / 2.0f &&
			//		pos.z >= posWall.z - fSize &&
			//		posOld.z <= posWall.z - fSize)
			//	{
			//		//位置を設定
			//		pos.z = posWall.z - fSize;
			//		pScene->SetPos(pos);
			//		bContact = true;
			//	}
			//}

			//if (rotWall.y <= 3.15f && rotWall.y >= 3.13f)
			//{
			//	//壁に奥から当たった時
			//	if (pos.y + fSize	> posWall.y &&
			//		posOld.y		< posWall.y + sizeWall.y &&
			//		pos.x + fSize	> posWall.x - sizeWall.x / 2.0f &&
			//		pos.x - fSize	< posWall.x + sizeWall.x / 2.0f &&
			//		pos.z <= posWall.z + fSize &&
			//		posOld.z >= posWall.z + fSize)
			//	{
			//		//位置を設定
			//		pos.z = posWall.z + fSize;
			//		pScene->SetPos(pos);
			//		bContact = true;
			//	}
			//}

			//新しいやり方。平面方程式を使ったやり方。どの角度でも使える(多分)
			//壁の4頂点
			D3DXVECTOR3 aPoint[4];
			aPoint[0] = D3DXVECTOR3(posWall.x - (sizeWall.x * 0.5f) * cosf(rotWall.y), posWall.y + sizeWall.y	, posWall.z - (sizeWall.x * 0.5f) * sinf(-rotWall.y));
			aPoint[1] = D3DXVECTOR3(posWall.x + (sizeWall.x * 0.5f) * cosf(rotWall.y), posWall.y + sizeWall.y	, posWall.z + (sizeWall.x * 0.5f) * sinf(-rotWall.y));
			aPoint[2] = D3DXVECTOR3(posWall.x - (sizeWall.x * 0.5f) * cosf(rotWall.y), posWall.y				, posWall.z - (sizeWall.x * 0.5f) * sinf(-rotWall.y));
			aPoint[3] = D3DXVECTOR3(posWall.x + (sizeWall.x * 0.5f) * cosf(rotWall.y), posWall.y				, posWall.z + (sizeWall.x * 0.5f) * sinf(-rotWall.y));

			D3DXVECTOR3 Cross[3];
			D3DXVec3Cross(&Cross[0], &(aPoint[2] - aPoint[1]), &(aPoint[1] - aPoint[0]));									//壁の外積ベクトル
			float fLength = powf((Cross[0].x * Cross[0].x) + (Cross[0].y * Cross[0].y) + (Cross[0].z * Cross[0].z), 0.5f);	//長さ
			Cross[0].x /= fLength;
			Cross[0].y /= fLength;
			Cross[0].z /= fLength; //ここまで法線ベクトル

			Cross[1] = pos - aPoint[0];		//プレイヤーのposと壁の任意の点のベクトル
			Cross[2] = posOld - aPoint[0];	//プレイヤーのOldposと壁の任意の点のベクトル

			float fDistance = Cross[0].x * Cross[1].x + Cross[0].y * Cross[1].y + Cross[0].z * Cross[1].z;		//壁面との距離 マイナスの時、表側にいる
			float fOldDistance = Cross[0].x * Cross[2].x + Cross[0].y * Cross[2].y + Cross[0].z * Cross[2].z;	//壁面との距離　マイナスの時、表側にいる
			D3DXVECTOR3 Point = D3DXVECTOR3(pos.x - (Cross[0].x * fDistance), pos.y - (Cross[0].y * fDistance), pos.z - (Cross[0].z * fDistance));						//壁面上のプレイヤーの位置
			D3DXVECTOR3 OldPoint = D3DXVECTOR3(posOld.x - (Cross[0].x * fOldDistance), posOld.y - (Cross[0].y * fOldDistance), posOld.z - (Cross[0].z * fOldDistance));	//壁面上の1フレーム前のプレイヤーの位置

			if (aPoint[2].y < Point.y + fSize && Point.y < aPoint[0].y || aPoint[2].y < OldPoint.y + fSize && OldPoint.y < aPoint[0].y)
			{
				if ((aPoint[0].x < Point.x + fSize && Point.x - fSize < aPoint[1].x || aPoint[1].x < Point.x + fSize && Point.x - fSize < aPoint[0].x) ||
					(aPoint[0].x < OldPoint.x + fSize && OldPoint.x - fSize < aPoint[1].x || aPoint[1].x < OldPoint.x + fSize && OldPoint.x - fSize < aPoint[0].x))
				{
					if ((aPoint[0].z < Point.z + fSize && Point.z - fSize < aPoint[1].z || aPoint[1].z < Point.z + fSize && Point.z - fSize < aPoint[0].z) ||
						(aPoint[0].z < OldPoint.z + fSize && OldPoint.z - fSize < aPoint[1].z || aPoint[1].z < OldPoint.z + fSize && OldPoint.z - fSize < aPoint[0].z))
					{
						if (fabsf(fDistance) <= fSize || fOldDistance <= -fSize && fDistance >= -fSize)
						{
							pos.x -= sinf(rotWall.y) * (fSize - fabsf(fDistance));
							pos.z -= cosf(rotWall.y) * (fSize - fabsf(fDistance));
							pScene->SetPos(pos);
							Vec = Cross[0];
						}
					}
				}
			}
		}
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}

	return Vec;
}