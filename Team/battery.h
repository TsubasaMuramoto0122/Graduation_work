//=============================================================================
//
// 砲台処理 [battery.h]
// Author : 三上航世
//
//=============================================================================
#ifndef _BATTERY_H_
#define _BATTERY_H_

#include "main.h"
#include "object.h"
#include "model.h"

//=============================================================================
//マクロ
//=============================================================================
#define MAX_BATTERY (3)
#define MOTION_BATTERY_FILE "data/FILES/Models/battery.txt"	// ファイルのパス

class CMotion;

class CBattery : public CObject
{
public:
	CBattery(PRIORITY nPriority);
	~CBattery();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nTime, float fSpeed, float fHeight);
	void Uninit();
	void Update();
	void Draw();
	void ZTexDraw();

	void SetModelPos(int nCntModel, D3DXVECTOR3 pos) { m_pModel[nCntModel]->SetPos(pos); }		// モデル毎の位置設定処理
	D3DXVECTOR3 GetModelPos(int nCntModel) { return m_pModel[nCntModel]->GetPos(); }			// モデル毎の位置取得処理
	void SetModelRot(int nCntModel, D3DXVECTOR3 rot) { m_pModel[nCntModel]->SetRot(rot); }		// モデル毎の向き設定処理
	D3DXVECTOR3 GetModelRot(int nCntModel) { return m_pModel[nCntModel]->GetRot(); }			// モデル毎の向き取得処理
	
	static CBattery *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nTime, float fSpeed, float fHeight, float fFriction);
	static void BatteryLoad();
	static void BatteryUnLoad();

private:
	void RandomBomb(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	D3DXMATRIX m_mtxWorld;
	int m_nTime;
	int m_nMaxTime;
	CMotion *m_pMotion;
	CModel *m_pModel[MAX_BATTERY];
	float m_fSpeed;
	float m_fHeight;
	float m_fFriction;

	static CModel *m_pOriModel[MAX_BATTERY];	//モデルの原型(複数回モデルを読み込むのを防ぐため)
};

#endif