// ZTexCreator.h (2007. 2. 28)

// Z�l�e�N�X�`�������N���X�錾��
//  ������ �F IKD



#include "main.h"

///////////////////////////////////////////////
// CZTexCreator�N���X
//
//   Z�l�e�N�X�`�����쐬����w���p�[�N���X
//////////////////////////////
class CZTex
{
public:
	CZTex();
	~CZTex();

	// ���������\�b�h
	bool Init(UINT ZTexWidth, UINT ZTexHeight, D3DFORMAT ZTexFormat = D3DFMT_A8R8G8B8);

	// �`��ΏۃI�u�W�F�N�g�̃��[���h�ϊ��s���ݒ�
	void SetWorldMatrix(D3DXMATRIX *pMat);

	// �r���[�s���ݒ�
	void SetViewMatrix(D3DXMATRIX *pMat);

	// �ˉe�ϊ��s���ݒ�
	void SetProjMatrix(D3DXMATRIX *pMat);

	// �`��̊J�n��錾����
	HRESULT Begin();

	// �`��̏I����錾����
	HRESULT End();

	// �p�X�̊J�n��錾����
	HRESULT BeginPass();

	// �p�X�̏I����錾����
	HRESULT EndPass();

	// �o�^����Ă���p�����[�^�����G�t�F�N�g�ɃZ�b�g
	bool SetParamToEffect();

	// Z�l�e�N�X�`�����擾����
	IDirect3DTexture9 *GetZTex(){ return m_pZTex; }

	static CZTex *Create(UINT ZTexWidth, UINT ZTexHeight, D3DFORMAT ZTexFormat);

private:
	IDirect3DTexture9 *m_pZTex;		// Z�l�e�N�X�`��
	IDirect3DSurface9 *m_pZTexSurf;	// Z�l�e�N�X�`���T�[�t�F�C�X
	IDirect3DSurface9 *m_pDepthBuff;	// �[�x�o�b�t�@
	IDirect3DSurface9 *m_pDevBuffer;	// �f�o�C�X�o�b�N�o�b�t�@
	IDirect3DSurface9 *m_pDevDepth;	// �f�o�C�X�[�x�o�b�t�@
	ID3DXEffect *m_pEffect;			// Z�l�v���b�g�G�t�F�N�g
	D3DXMATRIX m_matWorld;						// ���[���h�ϊ��s��
	D3DXMATRIX m_matView;						// �r���[�ϊ��s��
	D3DXMATRIX m_matProj;						// �ˉe�ϊ��s��
	D3DXHANDLE m_hWorldMat;						// ���[���h�ϊ��s��n���h��
	D3DXHANDLE m_hViewMat;						// �r���[�ϊ��s��n���h��
	D3DXHANDLE m_hProjMat;						// �ˉe�ϊ��s��n���h��
	D3DXHANDLE m_hTechnique;					// �e�N�j�b�N�ւ̃n���h��
};