//=============================================================================
// ���ʏ��� [plane.h]
// Author : �����G��
//=============================================================================
#ifndef _PLANE_H_
#define _PLANE_H_

#include "main.h"
#include "scene3d.h"

//�}�N����`

class CPlane : public CScene3D
{
public:
	CPlane(int nPriority);
	~CPlane();
	HRESULT Init(D3DXVECTOR3 size, D3DXVECTOR3 pos, D3DXVECTOR2 Tex);
	void Uninit();
	void Update();
	void Draw();
	D3DXVECTOR3 GetSize() { return m_size; }
	void SetSize(D3DXVECTOR3 size);

	LPDIRECT3DVERTEXBUFFER9 GetVtx() { return m_pVtxBuff; }
	void SetTexture(int nTex) { m_nTexType = nTex; }		//�w�肳�ꂽ�ԍ��̃e�N�X�`����\���悤��
	void ChangeColor(D3DXCOLOR col);

	//�G�t�F�N�g�p�֐�
	void ColorChange(D3DCOLORVALUE color);	//�F�ύX
	void ChangeSize(D3DXVECTOR3 size);	//�T�C�Y�ύX
	void BillboardSize(float size);	//�T�C�Y�ύX

	void TexturMove(D3DXVECTOR2 MoveTex);

	void SetTexAnim(D3DXVECTOR2 TexPattern, D3DXVECTOR2 TexAnimSize);
	void SetPosField(D3DXVECTOR3 pos, D3DXVECTOR3 Size, float Rotate,float Rotate2);

	void SetPosBill(D3DXVECTOR3 pos, D3DXVECTOR3 pos2, D3DXVECTOR3 pos3, D3DXVECTOR3 pos4);

	static CPlane *Create(D3DXVECTOR3 size, D3DXVECTOR3 pos, D3DXVECTOR2 Tex);
	static void CreateTextureFiled();

	static LPDIRECT3DTEXTURE9 *GetTexture(int nTex) { return &m_pTexture[nTex]; }

	//�e�N�X�`���j��
	static void UninitTexture();

	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL; //���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_size;
	static int m_nMaxTex;					   //�g�p����ő�e�N�X�`��
	static int m_Synthetic;
	D3DXVECTOR3 m_rot;

protected:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];	//�e�N�X�`���ւ̃|�C���^

	int m_nTexType;												//�\��e�N�X�`��
	D3DXVECTOR2 m_TexNum;
	D3DXVECTOR2 m_TexMove;
	D3DXVECTOR2 m_TexSize;
	D3DXVECTOR2 m_PatternSize;

	int m_nAnimCount;
	int m_nSetAnimCnt;
	D3DXVECTOR2 m_nSplit;
	D3DXVECTOR2 m_MaxSplit;

};

#endif