//=============================================================================
//
// �C�䏈�� [battery.h]
// Author : �O��q��
//
//=============================================================================
#include "battery.h"
#include "manager.h"
#include "sound.h"
#include "motion.h"
#include "renderer.h"

#include "bomb.h"
#include "icebomb.h"
#include "normalbomb.h"
#include "confusionbomb.h"
#include "poisonbomb.h"
#include "firebomb.h"

//=============================================================================
//�}�N��
//=============================================================================
//#define BOMB_SPEED (6.0f)
//#define BOMB_HEIGHT (5.0f)

//�ÓI�����o�ϐ�
CModel *CBattery::m_pOriModel[MAX_BATTERY] = {};

CBattery::CBattery(PRIORITY nPriority) : CObject(nPriority)
{

}

CBattery::~CBattery()
{

}

//����������
HRESULT CBattery::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nTime, float fSpeed, float fHeight)
{
	SetPos(pos);
	SetRot(rot);
	m_nTime = nTime;
	m_nMaxTime = nTime;
	m_fSpeed = fSpeed;
	m_fHeight = fHeight;
	int nCnt;
	for (nCnt = 0; nCnt < MAX_BATTERY; nCnt++)
	{
		if (m_pOriModel[nCnt] != NULL)
		{
			m_pModel[nCnt] = new CModel;
			m_pModel[nCnt]->Copy(m_pOriModel[nCnt]);

			if (m_pOriModel[nCnt]->GetIdxParent() == -1)
			{
				m_pModel[nCnt]->SetParent(NULL);
			}
			else
			{
				m_pModel[nCnt]->SetParent(m_pModel[m_pOriModel[nCnt]->GetIdxParent()]);
			}
		}
	}
	m_pMotion = CMotion::Create(this, CMotion::MOTION_TYPE_BATTERY);
	m_pMotion->SetStop(true);
	m_pMotion->Update(this);

	return S_OK;
}

//�I������
void CBattery::Uninit()
{
	int nCnt;
	for (nCnt = 0; nCnt < MAX_BATTERY; nCnt++)
	{
		if (m_pModel[nCnt] != NULL)
		{
			m_pModel[nCnt]->Uninit();
			m_pModel[nCnt] = NULL;
		}
	}
	CObject::Uninit();
}

//�X�V����
void CBattery::Update()
{
	if (CManager::GetPause() == false && CManager::GetCountdown() == false && CManager::GetGameEnd() == false)
	{
		D3DXVECTOR3 pos = GetPos();
		D3DXVECTOR3 posOld = pos;
		D3DXVECTOR3 rot = GetRot();
		rot.y += 0.07f;
		if (m_nTime > 0)
		{
			m_nTime--;
		}
		else
		{
			RandomBomb(pos, rot);
		}
		SetRot(rot);

		// ���[�V����
		m_pMotion->Update(this);
	}
}

//�`�揈��
void CBattery::Draw()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//pos�Arot�̎擾
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	int nCnt;
	for (nCnt = 0; nCnt < MAX_BATTERY; nCnt++)
	{
		if (m_pModel[nCnt] != NULL)
		{
			m_pModel[nCnt]->Draw();
		}
	}
}

CBattery *CBattery::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nTime, float fSpeed, float fHeight)
{
	CBattery *pBattery;
	pBattery = new CBattery(CScene::PRIORITY_OBJECT);
	if (pBattery != NULL)
	{
		pBattery->Init(pos, rot, nTime, fSpeed, fHeight);
	}
	return pBattery;
}

void CBattery::RandomBomb(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//�������锚�e�Ƀ����_��������������
	int nRand = rand() % CBomb::MAX_BOMB;

	D3DXVECTOR3 BombPos = D3DXVECTOR3(pos.x, pos.y + 20.0f, pos.z);

	nRand = 3;

	//�����Ă�����Ɍ��Ă�悤�ɂ���
	D3DXVECTOR3 move = D3DXVECTOR3(-sinf(rot.y) * m_fSpeed, m_fHeight, -cosf(rot.y) * m_fSpeed);
	switch (nRand)
	{
	case CBomb::BOMB_NORMAL:
		CNormalBomb::Create(BombPos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), move);
		break;
	case CBomb::BOMB_ICE:
		CIceBomb::Create(BombPos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), move);
		break;
	case CBomb::BOMB_FIRE:
		CFireBomb::Create(BombPos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), move);
		break;
	case CBomb::BOMB_POISON:
		CPoisonBomb::Create(BombPos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), move);
		break;
	case CBomb::BOMB_CONFUSION:
		CConfusionBomb::Create(BombPos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), move);
		break;
	default:
		break;
	}
	m_pMotion->SetMotion(0);
	m_nTime = m_nMaxTime;
	CSound::Play(11);
}

//���f���̓ǂݍ���
void CBattery::BatteryLoad()
{
	// �e�L�X�g�t�@�C���̓ǂݍ���
	char cString[256];
	FILE *pFile = NULL;

	pFile = fopen(MOTION_BATTERY_FILE, "r");

	if (pFile != NULL)
	{
		int nCntModel = 0;
		char cFileName[MAX_BATTERY][256];

		while (1)
		{
			fscanf(pFile, "%s", &cString[0]);

			// ���f���̃p�X���擾
			if (strcmp(&cString[0], "MODEL_FILENAME") == 0)
			{
				fscanf(pFile, "%s", &cString[0]);
				fscanf(pFile, "%s", &cFileName[nCntModel][0]);
				nCntModel++;
			}

			// ���f�����ő吔�ɂȂ�����p�X�̓ǂݍ��݂��I��
			if (nCntModel >= MAX_BATTERY)
			{
				nCntModel = 0;
				break;
			}
		}

		int nIdx = 0, nParents = 0;
		D3DXVECTOR3 pos, rot;

		while (1)
		{
			fscanf(pFile, "%s", &cString[0]);

			if (strcmp(&cString[0], "PARTSSET") == 0)	//PARTSSET�̕�����
			{
				// ���f���̃p�[�c��������
				while (1)
				{
					fscanf(pFile, "%s", &cString[0]);

					if (strcmp(&cString[0], "INDEX") == 0) //�C���f�b�N�X�ԍ�
					{
						fscanf(pFile, "%s", &cString[0]);
						fscanf(pFile, "%d", &nIdx);
					}
					if (strcmp(&cString[0], "PARENT") == 0) //�e�̃��f��
					{
						fscanf(pFile, "%s", &cString[0]);
						fscanf(pFile, "%d", &nParents);
					}
					if (strcmp(&cString[0], "POS") == 0) //�ʒu
					{
						// �ʒu���擾����
						fscanf(pFile, "%s", &cString[0]);
						fscanf(pFile, "%f%f%f", &pos.x, &pos.y, &pos.z);
					}
					if (strcmp(&cString[0], "ROT") == 0) //����
					{
						// �������擾����
						fscanf(pFile, "%s", &cString[0]);
						fscanf(pFile, "%f%f%f", &rot.x, &rot.y, &rot.z);
					}
					if (strcmp(&cString[0], "END_PARTSSET") == 0)
					{
						break;
					}
				}

				// ���f���𐶐����A�����ƈʒu��ݒ�
				m_pOriModel[nCntModel] = CModel::Create(&cFileName[nCntModel][0]);
				m_pOriModel[nCntModel]->SetOriRot(rot);
				m_pOriModel[nCntModel]->SetOriPos(pos);

				// �e���f����ݒ�
				m_pOriModel[nCntModel]->SetIdxParent(nParents);

				nCntModel++;
			}

			// ���f�����ő吔�ɂȂ�����z�u���I��
			if (nCntModel >= MAX_BATTERY)
			{
				break;
			}
		}
		fclose(pFile);
	}
}

void CBattery::BatteryUnLoad()
{
	int nCntModel;
	for (nCntModel = 0; nCntModel < MAX_BATTERY; nCntModel++)
	{
		if (m_pOriModel[nCntModel] != NULL)
		{
			m_pOriModel[nCntModel]->Uninit();
			m_pOriModel[nCntModel] = NULL;
		}
	}
}