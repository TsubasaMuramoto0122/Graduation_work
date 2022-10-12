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
	m_moveOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fObjectiveRot = 0.0f;
	m_fNumRot = 0.0f;
	m_fSpeed = 0.0f;
	m_bRotate = false;
	m_bDodge = false;
	m_bAttack = false;
	m_bDamage = false;
	m_nDodgeCount = 0;
	m_nDodgeCoolTime = 0;
	m_nAttackCount = 0;
	m_nAttackCoolTime = 0;
	m_nKnockBackCount = 0;
	m_nStanCount = 0;
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
	m_moveOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fObjectiveRot = 0.0f;
	m_fNumRot = 0.0f;
	m_fSpeed = PLAYER_MOVE_SPEED;
	m_bRotate = false;
	m_bDodge = false;
	m_bRotate = false;
	m_bDodge = false;
	m_bAttack = false;
	m_bDamage = false;
	m_nDodgeCount = 0;
	m_nDodgeCoolTime = PLAYER_DODGE_COOLTIME;
	m_nAttackCount = 0;
	m_nAttackCoolTime = PLAYER_ATTACK_COOLTIME;
	m_nKnockBackCount = 0;
	m_nStanCount = 0;
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
	m_moveOld = m_move;

	//---------------------------------------------------
	// 重力
	//---------------------------------------------------
	if (m_bDamage == true && pPlayer->GetLand() == false)
	{
		m_move.y -= PLAYER_GRAVITY_DAMAGE;
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

	//---------------------------------------------------
	// 基本アクション
	//---------------------------------------------------
	// 攻撃していないなら
	if (m_bAttack == false)
	{
		// 回避処理
		Dodge(pPlayer);
	}

	// 回避・攻撃の両方をしていないなら
	if (m_bDodge == false && m_bAttack == false)
	{
		// 被ダメージ状態じゃないなら
		if (m_bDamage == false)
		{
			// 移動処理
			Move(pPlayer);
		}
	}

	// 回避していないなら
	if (m_bDodge == false)
	{
		// 攻撃処理
		Attack(pPlayer);
	}

	// 被ダメージ処理
	TakeDamage(pPlayer);

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

	// カメラの取得
	CCamera *pCamera = CManager::GetRenderer()->GetCamera();
	float rotCamera = 0.0f;

	if (pCamera != NULL)
	{
		// カメラの向き取得
		rotCamera = pCamera->GetRotY();
	}

	int nLeft = 0, nRight = 0, nUp = 0, nDown = 0;

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
	}

	//***********************************************************************
	// 移動 (キーボードＷ/Ａ/Ｓ/Ｄ または パッド左スティック)
	//***********************************************************************
	//左移動
	if (pKeyboard->GetPress(nLeft) == true /*||
										   pGamePad->LeftStickX() > 0*/)
	{
		//左奥移動
		if (pKeyboard->GetPress(nUp) == true /*||
											   pGamePad->LeftStickY() > 0*/)
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
		else if (pKeyboard->GetPress(nDown) == true /*||
													pGamePad->LeftStickY() < 0*/)
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
	else if (pKeyboard->GetPress(nRight) == true /*||
												pGamePad->LeftStickX() < 0*/)
	{
		//右奥移動
		if (pKeyboard->GetPress(nUp) == true /*||
											   pGamePad->LeftStickY() > 0*/)
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
		else if (pKeyboard->GetPress(nDown) == true /*||
													pGamePad->LeftStickY() < 0*/)
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
	else if (pKeyboard->GetPress(nUp) == true /*||
												pGamePad->LeftStickY() > 0*/)
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
	else if (pKeyboard->GetPress(nDown) == true /*||
												pGamePad->LeftStickY() < 0*/)
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
// 回避処理
//=============================================================================
void CControlPlayer::Dodge(CPlayer *pPlayer)
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

	// 回避中じゃないなら
	if (m_bDodge == false)
	{
		// クールタイムのカウントを増やす
		m_nDodgeCoolTime++;

		// クールタイムを過ぎているなら
		if (m_nDodgeCoolTime >= PLAYER_DODGE_COOLTIME)
		{
			//***********************************************************************
			// 回避 (キーボードShift または パッドXボタン)
			//***********************************************************************
			if (pKeyboard->GetTrigger(DIK_LSHIFT) == true/* ||
														 pGamePad->GetTrigger(CGamePad::DIP_X) == true*/)
			{
				// 回避している状態に設定
				m_bDodge = true;
			}
		}
	}
	// 回避中
	else if (m_bDodge == true)
	{
		// クールタイムをリセット
		m_nDodgeCoolTime = 0;

		// カウントを増やす
		m_nDodgeCount++;

		// 回避時間の間なら
		if (m_nDodgeCount <= PLAYER_DODGE_TIME)
		{
			// プレイヤーの向きを取得し、直進させる
			D3DXVECTOR3 rot = pPlayer->GetRot();
			m_move.x += -sinf(rot.y) * PLAYER_DODGE;
			m_move.z += -cosf(rot.y) * PLAYER_DODGE;
		}
	
		// 回避後、硬直時間が過ぎたら
		if (m_nDodgeCount > PLAYER_DODGE_WAITTIME + PLAYER_DODGE_TIME)
		{
			// 回避していない状態にする
			m_bDodge = false;
			m_nDodgeCount = 0;
		}
	}
}

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

	// 回避中じゃないなら
	if (m_bAttack == false)
	{
		// クールタイムのカウントを増やす
		m_nAttackCoolTime++;

		// クールタイムを過ぎているなら
		if (m_nAttackCoolTime >= PLAYER_ATTACK_COOLTIME)
		{
			int nAttack = 0;

			switch (pPlayer->GetType())
			{
			case CPlayer::PLAYER_TYPE_1P:
				nAttack = DIK_SPACE;
				break;

			case CPlayer::PLAYER_TYPE_2P:
				nAttack = DIK_RSHIFT;
				break;
			}

			//***********************************************************************
			// 攻撃 (キーボードSpaceキー または パッドBボタン)
			//***********************************************************************
			if (pKeyboard->GetTrigger(nAttack) == true/* ||
														 pGamePad->GetTrigger(CGamePad::DIP_B) == true*/)
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
		m_move.x += 0.0f;
		m_move.z += 0.0f;

		// 攻撃時間の間なら
		if (m_nAttackCount <= PLAYER_ATTACK_TIME)
		{
			if (m_nAttackCount == 0)
			{
				// 当たり判定を発生させる
				D3DXVECTOR3 pos = pPlayer->GetPos();
				m_pCollision = CCollisionSphere::Create(D3DXVECTOR3(pos.x, pos.y + (pPlayer->GetRadius() / 2), pos.z), pPlayer->GetRadius() * 3,
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
	if (pPlayer->GetState() == CPlayer::PLAYER_STATE_DAMAGE && m_bDamage == false)
	{
		m_bDamage = true;
		pPlayer->SetLand(false);
	}

	if (m_bDamage == true)
	{
		if (pPlayer->GetLand() == false)
		{
			if (m_nKnockBackCount <= PLAYER_KNOCKBACK_TIME)
			{
				m_move.y += PLAYER_KNOCKBACK_JUMP;
			}

			// プレイヤーの向きを取得し、後退させる
			D3DXVECTOR3 rot = pPlayer->GetRot();
			m_move.x += sinf(rot.y) * PLAYER_KNOCKBACK;
			m_move.z += cosf(rot.y) * PLAYER_KNOCKBACK;

			// カウントを進める
			m_nKnockBackCount++;
		}
		else if (pPlayer->GetLand() == true)
		{
			if (m_nStanCount > PLAYER_KNOCKBACK_STAN)
			{
				m_bDamage = false;
				m_nKnockBackCount = 0;
				m_nStanCount = 0;
			}

			// カウントを進める
			m_nStanCount++;
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