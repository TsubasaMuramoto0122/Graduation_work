//=============================================================================
// �v���C���[���� [player.cpp]
// Authore : Kusakari Kakeru
//=============================================================================
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "player.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
//#include "model_single.h"
//#include "model_load.h"
#include "camera.h"
//#include "motion_player.h"
#include "control_player.h"
#include "shadow.h"
#include "sound.h"
//#include "collision_sphere.h"
//#include "life.h"

//=============================================================================
// �R���X�g���N�^
//============================================================================
CPlayer::CPlayer(PRIORITY Priority) : CScene3D::CScene3D(Priority)
{
	// �ϐ��̃N���A
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	for (int nCntModel = 0; nCntModel < MAX_PLAYER_MODEL; nCntModel++)
	{
		m_apModel[nCntModel] = NULL;
	}
	m_pParent = NULL;
	//m_pMotionPlayer = NULL;
	m_pControl = NULL;
	m_bLand = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, PLAYER_TYPE type)
{
	// �ϐ��̏�����
	m_rot = rot;
	m_pos = pos;
	m_posOld = pos;
	//m_move = m_pControl->GetMove();
	m_bLand = false;

	// ���f����������
	ModelCreate(type);

	// �ϐ��̐ݒ�
	SetRot(m_rot);
	SetPos(m_pos);

	// ���[�V�����̐���
	//m_pMotionPlayer = CMotionPlayer::Create(this);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPlayer::Uninit(void)
{
	for(int nCntPlayer = 0; nCntPlayer < MAX_PLAYER_MODEL; nCntPlayer++)
	{
		if (m_apModel[nCntPlayer] != NULL)
		{
			m_apModel[nCntPlayer]->Uninit();
			m_apModel[nCntPlayer] = NULL;
		}
	}

	// �I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CPlayer::Update(void)
{
	if (this != NULL)
	{
		// 1�t���[���O�̈ʒu��ݒ�
		m_posOld = m_pos;

		// �ړ�����
		Move();

		// �ړ��ʔ��f
		m_pos += m_move;

		// ���[�V����
		//m_pMotionPlayer->Update(this);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CPlayer::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���f���̕`��
	for (int nCntModel = 0; nCntModel < MAX_PLAYER_MODEL; nCntModel++)
	{
		m_apModel[nCntModel]->Draw();
	}

}

//=============================================================================
// ��������
//=============================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, PLAYER_TYPE type)
{
	// �C���X�^���X�̐���
	CPlayer *pPlayer = NULL;

	// �k���`�F�b�N
	if (pPlayer == NULL)
	{
		// �N���X�̐���
		pPlayer = new CPlayer;
		if (pPlayer != NULL)
		{
			// �v���C���[����̃N���X�𐶐�
			pPlayer->m_pControl = CControlPlayer::Create();

			// �ϐ��̏�����
			pPlayer->m_rot = rot;

			// ����������
			pPlayer->Init(pos, rot, type);
		}
	}

	return pPlayer;
}

//=============================================================================
// ���f����������
//=============================================================================
void CPlayer::ModelCreate(PLAYER_TYPE type)
{
	//// �e�L�X�g�ۑ��p�̕ϐ�
	//char cString[256];

	//// �e�L�X�g�t�@�C���̓ǂݍ���
	//FILE *pFile = fopen("data/TEXT/motion_player.txt", "r");

	//if (pFile != NULL)
	//{
	//	// ���f���̎��
	//	int nModelType = (int)CModelLoad::MODEL_TYPE_PLAYER_WAIST;

	//	// �z�u���̓ǂݍ���
	//	for (int nCntMotion = 0; nCntMotion < MAX_PLAYER_MODEL; nCntMotion++, nModelType++)
	//	{
	//		// �e�L�X�g�t�@�C���̍Ō�(NULL)�܂œǂݍ���
	//		while (fgets(cString, 256, pFile) != NULL)
	//		{
	//			// �������ۑ�
	//			fscanf(pFile, "%s", cString);

	//			// ������̒���"PARTSSET"����������
	//			if (strncmp("PARTSSET", cString, 9) == 0)
	//			{
	//				break;
	//			}
	//		}

	//		while (fgets(cString, 256, pFile) != NULL)
	//		{
	//			// �������ۑ�
	//			fscanf(pFile, "%s", cString);

	//			// ������̒���"INDEX"����������
	//			if (strncmp("INDEX", cString, 6) == 0)
	//			{
	//				int nIdx, nParents;
	//				D3DXVECTOR3 pos, rot;

	//				//�C���f�b�N�X�ԍ��Ɛe�q�t���̔ԍ����擾
	//				fscanf(pFile, "%s%d%*s%*s", cString, &nIdx);
	//				fscanf(pFile, "%s%*s%d%*s%*s%*s", cString, &nParents);

	//				//�ʒu�E��]�����擾
	//				fscanf(pFile, "%s%f%f%f", cString, &pos.x, &pos.y, &pos.z);
	//				fscanf(pFile, "%s%*s%f%f%f", cString, &rot.x, &rot.y, &rot.z);

	//				// ���f���̐���
	//				m_apModel[nCntMotion] = CModel::Create(NULL);

	//				// �e�̐ݒ�(-1���w�肳��Ă����ꍇ�A�e�q�t���͖����Ƃ���NULL�Őݒ肵�Ă���)
	//				if (nParents == -1)
	//				{
	//					m_apModel[nCntMotion]->SetParent(NULL);
	//				}
	//				else
	//				{
	//					m_apModel[nCntMotion]->SetParent(m_apModel[nParents]);
	//				}

	//				break;
	//			}
	//		}

	//		while (fgets(cString, 256, pFile) != NULL)
	//		{
	//			// �������ۑ�
	//			fscanf(pFile, "%s", cString);

	//			// ������̒���"END_PARTSSET"���������炻���ŏI��
	//			if (strncmp("END_PARTSSET", cString, 13) == 0)
	//			{
	//				break;
	//			}
	//		}
	//	}
	//	// �t�@�C�������
	//	fclose(pFile);
	//}

	switch (type)
	{
	case PLAYER_TYPE_1P:
		// ���f���̐���
		m_apModel[0] = CModel::Create("data/MODEL/kirby.x");
		break;
	}

	D3DXVECTOR3 VtxMax, VtxMin;
	VtxMax = m_apModel[0]->GetMaxSize();
	VtxMin = m_apModel[0]->GetMinSize();

	float fRadius = (VtxMax.x - VtxMin.x) / 2;
	if (fRadius < (VtxMax.y - VtxMin.y) / 2)
	{
		fRadius = (VtxMax.y - VtxMin.y) / 2;
	}
	if (fRadius < (VtxMax.z - VtxMin.z) / 2)
	{
		fRadius = (VtxMax.z - VtxMin.z) / 2;
	}
}

//=============================================================================
// �ړ�����
//=============================================================================
void CPlayer::Move(void)
{
	// �k���`�F�b�N
	if (m_pControl != NULL)
	{
		// �v���C���[����̃N���X�Ƀv���C���[�̃|�C���^�����A�ړ��ʂ��擾
		m_pControl->Update(this);
		m_move = m_pControl->GetMove();
	}
}

//=============================================================================
// �����ݒ菈��
//=============================================================================
void CPlayer::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
// �����擾����
//=============================================================================
D3DXVECTOR3 CPlayer::GetRot(void)
{
	return m_rot;
}

//=============================================================================
// 1�t���[���O�̈ʒu�擾����
//=============================================================================
D3DXVECTOR3 CPlayer::GetPosOld(void)
{
	return m_posOld;
}


//=============================================================================
// ���n�ݒ菈��
//=============================================================================
void CPlayer::SetLand(bool bLand)
{
	m_bLand = bLand;
}

//=============================================================================
// ���n�擾����
//=============================================================================
bool CPlayer::GetLand(void)
{
	return m_bLand;
}

//=============================================================================
// ���f�����̈ʒu�ݒ菈��
//=============================================================================
void CPlayer::SetModelPos(int nCntModel, D3DXVECTOR3 pos)
{
	m_apModel[nCntModel]->SetPos(pos);
}

//=============================================================================
// ���f�����̈ʒu�擾����
//=============================================================================
D3DXVECTOR3 CPlayer::GetModelPos(int nCntModel)
{
	return m_apModel[nCntModel]->GetPos();
}

//=============================================================================
// ���f�����̌����ݒ菈��
//=============================================================================
void CPlayer::SetModelRot(int nCntModel, D3DXVECTOR3 rot)
{
	m_apModel[nCntModel]->SetRot(rot);
}

//=============================================================================
// ���f�����̌����擾����
//=============================================================================
D3DXVECTOR3 CPlayer::GetModelRot(int nCntModel)
{
	return m_apModel[nCntModel]->GetRot();
}

////=============================================================================
//// �v���C���[�̃��[�V�����擾����
////=============================================================================
//CMotionPlayer *CPlayer::GetMotionPlayer(void)
//{
//	return m_pMotionPlayer;
//}
//
////=============================================================================
//// �v���C���[�̃��f���擾����
////=============================================================================
//CModel *CPlayer::GetModel(int nCntModel)
//{
//	return m_apModel[nCntModel];
//}