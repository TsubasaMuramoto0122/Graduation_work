//=============================================================================
// �r���{�[�h���� [Billboard.h]
// Author : �O��q��
//=============================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"
#include "scene3d.h"

class CBillboard : public CScene3D
{
public:
	CBillboard(PRIORITY nPriority);
	~CBillboard();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 Size, int nTex, D3DXCOLOR col, int nLife);	//������

	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��
	void ZTexDraw();

	static CBillboard *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 Size, int nTex, D3DXCOLOR col, int nLife);

private:
	LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�̃|�C���^
	D3DXVECTOR3 m_pos;					// �ʒu
	D3DXVECTOR3 m_move;
	int m_nLife;						//����
};
#endif