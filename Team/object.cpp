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
HRESULT CObject::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, int nType)
{
	SetPos(pos);
	SetRot(rot);
	m_move = move;
	ModelCopy(nType);
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
	if (CManager::GetPause() == false)
	{
		D3DXVECTOR3 pos = GetPos();
		D3DXVECTOR3 posOld = pos;
		D3DXVECTOR3 rot = GetRot();

	}
}

//描画処理
void CObject::Draw()
{
	m_pModel->DrawObject(GetPos(), GetRot());
}

CObject *CObject::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, int nType)
{
	CObject *pObject;
	pObject = new CObject(CScene::PRIORITY_OBJECT);
	if (pObject != NULL)
	{
		pObject->Init(pos, rot, move, nType);
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