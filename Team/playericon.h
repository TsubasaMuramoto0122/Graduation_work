//*****************************************************************************
// プレイヤーアイコン処理(playericon.h)
// Author : 三上航世
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
	bool m_bDamage;		//ダメージ食らったか
	int m_nDamageTime;	//ダメージ食らってからの時間
	float m_fPlus;		//振動する際のずれ
};
#endif