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

//*****************************************************************************
//クラスの定義
//*****************************************************************************
class CPlayer : public CScene3D
{
public:
	CPlayer(PRIORITY nPriority = PRIORITY_CHARA);			// コンストラクタ
	~CPlayer();													// デストラクタ
	HRESULT Init(D3DXVECTOR3 pos);								// 初期化処理
	void Uninit(void);											// 終了処理
	void Update(void);											// 更新処理
	void Draw(void);											// 描画処理
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// 生成処理
	OBJTYPE GetObjType() { return OBJECTTYPE_BOMB; }

	D3DXVECTOR3 GetPosOld(void);								// 1フレーム前の位置取得処理
	void SetLand(bool bLand);									// 着地設定処理
	bool GetLand(void);											// 着地取得処理
	void SetModelPos(int nCntModel, D3DXVECTOR3 pos);			// モデル毎の位置設定処理
	D3DXVECTOR3 GetModelPos(int nCntModel);						// モデル毎の位置取得処理
	void SetModelRot(int nCntModel, D3DXVECTOR3 rot);			// モデル毎の向き設定処理
	D3DXVECTOR3 GetModelRot(int nCntModel);						// モデル毎の向き取得処理
																//CMotionPlayer *GetMotionPlayer(void);						// プレイヤーのモーション取得処理
																//CModel *GetModel(int nCntModel);							// プレイヤーのモデル取得処理

private:
	void ModelCreate(void);										// モデル生成処理
	void Move(void);											// 移動処理

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
	bool m_bLand;												// 着地しているかどうか
};

#endif // _PLAYER_H_