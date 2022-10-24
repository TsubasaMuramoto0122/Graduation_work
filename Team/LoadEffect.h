//=============================================================================
// エフェクト情報をロードさせる [Load.h]
// Author : 佐藤秀亮
//=============================================================================
#ifndef _LOADEFFECT_H_
#define _LOADEFFECT_H_

#include "main.h"

class CLoadEffect
{
public:
	CLoadEffect();
	~CLoadEffect();

	static void EffectStateLoad(const char *aFileName);	//エフェクトのステータス

	static int GetPresetTotal2D() { return m_Total2d; }
	static int GetPresetTotal3D() { return m_Total3d; }

	static void EffectOrder(const char *aFileName);	//エフェクトオーダー
	static int GetOrderTotal() { return m_OrderTotal; }
	static int GetFullOrder() { return m_FullOrder; }

private:
	static int m_Total2d;
	static int m_Total3d;

	static int m_OrderTotal;
	static int m_FullOrder;

};

#endif // !_LOADEFFECT_H_