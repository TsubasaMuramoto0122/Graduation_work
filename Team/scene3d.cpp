//=============================================================================
//
// フェード処理 [scene3d.h]
// Author : 三上航世
//
//=============================================================================
#include "scene3d.h"
#include "manager.h"
#include "renderer.h"

//静的メンバ変数
LPDIRECT3DTEXTURE9 CScene3D::m_pTexture[MAX_3DTEXTURE] = {};
int CScene3D::m_nMaxTex = 0;

//マクロ定義
#define TEXTURE_FILENAME_3D "data/FILES/3DTexNameRead.txt"

CScene3D::CScene3D(PRIORITY Priority) : CScene::CScene(Priority)
{

}

CScene3D::~CScene3D()
{

}


//初期化処理
HRESULT CScene3D::Init(D3DXVECTOR3 /*pos*/)
{
	return S_OK;
}

//終了処理
void CScene3D::Uninit()
{
	Release();
}

//更新処理
void CScene3D::Update()
{

}

//描画処理
void CScene3D::Draw()
{

}

void CScene3D::ZTexDraw()
{

}

CScene3D *CScene3D::Create(const D3DXVECTOR3& pos)
{
	CScene3D *pScene3D;
	pScene3D = new CScene3D(PRIORITY_OBJECT);
	if (pScene3D != NULL)
	{
		pScene3D->Init(pos);
	}
	return pScene3D;
}

//=============================================================================
// テクスチャ破棄
//=============================================================================
void CScene3D::UninitTexture()
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
// テクスチャ生成
//=============================================================================
void CScene3D::CreateTextureFiled()
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
		fclose(pFile);
	}
}


void CScene3D::SetRot(D3DXVECTOR3 rot)
{
	if (rot.x  < -D3DX_PI)
	{
		rot.x += D3DX_PI * 2.0f;
	}
	else if (D3DX_PI < rot.x)
	{
		rot.x -= D3DX_PI * 2.0f;
	}
	if (rot.y  < -D3DX_PI)
	{
		rot.y += D3DX_PI * 2.0f;
	}
	else if (D3DX_PI < rot.y)
	{
		rot.y -= D3DX_PI * 2.0f;
	}
	if (rot.z  < -D3DX_PI)
	{
		rot.z += D3DX_PI * 2.0f;
	}
	else if (D3DX_PI < rot.z)
	{
		rot.z -= D3DX_PI * 2.0f;
	}
	m_rot = rot;
}