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
<<<<<<< HEAD
#include "scene.h"
=======
<<<<<<< HEAD
#include "scene.h"
=======
#include "manager.h"
>>>>>>> edf369e2fe44aed194aa4aed39d2958e583283af
>>>>>>> e1265ec22361454c26360ce27e721e0a1665dc3a

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
<<<<<<< HEAD
	// プリセット呼び出し情報を保存
	CLoadEffect::CALL_PRESET CallPreset = CLoadEffect::GetCallPreset(m_nArray);

	//-----------------------------------------------------------------
	// プリセット呼び出し
	//-----------------------------------------------------------------
	// コール数が最大数を超えるまで通る
	if (m_nCallCnt < CallPreset.m_CallMax)
=======
	if (CManager::GetPause() == false && CManager::GetCountdown() == false)
>>>>>>> e1265ec22361454c26360ce27e721e0a1665dc3a
	{
		// エフェクトを呼び出す
		if (m_nDelay >= CallPreset.m_nDelay[m_nCallCnt])
		{
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> e1265ec22361454c26360ce27e721e0a1665dc3a
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
<<<<<<< HEAD
=======
=======
			// エフェクトを呼び出す
			if (m_nDelay >= CallPreset.m_nDelay[m_nCallCnt])
			{
				// プリセットのローカルクラス
				CPresetEffect *pPreset = nullptr;

				// 座標がテキストで読み込まれていたら
				auto itr = CallPreset.m_Sftpos.find(m_nCallCnt);
				if (itr != CallPreset.m_Sftpos.end())
				{
					// 出現位置にテキストで読み込んだ座標をプラスする
					D3DXVECTOR3 pos = CallPreset.m_Sftpos[m_nCallCnt] + m_pos;
					for (int nCnt = 0; nCnt < CallPreset.m_nPresetNum[m_nCallCnt]; nCnt++)
					{
						// プリセットの生成
						pPreset = CPresetEffect::Create();
						pPreset->SetEffect3D(CallPreset.m_nType[m_nCallCnt].at(nCnt), pos, {}, {});
						m_vPreset.emplace_back(pPreset);
					}
>>>>>>> edf369e2fe44aed194aa4aed39d2958e583283af
>>>>>>> e1265ec22361454c26360ce27e721e0a1665dc3a
				}
			}

			// 座標が無い場合
			else
			{
				// 出現位置にエフェクトを出す(m_posのまま)
				for (int nCnt = 0; nCnt < CallPreset.m_nPresetNum[m_nCallCnt]; nCnt++)
				{
<<<<<<< HEAD
					// プリセットの生成
					CPresetEffect::Create(CallPreset.m_nType[m_nCallCnt].at(nCnt), m_pos, {}, m_pPlayer);
=======
<<<<<<< HEAD
					// プリセットの生成
					CPresetEffect::Create(CallPreset.m_nType[m_nCallCnt].at(nCnt), m_pos, {}, m_pPlayer);
=======
					// 出現位置にエフェクトを出す(m_posのまま)
					for (int nCnt = 0; nCnt < CallPreset.m_nPresetNum[m_nCallCnt]; nCnt++)
					{
						// プリセットの生成
						pPreset = CPresetEffect::Create();
						pPreset->SetEffect3D(CallPreset.m_nType[m_nCallCnt].at(nCnt), m_pos, {}, {});
						m_vPreset.emplace_back(pPreset);
					}
>>>>>>> edf369e2fe44aed194aa4aed39d2958e583283af
>>>>>>> e1265ec22361454c26360ce27e721e0a1665dc3a
				}
			}

<<<<<<< HEAD
			// コール数をカウント
			m_nCallCnt++;
		}

		// ディレイを進める
		m_nDelay++;
	}

	else
	{
		SetDeath(true);
=======
<<<<<<< HEAD
		// ディレイを進める
		m_nDelay++;
	}

	else
	{
		SetDeath(true);
=======
		//-----------------------------------------------------------------
		// プリセットを呼び出し終わった後の処理
		//-----------------------------------------------------------------
		else
		{
			SetDeath(true);
			if (!m_bMove)
			{
				m_bMove = true;
			}
		}
>>>>>>> edf369e2fe44aed194aa4aed39d2958e583283af
>>>>>>> e1265ec22361454c26360ce27e721e0a1665dc3a
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
<<<<<<< HEAD
CPresetDelaySet* CPresetDelaySet::Create(string sName, D3DXVECTOR3 pos, CPlayer *pPlayer)
=======
<<<<<<< HEAD
CPresetDelaySet* CPresetDelaySet::Create(string sName, D3DXVECTOR3 pos, CPlayer *pPlayer)
=======
CPresetDelaySet* CPresetDelaySet::Create(string sName, D3DXVECTOR3 pos)
{
	return Create(CLoadEffect::GetPresetName(sName), pos);
}

//=============================================================================
// 生成(文字列入力)
//=============================================================================
void CPresetDelaySet::Move(D3DXVECTOR3 move)
>>>>>>> edf369e2fe44aed194aa4aed39d2958e583283af
>>>>>>> e1265ec22361454c26360ce27e721e0a1665dc3a
{
	return Create(CLoadEffect::GetPresetName(sName), pos, pPlayer);
}