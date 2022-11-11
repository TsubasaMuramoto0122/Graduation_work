//=============================================================================
// ���[�h�����鏈�� [Load.cpp]
// Author : �����G��
//=============================================================================
//*****************************************************************************
// �C���N���[�h�t�@�C��
//***************************************************************************** 
#include "LoadEffect.h"
#include "PresetSetEffect.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define PRESETCALL_TEXT ("data/FILES/PresetCall.txt")

//=============================================================================
// �ÓI
//=============================================================================
int CLoadEffect::m_Total3d = 0;
int CLoadEffect::m_Total2d = 0;

int CLoadEffect::m_OrderTotal = 0;
int CLoadEffect::m_FullOrder = 0;

//CLoadEffect::CALL_PRESET CLoadEffect::m_CallPreset[MAX_PRESET] = {};
std::vector<CLoadEffect::CALL_PRESET> CLoadEffect::m_vCallPreset;

std::map<std::string, int> CLoadEffect::m_Name;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CLoadEffect::CLoadEffect()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CLoadEffect::~CLoadEffect()
{

}

//=============================================================================
// �G�t�F�N�g���̓ǂݍ���
//=============================================================================
void CLoadEffect::EffectStateLoad(const char *aFileName)
{
	FILE *pFile;
	pFile = fopen(aFileName, "r");
	char aFile[256];

	//�ϐ���`
#if 1
	m_Total3d = 0;
	m_Total2d = 0;

	bool bEffectState2D = false;
	bool bEffectState3D = false;

	int nPattern = 0;
	D3DXVECTOR2 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR2 Addmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	int Diffusion = 1;
	int Destroyvec = 0;
	float fSize = 0;
	float fAddSize = 0;
	float fSizeY = 0;
	float fAddSizeY = 0;
	float fRotate = 0;
	D3DCOLORVALUE col;
	D3DCOLORVALUE ChangeColor;
	int nLife = 0;
	int Density = 1;
	int bRandColR = 0;
	int bRandColG = 0;
	int bRandColB = 0;
	int nSynthetic = 0;
	int nTexture = 0;

	float move3d = 0.0f;
	float Addmove3d = 0.0f;
	float MaxSize = 100.0f;
	float ParticleSize = 0.0f;
	float ParticleAddSize = 0.0f;
	int Active = 0;
	D3DCOLORVALUE Secondcol;
	D3DCOLORVALUE SecondChangeColor;
	int SecondSynthetic = 0;
	int TrajectTop = 0;
	int TrajectCur = 0;
	D3DXVECTOR3 Move3D = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	int RandMove = 1;
	int Distance = 1;
	int ParticleTime = 1;
	float fActiveAddSize = 0.0f;
	int FieldTime = 0;
	int FieldCreate = 0;
	int CreatePreset = 0;
	int nSecondTime = 0;
	int nVtx = 0;
	int nType = 0;
	D3DXVECTOR2 TexMove = D3DXVECTOR2(0.0f, 0.0f);
	D3DXVECTOR2 TexNum = D3DXVECTOR2(1.0f, 1.0f);
	int nSecondType = 0;
	D3DXVECTOR2 TexSplit = D3DXVECTOR2(1.0f, 1.0f);
	int nAnimCont = -1;
	float fHigth = 30.0f;
	int AnimPatternType = 0;
	D3DXVECTOR3 ControlBezier = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DCOLORVALUE Therdcol;
	D3DCOLORVALUE TherdChangeColor;
	int SecondTex = 0;
#endif

	if (pFile != NULL)
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]); //fscanf���J��Ԃ��ăt�@�C����ǂݎ���Ă���

			if (bEffectState2D == true)
			{
				if (strcmp(&aFile[0], "PATTERN") == 0)	//�����̃p�^�[��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nPattern);
				}
				if (strcmp(&aFile[0], "ROTATE") == 0)	//��]
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &fRotate);
				}
				if (strcmp(&aFile[0], "MOVE") == 0)	//�ړ���
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f", &move.x, &move.y);
				}
				if (strcmp(&aFile[0], "ADDMOVE") == 0)	//�������Z
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f", &Addmove.x, &Addmove.y);
				}
				if (strcmp(&aFile[0], "DIFFUSION") == 0)	//�g�U��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &Diffusion);
				}
				if (strcmp(&aFile[0], "DESTROYVEC") == 0)	//������x�N�g��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &Destroyvec);
				}
				if (strcmp(&aFile[0], "SIZE") == 0)	//�傫��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &fSize);
				}
				if (strcmp(&aFile[0], "ADDSIZE") == 0)	//�傫�����Z
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &fAddSize);
				}
				if (strcmp(&aFile[0], "COLOR") == 0)	//�J���[
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f %f", &col.r, &col.g, &col.b, &col.a);
				}
				if (strcmp(&aFile[0], "CHANGECOLOR") == 0)	//�J���[�ϓ�
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f %f", &ChangeColor.r, &ChangeColor.g, &ChangeColor.b, &ChangeColor.a);
				}
				if (strcmp(&aFile[0], "LIFE") == 0)	//����
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nLife);
				}
				if (strcmp(&aFile[0], "DENSITY") == 0)	//���x
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &Density);
				}
				if (strcmp(&aFile[0], "COLORRANDR") == 0)	//�J���[�����_����
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &bRandColR);
				}
				if (strcmp(&aFile[0], "COLORRANDG") == 0)	//�J���[�����_����
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &bRandColG);
				}
				if (strcmp(&aFile[0], "COLORRANDB") == 0)	//�J���[�����_����
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &bRandColB);
				}
				if (strcmp(&aFile[0], "SYNTHETIC") == 0)		//����
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nSynthetic);
				}
				if (strcmp(&aFile[0], "TEXTURE") == 0)		//�e�N�X�`��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nTexture);
				}
				if (strcmp(&aFile[0], "DISTANCE") == 0)		//��������
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &Distance);
				}
				if (strcmp(&aFile[0], "TYPE") == 0)	//�^�C�v
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nType);
				}
				if (strcmp(&aFile[0], "HIGTH") == 0)	//����
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &fHigth);
				}
				if (strcmp(&aFile[0], "PARTICLESIZE") == 0)	//�ő�̑傫��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &ParticleSize);
				}
				if (strcmp(&aFile[0], "SECONDCOLOR") == 0)	//�Q�ԃJ���[
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f %f", &Secondcol.r, &Secondcol.g, &Secondcol.b, &Secondcol.a);
				}
				if (strcmp(&aFile[0], "SECONDADDCOLOR") == 0)	//�Q�ԃJ���[�ϓ�
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f %f", &SecondChangeColor.r, &SecondChangeColor.g, &SecondChangeColor.b, &SecondChangeColor.a);
				}
				if (strcmp(&aFile[0], "TEXMOVE") == 0)	//�e�N�X�`���ړ���
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f", &TexMove.x, &TexMove.y);
				}
				if (strcmp(&aFile[0], "TEXNUM") == 0)	//�e�N�X�`���ړ���
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f", &TexNum.x, &TexNum.y);
				}
				if (strcmp(&aFile[0], "TEXSPLIT") == 0)	//�e�N�X�`���ړ���
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f", &TexSplit.x, &TexSplit.y);
				}
				if (strcmp(&aFile[0], "TEXANIMCOUNT") == 0)	//���_��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nAnimCont);
				}
				if (strcmp(&aFile[0], "HIGTH") == 0)	//����
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &fHigth);
				}
				if (strcmp(&aFile[0], "ANIMPATTERNTYPE") == 0)	//�A�j���[�V�����p�^�[���^�C�v
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &AnimPatternType);
				}

			}

			if (bEffectState3D == true)
			{
				if (strcmp(&aFile[0], "PATTERN") == 0)	//�����̃p�^�[��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nPattern);
				}
				if (strcmp(&aFile[0], "ROTATE") == 0)	//��]
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &fRotate);
				}
				if (strcmp(&aFile[0], "MOVE") == 0)	//�ړ���
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &move3d);
				}
				if (strcmp(&aFile[0], "ADDMOVE") == 0)	//�������Z
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &Addmove3d);
				}
				if (strcmp(&aFile[0], "DIFFUSION") == 0)	//�g�U��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &Diffusion);
				}
				if (strcmp(&aFile[0], "SIZE") == 0)	//�傫��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &fSize);
				}
				if (strcmp(&aFile[0], "ADDSIZE") == 0)	//�傫�����Z
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &fAddSize);
				}
				if (strcmp(&aFile[0], "SIZEY") == 0)	//�傫��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &fSizeY);
				}
				if (strcmp(&aFile[0], "ADDSIZEY") == 0)	//�傫�����Z
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &fAddSizeY);
				}

				if (strcmp(&aFile[0], "MAXSIZE") == 0)	//�ő�̑傫��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &MaxSize);
				}
				if (strcmp(&aFile[0], "PARTICLESIZE") == 0)	//�ő�̑傫��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &ParticleSize);
				}
				if (strcmp(&aFile[0], "PARTICLEADDSIZE") == 0)	//�ő�̑傫��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &ParticleAddSize);
				}
				if (strcmp(&aFile[0], "ACTIVE") == 0)	//�ғ�����
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &Active);
				}
				if (strcmp(&aFile[0], "COLOR") == 0)	//�J���[
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f %f", &col.r, &col.g, &col.b, &col.a);
				}
				if (strcmp(&aFile[0], "CHANGECOLOR") == 0)	//�J���[�ϓ�
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f %f", &ChangeColor.r, &ChangeColor.g, &ChangeColor.b, &ChangeColor.a);
				}
				if (strcmp(&aFile[0], "SECONDCOLOR") == 0)	//�Q�ԃJ���[
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f %f", &Secondcol.r, &Secondcol.g, &Secondcol.b, &Secondcol.a);
				}
				if (strcmp(&aFile[0], "SECONDADDCOLOR") == 0)	//�Q�ԃJ���[�ϓ�
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f %f", &SecondChangeColor.r, &SecondChangeColor.g, &SecondChangeColor.b, &SecondChangeColor.a);
				}
				if (strcmp(&aFile[0], "SECONDSYNTHETIC") == 0)		//����
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &SecondSynthetic);
				}
				if (strcmp(&aFile[0], "LIFE") == 0)	//����
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nLife);
				}
				if (strcmp(&aFile[0], "DENSITY") == 0)	//���x
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &Density);
				}
				if (strcmp(&aFile[0], "TRAJECTTOP") == 0)	//���f���P
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &TrajectTop);
				}
				if (strcmp(&aFile[0], "TRAJECTCUR") == 0)	//���f���Q
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &TrajectTop);
				}
				if (strcmp(&aFile[0], "TRAJECTCUR") == 0)	//���f���Q
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &TrajectTop);
				}
				if (strcmp(&aFile[0], "MOVE3D") == 0)	//�R���ړ���
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &Move3D.x, &Move3D.y, &Move3D.z);
				}
				if (strcmp(&aFile[0], "RANDMOVE") == 0)	//�����_���ړ�
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &RandMove);
				}
				if (strcmp(&aFile[0], "COLORRANDR") == 0)	//�J���[�����_����
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &bRandColR);
				}
				if (strcmp(&aFile[0], "COLORRANDG") == 0)	//�J���[�����_����
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &bRandColG);
				}
				if (strcmp(&aFile[0], "COLORRANDB") == 0)	//�J���[�����_����
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &bRandColB);
				}
				if (strcmp(&aFile[0], "SYNTHETIC") == 0)		//����
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nSynthetic);
				}
				if (strcmp(&aFile[0], "TEXTURE") == 0)		//�e�N�X�`��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nTexture);
				}
				if (strcmp(&aFile[0], "DISTANCE") == 0)		//��������
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &Distance);
				}
				if (strcmp(&aFile[0], "PARTICLETIME") == 0)		//�����Ԋu
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &ParticleTime);
				}
				if (strcmp(&aFile[0], "ACTIVEADDSIZE") == 0)	//�傫��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &fActiveAddSize);
				}
				if (strcmp(&aFile[0], "FIELDTIME") == 0)		//��������
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &FieldTime);
				}
				if (strcmp(&aFile[0], "FIELDCREATE") == 0)	//�J���[�����_����
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &FieldCreate);
				}
				if (strcmp(&aFile[0], "CREATEPRESET") == 0)	//�傫��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &CreatePreset);
				}
				if (strcmp(&aFile[0], "SECONDTIME") == 0)	//2�Ԗڂ̎���
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nSecondTime);
				}
				if (strcmp(&aFile[0], "VTX") == 0)	//���_��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nVtx);
				}
				if (strcmp(&aFile[0], "TYPE") == 0)	//���_��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nType);
				}
				if (strcmp(&aFile[0], "TEXMOVE") == 0)	//�e�N�X�`���ړ���
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f", &TexMove.x, &TexMove.y);
				}
				if (strcmp(&aFile[0], "TEXNUM") == 0)	//�e�N�X�`���ړ���
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f", &TexNum.x, &TexNum.y);
				}
				if (strcmp(&aFile[0], "SECONDTYPE") == 0)	//���_��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nSecondType);
				}
				if (strcmp(&aFile[0], "TEXSPLIT") == 0)	//�e�N�X�`���ړ���
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f", &TexSplit.x, &TexSplit.y);
				}
				if (strcmp(&aFile[0], "TEXANIMCOUNT") == 0)	//���_��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nAnimCont);
				}
				if (strcmp(&aFile[0], "HIGTH") == 0)	//����
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &fHigth);
				}
				if (strcmp(&aFile[0], "ANIMPATTERNTYPE") == 0)	//�A�j���[�V�����p�^�[���^�C�v
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &AnimPatternType);
				}
				if (strcmp(&aFile[0], "THERDCOLOR") == 0)	//�p�[�e�B�N���J���[
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f %f", &Therdcol.r, &Therdcol.g, &Therdcol.b, &Therdcol.a);
				}
				if (strcmp(&aFile[0], "THERDADDCOLOR") == 0)	//�p�[�e�B�N���J���[
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f %f", &TherdChangeColor.r, &TherdChangeColor.g, &TherdChangeColor.b, &TherdChangeColor.a);
				}
				if (strcmp(&aFile[0], "SECONDTEX") == 0)	//�p�[�e�B�N���J���[
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &SecondTex);
				}
				if (strcmp(&aFile[0], "CONTROLBEZIER") == 0)	//�p�[�e�B�N���J���[
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &ControlBezier.x, &ControlBezier.y, &ControlBezier.z);
				}

			}
			//�G�t�F�N�g���Z�b�g
			if (strcmp(&aFile[0], "EFFECTSTATE2D") == 0)
			{
				bEffectState2D = true;
			}
			if (strcmp(&aFile[0], "END_EFFECTSTATE2D") == 0)
			{
				bEffectState2D = false;
				//CPresetEffect::SetEffectState2D(nPattern, fRotate, move, Addmove, Diffusion, Destroyvec, fSize, fAddSize, col, ChangeColor, nLife, Density,
				//	(bool)bRandColR, (bool)bRandColG, (bool)bRandColB, nSynthetic, nTexture, (float)Distance,
				//	TexMove, TexNum, AnimPatternType, TexSplit,
				//	nAnimCont, nType, fHigth,ParticleSize, Secondcol, SecondChangeColor);

				m_Total2d++;

			}

			//3D�G�t�F�N�g���Z�b�g
			if (strcmp(&aFile[0], "EFFECTSTATE3D") == 0)
			{
				bEffectState3D = true;
			}
			if (strcmp(&aFile[0], "END_EFFECTSTATE3D") == 0)
			{
				bEffectState3D = false;
				CPresetEffect::SetEffectState3D
				(
					nPattern,			// �G�t�F�N�g�p�^�[��
					fRotate,			// ��]��
					move3d,				// �ړ���
					Addmove3d,			// �ړ����Z��
					Diffusion,			// �g�U��
					fSize,				// �傫���w
					fAddSize,			// �傫�����Z�ʂw
					fSizeY,			    // �傫���x
					fAddSizeY,		    // �傫�����Z�ʂx
					MaxSize, 		    // �ő�傫��
					ParticleSize,	    // �p�[�e�B�N���̑傫��
					ParticleAddSize,    // �p�[�e�B�N���̑傫�����Z��
					Active,			    // �ړ�����
					col,			    // �J���[
					ChangeColor,	    // �J���[�ύX��
					Secondcol, 		    // �Q�Ԗڂ̃J���[
					SecondChangeColor,  // �Q�Ԗڂ̃J���[�ύX��
					SecondSynthetic,    // �Q�Ԗڂ̃G�t�F�N�g�`�捇�����@
					nLife, 			    // �G�t�F�N�g����
					Density, 		    // ���x(��x�ɏo���G�t�F�N�g��)
					TrajectTop,		    // ���f��1
					TrajectCur,		    // ���f��2
					Move3D, 		    // �R�c�ړ���
					RandMove,		    // �ړ������_��
					(bool)bRandColR,    // �����_���J���[�q
					(bool)bRandColG,    // �����_���J���[�f
					(bool)bRandColB,    // �����_���J���[�a
					nSynthetic, 	    // �G�t�F�N�g�������@
					nTexture, 		    // �e�N�X�`���ԍ�
					Distance, 		    // �o���ʒu�͈̔�
					ParticleTime, 	    // �p�[�e�B�N�������Ԋu
					fActiveAddSize,	    // �A�N�e�B�u���̑傫�����Z��
					FieldTime, 		    // �t�B�[���h�̎���
					(bool)FieldCreate,  // �t�B�[���h��������
					CreatePreset,	    // �v���Z�b�g��������
					nSecondTime,	    // �t�B�[���h��������܂ł̎���
					nVtx, 			    // ���_��(���̃G�t�F�N�g�Ɏg��)
					nType, 			    // �G�t�F�N�g�^�C�v
					TexMove,		    // �e�N�X�`���ړ��ʂt�u
					TexNum, 		    // �e�N�X�`���̖����t�u
					nSecondType, 	    // �ړ��̃p�^�[������
					TexSplit,		    // �e�N�X�`��������
					nAnimCont, 		    // �A�j���[�V�����J�E���g
					fHigth, 		    // ����
					AnimPatternType,    // �A�j���[�V�����̃p�^�[���^�C�v
					ControlBezier,	    // �H
					Therdcol,		    // 3�ԖڃJ���[
					TherdChangeColor,   // 3�ԖڃJ���[�ύX��
					SecondTex		    // 2�Ԗڃe�N�X�`��
				);

				// �ϐ���������
				nPattern			= 0;
				fRotate				= 0.0f;
				move3d				= 0.0f;
				Addmove3d			= 0.0f;
				Diffusion			= 0;
				fSize				= 0.0f;
				fAddSize			= 0.0f;
				fSizeY				= 0.0f;
				fAddSizeY			= 0.0f;
				MaxSize				= 0.0f;
				ParticleSize		= 0.0f;
				ParticleAddSize		= 0.0f;
				Active				= 0;
				col					= {};
				ChangeColor			= {};
				Secondcol			= {};
				SecondChangeColor	= {};
				SecondSynthetic		= 0;
				nLife				= 0;
				Density				= 0;
				TrajectTop			= 0;
				TrajectCur			= 0;
				Move3D				= {};
				RandMove			= 0;
				bRandColR			= 0;
				bRandColG			= 0;
				bRandColB			= 0;
				nSynthetic			= 0;
				nTexture			= 0;
				Distance			= 0;
				ParticleTime		= 0;
				fActiveAddSize		= 0.0f;
				FieldTime			= 0;
				FieldCreate			= 0;
				CreatePreset		= 0;
				nSecondTime			= 0;
				nVtx				= 0;
				nType				= 0;
				TexMove				= {};
				TexNum				= {};
				nSecondType			= 0;
				TexSplit			= {};
				nAnimCont			= 0;
				fHigth				= 0.0f;
				AnimPatternType		= 0;
				ControlBezier		= {};
				Therdcol			= {};
				TherdChangeColor	= {};
				SecondTex			= 0;

				m_Total3d++;
			}

			//�I���
			if (strcmp(&aFile[0], "END_SCRIPT") == 0)
			{
				break;
			}
		}
		fclose(pFile);
	}
	CPresetEffect::ResetPattern();
	PresetCallLoad(PRESETCALL_TEXT);
}

//=============================================================================
// �v���Z�b�g�Ăяo���e�L�X�g�̓ǂݍ��� Author:������
//=============================================================================
void CLoadEffect::PresetCallLoad(const char *aFileName)
{
	FILE *pFile;
	pFile = fopen(aFileName, "r");

	char aData[128];

	int nDelay = 0;
	int nPresetNum = 0;
	int nType = 0;
	int nTypeArray = 0;
	int nArray = 0;
	char aName[128];
	D3DXVECTOR3 offset = {};

	//--------------------------------------------------
	// ���������
	//--------------------------------------------------
	if(!m_vCallPreset.empty())
	{
		for (int nCnt = 0; nCnt < m_vCallPreset.size(); nCnt++)
		{
			if (!m_vCallPreset[nCnt].m_nDelay.empty())
			{
				m_vCallPreset[nCnt].m_nDelay.clear();				// �T�C�Y��0�ɂ���
				m_vCallPreset[nCnt].m_nDelay.shrink_to_fit();		// ���������T�C�Y���܂ŏk�߂�(�������J��)
			}

			if (!m_vCallPreset[nCnt].m_nPresetNum.empty())
			{
				m_vCallPreset[nCnt].m_nPresetNum.clear();
				m_vCallPreset[nCnt].m_nPresetNum.shrink_to_fit();
			}

			if (m_vCallPreset[nCnt].m_CallMax != NULL)
			{
				m_vCallPreset[nCnt].m_CallMax = NULL;
			}

			if (!m_vCallPreset[nCnt].m_nType.empty())
			{
				for (int nCnt2 = 0; nCnt2 < m_vCallPreset[nCnt].m_nType.size(); nCnt2++)
				{
					if (!m_vCallPreset[nCnt].m_nType[nCnt2].empty())
					{
						m_vCallPreset[nCnt].m_nType[nCnt2].clear();
						m_vCallPreset[nCnt].m_nType[nCnt2].shrink_to_fit();
					}
				}

				m_vCallPreset[nCnt].m_nType.clear();
				m_vCallPreset[nCnt].m_nType.shrink_to_fit();
			}

			if (!m_vCallPreset[nCnt].m_Offset.empty())
			{
				// map��clear�֐��݂̂Ń���������������
				m_vCallPreset[nCnt].m_Offset.clear();
			}
		}

		m_vCallPreset.clear();
		m_vCallPreset.shrink_to_fit();	// �z�����ɂ���
	}

	if (!m_Name.empty())
	{
		m_Name.clear();
	}

	//--------------------------------------------------
	// �t�@�C���̓ǂݍ���
	//--------------------------------------------------
	if (pFile)
	{
		while (fgets(aData, 128, pFile))					// ��s���ǂݍ���
		{
			fscanf(pFile, "%s", aData);						// ��P��ۑ�
															// �p�^�[�������J�n
			if (strncmp(aData, "PRESETCALL", 11) == 0)
			{
				m_vCallPreset.emplace_back();						// �z���ǉ�

				while (fgets(aData, 128, pFile))					// ��s���ǂݍ���
				{
					fscanf(pFile, "%s", aData);						// ��P��ۑ�

					if (strncmp(aData, "NAME", 5) == 0)
					{
						fscanf(pFile, "%*s%s", aName);			// 
						m_Name[aName] = nArray;					// ���O�Ɣԍ������т���
					}

					if (strncmp(aData, "CALLSET", 8) == 0)
					{
						while (fgets(aData, 128, pFile))					// ��s���ǂݍ���
						{
							fscanf(pFile, "%s", aData);						// ��P��ۑ�

							// �Ăяo���Ă��牽�t���[����ɐ������邩
							if (strncmp(aData, "DELEY", 6) == 0)
							{
								fscanf(pFile, "%*s%d", &nDelay);
								m_vCallPreset[nArray].m_nDelay.emplace_back(nDelay);
							}

							// �����G�t�F�N�g���Ăяo����
							else if (strncmp(aData, "PRESETNUM", 6) == 0)
							{
								fscanf(pFile, "%*s%d", &nPresetNum);
								m_vCallPreset[nArray].m_nPresetNum.emplace_back(nPresetNum);
							}

							// �G�t�F�N�g�̃^�C�v
							else if (strncmp(aData, "TYPE", 6) == 0)
							{
								fscanf(pFile, "%*s");

								// ��̃f�[�^��ǉ�����
								m_vCallPreset[nArray].m_nType.emplace_back();

								// �Ăяo�����������[�v����
								for (int nCnt = 0; nCnt < nPresetNum; nCnt++)
								{
									fscanf(pFile, "%d", &nType);
									m_vCallPreset[nArray].m_nType[nTypeArray].emplace_back(nType);
								}
							}

							// ���炷���W
							else if (strncmp(aData, "OFFSET", 4) == 0)
							{
								fscanf(pFile, "%*s%f%f%f", &offset.x, &offset.y, &offset.z);
								m_vCallPreset[nArray].m_Offset[m_vCallPreset[nArray].m_CallMax] = offset;
							}

							if (strncmp(aData, "END_CALLSET", 12) == 0)
							{
								nTypeArray++;
								m_vCallPreset[nArray].m_CallMax++;	// �Ăяo���ő吔�J�E���g
								break;
							}
						}
					}

					if (strncmp(aData, "END_PRESETCALL", 8) == 0)
					{
						nArray++;		// �z���i�߂�
						nTypeArray = 0;	// �G�t�F�N�g�^�C�v�̔z���������
						break;
					}
				}
			}

			// �ǂݍ��ݏI��
			if (strncmp(aData, "END_SCRIPT", 11) == 0)
			{
				break;
			}
		}
	}

	else
	{
		printf("�ǂݍ��߂܂���ł����B");
	}

	// �t�@�C�������
	fclose(pFile);
}

//����
#if 0
//=============================================================================
// �G�t�F�N�g�I�[�_�[
//=============================================================================
void CLoadEffect::EffectOrder(const char *aFileName)	//�G�t�F�N�g�I�[�_�[
{
	FILE *pFile;
	pFile = fopen(aFileName, "r");
	char aFile[256];

	m_OrderTotal = 0;
	m_FullOrder = 0;

	int nDeley = {};
	int nPatternNum = {};
	int nOrder[MAX_ORDER_3D] = {};

	for (int i2 = 0; i2 < MAX_ORDER_3D; i2++)
	{
		nOrder[i2] = -1;
		nDeley = -1;
		nPatternNum = -1;
	}

	bool bLodeOrder = false;
	bool bLodeFull = false;

	if (pFile != NULL)
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]); //fscanf���J��Ԃ��ăt�@�C����ǂݎ���Ă���
			if (bLodeFull == true)
			{
				if (bLodeOrder == true)
				{
					if (strcmp(&aFile[0], "DELEY") == 0)		//�����f�B���C
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &nDeley);
					}
					if (strcmp(&aFile[0], "PRESETNUM") == 0)		//�����v���Z�b�g
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &nPatternNum);
					}
					if (strcmp(&aFile[0], "ORDER") == 0)		//�����v���Z�b�g
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &nOrder[0], &nOrder[1], &nOrder[2], &nOrder[3], &nOrder[4], &nOrder[5], &nOrder[6], &nOrder[7],
							&nOrder[8], &nOrder[9], &nOrder[10], &nOrder[11], &nOrder[12], &nOrder[13], &nOrder[14], nOrder[15]);
					}
				}
				//�I�[�_�[���
				if (strcmp(&aFile[0], "ORDERSET") == 0)
				{
					bLodeOrder = true;
				}
				if (strcmp(&aFile[0], "END_ORDERSET") == 0)
				{
					bLodeOrder = false;
					CPresetEffect::CreateOrderMenu(nDeley, nPatternNum, nOrder);

					m_OrderTotal++;
				}
			}
			//�I�[�_�[���
			if (strcmp(&aFile[0], "ORDERMENU") == 0)
			{
				bLodeFull = true;
			}

			if (strcmp(&aFile[0], "END_ORDERMENU") == 0)
			{
				bLodeFull = false;


				for (int i = 0; i < 8; i++)
				{
					nOrder[i] = -1;
				}

				m_FullOrder++;
			}


			//�I���
			if (strcmp(&aFile[0], "END_SCRIPT") == 0)
			{
				break;
			}
		}
	}
	fclose(pFile);
	CPresetEffect::ResetOrder();
}

#endif