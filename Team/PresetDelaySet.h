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

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> e1265ec22361454c26360ce27e721e0a1665dc3a
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
<<<<<<< HEAD
=======
=======
	static CPresetDelaySet *Create(int nArray, D3DXVECTOR3 pos);
	static CPresetDelaySet *Create(string sName, D3DXVECTOR3 pos);
	void Move(D3DXVECTOR3 move);

	bool GetbMove(void) { return m_bMove; }

private:
	D3DXVECTOR3 m_pos;
	int m_nDelay;
	int m_nCallCnt;
	int m_nArray;
	bool m_bMove;

	vector<CPresetEffect*> m_vPreset;
};
>>>>>>> edf369e2fe44aed194aa4aed39d2958e583283af
>>>>>>> e1265ec22361454c26360ce27e721e0a1665dc3a

#endif