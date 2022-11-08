//=============================================================================
// AI操作処理 [cpu.cpp]
// Author : 三上　航世
//=============================================================================
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "cpu.h"
#include "manager.h"
#include "player.h"
#include "camera.h"
#include "sound.h"
#include "model.h"
#include "player.h"
#include "renderer.h"
#include "collision_sphere.h"
#include "bomb.h"
#include "danger.h"
#include "presetdelayset.h"
#include "motion.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CPU_MOVE_TIME				(40)	// 最低限の移動時間
#define CPU_THINK_TIME				(10)	// 最低限の思考時間
#define CPU_ATTACK_TIME				(120)	// 最低限の次攻撃するまでの時間
#define CPU_SLIDING_TIME			(15)	// 爆発何フレーム前になったら回避するか

//=============================================================================
// コンストラクタ
//=============================================================================
CCPU::CCPU()
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
	m_pBomb = NULL;
	m_pPlayer = NULL;

	m_bMove = false;
	m_nMoveTime = 0;
	m_thinkType = THINK_NONE;
	m_nThinkTime = CPU_THINK_TIME;
	m_bNextAttack = false;
	m_bNextSliding = false;
	m_bWall = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CCPU::~CCPU()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CCPU::Init(void)
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
	m_nMoveTime = 0;
	m_thinkType = THINK_NONE;
	m_nThinkTime = CPU_THINK_TIME;
	m_bNextAttack = false;
	m_bNextSliding = false;
	m_bWall = false;
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CCPU::Uninit(void)
{
	if (m_pCollision != NULL)
	{
		m_pCollision = NULL;
	}
	if (m_pBomb != NULL)
	{
		m_pBomb = NULL;
	}
	if (m_pPlayer != NULL)
	{
		m_pPlayer = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CCPU::Update(CScene *pScene)
{
	// 引数のポインタをプレイヤークラスのポインタにキャスト
	CPlayer *pPlayer = NULL;
	pPlayer = (CPlayer*)pScene;

	// モーション取得処理
	CMotion *pMotion = NULL;
	pMotion = pPlayer->GetMotion();

	// サウンド取得処理

	// 移動量を設定
	m_move = pPlayer->GetMove();

	if (CManager::GetPause() == false && CManager::GetCountdown() == false && CManager::GetGameEnd() == false)
	{
		//---------------------------------------------------
		// 重力
		//---------------------------------------------------
		if (pPlayer->GetState() != CPlayer::PLAYER_STATE_DEFEAT && m_bDamage == true && pPlayer->GetLand() == false)
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
	}

	// 敗北していなかったら
	if (pPlayer->GetState() != CPlayer::PLAYER_STATE_DEFEAT)
	{
		if (CManager::GetPause() == false && CManager::GetCountdown() == false && CManager::GetGameEnd() == false)
		{
			// 被ダメージ処理
			TakeDamage(pPlayer);

			if (m_thinkType == THINK_NONE)
			{
				if (m_nThinkTime <= 0)
				{
					Search(pPlayer);
				}
				else
				{
					m_nThinkTime--;
				}
			}

			if (m_nThinkTime < -50)
			{
				m_thinkType = THINK_NONE;
				m_nThinkTime = CPU_THINK_TIME;
			}
			else if (m_nMoveTime < -50)
			{
				m_thinkType = THINK_NONE;
				m_nThinkTime = CPU_THINK_TIME;
			}
			if (m_nAfterAttack > 0)
			{
				m_nAfterAttack--;
			}

			//---------------------------------------------------
			// 基本アクション
			//---------------------------------------------------
			// 氷の状態異常じゃないなら
			if (pPlayer->GetBadState() != CPlayer::PLAYER_BAD_STATE_ICE)
			{
				// 被ダメージ状態じゃないなら
				if (m_bDamage == false)
				{
					// 攻撃とスライディング(回避)の両方をしていないなら
					if (m_bAttack == false && m_bSliding == false)
					{
						// 移動処理
						Move(pPlayer);
					}

					if (m_bSliding == false)
					{
						Attack(pPlayer);
					}

					if (m_bAttack == false)
					{
						Sliding(pPlayer);
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
					m_nThinkTime = CPU_THINK_TIME;
					m_thinkType = THINK_NONE;
					m_pBomb = NULL;
					m_pPlayer = NULL;
				}
			}
		}
	}
	else
	{
		// 敗北時の処理
		Defeat(pPlayer);
	}
	if (CManager::GetPause() == false && CManager::GetGameEnd() == false)
	{
		//---------------------------------------------------
		// モーション遷移
		//---------------------------------------------------
		// 移動量が0じゃないかつ、モーションをつなげていないかつ、ニュートラルモーションだったら
		if ((m_move.x != 0 && m_move.z != 0) && pMotion->GetConnect() == false && pMotion->GetMotion() == 0)
		{
			// 移動モーションにする
			pMotion->SetMotion(1);
		}

		//---------------------------------------------------
		// 慣性
		//---------------------------------------------------
		// 移動の慣性(詳しい処理は関数の中)
		MoveInteria(pPlayer);

		// 回転の慣性(詳しい処理は関数の中)
		Rotate(pPlayer);
	}
}

//=============================================================================
// 生成処理
//=============================================================================
CCPU *CCPU::Create(void)
{
	// インスタンスの生成
	CCPU *pCPU = NULL;

	// ヌルチェック
	if (pCPU == NULL)
	{
		// クラスの生成
		pCPU = new CCPU;
		if (pCPU != NULL)
		{
			// 初期化処理
			pCPU->Init();
		}
	}

	return pCPU;
}

//=============================================================================
// 移動処理
//=============================================================================
void CCPU::Move(CPlayer *pPlayer)
{
	if (m_bMove == false)
	{
		if (m_thinkType != THINK_NONE)
		{
			//***********************************************************************
			// 移動
			//***********************************************************************
			if (m_thinkType == THINK_MOVE)
			{
				m_bMove = SetMove();
			}
			else
			{
				m_bMove = true;
			}
		}
	}
	else
	{
		D3DXVECTOR3 pos = pPlayer->GetPos();
		
		//一番近くの当たり判定があるとき
		if (m_pNearCollision != NULL)
		{
			//まだ消えない
			if (m_pNearCollision->GetDeath() == false && m_pNearCollision->GetTime() > 2.0f)
			{
				D3DXVECTOR3 ColPos = m_pNearCollision->GetPos();

				//対象のコリジョンとの距離
				float fDistance = sqrtf(powf(pos.x - ColPos.x, 2.0f) + powf(pos.z - ColPos.z, 2.0f));

				//近い
				if (fDistance < pPlayer->GetRadius() * 2.0f + m_pNearCollision->GetRadius())
				{
					m_nThinkTime = CPU_THINK_TIME * 3;
					m_thinkType = THINK_NONE;
					m_bMove = false;

					m_pNearCollision = NULL;
					m_pBomb = NULL;
					m_pPlayer = NULL;
				}
			}
			else
			{
				m_nThinkTime = CPU_THINK_TIME;
				m_thinkType = THINK_NONE;
				m_bMove = false;

				m_pNearCollision = NULL;
				m_pBomb = NULL;
				m_pPlayer = NULL;
			}
		}

		switch (m_thinkType)
		{
		case THINK_BOMB:
			if (m_pBomb != NULL)
			{
				if (m_pBomb->GetDeath() == false && m_pBomb->GetTime() > 2)
				{
					//爆弾の位置
					D3DXVECTOR3 BombPos = m_pBomb->GetPos();

					//対象の爆弾との距離
					float fDistance = sqrtf(powf(pos.x - BombPos.x, 2.0f) + powf(pos.z - BombPos.z, 2.0f));
					
					//爆弾と距離が近い場合、または逃げていて壁の当たったか
					if ((fDistance < (pPlayer->GetRadius() + m_pBomb->GetDanger()->GetRadius()) * 1.4f || m_bWall == true) && m_nAfterAttack <= 0)
					{
						//回転の慣性をオンにする
						m_bRotate = true;
						
						//爆弾の方向に向く
						m_fObjectiveRot = atan2f(BombPos.x - pos.x, BombPos.z - pos.z) - D3DX_PI;
						//角度が狂わないようにする
						if (m_fObjectiveRot < -D3DX_PI)
						{
							m_fObjectiveRot += D3DX_PI * 2.0f;
						}

						//もうすぐ爆発する場合
						if (m_pBomb->GetTime() < CPU_SLIDING_TIME)
						{
							//回避する
							if (m_nSlidingCoolTime >= PLAYER_SLIDING_COOLTIME && m_bSliding == false && m_bAttack == false)
							{
								if (m_pBomb->GetDanger()->GetRadius() * 0.7f < fDistance && fDistance < (m_pBomb->GetDanger()->GetRadius() + pPlayer->GetRadius()))
								{
									m_fObjectiveRot += D3DX_PI;
									//角度が狂わないようにする
									if (D3DX_PI < m_fObjectiveRot)
									{
										m_fObjectiveRot -= D3DX_PI * 2.0f;
									}
								}
								m_bNextSliding = true;
								m_bMove = false;
								m_thinkType = THINK_NONE;
								m_nThinkTime = CPU_THINK_TIME;
								m_bWall = false;
							}
						}

						//爆弾と至近距離な場合
						if (fDistance < pPlayer->GetRadius() + m_pBomb->GetRadius())
						{
							//攻撃する
							if (m_nAttackCoolTime >= PLAYER_ATTACK_COOLTIME)
							{
								m_bNextAttack = true;
								m_bMove = false;
								m_thinkType = THINK_NONE;
								m_nThinkTime = CPU_THINK_TIME;
								m_bWall = false;
							}
						}
					}
					else
					{
						//壁に当たっていたら
						if (pPlayer->GetHitWall() == true)
						{
							//壁に当たった
							m_bWall = true;
						}
						else
						{
							//回転の慣性をオンにする
							m_bRotate = true;

							//爆弾とは正反対の方向を向く
							m_fObjectiveRot = atan2f(BombPos.x - pos.x, BombPos.z - pos.z);

							//もうすぐ爆発する場合
							if (m_pBomb->GetTime() < CPU_SLIDING_TIME)
							{
								if (m_nSlidingCoolTime >= PLAYER_SLIDING_COOLTIME && m_bSliding == false && m_bAttack == false)
								{
									m_bNextSliding = true;
									m_bMove = false;
									m_thinkType = THINK_NONE;
									m_nThinkTime = CPU_THINK_TIME;
								}
							}

							//十分距離が空いたら
							if (fDistance > (pPlayer->GetRadius() + m_pBomb->GetDanger()->GetRadius()) * 2.0f)
							{
								//移動をやめる
								m_bMove = false;
								m_thinkType = THINK_NONE;
								m_nThinkTime = CPU_THINK_TIME;
							}
						}
					}
				}
				else
				{
					//爆弾をNULLにし、考える
					m_pBomb = NULL;
					m_bWall = false;
					m_bMove = false;
					m_thinkType = THINK_NONE;
					m_nThinkTime = CPU_THINK_TIME;
				}
			}
			else
			{
				m_thinkType = THINK_NONE;
				m_nThinkTime = CPU_THINK_TIME;
			}
			break;
		case THINK_PLAYER:
			if (m_pPlayer != NULL)
			{
				if (m_pPlayer->GetDeath() == false && m_pPlayer->GetState() != CPlayer::PLAYER_STATE_DEFEAT)
				{
					//プレイヤーの位置取得
					D3DXVECTOR3 PlayerPos = m_pPlayer->GetPos();

					//回転の慣性をオンにする
					m_bRotate = true;

					//プレイヤーの方向を向く
					m_fObjectiveRot = atan2f(PlayerPos.x - pos.x, PlayerPos.z - pos.z) - D3DX_PI;
					if (m_fObjectiveRot < -D3DX_PI)
					{
						m_fObjectiveRot += D3DX_PI * 2.0f;
					}

					//プレイヤーとの距離計算
					float fDistance = sqrtf(powf(pos.x - PlayerPos.x, 2.0f) + powf(pos.z - PlayerPos.z, 2.0f));
					
					//プレイヤーと距離が近い場合
					if (fDistance < pPlayer->GetRadius() + m_pPlayer->GetRadius() + 2.0f && m_nAfterAttack <= 0)
					{
						//クールタイムが終わっていたら
						if (m_nAttackCoolTime >= PLAYER_ATTACK_COOLTIME)
						{
							//攻撃する
							m_bNextAttack = true;
							m_bMove = false;
							m_thinkType = THINK_NONE;
							m_nThinkTime = CPU_THINK_TIME;
						}
					}
				}
				else
				{
					//プレイヤーをNULLにし、また新たに考える
					m_pPlayer = NULL;
					m_bMove = false;
					m_thinkType = THINK_NONE;
					m_nThinkTime = CPU_THINK_TIME;
				}
			}
			else
			{
				m_thinkType = THINK_NONE;
				m_nThinkTime = CPU_THINK_TIME;
			}
			break;
		case THINK_MOVE:
			m_nMoveTime--;
			if (m_nMoveTime <= 0)
			{
				m_thinkType = THINK_NONE;
				m_nThinkTime = CPU_THINK_TIME;
				m_bMove = false;
			}
			break;
		default:
			break;
		}
		m_move.x -= (sinf(m_fObjectiveRot) * MAX_MOVE + m_move.x) * 0.1f;
		m_move.z -= (cosf(m_fObjectiveRot) * MAX_MOVE + m_move.z) * 0.1f;
	}
}

//=============================================================================
// 回避処理
//=============================================================================
void CCPU::Sliding(CPlayer *pPlayer)
{
	// モーション取得処理
	//CMotionPlayer *pMotionPlayer = NULL;
	//pMotionPlayer = pPlayer->GetMotionPlayer();

	// 回避中じゃないなら
	if (m_bSliding == false)
	{
		// クールタイムのカウントを増やす
		m_nSlidingCoolTime++;

		// クールタイムを過ぎているなら
		if (m_nSlidingCoolTime >= PLAYER_SLIDING_COOLTIME && m_bNextSliding == true)
		{
			// モーション取得処理
			CMotion *pMotion = pPlayer->GetMotion();

			// スライディングモーションにする
			pMotion->SetMotion(2);

			//回避する
			m_nThinkTime = CPU_THINK_TIME;
			m_bSliding = true;

			CSound::Play(20);
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
			m_move.x = -sinf(rot.y) * MAX_SLIDE;
			m_move.z = -cosf(rot.y) * MAX_SLIDE;
			//m_move.x -= (sinf(rot.y) * MAX_SLIDE + m_move.x) * 0.1f;
			//m_move.z -= (cosf(rot.y) * MAX_SLIDE + m_move.z) * 0.1f;
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

			m_thinkType = THINK_NONE;

			//次やる行動をリセットする
			m_bNextSliding = false;
			m_bNextAttack = false;
		}
	}
}

//=============================================================================
// 攻撃処理
//=============================================================================
void CCPU::Attack(CPlayer *pPlayer)
{
	// モーション取得処理
	//CMotionPlayer *pMotionPlayer = NULL;
	//pMotionPlayer = pPlayer->GetMotionPlayer();

	// 攻撃中じゃないなら
	if (m_bAttack == false)
	{
		// クールタイムのカウントを増やす
		m_nAttackCoolTime++;

		// クールタイムを過ぎているなら
		if (m_nAttackCoolTime >= PLAYER_ATTACK_COOLTIME && m_bNextAttack == true)
		{
			//***********************************************************************
			// 攻撃
			//***********************************************************************
			m_bAttack = true;
			m_nThinkTime = CPU_THINK_TIME;
			m_nAfterAttack = CPU_ATTACK_TIME;

			// モーション取得処理
			CMotion *pMotion = pPlayer->GetMotion();

			// 攻撃モーションにする
			pMotion->SetMotion(3);
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

		// 攻撃時間の間なら
		if (m_nAttackCount == 15)
		{
			// 前方に当たり判定を発生させる
			D3DXVECTOR3 pos = pPlayer->GetPos();
			D3DXVECTOR3 rot = pPlayer->GetRot();
			pos.x -= sinf(rot.y) * 20.0f;
			pos.z -= cosf(rot.y) * 20.0f;
			m_pCollision = CCollisionSphere::Create(D3DXVECTOR3(pos.x, pos.y + pPlayer->GetRadius(), pos.z),
				pPlayer->GetRadius() * 2.5f, 16, 16, CCollisionSphere::COLLISION_S_TYPE::COLLISION_S_TYPE_ATTACK, PLAYER_ATTACK_TIME);
			// どのプレイヤーの攻撃か設定
			m_pCollision->SetNumPlayer(pPlayer->GetType());

			//エフェクト出す
			CPresetDelaySet::Create("ATTACK", pos);

			CSound::Play(16);
		}

		// カウントを増やす
		m_nAttackCount++;

		// 攻撃後、硬直時間が過ぎたら
		if (m_nAttackCount > PLAYER_ATTACK_WAITTIME + PLAYER_ATTACK_TIME)
		{
			// 攻撃していない状態にする
			m_bAttack = false;
			m_nAttackCount = 0;

			//次攻撃するのをリセットする
			m_bNextAttack = false;
			m_bNextSliding = false;
		}
	}
}

//=============================================================================
// 被ダメージ処理
//=============================================================================
void CCPU::TakeDamage(CPlayer *pPlayer)
{
	// モーション取得処理
	CMotion *pMotion = pPlayer->GetMotion();

	// プレイヤーの状態が<吹っ飛び>になったかつ、ダメージを受けていなかったら
	if (pPlayer->GetState() == CPlayer::PLAYER_STATE_BLOWAWAY && m_bDamage == false)
	{
		// スライディングと攻撃状態の解除、スタン時間のリセット
		m_bSliding = false;
		m_nSlidingCount = 0;
		m_bAttack = false;
		m_nAttackCount = 0;

		// ダメージを受けた状態にし、着地していない状態にする
		m_bDamage = true;
		pPlayer->SetLand(false);

		// 目的の向きを設定
		D3DXVECTOR3 rot = pPlayer->GetRot();
		m_fObjectiveRot = rot.y;

		m_nThinkTime = CPU_THINK_TIME;

		m_bMove = false;
		m_bSliding = false;

		CSound::Play(17);
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
			// モーションをつなげていないかつ、ダメージモーション(1)・(2)じゃなかったら
			if (pMotion->GetConnect() == false && pMotion->GetMotion() != 5 && pMotion->GetMotion() != 6)
			{
				// ダメージモーション(2)にする
				pMotion->SetMotion(5);
			}

			// カウントを進める
			m_nStanCount++;

			if (pMotion->GetConnect() == false && pMotion->GetMotion() != 6 && m_nStanCount > PLAYER_GETUP_TIME)
			{
				// 起き上がりモーションにする
				pMotion->SetMotion(6);
			}

			if (m_nStanCount > PLAYER_KNOCKBACK_STAN)
			{
				m_bDamage = false;
				m_nStanCount = 0;

				m_thinkType = THINK_NONE;
			}
		}
	}
}

//=============================================================================
// 敗北処理
//=============================================================================
void CCPU::Defeat(CPlayer *pPlayer)
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

		CSound::Play(18);
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
// 移動の慣性についての処理
//=============================================================================
void CCPU::MoveInteria(CPlayer *pPlayer)
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
void CCPU::Rotate(CPlayer *pPlayer)
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

bool CCPU::SetMove()
{
	m_nMoveTime = CPU_MOVE_TIME + (rand() % 3) * 30;
	m_nThinkTime = CPU_THINK_TIME;
	m_fObjectiveRot = D3DX_PI * (float)((rand() % 361) / 180.0f) - D3DX_PI;

	//回転の慣性をオンにする
	m_bRotate = true;
	return true;
}

void CCPU::Search(CPlayer *pPlayer)
{
	m_pBomb = CBomb::SearchBomb(pPlayer->GetPos());
	m_pPlayer = CPlayer::SearchPlayer(pPlayer);
	m_pNearCollision = CCollisionSphere::SearchCollision(pPlayer->GetPos());
	D3DXVECTOR3 pos = pPlayer->GetPos();

	//どっちも存在してる
	if (m_pBomb != NULL && m_pPlayer != NULL)
	{
		D3DXVECTOR3 BombPos = m_pBomb->GetPos();
		D3DXVECTOR3 PlayerPos = m_pPlayer->GetPos();
		float fBombDistance;
		float fPlayerDistance;
		fBombDistance = sqrtf(powf(pos.x - BombPos.x, 2.0f) + powf(pos.z - BombPos.z, 2.0f));
		fPlayerDistance = sqrtf(powf(pos.x - PlayerPos.x, 2.0f) + powf(pos.z - PlayerPos.z, 2.0f));

		//爆弾とプレイヤーの距離を比較、プレイヤーの方が近い
		if (fBombDistance > fPlayerDistance * 3.0f)
		{
			m_thinkType = THINK_PLAYER;
		}
		else
		{
			m_thinkType = THINK_BOMB;
		}
	}
	else if (m_pBomb != NULL && m_pPlayer == NULL)
	{
		m_thinkType = THINK_BOMB;
	}
	else if (m_pBomb == NULL && m_pPlayer != NULL)
	{
		m_thinkType = THINK_PLAYER;
	}
	else if (m_pBomb == NULL && m_pPlayer == NULL)
	{
		m_thinkType = THINK_NONE;
		m_nThinkTime = CPU_MOVE_TIME * 3;
	}
}