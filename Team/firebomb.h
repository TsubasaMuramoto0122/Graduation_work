//=============================================================================
//
// âäîöíeèàóù [firebomb.h]
// Author : éOè„çqê¢
//
//=============================================================================
#ifndef _FIREBOMB_H_
#define _FIREBOMB_H_

#include "main.h"
#include "bomb.h"

class CCollisionSphere;

class CFireBomb : public CBomb
{
public:
	CFireBomb(PRIORITY Priority);
	~CFireBomb();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, float fFriction);
	void Uninit();
	void Update();
	void Draw();
	void ZTexDraw();

	static CFireBomb *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, float fFriction);
private:
	void Explosion(D3DXVECTOR3 pos);
};
#endif