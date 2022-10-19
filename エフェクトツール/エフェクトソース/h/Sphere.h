//=============================================================================
// ���󏈗� [Sphere.h]
// Author : �����G��
//=============================================================================
#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "main.h"
#include "plane.h"


class CSphere : public CScene3D
{
public:
	CSphere(int nPriority);	//�R���X�g���N�^
	~CSphere();	//�f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, float rot,
		float fSize, int Vertical,
		int Line, int nTex,
		int Synthetic, D3DXVECTOR2 TexNum);
	void Uninit();
	void Update();
	void Draw();

	D3DXVECTOR3 GetSherePos() { return m_Pos; }

	void SetColor(D3DCOLORVALUE Color);
	void SetSize(D3DXVECTOR3 pos ,float Size);
	void Rotate(float Rotate);

	void SetTexUV(D3DXVECTOR2 TexUV);
	void SetAnimTexUV(D3DXVECTOR2 TexPattern);


	static  void CreateTextureSphere(void);
	static void UninitTextureSphere();


protected:
	bool m_bUninit;	//�����t���O
	int m_nLife;	//����

	D3DXVECTOR2 m_PatternSize;
	int m_nAnimCount;
	int m_nSetAnimCnt;
	D3DXVECTOR2 m_nSplit;
	D3DXVECTOR2 m_MaxSplit;
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];	//�e�N�X�`��
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;	//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff = NULL;	//�C���f�b�N�X�o�b�t�@

	D3DXMATRIX m_mtxWorld;	//���[���h�}�g���b�N�X
	D3DXVECTOR3 m_Pos;	//�ʒu
	D3DXVECTOR2 m_TexUV;	//�e�N�X�`�����W
	D3DXVECTOR2 m_TexMoveUV;	//�e�N�X�`�����W�̈ړ�

	D3DXVECTOR2 m_PatternUV;

	float m_Rot;	//��]
	float m_Rot2;	//��]

	int m_nVertical;	//���̕�����
	int m_nLine;		//�c�̕�����
	int m_nTex;		//�e�N�X�`��

	int m_nVtx;	//���_��
	int m_nIdx;	//�C���f�b�N�X��
	int m_Synthetic;	//����

	float m_fRotate;	//��]

	float m_fRadius;	//���a
	int m_Primithive;	//�v���~�e�B�u

	static int m_nMaxTex;

};

#endif // !_MESHEFFECT_H_
