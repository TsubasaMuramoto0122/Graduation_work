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

	CCollisionSphere(PRIORITY Priority = PRIORITY_EFFECT);					// �R���X�g���N�^
	~CCollisionSphere();													// �f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos, float fSize);								// ����������
	void Uninit(void);														// �I������
	void Update(void);														// �X�V����
	void Draw(void);														// �`�揈��
	static CCollisionSphere *Create(D3DXVECTOR3 pos,
		float fSize, int nVertical, int nSide,
		COLLISION_S_TYPE type, float fTime);								// ��������
	OBJTYPE GetObjType() { return OBJECTTYPE_NONE; }						// �I�u�W�F�N�g�̎��
	void SetPosCollision(D3DXVECTOR3 pos) { m_pos = pos; }					// �ʒu�ݒ菈��
	COLLISION_S_TYPE GetCollisionType(void) { return m_collisionType; }		// �R���W�����̎�ނ̎擾����
	void SetParent(CModel *pModel) { m_pParent = pModel; }					// �e���f���ݒ菈��
	float GetRadius(void) { return m_fSize / 2; }							// ���a�擾����
	void SetNumPlayer(int nNum) { m_nNumPlayer = nNum; }					// �ԍ��ݒ菈��
	int GetNumPlayer(void) { return m_nNumPlayer; }							// �ԍ��擾����
	float GetObjectiveRot(void) { return m_fObjectiveRot; }					// �ړI�̌����擾����
	D3DXVECTOR3 GetMtxPos(void);											// ���[���h�}�g���b�N�X���W�擾����
	void Collision(CScene *pScene);											// �Փˏ���
	void SetCollisionType(COLLISION_S_TYPE type);							// �R���W�����̎�ސݒ菈��
	bool GetTouchCollision(COLLISION_S_TYPE type);							// �w��̎�ނɓ����������ǂ���

#ifdef _DEBUG
	static void SetVisual(bool bVisual);									// ����̉����ݒ菈��
#endif

private:
#ifdef _DEBUG
	void VisualOn(bool bVisual);											// ����̉�������
#endif
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;										// ���_�o�b�t�@�̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;										// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;														// �ʒu
	D3DXVECTOR3 m_rot;														// ����
	D3DXMATRIX m_mtxWorld;													// ���[���h�}�g���b�N�X
	CModel *m_pParent;														// �e�̃��f��
	D3DXCOLOR m_col;														// �J���[
	COLLISION_S_TYPE m_collisionType;										// �����蔻��̎��
	int m_nVertical;														// �c�̕�����
	int m_nSide;															// ���̕�����
	int m_nNumPlayer;														// �v���C���[�̔ԍ�
	float m_fSize;															// �T�C�Y
	float m_fTime;															// ��������
	float m_fDamage;														// �_���[�W�̒l
	float m_fObjectiveRot;													// �ړI�̌���
	static bool m_bMngVisual;												// ������������邩�ǂ���
	bool m_bContact;														// ��x�ł������������ǂ���
	bool m_bTouchAttack;													// �U���ɓ������Ă��邩�ǂ���
	bool m_bTouchExplosion;													// �����ɓ������Ă��邩�ǂ���
};

#endif // _SPHERE_COLLISION_H_