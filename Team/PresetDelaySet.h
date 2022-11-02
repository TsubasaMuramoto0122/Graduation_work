//=============================================================================
// 遅延付きエフェクトプリセット呼び出しクラス
// Author : 村元翼
//=============================================================================
#ifndef _PRESETDELAYSET_H_
#define _PRESETDELAYSET_H_
#include "scene3d.h"
#include "main.h"
#include <string>
#include <vector>
using namespace std;

//=============================================================================
// 前方宣言
//=============================================================================
class CStraight3D;
class CFieldEffect;
class CPlayer;
class CPresetEffect;

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

	// 生成
	static CPresetDelaySet *Create(int nArray, D3DXVECTOR3 pos);
	static CPresetDelaySet *Create(string sName, D3DXVECTOR3 pos);

	// 移動
	void Move(D3DXVECTOR3 move);

	// 移動判定取得
	bool GetbMove(void) { return m_bMove; }

private:
	D3DXVECTOR3 m_pos;	// 位置
	int m_nDelay;		// 遅延
	int m_nCallCnt;		// コールカウント
	int m_nArray;		// 配列
	bool m_bMove;		// 移動判定

	vector<CPresetEffect*> m_vPreset;	// プリセット
};									 

#endif