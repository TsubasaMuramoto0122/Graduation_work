//=============================================================================
//
// 爆発範囲処理 [danger.h]
// Author : 三上航世
//
//=============================================================================
#include "danger.h"
#include "manager.h"
#include "renderer.h"

CDanger::CDanger(PRIORITY Priority) : CPlane::CPlane(Priority)
{

}

CDanger::~CDanger()
{

}

//初期化処理
HRESULT CDanger::Init(D3DXVECTOR3 size, D3DXVECTOR3 pos)
{
	CPlane::Init(size, pos, D3DXVECTOR2(1.0f, 1.0f), false);
	ChangeColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	return S_OK;
}

//終了処理
void CDanger::Uninit()
{
	CPlane::Uninit();
}

//更新処理
void CDanger::Update()
{
	if (CManager::GetPause() == false)
	{

	}
}

//描画処理
void CDanger::Draw()
{
	//LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	//pDevice = CManager::GetRenderer()->GetDevice();     //デバイスを取得する
	////減算合成の設定
	//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	//CPlane::Draw();
	////通常合成に戻す
	//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	CPlane::Draw();
}

CDanger *CDanger::Create(D3DXVECTOR3 size, D3DXVECTOR3 pos)
{
	CDanger *pDanger;
	pDanger = new CDanger(PRIORITY_EFFECT);
	if (pDanger != NULL)
	{
		pDanger->Init(size, pos);
		pDanger->SetTexture(1);
	}
	return pDanger;
}

void CDanger::Move(D3DXVECTOR3 pos)
{
	//m_fPosY = pos.y + 0.1f;
	SetPos(D3DXVECTOR3(pos.x, 0.01f, pos.z));
}