//---------------------------
// Author:三上航世
// ボム(bomb.cpp)
//---------------------------
#include "bomb.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "danger.h"
#include "sound.h"
#include "ui.h"

//=============================================================================
//静的
//=============================================================================
CModel *CBomb::m_paModel[MAX_BOMB] = {};

//=============================================================================
//マクロ
//=============================================================================
#define REFLECT (-0.4f)		//反射
#define GRAVITY (0.3f)		//重力

CBomb::CBomb(PRIORITY Priority) : CScene3D::CScene3D(Priority)
{

}

CBomb::~CBomb()
{

}

//初期化処理
HRESULT CBomb::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, BOMBTYPE BombType)
{
	D3DXVECTOR3 VtxMax, VtxMin;
	m_pModel = new CModel;
	m_pModel->Copy(m_paModel[BombType]);
	VtxMax = m_pModel->GetMaxSize();
	VtxMin = m_pModel->GetMinSize();
	float fRadius = (VtxMax.x - VtxMin.x) / 2.0f;
	if (fRadius < (VtxMax.y - VtxMin.y) / 2.0f)
	{
		fRadius = (VtxMax.y - VtxMin.y) / 2.0f;
	}
	if (fRadius < (VtxMax.z - VtxMin.z) / 2.0f)
	{
		fRadius = (VtxMax.z - VtxMin.z) / 2.0f;
	}
	m_move = move;
	m_nTime = 250;
	m_pDanger = CDanger::Create(D3DXVECTOR3(fRadius * 3.0f, 0.0f, fRadius * 3.0f), pos);
	SetRot(rot);
	SetPos(pos);
	m_bBound = false;
	m_bLand = false;
	return S_OK;
}

//終了処理
void CBomb::Uninit()
{
	if (m_pModel != NULL)
	{
		//m_pModel->Uninit();
		m_pModel = NULL;
	}
	if (m_pDanger != NULL)
	{
		m_pDanger->SetDeath(true);
		m_pDanger = NULL;
	}
	CScene3D::Uninit();
}

//更新処理
void CBomb::Update()
{
	if (CManager::GetPause() == false)
	{
		D3DXVECTOR3 pos = GetPos();
		D3DXVECTOR3 rot = GetRot();
		if (m_bLand == false)
		{
			pos += m_move;
			m_move.y -= GRAVITY;
		}
		else
		{
			pos += m_move;
			m_move *= 0.97f;
		}
		if (pos.y < 0.0f)
		{
			if (m_bBound == true)
			{
				pos.y = 0.0f;
				m_move.y = 0.0f;
				m_bLand = true;
			}
			else
			{
				pos.y = 0.0f;
				m_move.y *= REFLECT;
				m_bBound = true;
			}
		}
		SetPos(pos);
		m_pDanger->Move(pos);
		if (m_nTime > 0)
		{
			m_nTime--;
		}
		else
		{
			//Explosion();
			SetDeath(true);
		}
	}
}

//描画処理
void CBomb::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;   //デバイスのポインタ
	D3DXMATRIX mtxPlayer, mtxRot, mtxTrans;
	pDevice = CManager::GetRenderer()->GetDevice();		 //デバイスを取得する

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxPlayer);
	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, GetRot().y, GetRot().x, GetRot().z);
	D3DXMatrixMultiply(&mtxPlayer, &mtxPlayer, &mtxRot);
	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);
	D3DXMatrixMultiply(&mtxPlayer, &mtxPlayer, &mtxTrans);
	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxPlayer);
	SetMatrix(mtxPlayer);
	m_pModel->Draw();
}

void CBomb::Load(int nCnt, const char *aModelName)
{
	m_paModel[nCnt] = CModel::Create(aModelName);
}

void CBomb::UnLoad()
{
	int nCntModel;
	for (nCntModel = 0; nCntModel < MAX_BOMB; nCntModel++)
	{
		if (m_paModel[nCntModel] != NULL)
		{
			m_paModel[nCntModel]->Uninit();
			m_paModel[nCntModel] = NULL;
		}
	}
}