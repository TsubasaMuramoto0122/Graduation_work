//=============================================================================
// コントロール処理 [control.h]
// Author : Kusakari Kakeru
//=============================================================================
#ifndef _CONTROL_H_
#define _CONTROL_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PLAYER_GRAVITY				(0.5f)	// 重力の大きさ
#define PLAYER_GRAVITY_DAMAGE		(1.1f)	// 被ダメージ時の重力の大きさ
#define PLAYER_GRAVITY_DEFEAT		(0.2f)	// 敗北時の重力の大きさ
#define PLAYER_MOVE_SPEED			(0.4f)	// 移動量の基準値
#define PLAYER_INTERIA_SUBTRACTION	(0.86f)	// 地上での慣性の減算値
#define PLAYER_MOVE_STOP_COUNT		(0.02f)	// プレイヤーの移動量を0にする時の移動量の値
#define PLAYER_MAX_GRAVITY			(26.0f)	// 重力の最大値
#define PLAYER_ATTACK_TIME			(15)	// 攻撃時間
#define PLAYER_ATTACK_WAITTIME		(13)	// 攻撃後の硬直時間
#define PLAYER_ATTACK_COOLTIME		(10)	// 攻撃後、再び攻撃できるまでの時間
//#define PLAYER_SLIDING_MOVE		(1.2f)	// スライディング(回避)の移動量の基準値
#define PLAYER_SLIDING_TIME			(30)	// スライディング(回避)時間
#define PLAYER_SLIDING_WAITTIME		(14)	// スライディング(回避)後の硬直時間
#define PLAYER_SLIDING_COOLTIME		(30)	// スライディング(回避)後、再び回避を使えるまでの時間
//#define PLAYER_JUMP				(8.0f)	// ジャンプ力
#define PLAYER_KNOCKBACK			(7.0f)	// ノックバックの大きさ
//#define PLAYER_KNOCKBACK_TIME		(4)		// ノックバックの時間
#define PLAYER_KNOCKBACK_STAN		(74)	// ノックバック後のスタンの時間
#define PLAYER_GETUP_TIME			(20)	// スタン中、起き上がる時間
#define PLAYER_DEFEAT_KNOCKBACK		(19.0f)	// 敗北時のノックバックの大きさ
#define MAX_MOVE					(3.6f)	// 限界の移動量
#define MAX_SLIDE					(6.0f)	// 限界のスライド量
#define PLAYER_KNOCKBACK_JUMP		(8.0f)	// ノックバックのジャンプ量
#define PLAYER_DEFEATKNOCKBACK_JUMP	(12.0f)	// 敗北時のノックバックのジャンプ量

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CScene;

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CControl
{
public:
	CControl();									// コンストラクタ
	virtual ~CControl();						// デストラクタ
	virtual HRESULT Init(void) = 0;				// 初期化処理
	virtual void Uninit(void) = 0;				// 終了処理
	virtual void Update(CScene *pScene) = 0;	// 更新処理
	D3DXVECTOR3 GetMove(void);					// 移動量の取得処理

protected:
	D3DXVECTOR3 m_move;							// 移動量
};

#endif	// _CONTROL_H_