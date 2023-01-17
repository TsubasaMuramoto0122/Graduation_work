//=============================================================================
//
// �V�[������ [scene.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_
#include "main.h"

//�}�N����`
//#define POLYGON_SIZE (70.0f)
//#define PRIORITY (7)
//#define CIRCLE (float(rand() % 324) / 100.0f - float(rand() % 324) / 100.0f) //�~

class CScene
{
public:

	//�I�u�W�F�N�g�̎��
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
		PRIORITY_PLANE = 0,
		PRIORITY_BOMB,
		PRIORITY_OBJECT,
		PRIORITY_CHARA,
		PRIORITY_EFFECTSET,
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
	static CScene *GetTopObj(int nPriority);// �擪�I�u�W�F�N�g�̎擾����
	CScene *GetObjNext(CScene *pObject);	// ���̃I�u�W�F�N�g�̏��擾����

private:
	static CScene *m_pTop[PRIORITY_MAX]; //�擪�̃I�u�W�F�N�g�̃|�C���^
	static CScene *m_pCur[PRIORITY_MAX]; //����(��Ԍ��)�̃I�u�W�F�N�g�̃|�C���^
	CScene *m_pPrev;       //�O�̃I�u�W�F�N�g�̃|�C���^
	CScene *m_pNext;       //���̃I�u�W�F�N�g�̃|�C���^

	static int m_nNumAll;
	bool m_bDeath;

	PRIORITY m_Priority;//�D�揇��

protected:
	void Release();
};
#endif