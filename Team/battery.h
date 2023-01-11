//=============================================================================
//
// �C�䏈�� [battery.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _BATTERY_H_
#define _BATTERY_H_

#include "main.h"
#include "object.h"
#include "model.h"

//=============================================================================
//�}�N��
//=============================================================================
#define MAX_BATTERY (3)
#define MOTION_BATTERY_FILE "data/FILES/Models/battery.txt"	// �t�@�C���̃p�X

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

	void SetModelPos(int nCntModel, D3DXVECTOR3 pos) { m_pModel[nCntModel]->SetPos(pos); }		// ���f�����̈ʒu�ݒ菈��
	D3DXVECTOR3 GetModelPos(int nCntModel) { return m_pModel[nCntModel]->GetPos(); }			// ���f�����̈ʒu�擾����
	void SetModelRot(int nCntModel, D3DXVECTOR3 rot) { m_pModel[nCntModel]->SetRot(rot); }		// ���f�����̌����ݒ菈��
	D3DXVECTOR3 GetModelRot(int nCntModel) { return m_pModel[nCntModel]->GetRot(); }			// ���f�����̌����擾����
	
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

	static CModel *m_pOriModel[MAX_BATTERY];	//���f���̌��^(�����񃂃f����ǂݍ��ނ̂�h������)
};

#endif