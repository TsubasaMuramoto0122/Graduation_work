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
#include "camera.h"
#include "motion.h"
#include "control_player.h"
#include "shadow.h"
#include "sound.h"
#include "collision_sphere.h"
#include "mesh_field.h"
#include "mesh_wall.h"
#include "life.h"
#include "game.h"
#include "cpu.h"
#include "presetdelayset.h"
#include "realshadow.h"
#include "playerui.h"
#include "playericon.h"
#include "playerice.h"
#include "billboard.h"

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define PLAYER_BEGIN_LIFE		(550)	// �������C�t
#define INVINCIBLE_TIME			(210)	// ���G����
#define ICE_TIME				(210)	// �X�̏�Ԉُ�̎���
#define POISON_TIME				(300)	// �ł̏�Ԉُ�̎���
#define CONFUSION_TIME			(500)	// �����̏�Ԉُ�̎���
#define POISON_DAMAGE			(3)		// �ł̃X���b�v�_���[�W
#define PUSH_INVALID_TIME		(180)	// �����ꂽ��A�Ăщ������悤�ɂȂ�܂ł̎���
#define POISON_COUNT			(15)	// �ł̃X���b�v�_���[�W������܂ł̎���
#define POISON_BUBBLE_COUNT		(14)	// �ł̖A�����Ԋu

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
int CPlayer::m_nSurviveTime[PLAYER_TYPE_MAX] = {};

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
	m_pMotion = NULL;
	m_pControl = NULL;
	m_pCollision = NULL;
	m_pLife = NULL;
	m_pDelaySet = NULL;
	m_state = PLAYER_STATE_NORMAL;
	m_badState = PLAYER_BAD_STATE_NONE;
	m_type = PLAYER_TYPE_MAX;
	m_bLand = false;
	m_bInvDamage = false;
	m_bInvSliding = false;
	m_bPressed = false;
	m_bDraw = true;
	m_nLife = 0;
	m_nInvincibleTime = 0;
	m_nBadStateTime = 0;
	m_nPoisonCount = 0;
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
HRESULT CPlayer::Init(D3DXVECTOR3 pos)
{
	// �ϐ��̏�����
	m_pos = pos;
	m_posOld = pos;
	m_move = m_pControl->GetMove();
	m_state = PLAYER_STATE_NORMAL;
	m_bLand = false;
	m_bInvDamage = false;
	m_bInvSliding = false;
	m_bPressed = false;
	m_bDraw = true;
	m_nLife = PLAYER_BEGIN_LIFE;
	m_nInvincibleTime = 0;
	m_nBadStateTime = 0;
	m_nPoisonCount = 0;
	m_nPressCount = 0;

	// ���f����������
	ModelCreate(m_type);

	// �ϐ��̐ݒ�
	SetRot(m_rot);
	SetPos(m_pos);

	// �̂ɃR���W����(�v���C���[����)������
	m_pCollision = CCollisionSphere::Create(m_pos, m_size.x, 16, 16, CCollisionSphere::COLLISION_S_TYPE::COLLISION_S_TYPE_PLAYER, -1.0f, 0.0f);
	m_pCollision->SetNumPlayer(m_type);

	m_fHeadHeight = m_apModel[1]->GetMaxSize().y;

	// ���C�t�A���[�V�����̐���
	D3DXVECTOR2 lifePos = D3DXVECTOR2(0.0f, 0.0f);
	switch (m_type)
	{
	case PLAYER_TYPE_1P:
		lifePos = D3DXVECTOR2(150.0f, 100.0f);
		CUI::Create(D3DXVECTOR2(lifePos.x + 50.0f, lifePos.y - 60.0f), D3DXVECTOR2(70.0f, 60.0f), 8, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pMotion = CMotion::Create(this, CMotion::MOTION_TYPE_P1);
		m_pPlayerUI = CPlayerUI::Create(42, m_fHeadHeight);
		m_pPlayerIcon = CPlayerIcon::Create(D3DXVECTOR2(lifePos.x - 45.0f, lifePos.y - 60.0f), D3DXVECTOR2(60.0f, 60.0f), 37, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		break;
	case PLAYER_TYPE_2P:
		lifePos = D3DXVECTOR2(400.0f, 100.0f);
		CUI::Create(D3DXVECTOR2(lifePos.x + 50.0f, lifePos.y - 60.0f), D3DXVECTOR2(70.0f, 60.0f), 9, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pMotion = CMotion::Create(this, CMotion::MOTION_TYPE_P2);
		m_pPlayerUI = CPlayerUI::Create(43, m_fHeadHeight);
		m_pPlayerIcon = CPlayerIcon::Create(D3DXVECTOR2(lifePos.x - 45.0f, lifePos.y - 60.0f), D3DXVECTOR2(60.0f, 60.0f), 38, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		break;
	case PLAYER_TYPE_3P:
		lifePos = D3DXVECTOR2(SCREEN_WIDTH - 400.0f, 100.0f);
		CUI::Create(D3DXVECTOR2(lifePos.x + 50.0f, lifePos.y - 60.0f), D3DXVECTOR2(70.0f, 60.0f), 10, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pMotion = CMotion::Create(this, CMotion::MOTION_TYPE_P3);
		m_pPlayerUI = CPlayerUI::Create(44, m_fHeadHeight);
		m_pPlayerIcon = CPlayerIcon::Create(D3DXVECTOR2(lifePos.x - 45.0f, lifePos.y - 60.0f), D3DXVECTOR2(60.0f, 60.0f), 39, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		break;
	case PLAYER_TYPE_4P:
		lifePos = D3DXVECTOR2(SCREEN_WIDTH - 150.0f, 100.0f);
		CUI::Create(D3DXVECTOR2(lifePos.x + 50.0f, lifePos.y - 60.0f), D3DXVECTOR2(70.0f, 60.0f), 11, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pMotion = CMotion::Create(this, CMotion::MOTION_TYPE_P4);
		m_pPlayerUI = CPlayerUI::Create(45, m_fHeadHeight);
		m_pPlayerIcon = CPlayerIcon::Create(D3DXVECTOR2(lifePos.x - 45.0f, lifePos.y - 60.0f), D3DXVECTOR2(60.0f, 60.0f), 40, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		break;
	default:
		break;
	}
	m_pLife = CLifeUI::Create(lifePos, D3DXVECTOR2(200.0f, 50.0f));

	//m_pShadow = CShadow::Create(D3DXVECTOR3(m_size.x * 0.5f, 0.0f, m_size.z * 0.5f), pos, 1);

	m_pMotion->Update(this);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPlayer::Uninit(void)
{
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER_MODEL; nCntPlayer++)
	{
		if (m_apModel[nCntPlayer] != NULL)
		{
			m_apModel[nCntPlayer]->Uninit();
			m_apModel[nCntPlayer] = NULL;
		}
	}

	if (m_pControl != NULL)
	{
		m_pControl->Uninit();
		m_pControl = NULL;
	}

	if (m_pCollision != NULL)
	{
		m_pCollision = NULL;
	}

	if (m_pDelaySet != NULL)
	{
		m_pDelaySet = NULL;
	}

	if (m_pLife != NULL)
	{
		m_pLife = NULL;
	}

	if (m_pMotion != NULL)
	{
		m_pMotion = NULL;
	}

	if (m_pPlayerIce != NULL)
	{
		m_pPlayerIce = NULL;
	}

	/*if (m_pShadow != NULL)
	{
		m_pShadow = NULL;
	}*/

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
		if (m_pControl != NULL)
		{
			m_pControl->Update(this);
		}
		if (CManager::GetPause() == false)
		{
			// �ʒu�̎擾
			D3DXVECTOR3 pos = GetPos();
			m_pos = pos;
			m_posOld = m_pos;

			// 1�t���[���O�̈ʒu�ݒ�
			SetPosOld(m_posOld);

			// �ړ�����
			Move();

			// �����ꂽ��
			if (m_bPressed == true)
			{
				// �J�E���g�𑝂₷
				m_nPressCount++;

				if (m_nPressCount >= PUSH_INVALID_TIME)
				{
					m_nPressCount = 0;
					m_bPressed = false;
				}
			}

			// ���̃R���W�����ƐڐG�������̏���
			TouchCollision();

			// ��Ԉُ�̏���
			BadState(m_badState);

			// �ړ��ʔ��f
			m_pos += m_move;

			// ���[�V����
			m_pMotion->Update(this);

			// �ʒu���f
			SetPos(m_pos);
			//m_pShadow->MoveY(D3DXVECTOR3(m_pos.x, 0.0f, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

			// ���n��Ԃ�������
			m_bLand = false;

			// �s�k�̏�Ԃ���Ȃ�������
			if (GetState() != PLAYER_STATE_DEFEAT)
			{
				m_Wall = CMeshWall::Collision(this);
				// �ǂƂ̓����蔻��
				if (m_Wall.x < D3DX_PI)
				{
					m_bWall = true;
				}
				else
				{
					m_bWall = false;
				}
			}

			if (m_bLand == false)
			{
				// �n�ʂƂ̓����蔻��
				m_bLand = CMeshField::Collision(this);
			}
			else
			{
				// ���n������Y�����̈ړ��ʂ�0��
				m_move.y = 0.0f;
			}

			// �ʒu�擾
			m_pos = GetPos();

			// �v���C���[�Ƃ̉��o����
			Push(this);

			// ���G���̏���
			Invincible();

			// �R���W�����̒Ǐ]
			D3DXVECTOR3 collisionPos = D3DXVECTOR3(m_pos.x, m_pos.y + GetRadius(), m_pos.z);
			m_pCollision->SetPosCollision(collisionPos);

			// �G�t�F�N�g�̒Ǐ]
			if (m_pDelaySet != NULL)
			{
				//m_pDelaySet->Move(m_pos - m_posOld);
			}

			//�v���C���[UI�̒Ǐ]
			D3DXVECTOR3 HeadPos = D3DXVECTOR3(m_apModel[1]->GetMatrix()._41, m_apModel[1]->GetMatrix()._42, m_apModel[1]->GetMatrix()._43);
			m_pPlayerUI->SetPos(HeadPos);

			//HP�Q�[�W�̐ݒ�
			m_pLife->SetLifeBar(m_nLife, PLAYER_BEGIN_LIFE);
		}
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

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���f���̕`��
	for (int nCntModel = 0; nCntModel < MAX_PLAYER_MODEL; nCntModel++)
	{
		if (m_bDraw == true)
		{
			m_apModel[nCntModel]->Draw();
		}
	}
}

void CPlayer::ZTexDraw()
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
		if (m_bDraw == true)
		{
			m_apModel[nCntModel]->ZTexDraw();
		}
	}
}

//=============================================================================
// ��������
//=============================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, PLAYER_TYPE type, bool bPlayer, float fFriction, float fMaxSpeed, float fGravity, bool bTutorial)
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
			if(bPlayer == true)
			{
				// �v���C���[����̃N���X�𐶐�
				pPlayer->m_pControl = CControlPlayer::Create(fFriction, fMaxSpeed, fGravity);
			}
			else
			{
				// CPU�̃N���X�𐶐�
				pPlayer->m_pControl = CCPU::Create(fFriction, fMaxSpeed, fGravity);
			}

			// �ϐ��̏�����
			pPlayer->m_rot = rot;
			pPlayer->m_type = type;

			pPlayer->m_bPlayer = bPlayer;
			pPlayer->m_bTutorial = bTutorial;

			// ����������
			pPlayer->Init(pos);
		}
	}

	return pPlayer;
}

//=============================================================================
// ���f����������
//=============================================================================
void CPlayer::ModelCreate(PLAYER_TYPE type)
{
	// �e�L�X�g�t�@�C���̓ǂݍ���
	char cString[256];
	FILE *pFile = NULL;

	switch (type)
	{
	case PLAYER_TYPE_1P:
		pFile = fopen("data/FILES/Motions/motion_p1.txt", "r");
		break;
	case PLAYER_TYPE_2P:
		pFile = fopen("data/FILES/Motions/motion_p2.txt", "r");
		break;
	case PLAYER_TYPE_3P:
		pFile = fopen("data/FILES/Motions/motion_p3.txt", "r");
		break;
	case PLAYER_TYPE_4P:
		pFile = fopen("data/FILES/Motions/motion_p4.txt", "r");
		break;
	default:
		break;
	}

	if (pFile != NULL)
	{
		int nCntModel = 0;
		char cFileName[MAX_PLAYER_MODEL][256];

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
			if (nCntModel >= MAX_PLAYER_MODEL)
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
				m_apModel[nCntModel] = CModel::Create(&cFileName[nCntModel][0]);
				m_apModel[nCntModel]->SetRot(rot);
				m_apModel[nCntModel]->SetPos(pos);

				// �e���f����ݒ�
				if (nParents == -1)
				{
					// -1 �Ȃ�e���f������
					m_apModel[nCntModel]->SetParent(NULL);
				}
				else
				{
					// -1 �ȊO�Ȃ�e�q�t��
					m_apModel[nCntModel]->SetParent(m_apModel[nParents]);
				}

				nCntModel++;
			}

			// ���f�����ő吔�ɂȂ�����z�u���I��
			if (nCntModel >= MAX_PLAYER_MODEL)
			{
				break;
			}
		}
		fclose(pFile);
	}

	m_size.x = 50.0f;
	m_size.y = 50.0f;
	m_size.z = 50.0f;
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
		m_move = m_pControl->GetMove();
	}
}

//=============================================================================
// �R���W�������g�������o����
//=============================================================================
void CPlayer::Push(CPlayer *pPlayer)
{
	//�I�u�W�F�N�g��������|�C���^
	CScene *pObject = NULL;
	CScene *pSaveObject = NULL;

	//�擪�̃|�C���^����
	pObject = pObject->GetTopObj(CScene::PRIORITY_CHARA);

	while (pObject != NULL)
	{
		//���݂̃I�u�W�F�N�g�̃|�C���^��ۑ�
		pSaveObject = pObject;

		if (pObject->GetObjType() == CScene::OBJECTTYPE_PLAYER)
		{
			//�v���C���[�ɃL���X�g
			CPlayer *pOtherPlayer = NULL;
			pOtherPlayer = (CPlayer*)pObject;

			// �����ȊO�̃I�u�W�F�N�g�Ȃ�
			if (pObject != this)
			{
				D3DXVECTOR3 posPlayer = pOtherPlayer->GetPos();			// ���̃v���C���[�̈ʒu���擾
				float fSizePlayer = pOtherPlayer->GetRadius();			// ���̃v���C���[�̃T�C�Y�̔��a���擾
				float totalSize = (GetRadius() + fSizePlayer) * 0.75f;	// �v���C���[2�l�̔��a�̍��v

				// �����ƌ������v�Z
				float fDistance = sqrtf((pPlayer->m_pos.x - posPlayer.x) * (pPlayer->m_pos.x - posPlayer.x) + (pPlayer->m_pos.y - posPlayer.y) * (pPlayer->m_pos.y - posPlayer.y) + (pPlayer->m_pos.z - posPlayer.z) * (pPlayer->m_pos.z - posPlayer.z));
				float fRot = (float)atan2((posPlayer.x - pPlayer->m_pos.x), (posPlayer.z - pPlayer->m_pos.z)) - D3DX_PI;

				// �������v���C���[2�l�̔��a�̍��v��菬����������
				if (fDistance <= totalSize)
				{
					pPlayer->m_pos.x = posPlayer.x + (sinf(fRot) * totalSize);
					pPlayer->m_pos.z = posPlayer.z + (cosf(fRot) * totalSize);

					// �Ώۂ̈ʒu��ݒ�
					SetPos(pPlayer->m_pos);
				}
			}
		}
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}
}

//=============================================================================
// ���̃R���W�����ƐڐG�������̏���
//=============================================================================
void CPlayer::TouchCollision(void)
{
	// �s�k�̏�Ԃ���Ȃ�������
	if (GetState() != PLAYER_STATE_DEFEAT)
	{
		// ������Ă��Ȃ����A���̃v���C���[�̍U���ɓ��������u�ԂȂ�
		if (m_bPressed == false && m_pCollision->GetTouchCollision(CCollisionSphere::COLLISION_S_TYPE_ATTACK) == true)
		{
			// ���炩�̖��G��Ԃ���Ȃ��Ȃ�
			if (m_bInvDamage == false && m_bInvSliding == false)
			{
				// �_���[�W���[�V����(4)�ɂ���
				m_pMotion->SetMotion(4);

				// ��Ԃ�<�������>�ɐݒ�
				SetState(PLAYER_STATE_BLOWAWAY);

				// �X�̏�Ԉُ������
				if (GetBadState() == PLAYER_BAD_STATE_ICE)
				{
					SetBadState(PLAYER_BAD_STATE_NONE);
				}

				// �����ꂽ��Ԃɂ���
				m_bPressed = true;

				// �U�����Ă����v���C���[�̕�������������
				m_rot.y = m_pCollision->GetPlayerRot() - D3DX_PI;

				//�p�x������Ȃ��悤�ɂ���
				if (m_rot.y < -D3DX_PI)
				{
					m_rot.y += D3DX_PI * 2.0f;
				}

				// Y�����ւ̈ړ��ʂ����Z�b�g���A�W�����v������
				m_move.y = PLAYER_KNOCKBACK_JUMP;
			}
		}
		// ���̃v���C���[�̍U�� �܂��� �����ɓ��������u�ԂȂ�
		else if (m_pCollision->GetTouchCollision(CCollisionSphere::COLLISION_S_TYPE_EXPLOSION) == true ||
				m_pCollision->GetTouchCollision(CCollisionSphere::COLLISION_S_TYPE_POISON) == true ||
				m_pCollision->GetTouchCollision(CCollisionSphere::COLLISION_S_TYPE_CONFUSION) == true)
		{
			// ���炩�̖��G��Ԃ���Ȃ��Ȃ�
			if (m_bInvDamage == false && m_bInvSliding == false)
			{
				// �_���[�W���[�V����(4)�ɂ���
				m_pMotion->SetMotion(4);

				// ��Ԃ�<�������>�ɐݒ�
				SetState(PLAYER_STATE_BLOWAWAY);

				// �X�̏�Ԉُ������
				if (GetBadState() == PLAYER_BAD_STATE_ICE)
				{
					SetBadState(PLAYER_BAD_STATE_NONE);
				}

				// �ʏ�̔����ɓ������Ă�����
				if (m_pCollision->GetTouchCollision(CCollisionSphere::COLLISION_S_TYPE_EXPLOSION) == true)
				{
					// ���C�t�����炷
					m_nLife -= 100;

					// ���C�t���c���Ă�����
					if (m_nLife > 0)
					{
						// ��_���[�W�ɂ�閳�G�ɂ���
						m_bInvDamage = true;

						//�A�C�R���U��������
						m_pPlayerIcon->SetDamage(true);
					}

					// �Ώۂ̃R���W�����̕�������������
					m_rot.y = m_pCollision->GetObjectiveRot();
				}
				// �ł̔����ɓ������Ă�����
				else if (m_pCollision->GetTouchCollision(CCollisionSphere::COLLISION_S_TYPE_POISON) == true)
				{
					// ���C�t�����炷
					m_nLife -= 100;

					// ���C�t���c���Ă�����
					if (m_nLife > 0)
					{
						// ��_���[�W�ɂ�閳�G�ɂ���
						m_bInvDamage = true;

						//�A�C�R���U��������
						m_pPlayerIcon->SetDamage(true);
					}

					SetBadState(PLAYER_BAD_STATE_POISON);

					// �Ώۂ̃R���W�����̕�������������
					m_rot.y = m_pCollision->GetObjectiveRot();
				}
				// �����̔����ɓ������Ă�����
				else if (m_pCollision->GetTouchCollision(CCollisionSphere::COLLISION_S_TYPE_CONFUSION) == true)
				{
					// ���C�t�����炷
					m_nLife -= 100;

					// ���C�t���c���Ă�����
					if (m_nLife > 0)
					{
						// ��_���[�W�ɂ�閳�G�ɂ���
						m_bInvDamage = true;

						//�A�C�R���U��������
						m_pPlayerIcon->SetDamage(true);

						// �����̌��ʉ����Đ�
						CSound::Play(6);
					}
					SetBadState(PLAYER_BAD_STATE_CONFUSION);

					// �Ώۂ̃R���W�����̕�������������
					m_rot.y = m_pCollision->GetObjectiveRot();
				}

				// ���C�t���Ȃ��Ȃ�����
				if (m_nLife <= 0)
				{
					// �s�k�̏�Ԃɐݒ�
					SetState(PLAYER_STATE_DEFEAT);

					// �J�����̌������擾���A�v���C���[�̌������w��
					CCamera *pCamera = CManager::GetRenderer()->GetCamera();
					float rotCamera = pCamera->GetRotY();
					m_rot.y = rotCamera;

					// Y�����ւ̈ړ��ʂ����Z�b�g���A�W�����v������
					m_move.y = PLAYER_DEFEATKNOCKBACK_JUMP;
					//m_move.y += PLAYER_DEFEATKNOCKBACK_JUMP;
				}
				// ���C�t������Ȃ�ʏ�̋���
				else
				{
					// Y�����ւ̈ړ��ʂ����Z�b�g���A�W�����v������
					m_move.y = PLAYER_KNOCKBACK_JUMP;
					//m_move.y += PLAYER_KNOCKBACK_JUMP;
				}
			}
		}
		else if (m_pCollision->GetTouchCollision(CCollisionSphere::COLLISION_S_TYPE_ICE) == true)
		{
			// ���炩�̖��G��Ԃ���Ȃ��Ȃ�
			if (m_bInvDamage == false && m_bInvSliding == false)
			{
				SetBadState(PLAYER_BAD_STATE_ICE);
			}
		}
		else if (m_pCollision->GetTouchCollision(CCollisionSphere::COLLISION_S_TYPE_POISON_FIELD) == true)
		{
			// ���炩�̖��G��Ԃ���Ȃ��Ȃ�
			if (m_bInvDamage == false && m_bInvSliding == false)
			{
				SetBadState(PLAYER_BAD_STATE_POISON);
			}
		}
		else
		{
			// �R���W�����ɓ������Ă��Ȃ��Ȃ�ʏ�̏�Ԃɖ߂�
			SetState(PLAYER_STATE_NORMAL);
		}
	}
}

//=============================================================================
// ���G���̏���
//=============================================================================
void CPlayer::Invincible(void)
{
	// ��_���[�W�ɂ�閳�G�̊�
	if (m_bInvDamage == true)
	{
		// ���G���Ԃ̃J�E���g�𑝂₷
		m_nInvincibleTime++;

		// ���G���Ԓ��A�_�ł�����
		if (m_nInvincibleTime % 8 == 0 || m_nInvincibleTime % 8 == 1)
		{
			m_bDraw = false;
		}
		else
		{
			m_bDraw = true;
		}

		// ���G���Ԃ��I�������
		if (m_nInvincibleTime >= INVINCIBLE_TIME)
		{
			// ���G��Ԃ�����
			m_bInvDamage = false;
			m_bDraw = true;

			// ���G���Ԃ����Z�b�g
			m_nInvincibleTime = 0;
		}
		if (m_pCollision != NULL)
		{
			if (m_bInvDamage == true || m_bInvSliding == true)
			{
				m_pCollision->SetColor(D3DCOLOR_RGBA(255, 255, 0, 153));
			}
			else
			{
				m_pCollision->SetColor(D3DCOLOR_RGBA(255, 255, 255, 153));
			}
		}
	}
}

//=============================================================================
// ��Ԉُ�̏���
//=============================================================================
void CPlayer::BadState(PLAYER_BAD_STATE state)
{
	switch (state)
	{
		// �X
	case PLAYER_BAD_STATE_ICE:
		// �J�E���g�𑝂₷
		m_nBadStateTime++;

		m_move.x = 0.0f;
		m_move.z = 0.0f;

		// ���[�V�������~�߂�
		m_pMotion->SetStop(true);

		// ��莞�Ԃ��o������
		if (m_nBadStateTime >= ICE_TIME)
		{
			// ��Ԉُ��������
			SetBadState(PLAYER_BAD_STATE_NONE);

			// ���[�V�����𓮂���
			m_pMotion->SetStop(false);

			// ���Ԃ����Z�b�g
			m_nBadStateTime = 0;
		}
		break;
		// ��
	case PLAYER_BAD_STATE_POISON:
		// �J�E���g�𑝂₷
		m_nBadStateTime++;

		if (m_nBadStateTime % POISON_BUBBLE_COUNT == 0)
		{
			//�A�o��
			PoisonBubble();
		}

		// <�������>�̏�ԈȊO�œ����Ă���ꍇ
		if (m_state != PLAYER_STATE_BLOWAWAY && m_move.x != 0.0f || m_move.z != 0.0f)
		{
			// �J�E���g�𑝂₷
			m_nPoisonCount++;

			// ��莞�Ԃ��o�߂���
			if (m_nPoisonCount >= POISON_COUNT)
			{
				// ���C�t���Ń_���[�W���ゾ������
				if (m_nLife > POISON_DAMAGE)
				{
					// ���C�t�����炷
					m_nLife -= POISON_DAMAGE;
				}
				// ���C�t��1��荂��
				else if (m_nLife > 1)
				{
					// ���C�t��1�ɂ���
					m_nLife = 1;
				}
				m_nPoisonCount = 0;
			}
		}

		// ��莞�Ԃ��o������
		if (m_nBadStateTime >= POISON_TIME)
		{
			// ��Ԉُ��������
			SetBadState(PLAYER_BAD_STATE_NONE);

			// ���Ԃ����Z�b�g
			m_nBadStateTime = 0;
			m_nPoisonCount = 0;
		}
		break;
		// ����
	case PLAYER_BAD_STATE_CONFUSION:
		// �J�E���g�𑝂₷
		m_nBadStateTime++;

		// ��莞�Ԃ��o������
		if (m_nBadStateTime >= CONFUSION_TIME)
		{
			// ��Ԉُ������
			SetBadState(PLAYER_BAD_STATE_NONE);

			// �����̌��ʉ����~�߂�
			CSound::Stop(6);

			// ���Ԃ����Z�b�g
			m_nBadStateTime = 0;
		}
		break;

	default:
		// �J�E���^�[�����Z�b�g
		m_nBadStateTime = 0;
		m_nPoisonCount = 0;
		break;
	}
}

//================================================
// ��ԋ߂��v���C���[�T��(CPU�p)
//================================================
CPlayer *CPlayer::SearchPlayer(CScene *pScene)
{
	//�I�u�W�F�N�g��������|�C���^
	CScene *pObject = NULL;
	//�I�u�W�F�N�g����ۑ�����|�C���^�ϐ�
	CScene *pSaveObject = NULL;

	float fShortDistance = 9999999.0f;
	CPlayer *pSavePlayer = NULL;

	D3DXVECTOR3 pos = pScene->GetPos();			//�v���C���[�̈ʒu

	//�擪�̃|�C���^����
	pObject = pObject->GetTopObj(CScene::PRIORITY_CHARA);

	while (pObject != NULL)
	{
		//���݂̃I�u�W�F�N�g�̃|�C���^��ۑ�
		pSaveObject = pObject;

		if (pObject->GetObjType() == CScene::OBJECTTYPE_PLAYER && pScene != pObject)
		{
			CPlayer *pPlayer = (CPlayer*)pObject;

			if (pPlayer->GetDeath() == false && pPlayer->m_state != PLAYER_STATE_DEFEAT && pPlayer->GetState() != PLAYER_STATE_BLOWAWAY)
			{
				D3DXVECTOR3 Bombpos = pPlayer->GetPos();	//�Ώۂ̈ʒu

				float fDistance = sqrtf(powf(Bombpos.x - pos.x, 2.0f) + powf(Bombpos.z - pos.z, 2.0f));
				if (fShortDistance > fDistance)
				{
					pSavePlayer = pPlayer;
					fShortDistance = fDistance;
				}
			}
		}
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}
	return pSavePlayer;
}

void CPlayer::SetBadState(PLAYER_BAD_STATE state)
{
	//�����G�t�F�N�g
	if (m_badState != PLAYER_BAD_STATE_CONFUSION && state == PLAYER_BAD_STATE_CONFUSION)
	{
		CPresetDelaySet::Create("EDDY", m_pos, this);
	}
	m_badState = state;
	//�X����
	if (state == PLAYER_BAD_STATE_ICE)
	{
		if (m_pPlayerIce == NULL)
		{
			m_pPlayerIce = CPlayerIce::Create(m_apModel[0]->GetMatrix());
		}
	}
	else if (m_pPlayerIce != NULL)
	{
		m_pPlayerIce->Uninit();
		m_pPlayerIce = NULL;
	}
}

//�ł̖A�o��
void CPlayer::PoisonBubble()
{
	D3DXMATRIX mtx = m_apModel[1]->GetMatrix();
	D3DXVECTOR3 pos = m_apModel[1]->GetPos();
	D3DXMATRIX mtxTrans, mtxWorld; //�p�[�c�p�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxParent; //�e�̃}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y + m_fHeadHeight, pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	//�Z�o�����e���[���h�}�g���b�N�X�Ɛe(��)�̃}�g���b�N�X���|�����킹��
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtx);

	CBillboard::Create(D3DXVECTOR3(mtxWorld._41, mtxWorld._42, mtxWorld._43), D3DXVECTOR3(0.3f, 0.7f, 0.0f), D3DXVECTOR3(16.0f, 16.0f, 0.0f), 6, D3DXCOLOR(1.0f, 0.5f, 1.0f, 0.6f), 70);
}