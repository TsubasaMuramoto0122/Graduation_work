//=============================================================================
//
// ñCë‰èàóù [battery.h]
// Author : éOè„çqê¢
//
//=============================================================================
#ifndef _BATTERY_H_
#define _BATTERY_H_

#include "main.h"
#include "object.h"

class CBattery : public CObject
{
public:
	CBattery(PRIORITY nPriority);
	~CBattery();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, int nTime);
	void Uninit();
	void Update();
	void Draw();

	static CBattery *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, int nTime);

private:
	void RandomBomb(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	int m_nTime;
	int m_nMaxTime;
};

#endif