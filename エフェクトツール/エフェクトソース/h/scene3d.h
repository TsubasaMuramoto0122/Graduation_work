//=============================================================================
// �V�[������ [scene3d.h]
// Author : �����G��
//=============================================================================
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

#include "main.h"
#include "scene.h"

struct VERTEX_3D
{
	D3DXVECTOR3 pos; //���_���W
	D3DXVECTOR3 nor; //�@���x�N�g��
	D3DCOLOR col;    //���_�J���[
	D3DXVECTOR2 tex; //�e�N�X�`�����W
};

class CScene3D : public CScene
{
public:
	CScene3D(int nPriority);
	~CScene3D();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit();
	void Update();
	void Draw();
	D3DXMATRIX GetMatrix() const { return m_mtxWorld; }
	void SetMatrix(const D3DXMATRIX& mtx) { m_mtxWorld = mtx; }
	D3DXVECTOR3 GetRot() const { return m_rot; }
	void SetRot(const D3DXVECTOR3& rot) { m_rot = rot; }
	static CScene3D *Create(const D3DXVECTOR3& pos);


private:
	D3DXVECTOR3 m_rot; //����
	D3DXMATRIX m_mtxWorld; //���[���h�}�g���b�N�X
};
#endif
