//=============================================================================
//
// ç¨óêîöíeèàóù [confusionbomb.h]
// Author : éOè„çqê¢
//
//=============================================================================
#ifndef _CONFUSIONBOMB_H_
#define _CONFUSIONBOMB_H_

#include "main.h"
#include "bomb.h"

class CConfusionBomb : public CBomb
{
public:
	CConfusionBomb(PRIORITY Priority);
	~CConfusionBomb();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Uninit();
	void Update();
	void Draw();

	static CConfusionBomb *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
private:

};
#endif