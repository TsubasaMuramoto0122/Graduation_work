//=============================================================================
// �x���t���G�t�F�N�g�v���Z�b�g�Ăяo���N���X
// Author : ������
//=============================================================================
#ifndef _PRESETDELAYSET_H_
#define _PRESETDELAYSET_H_
#include "scene3d.h"
#include "main.h"
#include <string>

//=============================================================================
// �N���X��`
//=============================================================================
class CPresetDelaySet : public CScene3D
{
public:
	CPresetDelaySet(PRIORITY nPriority);	// �R���X�g���N�^
	~CPresetDelaySet();						// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos);	 // ������
	void Uninit();					 // �I��
	void Update();					 // �X�V
	void Draw();					 // �`��

	static CPresetDelaySet *Create(int nArray, D3DXVECTOR3 pos);
	static CPresetDelaySet *Create(std::string sName, D3DXVECTOR3 pos);

private:
	D3DXVECTOR3 m_pos;
	int m_nDelay;
	int m_nCallCnt;
	int m_nArray;
	bool m_bUninit;
};									 

#endif