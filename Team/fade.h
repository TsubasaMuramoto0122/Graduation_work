//=============================================================================
//
// �t�F�[�h���� [fade.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_
#include "main.h"
#include "manager.h"

class CFade
{
public:
	typedef enum
	{
		FADE_NONE = 0,
		FADE_IN,
		FADE_OUT,
		FADE_MAX
	} FADE;

	CFade();
	~CFade();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static FADE GetFade(void) { return m_fade; }
	static void SetFade(CManager::MODE modenext);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;	//���_�o�b�t�@�ւ̃|�C���^
	D3DXCOLOR m_FadeColor;						//�t�F�[�h�̐F
	static CManager::MODE m_mode;				//���[�h(�^�C�g���A�Q�[���A���U���getc...)
	static FADE m_fade;							//�t�F�[�h�̃��[�h(���邭�Ȃ邩�A�Â��Ȃ邩�A�������Ȃ���)

};
#endif