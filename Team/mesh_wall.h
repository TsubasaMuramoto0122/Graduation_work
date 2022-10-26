//=============================================================================
// ���b�V��(�E�H�\��)���� [mesh_wall.h]
// Author : Kusakari Kakeru
//=============================================================================
#ifndef _MESH_WALL_H_
#define _MESH_WALL_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene3D.h"

//*****************************************************************************
//�N���X�̒�`
//*****************************************************************************
class CMeshWall : public CScene3D
{
public:
	CMeshWall(PRIORITY nPriority = PRIORITY_OBJECT);						// �R���X�g���N�^
	~CMeshWall();															// �f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);						// ����������
	void Uninit(void);														// �I������
	void Update(void);														// �X�V����
	void Draw(void);														// �`�揈��
	static CMeshWall *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,
		D3DXVECTOR3 rot, int nRow, int nLine, int nTex);					// ��������
	OBJTYPE GetObjType() { return OBJECTTYPE_WALL; }						// �I�u�W�F�N�g�̎��
	D3DXVECTOR3 GetSize() { return m_size; }								// �T�C�Y�擾����
	void SetColor(D3DXCOLOR col);											// �J���[�ݒ菈��
	static D3DXVECTOR3 Collision(CScene *pScene);							// �����蔻��

private:
	LPDIRECT3DTEXTURE9 m_pTexture;											// �e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;										// ���_�o�b�t�@�̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;										// �C���f�b�N�X�o�b�t�@�̃|�C���^
	D3DXVECTOR3 m_pos;														// �ʒu
	D3DXVECTOR3	m_size;														// �T�C�Y
	D3DXVECTOR3 m_rot;														// ����
	D3DXMATRIX m_mtxWorld;													// ���[���h�}�g���b�N�X
	int m_nRow;																// ���̕�����
	int m_nLine;															// �c�̕�����
};

#endif // _MESH_FIELD_H_