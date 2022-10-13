//=============================================================================
//
// �����͈� [danger.h]
// Author : �O��q��
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
	float m_fPosY;		//�^���̒n�ʂ�Y�ʒu
	D3DXVECTOR3 m_size;	//�傫��
};

#endif