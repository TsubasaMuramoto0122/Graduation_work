//=============================================================================
//
// シーン処理 [scene.h]
// Author : 三上航世
//
//=============================================================================
#include "scene.h"
//#include "game.h"
#include "manager.h"
#include "renderer.h"
#include "realshadow.h"
#include "ztex.h"

//静的メンバ変数
CScene *CScene::m_pTop[PRIORITY_MAX] = {};
CScene *CScene::m_pCur[PRIORITY_MAX] = {};
int CScene::m_nNumAll = 0;

//=============================================================================
// コンストラクタ
//=============================================================================
CScene::CScene(CScene::PRIORITY Priority)
{
	m_Priority = Priority;

	m_pNext = NULL;
	m_bDeath = false;
	if (m_pTop[m_Priority] == NULL && m_pCur[m_Priority] == NULL)
	{
		m_pPrev = NULL;
		m_pTop[m_Priority] = this;
		m_pCur[m_Priority] = this;
	}
	else if (m_pCur != NULL)
	{
		m_pCur[m_Priority]->m_pNext = this;
		m_pPrev = m_pCur[m_Priority];
		m_pCur[m_Priority] = this;
	}
	m_nNumAll++;
}

//=============================================================================
// デストラクタ
//=============================================================================
CScene::~CScene()
{
	//エフェクトに不具合が発生して勝手に自分のやつに変えました、すまぬ
	PRIORITY Priority = m_Priority;

	//消す対象がTopでありCurだった場合
	if (this == m_pTop[Priority] &&
		this == m_pCur[Priority])
	{
		m_pTop[Priority] = NULL;
		m_pNext = NULL;
		m_pCur[Priority] = NULL;
		m_pPrev = NULL;
	}
	//消す対象がTop
	else if (this == m_pTop[Priority])
	{
		m_pTop[Priority] = m_pNext;
		m_pPrev = NULL;
		m_pNext->m_pPrev = NULL;
	}
	//消す対象がCur
	else if (this == m_pCur[Priority])
	{
		m_pCur[Priority] = m_pPrev;
		m_pNext = NULL;
		m_pPrev->m_pNext = NULL;
	}
	//それ以外
	else
	{
		m_pNext->m_pPrev = m_pPrev;
		m_pPrev->m_pNext = m_pNext;
	}
}

void CScene::ReleaseAll()
{
	//描画処理順を判別
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		CScene *pScene;
		pScene = m_pTop[nCntPriority];
		while (pScene)
		{
			CScene *pSceneNext;
			pSceneNext = pScene->m_pNext;
			pScene->Uninit();
			pScene = pSceneNext;
		}
	}
}

void CScene::UpdateAll()
{
	//描画処理順を判別
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		CScene *pScene;
		pScene = m_pTop[nCntPriority];
		while (pScene)
		{
			CScene *pSceneNext;
			pSceneNext = pScene->m_pNext;
			pScene->Update();
			if (pScene->m_bDeath == true)
			{
				pScene->Uninit();
			}
			pScene = pSceneNext;
		}
	}
}

void CScene::DrawAll()
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	int nCntPriority;

	CZTex *pZTex;
	pZTex = CManager::GetRenderer()->GetZTex();
	pZTex->Begin();
	//描画処理順を判別
	for (nCntPriority = 0; nCntPriority < PRIORITY_EFFECT; nCntPriority++)
	{
		CScene *pScene;
		pScene = m_pTop[nCntPriority];
		while (pScene)
		{
			CScene *pSceneNext;
			pSceneNext = pScene->m_pNext;
			pScene->ZTexDraw();
			pScene = pSceneNext;
		}
	}
	pZTex->End();

	CRealShadow *pRealShadow;
	pRealShadow = CManager::GetRenderer()->GetRealShadow();
	pRealShadow->Begin();
	//描画処理順を判別
	for (nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		CScene *pScene;
		pScene = m_pTop[nCntPriority];
		if (nCntPriority == PRIORITY_EFFECT)
		{
			pRealShadow->End();
		}
		while (pScene)
		{
			CScene *pSceneNext;
			pSceneNext = pScene->m_pNext;
			pScene->Draw();
			pScene = pSceneNext;
		}
	}
}

//削除
void CScene::Release()
{
	delete this;
	m_nNumAll--;
}

CScene *CScene::GetTopObj(int nPriority)
{
	// 引数で指定したプライオリティの、先頭のオブジェクトを返す
	return m_pTop[nPriority];
}

CScene *CScene::GetObjNext(CScene *pObject)
{
	// 引数で指定したオブジェクトの、次のオブジェクトを返す
	return pObject->m_pNext;
}