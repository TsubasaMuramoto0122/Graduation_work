//=============================================================================
//
// �I�u�W�F�N�g���� [object.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "main.h"
#include "scene3d.h"

//=============================================================================
//�}�N��
//=============================================================================
#define MAX_OBJECTS (8)

class CModel;

class CObject : public CScene3D
{
public:
	CObject(PRIORITY nPriority);
	~CObject();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, int nType);
	void Uninit();
	void Update();
	void Draw();

	static CObject *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, int nType);
	static void Load(int nCnt, const char *aModelName);
	static void UnLoad();

private:
	void ModelCopy(int nType);

	CModel *m_pModel;
	D3DXVECTOR3 m_move;

	static CModel *m_paModel[MAX_OBJECTS];
};

#endif