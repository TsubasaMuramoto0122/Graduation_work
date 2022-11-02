//=============================================================================
// ���[�V�������� [motion.h]
// Author : ���� ��
//=============================================================================
#ifndef _MOTION_H_
#define _MOTION_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_MODEL_INFO		(64)	// ���f��(�p�[�c)�̍ő�l
#define MAX_KEY_INFO		(128)	// �L�[�̏��̍ő�l
#define MAX_MOTION_INFO		(128)	// �L�[�̏��̍ő�l

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CScene;

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CMotion
{
public:
	typedef enum
	{
		MOTION_TYPE_P1 = 0,
		MOTION_TYPE_P2,
		MOTION_TYPE_P3,
		MOTION_TYPE_P4,
		MOTION_TYPE_MAX
	} MOTION_TYPE;

	//�L�[�̍\����
	typedef struct
	{
		D3DXVECTOR3 pos;	//�ʒu
		D3DXVECTOR3 rot;	//����
	} KEY;

	//�L�[���̍\����
	typedef struct
	{
		int nFrame;					//�Đ��t���[��
		KEY aKey[MAX_MODEL_INFO];	//�e���f���̃L�[�v�f(�p�[�c�̍ő吔)
	} KEY_INFO;

	//���[�V�������̍\����
	typedef struct
	{
		int nLoop;							//���[�v���邩�ǂ���
		int nNumKey;						//�L�[�̑���
		KEY_INFO aKeyInfo[MAX_KEY_INFO];	//�L�[�̏��
	} MOTION_INFO;

	CMotion();													// �R���X�g���N�^
	virtual ~CMotion();											// �f�X�g���N�^
	HRESULT Init(CScene *pScene, MOTION_TYPE type);				// ����������
	void Uninit(void);											// �I������
	void Update(CScene *pScene);								// �X�V����
	static CMotion *Create(CScene *pScene, MOTION_TYPE type);	// ��������
	bool GetConnect(void);										// ���[�V���������擾����
	void SetMotion(int nType);									// ���[�V�����ݒ菈��
	int GetMotion(void) { return m_nType; }						// ���[�V�����擾����
	int GetNextMotion(void) { return m_nTypeNext; }				// ���̃��[�V�����擾����

private:
	int m_nMaxModelNum;								// ���f��(�p�[�c)�̍ő吔
	int m_nMaxMotionNum;							// ���[�V�����̍ő吔
	int m_nNumKey;									// �L�[��
	int m_nKey;										// ���݂̃L�[
	int m_nKeyNext;									// ���̃L�[
	int m_nKeyOld;									// 1�t���[���O�̃L�[
	int m_nType;									// ���݂̃��[�V�����^�C�v
	int m_nTypeNext;								// ���̃��[�V�����^�C�v
	float m_fCounter;								// ���[�V�����̃J�E���^�[
	bool m_bConnect;								// ���[�V�������������ǂ���
	MOTION_INFO m_aInfo[MAX_MOTION_INFO];			// ���[�V�������
	MOTION_TYPE m_type;								// ���

};
#endif	// _MOTION_H_