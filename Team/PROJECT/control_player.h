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
#define PLAYER_MOVE_SPEED			(0.9f)	// 移動量の基準値
#define PLAYER_INTERIA_SUBTRACTION	(0.86f)	// 地上での慣性の減算値
#define PLAYER_MOVE_STOP_COUNT		(0.02f)	// プレイヤーの移動量を0にする時の移動量の値

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
	void Jump(CPlayer *pPlayer);			// ジャンプ処理
	void Dodge(void);						// 回避処理
	void MoveInteria(CPlayer *pPlayer);		// 移動の慣性についての処理
	void Rotate(CPlayer *pPlayer);			// 回転処理

	D3DXVECTOR3 m_rot;						// 向き
	D3DXVECTOR3 m_moveOld;					// 1フレーム前の移動量
	float m_fObjectiveRot;					// 目的の向き
	float m_fNumRot;						// 向きを変える量
	float m_fSpeed;							// 移動量に加える速さ
	bool m_bDodge;							// 回避しているかどうか
	bool m_bRotate;							// 回転しているかどうか
};

#endif	//_CONTROL_PLAYER_H_