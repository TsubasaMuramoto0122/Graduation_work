//=============================================================================
//
// ���[�h���� [load.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _LOAD_H_
#define _LOAD_H_

#include "main.h"

class CPlayer;

class CLoad
{
public:
	CLoad();
	~CLoad();
	static void StageLoad(const char *aFileName, CPlayer *pPlayer[4], int *pTime);	//�X�e�[�W���[�h
	static void SoundLoad(const char *aFileName);	//�T�E���h���[�h
	static void BombsLoad(const char *aFileName);	//���e���[�h
private:
};

#endif