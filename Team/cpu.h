//=============================================================================
// AI操作処理 [cpu.h]
// Author : 三上　航世
//=============================================================================
#ifndef _CPU_H_
#define _CPU_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "control.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CScene;
class CPlayer;
class CBomb;
class CCollisionSphere;

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CCPU : public CControl
{
	//考え方
	typedef enum
	{
		THINK_NONE,		// 何もしない
		THINK_BOMB,		// 爆弾に攻撃
		THINK_PLAYER,	// プレイヤーに攻撃
		THINK_MOVE,		// どっかに動く
		THINK_SLIDING,	// スライディング
		MAX_THINK
	} THINKTYPE;

public:
	CCPU();										// コンストラクタ
	~CCPU();									// デストラクタ
	HRESULT Init(void);							// 初期化処理
	void Uninit(void);							// 終了処理
	void Update(CScene *pScene);				// 更新処理
	static CCPU *Create(void);					// 生成処理

private:
	void Move(CPlayer *pPlayer);					// 移動処理
	void Sliding(CPlayer *pPlayer);				// スライディング(回避)処理
	void Attack(CPlayer *pPlayer);				// 攻撃処理
	void TakeDamage(CPlayer *pPlayer);			// 被ダメージ処理
	void Defeat(CPlayer *pPlayer);				// 敗北処理

	void MoveInteria(CPlayer *pPlayer);			// 移動の慣性についての処理
	void Rotate(CPlayer *pPlayer);				// 回転処理
	bool SetMove();								// 移動量の加算および目的の向きの設定
	void Search(CPlayer *pPlayer);				// 一番近いプレイヤーと爆弾を探す

	D3DXVECTOR3 m_rot;							// 向き
	float m_fObjectiveRot;						// 目的の向き
	float m_fNumRot;							// 向きを変える量
	float m_fSpeed;								// 移動量に加える速さ
	bool m_bRotate;								// 回転しているかどうか
	bool m_bAttack;								// 攻撃しているかどうか
	bool m_bDamage;								// ダメージを受けたかどうか
	bool m_bStan;								// スタン中かどうか
	bool m_bSliding;							// スライディング(回避)しているかどうか
	bool m_bDefeat;								// 敗北したかどうか
	int m_nSlidingCount;						// スライディング(回避)中のカウント
	int m_nSlidingCoolTime;						// スライディング(回避)のクールタイム
	int m_nAttackCount;							// 攻撃中のカウント
	int m_nAttackCoolTime;						// 攻撃のクールタイム
	int m_nStanCount;							// スタン中のカウント
	CCollisionSphere *m_pCollision;				// 球体コリジョンのポインタ
	CPlayer *m_pPlayer;							// 一番近いプレイヤー
	CBomb *m_pBomb;								// 一番近い爆弾

	bool m_bMove;								// 移動しているかどうか
	int m_nMoveTime;							// 移動する時間
	int m_nThinkTime;							// 思考時間
	float m_fMoveRot;							// 移動する方向
	THINKTYPE m_thinkType;						// 何しようとしてるか
	bool m_bNextAttack;							// 次攻撃する
	bool m_bNextSliding;						// 次回避する
	bool m_bWall;								// 壁に当たったか
};
#endif	//_CONTROL_PLAYER_H_