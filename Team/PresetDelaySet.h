//=============================================================================
// 遅延付きエフェクトプリセット呼び出しクラス
// Author : 村元翼
//=============================================================================
#ifndef _PRESETDELAYSET_H_
#define _PRESETDELAYSET_H_
#include "scene3d.h"
#include "main.h"
#include <string>

//=============================================================================
// クラス定義
//=============================================================================
class CPresetDelaySet : public CScene3D
{
public:
	CPresetDelaySet(PRIORITY nPriority);	// コンストラクタ
	~CPresetDelaySet();						// デストラクタ

	HRESULT Init(D3DXVECTOR3 pos);	 // 初期化
	void Uninit();					 // 終了
	void Update();					 // 更新
	void Draw();					 // 描画

	static CPresetDelaySet *Create(int nArray, D3DXVECTOR3 pos);
	static CPresetDelaySet *Create(std::string sName, D3DXVECTOR3 pos);

private:
	D3DXVECTOR3 m_pos;
	int m_nDelay;
	int m_nCallCnt;
	int m_nArray;
	bool m_bUninit;
};									 

#endif