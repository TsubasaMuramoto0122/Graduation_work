//=============================================================================
// ライフ管理 [life.cpp]
// Author : Kusakari Kakeru
//=============================================================================
//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "life.h"
#include "manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CLifeUI::CLifeUI(PRIORITY Priority) : CUI::CUI(Priority)
{
	// 変数のクリア
	m_nLife = 0;
	m_fObjectiveSize = 0.0f;
	m_fMaxSize = 0.0f;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR2(0.0f, 0.0f);
	m_barPos = D3DXVECTOR2(0.0f, 0.0f);
	memset(&m_apUI, NULL, sizeof(m_apUI));
}

//=============================================================================
// デストラクタ
//=============================================================================
CLifeUI::~CLifeUI()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CLifeUI::Init(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	// 変数の初期化
	m_nLife = 0;
	m_pos = pos;
	m_size = size;
	m_fObjectiveSize = m_size.x;
	m_fMaxSize = m_size.x;
	m_barPos = D3DXVECTOR2(m_pos.x - (m_size.x / 2), m_pos.y);

	// ライフの背景部分
	m_apUI[0] = CUI::Create(m_pos, m_size, -1, D3DCOLOR_RGBA(80, 80, 80, 255));

	// ライフのゲージ部分
	m_apUI[1] = CUI::Create(D3DXVECTOR3(m_barPos.x, m_barPos.y , 0.0f), D3DXVECTOR2(m_size.x, m_size.y * 0.8f), -1, D3DCOLOR_RGBA(50, 255, 20, 255));
	m_apUI[1]->SetBesideGauge(m_size.x);

	// ライフの枠部分
	/*m_apUI[2] = CScene2D::Create(m_pos);
	m_apUI[2]->SetSize(m_size * 0.9f);
	m_apUI[2]->SetTexture(-1);
	m_apUI[2]->ColorChange(D3DCOLOR_RGBA(50, 255, 20, 255));*/


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CLifeUI::Uninit()
{
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CLifeUI::Update()
{

}

//=============================================================================
// 描画処理
//=============================================================================
void CLifeUI::Draw()
{
	for (int nCnt2D = 0; nCnt2D < MAX_LIFE_IMAGE; nCnt2D++)
	{
		if (m_apUI[nCnt2D] != NULL)
		{
			m_apUI[nCnt2D]->Draw();
		}
	}
}

//=============================================================================
// 生成処理
//=============================================================================
CLifeUI *CLifeUI::Create(D3DXVECTOR2 pos, D3DXVECTOR2 size)
{
	CLifeUI *pLifeUI = NULL;
	pLifeUI = new CLifeUI(PRIORITY_UI);		//メモリ確保
											//NULLチェック
	if (pLifeUI != NULL)
	{
		pLifeUI->Init(D3DXVECTOR3(pos.x, pos.y, 0.0f), size);
	}

	return pLifeUI;
}

//=============================================================================
// ライフバーの設定処理
//=============================================================================
void CLifeUI::SetLifeBar(int nNowLife, int nMaxLife)
{
	m_nLife = nNowLife;

	// 画像のサイズとライフの最大値から割合の値を出す
	float fRatio = m_fMaxSize / nMaxLife;

	// <割合×現在のライフ>で目的のサイズを出す
	m_fObjectiveSize = fRatio * m_nLife;

	// ライフが0になったら
	if (nNowLife <= 0)
	{
		// サイズをすぐに変更し、ゲージを消す
		m_size.x = m_fObjectiveSize;
		m_apUI[1]->SetBesideGauge(m_size.x);
	}

	// 目的のサイズと現在のサイズが違うなら
	if (m_fObjectiveSize != m_size.x)
	{
		// 目的のサイズが現在のサイズより小さい場合
		if (m_fObjectiveSize < m_size.x)
		{
			m_size.x *= 0.99f;

			if (m_fObjectiveSize > m_size.x)
			{
				m_size.x = m_fObjectiveSize;
			}
		}
		// 目的のサイズが現在のサイズより大きい場合
		else if (m_fObjectiveSize > m_size.x)
		{
			m_size.x *= 1.01f;

			if (m_fObjectiveSize < m_size.x)
			{
				m_size.x = m_fObjectiveSize;
			}
		}

		// ある程度の値の範囲に達するまでゲージのサイズを変更
		if (m_size.x - m_fObjectiveSize > 0.01f || m_size.x - m_fObjectiveSize < -0.01f)
		{
			m_apUI[1]->SetBesideGauge(m_size.x);
		}
	}
}