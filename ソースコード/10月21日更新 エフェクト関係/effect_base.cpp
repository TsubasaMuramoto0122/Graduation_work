//---------------------------
// エフェクトのベース処理 [Effect_base.cpp]
// Author : 佐藤秀亮
//---------------------------
#include "Effect_base.h"
#include "manager.h"
#include "renderer.h"

//マクロ定義
#define TEXTURE_FILENAME_3D "data/FILES/EffectTexNameRead.txt"

//静的メンバ変数
LPDIRECT3DTEXTURE9 CEffect_base::m_pTexture[MAX_TEXTURE_3D] = {};
int CEffect_base::m_nMaxTex = 0;

CEffect_base::CEffect_base(PRIORITY nPriority) : CScene3D::CScene3D(nPriority)
{

}

CEffect_base::~CEffect_base()
{

}

//初期化処理
HRESULT CEffect_base::Init(D3DXVECTOR3 size, D3DXVECTOR3 pos, D3DXVECTOR2 Tex)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = CManager::GetRenderer()->GetDevice();     //デバイスを取得する

	SetPos(pos);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);


	m_TexNum = Tex;

	m_size = size;

	VERTEX_3D *pVtx; //頂点情報へのポインタ
					 //頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);
	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-size.x, size.y, size.z);
	pVtx[1].pos = D3DXVECTOR3(size.x, size.y, size.z);
	pVtx[2].pos = D3DXVECTOR3(-size.x, -size.y, -size.z);
	pVtx[3].pos = D3DXVECTOR3(size.x, -size.y, -size.z);

	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラー
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(Tex.x, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, Tex.y);
	pVtx[3].tex = D3DXVECTOR2(Tex.x, Tex.y);
	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
	return S_OK;
}

//終了処理
void CEffect_base::Uninit()
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	CScene3D::Uninit();
}

//更新処理
void CEffect_base::Update()
{

}

//描画処理
void CEffect_base::Draw()
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	D3DXMATRIX mtxRot, mtxTrans, mtxWorld; //計算用マトリックス
	pDevice = CManager::GetRenderer()->GetDevice();     //デバイスを取得する
														//ラインティングを無視する
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//透明な部分を描画しないようにする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);
	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, GetRot().y, GetRot().x, GetRot().z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

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
	if (m_nTexType != -1)
	{
		pDevice->SetTexture(0, m_pTexture[m_nTexType]);    //テクスチャの設定
	}
	else
	{
		pDevice->SetTexture(0, NULL);    //テクスチャの設定
	}
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,  //開始する始点のインデックス
		2); //描画するプリミティブ数
			//ラインティングを有効にする

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	//デフォルトに戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
}
//=============================================================================
// テクスチャ破棄
//=============================================================================
void CEffect_base::UninitTexture()
{
	//テクスチャ破棄
	for (int nCnt = 0; nCnt < m_nMaxTex; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}

//=============================================================================
//たぶんいらない
////作成
//CEffect_base *CEffect_base::Create(D3DXVECTOR3 size, D3DXVECTOR3 pos, D3DXVECTOR2 Tex)
//{
//	CEffect_base *pPlane;
//	pPlane = new CEffect_base(CManager::PRIORITY_SET);
//	if (pPlane != NULL)
//	{
//		pPlane->Init(size, pos, Tex);
//	}
//	return pPlane;
//}
//=============================================================================

//=============================================================================
// サイズセット
//=============================================================================
void CEffect_base::SetSize(D3DXVECTOR3 size)
{
	//m_size = size;
	VERTEX_3D *pVtx; //頂点情報へのポインタ
					 //頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);
	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-size.x, size.y, size.z);
	pVtx[1].pos = D3DXVECTOR3(size.x, size.y, size.z);
	pVtx[2].pos = D3DXVECTOR3(-size.x, -size.y, -size.z);
	pVtx[3].pos = D3DXVECTOR3(size.x, -size.y, -size.z);
	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
// 色セット
//=============================================================================
void CEffect_base::ChangeColor(D3DXCOLOR col)
{
	VERTEX_3D *pVtx; //頂点情報へのポインタ
					 //頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);
	//頂点座標の設定
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;
	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
// テクスチャ生成
//=============================================================================
void CEffect_base::CreateTextureEffect()
{
	// 頂点情報を設定
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//デバイスの取得

	//ファイル読み込み
	char aFile[256];
	FILE *pFile = fopen(TEXTURE_FILENAME_3D, "r");

	int nCntTex = 0;

	if (pFile != NULL)
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]);

			if (strcmp(&aFile[0], "NUM_TEXTURE") == 0)	//NUM_TEXTUREの文字列
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &m_nMaxTex);//使用するテクスチャ数を読み込む
			}

			if (strcmp(&aFile[0], "TEXTURE_FILENAME") == 0) //TEXTURE_FILENAMEの文字列
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%s", &aFile[0]);
				D3DXCreateTextureFromFile(pDevice, &aFile[0], &m_pTexture[nCntTex]);
				nCntTex++;
			}

			if (strcmp(&aFile[0], "END_SCRIPT") == 0) //END_SCRIPTの文字列を見つけたら
			{
				break;
			}

		}
	}
	fclose(pFile);
}

//=============================================================================
//カラー変更
//=============================================================================
void CEffect_base::ColorChange(D3DCOLORVALUE color)
{
	VERTEX_3D*pVtx;//頂点情報へのポインタ

				   //頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点の色
	pVtx[0].col = D3DCOLOR_RGBA((int)color.r, (int)color.g, (int)color.b, (int)color.a);
	pVtx[1].col = D3DCOLOR_RGBA((int)color.r, (int)color.g, (int)color.b, (int)color.a);
	pVtx[2].col = D3DCOLOR_RGBA((int)color.r, (int)color.g, (int)color.b, (int)color.a);
	pVtx[3].col = D3DCOLOR_RGBA((int)color.r, (int)color.g, (int)color.b, (int)color.a);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//=============================================================================
//サイズ変更
//=============================================================================
void CEffect_base::ChangeSize(D3DXVECTOR3 size)
{
	VERTEX_3D*pVtx;//頂点情報へのポインタ

				   //頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-size.x, size.y, size.z);
	pVtx[1].pos = D3DXVECTOR3(size.x, size.y, size.z);
	pVtx[2].pos = D3DXVECTOR3(-size.x, -size.y, -size.z);
	pVtx[3].pos = D3DXVECTOR3(size.x, -size.y, -size.z);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//=============================================================================
//平面エフェクト
//=============================================================================
void CEffect_base::SetPosField(D3DXVECTOR3 pos, D3DXVECTOR3 Size, float Rotate, float Rotate2)
{
	VERTEX_3D *pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(/*pos.x*/ + (cosf(Rotate2)) * Size.x, Size.y, /*pos.z*/ + (sinf(Rotate))* Size.x);
	pVtx[1].pos = D3DXVECTOR3(/*pos.x*/ + (sinf(Rotate))  * Size.x, Size.y, /*pos.z*/ - (cosf(Rotate2))* Size.x);
	pVtx[2].pos = D3DXVECTOR3(/*pos.x*/ - (sinf(Rotate))  * Size.x, Size.y, /*pos.z*/ + (cosf(Rotate2))* Size.x);
	pVtx[3].pos = D3DXVECTOR3(/*pos.x*/ - (cosf(Rotate2)) * Size.x, Size.y, /*pos.z*/ - (sinf(Rotate))* Size.x);


	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();

}

//=============================================================================
//サイズ変更
//=============================================================================
void CEffect_base::BillboardSize(float size)
{
	VERTEX_3D*pVtx;//頂点情報へのポインタ

				   //頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-size, size, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(size, size, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-size, -size, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(size, -size, 0.0f);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//=============================================================================
//テクスチャ移動
//=============================================================================
void CEffect_base::TexturMove(D3DXVECTOR2 MoveTex)
{
	VERTEX_3D*pVtx;//頂点情報へのポインタ
	m_TexMove += MoveTex;

	if (m_TexMove.x >= 1.0f)
	{
		m_TexMove.x -= 1.0f;
	}
	else if (m_TexMove.x < 0.0f)
	{
		m_TexMove.x += 1.0f;
	}

	if (m_TexMove.y >= 1.0f)
	{
		m_TexMove.y -= 1.0f;
	}
	else if (m_TexMove.y < 0.0f)
	{
		m_TexMove.y += 1.0f;
	}

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(m_TexMove.x, m_TexMove.y);
	pVtx[1].tex = D3DXVECTOR2(m_TexNum.x + m_TexMove.x, m_TexMove.y);
	pVtx[2].tex = D3DXVECTOR2(m_TexMove.x, m_TexNum.y + m_TexMove.y);
	pVtx[3].tex = D3DXVECTOR2(m_TexNum.x + m_TexMove.x, m_TexNum.y + m_TexMove.y);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//=============================================================================
//テクスチャパターン
//=============================================================================
void CEffect_base::SetTexAnim(D3DXVECTOR2 TexPattern, D3DXVECTOR2 TexAnimSize)
{
	VERTEX_3D*pVtx;//頂点情報へのポインタ

	m_nSplit = TexPattern;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(m_TexNum.x + m_nSplit.x * TexAnimSize.x + m_TexMove.x, m_TexNum.y + m_nSplit.y * TexAnimSize.y + m_TexMove.y);
	pVtx[1].tex = D3DXVECTOR2(m_TexNum.x + m_nSplit.x * TexAnimSize.x + TexAnimSize.x + m_TexMove.x, m_TexNum.y + m_nSplit.y * TexAnimSize.y + m_TexMove.y);
	pVtx[2].tex = D3DXVECTOR2(m_TexNum.x + m_nSplit.x * TexAnimSize.x + m_TexMove.x, m_TexNum.y + m_nSplit.y *  +TexAnimSize.y + TexAnimSize.y + m_TexMove.y);
	pVtx[3].tex = D3DXVECTOR2(m_TexNum.x + m_nSplit.x * TexAnimSize.x + TexAnimSize.x + m_TexMove.x, m_TexNum.y + m_nSplit.y *  +TexAnimSize.y + TexAnimSize.y + m_TexMove.y);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();

}

//=============================================================================
//座標
//=============================================================================
void CEffect_base::SetPosBill(D3DXVECTOR3 pos, D3DXVECTOR3 pos2, D3DXVECTOR3 pos3, D3DXVECTOR3 pos4)
{
	VERTEX_3D*pVtx;//頂点情報へのポインタ
				   //頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = pos;
	pVtx[1].pos = pos2;
	pVtx[2].pos = pos3;
	pVtx[3].pos = pos4;

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}