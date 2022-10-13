//=============================================================================
//
// �t�F�[�h���� [scene3d.h]
// Author : �O��q��
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


//����������
HRESULT CScene3D::Init(D3DXVECTOR3 /*pos*/)
{
	return S_OK;
}

//�I������
void CScene3D::Uninit()
{
	Release();
}

//�X�V����
void CScene3D::Update()
{

}

//�`�揈��
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