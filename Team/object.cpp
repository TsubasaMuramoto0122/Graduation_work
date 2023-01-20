//=============================================================================
//
// オブジェクト処理 [object.h]
// Author : 三上航世
//
//=============================================================================
#include "object.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"

//静的メンバ変数
CModel *CObject::m_paModel[8] = {};

CObject::CObject(PRIORITY nPriority) : CScene3D(nPriority)
{

}

CObject::~CObject()
{

}

//初期化処理
HRESULT CObject::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType, bool bShadow)
{
	SetPos(pos);
	SetRot(rot);
	ModelCopy(nType);
	m_pModel->SetShadow(bShadow);
	
	return S_OK;
}

//終了処理
void CObject::Uninit()
{
	if (m_pModel != NULL)
	{
		m_pModel = NULL;
	}
	CScene3D::Uninit();
}

//更新処理
void CObject::Update()
{
	if (CManager::GetPause() == false && CManager::GetCountdown() == false && CManager::GetGameEnd() == false)
	{
		
	}
}

//描画処理
void CObject::Draw()
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	m_pModel->Draw();
}

void CObject::ZTexDraw()
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

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	m_pModel->ZTexDraw();
}

CObject *CObject::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType, bool bShadow)
{
	CObject *pObject;
	pObject = new CObject(CScene::PRIORITY_OBJECT);
	if (pObject != NULL)
	{
		pObject->Init(pos, rot, nType, bShadow);
	}
	return pObject;
}

void CObject::Load(int nCnt, const char *aModelName)
{
	m_paModel[nCnt] = CModel::Create(aModelName);
}

void CObject::UnLoad()
{
	int nCntModel;
	for (nCntModel = 0; nCntModel < MAX_OBJECTS; nCntModel++)
	{
		if (m_paModel[nCntModel] != NULL)
		{
			m_paModel[nCntModel]->Uninit();
			m_paModel[nCntModel] = NULL;
		}
	}
}

void CObject::ModelCopy(int nType)
{
	m_pModel = new CModel;
	m_pModel->Copy(m_paModel[nType]);
}