//=============================================================================
//
// �e���� [shadow.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"
#include "plane.h"

class CShadow : public CPlane
{
public:
	CShadow(PRIORITY Priority);
	~CShadow();
	HRESULT Init(D3DXVECTOR3 size, D3DXVECTOR3 pos);
	void Uninit();
	void Update();
	void Draw();
	void Move(float fHeight);
	void MoveY(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	OBJTYPE GetObjType() { return OBJECTTYPE_NONE; }

	static CShadow *Create(D3DXVECTOR3 size, D3DXVECTOR3 pos, int nTex);

private:
	float m_fPosY;		//Y�ʒu
	float m_fLength;	//���a
	D3DXVECTOR3 m_size;	//���̑傫��
};

#endif