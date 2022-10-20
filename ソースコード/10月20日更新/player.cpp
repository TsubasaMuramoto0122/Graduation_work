//=============================================================================
// プレイヤー処理 [player.cpp]
// Authore : Kusakari Kakeru
//=============================================================================
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "player.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "camera.h"
//#include "motion_player.h"
#include "control_player.h"
#include "shadow.h"
#include "sound.h"
#include "collision_sphere.h"
#include "mesh_field.h"
#include "mesh_wall.h"
#include "life.h"

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define PLAYER_BEGIN_LIFE	(100)	// 初期ライフ
#define INVINCIBLE_TIME		(160)	// 無敵時間
#define ICE_TIME			(210)	// 氷の状態異常の時間
#define POISON_TIME			(300)	// 毒の状態異常の時間
#define CONFUSION_TIME		(270)	// 混乱の状態異常の時間

//=============================================================================
// コンストラクタ
//============================================================================
CPlayer::CPlayer(PRIORITY Priority) : CScene3D::CScene3D(Priority)
{
	// 変数のクリア
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	for (int nCntModel = 0; nCntModel < MAX_PLAYER_MODEL; nCntModel++)
	{
		m_apModel[nCntModel] = NULL;
	}
	m_pParent = NULL;
	//m_pMotionPlayer = NULL;
	m_pControl = NULL;
	m_pCollision = NULL;
	m_pLife = NULL;
	m_state = PLAYER_STATE_NORMAL;
	m_badState = PLAYER_BAD_STATE_NONE;
	m_type = PLAYER_TYPE_MAX;
	m_bLand = false;
	m_bDamage = false;
	m_bInvDamage = false;
	m_bInvSliding = false;
	m_bDraw = true;
	m_nLife = 0;
	m_nInvincibleTime = 0;
	m_nBadStateTime = 0;
	m_nPoisonCount = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CPlayer::~CPlayer()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos)
{
	// 変数の初期化
	m_pos = pos;
	m_posOld = pos;
	m_move = m_pControl->GetMove();
	m_state = PLAYER_STATE_NORMAL;
	m_bLand = false;
	m_bDamage = false;
	m_bInvDamage = false;
	m_bInvSliding = false;
	m_bDraw = true;
	m_nLife = PLAYER_BEGIN_LIFE;
	m_nInvincibleTime = 0;
	m_nBadStateTime = 0;
	m_nPoisonCount = 0;

	// モデル生成処理
	ModelCreate(m_type);

	// 変数の設定
	SetRot(m_rot);
	SetPos(m_pos);

	// モーションの生成
	//m_pMotionPlayer = CMotionPlayer::Create(this);

	// 体にコリジョン(プレイヤー判定)をつける
	m_pCollision = CCollisionSphere::Create(m_pos, m_size.x, 16, 16, CCollisionSphere::COLLISION_S_TYPE::COLLISION_S_TYPE_PLAYER, -1.0f);
	m_pCollision->SetNumPlayer(m_type);

	// ライフの生成
	D3DXVECTOR2 lifePos = D3DXVECTOR2(0.0f, 0.0f);
	switch(m_type)
	{
	case PLAYER_TYPE_1P:
		lifePos = D3DXVECTOR2(150.0f, 100.0f);
		break;
	case PLAYER_TYPE_2P:
		lifePos = D3DXVECTOR2(400.0f, 100.0f);
		break;
	case PLAYER_TYPE_3P:
		lifePos = D3DXVECTOR2(SCREEN_WIDTH - 400.0f, 100.0f);
		break;
	case PLAYER_TYPE_4P:
		lifePos = D3DXVECTOR2(SCREEN_WIDTH - 150.0f, 100.0f);
		break;
	default:
		break;
	}
	m_pLife = CLifeUI::Create(lifePos, D3DXVECTOR2(200.0f, 50.0f));

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPlayer::Uninit(void)
{
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER_MODEL; nCntPlayer++)
	{
		if (m_apModel[nCntPlayer] != NULL)
		{
			m_apModel[nCntPlayer]->Uninit();
			m_apModel[nCntPlayer] = NULL;
		}
	}

	// オブジェクトの破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CPlayer::Update(void)
{
	if (this != NULL)
	{
		// 位置の取得
		D3DXVECTOR3 pos = GetPos();
		m_pos = pos;
		m_posOld = m_pos;

		// 1フレーム前の位置設定
		SetPosOld(m_posOld);

		// 移動処理
		Move();

		// 他のコリジョンと接触した時の処理
		TouchCollision();

		// 状態異常の処理
		BadState(m_badState);

		// 移動量反映
		m_pos += m_move;

		// モーション
		//m_pMotionPlayer->Update(this);

		// 位置反映
		SetPos(m_pos);

		// 着地状態を初期化
		m_bLand = false;

		// プレイヤーとの押出判定
		Push(this);

		// 敗北の状態じゃなかったら
		if (GetState() != PLAYER_STATE_DEFEAT)
		{
			// 壁との当たり判定
			CMeshWall::Collision(this);
		}

		if (m_bLand == false)
		{
			// 地面との当たり判定
			m_bLand = CMeshField::Collision(this);
		}

		if (m_bLand == true)
		{
			// 着地したらY方向の移動量を0に
			m_move.y = 0.0f;
		}

		// 位置取得
		m_pos = GetPos();

		// 無敵時の処理
		Invincible();

		// コリジョンの追従
		D3DXVECTOR3 collisionPos = D3DXVECTOR3(m_pos.x, m_pos.y + GetRadius(), m_pos.z);
		m_pCollision->SetPosCollision(collisionPos);

		m_pLife->SetLifeBar(m_nLife, PLAYER_BEGIN_LIFE);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CPlayer::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// モデルの描画
	for (int nCntModel = 0; nCntModel < MAX_PLAYER_MODEL; nCntModel++)
	{
		if (m_bDraw == true)
		{
			m_apModel[nCntModel]->Draw();
		}
	}

}

//=============================================================================
// 生成処理
//=============================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, PLAYER_TYPE type)
{
	// インスタンスの生成
	CPlayer *pPlayer = NULL;

	// ヌルチェック
	if (pPlayer == NULL)
	{
		// クラスの生成
		pPlayer = new CPlayer;
		if (pPlayer != NULL)
		{
			// プレイヤー操作のクラスを生成
			pPlayer->m_pControl = CControlPlayer::Create();

			// 変数の初期化
			pPlayer->m_rot = rot;
			pPlayer->m_type = type;

			// 初期化処理
			pPlayer->Init(pos);
		}
	}

	return pPlayer;
}

//=============================================================================
// モデル生成処理
//=============================================================================
void CPlayer::ModelCreate(PLAYER_TYPE type)
{
	// モデルの生成
	switch (type)
	{
	case PLAYER_TYPE_1P:
		m_apModel[0] = CModel::Create("data/MODEL/kirby.x");
		break;
	case PLAYER_TYPE_2P:
		m_apModel[0] = CModel::Create("data/MODEL/kirby_Y.x");
		break;
	case PLAYER_TYPE_3P:
		m_apModel[0] = CModel::Create("data/MODEL/kirby_B.x");
		break;
	case PLAYER_TYPE_4P:
		m_apModel[0] = CModel::Create("data/MODEL/kirby_G2.x");
		break;
	default:
		break;
	}

	if (m_apModel[0] != NULL)
	{
		D3DXVECTOR3 VtxMax, VtxMin;
		VtxMax = m_apModel[0]->GetMaxSize();
		VtxMin = m_apModel[0]->GetMinSize();

		float fRadius = (VtxMax.x - VtxMin.x) / 2;
		if (fRadius < (VtxMax.y - VtxMin.y) / 2)
		{
			fRadius = (VtxMax.y - VtxMin.y) / 2;
		}
		if (fRadius < (VtxMax.z - VtxMin.z) / 2)
		{
			fRadius = (VtxMax.z - VtxMin.z) / 2;
		}
		m_size.x = fRadius * 2;
		m_size.y = fRadius * 2;
		m_size.z = fRadius * 2;
	}
}

//=============================================================================
// 移動処理
//=============================================================================
void CPlayer::Move(void)
{
	// ヌルチェック
	if (m_pControl != NULL)
	{
		// プレイヤー操作のクラスにプレイヤーのポインタを入れ、移動量を取得
		m_pControl->Update(this);
		m_move = m_pControl->GetMove();
	}
}

//=============================================================================
// コリジョンを使った押出処理
//=============================================================================
void CPlayer::Push(CPlayer *pPlayer)
{
	//オブジェクト情報を入れるポインタ
	CScene *pObject = NULL;
	CScene *pSaveObject = NULL;

	//先頭のポインタを代入
	pObject = pObject->GetTopObj(CScene::PRIORITY_CHARA);

	while (pObject != NULL)
	{
		//現在のオブジェクトのポインタを保存
		pSaveObject = pObject;

		if (pObject->GetObjType() == CScene::OBJECTTYPE_PLAYER)
		{
			//プレイヤーにキャスト
			CPlayer *pOtherPlayer = NULL;
			pOtherPlayer = (CPlayer*)pObject;

			// 自分以外のオブジェクトなら
			if (pObject != this)
			{
				D3DXVECTOR3 posPlayer = pOtherPlayer->GetPos();			// 他のプレイヤーの位置を取得
				float fSizePlayer = pOtherPlayer->GetRadius();			// 他のプレイヤーのサイズの半径を取得
				float totalSize = (GetRadius() + fSizePlayer) * 0.75f;	// プレイヤー2人の半径の合計

				// 距離と向きを計算
				float fDistance = sqrtf((pPlayer->m_pos.x - posPlayer.x) * (pPlayer->m_pos.x - posPlayer.x) + (pPlayer->m_pos.y - posPlayer.y) * (pPlayer->m_pos.y - posPlayer.y) + (pPlayer->m_pos.z - posPlayer.z) * (pPlayer->m_pos.z - posPlayer.z));
				float fRot = (float)atan2((posPlayer.x - pPlayer->m_pos.x), (posPlayer.z - pPlayer->m_pos.z)) - D3DX_PI;

				// 距離がプレイヤー2人の半径の合計より小さかったら
				if (fDistance <= totalSize)
				{
					pPlayer->m_pos.x = posPlayer.x + (sinf(fRot) * totalSize);
					pPlayer->m_pos.z = posPlayer.z + (cosf(fRot) * totalSize);

					// 対象の位置を設定
					SetPos(pPlayer->m_pos);
				}
			}
		}
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}
}

//=============================================================================
// 他のコリジョンと接触した時の処理
//=============================================================================
void CPlayer::TouchCollision(void)
{
	// 敗北の状態じゃなかったら
	if (GetState() != PLAYER_STATE_DEFEAT)
	{
		// 他のプレイヤーの攻撃 または 爆発に当たった瞬間なら
		if (m_pCollision->GetTouchCollision(CCollisionSphere::COLLISION_S_TYPE_ATTACK) == true ||
			m_pCollision->GetTouchCollision(CCollisionSphere::COLLISION_S_TYPE_EXPLOSION) == true ||
			m_pCollision->GetTouchCollision(CCollisionSphere::COLLISION_S_TYPE_POISON) == true ||
			m_pCollision->GetTouchCollision(CCollisionSphere::COLLISION_S_TYPE_CONFUSION) == true)
		{
			// 何らかの無敵状態じゃないなら
			if (m_bInvDamage == false && m_bInvSliding == false)
			{
				// ダメージを受けた状態にする
				m_bDamage = true;

				// 状態を<吹っ飛び>に設定
				SetState(PLAYER_STATE_BLOWAWAY);

				// 氷の状態異常を治す
				if (GetBadState() == PLAYER_BAD_STATE_ICE)
				{
					SetBadState(PLAYER_BAD_STATE_NONE);
				}

				// 通常の爆発に当たっていたら
				if (m_pCollision->GetTouchCollision(CCollisionSphere::COLLISION_S_TYPE_EXPLOSION) == true)
				{
					// ライフを減らす
					m_nLife -= 30;

					// ライフが残っていたら
					if (m_nLife > 0)
					{
						// 被ダメージによる無敵にする
						m_bInvDamage = true;
					}
				}
				// 毒の爆発に当たっていたら
				else if (m_pCollision->GetTouchCollision(CCollisionSphere::COLLISION_S_TYPE_POISON) == true)
				{
					// ライフを減らす
					m_nLife -= 30;

					// ライフが残っていたら
					if (m_nLife > 0)
					{
						// 被ダメージによる無敵にする
						m_bInvDamage = true;
					}

					SetBadState(PLAYER_BAD_STATE_POISON);
				}
				// 混乱の爆発に当たっていたら
				else if (m_pCollision->GetTouchCollision(CCollisionSphere::COLLISION_S_TYPE_CONFUSION) == true)
				{
					// ライフを減らす
					m_nLife -= 30;

					// ライフが残っていたら
					if (m_nLife > 0)
					{
						// 被ダメージによる無敵にする
						m_bInvDamage = true;
					}

					SetBadState(PLAYER_BAD_STATE_CONFUSION);
				}

				// ライフがなくなったら
				if (m_nLife <= 0)
				{
					// 敗北の状態に設定
					SetState(PLAYER_STATE_DEFEAT);

					// カメラの向きを取得し、プレイヤーの向きを指定
					CCamera *pCamera = CManager::GetRenderer()->GetCamera();
					float rotCamera = pCamera->GetRotY();
					m_rot.y = rotCamera;

					// Y方向への移動量をリセットし、ジャンプさせる
					m_move.y = 0.0f;
					m_move.y += PLAYER_DEFEATKNOCKBACK_JUMP;
				}
				// ライフがあるなら通常の挙動
				else
				{
					// 対象のコリジョンの方向を向かせる
					m_rot.y = m_pCollision->GetObjectiveRot();

					// Y方向への移動量をリセットし、ジャンプさせる
					m_move.y = 0.0f;
					m_move.y += PLAYER_KNOCKBACK_JUMP;
				}
			}
		}
		else if (m_pCollision->GetTouchCollision(CCollisionSphere::COLLISION_S_TYPE_ICE) == true)
		{
			// 何らかの無敵状態じゃないなら
			if (m_bInvDamage == false && m_bInvSliding == false)
			{
				SetBadState(PLAYER_BAD_STATE_ICE);
			}
		}
		else
		{
			// コリジョンに当たっていないなら通常の状態に戻す
			SetState(PLAYER_STATE_NORMAL);
		}
	}
}

//=============================================================================
// 無敵時の処理
//=============================================================================
void CPlayer::Invincible(void)
{
	// 被ダメージによる無敵の間
	if (m_bInvDamage == true)
	{
		// 無敵時間のカウントを増やす
		m_nInvincibleTime++;

		// 無敵時間中、点滅させる
		if (m_nInvincibleTime % 8 == 0 || m_nInvincibleTime % 8 == 1)
		{
			m_bDraw = false;
		}
		else
		{
			m_bDraw = true;
		}

		// 無敵時間が終わったら
		if (m_nInvincibleTime >= INVINCIBLE_TIME)
		{
			// 無敵状態を消す
			m_bInvDamage = false;
			m_bDamage = false;
			m_bDraw = true;

			// 無敵時間をリセット
			m_nInvincibleTime = 0;
		}
	}
}

//=============================================================================
// 状態異常の処理
//=============================================================================
void CPlayer::BadState(PLAYER_BAD_STATE state)
{
	switch (state)
	{
		// 氷
	case PLAYER_BAD_STATE_ICE:
		// カウントを増やす
		m_nBadStateTime++;

		m_move.x = 0.0f;
		m_move.z = 0.0f;

		// 一定時間が経ったら
		if (m_nBadStateTime >= ICE_TIME)
		{
			// 状態異常をを消す
			SetBadState(PLAYER_BAD_STATE_NONE);

			// 時間をリセット
			m_nBadStateTime = 0;
		}
		break;
		// 毒
	case PLAYER_BAD_STATE_POISON:
		// カウントを増やす
		m_nBadStateTime++;

		// <吹っ飛び>の状態以外で動いている場合
		if (m_state != PLAYER_STATE_BLOWAWAY && m_move.x != 0.0f || m_move.z != 0.0f)
		{
			// カウントを増やす
			m_nPoisonCount++;

			// 一定時間が経過し、ライフが1より上だったら
			if (m_nPoisonCount >= 30 && m_nLife > 1)
			{
				// ライフを減らす
				m_nLife--;
				m_nPoisonCount = 0;
			}
		}

		// 一定時間が経ったら
		if (m_nBadStateTime >= POISON_TIME)
		{
			// 状態異常をを消す
			SetBadState(PLAYER_BAD_STATE_NONE);

			// 時間をリセット
			m_nBadStateTime = 0;
		}
		break;
		// 混乱
	case PLAYER_BAD_STATE_CONFUSION:
		// カウントを増やす
		m_nBadStateTime++;

		// 一定時間が経ったら
		if (m_nBadStateTime >= CONFUSION_TIME)
		{
			// 状態異常をを消す
			SetBadState(PLAYER_BAD_STATE_NONE);

			// 時間をリセット
			m_nBadStateTime = 0;
		}
		break;

	default:
		// カウンターをリセット
		m_nBadStateTime = 0;
		m_nPoisonCount = 0;
		break;
	}
}

//=============================================================================
// モデル毎の位置設定処理
//=============================================================================
void CPlayer::SetModelPos(int nCntModel, D3DXVECTOR3 pos)
{
	m_apModel[nCntModel]->SetPos(pos);
}

//=============================================================================
// モデル毎の位置取得処理
//=============================================================================
D3DXVECTOR3 CPlayer::GetModelPos(int nCntModel)
{
	return m_apModel[nCntModel]->GetPos();
}

//=============================================================================
// モデル毎の向き設定処理
//=============================================================================
void CPlayer::SetModelRot(int nCntModel, D3DXVECTOR3 rot)
{
	m_apModel[nCntModel]->SetRot(rot);
}

//=============================================================================
// モデル毎の向き取得処理
//=============================================================================
D3DXVECTOR3 CPlayer::GetModelRot(int nCntModel)
{
	return m_apModel[nCntModel]->GetRot();
}

////=============================================================================
//// プレイヤーのモーション取得処理
////=============================================================================
//CMotionPlayer *CPlayer::GetMotionPlayer(void)
//{
//	return m_pMotionPlayer;
//}
//
////=============================================================================
//// プレイヤーのモデル取得処理
////=============================================================================
//CModel *CPlayer::GetModel(int nCntModel)
//{
//	return m_apModel[nCntModel];
//}