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

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define MAX_PLAYER_MODEL	(1)		// モデルの最大数
#define PLAYER_BEGIN_LIFE	(5)		// 初期ライフ
#define INVINCIBLE_TIME		(120)	// 無敵時間

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CModel;
//class CMotionPlayer;
class CControl;
class CCollisionSphere;

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
		PLAYER_TYPE_MAX
	} PLAYER_TYPE;

	// プレイヤーの状態
	typedef enum
	{
		PLAYER_STATE_NORMAL = 0,	// 通常
		PLAYER_STATE_BLOWAWAY,		// 吹っ飛び
		PLAYER_STATE_MAX
	} PLAYER_STATE;

	CPlayer(PRIORITY Priority = PRIORITY_CHARA);				// コンストラクタ
	~CPlayer();													// デストラクタ
	HRESULT Init(D3DXVECTOR3 pos);								// 初期化処理
	void Uninit(void);											// 終了処理
	void Update(void);											// 更新処理
	void Draw(void);											// 描画処理
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,
		PLAYER_TYPE type);										// 生成処理
	OBJTYPE GetObjType() { return OBJECTTYPE_PLAYER; }			// オブジェクトの種類
	void SetPosOld(D3DXVECTOR3 pos) { m_posOld = pos; }			// 1フレーム前の位置設定処理
	D3DXVECTOR3 GetPosOld() { return m_posOld; }				// 1フレーム前の位置取得処理
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }				// 向き設定処理
	D3DXVECTOR3 GetRot(void) { return m_rot; }					// 向き取得処理
	float GetRadius(void) { return m_size.x / 2; }				// 半径取得処理
	D3DXVECTOR3 GetMove() { return m_move; }					// 移動量取得処理
	void SetLand(bool bLand) { m_bLand = bLand; }				// 着地設定処理
	bool GetLand(void) { return m_bLand; }						// 着地取得処理
	void SetState(PLAYER_STATE state) { m_state = state; }		// 状態設定処理
	PLAYER_STATE GetState(void) { return m_state; }				// 状態取得処理
	PLAYER_TYPE GetType(void) { return m_type; }				// 種類取得処理
	void SetModelPos(int nCntModel, D3DXVECTOR3 pos);			// モデル毎の位置設定処理
	D3DXVECTOR3 GetModelPos(int nCntModel);						// モデル毎の位置取得処理
	void SetModelRot(int nCntModel, D3DXVECTOR3 rot);			// モデル毎の向き設定処理
	D3DXVECTOR3 GetModelRot(int nCntModel);						// モデル毎の向き取得処理

																//CMotionPlayer *GetMotionPlayer(void);						// プレイヤーのモーション取得処理
																//CModel *GetModel(int nCntModel);							// プレイヤーのモデル取得処理

private:
	void ModelCreate(PLAYER_TYPE type);							// モデル生成処理
	void Move(void);											// 移動処理
	void Push(CPlayer *pPlayer);								// コリジョンを使った押出処理
	void TouchCollision(void);									// 他のコリジョンと接触した時の処理
	void Invincible(void);										// 無敵時の処理

	D3DXVECTOR3 m_pos;											// 位置
	D3DXVECTOR3 m_posOld;										// 1フレーム前の位置
	D3DXVECTOR3 m_move;											// 移動量
	D3DXVECTOR3 m_size;											// サイズ
	D3DXVECTOR3 m_rot;											// 向き
	D3DXMATRIX m_mtxWorld;										// ワールドマトリックス

	CModel *m_apModel[MAX_PLAYER_MODEL];						// モデルのポインタ
	CModel *m_pParent;											// 親モデルへのポインタ
																//CMotionPlayer *m_pMotionPlayer;							// モーションのポインタ
	CControl *m_pControl;										// コントロールのポインタ
	CCollisionSphere *m_pCollision;								// 球体コリジョンのポインタ
	PLAYER_STATE m_state;										// 状態
	PLAYER_TYPE m_type;											// 種類
	bool m_bLand;												// 着地しているかどうか
	bool m_bInvincible;											// 無敵状態かどうか
	bool m_bDraw;												// 描画させるかどうか
	int m_nLife;												// プレイヤーのライフ
	int m_nInvincibleTime;										// 無敵時間
};

#endif // _PLAYER_H_