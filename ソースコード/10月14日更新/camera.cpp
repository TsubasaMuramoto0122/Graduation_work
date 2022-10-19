//=============================================================================
//
// カメラ処理 [camera.h]
// Author : 三上航世
//
//=============================================================================
#include "camera.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"

#define UNDER_CAMERA (-500.0f)
#define UP_CAMERA (550.0f)

CCamera::CCamera()
{

}

CCamera::~CCamera()
{

}

//初期化処理
HRESULT CCamera::Init(D3DXVECTOR3 ref, float fDistance, D3DXVECTOR3 pos)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = CManager::GetRenderer()->GetDevice();     //デバイスを取得する
	m_camera.posV = ref;
	m_camera.posVDest = ref;
	m_camera.posR = pos;
	m_camera.posRDest = pos;
	m_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_camera.rot = MathFront();
	m_camera.rotDesh = m_camera.rot;
	m_camera.fLength = fDistance;		//距離

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_camera.mtxProjection);
	//プロジェクションマトリックス作成
	D3DXMatrixPerspectiveFovLH(&m_camera.mtxProjection, D3DXToRadian(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, 30000.0f);
	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_camera.mtxProjection);
	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_camera.mtxView);
	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_camera.mtxView, &m_camera.posV, &m_camera.posR, &m_camera.vecU);
	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_camera.mtxView);

	return S_OK;
}

//終了処理
void CCamera::Uninit()
{
	delete this;
}

//更新処理
void CCamera::Update()
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = CManager::GetRenderer()->GetDevice();     //デバイスを取得する
	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		//D3DXVECTOR3 pos = m_pPlayer->GetPos();
		//if (m_camera.bRot[1] == true && m_camera.bAdd[1] == false)
		//{
		//	//Y方向回転
		//	if (m_camera.rot.y != m_camera.rotDesh.y)
		//	{
		//		if (m_camera.rotDesh.y - m_camera.rot.y < -D3DX_PI)
		//		{
		//			m_camera.rot.y += (m_camera.rotDesh.y - m_camera.rot.y + D3DX_PI * 2) * 0.1f;
		//		}
		//		else if (m_camera.rotDesh.y - m_camera.rot.y > D3DX_PI)
		//		{
		//			m_camera.rot.y += (m_camera.rotDesh.y - m_camera.rot.y - D3DX_PI * 2) * 0.1f;
		//		}
		//		else
		//		{
		//			m_camera.rot.y += (m_camera.rotDesh.y - m_camera.rot.y) * 0.1f;
		//		}
		//	}
		//	if (fabsf(m_camera.rotDesh.y - m_camera.rot.y) < 0.3f)
		//	{
		//		m_camera.bRot[1] = false;
		//	}
		//}
		//if (m_camera.bRot[0] == true && m_camera.bAdd[0] == false)
		//{
		//	//X方向回転
		//	if (m_camera.rot.x != m_camera.rotDesh.x)
		//	{
		//		if (m_camera.rotDesh.x - m_camera.rot.x < -D3DX_PI)
		//		{
		//			m_camera.rot.x += (m_camera.rotDesh.x - m_camera.rot.x + D3DX_PI * 2) * 0.1f;
		//		}
		//		else if (m_camera.rotDesh.x - m_camera.rot.x > D3DX_PI)
		//		{
		//			m_camera.rot.x += (m_camera.rotDesh.x - m_camera.rot.x - D3DX_PI * 2) * 0.1f;
		//		}
		//		else
		//		{
		//			m_camera.rot.x += (m_camera.rotDesh.x - m_camera.rot.x) * 0.1f;
		//		}
		//	}
		//	if (fabsf(m_camera.rotDesh.x - m_camera.rot.x) < 0.1f)
		//	{
		//		m_camera.bRot[0] = false;
		//	}
		//}
		/*if (CManager::GetGameClear() == false && CManager::GetGameEnd() == false)
		{
			m_camera.posR.x = pos.x + m_camera.posPlus.x;
			m_camera.posR.y = pos.y + m_pPlayer->GetHeight() * 1.5f + m_camera.posPlus.y;
			m_camera.posR.z = pos.z + m_camera.posPlus.z;
			m_camera.posV.x = pos.x - (sinf(m_camera.rot.y)) * m_camera.fLength + m_camera.posPlus.x;
			m_camera.posV.y = pos.y + m_pPlayer->GetHeight() * 1.5f + m_camera.posPlus.y;
			m_camera.posV.z = pos.z - (cosf(m_camera.rot.y)) * m_camera.fLength + m_camera.posPlus.z;
		}*/
	}
	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_camera.mtxView);
	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_camera.mtxView, &m_camera.posV, &m_camera.posR, &m_camera.vecU);
	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_camera.mtxView);
}

//設定処理
CCamera *CCamera::Create(D3DXVECTOR3 ref, float fDistance, D3DXVECTOR3 pos)
{
	CCamera *pCamera;
	pCamera = new CCamera;
	if (pCamera != NULL)
	{
		pCamera->Init(ref, fDistance, pos);
	}
	return pCamera;
}

void CCamera::SetPosV(D3DXVECTOR3 pos)
{
	m_camera.posVDest = pos;
	m_camera.posV = pos;
}

void CCamera::SetPosR(D3DXVECTOR3 pos)
{
	m_camera.posRDest = pos;
	m_camera.posR = pos;
}

void CCamera::ResetRot()
{
	m_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

void CCamera::SetRotDeshX(float fRotX)
{
	m_camera.rotDesh.x = fRotX;
}

void CCamera::SetRotDeshY(float fRotY)
{
	m_camera.rotDesh.y = fRotY;
	if (m_camera.rotDesh.y >= D3DX_PI)
	{
		m_camera.rotDesh.y -= D3DX_PI * 2;
	}
	if (m_camera.rotDesh.y < -D3DX_PI)
	{
		m_camera.rotDesh.y += D3DX_PI * 2;
	}
}

D3DXVECTOR3 CCamera:: MathFront(void)
{
	float fFrontRot = 0;
	D3DXVECTOR3 posR = GetPosV(), posV = GetPosR();

	// 視点と注視点の位置から正面の向きを計算
	fFrontRot = (float)atan2((posR.x - posV.x), (posR.z - posV.z)) - D3DX_PI;

	return D3DXVECTOR3(0.0f, fFrontRot, 0.0f);
}