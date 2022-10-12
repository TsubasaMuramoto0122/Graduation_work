//=============================================================================
//
// 爆発範囲 [danger.h]
// Author : 三上航世
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
	void Move(D3DXVECTOR3 pos);

	static CDanger *Create(D3DXVECTOR3 size, D3DXVECTOR3 pos);

private:
	float m_fPosY;		//真下の地面のY位置
	D3DXVECTOR3 m_size;	//大きさ
};

#endif