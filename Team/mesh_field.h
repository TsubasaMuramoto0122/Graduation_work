//=============================================================================
// ���b�V��(�n��)���� [mesh_field.h]
// Author : Kusakari Kakeru
//=============================================================================
#ifndef _MESH_FIELD_H_
#define _MESH_FIELD_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene3D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_TEXTURE_MESHFILED (16)

//*****************************************************************************
//�N���X�̒�`
//*****************************************************************************
class CMeshField : public CScene3D
{
public:
	CMeshField(PRIORITY Priority = PRIORITY_PLANE);					// �R���X�g���N�^
	~CMeshField();														// �f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);					// ����������
	void Uninit(void);													// �I������
	void Update(void);													// �X�V����
	void Draw(void);													// �`�揈��
	void ZTexDraw();
	static CMeshField *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,
		D3DXVECTOR3 rot, int nRow, int nLine, int nTex);				// ��������

	OBJTYPE GetObjType() { return OBJECTTYPE_FIELD; }					// �I�u�W�F�N�g�̎��
	float GetRadius() { return m_size.x / 2; }							// ���a�擾����
	void SetColor(D3DXCOLOR col);										// �J���[�ݒ菈��
	static bool Collision(CScene *pScene);								// �����蔻�菈��

private:
	LPDIRECT3DTEXTURE9 m_pTexture;										// �e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;									// ���_�o�b�t�@�̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;									// �C���f�b�N�X�o�b�t�@�̃|�C���^
	D3DXVECTOR3 m_pos;													// �ʒu
	D3DXVECTOR3	m_size;													// �T�C�Y
	D3DXVECTOR3 m_rot;													// ����
	D3DXMATRIX m_mtxWorld;												// ���[���h�}�g���b�N�X
	int m_nRow;															// ���̕�����
	int m_nLine;														// �c�̕�����
	//int m_nTexType;													// �\��e�N�X�`��
	//static int m_nMaxTex;												// �g�p����ő�e�N�X�`��
};

#endif // _MESH_FIELD_H_