//=============================================================================
//
// �{������ [bomb.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _BOMB_H_
#define _BOMB_H_

#include "main.h"
#include "scene3d.h"
#include "model.h"

class CDanger;

class CBomb : public CScene3D
{
public:
	//���e�̎��
	typedef enum
	{
		BOMB_NORMAL = 0,
		BOMB_ICE,
		BOMB_FIRE,
		BOMB_POISON,
		BOMB_CONFUSION,
		MAX_BOMB
	} BOMBTYPE;

	CBomb(PRIORITY Priority);
	~CBomb();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, BOMBTYPE BombType);
	void Uninit();
	void Update();
	void Draw();
	OBJTYPE GetObjType() { return OBJECTTYPE_BOMB; }

	//static CBomb *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *aFileName);
	static CModel *m_paModel[MAX_BOMB]; //���f���i�p�[�c�j
	static void Load(int nCnt, const char *aFileName);
	static void UnLoad();

private:
	CModel *m_pModel;
	CDanger *m_pDanger;
};
#endif