//=============================================================================
// プレイヤー操作処理 [control_player.cpp]
// Author : Kusakari Kakeru
//=============================================================================
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "control_player.h"
#include "manager.h"
#include "keyboard.h"
#include "gamepad.h"
#include "player.h"
//#include "motion_player.h"
#include "camera.h"
#include "sound.h"
#include "model.h"
#include "player.h"
#include "renderer.h"
#include "collision_sphere.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CControlPlayer::CControlPlayer()
{
	// 変数のクリア
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fObjectiveRot = 0.0f;
	m_fNumRot = 0.0f;
	m_fSpeed = 0.0f;
	m_bRotate = false;
	m_bJump = false;
	m_bAttack = false;
	m_bDamage = false;
	//m_bDodge = false;
	m_nAttackCount = 0;
	m_nAttackCoolTime = 0;
	m_nStanCount = 0;
	//m_nDodgeCount = 0;
	//m_nDodgeCoolTime = 0;
	m_pCollision = NULL;
}

//=============================================================================
// デストラクタ
//=============================================================================
CControlPlayer::~CControlPlayer()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CControlPlayer::Init(void)
{
	// 変数の初期化
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fObjectiveRot = 0.0f;
	m_fNumRot = 0.0f;
	m_fSpeed = PLAYER_MOVE_SPEED;
	m_bRotate = false;
	m_bJump = false;
	m_bAttack = false;
	m_bDamage = false;
	//m_bDodge = false;
	m_nAttackCount = 0;
	m_nAttackCoolTime = PLAYER_ATTACK_COOLTIME;
	m_nStanCount = 0;
	//m_nDodgeCount = 0;
	//m_nDodgeCoolTime = PLAYER_DODGE_COOLTIME;
	m_pCollision = NULL;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CControlPlayer::Uninit(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void CControlPlayer::Update(CScene *pScene)
{
	// 引数のポインタをプレイヤークラスのポインタにキャスト
	CPlayer *pPlayer = NULL;
	pPlayer = (CPlayer*)pScene;

	// サウンド取得処理

	// キーボード取得処理
	CKeyboard *pKeyboard;
	pKeyboard = CManager::GetKeyboard();

	// ゲームパッド取得処理
	CGamePad *pGamePad;
	pGamePad = CManager::GetGamepad();

	// 移動量を設定
	m_move = pPlayer->GetMove();

	//---------------------------------------------------
	// 重力
	//---------------------------------------------------
	if (m_bDamage == true && pPlayer->GetLand() == false)
	{
		m_move.y -= PLAYER_GRAVITY_DAMAGE;
	}
	else if (pPlayer->GetDefeat() == true)
	{
		m_move.y -= PLAYER_GRAVITY_DEFEAT;
	}
	else
	{
		m_move.y -= PLAYER_GRAVITY;
	}

	// 重力が強くなりすぎたら重力の最大値で固定しておく
	if (m_move.y <= -PLAYER_MAX_GRAVITY)
	{
		m_move.y = -PLAYER_MAX_GRAVITY;
	}

	// 敗北していなかったら
	if (pPlayer->GetDefeat() == false)
	{
		// 被ダメージ処理
		TakeDamage(pPlayer);

		//---------------------------------------------------
		// 基本アクション
		//---------------------------------------------------
		// 被ダメージ状態じゃないなら
		if (m_bDamage == false)
		{
			// 攻撃していないなら
			if (m_bAttack == false)
			{
				// 移動処理
				Move(pPlayer);

				// ジャンプ処理
				Jump(pPlayer);
			}

			// 攻撃処理
			Attack(pPlayer);
		}
	}

	// 回避処理
	//Dodge(pPlayer);

	// 敗北時の処理
	Defeat(pPlayer);

	//---------------------------------------------------
	// モーション遷移
	//---------------------------------------------------

	//---------------------------------------------------
	// 慣性
	//---------------------------------------------------
	// 移動の慣性(詳しい処理は関数の中)
	MoveInteria();

	// 回転の慣性(詳しい処理は関数の中)
	Rotate(pPlayer);
}

//=============================================================================
// 生成処理
//=============================================================================
CControlPlayer *CControlPlayer::Create(void)
{
	// インスタンスの生成
	CControlPlayer *pControlPlayer = NULL;

	// ヌルチェック
	if (pControlPlayer == NULL)
	{
		// クラスの生成
		pControlPlayer = new CControlPlayer;
		if (pControlPlayer != NULL)
		{
			// 初期化処理
			pControlPlayer->Init();
		}
	}

	return pControlPlayer;
}

//=============================================================================
// 移動処理
//=============================================================================
void CControlPlayer::Move(CPlayer *pPlayer)
{
	// キーボード取得処理
	CKeyboard *pKeyboard;
	pKeyboard = CManager::GetKeyboard();

	// ゲームパッド取得処理
	CGamePad *pGamePad;
	pGamePad = CManager::GetGamepad();

	// カメラの向きを取得
	CCamera *pCamera = CManager::GetRenderer()->GetCamera();
	float rotCamera = pCamera->GetRotY();

	// 入力情報を分ける
	int nLeft = 0, nRight = 0, nUp = 0, nDown = 0, nPlayerNum = 0;
	nPlayerNum = (int)pPlayer->GetType();
	switch (pPlayer->GetType())
	{
	case CPlayer::PLAYER_TYPE_1P:
		nLeft = DIK_A;
		nRight = DIK_D;
		nUp = DIK_W;
		nDown = DIK_S;
		break;
	case CPlayer::PLAYER_TYPE_2P:
		nLeft = DIK_LEFT;
		nRight = DIK_RIGHT;
		nUp = DIK_UP;
		nDown = DIK_DOWN;
		break;
	case CPlayer::PLAYER_TYPE_3P:
		break;
	case CPlayer::PLAYER_TYPE_4P:
		break;
	default:
		break;
	}

	//***********************************************************************
	// 移動 (キーボードＷ/Ａ/Ｓ/Ｄ または パッド左スティック)
	//***********************************************************************
	//左移動
	if (pKeyboard->GetPress(nLeft) == true ||
		pGamePad->GetPress(CGamePad::PAD_INPUTTYPE_LSTICK_LEFT, nPlayerNum) == true)
	{
		//左奥移動
		if (pKeyboard->GetPress(nUp) == true ||
			pGamePad->GetPress(CGamePad::PAD_INPUTTYPE_LSTICK_UP, nPlayerNum) == true)
		{
			//移動量加算
			m_move.x += -cosf(rotCamera + D3DX_PI / 4.0f) * m_fSpeed;
			m_move.z += +sinf(rotCamera + D3DX_PI / 4.0f) * m_fSpeed;

			//目的の向きを設定
			m_fObjectiveRot = rotCamera + D3DX_PI / 1.5f;
			//回転の慣性をオンにする
			m_bRotate = true;
		}
		//左手前移動
		else if (pKeyboard->GetPress(nDown) == true ||
			pGamePad->GetPress(CGamePad::PAD_INPUTTYPE_LSTICK_DOWN, nPlayerNum) == true)
		{
			//移動量加算
			m_move.x += -cosf(rotCamera - D3DX_PI / 4.0f) * m_fSpeed;
			m_move.z += +sinf(rotCamera - D3DX_PI / 4.0f) * m_fSpeed;

			//目的の向きを設定
			m_fObjectiveRot = rotCamera + D3DX_PI / 4.0f;
			//回転の慣性をオンにする
			m_bRotate = true;
		}
		else
		{
			//移動量加算
			m_move.x += -cosf(rotCamera) * m_fSpeed;
			m_move.z += +sinf(rotCamera) * m_fSpeed;

			//目的の向きを設定
			m_fObjectiveRot = rotCamera + D3DX_PI / 2.0f;
			//回転の慣性をオンにする
			m_bRotate = true;
		}
	}
	//右移動
	else if (pKeyboard->GetPress(nRight) == true ||
		pGamePad->GetPress(CGamePad::PAD_INPUTTYPE_LSTICK_RIGHT, nPlayerNum) == true)
	{
		//右奥移動
		if (pKeyboard->GetPress(nUp) == true ||
			pGamePad->GetPress(CGamePad::PAD_INPUTTYPE_LSTICK_UP, nPlayerNum) == true)
		{
			//移動量加算
			m_move.x += +cosf(rotCamera - D3DX_PI / 4.0f) * m_fSpeed;
			m_move.z += -sinf(rotCamera - D3DX_PI / 4.0f) * m_fSpeed;

			//目的の向きを設定
			m_fObjectiveRot = rotCamera - (D3DX_PI / 4.0f) * 3.0f;
			//回転の慣性をオンにする
			m_bRotate = true;
		}
		//右手前移動
		else if (pKeyboard->GetPress(nDown) == true ||
			pGamePad->GetPress(CGamePad::PAD_INPUTTYPE_LSTICK_DOWN, nPlayerNum) == true)
		{
			//移動量加算
			m_move.x += +cosf(rotCamera + D3DX_PI / 4.0f) * m_fSpeed;
			m_move.z += -sinf(rotCamera + D3DX_PI / 4.0f) * m_fSpeed;

			//目的の向きを設定
			m_fObjectiveRot = rotCamera - D3DX_PI / 4.0f;
			//回転の慣性をオンにする
			m_bRotate = true;
		}
		else
		{
			//移動量加算
			m_move.x += +cosf(rotCamera) * m_fSpeed;
			m_move.z += -sinf(rotCamera) * m_fSpeed;

			//目的の向きを設定
			m_fObjectiveRot = rotCamera - D3DX_PI / 2.0f;
			//回転の慣性をオンにする
			m_bRotate = true;
		}
	}
	//奥移動
	else if (pKeyboard->GetPress(nUp) == true ||
		pGamePad->GetPress(CGamePad::PAD_INPUTTYPE_LSTICK_UP, nPlayerNum) == true)
	{
		//移動量加算
		m_move.z += +cosf(rotCamera) * m_fSpeed;
		m_move.x += +sinf(rotCamera) * m_fSpeed;

		//目的の向きを設定
		m_fObjectiveRot = rotCamera + D3DX_PI;
		//回転の慣性をオンにする
		m_bRotate = true;
	}
	//手前移動
	else if (pKeyboard->GetPress(nDown) == true ||
		pGamePad->GetPress(CGamePad::PAD_INPUTTYPE_LSTICK_DOWN, nPlayerNum) == true)
	{
		//移動量加算
		m_move.z += -cosf(rotCamera) * m_fSpeed;
		m_move.x += -sinf(rotCamera) * m_fSpeed;

		//目的の向きを設定
		m_fObjectiveRot = rotCamera;
		//回転の慣性をオンにする
		m_bRotate = true;
	}
}

//=============================================================================
// ジャンプ処理
//=============================================================================
void CControlPlayer::Jump(CPlayer *pPlayer)
{
	// キーボード取得処理
	CKeyboard *pKeyboard;
	pKeyboard = CManager::GetKeyboard();

	// ゲームパッド取得処理
	CGamePad *pGamePad;
	pGamePad = CManager::GetGamepad();

	// モーション取得処理
	/*CMotionPlayer *pMotionPlayer = NULL;
	pMotionPlayer = pPlayer->GetMotionPlayer();*/

	// 入力情報を分ける
	int nJump = 0, nPlayerNum = 0;
	switch (pPlayer->GetType())
	{
	case CPlayer::PLAYER_TYPE_1P:
		nJump = DIK_SPACE;
		nPlayerNum = 0;
		break;
	case CPlayer::PLAYER_TYPE_2P:
		nJump = DIK_RCONTROL;
		nPlayerNum = 1;
		break;
	case CPlayer::PLAYER_TYPE_3P:
		nPlayerNum = 2;
		break;
	case CPlayer::PLAYER_TYPE_4P:
		nPlayerNum = 3;
		break;
	default:
		break;
	}

	// プレイヤーが着地しているなら
	if (pPlayer->GetLand() == true)
	{
		//***********************************************************************
		// ジャンプ (キーボードSpace または パッドAボタン)
		//***********************************************************************
		if (pKeyboard->GetTrigger(nJump) == true ||
			pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_A, nPlayerNum) == true)
		{
			// Y方向の移動量を0に
			m_move.y = 0.0f;

			// 移動量をジャンプ力ぶん加算
			m_move.y = PLAYER_JUMP;

			// ジャンプをさせ、着地していないに設定
			m_bJump = true;
			pPlayer->SetLand(false);

			m_bJump = true;
		}
		else
		{
			// 着地したらまたジャンプを可能にする
			m_bJump = false;
		}
	}
}

//=============================================================================
// 回避処理
//=============================================================================
//void CControlPlayer::Dodge(CPlayer *pPlayer)
//{
//	// キーボード取得処理
//	CKeyboard *pKeyboard;
//	pKeyboard = CManager::GetKeyboard();
//
//	// ゲームパッド取得処理
//	CGamePad *pGamePad;
//	pGamePad = CManager::GetGamepad();
//
//	// モーション取得処理
//	//CMotionPlayer *pMotionPlayer = NULL;
//	//pMotionPlayer = pPlayer->GetMotionPlayer();
//
//	// 回避中じゃないなら
//	if (m_bDodge == false)
//	{
//		// クールタイムのカウントを増やす
//		m_nDodgeCoolTime++;
//
//		// クールタイムを過ぎているなら
//		if (m_nDodgeCoolTime >= PLAYER_DODGE_COOLTIME)
//		{
//			//***********************************************************************
//			// 回避 
//			//***********************************************************************
//			if (pKeyboard->GetTrigger(DIK_LSHIFT) == true/* ||
//														 pGamePad->GetTrigger(CGamePad::DIP_X) == true*/)
//			{
//				// 回避している状態に設定
//				m_bDodge = true;
//			}
//		}
//	}
//	// 回避中
//	else if (m_bDodge == true)
//	{
//		// クールタイムをリセット
//		m_nDodgeCoolTime = 0;
//
//		// カウントを増やす
//		m_nDodgeCount++;
//
//		// 回避時間の間なら
//		if (m_nDodgeCount <= PLAYER_DODGE_TIME)
//		{
//			// プレイヤーの向きを取得し、直進させる
//			D3DXVECTOR3 rot = pPlayer->GetRot();
//			m_move.x += -sinf(rot.y) * PLAYER_DODGE;
//			m_move.z += -cosf(rot.y) * PLAYER_DODGE;
//		}
//
//		// 回避後、硬直時間が過ぎたら
//		if (m_nDodgeCount > PLAYER_DODGE_WAITTIME + PLAYER_DODGE_TIME)
//		{
//			// 回避していない状態にする
//			m_bDodge = false;
//			m_nDodgeCount = 0;
//		}
//	}
//}

//=============================================================================
// 攻撃処理
//=============================================================================
void CControlPlayer::Attack(CPlayer *pPlayer)
{
	// キーボード取得処理
	CKeyboard *pKeyboard;
	pKeyboard = CManager::GetKeyboard();

	// ゲームパッド取得処理
	CGamePad *pGamePad;
	pGamePad = CManager::GetGamepad();

	// モーション取得処理
	//CMotionPlayer *pMotionPlayer = NULL;
	//pMotionPlayer = pPlayer->GetMotionPlayer();

	// 入力情報を分ける
	int nAttack = 0, nPlayerNum = 0;
	switch (pPlayer->GetType())
	{
	case CPlayer::PLAYER_TYPE_1P:
		nAttack = DIK_LSHIFT;
		nPlayerNum = 0;
		break;
	case CPlayer::PLAYER_TYPE_2P:
		nAttack = DIK_RSHIFT;
		nPlayerNum = 1;
		break;
	case CPlayer::PLAYER_TYPE_3P:
		nPlayerNum = 2;
		break;
	case CPlayer::PLAYER_TYPE_4P:
		nPlayerNum = 3;
		break;
	default:
		break;
	}

	// 回避中じゃないなら
	if (m_bAttack == false)
	{
		// クールタイムのカウントを増やす
		m_nAttackCoolTime++;

		// クールタイムを過ぎているなら
		if (m_nAttackCoolTime >= PLAYER_ATTACK_COOLTIME)
		{
			//***********************************************************************
			// 攻撃 (キーボードSpaceキー または パッドBボタン)
			//***********************************************************************
			if (pKeyboard->GetTrigger(nAttack) == true ||
				pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_B, nPlayerNum) == true)
			{
				// 攻撃している状態に設定
				m_bAttack = true;
			}
		}
	}
	// 回避中
	else if (m_bAttack == true)
	{
		// クールタイムをリセット
		m_nAttackCoolTime = 0;

		// 攻撃中は動きを止める
		m_move.x = 0.0f;
		m_move.z = 0.0f;

		// 攻撃時間の間なら
		if (m_nAttackCount <= PLAYER_ATTACK_TIME)
		{
			if (m_nAttackCount == 0)
			{
				// 当たり判定を発生させる
				D3DXVECTOR3 pos = pPlayer->GetPos();
				m_pCollision = CCollisionSphere::Create(D3DXVECTOR3(pos.x, pos.y + pPlayer->GetRadius(), pos.z), pPlayer->GetRadius() * 3.0f,
					16, 16, CCollisionSphere::COLLISION_S_TYPE::COLLISION_S_TYPE_ATTACK, PLAYER_ATTACK_TIME);
				// どのプレイヤーの攻撃か設定
				m_pCollision->SetNumPlayer(pPlayer->GetType());
			}
		}

		// カウントを増やす
		m_nAttackCount++;

		// 攻撃後、硬直時間が過ぎたら
		if (m_nAttackCount > PLAYER_ATTACK_WAITTIME + PLAYER_ATTACK_TIME)
		{
			// 回避していない状態にする
			m_bAttack = false;
			m_nAttackCount = 0;
		}
	}
}

//=============================================================================
// 被ダメージ処理
//=============================================================================
void CControlPlayer::TakeDamage(CPlayer *pPlayer)
{
	// プレイヤーの状態が<吹っ飛び>になったかつ、ダメージを受けていなかったら
	if (pPlayer->GetState() == CPlayer::PLAYER_STATE_BLOWAWAY && m_bDamage == false)
	{
		// ダメージを受けた状態にし、着地していない状態にする
		m_bDamage = true;
		pPlayer->SetLand(false);

		// 目的の向きを設定
		D3DXVECTOR3 rot = pPlayer->GetRot();
		m_fObjectiveRot = rot.y;
	}

	// ダメージ中
	if (m_bDamage == true)
	{
		// 着地していないなら
		if (pPlayer->GetLand() == false)
		{
			// プレイヤーの正面から逆方向へ後退させる
			D3DXVECTOR3 rot = pPlayer->GetRot();
			m_move.x = sinf(rot.y) * PLAYER_KNOCKBACK;
			m_move.z = cosf(rot.y) * PLAYER_KNOCKBACK;
		}
		// 着地しているなら
		else if (pPlayer->GetLand() == true)
		{
			// カウントを進める
			m_nStanCount++;

			if (m_nStanCount > PLAYER_KNOCKBACK_STAN)
			{
				m_bDamage = false;
				m_nStanCount = 0;
			}
		}
	}
}

//=============================================================================
// 敗北処理
//=============================================================================
void CControlPlayer::Defeat(CPlayer *pPlayer)
{
	// プレイヤーの状態が<吹っ飛び>になったかつ、敗北したら
	if (pPlayer->GetState() == CPlayer::PLAYER_STATE_BLOWAWAY && pPlayer->GetDefeat() == true)
	{
		// 着地していない状態にする
		pPlayer->SetLand(false);

		// 目的の向きを設定
		D3DXVECTOR3 rot = pPlayer->GetRot();
		m_fObjectiveRot = rot.y;
	}

	// 敗北
	if (pPlayer->GetDefeat() == true)
	{
		// 着地していないなら
		if (pPlayer->GetLand() == false)
		{
			// プレイヤーの正面から直進させる
			D3DXVECTOR3 rot = pPlayer->GetRot();
			m_move.x = -sinf(rot.y) * PLAYER_DEFEAT_KNOCKBACK;
			m_move.z = -cosf(rot.y) * PLAYER_DEFEAT_KNOCKBACK;
		}

		// 位置を取得し、Y方向において0から下の位置に行かないようにする
		D3DXVECTOR3 pos = pPlayer->GetPos();
		if (pos.y <= 0)
		{
			pos.y = 0.0f;
			m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
	}
}

//=============================================================================
// 移動の慣性についての処理
//=============================================================================
void CControlPlayer::MoveInteria(void)
{
	// 慣性の減算
	m_move.z *= PLAYER_INTERIA_SUBTRACTION;
	m_move.x *= PLAYER_INTERIA_SUBTRACTION;

	// 移動量が既定の値になったら0にする
	if (m_move.x <= PLAYER_MOVE_STOP_COUNT && m_move.x >= -PLAYER_MOVE_STOP_COUNT)
	{
		m_move.x = 0.0f;
	}
	if (m_move.z <= PLAYER_MOVE_STOP_COUNT && m_move.z >= -PLAYER_MOVE_STOP_COUNT)
	{
		m_move.z = 0.0f;
	}
}

//=============================================================================
// 回転処理
//=============================================================================
void CControlPlayer::Rotate(CPlayer *pPlayer)
{
	// プレイヤーの向きを取得
	D3DXVECTOR3 rotPlayer = pPlayer->GetRot();

	// 回転させる状態なら
	if (m_bRotate == true)
	{
		// 目的の向きを計算
		if (m_fObjectiveRot > D3DX_PI)
		{
			m_fObjectiveRot = -D3DX_PI - (D3DX_PI - m_fObjectiveRot);
		}
		else if (m_fObjectiveRot < -D3DX_PI)
		{
			m_fObjectiveRot = D3DX_PI - (-D3DX_PI - m_fObjectiveRot);
		}

		// プレイヤーの現在の向きごとにそれぞれ向きを変える量を計算
		if (rotPlayer.y < 0.0f && -rotPlayer.y + m_fObjectiveRot > D3DX_PI)
		{
			m_fNumRot = (-D3DX_PI - rotPlayer.y) + -(D3DX_PI - m_fObjectiveRot);
		}
		else if (rotPlayer.y >= D3DX_PI / 2.0f && rotPlayer.y - m_fObjectiveRot > D3DX_PI)
		{
			m_fNumRot = (D3DX_PI - rotPlayer.y) - (-D3DX_PI - m_fObjectiveRot);
		}
		else
		{
			m_fNumRot = (m_fObjectiveRot - rotPlayer.y);
		}

		// プレイヤーの向きに加算
		rotPlayer.y += m_fNumRot * 0.2f;

		// 既定の値に達したら回転をやめる
		if (rotPlayer.y - m_fObjectiveRot < 0.001f && rotPlayer.y - m_fObjectiveRot > -0.001f)
		{
			m_bRotate = false;
		}
	}

	// 向きを3.14から-3.14の値の範囲内に収める
	if (rotPlayer.y > D3DX_PI)
	{
		rotPlayer.y -= D3DX_PI * 2.0f;
	}
	else if (rotPlayer.y < -D3DX_PI)
	{
		rotPlayer.y += D3DX_PI * 2.0f;
	}

	// 向きを反映
	pPlayer->SetRot(rotPlayer);
}