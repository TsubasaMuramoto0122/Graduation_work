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
class CStraight3D;
class CFieldEffect;
class CPlayer;
class CPresetEffect;

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
	static CPresetDelaySet *Create(int nArray, D3DXVECTOR3 pos);
	static CPresetDelaySet *Create(string sName, D3DXVECTOR3 pos);

	// �ړ�
	void Move(D3DXVECTOR3 move);

	// �ړ�����擾
	bool GetbMove(void) { return m_bMove; }

private:
	D3DXVECTOR3 m_pos;	// �ʒu
	int m_nDelay;		// �x��
	int m_nCallCnt;		// �R�[���J�E���g
	int m_nArray;		// �z��
	bool m_bMove;		// �ړ�����

	vector<CPresetEffect*> m_vPreset;	// �v���Z�b�g
};									 

#endif