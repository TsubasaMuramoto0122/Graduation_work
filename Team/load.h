//=============================================================================
//
// ���[�h���� [load.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _LOAD_H_
#define _LOAD_H_

#include "main.h"

class CLoad
{
public:
	CLoad();
	~CLoad();
	static void Load(const char *aFileName);		//�X�e�[�W���[�h
	static void SoundLoad(const char *aFileName);	//�T�E���h���[�h
	static void RankLoad(const char *aFileName);	//�����L���O���[�h
private:
};

#endif