//=============================================================================
// 遅延付きプリセット呼び出しクラス
// Author : 村元翼
//=============================================================================
#include "PresetDelaySet.h"
#include "loadeffect.h"
#include "presetseteffect.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CPresetDelaySet::CPresetDelaySet(PRIORITY nPriority) : CScene3D(nPriority)
{
	m_pos = {};			// 位置
	m_nDelay = 0;		// ディレイ
	m_nCallCnt = 0;		// 呼び出しカウント 
	m_nArray = 0;			// 番号
	m_bUninit = false;	// 終了判定するか
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

	// エフェクトを呼び出す
	if (m_nDelay >= CallPreset.m_nDelay[m_nCallCnt])
	{
		for (int nCnt = 0; nCnt < CallPreset.m_nPresetNum[m_nCallCnt]; nCnt++)
		{
			CPresetEffect::SetEffect3D(CallPreset.m_nType[m_nCallCnt].at(nCnt), m_pos, {}, {});
		}
		m_nCallCnt++;
	}

	// コール数が最大数を超える
	if (m_nCallCnt >= CallPreset.m_CallMax)
	{
		SetDeath(true);
	}

	// ディレイを進める
	m_nDelay++;
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
// 生成
//=============================================================================
CPresetDelaySet* CPresetDelaySet::Create(std::string sName, D3DXVECTOR3 pos)
{
	return Create(CLoadEffect::GetPresetName(sName), pos);
}