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
	m_size = size;
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
	if (CManager::GetPause() == false && CManager::GetCountdown() == false && CManager::GetGameEnd() == false)
	{

	}
}

//描画処理
void CDanger::Draw()
{
	CPlane::Draw();
}

void CDanger::ZTexDraw()
{
	//CPlane::Draw();
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
	SetPos(D3DXVECTOR3(pos.x, 0.1f, pos.z));
}