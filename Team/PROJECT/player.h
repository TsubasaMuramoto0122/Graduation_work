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

//*****************************************************************************
//�N���X�̒�`
//*****************************************************************************
class CPlayer : public CScene3D
{
public:
	CPlayer(PRIORITY nPriority = PRIORITY_CHARA);			// �R���X�g���N�^
	~CPlayer();													// �f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos);								// ����������
	void Uninit(void);											// �I������
	void Update(void);											// �X�V����
	void Draw(void);											// �`�揈��
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// ��������
	OBJTYPE GetObjType() { return OBJECTTYPE_BOMB; }

	D3DXVECTOR3 GetPosOld(void);								// 1�t���[���O�̈ʒu�擾����
	void SetLand(bool bLand);									// ���n�ݒ菈��
	bool GetLand(void);											// ���n�擾����
	void SetModelPos(int nCntModel, D3DXVECTOR3 pos);			// ���f�����̈ʒu�ݒ菈��
	D3DXVECTOR3 GetModelPos(int nCntModel);						// ���f�����̈ʒu�擾����
	void SetModelRot(int nCntModel, D3DXVECTOR3 rot);			// ���f�����̌����ݒ菈��
	D3DXVECTOR3 GetModelRot(int nCntModel);						// ���f�����̌����擾����
																//CMotionPlayer *GetMotionPlayer(void);						// �v���C���[�̃��[�V�����擾����
																//CModel *GetModel(int nCntModel);							// �v���C���[�̃��f���擾����

private:
	void ModelCreate(void);										// ���f����������
	void Move(void);											// �ړ�����

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
	bool m_bLand;												// ���n���Ă��邩�ǂ���
};

#endif // _PLAYER_H_