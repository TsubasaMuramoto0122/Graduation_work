//=============================================================================
//
// ì≈îöíeèàóù [poisonbomb.h]
// Author : éOè„çqê¢
//
//=============================================================================
#ifndef _POISONBOMB_H_
#define _POISONBOMB_H_

#include "main.h"
#include "bomb.h"

class CCollisionSphere;

class CPoisonBomb : public CBomb
{
public:
	CPoisonBomb(PRIORITY Priority);
	~CPoisonBomb();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, float fFriction);
	void Uninit();
	void Update();
	void Draw();
	void ZTexDraw();

	static CPoisonBomb *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, float fFriction);
private:
	void Explosion(D3DXVECTOR3 pos);
};
#endif