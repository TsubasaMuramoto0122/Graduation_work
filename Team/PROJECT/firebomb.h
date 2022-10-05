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

class CFireBomb : public CBomb
{
public:
	CFireBomb(PRIORITY Priority);
	~CFireBomb();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Uninit();
	void Update();
	void Draw();

	static CFireBomb *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
private:

};
#endif