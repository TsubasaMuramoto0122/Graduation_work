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

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define MAX_PLAYER_MODEL	(1)		// ���f���̍ő吔
#define PLAYER_BEGIN_LIFE	(5)		// �������C�t
#define INVINCIBLE_TIME		(120)	// ���G����

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CModel;
//class CMotionPlayer;
class CControl;
class CCollisionSphere;

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
		PLAYER_TYPE_MAX
	} PLAYER_TYPE;

	// �v���C���[�̏��
	typedef enum
	{
		PLAYER_STATE_NORMAL = 0,
		PLAYER_STATE_DAMAGE,
		PLAYER_STATE_MAX
	} PLAYER_STATE;

	CPlayer(PRIORITY Priority = PRIORITY_CHARA);				// �R���X�g���N�^
	~CPlayer();													// �f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot,
		PLAYER_TYPE type);										// ����������
	void Uninit(void);											// �I������
	void Update(void);											// �X�V����
	void Draw(void);											// �`�揈��
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,
		PLAYER_TYPE type);										// ��������
	OBJTYPE GetObjType() { return OBJECTTYPE_PLAYER; }			// �I�u�W�F�N�g�̎��

	D3DXVECTOR3 GetPosOld(void);								// 1�t���[���O�̈ʒu�擾����
	void SetRot(D3DXVECTOR3 rot);								// �����ݒ菈��
	D3DXVECTOR3 GetRot(void);									// �����擾����
	float GetRadius(void);										// ���a�擾����
	void SetLand(bool bLand);									// ���n�ݒ菈��
	bool GetLand(void);											// ���n�擾����
	void SetModelPos(int nCntModel, D3DXVECTOR3 pos);			// ���f�����̈ʒu�ݒ菈��
	D3DXVECTOR3 GetModelPos(int nCntModel);						// ���f�����̈ʒu�擾����
	void SetModelRot(int nCntModel, D3DXVECTOR3 rot);			// ���f�����̌����ݒ菈��
	D3DXVECTOR3 GetModelRot(int nCntModel);						// ���f�����̌����擾����
																//CMotionPlayer *GetMotionPlayer(void);						// �v���C���[�̃��[�V�����擾����
																//CModel *GetModel(int nCntModel);							// �v���C���[�̃��f���擾����

private:
	void ModelCreate(PLAYER_TYPE type);							// ���f����������
	void Move(void);											// �ړ�����
	void Push(CPlayer *pPlayer);								// �R���W�������g�������o����
	void TouchCollision(void);									// ���̃R���W�����ƐڐG�������̏���

	D3DXVECTOR3 m_pos;											// �ʒu
	D3DXVECTOR3 m_posOld;										// 1�t���[���O�̈ʒu
	D3DXVECTOR3 m_move;											// �ړ���
	D3DXVECTOR3 m_size;											// �T�C�Y
	D3DXVECTOR3 m_rot;											// ����
	D3DXMATRIX m_mtxWorld;										// ���[���h�}�g���b�N�X

	CModel *m_apModel[MAX_PLAYER_MODEL];						// ���f���̃|�C���^
	CModel *m_pParent;											// �e���f���ւ̃|�C���^
																//CMotionPlayer *m_pMotionPlayer;							// ���[�V�����̃|�C���^
	CControl *m_pControl;										// �R���g���[���̃|�C���^
	CCollisionSphere *m_pCollision;								// ���̃R���W�����̃|�C���^
	PLAYER_STATE m_state;										// ���
	bool m_bLand;												// ���n���Ă��邩�ǂ���
};

#endif // _PLAYER_H_