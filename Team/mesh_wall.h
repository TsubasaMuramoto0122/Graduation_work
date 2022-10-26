//=============================================================================
// メッシュ(ウォ―ル)処理 [mesh_wall.h]
// Author : Kusakari Kakeru
//=============================================================================
#ifndef _MESH_WALL_H_
#define _MESH_WALL_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene3D.h"

//*****************************************************************************
//クラスの定義
//*****************************************************************************
class CMeshWall : public CScene3D
{
public:
	CMeshWall(PRIORITY nPriority = PRIORITY_OBJECT);						// コンストラクタ
	~CMeshWall();															// デストラクタ
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);						// 初期化処理
	void Uninit(void);														// 終了処理
	void Update(void);														// 更新処理
	void Draw(void);														// 描画処理
	static CMeshWall *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,
		D3DXVECTOR3 rot, int nRow, int nLine, int nTex);					// 生成処理
	OBJTYPE GetObjType() { return OBJECTTYPE_WALL; }						// オブジェクトの種類
	D3DXVECTOR3 GetSize() { return m_size; }								// サイズ取得処理
	void SetColor(D3DXCOLOR col);											// カラー設定処理
	static D3DXVECTOR3 Collision(CScene *pScene);							// 当たり判定

private:
	LPDIRECT3DTEXTURE9 m_pTexture;											// テクスチャのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;										// 頂点バッファのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;										// インデックスバッファのポインタ
	D3DXVECTOR3 m_pos;														// 位置
	D3DXVECTOR3	m_size;														// サイズ
	D3DXVECTOR3 m_rot;														// 向き
	D3DXMATRIX m_mtxWorld;													// ワールドマトリックス
	int m_nRow;																// 横の分割数
	int m_nLine;															// 縦の分割数
};

#endif // _MESH_FIELD_H_