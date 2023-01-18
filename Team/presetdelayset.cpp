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
#include "scene.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CPresetDelaySet::CPresetDelaySet(PRIORITY nPriority) : CScene3D(nPriority)
{
	m_pos = {};			// 位置
	m_nDelay = 0;		// ディレイ
	m_nCallCnt = 0;		// 呼び出しカウント 
	m_nArray = 0;		// 番号
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
			// オフセットがテキストで読み込まれていたら
			auto itr = CallPreset.m_Offset.find(m_nCallCnt);
			if (itr != CallPreset.m_Offset.end())
			{
				// オフセットの設定
				D3DXVECTOR3 offset = CallPreset.m_Offset[m_nCallCnt];
				for (int nCnt = 0; nCnt < CallPreset.m_nPresetNum[m_nCallCnt]; nCnt++)
				{
					// プリセットの生成
					CPresetEffect::Create(CallPreset.m_nType[m_nCallCnt].at(nCnt), m_pos, offset, m_pPlayer);
				}
			}

			// 座標が無い場合
			else
			{
				// 出現位置にエフェクトを出す(m_posのまま)
				for (int nCnt = 0; nCnt < CallPreset.m_nPresetNum[m_nCallCnt]; nCnt++)
				{
					// プリセットの生成
					CPresetEffect::Create(CallPreset.m_nType[m_nCallCnt].at(nCnt), m_pos, {}, m_pPlayer);
				}
			}

			// コール数をカウント
			m_nCallCnt++;
		}

		// ディレイを進める
		m_nDelay++;
	}

	else
	{
		SetDeath(true);
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
CPresetDelaySet* CPresetDelaySet::Create(int nArray, D3DXVECTOR3 pos, CPlayer *pPlayer)
{
	// メモリ確保
	CPresetDelaySet *pPresetDelay = nullptr;
	pPresetDelay = new CPresetDelaySet(PRIORITY_EFFECTSET);

	if (pPresetDelay)
	{
		pPresetDelay->m_pPlayer = pPlayer;
		pPresetDelay->m_nArray = nArray;
		pPresetDelay->Init(pos);
	}

	return pPresetDelay;
}

//=============================================================================
// 生成(文字列入力)
//=============================================================================
CPresetDelaySet* CPresetDelaySet::Create(string sName, D3DXVECTOR3 pos, CPlayer *pPlayer)
{
	return Create(CLoadEffect::GetPresetName(sName), pos, pPlayer);
}
