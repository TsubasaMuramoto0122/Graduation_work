//=============================================================================
//
// �������e���� [confusionbomb.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _CONFUSIONBOMB_H_
#define _CONFUSIONBOMB_H_

#include "main.h"
#include "bomb.h"

class CCollisionSphere;

class CConfusionBomb : public CBomb
{
public:
	CConfusionBomb(PRIORITY Priority);
	~CConfusionBomb();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, float fFriction, float fMaxSpeed, float fGravity);
	void Uninit();
	void Update();
	void Draw();
	void ZTexDraw();

	static CConfusionBomb *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, float fFriction, float fMaxSpeed, float fGravity);
private:
	void Explosion(D3DXVECTOR3 pos);
};
#endif