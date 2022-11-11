//=============================================================================
// �x���t���G�t�F�N�g�v���Z�b�g�Ăяo���N���X
// Author : ������
//=============================================================================
#ifndef _PRESETDELAYSET_H_
#define _PRESETDELAYSET_H_
#include "scene3d.h"
#include "main.h"
#include <string>
#include <vector>
using namespace std;

//=============================================================================
// �O���錾
//=============================================================================
class CPlayer;

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

	// ����
	static CPresetDelaySet *Create(int nArray, D3DXVECTOR3 pos, CPlayer *pPlayer = nullptr);
	static CPresetDelaySet *Create(string sName, D3DXVECTOR3 pos, CPlayer *pPlayer = nullptr);

private:
	CPlayer *m_pPlayer;	// �v���C���[
	D3DXVECTOR3 m_pos;	// �ʒu
	int m_nDelay;		// �x��
	int m_nCallCnt;		// �R�[���J�E���g
	int m_nArray;		// �z��
};									 

#endif