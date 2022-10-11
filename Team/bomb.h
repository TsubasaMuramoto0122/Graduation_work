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

//*****************************************************************************
// �}�N����`
//*****************************************************************************


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
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, BOMBTYPE BombType);
	void Uninit();
	void Update();
	void Draw();
	OBJTYPE GetObjType() { return OBJECTTYPE_BOMB; }

	static CModel *m_paModel[MAX_BOMB]; //���f���i�p�[�c�j
	static void Load(int nCnt, const char *aFileName);
	static void UnLoad();

private:
	virtual void Explosion() = 0;

	bool m_bBound;			//�o�E���h������
	bool m_bLand;			//���n���Ă�
	int m_nTime;			//����
	D3DXVECTOR3 m_move;		//�ړ���
	CModel *m_pModel;		//���f��
	CDanger *m_pDanger;		//�댯�͈�
};
#endif