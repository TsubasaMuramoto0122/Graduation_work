//=============================================================================
// プレイヤー操作処理 [control_player.cpp]
// Author : 草刈 翔
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

	//// テキスト保存用の変数
	//char cString[MAX_STRING];
	//// テキストファイルの読み込み
	//FILE *pFile = fopen("data/TEXT/motion_player.txt", "r");
	//if (pFile != NULL)
	//{
	//	while (fgets(cString, MAX_STRING, pFile) != NULL)
	//	{
	//		// 文字列を保存
	//		fscanf(pFile, "%s", cString);
	//		// 文字列の中に"CHARACTERSET"があったら
	//		if (strncmp("CHARACTERSET", cString, 12) == 0)
	//		{
	//			break;
	//		}
	//	}
	//	while (fgets(cString, MAX_STRING, pFile) != NULL)
	//	{
	//		// 文字列を保存
	//		fscanf(pFile, "%s", cString);
	//		// 文字列の中に"MOVE"があったら
	//		if (strncmp("MOVE", cString, 5) == 0)
	//		{
	//			// 移動の早さを取得する
	//			fscanf(pFile, "%s%f%*s%*s", cString, &m_fSpeed);
	//			// 基本の速さも設定しておく
	//			m_fBasicSpeed = m_fSpeed;
	//			// ジャンプ力を取得
	//			fscanf(pFile, "%s%*s%f%*s%*s%*s", cString, &m_fJump);
	//			break;
	//		}
	//	}
	//	while (fgets(cString, MAX_STRING, pFile) != NULL)
	//	{
	//		// 文字列を保存
	//		fscanf(pFile, "%s", cString);
	//		// 文字列の中に"END_CHARACTERSET"があったらそこで終了
	//		if (strncmp("END_CHARACTERSET", cString, 17) == 0)
	//		{
	//			break;
	//		}
	//	}
	//	// ファイルを閉じる
	//	fclose(pFile);
	//}

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
	//m_move.y -= PLAYER_GRAVITY;

	//// 重力が強くなりすぎたら重力の最大値で固定しておく
	//if (m_move.y <= -PLAYER_MAX_GRAVITY)
	//{
	//	m_move.y = -PLAYER_MAX_GRAVITY;
	//}

	//---------------------------------------------------
	// 基本アクション
	//---------------------------------------------------
	// 移動処理(詳しい処理は関数の中)
	Move();

	//---------------------------------------------------
	// モーション遷移
	//---------------------------------------------------

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
void CControlPlayer::Move(void)
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

	//***********************************************************************
	// 移動 (キーボードＷ/Ａ/Ｓ/Ｄ または パッド左スティック)
	//***********************************************************************
	//左移動
	if (pKeyboard->GetPress(DIK_A) == true /*||
										   pGamePad->LeftStickX() > 0*/)
	{
		//左奥移動
		if (pKeyboard->GetPress(DIK_W) == true /*||
											   pGamePad->LeftStickY() > 0*/)
		{
			//移動量加算
			m_move.x += +cosf(rotCamera + D3DX_PI / 4.0f) * m_fSpeed;
			m_move.z += -sinf(rotCamera + D3DX_PI / 4.0f) * m_fSpeed;

			//目的の向きを設定
			m_fObjectiveRot = rotCamera - D3DX_PI / 4.0f;
			//回転の慣性をオンにする
			m_bRotate = true;
		}
		//左手前移動
		else if (pKeyboard->GetPress(DIK_S) == true /*||
													pGamePad->LeftStickY() < 0*/)
		{
			//移動量加算
			m_move.x += +cosf(rotCamera - D3DX_PI / 4.0f) * m_fSpeed;
			m_move.z += -sinf(rotCamera - D3DX_PI / 4.0f) * m_fSpeed;

			//目的の向きを設定
			m_fObjectiveRot = rotCamera - (D3DX_PI / 4.0f) * 3.0f;
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
	//右移動
	else if (pKeyboard->GetPress(DIK_D) == true /*||
												pGamePad->LeftStickX() < 0*/)
	{
		//右奥移動
		if (pKeyboard->GetPress(DIK_W) == true /*||
											   pGamePad->LeftStickY() > 0*/)
		{
			//移動量加算
			m_move.x += -cosf(rotCamera - D3DX_PI / 4.0f) * m_fSpeed;
			m_move.z += +sinf(rotCamera - D3DX_PI / 4.0f) * m_fSpeed;

			//目的の向きを設定
			m_fObjectiveRot = rotCamera + D3DX_PI / 4.0f;
			//回転の慣性をオンにする
			m_bRotate = true;
		}
		//右手前移動
		else if (pKeyboard->GetPress(DIK_S) == true /*||
													pGamePad->LeftStickY() < 0*/)
		{
			//移動量加算
			m_move.x += -cosf(rotCamera + D3DX_PI / 4.0f) * m_fSpeed;
			m_move.z += +sinf(rotCamera + D3DX_PI / 4.0f) * m_fSpeed;

			//目的の向きを設定
			m_fObjectiveRot = rotCamera + D3DX_PI / 1.5f;
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
	//奥移動
	else if (pKeyboard->GetPress(DIK_W) == true /*||
												pGamePad->LeftStickY() > 0*/)
	{
		//移動量加算
		m_move.z += -cosf(rotCamera) * m_fSpeed;
		m_move.x += -sinf(rotCamera) * m_fSpeed;

		//目的の向きを設定
		m_fObjectiveRot = rotCamera;
		//回転の慣性をオンにする
		m_bRotate = true;
	}
	//手前移動
	else if (pKeyboard->GetPress(DIK_S) == true /*||
												pGamePad->LeftStickY() < 0*/)
	{
		//移動量加算
		m_move.z += +cosf(rotCamera) * m_fSpeed;
		m_move.x += +sinf(rotCamera) * m_fSpeed;

		//目的の向きを設定
		m_fObjectiveRot = rotCamera + D3DX_PI;
		//回転の慣性をオンにする
		m_bRotate = true;
	}
}

//=============================================================================
// 回避処理
//=============================================================================
void CControlPlayer::Dodge(void)
{

}

//=============================================================================
// 移動の慣性についての処理
//=============================================================================
void CControlPlayer::MoveInteria(CPlayer *pPlayer)
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