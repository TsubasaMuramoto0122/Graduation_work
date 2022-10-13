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
#include "camera.h"
//#include "motion_player.h"
#include "control_player.h"
#include "shadow.h"
#include "sound.h"
#include "collision_sphere.h"
#include "mesh_field.h"
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
	m_pCollision = NULL;
	m_state = PLAYER_STATE_NORMAL;
	m_bLand = false;
	m_bInvincible = false;
	m_bDraw = true;
	m_nLife = 0;
	m_nInvincibleTime = 0;
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
	m_bInvincible = false;
	m_bDraw = true;
	m_nLife = PLAYER_BEGIN_LIFE;
	m_nInvincibleTime = INVINCIBLE_TIME;

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

		// ���G���̏���
		Invincible();

		// �R���W�����̒Ǐ]
		D3DXVECTOR3 collisionPos = D3DXVECTOR3(m_pos.x, m_pos.y + GetRadius(), m_pos.z);
		m_pCollision->SetPosCollision(collisionPos);
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
	switch (type)
	{
	case PLAYER_TYPE_1P:
		// ���f���̐���
		m_apModel[0] = CModel::Create("data/MODEL/kirby.x");
		break;

	case PLAYER_TYPE_2P:
		// ���f���̐���
		m_apModel[0] = CModel::Create("data/MODEL/kirby.x");
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
				D3DXVECTOR3 posPlayer = pOtherPlayer->GetPos();		// ���̃v���C���[�̈ʒu���擾
				float fSizePlayer = pOtherPlayer->GetRadius();		// ���̃v���C���[�̃T�C�Y�̔��a���擾
				float totalSize = (GetRadius() + fSizePlayer) * 0.75f;		// �v���C���[2�l�̔��a�̍��v

				float fDistance = sqrtf((pPlayer->m_pos.x - posPlayer.x) * (pPlayer->m_pos.x - posPlayer.x) + (pPlayer->m_pos.y - posPlayer.y) * (pPlayer->m_pos.y - posPlayer.y) + (pPlayer->m_pos.z - posPlayer.z) * (pPlayer->m_pos.z - posPlayer.z));
				float fRot = (float)atan2((posPlayer.x - pPlayer->m_pos.x), (posPlayer.z - pPlayer->m_pos.z)) - D3DX_PI;

				// �������v���C���[2�l�̔��a�̍��v��菬����������
				if (fDistance <= totalSize)
				{
					pPlayer->m_pos.x = posPlayer.x + (sinf(fRot) * totalSize);
					pPlayer->m_pos.z = posPlayer.z + (cosf(fRot) * totalSize);

					// �ʒu��ݒ�
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
	if (m_pCollision->GetTouchCollision(CCollisionSphere::COLLISION_S_TYPE_ATTACK) == true ||
		m_pCollision->GetTouchCollision(CCollisionSphere::COLLISION_S_TYPE_EXPLOSION) == true)
	{
		if (m_bInvincible == false)
		{
			// �Ώۂ̃R���W�����̕������������A��Ԃ�<�������>�ɐݒ�
			m_rot.y = m_pCollision->GetObjectiveRot();
			m_state = PLAYER_STATE_BLOWAWAY;

			if (m_pCollision->GetTouchCollision(CCollisionSphere::COLLISION_S_TYPE_EXPLOSION) == true)
			{
				m_bInvincible = true;
			}

			// Y�����ւ̈ړ��ʂ����Z�b�g���A�W�����v������
			m_move.y = 0.0f;
			m_move.y += PLAYER_KNOCKBACK_JUMP;
		}
	}
	else
	{
		m_state = PLAYER_STATE_NORMAL;
	}
}

//=============================================================================
// ���G���̏���
//=============================================================================
void CPlayer::Invincible(void)
{
	if (m_bInvincible == true)
	{
		// ���G���Ԃ̃J�E���g�����炷
		m_nInvincibleTime--;

		if (m_nInvincibleTime % 8 == 0 || m_nInvincibleTime % 8 == 1)
		{
			m_bDraw = false;
		}
		else
		{
			m_bDraw = true;
		}

		// ���G���Ԃ��I�������
		if (m_nInvincibleTime <= 0)
		{
			// ���G��Ԃ�����
			m_bInvincible = false;
			m_bDraw = true;

			// ���G���Ԃ����Z�b�g
			m_nInvincibleTime = INVINCIBLE_TIME;
		}
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