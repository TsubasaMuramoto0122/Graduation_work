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
class CCPU;

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
	void ZTexDraw();

	OBJTYPE GetObjType() { return OBJECTTYPE_BOMB; }
	float GetRadius() { return m_fRadius; }
	int GetTime() { return m_nTime; }
	CDanger *GetDanger() { return m_pDanger; }
	
	void SetCPU(CCPU *pCPU) { m_pCPU = pCPU; }
	CCPU *GetCPU() { return m_pCPU; }

	static CBomb *SearchBomb(D3DXVECTOR3 pos, CCPU *pCPU);
	static CModel *m_paModel[MAX_BOMB];				//���e�̃��f���S��
	static int m_nSound[MAX_BOMB];					//�������̉��S��
	static void LoadModel(int nCnt, const char *aModelName) { m_paModel[nCnt] = CModel::Create(aModelName); }	//���f���f�[�^�ǂݍ���
	static void LoadSound(int nCnt, int nSound) { m_nSound[nCnt] = nSound; }	//���f���f�[�^�ǂݍ���
	static void UnLoad();							//���f���f�[�^�̂Ă�

private:
	virtual void Explosion(D3DXVECTOR3 pos) = 0;	//��������
	void Flash();									//�����͈͂̓_��(���������邩������₷���悤��)
	void TimeDec(D3DXVECTOR3 pos);					//�����̌���
	D3DXVECTOR3 Bound(D3DXVECTOR3 pos);				//�o�E���h
	void MoveDown();								//�ړ��ʂ̌���
	D3DXVECTOR3 Predict(D3DXVECTOR3 pos);			//���e�_�̗\��
	void Clash();									//�v���C���[�̍U���ɓ��������Ƃ�
	void WallReflect();								//�ǔ���

	bool m_bBound;									//�o�E���h������
	bool m_bHit;									//�U��������������
	bool m_bLand;									//���n���Ă�
	int m_nTime;									//����
	int m_nFlash;									//�_��
	int m_nPlaySound;								//�Đ����鉹���ԍ�
	float m_fClear;									//�����x
	float m_fRadius;								//���a
	D3DXVECTOR3 m_move;								//�ړ���
	CCPU *m_pCPU;
	CModel *m_pModel;								//���f��
	CDanger *m_pDanger;								//�댯�͈�
	CCollisionSphere *m_pCollision;					//���̃R���W�����̃|�C���^

};
#endif