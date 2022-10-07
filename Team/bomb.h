//=============================================================================
//
// ボム処理 [bomb.h]
// Author : 三上航世
//
//=============================================================================
#ifndef _BOMB_H_
#define _BOMB_H_

#include "main.h"
#include "scene3d.h"
#include "model.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


class CDanger;

class CBomb : public CScene3D
{
public:
	//爆弾の種類
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

	static CModel *m_paModel[MAX_BOMB]; //モデル（パーツ）
	static void Load(int nCnt, const char *aFileName);
	static void UnLoad();

private:
	virtual void Explosion() = 0;

	bool m_bBound;			//バウンドしたか
	bool m_bLand;			//着地してる
	int m_nTime;			//時間
	D3DXVECTOR3 m_move;		//移動量
	CModel *m_pModel;		//モデル
	CDanger *m_pDanger;		//危険範囲
};
#endif