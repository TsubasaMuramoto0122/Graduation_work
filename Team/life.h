//=============================================================================
// ���C�t�Ǘ� [life.h]
// Author : Kusakari Kakeru
//=============================================================================
#ifndef _LIFE_H_
#define _LIFE_H_

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define MAX_LIFE_IMAGE	(4)		// ���C�t�̉摜�̍ő吔

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "ui.h"
//#include "DxLib.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CLifeUI : public CUI
{
public:
	CLifeUI(PRIORITY Priority);									// �R���X�g���N�^
	~CLifeUI();													// �f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 size);			// ����������
	void Uninit();												// �I������
	void Update();												// �X�V����
	void Draw();												// �`�揈��
	static CLifeUI *Create(D3DXVECTOR2 pos, D3DXVECTOR2 size);	// ��������
	void SetLifeBar(int nNowLife, int nMaxLife);				// ���C�t�o�[�̐ݒ菈��
	void SetOut();												// �A�E�g�ݒu

private:
	int m_nLife;												// ���C�t
	float m_fObjectiveSize;										// �ړI�̃T�C�Y
	float m_fMaxSize;											// �ő�̃T�C�Y
	D3DXVECTOR3 m_pos;											// �ʒu
	D3DXVECTOR2 m_size;											// �T�C�Y
	D3DXVECTOR2 m_barPos;										// �Q�[�W�����̈ʒu
	CUI *m_apUI[MAX_LIFE_IMAGE];								// UI�̃|�C���^
};
#endif //_LIFE_H_