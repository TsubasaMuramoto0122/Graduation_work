//=============================================================================
// プレイヤー操作処理 [control_player.h]
// Author : Kusakari Kakeru
//=============================================================================
#ifndef _CONTROL_PLAYER_H_
#define _CONTROL_PLAYER_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "control.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PLAYER_KNOCKBACK_JUMP		(6.5f)	// ノックバックのジャンプ量
#define PLAYER_DEFEATKNOCKBACK_JUMP	(11.0f)	// 敗北時のノックバックのジャンプ量

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CScene;
class CPlayer;
class CCollisionSphere;

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CControlPlayer : public CControl
{
public:
	CControlPlayer();						// コンストラクタ
	~CControlPlayer();						// デストラクタ
	HRESULT Init(void);						// 初期化処理
	void Uninit(void);						// 終了処理
	void Update(CScene *pScene);			// 更新処理
	static CControlPlayer *Create(void);	// 生成処理

private:
	void Move(CPlayer *pPlayer);			// 移動処理
	void Sliding(CPlayer *pPlayer);			// スライディング(回避)処理
	void Attack(CPlayer *pPlayer);			// 攻撃処理
	void TakeDamage(CPlayer *pPlayer);		// 被ダメージ処理
	void Defeat(CPlayer *pPlayer);			// 敗北処理
	//void Jump(CPlayer *pPlayer);			// ジャンプ処理
	void MoveInteria(void);					// 移動の慣性についての処理
	void Rotate(CPlayer *pPlayer);			// 回転処理

	D3DXVECTOR3 m_rot;						// 向き
	float m_fObjectiveRot;					// 目的の向き
	float m_fNumRot;						// 向きを変える量
	float m_fSpeed;							// 移動量に加える速さ
	bool m_bRotate;							// 回転しているかどうか
	//bool m_bJump;							// ジャンプしているかどうか
	bool m_bAttack;							// 攻撃しているかどうか
	bool m_bDamage;							// ダメージを受けたかどうか
	bool m_bStan;							// スタン中かどうか
	bool m_bSliding;						// スライディング(回避)しているかどうか
	bool m_bDefeat;;						// 敗北したかどうか
	int m_nSlidingCount;					// スライディング(回避)中のカウント
	int m_nSlidingCoolTime;					// スライディング(回避)のクールタイム
	int m_nAttackCount;						// 攻撃中のカウント
	int m_nAttackCoolTime;					// 攻撃のクールタイム
	int m_nStanCount;						// スタン中のカウント
	CCollisionSphere *m_pCollision;			// 球体コリジョンのポインタ
};
#endif	//_CONTROL_PLAYER_H_