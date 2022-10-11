//=============================================================================
// 球体コリジョン処理 [collision_sphere.cpp]
// Author : Kusakari Kakeru
//=============================================================================
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "collision_sphere.h"
#include "manager.h"
#include "renderer.h"
#include "scene3D.h"
#include "model.h"
#include "sound.h"
#include "keyboard.h"

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
bool CCollisionSphere::m_bMngVisual = false;

//=============================================================================
// コンストラクタ
//=============================================================================
CCollisionSphere::CCollisionSphere(PRIORITY Priority) : CScene3D::CScene3D(Priority)
{
	// 変数のクリア
	m_pVtxBuff = NULL;
	m_pIdxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pParent = NULL;
	m_col = D3DCOLOR_RGBA(0, 0, 0, 153);
	m_collisionType = COLLISION_S_TYPE_MAX;
	m_nVertical = 0;
	m_nSide = 0;
	m_nNumPlayer = 0;
	m_fSize = 0.0f;
	m_fTime = 0.0f;
	m_fDamage = 0.0f;
	m_fObjectiveRot = 0.0f;
	m_bContact = false;
	m_bTouchAttack = false;
	m_bTouchExplosion = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CCollisionSphere::~CCollisionSphere()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CCollisionSphere::Init(D3DXVECTOR3 pos, float fSize)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// 変数の初期化
	m_pos = pos;
	m_fSize = fSize;
	m_nNumPlayer = -1;
	m_fObjectiveRot = 0.0f;
	m_bContact = false;
	m_bTouchAttack = false;
	m_bTouchExplosion = false;

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

	// 頂点座標の設定
	for (int nCntSide = m_nSide + 1; nCntSide > 0; nCntSide--)
	{
		for (int nCntVertical = 0; nCntVertical < m_nVertical + 1; nCntVertical++, nCntVtx++)
		{
			pVtx[nCntVtx].pos = D3DXVECTOR3(cosf((D3DX_PI * 2.0f / m_nVertical) * nCntVertical) * (sinf(((D3DX_PI * 2.0f / m_nVertical) * nCntSide) + ((D3DX_PI * 2.0f / m_nVertical) * m_nSide)) * (m_fSize / 2.0f)),
								  m_pos.y + cosf((D3DX_PI * 2.0f / m_nVertical) * nCntSide) * (m_fSize / 2.0f),
											sinf((D3DX_PI * 2.0f / m_nVertical) * nCntVertical) * (sinf(((D3DX_PI * 2.0f / m_nVertical) * nCntSide) + ((D3DX_PI * 2.0f / m_nVertical) * m_nSide)) * (m_fSize / 2.0f)));

			// 法線
			pVtx[nCntVtx].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

			// カラー
			pVtx[nCntVtx].col = m_col;

			// テクスチャ
			pVtx[nCntVtx].tex = D3DXVECTOR2(0.0f + -(1.0f / m_nVertical * nCntVertical), 0.0f + -(1.0f / m_nSide * nCntSide));
		}
	}

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	// インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * ((m_nSide - 1) * (m_nVertical + 3) + (m_nVertical + 1) * (m_nSide + 1)),
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
	for (int nCntSide = 0; nCntSide < m_nSide; nCntSide++)
	{
		for (int nCntVertical = 0; nCntVertical < m_nVertical + 1; nCntVertical++)
		{
			pIdx[(nCntVertical * 2) + 0 + (m_nVertical + 2) * 2 * nCntSide] = (WORD)((m_nVertical + 1) + nCntVertical + (m_nVertical + 1) * nCntSide);
			pIdx[(nCntVertical * 2) + 1 + (m_nVertical + 2) * 2 * nCntSide] = (WORD)(0 + nCntVertical + (m_nVertical + 1) * nCntSide);
		}
	}

	for (int nCntSide = 0; nCntSide < m_nSide - 1; nCntSide++)
	{
		pIdx[((m_nVertical + 1) * 2 + 0) * (nCntSide + 1) + (2 * nCntSide)] = (WORD)(m_nVertical + (m_nVertical + 1) * nCntSide);
		pIdx[((m_nVertical + 1) * 2 + 1) * (nCntSide + 1) + (1 * nCntSide)] = (WORD)(m_nVertical * 2 + 2 + (m_nVertical + 1) * nCntSide);
	}

	//インデックスバッファをアンロックする
	m_pIdxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CCollisionSphere::Uninit(void)
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
void CCollisionSphere::Update(void)
{
	if (this != NULL)
	{
		m_bContact = false;

		// 球同士の当たり判定
		Collision(this);

#ifdef _DEBUG
		// 判定の可視化処理
		VisualOn(m_bMngVisual);
#endif

		// 寿命を減らす
		if (m_fTime > -1.0f)
		{
			m_fTime -= 1.0f;

			// 時間経過で消す
			if (m_fTime <= 0.0f)
			{
				Uninit();
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CCollisionSphere::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// ライティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans, mtxScale, mtxParent;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスを取得
	pDevice->GetTransform(D3DTS_WORLD, &mtxParent);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdxBuff);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

#ifdef _DEBUG
	//テクスチャの設定
	pDevice->SetTexture(0, NULL);

	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
		0,
		0,
		((m_nVertical + 1) * (m_nSide + 1)),				//頂点の数
		0,													//開始する頂点のインデックス
		(m_nSide * m_nVertical * 2) + (m_nSide * 4) - 4);	//描画するプリミティブ数
#endif

	//ライティングを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=============================================================================
// 生成処理
//=============================================================================
CCollisionSphere* CCollisionSphere::Create(D3DXVECTOR3 pos, float fSize, int nVertical, int nSide,
	COLLISION_S_TYPE type, float fTime)
{
	// インスタンスの生成
	CCollisionSphere *pCollisionS = NULL;

	// ヌルチェック
	if (pCollisionS == NULL)
	{
		// クラスの生成
		pCollisionS = new CCollisionSphere;
		if (pCollisionS != NULL)
		{
			// 変数の初期化
			pCollisionS->m_nVertical = nVertical;
			pCollisionS->m_nSide = nSide;
			pCollisionS->m_fTime = fTime;
			pCollisionS->m_collisionType = type;

			// ワールドマトリックス設定前に衝突判定を行うため、先に指定位置をワールドマトリックスに設定しておく
			pCollisionS->m_mtxWorld._41 = pos.x;
			pCollisionS->m_mtxWorld._42 = pos.y;
			pCollisionS->m_mtxWorld._43 = pos.z;

			switch (type)
			{
				// プレイヤー：白
			case COLLISION_S_TYPE_PLAYER:
				pCollisionS->m_col = D3DCOLOR_RGBA(255, 255, 255, 0);
				break;
				// 攻撃：緑
			case COLLISION_S_TYPE_ATTACK:
				pCollisionS->m_col = D3DCOLOR_RGBA(0, 255, 0, 0);
				break;
				// 爆発：赤
			case COLLISION_S_TYPE_EXPLOSION:
				pCollisionS->m_col = D3DCOLOR_RGBA(255, 0, 0, 0);
				break;
				// 氷：水色
			case COLLISION_S_TYPE_ICE:
				pCollisionS->m_col = D3DCOLOR_RGBA(0, 210, 255, 0);
				break;
				// 毒：紫
			case COLLISION_S_TYPE_POISON:
				pCollisionS->m_col = D3DCOLOR_RGBA(200, 100, 225, 0);
				break;
				// 混乱：黄色
			case COLLISION_S_TYPE_PANIC:
				pCollisionS->m_col = D3DCOLOR_RGBA(255, 255, 0, 0);
				break;
			default:
				break;
			}

			// 初期化処理
			pCollisionS->Init(pos, fSize);
		}
	}

	return pCollisionS;
}

//=============================================================================
// 衝突処理
//=============================================================================
void CCollisionSphere::Collision(CScene *pScene)
{
	m_bContact = false;
	m_bTouchAttack = false;
	m_bTouchExplosion = false;

	//オブジェクト情報を入れるポインタ
	CScene *pObject = NULL;
	//オブジェクト情報を保存するポインタ変数
	CScene *pSaveObject = NULL;

	//先頭のポインタを代入
	pObject = pObject->GetTopObj(CScene::PRIORITY_EFFECT);

	while (pObject != NULL)
	{
		//現在のオブジェクトのポインタを保存
		pSaveObject = pObject;

		if (pObject->GetObjType() == CScene::OBJECTTYPE_NONE)
		{
			CCollisionSphere *pCollisionS = NULL;
			pCollisionS = (CCollisionSphere*)pObject;

			// 自分以外の球体コリジョンがあったら
			if (pObject != this)
			{
				D3DXVECTOR3 pos = D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43);	//自身の位置
				float fSize = pScene->GetRadius();												//自身の半径の大きさ
				D3DXVECTOR3 posColl = pCollisionS->GetMtxPos();									//対象のコリジョンの位置
				float fSizeColl = pCollisionS->GetRadius();										//対象のコリジョンのサイズ
				COLLISION_S_TYPE typeColl = pCollisionS->GetCollisionType();					//対象のコリジョンの種類
				int nNumPlayerColl = pCollisionS->GetNumPlayer();								//対象の番号

				// コリジョン同士の距離と半径を求める
				float fDistance = sqrtf((posColl.x - pos.x) * (posColl.x - pos.x) + (posColl.y - pos.y) * (posColl.y - pos.y) + (posColl.z - pos.z) * (posColl.z - pos.z));
				float fRadius = sqrtf((fSizeColl + fSize) * (fSizeColl + fSize));

				// 目的の向きを設定
				m_fObjectiveRot = (float)atan2((posColl.x - pos.x), (posColl.z - pos.z)) - D3DX_PI;

				// 距離が半径より小さくなったかつ、自身の攻撃じゃないなら
				if (fDistance < fRadius && m_nNumPlayer != nNumPlayerColl)
				{
					m_bContact = true;

					if (typeColl == COLLISION_S_TYPE_ATTACK)
					{
						m_bTouchAttack = true;
					}

					if (typeColl == COLLISION_S_TYPE_EXPLOSION)
					{
						m_bTouchExplosion = true;
					}
				}
			}
		}
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}
}

//=============================================================================
// 位置設定処理
//=============================================================================
void CCollisionSphere::SetPosCollision(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// コリジョンの種類の取得処理
//=============================================================================
CCollisionSphere::COLLISION_S_TYPE CCollisionSphere::GetCollisionType(void)
{
	return m_collisionType;
}

//=============================================================================
// 親モデル設定処理
//=============================================================================
void CCollisionSphere::SetParent(CModel *pModel)
{
	m_pParent = pModel;
}

//=============================================================================
// ワールドマトリックス座標取得処理
//=============================================================================
D3DXVECTOR3 CCollisionSphere::GetMtxPos(void)
{
	D3DXVECTOR3 pos = D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43);

	return pos;
}

//=============================================================================
// 半径取得処理
//=============================================================================
float CCollisionSphere::GetRadius(void)
{
	return m_fSize / 2;
}

//=============================================================================
// コリジョンの種類設定処理
//=============================================================================
void CCollisionSphere::SetCollisionType(COLLISION_S_TYPE type)
{
	m_collisionType = type;

	switch (type)
	{
		// プレイヤー：白
	case COLLISION_S_TYPE_PLAYER:
		m_col = D3DCOLOR_RGBA(255, 255, 255, 0);
		break;
		// 攻撃：緑
	case COLLISION_S_TYPE_ATTACK:
		m_col = D3DCOLOR_RGBA(0, 255, 0, 0);
		break;
		// 爆発：赤
	case COLLISION_S_TYPE_EXPLOSION:
		m_col = D3DCOLOR_RGBA(255, 0, 0, 0);
		break;
		// 氷：水色
	case COLLISION_S_TYPE_ICE:
		m_col = D3DCOLOR_RGBA(0, 210, 255, 0);
		break;
		// 毒：紫
	case COLLISION_S_TYPE_POISON:
		m_col = D3DCOLOR_RGBA(200, 100, 225, 0);
		break;
		// 混乱：黄色
	case COLLISION_S_TYPE_PANIC:
		m_col = D3DCOLOR_RGBA(255, 255, 0, 0);
		break;
	default:
		break;
	}
}

//=============================================================================
// 指定のオブジェクトに当たったかどうか
//=============================================================================
bool CCollisionSphere::GetTouchCollision(COLLISION_S_TYPE type)
{
	switch (type)
	{
	case COLLISION_S_TYPE_PLAYER:
		return false;
		break;
	case COLLISION_S_TYPE_ATTACK:
 		return m_bTouchAttack;
		break;
	case COLLISION_S_TYPE_EXPLOSION:
		return m_bTouchExplosion;
		break;
	case COLLISION_S_TYPE_ICE:
		return false;
		break;
	case COLLISION_S_TYPE_POISON:
		return false;
		break;
	case COLLISION_S_TYPE_PANIC:
		return false;
		break;
	default:
		return false;
		break;
	}
}

//=============================================================================
// 番号設定処理
//=============================================================================
void CCollisionSphere::SetNumPlayer(int nNum)
{
	m_nNumPlayer = nNum;
}

//=============================================================================
// 番号取得処理
//=============================================================================
int CCollisionSphere::GetNumPlayer(void)
{
	return m_nNumPlayer;
}

//=============================================================================
// 番号取得処理
//=============================================================================
float CCollisionSphere::GetObjectiveRot(void)
{
	return m_fObjectiveRot;
}

#ifdef _DEBUG
//=============================================================================
// 判定の可視化設定処理
//=============================================================================
void CCollisionSphere::SetVisual(bool bVisual)
{
	m_bMngVisual = bVisual;
}

//=============================================================================
// 判定の可視化処理
//=============================================================================
void CCollisionSphere::VisualOn(bool bVisual)
{
	D3DXCOLOR col = m_col;

	// 可視化OFF
	if (bVisual == false)
	{
		col = D3DXCOLOR(col.r, col.g, col.b, 0);
	}
	// 可視化ON
	else
	{
		col = D3DXCOLOR(col.r, col.g, col.b, 0.6f);
	}

	// 頂点バッファがNULLじゃなかったら
	//※これがないとモデル本体が消えた際、球体が残り続けてしまう
	if (m_pVtxBuff != NULL)
	{
		// 頂点バッファへのポインタ
		VERTEX_3D *pVtx;

		// 頂点バッファをロックし、頂点データのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		int nCntVtx = 0;

		for (int nCntSide = m_nSide + 1; nCntSide > 0; nCntSide--)
		{
			for (int nCntVertical = 0; nCntVertical < m_nVertical + 1; nCntVertical++, nCntVtx++)
			{
				// カラー
				pVtx[nCntVtx].col = col;
			}
		}

		// 頂点バッファをアンロックする
		m_pVtxBuff->Unlock();
	}
}
#endif