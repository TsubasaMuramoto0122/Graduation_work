//=============================================================================
// プレイヤー処理 [player.h]
// Authore : kusakari Kakeru
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "scene3d.h"
#include "model.h"

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define MAX_PLAYER_MODEL	(14)		// モデルの最大数

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CModel;
class CMotion;
class CControl;
class CCollisionSphere;
class CLifeUI;

//*****************************************************************************
//クラスの定義
//*****************************************************************************
class CPlayer : public CScene3D
{
public:
	// プレイヤーの種類
	typedef enum
	{
		PLAYER_TYPE_1P = 0,
		PLAYER_TYPE_2P,
		PLAYER_TYPE_3P,
		PLAYER_TYPE_4P,
		PLAYER_TYPE_MAX
	} PLAYER_TYPE;

	// プレイヤーの状態
	typedef enum
	{
		PLAYER_STATE_NORMAL = 0,	// 通常
		PLAYER_STATE_BLOWAWAY,		// 吹っ飛び
		PLAYER_STATE_DEFEAT,		// 負け
		PLAYER_STATE_MAX
	} PLAYER_STATE;

	// プレイヤーの状態異常
	typedef enum
	{
		PLAYER_BAD_STATE_NONE = 0,	// なし
		PLAYER_BAD_STATE_ICE,		// 氷
		PLAYER_BAD_STATE_POISON,	// 毒
		PLAYER_BAD_STATE_CONFUSION,	// 混乱
		PLAYER_BAD_STATE_MAX
	} PLAYER_BAD_STATE;

	CPlayer(PRIORITY Priority = PRIORITY_CHARA);							// コンストラクタ
	~CPlayer();																// デストラクタ
	HRESULT Init(D3DXVECTOR3 pos);											// 初期化処理
	void Uninit(void);														// 終了処理
	void Update(void);														// 更新処理
	void Draw(void);														// 描画処理
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,
		PLAYER_TYPE type, bool bCPU);										// 生成処理

	OBJTYPE GetObjType() { return OBJECTTYPE_PLAYER; }						// オブジェクトの種類
	void SetPosOld(D3DXVECTOR3 pos) { m_posOld = pos; }						// 1フレーム前の位置設定処理
	D3DXVECTOR3 GetPosOld() { return m_posOld; }							// 1フレーム前の位置取得処理
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }							// 向き設定処理
	D3DXVECTOR3 GetRot(void) { return m_rot; }								// 向き取得処理
	float GetRadius(void) { return m_size.x / 2; }							// 半径取得処理
	D3DXVECTOR3 GetMove() { return m_move; }								// 移動量取得処理
	void SetLand(bool bLand) { m_bLand = bLand; }							// 着地設定処理
	bool GetLand(void) { return m_bLand; }									// 着地取得処理
	void SetInvSliding(bool bInvincible) { m_bInvSliding = bInvincible; }	// スライディング(回避)による無敵設定処理
	bool GetInvSliding(void) { return m_bInvSliding; }						// スライディング(回避)による無敵取得処理
	void SetState(PLAYER_STATE state) { m_state = state; }					// 状態設定処理
	PLAYER_STATE GetState(void) { return m_state; }							// 状態取得処理
	void SetBadState(PLAYER_BAD_STATE state) { m_badState = state; }		// 状態異常取得処理
	PLAYER_BAD_STATE GetBadState(void) { return m_badState; }				// 状態異常取得処理
	PLAYER_TYPE GetType(void) { return m_type; }							// 種類取得処理
	void SetModelPos(int nCntModel, D3DXVECTOR3 pos) { m_apModel[nCntModel]->SetPos(pos); }		// モデル毎の位置設定処理
	D3DXVECTOR3 GetModelPos(int nCntModel) { return m_apModel[nCntModel]->GetPos(); }			// モデル毎の位置取得処理
	void SetModelRot(int nCntModel, D3DXVECTOR3 rot) { m_apModel[nCntModel]->SetRot(rot); }		// モデル毎の向き設定処理
	D3DXVECTOR3 GetModelRot(int nCntModel) { return m_apModel[nCntModel]->GetRot(); }			// モデル毎の向き取得処理
	bool GetHitWall() { return m_bWall; }

	static CPlayer *CPlayer::SearchPlayer(CScene *pScene);
	static void SetSurviveTime(int nTime, int nNum) { m_nSurviveTime[nNum] = nTime; }	// 生存時間取得処理
	static int GetSurviveTime(int nNum) { return m_nSurviveTime[nNum]; }				// 生存時間取得処理
	CMotion *GetMotion(void) { return m_pMotion; }										// モーション取得処理
	//CModel *GetModel(int nCntModel) { return m_apModel[nCntModel]; }					// プレイヤーのモデル取得処理

private:
	void ModelCreate(PLAYER_TYPE type);					// モデル生成処理
	void Move(void);									// 移動処理
	void Push(CPlayer *pPlayer);						// コリジョンを使った押出処理
	void TouchCollision(void);							// 他のコリジョンと接触した時の処理
	void Invincible(void);								// 無敵時の処理
	void BadState(PLAYER_BAD_STATE state);				// 状態異常の処理

	D3DXVECTOR3 m_pos;									// 位置
	D3DXVECTOR3 m_posOld;								// 1フレーム前の位置
	D3DXVECTOR3 m_move;									// 移動量
	D3DXVECTOR3 m_size;									// サイズ
	D3DXVECTOR3 m_rot;									// 向き
	D3DXMATRIX m_mtxWorld;								// ワールドマトリックス
	CModel *m_apModel[MAX_PLAYER_MODEL];				// モデルのポインタ
	CModel *m_pParent;									// 親モデルへのポインタ
	CMotion *m_pMotion;									// モーションのポインタ
	CControl *m_pControl;								// コントロールのポインタ
	CCollisionSphere *m_pCollision;						// 球体コリジョンのポインタ
	CLifeUI *m_pLife;									// ライフのポインタ
	PLAYER_STATE m_state;								// 状態
	PLAYER_BAD_STATE m_badState;						// 状態異常
	PLAYER_TYPE m_type;									// 種類
	bool m_bLand;										// 着地しているかどうか
	bool m_bDamage;										// ダメージを受けたかどうか
	bool m_bInvDamage;									// 被ダメージによる無敵かどうか
	bool m_bInvSliding;									// スライディング(回避)による無敵かどうか
	bool m_bDraw;										// 描画させるかどうか
	bool m_bCPU;										// CPUかどうか
	bool m_bWall;										// 壁に当たったか(CPUに必要)
	int m_nLife;										// プレイヤーのライフ
	int m_nInvincibleTime;								// 無敵時間
	int m_nBadStateTime;								// 状態異常の時間
	int m_nPoisonCount;									// 毒状態のカウント
	static int m_nSurviveTime[PLAYER_TYPE_MAX];			// プレイヤーの生存時間
};

#endif // _PLAYER_H_