//=============================================================================
//
// �X���e���� [icebomb.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _ICEBOMB_H_
#define _ICEBOMB_H_

#include "main.h"
#include "bomb.h"
#include "scene3d.h"

class CIceBomb : public CBomb
{
public:
	CIceBomb(PRIORITY Priority);
	~CIceBomb();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move);
	void Uninit();
	void Update();
	void Draw();

	static CIceBomb *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move);
private:
	void Explosion();
};
#endif