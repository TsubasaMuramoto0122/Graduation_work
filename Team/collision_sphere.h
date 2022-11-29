//=============================================================================
// 球体コリジョン処理 [collision_sphere.h]
// Author : Kusakari Kakaeru
//=============================================================================
#ifndef _SPHERE_COLLISION_H_
#define _SPHERE_COLLISION_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene3D.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CModel;

//*****************************************************************************
//クラスの定義
//*****************************************************************************
class CCollisionSphere : public CScene3D
{
public:
	// どの当たり判定か
	typedef enum
	{
		COLLISION_S_TYPE_PLAYER = 0,	// プレイヤー
		COLLISION_S_TYPE_ATTACK,		// プレイヤーの攻撃
		COLLISION_S_TYPE_EXPLOSION,		// 爆発など、ダメージ判定
		COLLISION_S_TYPE_ICE,			// アイス
		COLLISION_S_TYPE_POISON,		// 毒
		COLLISION_S_TYPE_POISON_FIELD,	// 毒(フィールド)
		COLLISION_S_TYPE_CONFUSION,		// 混乱
		COLLISION_S_TYPE_NONE,			// なし
		COLLISION_S_TYPE_MAX
	} COLLISION_S_TYPE;

	CCollisionSphere(PRIORITY Priority = PRIORITY_COLLISION);				// コンストラクタ
	~CCollisionSphere();													// デストラクタ
	HRESULT Init(D3DXVECTOR3 pos, float fSize);								// 初期化処理
	void Uninit(void);														// 終了処理
	void Update(void);														// 更新処理
	void Draw(void);														// 描画処理
	void ZTexDraw();
	static CCollisionSphere *Create(D3DXVECTOR3 pos,
		float fSize, int nVertical, int nSide,
		COLLISION_S_TYPE type, float fTime, float fPlayerRot);				// 生成処理

	OBJTYPE GetObjType() { return OBJECTTYPE_COLLISION; }					// オブジェクトの種類
	void SetPosCollision(D3DXVECTOR3 pos) { m_pos = pos; }					// 位置設定処理
	D3DXVECTOR3 GetPos() { return m_pos; }									// 位置取得
	COLLISION_S_TYPE GetCollisionType(void) { return m_collisionType; }		// コリジョンの種類の取得処理
	void SetParent(CModel *pModel) { m_pParent = pModel; }					// 親モデル設定処理
	float GetRadius(void) { return m_fSize / 2; }							// 半径取得処理
	void SetNumPlayer(int nNum) { m_nNumPlayer = nNum; }					// 番号設定処理
	int GetNumPlayer(void) { return m_nNumPlayer; }							// 番号取得処理
	float GetObjectiveRot(void) { return m_fObjectiveRot; }					// 目的の向き取得処理
	D3DXVECTOR3 GetMtxPos(void);											// ワールドマトリックス座標取得処理
	void Collision(CScene *pScene);											// 衝突処理
	void SetCollisionType(COLLISION_S_TYPE type);							// コリジョンの種類設定処理
	bool GetTouchCollision(COLLISION_S_TYPE type);							// 指定の種類に当たったかどうか
	float GetTime() { return m_fTime; }
	//void SetPlayerRot(float fRot) { m_fPlayerRot = fRot; }
	float GetPlayerRot() { return m_fPlayerRot; }
	void SetColor(D3DXCOLOR col) { m_col = col; }							// カラー設定処理

	static CCollisionSphere *SearchCollision(D3DXVECTOR3 pos);

#ifdef _DEBUG
	static void SetVisual(bool bVisual);									// 判定の可視化設定処理
#endif

private:
#ifdef _DEBUG
	void VisualOn(bool bVisual);											// 判定の可視化処理
#endif
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;										// 頂点バッファのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;										// インデックスバッファへのポインタ
	D3DXVECTOR3 m_pos;														// 位置
	D3DXVECTOR3 m_rot;														// 向き
	D3DXMATRIX m_mtxWorld;													// ワールドマトリックス
	CModel *m_pParent;														// 親のモデル
	D3DXCOLOR m_col;														// カラー
	COLLISION_S_TYPE m_collisionType;										// 当たり判定の種類
	int m_nVertical;														// 縦の分割数
	int m_nSide;															// 横の分割数
	int m_nNumPlayer;														// プレイヤーの番号
	float m_fSize;															// サイズ
	float m_fTime;															// 持続時間
	float m_fDamage;														// ダメージの値
	float m_fObjectiveRot;													// 目的の向き
	static bool m_bMngVisual;												// 判定を可視化するかどうか
	bool m_bContact;														// 一度でも当たったかどうか
	bool m_bTouchAttack;													// 攻撃に当たっているかどうか
	bool m_bTouchExplosion;													// 爆発に当たっているかどうか
	bool m_bTouchIce;														// 氷の爆発に当たっているかどうか
	bool m_bTouchPoison;													// 毒の爆発に当たっているかどうか
	bool m_bTouchPoisonField;												// 毒のフィールドに当たっているかどうか
	bool m_bTouchConsusion;													// 混乱の爆発に当たっているかどうか

	float m_fPlayerRot;														// 攻撃した際の攻撃の向き(これがあるとプレイヤーが向いてる方向にプレイヤーを吹っ飛ばす)
};

#endif // _SPHERE_COLLISION_H_