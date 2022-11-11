//=============================================================================
//
// �V�[������ [scene3d.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

#include "main.h"
#include "scene.h"

struct VERTEX_3D
{
	D3DXVECTOR3 pos; //���_���W
	D3DXVECTOR3 nor; //�@���x�N�g��
	D3DCOLOR col;    //���_�J���[
	D3DXVECTOR2 tex; //�e�N�X�`�����W
};

//�}�N��
#define MAX_3DTEXTURE (32)		//�ő�Ŏg����3D�p�̉摜��

class CScene3D : public CScene
{
public:
	CScene3D(PRIORITY Priority);
	~CScene3D();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit();
	void Update();
	void Draw();
	OBJTYPE GetObjType() { return OBJECTTYPE_NONE; }

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	D3DXVECTOR3 GetPos() { return m_pos; }

	void SetPosOld(D3DXVECTOR3 pos) { m_posOld = pos; }
	D3DXVECTOR3 GetPosOld() { return m_posOld; }

	float GetRadius() { return 0.0f; }

	D3DXVECTOR3 GetRot() { return m_rot; }
	void SetRot(D3DXVECTOR3 rot);

	void SetMatrix(D3DXMATRIX mtx) { mtx = m_mtxWorld; }

	static void CreateTextureFiled();
	static LPDIRECT3DTEXTURE9 *GetTexture(int nTex) { return &m_pTexture[nTex]; }

	//�e�N�X�`���j��
	static void UninitTexture();

	static CScene3D *Create(const D3DXVECTOR3& pos);

private:
	D3DXVECTOR3 m_rot; //����
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_posOld;
	D3DXMATRIX m_mtxWorld; //���[���h�}�g���b�N�X
	static int m_nMaxTex;					   //�g�p����ő�e�N�X�`��

protected:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_3DTEXTURE];			//�e�N�X�`���[�|�C���^
};
#endif
