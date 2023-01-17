//=============================================================================
//
// �v���C���[�̕X���� [playerice.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _PLAYERICE_H_
#define _PLAYERICE_H_

#include "main.h"
#include "object.h"

//=============================================================================
//�}�N��
//=============================================================================
class CModel;

class CPlayerIce : public CObject
{
public:
	CPlayerIce(PRIORITY nPriority);
	~CPlayerIce();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit();
	void Update();
	void Draw();
	void ZTexDraw();

	static CPlayerIce *Create(D3DXVECTOR3 pos);
	static void Load(const char *aModelName);
	static void UnLoad();

private:
	CModel *m_pModel;
	D3DXMATRIX m_mtxWorld;

	static CModel *m_paModel;
};

#endif