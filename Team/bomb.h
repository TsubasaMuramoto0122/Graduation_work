//=============================================================================
//
// �{������ [bomb.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _BOMB_H_
#define _BOMB_H_

#include "main.h"
#include "scene3d.h"
#include "model.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


class CDanger;
class CCollisionSphere;

class CBomb : public CScene3D
{
public:
	//���e�̎��
	typedef enum
	{
		BOMB_NORMAL = 0,	//�m�[�}��
		BOMB_ICE,			//�X
		BOMB_FIRE,			//��
		BOMB_POISON,		//��
		BOMB_CONFUSION,		//����
		MAX_BOMB
	} BOMBTYPE;

	CBomb(PRIORITY Priority);
	~CBomb();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, BOMBTYPE BombType);
	void Uninit();
	void Update();
	void Draw();
	OBJTYPE GetObjType() { return OBJECTTYPE_BOMB; }
	float GetRadius() { return m_fRadius; }

	static CModel *m_paModel[MAX_BOMB];					//���e�̃��f���S��
	static void Load(int nCnt, const char *aModelName) { m_paModel[nCnt] = CModel::Create(aModelName); }	//���f���f�[�^�ǂݍ���
	static void UnLoad();								//���f���f�[�^�̂Ă�

private:
	virtual void Explosion(D3DXVECTOR3 pos) = 0;	//��������
	void Flash();									//�����͈͂̓_��(���������邩������₷���悤��)
	void TimeDec(D3DXVECTOR3 pos);					//�����̌���
	D3DXVECTOR3 Bound(D3DXVECTOR3 pos);				//�o�E���h
	void MoveDown();								//�ړ��ʂ̌���
	D3DXVECTOR3 Predict(D3DXVECTOR3 pos);			//���e�_�̗\��

	bool m_bBound;									//�o�E���h������
	bool m_bLand;									//���n���Ă�
	int m_nTime;									//����
	int m_nFlash;									//�_��
	float m_fClear;									//�����x
	float m_fRadius;								//���a
	D3DXVECTOR3 m_move;								//�ړ���
	CModel *m_pModel;								//���f��
	CDanger *m_pDanger;								//�댯�͈�
	CCollisionSphere *m_pCollision;					//���̃R���W�����̃|�C���^
};
#endif