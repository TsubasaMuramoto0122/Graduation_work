//=============================================================================
// 3D�G�t�F�N�g���� [BillEffect.h]
// Author : �����G��
//=============================================================================
#ifndef _BILLEFFECT_H_
#define _BILLEFFECT_H_

#include "main.h"
#include "Effect_base.h"

class CBillEffect : public CEffect_base
{
public:
	typedef enum
	{
		ANIMPATTERN_NOMAL,	//���ʂɃA�j���[�V����
		ANIMPATTERN_RAND,	//�p�^�[���̒����烉���_���ɕ\��
		ANIMPATTERN_MAX,
	} ANIMPATTERN;		//�A�j���[�V�����p�^�[���̎��

	CBillEffect(PRIORITY nPriority);
	virtual ~CBillEffect();

	virtual HRESULT Init(D3DXVECTOR3 Size,
		D3DXVECTOR3 MinSize,
		D3DCOLORVALUE color,
		D3DCOLORVALUE Mincolor,
		int nTex, int nLife,
		D3DXVECTOR2 TexNum,
		D3DXVECTOR2 TexMove,
		int nAnimCounter,
		D3DXVECTOR2 nSplit,
		ANIMPATTERN AnimPattern);	//������

	virtual void Uninit();	//�I��
	virtual void Update();	//�X�V
	virtual void Draw();	//�`��

	void SetTexture(int nTex);		//�w�肳�ꂽ�ԍ��̃e�N�X�`����\���悤��
protected:
	bool m_bUninit;	//�����t���O
	int m_nSynthenic;	//����
	D3DXVECTOR3 m_MinSize;		//�傫���ϓ��l
	D3DXVECTOR3 m_Size;			//�T�C�Y
	ANIMPATTERN m_AnimPattern;	//�A�j���[�V�����p�^�[���̓���
private:

	//�J���[
	D3DCOLORVALUE m_Color;

	//�J���[����
	D3DCOLORVALUE m_MinColor;

	int m_nLife;	//����
};

#endif