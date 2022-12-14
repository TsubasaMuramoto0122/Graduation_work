//*****************************************************************************
// 回転エフェクトの親処理(Rotate3d.h)
// Author : 佐藤秀亮
//*****************************************************************************
#ifndef _ROTATE3D_H_
#define _ROTATE3D_H_

#include "Effect_base.h"

class CRotate3D : public CEffect_base
{
public:
	typedef enum
	{
		START,	//広がり
		ACTIVE,	//回転
		END,	//祝量
		MAX,
	} EFFECT_TIME;	//エフェクトの状態

	typedef enum
	{
		TYPE_PARTICLE,	//パーティクル
		TYPE_TRAJECT,	//軌跡
		TYPE_MAX,
	} EFFECT_TYPE;	//何のエフェクト出すか

	typedef enum
	{
		TYPE_NOMAL,
		TYPE_MOVERAND,
		MOVETYPE_MAX,
	} MOVE_TYPE;	//なにこれ？

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
		MOVE_TYPE MoveType);	//初期化

	void Uninit();	//終了
	void Update();	//更新

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
		MOVE_TYPE MoveType);	//作成

private:
	EFFECT_TIME m_EffectTime;	//状態
	EFFECT_TYPE m_EffectType;
	MOVE_TYPE m_MoveType;

	bool m_bUninit;

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
	int m_nBuckTime;	//距離が縮まるまでの時間
	float m_fActive;	//アクティブになるまでの距離

	int m_nTex;
	int m_nSynthetic;
	int m_nLife;
	int m_ParticleLife;
	int m_PatternAnim;
};

#endif