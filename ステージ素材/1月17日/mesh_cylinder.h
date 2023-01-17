//=============================================================================
// メッシュ(円柱)処理 [mesh_cylinder.h]
// Authore : Kusakari Kakeru
//=============================================================================
#ifndef _MESH_CYLINDER_H_
#define _MESH_CYLINDER_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene3D.h"

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CMeshCylinder : public CScene3D
{
public:
	CMeshCylinder(PRIORITY nPriority = PRIORITY_OBJECT);			// コンストラクタ
	~CMeshCylinder();												// デストラクタ
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);				// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理
	void Draw(void);												// 描画処理
	static CMeshCylinder *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,
		int nVertical, int nSide, bool bOutSide, int nTex);			// 生成処理

	OBJTYPE GetObjType() { return OBJECTTYPE_FIELD; }				// オブジェクトの種類
	float GetRadius() { return m_size.x / 2; }						// 半径取得処理

private:
	LPDIRECT3DTEXTURE9 m_pTexture;									// テクスチャのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;								// 頂点バッファのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;								// インデックスバッファへのポインタ
	D3DXVECTOR3 m_pos;												// 位置
	D3DXVECTOR3	m_size;												// サイズ
	D3DXVECTOR3 m_rot;												// 向き
	D3DXMATRIX m_mtxWorld;											// ワールドマトリックス
	int m_nSide;													// 横の分割数
	int m_nVertical;												// 縦の分割数
	bool m_bOutSide;												// シリンダーの外側に描画するかどうか
};

#endif // _MESH_CYLINDER_H_