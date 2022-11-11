//=============================================================================
//
// シーン処理 [scene3d.h]
// Author : 三上航世
//
//=============================================================================
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

#include "main.h"
#include "scene.h"

struct VERTEX_3D
{
	D3DXVECTOR3 pos; //頂点座標
	D3DXVECTOR3 nor; //法線ベクトル
	D3DCOLOR col;    //頂点カラー
	D3DXVECTOR2 tex; //テクスチャ座標
};

//マクロ
#define MAX_3DTEXTURE (32)		//最大で使える3D用の画像数

class CScene3D : public CScene
{
public:
	CScene3D(PRIORITY Priority);
	~CScene3D();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit();
	void Update();
	void Draw();
	OBJTYPE GetObjType() { return OBJECTTYPE_NONE; }

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	D3DXVECTOR3 GetPos() { return m_pos; }

	void SetPosOld(D3DXVECTOR3 pos) { m_posOld = pos; }
	D3DXVECTOR3 GetPosOld() { return m_posOld; }

	float GetRadius() { return 0.0f; }

	D3DXVECTOR3 GetRot() { return m_rot; }
	void SetRot(D3DXVECTOR3 rot);

	void SetMatrix(D3DXMATRIX mtx) { mtx = m_mtxWorld; }

	static void CreateTextureFiled();
	static LPDIRECT3DTEXTURE9 *GetTexture(int nTex) { return &m_pTexture[nTex]; }

	//テクスチャ破棄
	static void UninitTexture();

	static CScene3D *Create(const D3DXVECTOR3& pos);

private:
	D3DXVECTOR3 m_rot; //向き
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_posOld;
	D3DXMATRIX m_mtxWorld; //ワールドマトリックス
	static int m_nMaxTex;					   //使用する最大テクスチャ

protected:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_3DTEXTURE];			//テクスチャーポインタ
};
#endif
