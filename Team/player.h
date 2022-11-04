//=============================================================================
// �v���C���[���� [player.h]
// Authore : kusakari Kakeru
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "scene3d.h"
#include "model.h"

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define MAX_PLAYER_MODEL	(14)		// ���f���̍ő吔

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CModel;
class CMotion;
class CControl;
class CCollisionSphere;
class CLifeUI;

//*****************************************************************************
//�N���X�̒�`
//*****************************************************************************
class CPlayer : public CScene3D
{
public:
	// �v���C���[�̎��
	typedef enum
	{
		PLAYER_TYPE_1P = 0,
		PLAYER_TYPE_2P,
		PLAYER_TYPE_3P,
		PLAYER_TYPE_4P,
		PLAYER_TYPE_MAX
	} PLAYER_TYPE;

	// �v���C���[�̏��
	typedef enum
	{
		PLAYER_STATE_NORMAL = 0,	// �ʏ�
		PLAYER_STATE_BLOWAWAY,		// �������
		PLAYER_STATE_DEFEAT,		// ����
		PLAYER_STATE_MAX
	} PLAYER_STATE;

	// �v���C���[�̏�Ԉُ�
	typedef enum
	{
		PLAYER_BAD_STATE_NONE = 0,	// �Ȃ�
		PLAYER_BAD_STATE_ICE,		// �X
		PLAYER_BAD_STATE_POISON,	// ��
		PLAYER_BAD_STATE_CONFUSION,	// ����
		PLAYER_BAD_STATE_MAX
	} PLAYER_BAD_STATE;

	CPlayer(PRIORITY Priority = PRIORITY_CHARA);							// �R���X�g���N�^
	~CPlayer();																// �f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos);											// ����������
	void Uninit(void);														// �I������
	void Update(void);														// �X�V����
	void Draw(void);														// �`�揈��
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,
		PLAYER_TYPE type, bool bCPU);										// ��������

	OBJTYPE GetObjType() { return OBJECTTYPE_PLAYER; }						// �I�u�W�F�N�g�̎��
	void SetPosOld(D3DXVECTOR3 pos) { m_posOld = pos; }						// 1�t���[���O�̈ʒu�ݒ菈��
	D3DXVECTOR3 GetPosOld() { return m_posOld; }							// 1�t���[���O�̈ʒu�擾����
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }							// �����ݒ菈��
	D3DXVECTOR3 GetRot(void) { return m_rot; }								// �����擾����
	float GetRadius(void) { return m_size.x / 2; }							// ���a�擾����
	D3DXVECTOR3 GetMove() { return m_move; }								// �ړ��ʎ擾����
	void SetLand(bool bLand) { m_bLand = bLand; }							// ���n�ݒ菈��
	bool GetLand(void) { return m_bLand; }									// ���n�擾����
	void SetInvSliding(bool bInvincible) { m_bInvSliding = bInvincible; }	// �X���C�f�B���O(���)�ɂ�閳�G�ݒ菈��
	bool GetInvSliding(void) { return m_bInvSliding; }						// �X���C�f�B���O(���)�ɂ�閳�G�擾����
	void SetState(PLAYER_STATE state) { m_state = state; }					// ��Ԑݒ菈��
	PLAYER_STATE GetState(void) { return m_state; }							// ��Ԏ擾����
	void SetBadState(PLAYER_BAD_STATE state) { m_badState = state; }		// ��Ԉُ�擾����
	PLAYER_BAD_STATE GetBadState(void) { return m_badState; }				// ��Ԉُ�擾����
	PLAYER_TYPE GetType(void) { return m_type; }							// ��ގ擾����
	void SetModelPos(int nCntModel, D3DXVECTOR3 pos) { m_apModel[nCntModel]->SetPos(pos); }		// ���f�����̈ʒu�ݒ菈��
	D3DXVECTOR3 GetModelPos(int nCntModel) { return m_apModel[nCntModel]->GetPos(); }			// ���f�����̈ʒu�擾����
	void SetModelRot(int nCntModel, D3DXVECTOR3 rot) { m_apModel[nCntModel]->SetRot(rot); }		// ���f�����̌����ݒ菈��
	D3DXVECTOR3 GetModelRot(int nCntModel) { return m_apModel[nCntModel]->GetRot(); }			// ���f�����̌����擾����
	bool GetHitWall() { return m_bWall; }

	static CPlayer *CPlayer::SearchPlayer(CScene *pScene);
	static void SetSurviveTime(int nTime, int nNum) { m_nSurviveTime[nNum] = nTime; }	// �������Ԏ擾����
	static int GetSurviveTime(int nNum) { return m_nSurviveTime[nNum]; }				// �������Ԏ擾����
	CMotion *GetMotion(void) { return m_pMotion; }										// ���[�V�����擾����
	//CModel *GetModel(int nCntModel) { return m_apModel[nCntModel]; }					// �v���C���[�̃��f���擾����

private:
	void ModelCreate(PLAYER_TYPE type);					// ���f����������
	void Move(void);									// �ړ�����
	void Push(CPlayer *pPlayer);						// �R���W�������g�������o����
	void TouchCollision(void);							// ���̃R���W�����ƐڐG�������̏���
	void Invincible(void);								// ���G���̏���
	void BadState(PLAYER_BAD_STATE state);				// ��Ԉُ�̏���

	D3DXVECTOR3 m_pos;									// �ʒu
	D3DXVECTOR3 m_posOld;								// 1�t���[���O�̈ʒu
	D3DXVECTOR3 m_move;									// �ړ���
	D3DXVECTOR3 m_size;									// �T�C�Y
	D3DXVECTOR3 m_rot;									// ����
	D3DXMATRIX m_mtxWorld;								// ���[���h�}�g���b�N�X
	CModel *m_apModel[MAX_PLAYER_MODEL];				// ���f���̃|�C���^
	CModel *m_pParent;									// �e���f���ւ̃|�C���^
	CMotion *m_pMotion;									// ���[�V�����̃|�C���^
	CControl *m_pControl;								// �R���g���[���̃|�C���^
	CCollisionSphere *m_pCollision;						// ���̃R���W�����̃|�C���^
	CLifeUI *m_pLife;									// ���C�t�̃|�C���^
	PLAYER_STATE m_state;								// ���
	PLAYER_BAD_STATE m_badState;						// ��Ԉُ�
	PLAYER_TYPE m_type;									// ���
	bool m_bLand;										// ���n���Ă��邩�ǂ���
	bool m_bDamage;										// �_���[�W���󂯂����ǂ���
	bool m_bInvDamage;									// ��_���[�W�ɂ�閳�G���ǂ���
	bool m_bInvSliding;									// �X���C�f�B���O(���)�ɂ�閳�G���ǂ���
	bool m_bDraw;										// �`�悳���邩�ǂ���
	bool m_bCPU;										// CPU���ǂ���
	bool m_bWall;										// �ǂɓ���������(CPU�ɕK�v)
	int m_nLife;										// �v���C���[�̃��C�t
	int m_nInvincibleTime;								// ���G����
	int m_nBadStateTime;								// ��Ԉُ�̎���
	int m_nPoisonCount;									// �ŏ�Ԃ̃J�E���g
	static int m_nSurviveTime[PLAYER_TYPE_MAX];			// �v���C���[�̐�������
};

#endif // _PLAYER_H_