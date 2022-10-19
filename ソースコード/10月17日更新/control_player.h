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
#define PLAYER_GRAVITY				(0.5f)	// 重力の大きさ
#define PLAYER_GRAVITY_DAMAGE		(1.1f)	// 被ダメージ時の重力の大きさ
#define PLAYER_GRAVITY_DEFEAT		(0.2f)	// 敗北時の重力の大きさ
#define PLAYER_MAX_GRAVITY			(26.0f)	// 重力の最大値
#define PLAYER_MOVE_SPEED			(0.4f)	// 移動量の基準値
#define PLAYER_INTERIA_SUBTRACTION	(0.86f)	// 地上での慣性の減算値
#define PLAYER_MOVE_STOP_COUNT		(0.02f)	// プレイヤーの移動量を0にする時の移動量の値
#define PLAYER_JUMP					(8.0f)	// ジャンプ力
#define PLAYER_ATTACK_TIME			(15)	// 攻撃時間
#define PLAYER_ATTACK_WAITTIME		(10)	// 攻撃後の硬直時間
#define PLAYER_ATTACK_COOLTIME		(1)		// 攻撃後、再び攻撃できるまでの時間
#define PLAYER_KNOCKBACK			(7.0f)	// ノックバックの大きさ
#define PLAYER_KNOCKBACK_TIME		(7)		// ノックバックの時間
#define PLAYER_KNOCKBACK_JUMP		(6.5f)	// ノックバックのジャンプ量
#define PLAYER_KNOCKBACK_STAN		(6)		// ノックバック後のスタンの時間
#define PLAYER_DEFEAT_KNOCKBACK		(19.0f)	// 敗北時のノックバックの大きさ
#define PLAYER_DEFEATKNOCKBACK_JUMP	(10.0f)	// 敗北時のノックバックのジャンプ量
//#define PLAYER_DODGE				(1.0f)	// 回避の移動量の基準値
//#define PLAYER_DODGE_TIME			(20)	// 回避時間
//#define PLAYER_DODGE_WAITTIME		(5)		// 回避後の硬直時間
//#define PLAYER_DODGE_COOLTIME		(120)	// 回避後、再び回避を使えるまでの時間

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
	void Jump(CPlayer *pPlayer);			// ジャンプ処理
	void Attack(CPlayer *pPlayer);			// 攻撃処理
	void TakeDamage(CPlayer *pPlayer);		// 被ダメージ処理
	void Defeat(CPlayer *pPlayer);			// 敗北処理
											//void Dodge(CPlayer *pPlayer);			// 回避処理
	void MoveInteria(void);					// 移動の慣性についての処理
	void Rotate(CPlayer *pPlayer);			// 回転処理

	D3DXVECTOR3 m_rot;						// 向き
	float m_fObjectiveRot;					// 目的の向き
	float m_fNumRot;						// 向きを変える量
	float m_fSpeed;							// 移動量に加える速さ
	bool m_bRotate;							// 回転しているかどうか
	bool m_bJump;							// ジャンプしているかどうか
	bool m_bAttack;							// 攻撃しているかどうか
	bool m_bDamage;							// ダメージを受けたかどうか
	bool m_bStan;							// スタン中かどうか
											//bool m_bDodge;							// 回避しているかどうか
	int m_nAttackCount;						// 攻撃中のカウント
	int m_nAttackCoolTime;					// 攻撃のクールタイム
	int m_nStanCount;						// スタン中のカウント
											//int m_nDodgeCount;					// 回避中のカウント
											//int m_nDodgeCoolTime;					// 回避のクールタイム
	CCollisionSphere *m_pCollision;			// 球体コリジョンのポインタ
};
#endif	//_CONTROL_PLAYER_H_