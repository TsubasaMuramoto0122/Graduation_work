//=============================================================================
//
// フェード処理 [scene3d.h]
// Author : 三上航世
//
//=============================================================================
#include "scene3d.h"
#include "manager.h"
#include "renderer.h"

CScene3D::CScene3D(PRIORITY Priority) : CScene::CScene(Priority)
{

}

CScene3D::~CScene3D()
{

}


//初期化処理
HRESULT CScene3D::Init(D3DXVECTOR3 /*pos*/)
{
	return S_OK;
}

//終了処理
void CScene3D::Uninit()
{
	Release();
}

//更新処理
void CScene3D::Update()
{

}

//描画処理
void CScene3D::Draw()
{

}

CScene3D *CScene3D::Create(const D3DXVECTOR3& pos)
{
	CScene3D *pScene3D;
	pScene3D = new CScene3D(PRIORITY_OBJECT);
	if (pScene3D != NULL)
	{
		pScene3D->Init(pos);
	}
	return pScene3D;
}

void CScene3D::SetRot(D3DXVECTOR3 rot)
{
	if (rot.x  < -D3DX_PI)
	{
		rot.x += D3DX_PI * 2.0f;
	}
	else if (D3DX_PI < rot.x)
	{
		rot.x -= D3DX_PI * 2.0f;
	}
	if (rot.y  < -D3DX_PI)
	{
		rot.y += D3DX_PI * 2.0f;
	}
	else if (D3DX_PI < rot.y)
	{
		rot.y -= D3DX_PI * 2.0f;
	}
	if (rot.z  < -D3DX_PI)
	{
		rot.z += D3DX_PI * 2.0f;
	}
	else if (D3DX_PI < rot.z)
	{
		rot.z -= D3DX_PI * 2.0f;
	}
	m_rot = rot;
}