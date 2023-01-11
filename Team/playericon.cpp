//=============================================================================
//
// プレイヤーアイコン [playericon.h]
// Author : 三上航世
//
//=============================================================================
//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "ui.h"
#include "scene2d.h"
#include "playericon.h"
#include "manager.h"


//*****************************************************************************
//静的
//*****************************************************************************

//*****************************************************************************
//マクロ
//*****************************************************************************

#if 1
//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CPlayerIcon::CPlayerIcon(CScene::PRIORITY Priority) : CUI(Priority)
{

}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CPlayerIcon::~CPlayerIcon()
{

}
#endif

//*****************************************************************************
//初期化
//*****************************************************************************
HRESULT CPlayerIcon::Init(D3DXVECTOR2 pos, D3DXVECTOR2 size, int nType, D3DXCOLOR col)
{
	CUI::Init(pos, size, nType, col);
	m_fPlus = 1.5f;
	return S_OK;
}

//*****************************************************************************
//終了
//*****************************************************************************
void CPlayerIcon::Uninit()
{
	CUI::Uninit();
}

//*****************************************************************************
//更新
//*****************************************************************************
void CPlayerIcon::Update()
{
	//ダメージ食らったら
	if (m_bDamage == true)
	{
		//カウント減らす
		m_nDamageTime--;

		//カウント0以下
		if (m_nDamageTime <= 0)
		{
			//振動終了
			D3DXVECTOR3 pos = GetPos();
			SetPos(pos);
			m_fPlus = 1.5f;
			m_bDamage = false;
		}
		//カウント一定ごと
		else if (m_nDamageTime % 2 == 0)
		{
			//カウント少なくなると、振動徐々に小さくする
			if (m_nDamageTime < 40)
			{
				m_fPlus *= -0.9f;
			}
			//通常の振動
			else
			{
				m_fPlus *= -1.0f;
			}

			//振動させる
			D3DXVECTOR3 pos = GetPos();
			SetPos(D3DXVECTOR3(pos.x + m_fPlus, pos.y, pos.z));
		}
	}
}

//描画・作成
#if 1
//*****************************************************************************
//描画
//*****************************************************************************
void CPlayerIcon::Draw()
{
	CUI::Draw();
}

//*****************************************************************************
//作成
//*****************************************************************************
CPlayerIcon *CPlayerIcon::Create(D3DXVECTOR2 pos, D3DXVECTOR2 size, int nType, D3DXCOLOR col)
{
	CPlayerIcon *pPlayerIcon = NULL;
	pPlayerIcon = new CPlayerIcon(PRIORITY_UI);
	if (pPlayerIcon != NULL)
	{
		pPlayerIcon->Init(pos, size, nType, col);
	}
	return pPlayerIcon;
}
#endif

//*****************************************************************************
//ダメージくらった
//*****************************************************************************
void CPlayerIcon::SetDamage(bool bDamage)
{
	m_bDamage = bDamage;
	m_nDamageTime = 120;
}