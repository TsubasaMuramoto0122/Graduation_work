//=============================================================================
//
// 砲台処理 [battery.h]
// Author : 三上航世
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
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move);
	void Uninit();
	void Update();
	void Draw();

	static CBattery *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move);

private:

};

#endif