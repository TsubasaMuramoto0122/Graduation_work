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
class CPlayer;

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
	static CPresetDelaySet *Create(int nArray, D3DXVECTOR3 pos, CPlayer *pPlayer = nullptr);
	static CPresetDelaySet *Create(string sName, D3DXVECTOR3 pos, CPlayer *pPlayer = nullptr);

private:
	CPlayer *m_pPlayer;	// プレイヤー
	D3DXVECTOR3 m_pos;	// 位置
	int m_nDelay;		// 遅延
	int m_nCallCnt;		// コールカウント
	int m_nArray;		// 配列
};									 

#endif