//*****************************************************************************
// �v���C���[�A�C�R������(playericon.h)
// Author : �O��q��
//*****************************************************************************

#ifndef _PLAYERICON_H_
#define _PLAYERICON_H_

#include "ui.h"


class CPlayerIcon :public CUI
{
public:
	CPlayerIcon(PRIORITY Priority);
	~CPlayerIcon();

	HRESULT Init(D3DXVECTOR2 pos, D3DXVECTOR2 size, int nType, D3DXCOLOR col);
	void Uninit();
	void Update();
	void Draw();

	void SetDamage(bool bDamage);

	OBJTYPE GetObjType() { return OBJECTTYPE_UI; }

	static CPlayerIcon *Create(D3DXVECTOR2 pos, D3DXVECTOR2 size, int nType, D3DXCOLOR col);
private:
	bool m_bDamage;		//�_���[�W�H�������
	int m_nDamageTime;	//�_���[�W�H����Ă���̎���
	float m_fPlus;		//�U������ۂ̂���
};
#endif