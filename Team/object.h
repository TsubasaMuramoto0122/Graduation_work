//=============================================================================
//
// オブジェクト処理 [object.h]
// Author : 三上航世
//
//=============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "main.h"
#include "scene3d.h"

//=============================================================================
//マクロ
//=============================================================================
#define MAX_OBJECTS (8)

class CModel;

class CObject : public CScene3D
{
public:
	CObject(PRIORITY nPriority);
	~CObject();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType);
	void Uninit();
	void Update();
	void Draw();
	void ZTexDraw();

	static CObject *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType);
	static void Load(int nCnt, const char *aModelName);
	static void UnLoad();

private:
	void ModelCopy(int nType);
	CModel *m_pModel;

	static CModel *m_paModel[MAX_OBJECTS];
};

#endif