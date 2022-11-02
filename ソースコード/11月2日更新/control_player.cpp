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
#include "motion.h"
#include "camera.h"
#include "sound.h"
#include "model.h"
#include "player.h"
#include "renderer.h"
#include "collision_sphere.h"
#include "pauseui.h"
#include "fade.h"

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
int CControlPlayer::m_nPause = 0;
int CControlPlayer::m_nSelectPause = 0;
CPauseUI *CControlPlayer::m_pUI[3] = {};

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
	//m_bJump = false;
	m_bAttack = false;
	m_bDamage = false;
	m_bSliding = false;
	m_bDefeat = false;
	m_nSlidingCount = 0;
	m_nSlidingCoolTime = 0;
	m_nAttackCount = 0;
	m_nAttackCoolTime = 0;
	m_nStanCount = 0;
	m_pCollision = NULL;

	m_bMove = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CControlPlayer::~CControlPlayer()
{
	if (m_pCollision != NULL)
	{
		m_pCollision = NULL;
	}
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
	//m_bJump = false;
	m_bAttack = false;
	m_bDamage = false;
	m_bSliding = false;
	m_bDefeat = false;
	m_nSlidingCount = 0;
	m_nSlidingCoolTime = PLAYER_SLIDING_COOLTIME;
	m_nAttackCount = 0;
	m_nAttackCoolTime = PLAYER_ATTACK_COOLTIME;
	m_nStanCount = 0;
	m_pCollision = NULL;

	m_bMove = false;

	if (m_pUI[0] == NULL)
	{
		m_pUI[0] = CPauseUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f - 160.0f, 0.0f), D3DXVECTOR2(280.0f, 50.0f), 1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pUI[1] = CPauseUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5, 0.0f), D3DXVECTOR2(280.0f, 50.0f), 2, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));
		m_pUI[2] = CPauseUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f + 160.0f, 0.0f), D3DXVECTOR2(280.0f, 50.0f), 3, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));
	}
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CControlPlayer::Uninit(void)
{
	int nCntUI;
	for (nCntUI = 0; nCntUI < 3; nCntUI++)
	{
		if (m_pUI[nCntUI] != NULL)
		{
			m_pUI[nCntUI] = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CControlPlayer::Update(CScene *pScene)
{
	// 引数のポインタをプレイヤークラスのポインタにキャスト
	CPlayer *pPlayer = NULL;
	pPlayer = (CPlayer*)pScene;

	// キーボード取得処理
	CKeyboard *pKeyboard = NULL;
	pKeyboard = CManager::GetKeyboard();

	// ゲームパッド取得処理
	CGamePad *pGamePad = NULL;
	pGamePad = CManager::GetGamepad();
	
	// モーション取得処理
	CMotion *pMotion = NULL;
	pMotion = pPlayer->GetMotion();

	// 移動量を設定
	m_move = pPlayer->GetMove();

	//---------------------------------------------------
	// 重力
	//---------------------------------------------------
	if (pPlayer->GetState() != CPlayer::PLAYER_STATE_DEFEAT &&m_bDamage == true && pPlayer->GetLand() == false)
	{
		m_move.y -= PLAYER_GRAVITY_DAMAGE;
	}
	else if (pPlayer->GetState() == CPlayer::PLAYER_STATE_DEFEAT)
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
	if (pPlayer->GetState() != CPlayer::PLAYER_STATE_DEFEAT)
	{
		if (CManager::GetPause() == false && CManager::GetCountdown() == false && CManager::GetGameEnd() == false)
		{
			// 被ダメージ処理
			TakeDamage(pPlayer);

			//---------------------------------------------------
			// 基本アクション
			//---------------------------------------------------
			// 氷の状態異常じゃないなら
			if (pPlayer->GetBadState() != CPlayer::PLAYER_BAD_STATE_ICE)
			{
				// 被ダメージ状態じゃないなら
				if (m_bDamage == false)
				{
					// 攻撃していないなら
					if (m_bAttack == false)
					{
						// スライディング(回避)処理
						Sliding(pPlayer);
					}

					// スライディング(回避)していないなら
					if (m_bSliding == false)
					{
						// 攻撃処理
						Attack(pPlayer);
					}

					// 攻撃とスライディング(回避)の両方をしていないなら
					if (m_bAttack == false && m_bSliding == false)
					{
						// 移動処理
						Move(pPlayer);
					}
				}
				// 氷の状態異常だったら
				else if (pPlayer->GetBadState() == CPlayer::PLAYER_BAD_STATE_ICE)
				{
					// アクションに使う変数の状態をリセット
					m_nAttackCoolTime = PLAYER_ATTACK_COOLTIME;
					m_bAttack = false;
					m_nSlidingCoolTime = PLAYER_SLIDING_COOLTIME;
					m_bSliding = false;
				}
			}
		}
		if (CManager::GetCountdown() == false && CManager::GetGameEnd() == false)
		{
			//ポーズ処理
			Pause(pPlayer);
		}
	}
	// 敗北時の処理
	Defeat(pPlayer);

	//---------------------------------------------------
	// モーション遷移
	//---------------------------------------------------
	// 移動量が0かつ、モーションをつなげていないかつ、移動モーションだったら
	if ((m_move.x == 0 && m_move.z == 0) && pMotion->GetConnect() == false && pMotion->GetMotion() == 1)
	{
		// ニュートラルモーションに設定
		pMotion->SetMotion(0);
	}

	//---------------------------------------------------
	// 慣性
	//---------------------------------------------------
	// 移動の慣性(詳しい処理は関数の中)
	MoveInteria(pPlayer);

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
	m_bMove = false;

	// キーボード取得処理
	CKeyboard *pKeyboard = CManager::GetKeyboard();
	
	// ゲームパッド取得処理
	CGamePad *pGamePad = CManager::GetGamepad();
	
	// モーション取得処理
	CMotion *pMotion = pPlayer->GetMotion();
	
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

	if (pPlayer->GetBadState() == CPlayer::PLAYER_BAD_STATE_CONFUSION)
	{
		rotCamera += D3DX_PI;
		// 向きを3.14から-3.14の値の範囲内に収める
		if (rotCamera > D3DX_PI)
		{
			rotCamera -= D3DX_PI * 2.0f;
		}
		else if (rotCamera < -D3DX_PI)
		{
			rotCamera += D3DX_PI * 2.0f;
		}
	}

	//***********************************************************************
	// 移動 (キーボードＷ/Ａ/Ｓ/Ｄ または パッド左スティック)
	//***********************************************************************
	//左移動
	if (pKeyboard->GetPress(nLeft) == true ||
		pGamePad->GetPress(CGamePad::PAD_INPUTTYPE_LSTICK_LEFT, nPlayerNum) == true)
	{
		// モーションをつなげていないかつ、ニュートラルモーションだったら
		if (pMotion->GetConnect() == false && pMotion->GetMotion() == 0)
		{
			// 移動モーションにする
			pMotion->SetMotion(1);
		}

		//左奥移動
		if (pKeyboard->GetPress(nUp) == true ||
			pGamePad->GetPress(CGamePad::PAD_INPUTTYPE_LSTICK_UP, nPlayerNum) == true)
		{
			//移動量の加算および目的の向きの設定
			m_bMove = SetMove(rotCamera, 0.75f);
		}
		//左手前移動
		else if (pKeyboard->GetPress(nDown) == true ||
			pGamePad->GetPress(CGamePad::PAD_INPUTTYPE_LSTICK_DOWN, nPlayerNum) == true)
		{
			//移動量の加算および目的の向きの設定
			m_bMove = SetMove(rotCamera, 0.25f);
		}
		else
		{
			//移動量の加算および目的の向きの設定
			m_bMove = SetMove(rotCamera, 0.5f);
		}
	}
	//右移動
	else if (pKeyboard->GetPress(nRight) == true ||
		pGamePad->GetPress(CGamePad::PAD_INPUTTYPE_LSTICK_RIGHT, nPlayerNum) == true)
	{
		// モーションをつなげていないかつ、ニュートラルモーションだったら
		if (pMotion->GetConnect() == false && pMotion->GetMotion() == 0)
		{
			// 移動モーションにする
			pMotion->SetMotion(1);
		}

		//右奥移動
		if (pKeyboard->GetPress(nUp) == true ||
			pGamePad->GetPress(CGamePad::PAD_INPUTTYPE_LSTICK_UP, nPlayerNum) == true)
		{
			//移動量の加算および目的の向きの設定
			m_bMove = SetMove(rotCamera, -0.75f);
		}
		//右手前移動
		else if (pKeyboard->GetPress(nDown) == true ||
			pGamePad->GetPress(CGamePad::PAD_INPUTTYPE_LSTICK_DOWN, nPlayerNum) == true)
		{
			//移動量の加算および目的の向きの設定
			m_bMove = SetMove(rotCamera, -0.25f);
		}
		else
		{
			//移動量加算
			m_move.x -= (sinf(rotCamera - D3DX_PI * 0.5f) * MAX_MOVE + m_move.x) * 0.1f;
			m_move.z -= (cosf(rotCamera - D3DX_PI * 0.5f) * MAX_MOVE + m_move.z) * 0.1f;

			//移動量の加算および目的の向きの設定
			m_bMove = SetMove(rotCamera, -0.5f);
		}
	}
	//奥移動
	else if (pKeyboard->GetPress(nUp) == true ||
		pGamePad->GetPress(CGamePad::PAD_INPUTTYPE_LSTICK_UP, nPlayerNum) == true)
	{
		// モーションをつなげていないかつ、ニュートラルモーションだったら
		if (pMotion->GetConnect() == false && pMotion->GetMotion() == 0)
		{
			// 移動モーションにする
			pMotion->SetMotion(1);
		}

		//移動量の加算および目的の向きの設定
		m_bMove = SetMove(rotCamera, 1.0f);
	}
	//手前移動
	else if (pKeyboard->GetPress(nDown) == true ||
		pGamePad->GetPress(CGamePad::PAD_INPUTTYPE_LSTICK_DOWN, nPlayerNum) == true)
	{
		// モーションをつなげていないかつ、ニュートラルモーションだったら
		if (pMotion->GetConnect() == false && pMotion->GetMotion() == 0)
		{
			// 移動モーションにする
			pMotion->SetMotion(1);
		}

		//移動量の加算および目的の向きの設定
		m_bMove = SetMove(rotCamera, 0.0f);
	}
}

//=============================================================================
// スライディング(回避)処理
//=============================================================================
void CControlPlayer::Sliding(CPlayer *pPlayer)
{
	// キーボード取得処理
	CKeyboard *pKeyboard = CManager::GetKeyboard();

	// ゲームパッド取得処理
	CGamePad *pGamePad = CManager::GetGamepad();
	
	// モーション取得処理
	CMotion *pMotion = pPlayer->GetMotion();

	// 入力情報を分ける
	int nSlide = 0, nPlayerNum = 0;
	switch (pPlayer->GetType())
	{
	case CPlayer::PLAYER_TYPE_1P:
		nSlide = DIK_LSHIFT;
		nPlayerNum = 0;
		break;
	case CPlayer::PLAYER_TYPE_2P:
		nSlide = DIK_RCONTROL;
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
	if (m_bSliding == false)
	{
		// クールタイムのカウントを増やす
		m_nSlidingCoolTime++;

		// クールタイムを過ぎているなら
		if (m_nSlidingCoolTime >= PLAYER_SLIDING_COOLTIME)
		{
			//***********************************************************************
			// スライディング(回避) (キーボード左シフトキー または パッドAボタン)
			//***********************************************************************
			if (pKeyboard->GetKey(nSlide) == true ||
				pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_A, nPlayerNum) == true)
			{
				// 回避している状態に設定
				m_bSliding = true;

				// スライディングモーションにする
				pMotion->SetMotion(2);
			}
		}
	}
	// 回避中
	else if (m_bSliding == true)
	{
		pPlayer->SetInvSliding(true);

		// クールタイムをリセット
		m_nSlidingCoolTime = 0;

		// カウントを増やす
		m_nSlidingCount++;

		// 回避時間の間なら
		if (m_nSlidingCount <= PLAYER_SLIDING_TIME)
		{
			// プレイヤーの向きを取得し、直進させる
			D3DXVECTOR3 rot = pPlayer->GetRot();
			m_move.x -= (sinf(rot.y) * MAX_SLIDE + m_move.x) * 0.1f;
			m_move.z -= (cosf(rot.y) * MAX_SLIDE + m_move.z) * 0.1f;
		}

		// 回避後、硬直時間が過ぎたら
		if (m_nSlidingCount > PLAYER_SLIDING_TIME)
		{
			pPlayer->SetInvSliding(false);

			// 慣性の減算
			m_move.x *= PLAYER_INTERIA_SUBTRACTION;
			m_move.z *= PLAYER_INTERIA_SUBTRACTION;
		}

		if (m_nSlidingCount > PLAYER_SLIDING_TIME + PLAYER_SLIDING_WAITTIME)
		{
			// 回避していない状態にする
			m_bSliding = false;
			m_nSlidingCount = 0;
		}
	}
}

//=============================================================================
// 攻撃処理
//=============================================================================
void CControlPlayer::Attack(CPlayer *pPlayer)
{
	// キーボード取得処理
	CKeyboard *pKeyboard = CManager::GetKeyboard();

	// ゲームパッド取得処理
	CGamePad *pGamePad = CManager::GetGamepad();

	// モーション取得処理
	CMotion *pMotion = pPlayer->GetMotion();

	// 入力情報を分ける
	int nAttack = 0, nPlayerNum = 0;
	switch (pPlayer->GetType())
	{
	case CPlayer::PLAYER_TYPE_1P:
		nAttack = DIK_SPACE;
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

	// 攻撃中じゃないなら
	if (m_bAttack == false)
	{
		// クールタイムのカウントを増やす
		m_nAttackCoolTime++;

		// クールタイムを過ぎているなら
		if (m_nAttackCoolTime >= PLAYER_ATTACK_COOLTIME)
		{
			//***********************************************************************
			// 攻撃 (キーボードスペースキー または パッドBボタン)
			//***********************************************************************
			if (pKeyboard->GetKey(nAttack) == true ||
				pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_B, nPlayerNum) == true)
			{
				// 攻撃している状態に設定
				m_bAttack = true;

				// 攻撃モーションにする
				pMotion->SetMotion(3);
			}
		}
	}
	// 攻撃中
	else if (m_bAttack == true)
	{
		// クールタイムをリセット
		m_nAttackCoolTime = 0;

		// 攻撃中は動きを止める
		m_move.x = 0.0f;
		m_move.z = 0.0f;

		// 一定のカウントになったら
		if (m_nAttackCount == 15)
		{
			// 当たり判定を発生させる
			D3DXVECTOR3 pos = pPlayer->GetPos();
			m_pCollision = CCollisionSphere::Create(D3DXVECTOR3(pos.x, pos.y + pPlayer->GetRadius(), pos.z), pPlayer->GetRadius() * 3.0f,
				16, 16, CCollisionSphere::COLLISION_S_TYPE::COLLISION_S_TYPE_ATTACK, PLAYER_ATTACK_TIME);
			// どのプレイヤーの攻撃か設定
			m_pCollision->SetNumPlayer(pPlayer->GetType());
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
// ジャンプ処理
//=============================================================================
//void CControlPlayer::Jump(CPlayer *pPlayer)
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
//	/*CMotionPlayer *pMotionPlayer = NULL;
//	pMotionPlayer = pPlayer->GetMotionPlayer();*/
//
//	// 入力情報を分ける
//	int nJump = 0, nPlayerNum = 0;
//	switch (pPlayer->GetType())
//	{
//	case CPlayer::PLAYER_TYPE_1P:
//		nJump = DIK_SPACE;
//		nPlayerNum = 0;
//		break;
//	case CPlayer::PLAYER_TYPE_2P:
//		nJump = DIK_RCONTROL;
//		nPlayerNum = 1;
//		break;
//	case CPlayer::PLAYER_TYPE_3P:
//		nPlayerNum = 2;
//		break;
//	case CPlayer::PLAYER_TYPE_4P:
//		nPlayerNum = 3;
//		break;
//	default:
//		break;
//	}
//
//	// プレイヤーが着地しているなら
//	if (pPlayer->GetLand() == true)
//	{
//		//***********************************************************************
//		// ジャンプ (キーボードSpace または パッドAボタン)
//		//***********************************************************************
//		if (pKeyboard->GetTrigger(nJump) == true ||
//			pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_A, nPlayerNum) == true)
//		{
//			// Y方向の移動量を0に
//			m_move.y = 0.0f;
//
//			// 移動量をジャンプ力ぶん加算
//			m_move.y = PLAYER_JUMP;
//
//			// ジャンプをさせ、着地していないに設定
//			m_bJump = true;
//			pPlayer->SetLand(false);
//
//			m_bJump = true;
//		}
//		else
//		{
//			// 着地したらまたジャンプを可能にする
//			m_bJump = false;
//		}
//	}
//}

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

		m_bMove = false;
		m_bSliding = false;
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
	// プレイヤーの状態が<敗北>になったかつ、敗北していなかったら
	if (pPlayer->GetState() == CPlayer::PLAYER_STATE_DEFEAT && m_bDefeat == false)
	{
		// 着地していない状態にする
		pPlayer->SetLand(false);
		m_bDefeat = true;

		// 目的の向きを設定
		D3DXVECTOR3 rot = pPlayer->GetRot();
		m_fObjectiveRot = rot.y;
	}

	// 敗北
	if (m_bDefeat == true)
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
// ポーズ処理
//=============================================================================
void CControlPlayer::Pause(CPlayer *pPlayer)
{
	// キーボード取得処理
	CKeyboard *pKeyboard;
	pKeyboard = CManager::GetKeyboard();

	// ゲームパッド取得処理
	CGamePad *pGamePad;
	pGamePad = CManager::GetGamepad();

	// 入力情報を分ける
	int nPause = 0, nUp = 0, nDown = 0, nSelect = 0, nPlayerNum = 0;
	switch (pPlayer->GetType())
	{
	case CPlayer::PLAYER_TYPE_1P:
		nPause = DIK_ESCAPE;
		nUp = DIK_W;
		nDown = DIK_S;
		nSelect = DIK_RETURN;
		nPlayerNum = 0;
		break;
	case CPlayer::PLAYER_TYPE_2P:
		nPause = DIK_DELETE;
		nUp = DIK_UP;
		nDown = DIK_DOWN;
		nSelect = DIK_RETURN;
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

	if (CManager::GetPause() == false)
	{
		if (pKeyboard->GetKey(nPause) == true || 
			pGamePad->GetTrigger(XINPUT_GAMEPAD_START,nPlayerNum) == true)
		{
			m_nPause = nPlayerNum;
			CManager::SetPause(true);
		}
	}
	else
	{
		if ((pKeyboard->GetKey(nPause) == true ||
			pGamePad->GetTrigger(XINPUT_GAMEPAD_START, nPlayerNum) == true) &&
			nPlayerNum == m_nPause)
		{
			CManager::SetPause(false);
		}
		if ((pKeyboard->GetKey(nUp) == true ||
			pGamePad->GetTrigger(XINPUT_GAMEPAD_DPAD_UP, nPlayerNum) == true ||
			pGamePad->GetTrigger(CGamePad::PAD_INPUTTYPE_LSTICK_UP, nPlayerNum) == true) &&
			nPlayerNum == m_nPause)
		{
			PauseChange(-1);
		}
		if ((pKeyboard->GetKey(nDown) == true ||
			pGamePad->GetTrigger(XINPUT_GAMEPAD_DPAD_DOWN, nPlayerNum) == true ||
			pGamePad->GetTrigger(CGamePad::PAD_INPUTTYPE_LSTICK_DOWN, nPlayerNum) == true) &&
			nPlayerNum == m_nPause)
		{
			PauseChange(1);
		}
		if ((pKeyboard->GetKey(nPause) == true ||
			pGamePad->GetTrigger(XINPUT_GAMEPAD_START, nPlayerNum) == true) &&
			nPlayerNum == m_nPause)
		{
			CManager::SetPause(false);
		}
		if ((pKeyboard->GetKey(nSelect) == true ||
			pGamePad->GetTrigger(XINPUT_GAMEPAD_B, nPlayerNum) == true) &&
			nPlayerNum == m_nPause)
		{
			PauseSelect();
		}
	}
}

void CControlPlayer::PauseChange(int nAdd)
{
	m_pUI[m_nSelectPause]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));
	m_nSelectPause += nAdd;
	if (m_nSelectPause < 0)
	{
		m_nSelectPause = 2;
	}
	else if (2 < m_nSelectPause)
	{
		m_nSelectPause = 0;
	}
	m_pUI[m_nSelectPause]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

void CControlPlayer::PauseSelect()
{
	switch (m_nSelectPause)
	{
	case 0:
		CManager::SetPause(false);
		break;
	case 1:
		CFade::SetFade(CManager::MODE_GAME);
		break;
	case 2:
		CFade::SetFade(CManager::MODE_TITLE);
	default:
		break;
	}
}

//=============================================================================
// 移動の慣性についての処理
//=============================================================================
void CControlPlayer::MoveInteria(CPlayer *pPlayer)
{
	if (pPlayer->GetLand() == true && m_bMove == false && m_bSliding == false)
	{
		// 慣性の減算
		m_move.x *= PLAYER_INTERIA_SUBTRACTION;
		m_move.z *= PLAYER_INTERIA_SUBTRACTION;
	}

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

bool CControlPlayer::SetMove(float fRotCamera, float fRot)
{
	//移動量加算
	m_move.x -= (sinf(fRotCamera + D3DX_PI * fRot) * MAX_MOVE + m_move.x) * 0.1f;
	m_move.z -= (cosf(fRotCamera + D3DX_PI * fRot) * MAX_MOVE + m_move.z) * 0.1f;

	//目的の向きを設定し、回転の慣性をオンにする
	m_fObjectiveRot = fRotCamera + D3DX_PI * fRot;
	m_bRotate = true;

	return true;
}