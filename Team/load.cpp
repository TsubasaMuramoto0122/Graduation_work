//=============================================================================
//
// �ǂݍ��ݏ��� [load.h]
// Author : �O��q��
//
//=============================================================================
#include "load.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "light.h"
#include "fade.h"
#include "camera.h"
#include "scene.h"
//#include "wall.h"
#include "player.h"
#include "sky.h"
#include "sound.h"
#include "object.h"
#include "bomb.h"
#include "plane.h"
#include "mesh_field.h"
#include "mesh_wall.h"
#include "battery.h"
#include "entry.h"

CLoad::CLoad()
{

}

CLoad::~CLoad(void)
{

}

void CLoad::StageLoad(const char *aFileName, CPlayer *pPlayer[4], int *pTime, int *pSnowTime)
{
	FILE *pFile;
	pFile = fopen(aFileName, "r");
	char aFile[256];
	int nNumModel;
	int nCntModel = 0;
	bool bField = false;
	bool bWall = false;
	bool bModel = false;
	bool bLight = false;
	bool bPlayer = false;
	bool bPlayerSet = false;
	bool bBattery = false;
	bool bTime = false;
	int nTime = 0;
	int nStartTime = 0;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	int nTex;
	int nDraw;
	D3DXVECTOR3 size;
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	int nType;
	int nCntLight = 0;
	int nRow;
	int nLine;
	int nSound;
	int nCntPlayer = 0;
	D3DXCOLOR col;
	D3DXVECTOR3 vec;
	D3DXVECTOR2 Tex;
	D3DXVECTOR3 posV;
	D3DXVECTOR3 posR;
	bool bSky = false;
	bool bDraw = true;
	float fSpeed;
	float fHeight;
	float fScroll;
	float fFriction = 1.0f;
	float fMaxSpeed = 1.0f;
	float fGravity = 0.3f;
	D3DXVECTOR3 PlayerPos[4];
	D3DXVECTOR3 PlayerRot[4];
	if (pFile != NULL)
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]); //fscanf���J��Ԃ��ăt�@�C����ǂݎ���Ă���
			if (strcmp(&aFile[0], "NUM_MODEL") == 0) //���f����
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &nNumModel);
			}
			if (strcmp(&aFile[0], "SOUND") == 0) //�����ȁisound�t�@�C���ƘA�����Ă�j
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &nSound);
				if (nSound != -1)
				{
					CSound::Play(nSound);
				}
			}
			if (strcmp(&aFile[0], "MODEL_FILENAME") == 0) //���f����
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%s", &aFile[0]);
				CObject::Load(nCntModel, &aFile[0]);
				nCntModel++;
			}
			if (strcmp(&aFile[0], "FRICTION") == 0) //���C��
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%f", &fFriction);
			}
			if (strcmp(&aFile[0], "MAX_SPEED") == 0) //�ő呬�x
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%f", &fMaxSpeed);
			}
			if (strcmp(&aFile[0], "GRAVITY") == 0) //�d��
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%f", &fGravity);
			}
			if (strcmp(&aFile[0], "SNOW_TIME") == 0) //��~�点��Ԋu
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &nTime);
				*pSnowTime = nTime;
			}
			if (strcmp(&aFile[0], "TIMESET") == 0) //����
			{
				bTime = true;
			}
			if (strcmp(&aFile[0], "END_TIMESET") == 0) //����
			{
				bTime = false;
			}
			if (strcmp(&aFile[0], "FIELDSET") == 0) //�n��
			{
				bField = true;
			}
			if (strcmp(&aFile[0], "END_FIELDSET") == 0) //�n��
			{
				CMeshField::Create(pos, size, rot, nRow, nLine, nTex, bDraw);
				bField = false;
			}
			if (strcmp(&aFile[0], "WALLSET") == 0) //��
			{
				bWall = true;
			}
			if (strcmp(&aFile[0], "END_WALLSET") == 0) //��
			{
				CMeshWall::Create(pos, size, rot, nRow, nLine, nTex, bDraw);
				bWall = false;
			}
			if (strcmp(&aFile[0], "MODELSET") == 0) //�I�u�W�F�N�g
			{
				bModel = true;
			}
			if (strcmp(&aFile[0], "END_MODELSET") == 0) //�I�u�W�F�N�g
			{
				CObject::Create(pos, rot, nType);
				bModel = false;
			}
			if (strcmp(&aFile[0], "BATTERYSET") == 0) //�I�u�W�F�N�g
			{
				bBattery = true;
			}
			if (strcmp(&aFile[0], "END_BATTERYSET") == 0) //�I�u�W�F�N�g
			{
				CBattery::Create(pos, rot, nTime, fSpeed, fHeight, fFriction, fMaxSpeed, fGravity, nStartTime);
				bBattery = false;
			}
			if (strcmp(&aFile[0], "LIGHTSET") == 0) //���C�g
			{
				bLight = true;
			}
			if (strcmp(&aFile[0], "END_LIGHTSET") == 0) //���C�g
			{
				CLight::Create(col, vec, nCntLight);
				nCntLight++;
				bLight = false;
			}
			if (strcmp(&aFile[0], "PLAYER") == 0) //�v���C���[
			{
				bPlayer = true;
			}
			if (strcmp(&aFile[0], "END_PLAYER") == 0) //�v���C���[
			{
				// �v���C���[�̃X�^�[�g�ʒu�������_���Őݒ�
				for (nCntPlayer = 0; nCntPlayer < 4; nCntPlayer++)
				{
					int nRandom = rand() % 4;
					D3DXVECTOR3 posSave = PlayerPos[nCntPlayer];
					PlayerPos[nCntPlayer] = PlayerPos[nRandom];
					PlayerPos[nRandom] = posSave;

					D3DXVECTOR3 rotSave = PlayerRot[nCntPlayer];
					PlayerRot[nCntPlayer] = PlayerRot[nRandom];
					PlayerRot[nRandom] = rotSave;
				}

				//�v���C���[�̐���
				for (nCntPlayer = 0; nCntPlayer < 4; nCntPlayer++)
				{
					pPlayer[nCntPlayer] = CPlayer::Create(PlayerPos[nCntPlayer], PlayerRot[nCntPlayer], 
					(CPlayer::PLAYER_TYPE)nCntPlayer, CEntry::GetStandby(nCntPlayer), fFriction, fMaxSpeed, fGravity, false);
				}
				bPlayer = false;
			}
			if (strcmp(&aFile[0], "SKYSET") == 0) //��
			{
				bSky = true;
			}
			if (strcmp(&aFile[0], "END_SKYSET") == 0) //��
			{
				//CSky::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.00002f, CPlane::GetTexture(0));
				bSky = false;
			}
			if (bTime == true)
			{
				if (strcmp(&aFile[0], "TIME") == 0) //���Ԃ̐ݒ�
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nTime);
					*pTime = nTime;
				}
			}
			if (bField == true)
			{
				if (strcmp(&aFile[0], "POS") == 0) //�ꏊ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
				}
				if (strcmp(&aFile[0], "ROT") == 0) //�p�x
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &rot.x, &rot.y, &rot.z);
					rot.x = rot.x / 180.0f * D3DX_PI;
					rot.y = rot.y / 180.0f * D3DX_PI;
					rot.z = rot.z / 180.0f * D3DX_PI;
				}
				if (strcmp(&aFile[0], "SIZE") == 0) //�傫��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &size.x, &size.y, &size.z);
				}
				if (strcmp(&aFile[0], "BLOCK") == 0) //������
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d %d", &nRow, &nLine);
				}
				if (strcmp(&aFile[0], "TEXTYPE") == 0) //�e�N�X�`��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nTex);
				}
				if (strcmp(&aFile[0], "DRAW") == 0) //�`�悷�邩(-1���ƕ`�悵�Ȃ�����ȊO���ƕ`�悷��)
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nDraw);
					if (nDraw == -1)
					{
						bDraw = false;
					}
					else
					{
						bDraw = true;
					}
				}
			}
			if (bWall == true)
			{
				if (strcmp(&aFile[0], "POS") == 0) //�ꏊ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
				}
				if (strcmp(&aFile[0], "ROT") == 0) //��]
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &rot.x, &rot.y, &rot.z);
					rot.x = rot.x / 180.0f * D3DX_PI;
					rot.y = rot.y / 180.0f * D3DX_PI;
					rot.z = rot.z / 180.0f * D3DX_PI;

				}
				if (strcmp(&aFile[0], "SIZE") == 0) //�傫��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &size.x, &size.y, &size.z);
				}
				//if (strcmp(&aFile[0], "ROW") == 0) //�c�̕�����
				//{
				//	fscanf(pFile, "%s", &aFile[0]);
				//	fscanf(pFile, "%d", &nRow);
				//}
				//if (strcmp(&aFile[0], "LINE") == 0) //���̕�����
				//{
				//	fscanf(pFile, "%s", &aFile[0]);
				//	fscanf(pFile, "%d", &nLine);
				//}
				if (strcmp(&aFile[0], "BLOCK") == 0) //������
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d %d", &nRow, &nLine);
				}
				if (strcmp(&aFile[0], "TEXTYPE") == 0) //�e�N�X�`��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nTex);
				}
				if (strcmp(&aFile[0], "DRAW") == 0) //�`�悷�邩(-1���ƕ`�悵�Ȃ�����ȊO���ƕ`�悷��)
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nDraw);
					if (nDraw == -1)
					{
						bDraw = false;
					}
					else
					{
						bDraw = true;
					}
				}
			}
			if (bModel == true)
			{
				if (strcmp(&aFile[0], "TYPE") == 0) //���f���̎��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nType);
				}
				if (strcmp(&aFile[0], "POS") == 0) //���f���̏ꏊ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
				}
				if (strcmp(&aFile[0], "ROT") == 0) //���f���̕���
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &rot.x, &rot.y, &rot.z);
					rot.x = rot.x / 180.0f * D3DX_PI;
					rot.y = rot.y / 180.0f * D3DX_PI;
					rot.z = rot.z / 180.0f * D3DX_PI;
				}
			}
			if (bBattery == true)
			{
				if (strcmp(&aFile[0], "POS") == 0) //���f���̏ꏊ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
				}
				if (strcmp(&aFile[0], "ROT") == 0) //���f���̕���
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &rot.x, &rot.y, &rot.z);
					rot.x = rot.x / 180.0f * D3DX_PI;
					rot.y = rot.y / 180.0f * D3DX_PI;
					rot.z = rot.z / 180.0f * D3DX_PI;
				}
				if (strcmp(&aFile[0], "START_TIME") == 0) //�ŏ����˂���܂ł̃J�E���g
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nStartTime);
				}
				if (strcmp(&aFile[0], "TIME") == 0) //���ˊԊu
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nTime);
				}
				if (strcmp(&aFile[0], "SPEED") == 0) //�ł��o�����e�̐��������̑���
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &fSpeed);
				}
				if (strcmp(&aFile[0], "HEIGHT") == 0) //�ł��o�����e�̍���
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &fHeight);
				}
			}
			if (bLight == true)
			{
				if (strcmp(&aFile[0], "DIRECTION") == 0) //���̕���
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &vec.x, &vec.y, &vec.z);
				}
				if (strcmp(&aFile[0], "DIFFUSE") == 0) //���̐F
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &col.r, &col.g, &col.b);
					col.a = 1.0f;
				}
			}
			if (bSky == true)
			{
				if (strcmp(&aFile[0], "TEXTYPE") == 0) //�e�N�X�`��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nTex);
				}
				if (strcmp(&aFile[0], "MOVE") == 0) //����
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &fScroll);
				}
			}
			if (bPlayer == true)
			{
				if (strcmp(&aFile[0], "PLAYERSET") == 0) //�v���C���[
				{
					bPlayerSet = true;
				}
				if (strcmp(&aFile[0], "END_PLAYERSET") == 0) //�v���C���[
				{
					nCntPlayer++;
					bPlayerSet = false;
				}
				if (bPlayerSet == true)
				{
					if (strcmp(&aFile[0], "POS") == 0) //���f���̏ꏊ
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f", &PlayerPos[nCntPlayer].x, &PlayerPos[nCntPlayer].y, &PlayerPos[nCntPlayer].z);
					}
					if (strcmp(&aFile[0], "ROT") == 0) //���f���̕���
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f", &PlayerRot[nCntPlayer].x, &PlayerRot[nCntPlayer].y, &PlayerRot[nCntPlayer].z);
						PlayerRot[nCntPlayer].x = PlayerRot[nCntPlayer].x / 180.0f * D3DX_PI;
						PlayerRot[nCntPlayer].y = PlayerRot[nCntPlayer].y / 180.0f * D3DX_PI;
						PlayerRot[nCntPlayer].z = PlayerRot[nCntPlayer].z / 180.0f * D3DX_PI;
					}
				}
			}
			if (strcmp(&aFile[0], "END_SCRIPT") == 0) //�I���
			{
				break;
			}
		}
		fclose(pFile);
	}
}

void CLoad::TutorialStageLoad(const char *aFileName, CPlayer *pPlayer[4])
{
	FILE *pFile;
	pFile = fopen(aFileName, "r");
	char aFile[256];
	int nNumModel;
	int nCntModel = 0;
	bool bField = false;
	bool bWall = false;
	bool bModel = false;
	bool bLight = false;
	bool bPlayer = false;
	bool bPlayerSet = false;
	bool bBattery = false;
	bool bTime = false;
	int nTime = 0;
	int nStartTime = 0;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	int nTex;
	int nDraw;
	D3DXVECTOR3 size;
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	int nType;
	int nCntLight = 0;
	int nRow;
	int nLine;
	int nSound;
	int nCntPlayer = 0;
	D3DXCOLOR col;
	D3DXVECTOR3 vec;
	D3DXVECTOR2 Tex;
	D3DXVECTOR3 posV;
	D3DXVECTOR3 posR;
	bool bSky = false;
	bool bDraw = true;
	float fSpeed;
	float fHeight;
	float fScroll;
	float fFriction = 1.0f;
	float fMaxSpeed = 1.0f;
	float fGravity = 0.3f;
	D3DXVECTOR3 PlayerPos[4];
	D3DXVECTOR3 PlayerRot[4];
	if (pFile != NULL)
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]); //fscanf���J��Ԃ��ăt�@�C����ǂݎ���Ă���
			if (strcmp(&aFile[0], "NUM_MODEL") == 0) //���f����
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &nNumModel);
			}
			if (strcmp(&aFile[0], "SOUND") == 0) //�����ȁisound�t�@�C���ƘA�����Ă�j
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &nSound);
				if (nSound != -1)
				{
					CSound::Play(nSound);
				}
			}
			if (strcmp(&aFile[0], "MODEL_FILENAME") == 0) //���f����
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%s", &aFile[0]);
				CObject::Load(nCntModel, &aFile[0]);
				nCntModel++;
			}
			if (strcmp(&aFile[0], "FRICTION") == 0) //���C��
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%f", &fFriction);
			}
			if (strcmp(&aFile[0], "MAX_SPEED") == 0) //�ő呬�x
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%f", &fMaxSpeed);
			}
			if (strcmp(&aFile[0], "GRAVITY") == 0) //�d��
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%f", &fGravity);
			}
			if (strcmp(&aFile[0], "FIELDSET") == 0) //�n��
			{
				bField = true;
			}
			if (strcmp(&aFile[0], "END_FIELDSET") == 0) //�n��
			{
				CMeshField::Create(pos, size, rot, nRow, nLine, nTex, bDraw);
				bField = false;
			}
			if (strcmp(&aFile[0], "WALLSET") == 0) //��
			{
				bWall = true;
			}
			if (strcmp(&aFile[0], "END_WALLSET") == 0) //��
			{
				CMeshWall::Create(pos, size, rot, nRow, nLine, nTex, bDraw);
				bWall = false;
			}
			if (strcmp(&aFile[0], "MODELSET") == 0) //�I�u�W�F�N�g
			{
				bModel = true;
			}
			if (strcmp(&aFile[0], "END_MODELSET") == 0) //�I�u�W�F�N�g
			{
				CObject::Create(pos, rot, nType);
				bModel = false;
			}
			if (strcmp(&aFile[0], "BATTERYSET") == 0) //�I�u�W�F�N�g
			{
				bBattery = true;
			}
			if (strcmp(&aFile[0], "END_BATTERYSET") == 0) //�I�u�W�F�N�g
			{
				CBattery::Create(pos, rot, nTime, fSpeed, fHeight, fFriction, fMaxSpeed, fGravity, nStartTime);
				bBattery = false;
			}
			if (strcmp(&aFile[0], "LIGHTSET") == 0) //���C�g
			{
				bLight = true;
			}
			if (strcmp(&aFile[0], "END_LIGHTSET") == 0) //���C�g
			{
				CLight::Create(col, vec, nCntLight);
				nCntLight++;
				bLight = false;
			}
			if (strcmp(&aFile[0], "PLAYER") == 0) //�v���C���[
			{
				bPlayer = true;
			}
			if (strcmp(&aFile[0], "END_PLAYER") == 0) //�v���C���[
			{
				// �v���C���[�̃X�^�[�g�ʒu�������_���Őݒ�
				for (nCntPlayer = 0; nCntPlayer < 4; nCntPlayer++)
				{
					int nRandom = rand() % 4;
					D3DXVECTOR3 posSave = PlayerPos[nCntPlayer];
					PlayerPos[nCntPlayer] = PlayerPos[nRandom];
					PlayerPos[nRandom] = posSave;

					D3DXVECTOR3 rotSave = PlayerRot[nCntPlayer];
					PlayerRot[nCntPlayer] = PlayerRot[nRandom];
					PlayerRot[nRandom] = rotSave;
				}

				//�v���C���[�̐���
				for (nCntPlayer = 0; nCntPlayer < 4; nCntPlayer++)
				{
					pPlayer[nCntPlayer] = CPlayer::Create(PlayerPos[nCntPlayer], PlayerRot[nCntPlayer],
						(CPlayer::PLAYER_TYPE)nCntPlayer, true, fFriction, fMaxSpeed, fGravity, true);
				}
				bPlayer = false;
			}
			if (strcmp(&aFile[0], "SKYSET") == 0) //��
			{
				bSky = true;
			}
			if (strcmp(&aFile[0], "END_SKYSET") == 0) //��
			{
				//CSky::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.00002f, CPlane::GetTexture(0));
				bSky = false;
			}
			if (bField == true)
			{
				if (strcmp(&aFile[0], "POS") == 0) //�ꏊ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
				}
				if (strcmp(&aFile[0], "ROT") == 0) //�p�x
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &rot.x, &rot.y, &rot.z);
					rot.x = rot.x / 180.0f * D3DX_PI;
					rot.y = rot.y / 180.0f * D3DX_PI;
					rot.z = rot.z / 180.0f * D3DX_PI;
				}
				if (strcmp(&aFile[0], "SIZE") == 0) //�傫��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &size.x, &size.y, &size.z);
				}
				if (strcmp(&aFile[0], "BLOCK") == 0) //������
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d %d", &nRow, &nLine);
				}
				if (strcmp(&aFile[0], "TEXTYPE") == 0) //�e�N�X�`��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nTex);
				}
				if (strcmp(&aFile[0], "DRAW") == 0) //�`�悷�邩(-1���ƕ`�悵�Ȃ�����ȊO���ƕ`�悷��)
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nDraw);
					if (nDraw == -1)
					{
						bDraw = false;
					}
					else
					{
						bDraw = true;
					}
				}
			}
			if (bWall == true)
			{
				if (strcmp(&aFile[0], "POS") == 0) //�ꏊ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
				}
				if (strcmp(&aFile[0], "ROT") == 0) //��]
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &rot.x, &rot.y, &rot.z);
					rot.x = rot.x / 180.0f * D3DX_PI;
					rot.y = rot.y / 180.0f * D3DX_PI;
					rot.z = rot.z / 180.0f * D3DX_PI;

				}
				if (strcmp(&aFile[0], "SIZE") == 0) //�傫��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &size.x, &size.y, &size.z);
				}
				if (strcmp(&aFile[0], "BLOCK") == 0) //������
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d %d", &nRow, &nLine);
				}
				if (strcmp(&aFile[0], "TEXTYPE") == 0) //�e�N�X�`��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nTex);
				}
				if (strcmp(&aFile[0], "DRAW") == 0) //�`�悷�邩(-1���ƕ`�悵�Ȃ�����ȊO���ƕ`�悷��)
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nDraw);
					if (nDraw == -1)
					{
						bDraw = false;
					}
					else
					{
						bDraw = true;
					}
				}
			}
			if (bModel == true)
			{
				if (strcmp(&aFile[0], "TYPE") == 0) //���f���̎��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nType);
				}
				if (strcmp(&aFile[0], "POS") == 0) //���f���̏ꏊ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
				}
				if (strcmp(&aFile[0], "ROT") == 0) //���f���̕���
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &rot.x, &rot.y, &rot.z);
					rot.x = rot.x / 180.0f * D3DX_PI;
					rot.y = rot.y / 180.0f * D3DX_PI;
					rot.z = rot.z / 180.0f * D3DX_PI;
				}
			}
			if (bBattery == true)
			{
				if (strcmp(&aFile[0], "POS") == 0) //���f���̏ꏊ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
				}
				if (strcmp(&aFile[0], "ROT") == 0) //���f���̕���
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &rot.x, &rot.y, &rot.z);
					rot.x = rot.x / 180.0f * D3DX_PI;
					rot.y = rot.y / 180.0f * D3DX_PI;
					rot.z = rot.z / 180.0f * D3DX_PI;
				}
				if (strcmp(&aFile[0], "START_TIME") == 0) //�ŏ����˂���܂ł̃J�E���g
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nStartTime);
				}
				if (strcmp(&aFile[0], "TIME") == 0) //���ˊԊu
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nTime);
				}
				if (strcmp(&aFile[0], "SPEED") == 0) //�ł��o�����e�̐��������̑���
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &fSpeed);
				}
				if (strcmp(&aFile[0], "HEIGHT") == 0) //�ł��o�����e�̍���
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &fHeight);
				}
			}
			if (bLight == true)
			{
				if (strcmp(&aFile[0], "DIRECTION") == 0) //���̕���
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &vec.x, &vec.y, &vec.z);
				}
				if (strcmp(&aFile[0], "DIFFUSE") == 0) //���̐F
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &col.r, &col.g, &col.b);
					col.a = 1.0f;
				}
			}
			if (bSky == true)
			{
				if (strcmp(&aFile[0], "TEXTYPE") == 0) //�e�N�X�`��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nTex);
				}
				if (strcmp(&aFile[0], "MOVE") == 0) //����
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &fScroll);
				}
			}
			if (bPlayer == true)
			{
				if (strcmp(&aFile[0], "PLAYERSET") == 0) //�v���C���[
				{
					bPlayerSet = true;
				}
				if (strcmp(&aFile[0], "END_PLAYERSET") == 0) //�v���C���[
				{
					nCntPlayer++;
					bPlayerSet = false;
				}
				if (bPlayerSet == true)
				{
					if (strcmp(&aFile[0], "POS") == 0) //���f���̏ꏊ
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f", &PlayerPos[nCntPlayer].x, &PlayerPos[nCntPlayer].y, &PlayerPos[nCntPlayer].z);
					}
					if (strcmp(&aFile[0], "ROT") == 0) //���f���̕���
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f", &PlayerRot[nCntPlayer].x, &PlayerRot[nCntPlayer].y, &PlayerRot[nCntPlayer].z);
						PlayerRot[nCntPlayer].x = PlayerRot[nCntPlayer].x / 180.0f * D3DX_PI;
						PlayerRot[nCntPlayer].y = PlayerRot[nCntPlayer].y / 180.0f * D3DX_PI;
						PlayerRot[nCntPlayer].z = PlayerRot[nCntPlayer].z / 180.0f * D3DX_PI;
					}
				}
			}
			if (strcmp(&aFile[0], "END_SCRIPT") == 0) //�I���
			{
				break;
			}
		}
		fclose(pFile);
	}
}

void CLoad::SoundLoad(const char *aFileName)
{
	FILE *pFile;
	pFile = fopen(aFileName, "r");
	char aFile[256];
	char aSoundName[64];
	int nLoop;
	int nCntSound = 0;
	int nSound = 0;
	bool bSet = false;
	if (pFile != NULL)
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]); //fscanf���J��Ԃ��ăt�@�C����ǂݎ���Ă���
			if (strcmp(&aFile[0], "NUM_SOUND") == 0) //�����������邩
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &nSound);
				CSound::SetSoundNum(nSound);
			}
			if (strcmp(&aFile[0], "SOUND_SET") == 0)
			{
				bSet = true;
			}
			if (strcmp(&aFile[0], "END_SOUND_SET") == 0)
			{
				CSound::SetParamData(&aSoundName[0], nLoop, nCntSound);
				bSet = false;
				nCntSound++;
			}
			if (bSet == true)
			{
				if (strcmp(&aFile[0], "NAME") == 0) //���O
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%s", &aSoundName[0]);
				}
				if (strcmp(&aFile[0], "LOOP") == 0) //���[�v���邩���Ȃ���
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nLoop);
				}
			}
			if (strcmp(&aFile[0], "END_SCRIPT") == 0) //�I���
			{
				break;
			}
		}
		fclose(pFile);
	}
}

void CLoad::BombsLoad(const char *aFileName)
{
	FILE *pFile;
	pFile = fopen(aFileName, "r");
	char aFile[256];
	int nCntModel = 0;
	int nSound;
	bool bBomb = false;
	if (pFile != NULL)
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]); //fscanf���J��Ԃ��ăt�@�C����ǂݎ���Ă���
			if (strcmp(&aFile[0], "BOMB_SET") == 0)
			{
				bBomb = true;
			}
			if (strcmp(&aFile[0], "END_BOMB_SET") == 0)
			{
				nCntModel++;
				bBomb = false;
			}
			if (bBomb == true)
			{
				if (strcmp(&aFile[0], "FILENAME") == 0) //���f����
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%s", &aFile[0]);
					CBomb::LoadModel(nCntModel, &aFile[0]);
				}
				if (strcmp(&aFile[0], "SOUND") == 0) //�����ԍ�
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nSound);
					CBomb::LoadSound(nCntModel, nSound);
				}
			}
			if (strcmp(&aFile[0], "END_SCRIPT") == 0) //�I���
			{
				break;
			}
		}
		fclose(pFile);
	}
}