//=============================================================================
//
// É{ÉÄé¸ï”ÇÃäÎåØãÊàÊ [danger.h]
// Author : éOè„çqê¢
//
//=============================================================================
#ifndef _DANGER_H_
#define _DANGER_H_

#include "main.h"
#include "plane.h"

class CDanger : public CPlane
{
public:
	CDanger(PRIORITY Priority);
	~CDanger();
	HRESULT Init(D3DXVECTOR3 size, D3DXVECTOR3 pos);
	void Uninit();
	void Update();
	void Draw();
	void Move(float fHeight);
	void MoveY(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	static CDanger *Create(D3DXVECTOR3 size, D3DXVECTOR3 pos);

private:
	float m_fPosY;
	D3DXVECTOR3 m_size;
};

#endif