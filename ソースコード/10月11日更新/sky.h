//=============================================================================
//
// 背景処理 [sky.h]
// Author : 三上航世
//
//=============================================================================
#ifndef _SKY_H_
#define _SKY_H_

#include "main.h"
#include "scene.h"

class CSky : public CScene
{
public:
	CSky(PRIORITY Priority);
	~CSky();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	OBJTYPE GetObjType() { return OBJECTTYPE_NONE; }
	void SetPos(D3DXVECTOR3 pos) { pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetPos() { return m_pos; }
	D3DXVECTOR3 GetRot() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetMove() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	void SetPosOld(D3DXVECTOR3 pos) { pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetPosOld() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	float GetRadius() { return 0.0f; }
	float GetHeight() { return 0.0f; }
	COLLISION GetCollision() { return COLLISION_SPHERE; }
	D3DXVECTOR3 GetVtxMax() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetVtxMin() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	bool GetRotX() { return false; }
	D3DXMATRIX GetMatrix(int) { return m_mtxWorld; }
	D3DXMATRIX GetMatrix() { return m_mtxWorld; }

	void SetTexture(LPDIRECT3DTEXTURE9 *Texture);
	void SetScroll(float fScroll);
	static CSky *Create(D3DXVECTOR3 pos, float fScroll, LPDIRECT3DTEXTURE9 *Texture);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL; //頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff = NULL;
	D3DXMATRIX m_mtxWorld; //ワールドマトリックス
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;

	float m_fScroll;
};

#endif