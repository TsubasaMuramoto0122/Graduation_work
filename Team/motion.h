//=============================================================================
// モーション処理 [motion.h]
// Author : 草刈 翔
//=============================================================================
#ifndef _MOTION_H_
#define _MOTION_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_MODEL_INFO		(32)	// モデル(パーツ)の最大値
#define MAX_KEY_INFO		(32)	// キーの情報の最大値
#define MAX_MOTION_INFO		(32)	// キーの情報の最大値

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CScene;
class CPlayer;

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CMotion
{
public:
	typedef enum
	{
		MOTION_TYPE_P1 = 0,
		MOTION_TYPE_P2,
		MOTION_TYPE_P3,
		MOTION_TYPE_P4,
		MOTION_TYPE_BATTERY,
		MOTION_TYPE_MAX
	} MOTION_TYPE;

	//キーの構造体
	typedef struct
	{
		D3DXVECTOR3 pos;	//位置
		D3DXVECTOR3 rot;	//向き
	} KEY;

	//キー情報の構造体
	typedef struct
	{
		int nFrame;					//再生フレーム
		KEY aKey[MAX_MODEL_INFO];	//各モデルのキー要素(パーツの最大数)
	} KEY_INFO;

	//モーション情報の構造体
	typedef struct
	{
		int nLoop;							//ループするかどうか
		int nNumKey;						//キーの総数
		KEY_INFO aKeyInfo[MAX_KEY_INFO];	//キーの情報
	} MOTION_INFO;

	CMotion();													// コンストラクタ
	virtual ~CMotion();											// デストラクタ
	HRESULT Init(CScene *pScene, MOTION_TYPE type);				// 初期化処理
	void Uninit(void);											// 終了処理
	void Update(CScene *pScene);								// 更新処理
	static CMotion *Create(CScene *pScene, MOTION_TYPE type);	// 生成処理

	bool GetConnect(void) { return m_bConnect; }				// モーション結合取得処理
	void SetMotion(int nType);									// モーション設定処理
	int GetMotion(void) { return m_nType; }						// モーション取得処理
	void SetStop(bool bStop) { m_bStop = bStop; }				// ストップ設定処理
	bool GetStop(void) { return m_bStop; }						// ストップ取得処理
	int GetNextMotion(void) { return m_nTypeNext; }				// 次のモーション取得処理

private:
	void FileLoad(FILE *pFile);						// ファイルの読み込み処理
	void SetParts(CScene *pScene);					// 位置関係の修正処理
	void NonLoopMotion(MOTION_TYPE type);			// 非ループモーションの処理

	int m_nMaxModelNum;								// モデル(パーツ)の最大数
	int m_nMaxMotionNum;							// モーションの最大数
	int m_nNumKey;									// キー数
	int m_nKey;										// 現在のキー
	int m_nKeyNext;									// 次のキー
	int m_nKeyOld;									// 1フレーム前のキー
	int m_nType;									// 現在のモーションタイプ
	int m_nTypeNext;								// 次のモーションタイプ
	float m_fCounter;								// モーションのカウンター
	bool m_bConnect;								// モーション結合中かどうか
	bool m_bStop;									// モーションを止めるかどうか
	MOTION_INFO m_aInfo[MAX_MOTION_INFO];			// モーション情報
	MOTION_TYPE m_type;								// 種類

};
#endif	// _MOTION_H_