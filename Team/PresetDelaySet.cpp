//=============================================================================
// 遅延付きプリセット呼び出しクラス
// Author : 村元翼
//=============================================================================
#include "PresetDelaySet.h"
#include "presetseteffect.h"
#include "straight3d.h"
#include "fieldeffect.h"
#include "loadeffect.h"
#include "player.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CPresetDelaySet::CPresetDelaySet(PRIORITY nPriority) : CScene3D(nPriority)
{
	m_pos = {};			// 位置
	m_nDelay = 0;		// ディレイ
	m_nCallCnt = 0;		// 呼び出しカウント 
	m_nArray = 0;		// 番号
	m_bMove = false;	// 終了判定するか
}

//=============================================================================
// デストラクタ
//=============================================================================
CPresetDelaySet::~CPresetDelaySet()
{

}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CPresetDelaySet::Init(D3DXVECTOR3 pos)
{
	m_pos = pos;	// 位置

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CPresetDelaySet::Uninit()
{
	if (!m_vPreset.empty())
	{
		m_vPreset.clear();
		m_vPreset.shrink_to_fit();
	}

	Release();
}

//=============================================================================
// 更新
//=============================================================================
void CPresetDelaySet::Update()
{
	// プリセット呼び出し情報を保存
	CLoadEffect::CALL_PRESET CallPreset = CLoadEffect::GetCallPreset(m_nArray);

	//-----------------------------------------------------------------
	// プリセット呼び出し
	//-----------------------------------------------------------------
	// コール数が最大数を超えるまで通る
	if (m_nCallCnt < CallPreset.m_CallMax)
	{
		// エフェクトを呼び出す
		if (m_nDelay >= CallPreset.m_nDelay[m_nCallCnt])
		{
			// プリセットのローカルクラス
			CPresetEffect *pPreset = nullptr;

			// 座標がテキストで読み込まれていたら
			auto itr = CallPreset.m_Offset.find(m_nCallCnt);
			if (itr != CallPreset.m_Offset.end())
			{
				// 出現位置にテキストで読み込んだ座標をプラスする
			D3DXVECTOR3 pos = CallPreset.m_Offset[m_nCallCnt] + m_pos;
				for (int nCnt = 0; nCnt < CallPreset.m_nPresetNum[m_nCallCnt]; nCnt++)
				{
					// プリセットの生成
					pPreset = CPresetEffect::Create();
					pPreset->SetEffect3D(CallPreset.m_nType[m_nCallCnt].at(nCnt), pos, {}, {});
					m_vPreset.emplace_back(pPreset);
				}
			}

			// 座標が無い場合
			else
			{
				// 出現位置にエフェクトを出す(m_posのまま)
				for (int nCnt = 0; nCnt < CallPreset.m_nPresetNum[m_nCallCnt]; nCnt++)
				{
					// プリセットの生成
					pPreset = CPresetEffect::Create();
					pPreset->SetEffect3D(CallPreset.m_nType[m_nCallCnt].at(nCnt), m_pos, {}, {});
					m_vPreset.emplace_back(pPreset);
				}
			}

			// コール数をカウント
			m_nCallCnt++;
		}

		//SetDeath(true)
		// ディレイを進める
		m_nDelay++;
	}

	//-----------------------------------------------------------------
	// プリセットを呼び出し終わった後の処理
	//-----------------------------------------------------------------
	else
	{
		if (!m_bMove)
		{
			m_bMove = true;
		}
	}
}

//=============================================================================
// 描画
//=============================================================================
void CPresetDelaySet::Draw()
{

}

//=============================================================================
// 生成
//=============================================================================
CPresetDelaySet* CPresetDelaySet::Create(int nArray, D3DXVECTOR3 pos)
{
	// メモリ確保
	CPresetDelaySet *pPresetDelay = nullptr;
	pPresetDelay = new CPresetDelaySet(PRIORITY_EFFECT);

	if (pPresetDelay)
	{
		pPresetDelay->m_nArray = nArray;
		pPresetDelay->Init(pos);
	}

	return pPresetDelay;
}

//=============================================================================
// 生成(文字列入力)
//=============================================================================
CPresetDelaySet* CPresetDelaySet::Create(string sName, D3DXVECTOR3 pos)
{
	return Create(CLoadEffect::GetPresetName(sName), pos);
}

//=============================================================================
// エフェクトの移動
//=============================================================================
void CPresetDelaySet::Move(D3DXVECTOR3 move)
{
	if (m_bMove)
	{
		if (!m_vPreset.empty())
		{
			for (CPresetEffect *pPreset : m_vPreset)
			{
				pPreset->Move(move);
			}
		}
	}
}