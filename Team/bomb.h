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
class CCollisionSphere;

class CBomb : public CScene3D
{
public:
	//爆弾の種類
	typedef enum
	{
		BOMB_NORMAL = 0,	//ノーマル
		BOMB_ICE,			//氷
		BOMB_FIRE,			//炎
		BOMB_POISON,		//毒
		BOMB_CONFUSION,		//混乱
		MAX_BOMB
	} BOMBTYPE;

	CBomb(PRIORITY Priority);
	~CBomb();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, BOMBTYPE BombType);
	void Uninit();
	void Update();
	void Draw();
	OBJTYPE GetObjType() { return OBJECTTYPE_BOMB; }
	float GetRadius() { return m_fRadius; }

	static CModel *m_paModel[MAX_BOMB];					//爆弾のモデル全種
	static void Load(int nCnt, const char *aModelName) { m_paModel[nCnt] = CModel::Create(aModelName); }	//モデルデータ読み込み
	static void UnLoad();								//モデルデータ捨てる

private:
	virtual void Explosion(D3DXVECTOR3 pos) = 0;	//爆発処理
	void Flash();									//爆発範囲の点滅(いつ爆発するか分かりやすいように)
	void TimeDec(D3DXVECTOR3 pos);					//寿命の減少
	D3DXVECTOR3 Bound(D3DXVECTOR3 pos);				//バウンド
	void MoveDown();								//移動量の減少
	D3DXVECTOR3 Predict(D3DXVECTOR3 pos);			//着弾点の予測

	bool m_bBound;									//バウンドしたか
	bool m_bLand;									//着地してる
	int m_nTime;									//寿命
	int m_nFlash;									//点滅
	float m_fClear;									//透明度
	float m_fRadius;								//半径
	D3DXVECTOR3 m_move;								//移動量
	CModel *m_pModel;								//モデル
	CDanger *m_pDanger;								//危険範囲
	CCollisionSphere *m_pCollision;					//球体コリジョンのポインタ
};
#endif