//=============================================================================
//
// ïÅí îöíeèàóù [normalbomb.h]
// Author : éOè„çqê¢
//
//=============================================================================
#ifndef _NORMALBOMB_H_
#define _NORMALBOMB_H_

#include "main.h"
#include "bomb.h"
#include "scene3d.h"

class CNormalBomb : public CBomb
{
public:
	CNormalBomb(PRIORITY Priority);
	~CNormalBomb();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Uninit();
	void Update();
	void Draw();

	static CNormalBomb *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
private:

};
#endif