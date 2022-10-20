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
//#include "motion_player.h"
#include "control_player.h"
#include "shadow.h"
#include "sound.h"
#include "collision_sphere.h"
#include "mesh_field.h"
#include "mesh_wall.h"
#include "life.h"

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define PLAYER_BEGIN_LIFE	(100)	// �������C�t
#define INVINCIBLE_TIME		(160)	// ���G����
#define ICE_TIME			(210)	// �X�̏�Ԉُ�̎���
#define POISON_TIME			(300)	// �ł̏�Ԉُ�̎���
#define CONFUSION_TIME		(270)	// �����̏�Ԉُ�̎���

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
	m_pCollision = NULL;
	m_pLife = NULL;
	m_state = PLAYER_STATE_NORMAL;
	m_badState = PLAYER_BAD_STATE_NONE;
	m_type = PLAYER_TYPE_MAX;
	m_bLand = false;
	m_bDamage = false;
	m_bInvDamage = false;
	m_bInvSliding = false;
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
	m_bDamage = false;
	m_bInvDamage = false;
	m_bInvSliding = false;
	m_bDraw = true;
	m_nLife = PLAYER_BEGIN_LIFE;
	m_nInvincibleTime = 0;
	m_nBadStateTime = 0;
	m_nPoisonCount = 0;

	// ���f����������
	ModelCreate(m_type);

	// �ϐ��̐ݒ�
	SetRot(m_rot);
	SetPos(m_pos);

	// ���[�V�����̐���
	//m_pMotionPlayer = CMotionPlayer::Create(this);

	// �̂ɃR���W����(�v���C���[����)������
	m_pCollision = CCollisionSphere::Create(m_pos, m_size.x, 16, 16, CCollisionSphere::COLLISION_S_TYPE::COLLISION_S_TYPE_PLAYER, -1.0f);
	m_pCollision->SetNumPlayer(m_type);

	// ���C�t�̐���
	D3DXVECTOR2 lifePos = D3DXVECTOR2(0.0f, 0.0f);
	switch(m_type)
	{
	case PLAYER_TYPE_1P:
		lifePos = D3DXVECTOR2(150.0f, 100.0f);
		break;
	case PLAYER_TYPE_2P:
		lifePos = D3DXVECTOR2(400.0f, 100.0f);
		break;
	case PLAYER_TYPE_3P:
		lifePos = D3DXVECTOR2(SCREEN_WIDTH - 400.0f, 100.0f);
		break;
	case PLAYER_TYPE_4P:
		lifePos = D3DXVECTOR2(SCREEN_WIDTH - 150.0f, 100.0f);
		break;
	default:
		break;
	}
	m_pLife = CLifeUI::Create(lifePos, D3DXVECTOR2(200.0f, 50.0f));

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
		// �ʒu�̎擾
		D3DXVECTOR3 pos = GetPos();
		m_pos = pos;
		m_posOld = m_pos;

		// 1�t���[���O�̈ʒu�ݒ�
		SetPosOld(m_posOld);

		// �ړ�����
		Move();

		// ���̃R���W�����ƐڐG�������̏���
		TouchCollision();

		// ��Ԉُ�̏���
		BadState(m_badState);

		// �ړ��ʔ��f
		m_pos += m_move;

		// ���[�V����
		//m_pMotionPlayer->Update(this);

		// �ʒu���f
		SetPos(m_pos);

		// ���n��Ԃ�������
		m_bLand = false;

		// �v���C���[�Ƃ̉��o����
		Push(this);

		// �s�k�̏�Ԃ���Ȃ�������
		if (GetState() != PLAYER_STATE_DEFEAT)
		{
			// �ǂƂ̓����蔻��
			CMeshWall::Collision(this);
		}

		if (m_bLand == false)
		{
			// �n�ʂƂ̓����蔻��
			m_bLand = CMeshField::Collision(this);
		}

		if (m_bLand == true)
		{
			// ���n������Y�����̈ړ��ʂ�0��
			m_move.y = 0.0f;
		}

		// �ʒu�擾
		m_pos = GetPos();

		// ���G���̏���
		Invincible();

		// �R���W�����̒Ǐ]
		D3DXVECTOR3 collisionPos = D3DXVECTOR3(m_pos.x, m_pos.y + GetRadius(), m_pos.z);
		m_pCollision->SetPosCollision(collisionPos);

		m_pLife->SetLifeBar(m_nLife, PLAYER_BEGIN_LIFE);
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
		if (m_bDraw == true)
		{
			m_apModel[nCntModel]->Draw();
		}
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
			pPlayer->m_type = type;

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
	// ���f���̐���
	switch (type)
	{
	case PLAYER_TYPE_1P:
		m_apModel[0] = CModel::Create("data/MODEL/kirby.x");
		break;
	case PLAYER_TYPE_2P:
		m_apModel[0] = CModel::Create("data/MODEL/kirby_Y.x");
		break;
	case PLAYER_TYPE_3P:
		m_apModel[0] = CModel::Create("data/MODEL/kirby_B.x");
		break;
	case PLAYER_TYPE_4P:
		m_apModel[0] = CModel::Create("data/MODEL/kirby_G2.x");
		break;
	default:
		break;
	}

	if (m_apModel[0] != NULL)
	{
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
		m_size.x = fRadius * 2;
		m_size.y = fRadius * 2;
		m_size.z = fRadius * 2;
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
		// ���̃v���C���[�̍U�� �܂��� �����ɓ��������u�ԂȂ�
		if (m_pCollision->GetTouchCollision(CCollisionSphere::COLLISION_S_TYPE_ATTACK) == true ||
			m_pCollision->GetTouchCollision(CCollisionSphere::COLLISION_S_TYPE_EXPLOSION) == true ||
			m_pCollision->GetTouchCollision(CCollisionSphere::COLLISION_S_TYPE_POISON) == true ||
			m_pCollision->GetTouchCollision(CCollisionSphere::COLLISION_S_TYPE_CONFUSION) == true)
		{
			// ���炩�̖��G��Ԃ���Ȃ��Ȃ�
			if (m_bInvDamage == false && m_bInvSliding == false)
			{
				// �_���[�W���󂯂���Ԃɂ���
				m_bDamage = true;

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
					m_nLife -= 30;

					// ���C�t���c���Ă�����
					if (m_nLife > 0)
					{
						// ��_���[�W�ɂ�閳�G�ɂ���
						m_bInvDamage = true;
					}
				}
				// �ł̔����ɓ������Ă�����
				else if (m_pCollision->GetTouchCollision(CCollisionSphere::COLLISION_S_TYPE_POISON) == true)
				{
					// ���C�t�����炷
					m_nLife -= 30;

					// ���C�t���c���Ă�����
					if (m_nLife > 0)
					{
						// ��_���[�W�ɂ�閳�G�ɂ���
						m_bInvDamage = true;
					}

					SetBadState(PLAYER_BAD_STATE_POISON);
				}
				// �����̔����ɓ������Ă�����
				else if (m_pCollision->GetTouchCollision(CCollisionSphere::COLLISION_S_TYPE_CONFUSION) == true)
				{
					// ���C�t�����炷
					m_nLife -= 30;

					// ���C�t���c���Ă�����
					if (m_nLife > 0)
					{
						// ��_���[�W�ɂ�閳�G�ɂ���
						m_bInvDamage = true;
					}

					SetBadState(PLAYER_BAD_STATE_CONFUSION);
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
					m_move.y = 0.0f;
					m_move.y += PLAYER_DEFEATKNOCKBACK_JUMP;
				}
				// ���C�t������Ȃ�ʏ�̋���
				else
				{
					// �Ώۂ̃R���W�����̕�������������
					m_rot.y = m_pCollision->GetObjectiveRot();

					// Y�����ւ̈ړ��ʂ����Z�b�g���A�W�����v������
					m_move.y = 0.0f;
					m_move.y += PLAYER_KNOCKBACK_JUMP;
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
			m_bDamage = false;
			m_bDraw = true;

			// ���G���Ԃ����Z�b�g
			m_nInvincibleTime = 0;
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

		// ��莞�Ԃ��o������
		if (m_nBadStateTime >= ICE_TIME)
		{
			// ��Ԉُ��������
			SetBadState(PLAYER_BAD_STATE_NONE);

			// ���Ԃ����Z�b�g
			m_nBadStateTime = 0;
		}
		break;
		// ��
	case PLAYER_BAD_STATE_POISON:
		// �J�E���g�𑝂₷
		m_nBadStateTime++;

		// <�������>�̏�ԈȊO�œ����Ă���ꍇ
		if (m_state != PLAYER_STATE_BLOWAWAY && m_move.x != 0.0f || m_move.z != 0.0f)
		{
			// �J�E���g�𑝂₷
			m_nPoisonCount++;

			// ��莞�Ԃ��o�߂��A���C�t��1���ゾ������
			if (m_nPoisonCount >= 30 && m_nLife > 1)
			{
				// ���C�t�����炷
				m_nLife--;
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
		}
		break;
		// ����
	case PLAYER_BAD_STATE_CONFUSION:
		// �J�E���g�𑝂₷
		m_nBadStateTime++;

		// ��莞�Ԃ��o������
		if (m_nBadStateTime >= CONFUSION_TIME)
		{
			// ��Ԉُ��������
			SetBadState(PLAYER_BAD_STATE_NONE);

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