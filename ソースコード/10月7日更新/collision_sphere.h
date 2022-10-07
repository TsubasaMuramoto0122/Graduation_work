//=============================================================================
// ���̃R���W�������� [collision_sphere.h]
// Author : Kusakari Kakaeru
//=============================================================================
#ifndef _SPHERE_COLLISION_H_
#define _SPHERE_COLLISION_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene3D.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CModel;

//*****************************************************************************
//�N���X�̒�`
//*****************************************************************************
class CCollisionSphere : public CScene3D
{
public:
	// �ǂ̓����蔻�肩
	typedef enum
	{
		COLLISION_S_TYPE_PLAYER = 0,	// �v���C���[
		COLLISION_S_TYPE_ATTACK,		// �v���C���[�̍U��
		COLLISION_S_TYPE_EXPLOSION,		// �����ȂǁA�_���[�W����
		COLLISION_S_TYPE_ICE,			// �A�C�X
		COLLISION_S_TYPE_POISON,		// ��
		COLLISION_S_TYPE_PANIC,			// ����
		COLLISION_S_TYPE_MAX
	} COLLISION_S_TYPE;

	CCollisionSphere(PRIORITY Priority = PRIORITY_EFFECT);			// �R���X�g���N�^
	~CCollisionSphere();											// �f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);				// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��
	static CCollisionSphere *Create(D3DXVECTOR3 pos,
		D3DXVECTOR3 size, int nVertical, int nSide,
		COLLISION_S_TYPE type, float fTime);						// ��������
	OBJTYPE GetObjType() { return OBJECTTYPE_NONE; }				// �I�u�W�F�N�g�̎��
	void Collision(CScene *pScene);									// �Փˏ���
	void SetPosCollision(D3DXVECTOR3 pos);							// �ʒu�ݒ菈��
	COLLISION_S_TYPE GetCollisionType(void);						// �R���W�����̎�ނ̎擾����
	void SetParent(CModel *pModel);									// �e���f���ݒ菈��
	D3DXVECTOR3 GetMtxPos(void);									// ���[���h�}�g���b�N�X���W�擾����
	bool OnCollisionEnter(void);									// �Փ˂����u�Ԃ̏���
	void SetCollisionType(COLLISION_S_TYPE type);					// �R���W�����̎�ސݒ菈��
	float GetRadius(void);											// ���a�擾����
	bool GetTouchCollision(COLLISION_S_TYPE type);					// �w��̃I�u�W�F�N�g�ɓ����������ǂ���

#ifdef _DEBUG
	static void SetVisual(bool bVisual);							// ����̉����ݒ菈��
#endif

private:
#ifdef _DEBUG
	void VisualOn(bool bVisual);									// ����̉�������
#endif
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;								// ���_�o�b�t�@�̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;								// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;												// �ʒu
	D3DXVECTOR3	m_size;												// �T�C�Y
	D3DXVECTOR3 m_rot;												// ����
	D3DXMATRIX m_mtxWorld;											// ���[���h�}�g���b�N�X
	CModel *m_pParent;												// �e�̃��f��
	D3DXCOLOR m_col;												// �J���[
	COLLISION_S_TYPE m_collisionType;								// �����蔻��̎��
	int m_nVertical;												// �c�̕�����
	int m_nSide;													// ���̕�����
	float m_fTime;													// ��������
	float m_fDamage;												// �_���[�W�̒l
	float m_fObjectiveRot;											// �ړI�̌���
	static bool m_bMngVisual;										// ������������邩�ǂ���
	bool m_bContact;												// ��x�ł������������ǂ���
	bool m_bContactOld;												// 1�t���[���O�ɓ������Ă������ǂ���
	bool m_bTouchAttack;											// �U���ɓ������Ă��邩�ǂ���
	bool m_bTouchExplosion;											// �����ɓ������Ă��邩�ǂ���
};

#endif // _SPHERE_COLLISION_H_