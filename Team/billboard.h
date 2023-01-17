//=============================================================================
// ビルボード処理 [Billboard.h]
// Author : 三上航世
//=============================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"
#include "scene3d.h"

class CBillboard : public CScene3D
{
public:
	CBillboard(PRIORITY nPriority);
	~CBillboard();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 Size, int nTex, D3DXCOLOR col, int nLife);	//初期化

	void Uninit();	//終了
	void Update();	//更新
	void Draw();	//描画
	void ZTexDraw();

	static CBillboard *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 Size, int nTex, D3DXCOLOR col, int nLife);

private:
	LPDIRECT3DTEXTURE9 m_pTexture;		// テクスチャのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファのポインタ
	D3DXVECTOR3 m_pos;					// 位置
	D3DXVECTOR3 m_move;
	int m_nLife;						//寿命
};
#endif