//=============================================================================
//
// ロード処理 [load.h]
// Author : 三上航世
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
	static void StageLoad(const char *aFileName, CPlayer *pPlayer[4], int *pTime);	//ステージロード
	static void SoundLoad(const char *aFileName);	//サウンドロード
	static void BombsLoad(const char *aFileName);	//爆弾ロード
private:
};

#endif