//=============================================================================
// 3Dエフェクト処理 [BillEffect.h]
// Author : 佐藤秀亮
//=============================================================================
#ifndef _BILLEFFECT_H_
#define _BILLEFFECT_H_

#include "main.h"
#include "Effect_base.h"

class CBillEffect : public CEffect_base
{
public:
	typedef enum
	{
		ANIMPATTERN_NOMAL,	//普通にアニメーション
		ANIMPATTERN_RAND,	//パターンの中からランダムに表示
		ANIMPATTERN_MAX,
	} ANIMPATTERN;		//アニメーションパターンの種類

	CBillEffect(PRIORITY nPriority);
	virtual ~CBillEffect();

	virtual HRESULT Init(D3DXVECTOR3 Size,
		D3DXVECTOR3 MinSize,
		D3DCOLORVALUE color,
		D3DCOLORVALUE Mincolor,
		int nTex, int nLife,
		D3DXVECTOR2 TexNum,
		D3DXVECTOR2 TexMove,
		int nAnimCounter,
		D3DXVECTOR2 nSplit,
		ANIMPATTERN AnimPattern);	//初期化

	virtual void Uninit();	//終了
	virtual void Update();	//更新
	virtual void Draw();	//描画

	void SetTexture(int nTex);		//指定された番号のテクスチャを貼れるように
protected:
	bool m_bUninit;	//抹消フラグ
	int m_nSynthenic;	//合成
	D3DXVECTOR3 m_MinSize;		//大きさ変動値
	D3DXVECTOR3 m_Size;			//サイズ
	ANIMPATTERN m_AnimPattern;	//アニメーションパターンの動き
private:

	//カラー
	D3DCOLORVALUE m_Color;

	//カラー減衰
	D3DCOLORVALUE m_MinColor;

	int m_nLife;	//寿命
};

#endif