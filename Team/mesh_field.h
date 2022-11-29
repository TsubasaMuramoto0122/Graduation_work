//=============================================================================
// メッシュ(地面)処理 [mesh_field.h]
// Author : Kusakari Kakeru
//=============================================================================
#ifndef _MESH_FIELD_H_
#define _MESH_FIELD_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene3D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_TEXTURE_MESHFILED (16)

//*****************************************************************************
//クラスの定義
//*****************************************************************************
class CMeshField : public CScene3D
{
public:
	CMeshField(PRIORITY Priority = PRIORITY_PLANE);					// コンストラクタ
	~CMeshField();														// デストラクタ
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);					// 初期化処理
	void Uninit(void);													// 終了処理
	void Update(void);													// 更新処理
	void Draw(void);													// 描画処理
	void ZTexDraw();
	static CMeshField *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,
		D3DXVECTOR3 rot, int nRow, int nLine, int nTex);				// 生成処理

	OBJTYPE GetObjType() { return OBJECTTYPE_FIELD; }					// オブジェクトの種類
	float GetRadius() { return m_size.x / 2; }							// 半径取得処理
	void SetColor(D3DXCOLOR col);										// カラー設定処理
	static bool Collision(CScene *pScene);								// 当たり判定処理

private:
	LPDIRECT3DTEXTURE9 m_pTexture;										// テクスチャのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;									// 頂点バッファのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;									// インデックスバッファのポインタ
	D3DXVECTOR3 m_pos;													// 位置
	D3DXVECTOR3	m_size;													// サイズ
	D3DXVECTOR3 m_rot;													// 向き
	D3DXMATRIX m_mtxWorld;												// ワールドマトリックス
	int m_nRow;															// 横の分割数
	int m_nLine;														// 縦の分割数
	//int m_nTexType;													// 貼るテクスチャ
	//static int m_nMaxTex;												// 使用する最大テクスチャ
};

#endif // _MESH_FIELD_H_