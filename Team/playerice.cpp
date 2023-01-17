//=============================================================================
//
// プレイヤーの氷処理 [playerice.h]
// Author : 三上航世
//
//=============================================================================
#include "playerice.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"

//静的メンバ変数
CModel *CPlayerIce::m_paModel = NULL;

CPlayerIce::CPlayerIce(PRIORITY nPriority) : CObject(nPriority)
{

}

CPlayerIce::~CPlayerIce()
{

}

//初期化処理
HRESULT CPlayerIce::Init(D3DXMATRIX mtx)
{
	int nRandom = rand() % 11;
	float fRot;
	if (nRandom == 5)
	{
		fRot = 0.0f;
	}
	else
	{
		fRot = D3DX_PI / (nRandom - 5);
	}

	m_mtxParent = mtx;
	SetRot(D3DXVECTOR3(0.0f, fRot, 0.0f));
	m_pModel = new CModel;
	m_pModel->Copy(m_paModel);
	return S_OK;
}

//終了処理
void CPlayerIce::Uninit()
{
	if (m_pModel != NULL)
	{
		m_pModel = NULL;
	}
	CScene3D::Uninit();
}

//更新処理
void CPlayerIce::Update()
{
	if (CManager::GetPause() == false && CManager::GetCountdown() == false && CManager::GetGameEnd() == false)
	{

	}
}

//描画処理
void CPlayerIce::Draw()
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	m_pModel->Draw();
}

void CPlayerIce::ZTexDraw()
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//pos、rotの取得
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 親モデルと加算
	//D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxParent);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	m_pModel->ZTexDraw();
}

CPlayerIce *CPlayerIce::Create(D3DXMATRIX mtx)
{
	CPlayerIce *pPlayerIce;
	pPlayerIce = new CPlayerIce(CScene::PRIORITY_OBJECT);
	if (pPlayerIce != NULL)
	{
		pPlayerIce->Init(mtx);
	}
	return pPlayerIce;
}

void CPlayerIce::Load(const char *aModelName)
{
	m_paModel = CModel::Create(aModelName);
}

void CPlayerIce::UnLoad()
{
	if (m_paModel != NULL)
	{
		m_paModel->Uninit();
		m_paModel = NULL;
	}
}