//=============================================================================
//
// ???ʔ??e???? [normalbomb.h]
// Author : ?O???q??
//
//=============================================================================
#ifndef _NORMALBOMB_H_
#define _NORMALBOMB_H_

#include "main.h"
#include "bomb.h"
#include "scene3d.h"

class CCollisionSphere;

class CNormalBomb : public CBomb
{
public:
	CNormalBomb(PRIORITY Priority);
	~CNormalBomb();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, float fFriction);
	void Uninit();
	void Update();
	void Draw();
	void ZTexDraw();

	static CNormalBomb *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, float fFriction);
private:
	void Explosion(D3DXVECTOR3 pos);
};
#endif