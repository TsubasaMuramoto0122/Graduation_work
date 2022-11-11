//*****************************************************************************	
// �G�t�F�N�g�ݒu���� [SetEffect.cpp]
// Author : �����G��
//*****************************************************************************
//*****************************************************************************
// �C���N���[�h�t�@�C��
//***************************************************************************** 
#include "PresetSetEffect.h"
#include "scene.h"

//�Q��
//#include "MouseTracking.h"
//#include "Movement.h"
//#include "Rotate.h"

//�R��
//#include "Trajectory.h"
#include "straight3d.h"
#include "FieldEffect.h"
#include "Rotate3d.h"
#include "sphereEffect.h"
//#include "ThunderBill.h"
//#include "BezierBillh.h"
//#include "BulletHoll.h"
//#include "Fountain.h"

#include "LoadEffect.h"
#include "PresetDelaySet.h"

#include <assert.h>

//*****************************************************************************
// �}�N��
//***************************************************************************** 
#define RAND_COLOR ((float(rand()% 10) + 1) / 10)		//�����_���J���[


//*****************************************************************************
// �ÓI
//***************************************************************************** 
//int CPresetEffect::m_nEffectPattern2d = 0;
int CPresetEffect::m_nEffectPattern3d = 0;
int CPresetEffect::m_PrticleCreateTime = 0;	//�p�[�e�B�N�������Ԋu�v�Z
int CPresetEffect::m_nMaxOrderCount = 0;	//�Ăяo���ő吔�J�E���g

											//CPresetEffect::EFFECT_STATE2D CPresetEffect::m_EffectState2D[MAX_EFFECTPATTERN_2D] = {};
CPresetEffect::EFFECT_STATE3D CPresetEffect::m_EffectState3D[MAX_EFFECTPATTERN_3D] = {};
//CPresetEffect::ORDER_PRESET CPresetEffect::m_Order3D[MAX_ORDER_3D][MAX_ORDER_3D] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPresetEffect::CPresetEffect(PRIORITY Priority) : CScene3D(Priority)
{
	//m_EffectState2D[MAX_EFFECTPATTERN_2D] = {};
	//m_Order3D[MAX_ORDER_3D][MAX_ORDER_3D] = {};
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPresetEffect::~CPresetEffect()
{

}
//2D�͍��̂Ƃ���K�v�Ȃ�
#if 0
//=============================================================================
// �ϐ��ɂԂ����ފ֐� 2D�p
//=============================================================================
void CPresetEffect::SetEffectState2D(int nPattern,
	float fRotate,
	D3DXVECTOR2 move,
	D3DXVECTOR2 Addmove,
	int Diffusion,
	int Destroyvec,
	float fSize,
	float fAddSize,
	D3DCOLORVALUE col,
	D3DCOLORVALUE Changecolor,
	int nLife,
	int nDensity,
	bool bColorRandR,
	bool bColorRandG,
	bool bColorRandB,
	int Synthetic,
	int Texture,
	float Distance,
	D3DXVECTOR2 m_TexMove,
	D3DXVECTOR2 m_TexNum,
	int AnimPatternType,
	D3DXVECTOR2 TexSplit,
	int AnimCnt,
	int nType,
	float fHigth,
	float SecondSize,
	D3DCOLORVALUE SecondCol,
	D3DCOLORVALUE SecondChangecolor)
{
	m_EffectState2D[m_nEffectPattern2d].m_nPattern = nPattern + 1;
	m_EffectState2D[m_nEffectPattern2d].m_fRotate = fRotate;
	m_EffectState2D[m_nEffectPattern2d].m_move = move;
	m_EffectState2D[m_nEffectPattern2d].m_Addmove = Addmove;
	m_EffectState2D[m_nEffectPattern2d].m_nDiffusion = Diffusion;
	m_EffectState2D[m_nEffectPattern2d].m_nDestroyvec = Destroyvec;
	m_EffectState2D[m_nEffectPattern2d].m_fSize = fSize;
	m_EffectState2D[m_nEffectPattern2d].m_fAddSize = fAddSize;
	m_EffectState2D[m_nEffectPattern2d].m_Col = col;
	m_EffectState2D[m_nEffectPattern2d].m_Changecolor = Changecolor;
	m_EffectState2D[m_nEffectPattern2d].m_nLife = nLife;
	m_EffectState2D[m_nEffectPattern2d].m_nDensity = nDensity;
	m_EffectState2D[m_nEffectPattern2d].m_bColorRandR = bColorRandR;
	m_EffectState2D[m_nEffectPattern2d].m_bColorRandG = bColorRandG;
	m_EffectState2D[m_nEffectPattern2d].m_bColorRandB = bColorRandB;
	m_EffectState2D[m_nEffectPattern2d].Synthetic = Synthetic;
	m_EffectState2D[m_nEffectPattern2d].nTexture = Texture;
	m_EffectState2D[m_nEffectPattern2d].m_Distance = Distance;
	m_EffectState2D[m_nEffectPattern2d].m_TexMove = m_TexMove;
	m_EffectState2D[m_nEffectPattern2d].m_TexNum = m_TexNum;
	m_EffectState2D[m_nEffectPattern2d].m_AnimPatternType = AnimPatternType;
	m_EffectState2D[m_nEffectPattern2d].m_TexSplit = TexSplit;
	m_EffectState2D[m_nEffectPattern2d].AnimCnt = AnimCnt;
	m_EffectState2D[m_nEffectPattern2d].m_nType = nType;
	m_EffectState2D[m_nEffectPattern2d].m_fHigth = fHigth;
	m_EffectState2D[m_nEffectPattern2d].m_SecondSize = SecondSize;
	m_EffectState2D[m_nEffectPattern2d].m_SecondCol = SecondCol;
	m_EffectState2D[m_nEffectPattern2d].m_SecondChangecolor = SecondChangecolor;

	m_nEffectPattern2d++;
}
#endif

//=============================================================================
// �ϐ��ɂԂ����ފ֐� 3D�p
//=============================================================================
void CPresetEffect::SetEffectState3D(
	int nPattern,
	float m_fRotate,
	float m_move,
	float m_Addmove,
	int m_nDiffusion,
	float m_fSize,
	float m_fAddSize,
	float m_fSizeY,
	float m_fAddSizeY,
	float m_MaxSize,
	float m_fParticleSize,
	float m_fParticleAddSize,
	int m_Active,
	D3DCOLORVALUE m_Col,
	D3DCOLORVALUE m_Changecolor,
	D3DCOLORVALUE m_SecondCol,
	D3DCOLORVALUE m_SecondChangecolor,
	int m_ParticleSynthetic,
	int m_nLife,
	int m_nDensity,
	int TrajectTop,
	int TrajectCur,
	D3DXVECTOR3 move3d,
	int RandMove,
	bool bColorRandR,
	bool bColorRandG,
	bool bColorRandB,
	int Synthetic,
	int Texture,
	int nDistance,
	int ParticleTime,
	float m_fActiveAddSize,
	int m_FieldTime,
	bool m_fieldCreate,
	int mCreatePreset,
	int m_nSecondTime,
	int m_nVtx,
	int m_nType,
	D3DXVECTOR2 m_TexMove,
	D3DXVECTOR2 m_TexNum,
	int m_nSecondType,
	D3DXVECTOR2 m_TexSplit,
	int AnimCnt,
	float fHigth,
	int AnimPatternType,
	D3DXVECTOR3 ControlBezier,
	D3DCOLORVALUE TherdCol,
	D3DCOLORVALUE TherdChangecolor,
	int SecondTex)
{
	m_EffectState3D[m_nEffectPattern3d].m_nPattern = nPattern;
	m_EffectState3D[m_nEffectPattern3d].m_fRotate = m_fRotate;
	m_EffectState3D[m_nEffectPattern3d].m_move = m_move;
	m_EffectState3D[m_nEffectPattern3d].m_Addmove = m_Addmove;
	m_EffectState3D[m_nEffectPattern3d].m_nDiffusion = m_nDiffusion;
	m_EffectState3D[m_nEffectPattern3d].m_fSize = m_fSize;
	m_EffectState3D[m_nEffectPattern3d].m_fAddSize = m_fAddSize;
	m_EffectState3D[m_nEffectPattern3d].m_fSizeY = m_fSizeY;
	m_EffectState3D[m_nEffectPattern3d].m_fAddSizeY = m_fAddSizeY;
	m_EffectState3D[m_nEffectPattern3d].m_MaxSize = m_MaxSize;
	m_EffectState3D[m_nEffectPattern3d].m_fParticleSize = m_fParticleSize;
	m_EffectState3D[m_nEffectPattern3d].m_fParticleAddSize = m_fParticleAddSize;
	m_EffectState3D[m_nEffectPattern3d].m_Col = m_Col;
	m_EffectState3D[m_nEffectPattern3d].m_Changecolor = m_Changecolor;
	m_EffectState3D[m_nEffectPattern3d].m_SecondCol = m_SecondCol;
	m_EffectState3D[m_nEffectPattern3d].m_SecondChangecolor = m_SecondChangecolor;
	m_EffectState3D[m_nEffectPattern3d].m_ParticleSynthetic = m_ParticleSynthetic;
	m_EffectState3D[m_nEffectPattern3d].m_nLife = m_nLife;
	m_EffectState3D[m_nEffectPattern3d].m_nDensity = m_nDensity;
	m_EffectState3D[m_nEffectPattern3d].TrajectTop = TrajectTop;
	m_EffectState3D[m_nEffectPattern3d].TrajectCur = TrajectCur;
	m_EffectState3D[m_nEffectPattern3d].move3d = move3d;
	m_EffectState3D[m_nEffectPattern3d].RandMove = RandMove;
	m_EffectState3D[m_nEffectPattern3d].m_bColorRandR = bColorRandR;
	m_EffectState3D[m_nEffectPattern3d].m_bColorRandG = bColorRandG;
	m_EffectState3D[m_nEffectPattern3d].m_bColorRandB = bColorRandB;
	m_EffectState3D[m_nEffectPattern3d].Synthetic = Synthetic;
	m_EffectState3D[m_nEffectPattern3d].nTexture = Texture;
	m_EffectState3D[m_nEffectPattern3d].m_Active = m_Active;
	m_EffectState3D[m_nEffectPattern3d].m_nDistance = nDistance;
	m_EffectState3D[m_nEffectPattern3d].ParticleTime = ParticleTime;
	m_EffectState3D[m_nEffectPattern3d].m_fActiveAddSize = m_fActiveAddSize;
	m_EffectState3D[m_nEffectPattern3d].m_FieldTime = m_FieldTime;
	m_EffectState3D[m_nEffectPattern3d].m_fieldCreate = m_fieldCreate;
	m_EffectState3D[m_nEffectPattern3d].mCreatePreset = mCreatePreset;
	m_EffectState3D[m_nEffectPattern3d].m_nSecondTime = m_nSecondTime;
	m_EffectState3D[m_nEffectPattern3d].m_nVtx = m_nVtx;
	m_EffectState3D[m_nEffectPattern3d].m_nType = m_nType;
	m_EffectState3D[m_nEffectPattern3d].m_TexMove = m_TexMove;
	m_EffectState3D[m_nEffectPattern3d].m_TexNum = m_TexNum;
	m_EffectState3D[m_nEffectPattern3d].m_SecondType = m_nSecondType;
	m_EffectState3D[m_nEffectPattern3d].m_TexSplit = m_TexSplit;
	m_EffectState3D[m_nEffectPattern3d].AnimCnt = AnimCnt;
	m_EffectState3D[m_nEffectPattern3d].m_fHigth = fHigth;
	m_EffectState3D[m_nEffectPattern3d].m_AnimPatternType = AnimPatternType;
	m_EffectState3D[m_nEffectPattern3d].m_ControlBezier = ControlBezier;
	m_EffectState3D[m_nEffectPattern3d].m_TherdCol = TherdCol;
	m_EffectState3D[m_nEffectPattern3d].m_TherdChangecolor = TherdChangecolor;
	m_EffectState3D[m_nEffectPattern3d].m_SecondTex = SecondTex;

	m_nEffectPattern3d++;
}

//2D�����͍��̂Ƃ��K�v�Ȃ��܂���
#if 0
//=============================================================================
// �Ă΂ꂽ�����Ăяo�����2D
//=============================================================================
void CPresetEffect::SetEffect2D(int nPattern, D3DXVECTOR3 pos, D3DXVECTOR3 Endpos, D3DXVECTOR3 PlayerPos, D3DXVECTOR3 rot)
{
	switch (m_EffectState2D[nPattern].m_nPattern)
	{
	case(1):
		for (int nCnt = 0; nCnt < m_EffectState2D[nPattern].m_nDensity; nCnt++)
		{
			//�e�F�̃����_����
			if (m_EffectState2D[nPattern].m_bColorRandR == true)
			{
				m_EffectState2D[nPattern].m_Col.r = RAND_COLOR;
			}
			if (m_EffectState2D[nPattern].m_bColorRandG == true)
			{
				m_EffectState2D[nPattern].m_Col.g = RAND_COLOR;
			}
			if (m_EffectState2D[nPattern].m_bColorRandB == true)
			{
				m_EffectState2D[nPattern].m_Col.b = RAND_COLOR;
			}

			CMovement::Create(pos,
				m_EffectState2D[nPattern].m_move,
				m_EffectState2D[nPattern].m_Col,
				m_EffectState2D[nPattern].m_Changecolor,
				D3DXVECTOR2(m_EffectState2D[nPattern].m_fSize, m_EffectState2D[nPattern].m_fSize),
				D3DXVECTOR2(m_EffectState2D[nPattern].m_fAddSize, m_EffectState2D[nPattern].m_fAddSize),
				m_EffectState2D[nPattern].m_nLife, m_EffectState2D[nPattern].nTexture,
				m_EffectState2D[nPattern].m_Addmove,
				m_EffectState2D[nPattern].Synthetic,
				m_EffectState2D[nPattern].m_TexMove,
				m_EffectState2D[nPattern].m_TexNum,
				m_EffectState2D[nPattern].AnimCnt,
				m_EffectState2D[nPattern].m_TexSplit,
				(CEffect::ANIMPATTERN)m_EffectState2D[nPattern].m_AnimPatternType,
				(CMovement::SHAPE_TYPE)m_EffectState2D[nPattern].m_nType,
				m_EffectState2D[nPattern].m_fHigth,
				m_EffectState2D[nPattern].m_Distance,
				m_EffectState2D[nPattern].m_SecondSize,
				m_EffectState2D[nPattern].m_SecondCol,
				m_EffectState2D[nPattern].m_SecondChangecolor);
		}
		break;
	case(2):
		for (int nCnt = 0; nCnt < m_EffectState2D[nPattern].m_nDensity; nCnt++)
		{
			//�e�F�̃����_����
			if (m_EffectState2D[nPattern].m_bColorRandR == true)
			{
				m_EffectState2D[nPattern].m_Col.r = RAND_COLOR;
			}
			if (m_EffectState2D[nPattern].m_bColorRandG == true)
			{
				m_EffectState2D[nPattern].m_Col.g = RAND_COLOR;
			}
			if (m_EffectState2D[nPattern].m_bColorRandB == true)
			{
				m_EffectState2D[nPattern].m_Col.b = RAND_COLOR;
			}

			CMouseTracking::Create(pos,
				m_EffectState2D[nPattern].m_move,
				m_EffectState2D[nPattern].m_Col,
				m_EffectState2D[nPattern].m_Changecolor,
				D3DXVECTOR2(m_EffectState2D[nPattern].m_fSize, m_EffectState2D[nPattern].m_fSize),
				D3DXVECTOR2(m_EffectState2D[nPattern].m_fAddSize, m_EffectState2D[nPattern].m_fAddSize),
				m_EffectState2D[nPattern].m_nLife, m_EffectState2D[nPattern].nTexture,
				Endpos, m_EffectState2D[nPattern].m_nDiffusion,
				m_EffectState2D[nPattern].m_nDestroyvec,
				m_EffectState2D[nPattern].Synthetic,
				m_EffectState2D[nPattern].m_Distance,
				PlayerPos,
				rot,
				m_EffectState2D[nPattern].m_TexMove,
				m_EffectState2D[nPattern].m_TexNum,
				m_EffectState2D[nPattern].AnimCnt,
				m_EffectState2D[nPattern].m_TexSplit,
				(CEffect::ANIMPATTERN)m_EffectState2D[nPattern].m_AnimPatternType);
		}
		break;
	case(3):
		for (int nCnt = 0; nCnt < m_EffectState2D[nPattern].m_nDensity; nCnt++)
		{

			//�e�F�̃����_����
			if (m_EffectState2D[nPattern].m_bColorRandR == true)
			{
				m_EffectState2D[nPattern].m_Col.r = RAND_COLOR;
			}
			if (m_EffectState2D[nPattern].m_bColorRandG == true)
			{
				m_EffectState2D[nPattern].m_Col.g = RAND_COLOR;
			}
			if (m_EffectState2D[nPattern].m_bColorRandB == true)
			{
				m_EffectState2D[nPattern].m_Col.b = RAND_COLOR;
			}

			CRotate::Create(pos,
				m_EffectState2D[nPattern].m_move,
				m_EffectState2D[nPattern].m_Col,
				m_EffectState2D[nPattern].m_Changecolor,
				D3DXVECTOR2(m_EffectState2D[nPattern].m_fSize, m_EffectState2D[nPattern].m_fSize),
				D3DXVECTOR2(m_EffectState2D[nPattern].m_fAddSize, m_EffectState2D[nPattern].m_fAddSize),
				m_EffectState2D[nPattern].m_nLife,
				m_EffectState2D[nPattern].nTexture,
				m_EffectState2D[nPattern].m_fRotate,
				m_EffectState2D[nPattern].Synthetic,
				m_EffectState2D[nPattern].m_TexMove,
				m_EffectState2D[nPattern].m_TexNum,
				m_EffectState2D[nPattern].AnimCnt,
				m_EffectState2D[nPattern].m_TexSplit,
				(CEffect::ANIMPATTERN)m_EffectState2D[nPattern].m_AnimPatternType);
		}
		break;
	case(4):
		for (int nCnt = 0; nCnt < m_EffectState2D[nPattern].m_nDensity; nCnt++)
		{

			//�e�F�̃����_����
			if (m_EffectState2D[nPattern].m_bColorRandR == true)
			{
				m_EffectState2D[nPattern].m_Col.r = RAND_COLOR;
			}
			if (m_EffectState2D[nPattern].m_bColorRandG == true)
			{
				m_EffectState2D[nPattern].m_Col.g = RAND_COLOR;
			}
			if (m_EffectState2D[nPattern].m_bColorRandB == true)
			{
				m_EffectState2D[nPattern].m_Col.b = RAND_COLOR;
			}

			CRotate::Create(pos,
				m_EffectState2D[nPattern].m_move,
				m_EffectState2D[nPattern].m_Col,
				m_EffectState2D[nPattern].m_Changecolor,
				D3DXVECTOR2(m_EffectState2D[nPattern].m_fSize, m_EffectState2D[nPattern].m_fSize),
				D3DXVECTOR2(m_EffectState2D[nPattern].m_fAddSize, m_EffectState2D[nPattern].m_fAddSize),
				m_EffectState2D[nPattern].m_nLife,
				m_EffectState2D[nPattern].nTexture,
				m_EffectState2D[nPattern].m_fRotate,
				m_EffectState2D[nPattern].Synthetic,
				m_EffectState2D[nPattern].m_TexMove,
				m_EffectState2D[nPattern].m_TexNum,
				m_EffectState2D[nPattern].AnimCnt,
				m_EffectState2D[nPattern].m_TexSplit,
				(CEffect::ANIMPATTERN)m_EffectState2D[nPattern].m_AnimPatternType);
		}
		break;

	default:
		break;
	}
}
#endif

//=============================================================================
// �Ă΂ꂽ�����Ăяo�����3D
//=============================================================================
void CPresetEffect::SetEffect3D(int nPattern, D3DXVECTOR3 pos, D3DXVECTOR3 Endpos, D3DXVECTOR3 rot)
{
	D3DXVECTOR3 Vectl;
	float fA;
	float fAY;
	int Vectlx;
	int Vectly;
	int Vectlz;
	float Rx;
	float Ry;
	float Rz;
	float y;
	float z;
	float x;
	bool bRx = false;
	bool bRy = false;
	bool bRz = false;
	float RandAngle;

	int a;

	D3DXVECTOR3 move = m_EffectState3D[nPattern].move3d;

	switch (m_EffectState3D[nPattern].m_nPattern)
	{
	case(0):	//�O��
		break;
	case(1):	//�p�[�e�B�N��
		for (int nCnt = 0; nCnt < m_EffectState3D[nPattern].m_nDensity; nCnt++)
		{
			CStraight3D *pStraight = CStraight3D::Create(pos,
				D3DXVECTOR3(m_EffectState3D[nPattern].m_fSize, m_EffectState3D[nPattern].m_fSizeY, 0.0f),
				D3DXVECTOR3(m_EffectState3D[nPattern].m_fAddSize, m_EffectState3D[nPattern].m_fAddSizeY, 0.0f),
				move,
				m_EffectState3D[nPattern].m_Col,
				m_EffectState3D[nPattern].m_Changecolor,
				m_EffectState3D[nPattern].nTexture,
				m_EffectState3D[nPattern].m_nLife,
				CStraight3D::STRAIGHT, {},
				m_EffectState3D[nPattern].Synthetic,
				m_EffectState3D[nPattern].m_nDistance,
				(CStraight3D::RAND_PATTEN)m_EffectState3D[nPattern].m_nType,
				(CStraight3D::POS_PATTERN)m_EffectState3D[nPattern].m_SecondType,
				m_EffectState3D[nPattern].m_TexMove,
				m_EffectState3D[nPattern].m_TexNum,
				m_EffectState3D[nPattern].AnimCnt,
				m_EffectState3D[nPattern].m_TexSplit,
				(CBillEffect::ANIMPATTERN)m_EffectState3D[nPattern].m_AnimPatternType);

			m_vStraight.emplace_back(pStraight);
		}
		break;
	case(2):	//�Z�킹
		Vectl = pos - Endpos;

		fA = (float)atan2(Vectl.x, Vectl.z);
		fAY = (float)atan2(Vectl.x, Vectl.y);

		Vectlx = (int)Vectl.x;
		Vectly = (int)Vectl.y;
		Vectlz = (int)Vectl.z;

		//�s�b�^��0����rand�Ŏ��ʂ̂�
		if (Vectlx == 0)
		{
			Vectlx = 1;
		}
		if (Vectly == 0)
		{
			Vectly = 1;
		}
		if (Vectlz == 0)
		{
			Vectlz = 1;
		}

		if (Vectlx <= 0)
		{
			Vectlx *= -1;
			bRx = true;
		}
		if (Vectly <= 0)
		{
			Vectly *= -1;
			bRy = true;
		}
		if (Vectlz <= 0)
		{
			Vectlz *= -1;
			bRz = true;
		}
		for (int nCnt = 0; nCnt < m_EffectState3D[nPattern].m_nDensity; nCnt++)
		{
			Rx = float(rand() % Vectlx);
			Ry = float(rand() % Vectly);
			Rz = float(rand() % Vectlz);

			if (bRx == true)
			{
				Rx *= -1;
			}
			if (bRy == true)
			{
				Ry *= -1;
			}
			if (bRz == true)
			{
				Rz *= -1;
			}

			//���������n�_���班��������
			x = float(rand() % m_EffectState3D[nPattern].RandMove) + 1;
			y = float(rand() % m_EffectState3D[nPattern].RandMove) + 1;
			z = float(rand() % m_EffectState3D[nPattern].RandMove) + 1;

			//�傫������l���Z.�Z�Z�̒l��
			x /= 100;
			y /= 100;
			z /= 100;

			//���̔���
			CStraight3D *pStraight = CStraight3D::Create(D3DXVECTOR3(Endpos.x + Rx, Endpos.y + Ry, Endpos.z + Rz),
				D3DXVECTOR3(m_EffectState3D[nPattern].m_fSize, m_EffectState3D[nPattern].m_fAddSizeY, 0.0f),
				D3DXVECTOR3(m_EffectState3D[nPattern].m_fAddSize, m_EffectState3D[nPattern].m_fAddSizeY, 0.0f),
				D3DXVECTOR3(sinf(fA) * x, cosf(fAY) * y, cosf(fA) * z),
				m_EffectState3D[nPattern].m_Col,
				m_EffectState3D[nPattern].m_Changecolor,
				m_EffectState3D[nPattern].nTexture, m_EffectState3D[nPattern].m_nLife, CStraight3D::STRAIGHT, {}, m_EffectState3D[nPattern].Synthetic,
				0,
				(CStraight3D::RAND_PATTEN)0,
				(CStraight3D::POS_PATTERN)3,
				m_EffectState3D[nPattern].m_TexMove,
				m_EffectState3D[nPattern].m_TexNum,
				m_EffectState3D[nPattern].AnimCnt,
				m_EffectState3D[nPattern].m_TexSplit,
				(CBillEffect::ANIMPATTERN)m_EffectState3D[nPattern].m_AnimPatternType);

			m_vStraight.emplace_back(pStraight);
		}
		break;
	case(3):	//�t�B�[���h
		CFieldEffect *pFieldEffect;
		pFieldEffect = CFieldEffect::Create(
			D3DXVECTOR3(m_EffectState3D[nPattern].m_fSize, 0.0f, m_EffectState3D[nPattern].m_fSizeY),
			pos,
			m_EffectState3D[nPattern].m_Col,
			m_EffectState3D[nPattern].m_Changecolor,
			m_EffectState3D[nPattern].m_fRotate,
			m_EffectState3D[nPattern].m_Active,
			m_EffectState3D[nPattern].m_MaxSize,
			m_EffectState3D[nPattern].m_fAddSize + 0.1,
			m_EffectState3D[nPattern].Synthetic,
			m_EffectState3D[nPattern].m_nDensity,
			m_EffectState3D[nPattern].m_nDistance,
			m_EffectState3D[nPattern].m_SecondCol,
			m_EffectState3D[nPattern].m_SecondChangecolor,
			m_EffectState3D[nPattern].nTexture,
			m_EffectState3D[nPattern].m_nLife,
			m_EffectState3D[nPattern].m_ParticleSynthetic,
			m_EffectState3D[nPattern].m_move,
			m_EffectState3D[nPattern].m_fParticleAddSize,
			m_EffectState3D[nPattern].m_fParticleSize,
			m_EffectState3D[nPattern].ParticleTime,
			m_EffectState3D[nPattern].m_fActiveAddSize,
			m_EffectState3D[nPattern].m_FieldTime,
			m_EffectState3D[nPattern].m_fieldCreate,
			m_EffectState3D[nPattern].mCreatePreset,
			(CBillEffect::ANIMPATTERN)m_EffectState3D[nPattern].m_AnimPatternType,
			m_EffectState3D[nPattern].m_nSecondTime);

		m_vFieldEffect.emplace_back(pFieldEffect);

		break;
	case(4):
		a = 1;
		break;
	case(5):
		for (int nCnt = 0; nCnt < m_EffectState3D[nPattern].m_nDensity; nCnt++)
		{
			RandAngle = CIRCLE;

			CRotate3D::Create(
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(pos.x, pos.y, pos.z), {},
				D3DXVECTOR3(m_EffectState3D[nPattern].m_fSize, m_EffectState3D[nPattern].m_fSizeY, 0.0f),
				D3DXVECTOR3(m_EffectState3D[nPattern].m_fAddSize, m_EffectState3D[nPattern].m_fAddSizeY, 0.0f),
				m_EffectState3D[nPattern].m_Col,
				m_EffectState3D[nPattern].m_Changecolor,
				m_EffectState3D[nPattern].m_nDistance,
				m_EffectState3D[nPattern].m_move,
				RandAngle,
				m_EffectState3D[nPattern].m_fRotate,
				m_EffectState3D[nPattern].nTexture,
				m_EffectState3D[nPattern].Synthetic,
				m_EffectState3D[nPattern].m_nLife,
				m_EffectState3D[nPattern].ParticleTime,
				m_EffectState3D[nPattern].m_nSecondTime,
				m_EffectState3D[nPattern].m_MaxSize,
				(CBillEffect::ANIMPATTERN)m_EffectState3D[nPattern].m_AnimPatternType,
				(CRotate3D::EFFECT_TYPE)m_EffectState3D[nPattern].m_nType,
				(CRotate3D::MOVE_TYPE)m_EffectState3D[nPattern].m_SecondType);
		}
		break;
	case(6):
		CSphereEffect::Create(
			pos,
			0.0f,
			m_EffectState3D[nPattern].m_fSize,
			m_EffectState3D[nPattern].nTexture,
			m_EffectState3D[nPattern].m_Col,
			m_EffectState3D[nPattern].m_Changecolor,
			m_EffectState3D[nPattern].m_nLife,
			m_EffectState3D[nPattern].Synthetic,
			m_EffectState3D[nPattern].m_fAddSize,
			m_EffectState3D[nPattern].m_nVtx,
			(CSphereEffect::SPHERE_TYPE)m_EffectState3D[nPattern].m_nType,
			m_EffectState3D[nPattern].m_TexMove,
			m_EffectState3D[nPattern].m_TexNum,
			m_EffectState3D[nPattern].AnimCnt,
			m_EffectState3D[nPattern].m_TexSplit);
		break;
	case(7):
		//for (int nCnt = 0; nCnt < m_EffectState3D[nPattern].m_nDensity; nCnt++)
		//{
		//	CThunderBill::Create(
		//		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		//		D3DXVECTOR3(m_EffectState3D[nPattern].m_fSize, m_EffectState3D[nPattern].m_fSizeY, 0.0f),
		//		D3DXVECTOR3(m_EffectState3D[nPattern].m_fAddSize, m_EffectState3D[nPattern].m_fAddSizeY, 0.0f),
		//		m_EffectState3D[nPattern].m_Col,
		//		m_EffectState3D[nPattern].m_Changecolor,
		//		m_EffectState3D[nPattern].nTexture,
		//		m_EffectState3D[nPattern].m_nLife,
		//		m_EffectState3D[nPattern].m_nDistance,
		//		m_EffectState3D[nPattern].m_TexMove,
		//		m_EffectState3D[nPattern].m_TexNum,
		//		m_EffectState3D[nPattern].AnimCnt,
		//		m_EffectState3D[nPattern].m_TexSplit,
		//		m_EffectState3D[nPattern].m_fHigth,
		//		D3DXVECTOR3(m_EffectState3D[nPattern].m_fParticleSize, m_EffectState3D[nPattern].m_fParticleSize, {}),
		//		m_EffectState3D[nPattern].Synthetic,
		//		(CBillEffect::ANIMPATTERN)m_EffectState3D[nPattern].m_AnimPatternType);
		//}
		break;
	case(8):
		//for (int nCnt = 0; nCnt < m_EffectState3D[nPattern].m_nDensity; nCnt++)
		//{
		//	CBezierBill::Create(
		//		D3DXVECTOR3(m_EffectState3D[nPattern].m_fSize, m_EffectState3D[nPattern].m_fSizeY, 0.0f),
		//		D3DXVECTOR3(m_EffectState3D[nPattern].m_fAddSize, m_EffectState3D[nPattern].m_fAddSizeY, 0.0f),
		//		m_EffectState3D[nPattern].m_Col,
		//		m_EffectState3D[nPattern].m_Changecolor,
		//		m_EffectState3D[nPattern].nTexture,
		//		m_EffectState3D[nPattern].m_nLife,
		//		m_EffectState3D[nPattern].m_TexNum,
		//		m_EffectState3D[nPattern].m_TexMove,
		//		m_EffectState3D[nPattern].AnimCnt,
		//		m_EffectState3D[nPattern].m_TexSplit,
		//		pos,
		//		Endpos,
		//		m_EffectState3D[nPattern].m_move,
		//		m_EffectState3D[nPattern].m_ControlBezier,
		//		{},
		//		m_EffectState3D[nPattern].m_MaxSize,
		//		m_EffectState3D[nPattern].m_SecondCol,
		//		m_EffectState3D[nPattern].m_SecondChangecolor,
		//		m_EffectState3D[nPattern].m_TherdCol,
		//		m_EffectState3D[nPattern].m_TherdChangecolor,
		//		0.0f,
		//		m_EffectState3D[nPattern].m_SecondTex,
		//		m_EffectState3D[nPattern].ParticleTime,
		//		m_EffectState3D[nPattern].m_nDistance,
		//		m_EffectState3D[nPattern].Synthetic,
		//		m_EffectState3D[nPattern].m_ParticleSynthetic,
		//		(CBillEffect::ANIMPATTERN)m_EffectState3D[nPattern].m_AnimPatternType);
		//}
		break;
	case(9):
		//for (int nCnt = 0; nCnt < m_EffectState3D[nPattern].m_nDensity; nCnt++)
		//{

		//	CBulletHoll::Create(D3DXVECTOR3(m_EffectState3D[nPattern].m_fSize, m_EffectState3D[nPattern].m_fSizeY, 0.0f),
		//		D3DXVECTOR3(m_EffectState3D[nPattern].m_fAddSize, m_EffectState3D[nPattern].m_fAddSizeY, 0.0f),
		//		pos,
		//		m_EffectState3D[nPattern].m_Col,
		//		m_EffectState3D[nPattern].m_Changecolor,
		//		m_EffectState3D[nPattern].m_nLife,
		//		m_EffectState3D[nPattern].nTexture,
		//		m_EffectState3D[nPattern].m_TexMove,
		//		m_EffectState3D[nPattern].m_TexNum,
		//		m_EffectState3D[nPattern].AnimCnt,
		//		m_EffectState3D[nPattern].m_TexSplit,
		//		rot,
		//		m_EffectState3D[nPattern].Synthetic,
		//		(CBillEffect::ANIMPATTERN)m_EffectState3D[nPattern].m_AnimPatternType,
		//		m_EffectState3D[nPattern].m_nDistance,
		//		(CBulletHoll::HEIGHT_TYPE)0);
		//}
		break;
	case(10):
		//for (int nCnt = 0; nCnt < m_EffectState3D[nPattern].m_nDensity; nCnt++)
		//{
		//	CFountain::Create(pos,
		//		D3DXVECTOR3(m_EffectState3D[nPattern].m_fSize, m_EffectState3D[nPattern].m_fSizeY, 0.0f),
		//		D3DXVECTOR3(m_EffectState3D[nPattern].m_fAddSize, m_EffectState3D[nPattern].m_fAddSizeY, 0.0f),
		//		m_EffectState3D[nPattern].m_Col,
		//		m_EffectState3D[nPattern].m_Changecolor,
		//		m_EffectState3D[nPattern].nTexture,
		//		m_EffectState3D[nPattern].m_nLife,
		//		m_EffectState3D[nPattern].m_TexNum,
		//		m_EffectState3D[nPattern].m_TexMove,
		//		m_EffectState3D[nPattern].AnimCnt,
		//		m_EffectState3D[nPattern].m_TexSplit,
		//		(CBillEffect::ANIMPATTERN)m_EffectState3D[nPattern].m_AnimPatternType,
		//		m_EffectState3D[nPattern].move3d,
		//		Endpos,
		//		m_EffectState3D[nPattern].m_nDiffusion,
		//		m_EffectState3D[nPattern].Synthetic,
		//		(CFountain::HIGHT_PATTERN)m_EffectState3D[nPattern].m_nType
		//	);
		//}
		break;
	}
}

//=============================================================================
// �v���Z�b�g�̐���
//=============================================================================
CPresetEffect *CPresetEffect::Create(void)
{
	CPresetEffect *pPreset;
	pPreset = new CPresetEffect(PRIORITY_EFFECT);
	if (pPreset)
	{
		pPreset->Init({ 0.0f,0.0f,0.0f });
	}

	return pPreset;
}

//=============================================================================
// ������
//=============================================================================
HRESULT CPresetEffect::Init(D3DXVECTOR3 pos)
{
	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CPresetEffect::Uninit()
{
	if (!m_vStraight.empty())
	{
		m_vStraight.clear();
		m_vStraight.shrink_to_fit();
	}

	if (!m_vFieldEffect.empty())
	{
		m_vFieldEffect.clear();
		m_vFieldEffect.shrink_to_fit();
	}

	Release();
}

//=============================================================================
// �X�V
//=============================================================================
void CPresetEffect::Update()
{

}

//=============================================================================
// �`��
//=============================================================================
void CPresetEffect::Draw()
{

}

//=============================================================================
// �v���Z�b�g�̈ړ�
//=============================================================================
void CPresetEffect::Move(D3DXVECTOR3 move)
{
	if (!m_vStraight.empty())
	{
		for (CStraight3D *pStraight : m_vStraight)
		{
			pStraight->Move(move);
		}
	}

	if (!m_vFieldEffect.empty())
	{
		for (CFieldEffect *pFieldEffect : m_vFieldEffect)
		{
			pFieldEffect->Move(move);
		}
	}
}

#if 0
//�I�[�_�[����(�s����ɂ�����)
//=============================================================================
// �I�[�_�[�Z�b�g(3D)
//=============================================================================
void CPresetEffect::SetOrderPreset(int nDeley, int nPresetNum)
{
	m_Order3D[CLoadEffect::GetFullOrder()][CLoadEffect::GetOrderTotal()].nDeley = nDeley;
	m_Order3D[CLoadEffect::GetFullOrder()][CLoadEffect::GetOrderTotal()].nPresetNum = nPresetNum;

	m_nMaxOrderCount++;

}


//=============================================================================
// �I�[�_�[�Ăяo��(3D)
//=============================================================================
void CPresetEffect::CallOrder3D(int nPattern, D3DXVECTOR3 pos, D3DXVECTOR3 Endpos)
{
	for (int i = 0; i < MAX_ORDER_3D; i++)
	{
		for (int i2 = 0; i2 < m_Order3D[nPattern][i].nPresetNum; i2++)
		{
			m_Order3D[nPattern][i].pos[i2] = pos;
			m_Order3D[nPattern][i].Endpos[i2] = Endpos;
			m_Order3D[nPattern][i].bOne[i2] = false;

		}
	}

}




//=============================================================================
// �I�[�_�[���j���[�̍쐬
//=============================================================================
CPresetEffect *CPresetEffect::CreateOrderMenu(int nDeley, int nPresetNum, int nOrder[MAX_ORDER_3D])
{
	CPresetEffect *pPresetEffect = new CPresetEffect();

	if (pPresetEffect != NULL)
	{
		for (int nCnt = {}; nCnt < MAX_ORDER_3D; nCnt++)
		{
			pPresetEffect->Init({});
			pPresetEffect->SetOrder(nOrder[nCnt], nCnt);
		}
		pPresetEffect->SetOrderPreset(nDeley, nPresetNum);
	}

	return pPresetEffect;
}

//=============================================================================
// �I�[�_�[�̍쐬
//=============================================================================
void CPresetEffect::SetOrder(int nOrder, int nPattern)
{
	m_Order3D[CLoadEffect::GetFullOrder()][CLoadEffect::GetOrderTotal()].m_nOrder[nPattern] = nOrder;
}
#endif