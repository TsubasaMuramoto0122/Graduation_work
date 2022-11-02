//*****************************************************************************
// ��]�G�t�F�N�g�̐e����(Rotate3d.h)
// Author : �����G��
//*****************************************************************************
#ifndef _ROTATE3D_H_
#define _ROTATE3D_H_

#include "Effect_base.h"

class CRotate3D : public CEffect_base
{
public:
	typedef enum
	{
		START,	//�L����
		ACTIVE,	//��]
		END,	//�j��
		MAX,
	} EFFECT_TIME;	//�G�t�F�N�g�̏��

	typedef enum
	{
		TYPE_PARTICLE,	//�p�[�e�B�N��
		TYPE_TRAJECT,	//�O��
		TYPE_MAX,
	} EFFECT_TYPE;	//���̃G�t�F�N�g�o����

	typedef enum
	{
		TYPE_NOMAL,
		TYPE_MOVERAND,
		MOVETYPE_MAX,
	} MOVE_TYPE;	//�Ȃɂ���H

	CRotate3D(PRIORITY nPriority);
	~CRotate3D();

	HRESULT Init(D3DXVECTOR3 SetSize,
		D3DXVECTOR3 pos,
		D3DXVECTOR2 Tex,
		D3DXVECTOR3 Size,
		D3DXVECTOR3 AddSize,
		D3DCOLORVALUE Color,
		D3DCOLORVALUE AddColor,
		float Distance,
		float AddDistance,
		float fAngle,
		float fAddAngle,
		int nTex,
		int Synthetic,
		int nLife,
		int nParticleLife,
		int nBuckTime,
		float fActive,
		int AnimPattern,
		EFFECT_TYPE EffectType,
		MOVE_TYPE MoveType);	//������

	void Uninit();	//�I��
	void Update();	//�X�V

	static CRotate3D *Create(D3DXVECTOR3 SetSize,
		D3DXVECTOR3 pos,
		D3DXVECTOR2 Tex,
		D3DXVECTOR3 Size,
		D3DXVECTOR3 AddSize,
		D3DCOLORVALUE Color,
		D3DCOLORVALUE AddColor,
		float Distance,
		float AddDistance,
		float fAngle,
		float fAddAngle,
		int nTex,
		int Synthetic,
		int nLife,
		int nParticleLife,
		int nBuckTime,
		float fActive,
		int AnimPattern,
		EFFECT_TYPE EffectType,
		MOVE_TYPE MoveType);	//�쐬

private:
	EFFECT_TIME m_EffectTime;	//���
	EFFECT_TYPE m_EffectType;
	MOVE_TYPE m_MoveType;

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_Oldpos;

	D3DXVECTOR3 m_Size;
	D3DXVECTOR3 m_AddSize;
	D3DCOLORVALUE m_Color;
	D3DCOLORVALUE m_MinColor;

	float m_nDistanse;
	float m_nBuckDistanse;

	float m_nAddDistance;
	float m_fAngle;
	float m_fAddAngle;
	float m_fRandAngle;
	float m_fRandAngle2;
	int m_nBuckTime;	//�������k�܂�܂ł̎���
	float m_fActive;	//�A�N�e�B�u�ɂȂ�܂ł̋���

	int m_nTex;
	int m_nSynthetic;
	int m_nLife;
	int m_ParticleLife;
	int m_PatternAnim;
};

#endif