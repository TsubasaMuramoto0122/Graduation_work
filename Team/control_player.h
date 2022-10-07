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
// 前方宣言
//*****************************************************************************
class CScene;
class CPlayer;

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PLAYER_GRAVITY				(0.6f)	// 重力の大きさ
#define PLAYER_MAX_GRAVITY			(15.0f)	// 重力の最大値
#define PLAYER_MOVE_SPEED			(1.8f)	// 移動量の基準値
#define PLAYER_INTERIA_SUBTRACTION	(0.86f)	// 地上での慣性の減算値
#define PLAYER_MOVE_STOP_COUNT		(0.02f)	// プレイヤーの移動量を0にする時の移動量の値
#define PLAYER_DODGE				(3.5f)	// 回避の移動量の基準値
#define PLAYER_DODGE_TIME			(20)	// 回避時間
#define PLAYER_DODGE_WAITTIME		(5)		// 回避後の硬直時間
#define PLAYER_DODGE_COOLTIME		(120)	// 回避後、再び回避を使えるまでの時間
#define PLAYER_ATTACK_TIME			(15)	// 攻撃時間
#define PLAYER_ATTACK_WAITTIME		(10)	// 攻撃後の硬直時間
#define PLAYER_ATTACK_COOLTIME		(120)	// 攻撃後、再び回避を使えるまでの時間

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
	void Move(void);						// 移動処理
	void Dodge(CPlayer *pPlayer);			// 回避処理
	void Attack(CPlayer *pPlayer);			// 攻撃処理
	void MoveInteria(void);					// 移動の慣性についての処理
	void Rotate(CPlayer *pPlayer);			// 回転処理

	D3DXVECTOR3 m_rot;						// 向き
	D3DXVECTOR3 m_moveOld;					// 1フレーム前の移動量
	float m_fObjectiveRot;					// 目的の向き
	float m_fNumRot;						// 向きを変える量
	float m_fSpeed;							// 移動量に加える速さ
	bool m_bRotate;							// 回転しているかどうか
	bool m_bDodge;							// 回避しているかどうか
	bool m_bAttack;							// 攻撃しているかどうか
	int m_nDodgeCount;						// 回避中のカウント
	int m_nDodgeCoolTime;					// 回避のクールタイム
	int m_nAttackCount;						// 攻撃中のカウント
	int m_nAttackCoolTime;					// 攻撃のクールタイム
};
#endif	//_CONTROL_PLAYER_H_