//=============================================================================
//
// ロード処理 [load.h]
// Author : 三上航世
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
	static void Load(const char *aFileName);		//ステージロード
	static void SoundLoad(const char *aFileName);	//サウンドロード
	static void RankLoad(const char *aFileName);	//ランキングロード
private:
};

#endif