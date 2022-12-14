//=============================================================================
//
// シーン処理 [scene.h]
// Author : 三上航世
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_
#include "main.h"

//マクロ定義
//#define POLYGON_SIZE (70.0f)
//#define PRIORITY (7)
//#define CIRCLE (float(rand() % 324) / 100.0f - float(rand() % 324) / 100.0f) //円

class CScene
{
public:

	//オブジェクトの種類
	typedef enum
	{
		OBJECTTYPE_NONE = 0,
		OBJECTTYPE_UI,
		OBJECTTYPE_PLAYER,
		OBJECTTYPE_BOMB,
		OBJECTTYPE_FIELD,
		OBJECTTYPE_WALL,
		OBJECTTYPE_COLLISION,
		OBJECTTYPE_MAX
	} OBJTYPE;

	typedef enum
	{
		COLLISION_SPHERE = 0,
		COLLISION_PALL,
		COLLISION_SQUARE,
		COLLISION_MAX
	} COLLISION;

	typedef enum
	{
		PRIORITY_BOMB = 0,
		PRIORITY_OBJECT,
		PRIORITY_CHARA,
		PRIORITY_PLANE,
		PRIORITY_EFFECT,
		PRIORITY_COLLISION,
		PRIORITY_UIEFFECT,
		PRIORITY_UI,
		PRIORITY_PAUSEUI,
		PRIORITY_MAX
	} PRIORITY;

	CScene(PRIORITY Priority);
	virtual ~CScene();
	virtual HRESULT Init(D3DXVECTOR3 pos) = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void ZTexDraw() = 0;
	virtual OBJTYPE GetObjType() = 0;
	virtual void SetPos(D3DXVECTOR3 pos) = 0;
	virtual D3DXVECTOR3 GetPos() = 0;
	virtual D3DXVECTOR3 GetPosOld() = 0;
	virtual float GetRadius() = 0;
	virtual CScene *GetNext() { return m_pNext; }

	static CScene *GetScene(PRIORITY Priority) { return m_pTop[Priority]; }
	static void ReleaseAll();
	static void UpdateAll();
	static void DrawAll();

	void SetDeath(bool bDeath) { m_bDeath = bDeath; }
	bool GetDeath() { return m_bDeath; }
	static CScene *GetTopObj(int nPriority);// 先頭オブジェクトの取得処理
	CScene *GetObjNext(CScene *pObject);	// 次のオブジェクトの情報取得処理

private:
	static CScene *m_pTop[PRIORITY_MAX]; //先頭のオブジェクトのポインタ
	static CScene *m_pCur[PRIORITY_MAX]; //現在(一番後ろ)のオブジェクトのポインタ
	static int m_nNumAll;

	CScene *m_pPrev;       //前のオブジェクトのポインタ
	CScene *m_pNext;       //後ろのオブジェクトのポインタ
	bool m_bDeath;

	PRIORITY m_Priority;//優先順位

protected:
	void Release();
};
#endif