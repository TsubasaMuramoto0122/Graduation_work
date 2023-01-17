//=============================================================================
// ���b�V��(�~��)���� [mesh_cylinder.h]
// Authore : Kusakari Kakeru
//=============================================================================
#ifndef _MESH_CYLINDER_H_
#define _MESH_CYLINDER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene3D.h"

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CMeshCylinder : public CScene3D
{
public:
	CMeshCylinder(PRIORITY nPriority = PRIORITY_OBJECT);			// �R���X�g���N�^
	~CMeshCylinder();												// �f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);				// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��
	static CMeshCylinder *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,
		int nVertical, int nSide, bool bOutSide, int nTex);			// ��������

	OBJTYPE GetObjType() { return OBJECTTYPE_FIELD; }				// �I�u�W�F�N�g�̎��
	float GetRadius() { return m_size.x / 2; }						// ���a�擾����

private:
	LPDIRECT3DTEXTURE9 m_pTexture;									// �e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;								// ���_�o�b�t�@�̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;								// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;												// �ʒu
	D3DXVECTOR3	m_size;												// �T�C�Y
	D3DXVECTOR3 m_rot;												// ����
	D3DXMATRIX m_mtxWorld;											// ���[���h�}�g���b�N�X
	int m_nSide;													// ���̕�����
	int m_nVertical;												// �c�̕�����
	bool m_bOutSide;												// �V�����_�[�̊O���ɕ`�悷�邩�ǂ���
};

#endif // _MESH_CYLINDER_H_