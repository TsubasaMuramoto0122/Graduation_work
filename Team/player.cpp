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
#include "motion.h"
#include "control_player.h"
#include "shadow.h"
#include "sound.h"
#include "collision_sphere.h"
#include "mesh_field.h"
#include "mesh_wall.h"
#include "life.h"
#include "game.h"
#include "cpu.h"
#include "presetdelayset.h"
#include "realshadow.h"
#include "playerui.h"
#include "playericon.h"
#include "playerice.h"
#include "billboard.h"

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define PLAYER_BEGIN_LIFE		(550)	// 初期ライフ
#define INVINCIBLE_TIME			(210)	// 無敵時間
#define ICE_TIME				(210)	// 氷の状態異常の時間
#define POISON_TIME				(300)	// 毒の状態異常の時間
#define CONFUSION_TIME			(500)	// 混乱の状態異常の時間
#define POISON_DAMAGE			(3)		// 毒のスリップダメージ
#define PUSH_INVALID_TIME		(180)	// 押された後、再び押されるようになるまでの時間
#define POISON_COUNT			(15)	// 毒のスリップダメージが入るまでの時間
#define POISON_BUBBLE_COUNT		(14)	// 毒の泡生成間隔

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
int CPlayer::m_nSurviveTime[PLAYER_TYPE_MAX] = {};

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
	m_pMotion = NULL;
	m_pControl = NULL;
	m_pCollision = NULL;
	m_pLife = NULL;
	m_pDelaySet = NULL;
	m_state = PLAYER_STATE_NORMAL;
	m_badState = PLAYER_BAD_STATE_NONE;
	m_type = PLAYER_TYPE_MAX;
	m_bLand = false;
	m_bInvDamage = false;
	m_bInvSliding = false;
	m_bPressed = false;
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
	m_bInvDamage = false;
	m_bInvSliding = false;
	m_bPressed = false;
	m_bDraw = true;
	m_nLife = PLAYER_BEGIN_LIFE;
	m_nInvincibleTime = 0;
	m_nBadStateTime = 0;
	m_nPoisonCount = 0;
	m_nPressCount = 0;

	// モデル生成処理
	ModelCreate(m_type);

	// 変数の設定
	SetRot(m_rot);
	SetPos(m_pos);

	// 体にコリジョン(プレイヤー判定)をつける
	m_pCollision = CCollisionSphere::Create(m_pos, m_size.x, 16, 16, CCollisionSphere::COLLISION_S_TYPE::COLLISION_S_TYPE_PLAYER, -1.0f, 0.0f);
	m_pCollision->SetNumPlayer(m_type);

	m_fHeadHeight = m_apModel[1]->GetMaxSize().y;

	// ライフ、モーションの生成
	D3DXVECTOR2 lifePos = D3DXVECTOR2(0.0f, 0.0f);
	switch (m_type)
	{
	case PLAYER_TYPE_1P:
		lifePos = D3DXVECTOR2(150.0f, 100.0f);
		CUI::Create(D3DXVECTOR2(lifePos.x + 50.0f, lifePos.y - 60.0f), D3DXVECTOR2(70.0f, 60.0f), 8, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pMotion = CMotion::Create(this, CMotion::MOTION_TYPE_P1);
		m_pPlayerUI = CPlayerUI::Create(42, m_fHeadHeight);
		m_pPlayerIcon = CPlayerIcon::Create(D3DXVECTOR2(lifePos.x - 45.0f, lifePos.y - 60.0f), D3DXVECTOR2(60.0f, 60.0f), 37, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		break;
	case PLAYER_TYPE_2P:
		lifePos = D3DXVECTOR2(400.0f, 100.0f);
		CUI::Create(D3DXVECTOR2(lifePos.x + 50.0f, lifePos.y - 60.0f), D3DXVECTOR2(70.0f, 60.0f), 9, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pMotion = CMotion::Create(this, CMotion::MOTION_TYPE_P2);
		m_pPlayerUI = CPlayerUI::Create(43, m_fHeadHeight);
		m_pPlayerIcon = CPlayerIcon::Create(D3DXVECTOR2(lifePos.x - 45.0f, lifePos.y - 60.0f), D3DXVECTOR2(60.0f, 60.0f), 38, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		break;
	case PLAYER_TYPE_3P:
		lifePos = D3DXVECTOR2(SCREEN_WIDTH - 400.0f, 100.0f);
		CUI::Create(D3DXVECTOR2(lifePos.x + 50.0f, lifePos.y - 60.0f), D3DXVECTOR2(70.0f, 60.0f), 10, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pMotion = CMotion::Create(this, CMotion::MOTION_TYPE_P3);
		m_pPlayerUI = CPlayerUI::Create(44, m_fHeadHeight);
		m_pPlayerIcon = CPlayerIcon::Create(D3DXVECTOR2(lifePos.x - 45.0f, lifePos.y - 60.0f), D3DXVECTOR2(60.0f, 60.0f), 39, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		break;
	case PLAYER_TYPE_4P:
		lifePos = D3DXVECTOR2(SCREEN_WIDTH - 150.0f, 100.0f);
		CUI::Create(D3DXVECTOR2(lifePos.x + 50.0f, lifePos.y - 60.0f), D3DXVECTOR2(70.0f, 60.0f), 11, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pMotion = CMotion::Create(this, CMotion::MOTION_TYPE_P4);
		m_pPlayerUI = CPlayerUI::Create(45, m_fHeadHeight);
		m_pPlayerIcon = CPlayerIcon::Create(D3DXVECTOR2(lifePos.x - 45.0f, lifePos.y - 60.0f), D3DXVECTOR2(60.0f, 60.0f), 40, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		break;
	default:
		break;
	}
	m_pLife = CLifeUI::Create(lifePos, D3DXVECTOR2(200.0f, 50.0f));

	//m_pShadow = CShadow::Create(D3DXVECTOR3(m_size.x * 0.5f, 0.0f, m_size.z * 0.5f), pos, 1);

	m_pMotion->Update(this);
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

	if (m_pControl != NULL)
	{
		m_pControl->Uninit();
		m_pControl = NULL;
	}

	if (m_pCollision != NULL)
	{
		m_pCollision = NULL;
	}

	if (m_pDelaySet != NULL)
	{
		m_pDelaySet = NULL;
	}

	if (m_pLife != NULL)
	{
		m_pLife = NULL;
	}

	if (m_pMotion != NULL)
	{
		m_pMotion = NULL;
	}

	if (m_pPlayerIce != NULL)
	{
		m_pPlayerIce = NULL;
	}

	/*if (m_pShadow != NULL)
	{
		m_pShadow = NULL;
	}*/

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
		if (m_pControl != NULL)
		{
			m_pControl->Update(this);
		}
		if (CManager::GetPause() == false)
		{
			// 位置の取得
			D3DXVECTOR3 pos = GetPos();
			m_pos = pos;
			m_posOld = m_pos;

			// 1フレーム前の位置設定
			SetPosOld(m_posOld);

			// 移動処理
			Move();

			// 押されたら
			if (m_bPressed == true)
			{
				// カウントを増やす
				m_nPressCount++;

				if (m_nPressCount >= PUSH_INVALID_TIME)
				{
					m_nPressCount = 0;
					m_bPressed = false;
				}
			}

			// 他のコリジョンと接触した時の処理
			TouchCollision();

			// 状態異常の処理
			BadState(m_badState);

			// 移動量反映
			m_pos += m_move;

			// モーション
			m_pMotion->Update(this);

			// 位置反映
			SetPos(m_pos);
			//m_pShadow->MoveY(D3DXVECTOR3(m_pos.x, 0.0f, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

			// 着地状態を初期化
			m_bLand = false;

			// 敗北の状態じゃなかったら
			if (GetState() != PLAYER_STATE_DEFEAT)
			{
				m_Wall = CMeshWall::Collision(this);
				// 壁との当たり判定
				if (m_Wall.x < D3DX_PI)
				{
					m_bWall = true;
				}
				else
				{
					m_bWall = false;
				}
			}

			if (m_bLand == false)
			{
				// 地面との当たり判定
				m_bLand = CMeshField::Collision(this);
			}
			else
			{
				// 着地したらY方向の移動量を0に
				m_move.y = 0.0f;
			}

			// 位置取得
			m_pos = GetPos();

			// プレイヤーとの押出判定
			Push(this);

			// 無敵時の処理
			Invincible();

			// コリジョンの追従
			D3DXVECTOR3 collisionPos = D3DXVECTOR3(m_pos.x, m_pos.y + GetRadius(), m_pos.z);
			m_pCollision->SetPosCollision(collisionPos);

			// エフェクトの追従
			if (m_pDelaySet != NULL)
			{
				//m_pDelaySet->Move(m_pos - m_posOld);
			}

			//プレイヤーUIの追従
			D3DXVECTOR3 HeadPos = D3DXVECTOR3(m_apModel[1]->GetMatrix()._41, m_apModel[1]->GetMatrix()._42, m_apModel[1]->GetMatrix()._43);
			m_pPlayerUI->SetPos(HeadPos);

			//HPゲージの設定
			m_pLife->SetLifeBar(m_nLife, PLAYER_BEGIN_LIFE);
		}
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

void CPlayer::ZTexDraw()
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
			m_apModel[nCntModel]->ZTexDraw();
		}
	}
}

//=============================================================================
// 生成処理
//=============================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, PLAYER_TYPE type, bool bPlayer, float fFriction, float fMaxSpeed, float fGravity, bool bTutorial)
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
			if(bPlayer == true)
			{
				// プレイヤー操作のクラスを生成
				pPlayer->m_pControl = CControlPlayer::Create(fFriction, fMaxSpeed, fGravity);
			}
			else
			{
				// CPUのクラスを生成
				pPlayer->m_pControl = CCPU::Create(fFriction, fMaxSpeed, fGravity);
			}

			// 変数の初期化
			pPlayer->m_rot = rot;
			pPlayer->m_type = type;

			pPlayer->m_bPlayer = bPlayer;
			pPlayer->m_bTutorial = bTutorial;

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
	// テキストファイルの読み込み
	char cString[256];
	FILE *pFile = NULL;

	switch (type)
	{
	case PLAYER_TYPE_1P:
		pFile = fopen("data/FILES/Motions/motion_p1.txt", "r");
		break;
	case PLAYER_TYPE_2P:
		pFile = fopen("data/FILES/Motions/motion_p2.txt", "r");
		break;
	case PLAYER_TYPE_3P:
		pFile = fopen("data/FILES/Motions/motion_p3.txt", "r");
		break;
	case PLAYER_TYPE_4P:
		pFile = fopen("data/FILES/Motions/motion_p4.txt", "r");
		break;
	default:
		break;
	}

	if (pFile != NULL)
	{
		int nCntModel = 0;
		char cFileName[MAX_PLAYER_MODEL][256];

		while (1)
		{
			fscanf(pFile, "%s", &cString[0]);

			// モデルのパスを取得
			if (strcmp(&cString[0], "MODEL_FILENAME") == 0)
			{
				fscanf(pFile, "%s", &cString[0]);
				fscanf(pFile, "%s", &cFileName[nCntModel][0]);
				nCntModel++;
			}

			// モデルが最大数になったらパスの読み込みを終了
			if (nCntModel >= MAX_PLAYER_MODEL)
			{
				nCntModel = 0;
				break;
			}
		}

		int nIdx = 0, nParents = 0;
		D3DXVECTOR3 pos, rot;

		while (1)
		{
			fscanf(pFile, "%s", &cString[0]);

			if (strcmp(&cString[0], "PARTSSET") == 0)	//PARTSSETの文字列
			{
				// モデルのパーツ数だけ回す
				while (1)
				{
					fscanf(pFile, "%s", &cString[0]);

					if (strcmp(&cString[0], "INDEX") == 0) //インデックス番号
					{
						fscanf(pFile, "%s", &cString[0]);
						fscanf(pFile, "%d", &nIdx);
					}
					if (strcmp(&cString[0], "PARENT") == 0) //親のモデル
					{
						fscanf(pFile, "%s", &cString[0]);
						fscanf(pFile, "%d", &nParents);
					}
					if (strcmp(&cString[0], "POS") == 0) //位置
					{
						// 位置を取得する
						fscanf(pFile, "%s", &cString[0]);
						fscanf(pFile, "%f%f%f", &pos.x, &pos.y, &pos.z);
					}
					if (strcmp(&cString[0], "ROT") == 0) //向き
					{
						// 向きを取得する
						fscanf(pFile, "%s", &cString[0]);
						fscanf(pFile, "%f%f%f", &rot.x, &rot.y, &rot.z);
					}
					if (strcmp(&cString[0], "END_PARTSSET") == 0)
					{
						break;
					}
				}

				// モデルを生成し、向きと位置を設定
				m_apModel[nCntModel] = CModel::Create(&cFileName[nCntModel][0]);
				m_apModel[nCntModel]->SetRot(rot);
				m_apModel[nCntModel]->SetPos(pos);

				// 親モデルを設定
				if (nParents == -1)
				{
					// -1 なら親モデル無し
					m_apModel[nCntModel]->SetParent(NULL);
				}
				else
				{
					// -1 以外なら親子付け
					m_apModel[nCntModel]->SetParent(m_apModel[nParents]);
				}

				nCntModel++;
			}

			// モデルが最大数になったら配置を終了
			if (nCntModel >= MAX_PLAYER_MODEL)
			{
				break;
			}
		}
		fclose(pFile);
	}

	m_size.x = 50.0f;
	m_size.y = 50.0f;
	m_size.z = 50.0f;
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
		// 押されていないかつ、他のプレイヤーの攻撃に当たった瞬間なら
		if (m_bPressed == false && m_pCollision->GetTouchCollision(CCollisionSphere::COLLISION_S_TYPE_ATTACK) == true)
		{
			// 何らかの無敵状態じゃないなら
			if (m_bInvDamage == false && m_bInvSliding == false)
			{
				// ダメージモーション(4)にする
				m_pMotion->SetMotion(4);

				// 状態を<吹っ飛び>に設定
				SetState(PLAYER_STATE_BLOWAWAY);

				// 氷の状態異常を治す
				if (GetBadState() == PLAYER_BAD_STATE_ICE)
				{
					SetBadState(PLAYER_BAD_STATE_NONE);
				}

				// 押された状態にする
				m_bPressed = true;

				// 攻撃してきたプレイヤーの方向を向かせる
				m_rot.y = m_pCollision->GetPlayerRot() - D3DX_PI;

				//角度が狂わないようにする
				if (m_rot.y < -D3DX_PI)
				{
					m_rot.y += D3DX_PI * 2.0f;
				}

				// Y方向への移動量をリセットし、ジャンプさせる
				m_move.y = PLAYER_KNOCKBACK_JUMP;
			}
		}
		// 他のプレイヤーの攻撃 または 爆発に当たった瞬間なら
		else if (m_pCollision->GetTouchCollision(CCollisionSphere::COLLISION_S_TYPE_EXPLOSION) == true ||
				m_pCollision->GetTouchCollision(CCollisionSphere::COLLISION_S_TYPE_POISON) == true ||
				m_pCollision->GetTouchCollision(CCollisionSphere::COLLISION_S_TYPE_CONFUSION) == true)
		{
			// 何らかの無敵状態じゃないなら
			if (m_bInvDamage == false && m_bInvSliding == false)
			{
				// ダメージモーション(4)にする
				m_pMotion->SetMotion(4);

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
					m_nLife -= 100;

					// ライフが残っていたら
					if (m_nLife > 0)
					{
						// 被ダメージによる無敵にする
						m_bInvDamage = true;

						//アイコン振動させる
						m_pPlayerIcon->SetDamage(true);
					}

					// 対象のコリジョンの方向を向かせる
					m_rot.y = m_pCollision->GetObjectiveRot();
				}
				// 毒の爆発に当たっていたら
				else if (m_pCollision->GetTouchCollision(CCollisionSphere::COLLISION_S_TYPE_POISON) == true)
				{
					// ライフを減らす
					m_nLife -= 100;

					// ライフが残っていたら
					if (m_nLife > 0)
					{
						// 被ダメージによる無敵にする
						m_bInvDamage = true;

						//アイコン振動させる
						m_pPlayerIcon->SetDamage(true);
					}

					SetBadState(PLAYER_BAD_STATE_POISON);

					// 対象のコリジョンの方向を向かせる
					m_rot.y = m_pCollision->GetObjectiveRot();
				}
				// 混乱の爆発に当たっていたら
				else if (m_pCollision->GetTouchCollision(CCollisionSphere::COLLISION_S_TYPE_CONFUSION) == true)
				{
					// ライフを減らす
					m_nLife -= 100;

					// ライフが残っていたら
					if (m_nLife > 0)
					{
						// 被ダメージによる無敵にする
						m_bInvDamage = true;

						//アイコン振動させる
						m_pPlayerIcon->SetDamage(true);

						// 混乱の効果音を再生
						CSound::Play(6);
					}
					SetBadState(PLAYER_BAD_STATE_CONFUSION);

					// 対象のコリジョンの方向を向かせる
					m_rot.y = m_pCollision->GetObjectiveRot();
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
					m_move.y = PLAYER_DEFEATKNOCKBACK_JUMP;
					//m_move.y += PLAYER_DEFEATKNOCKBACK_JUMP;
				}
				// ライフがあるなら通常の挙動
				else
				{
					// Y方向への移動量をリセットし、ジャンプさせる
					m_move.y = PLAYER_KNOCKBACK_JUMP;
					//m_move.y += PLAYER_KNOCKBACK_JUMP;
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
		else if (m_pCollision->GetTouchCollision(CCollisionSphere::COLLISION_S_TYPE_POISON_FIELD) == true)
		{
			// 何らかの無敵状態じゃないなら
			if (m_bInvDamage == false && m_bInvSliding == false)
			{
				SetBadState(PLAYER_BAD_STATE_POISON);
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
			m_bDraw = true;

			// 無敵時間をリセット
			m_nInvincibleTime = 0;
		}
		if (m_pCollision != NULL)
		{
			if (m_bInvDamage == true || m_bInvSliding == true)
			{
				m_pCollision->SetColor(D3DCOLOR_RGBA(255, 255, 0, 153));
			}
			else
			{
				m_pCollision->SetColor(D3DCOLOR_RGBA(255, 255, 255, 153));
			}
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

		// モーションを止める
		m_pMotion->SetStop(true);

		// 一定時間が経ったら
		if (m_nBadStateTime >= ICE_TIME)
		{
			// 状態異常をを消す
			SetBadState(PLAYER_BAD_STATE_NONE);

			// モーションを動かす
			m_pMotion->SetStop(false);

			// 時間をリセット
			m_nBadStateTime = 0;
		}
		break;
		// 毒
	case PLAYER_BAD_STATE_POISON:
		// カウントを増やす
		m_nBadStateTime++;

		if (m_nBadStateTime % POISON_BUBBLE_COUNT == 0)
		{
			//泡出す
			PoisonBubble();
		}

		// <吹っ飛び>の状態以外で動いている場合
		if (m_state != PLAYER_STATE_BLOWAWAY && m_move.x != 0.0f || m_move.z != 0.0f)
		{
			// カウントを増やす
			m_nPoisonCount++;

			// 一定時間が経過する
			if (m_nPoisonCount >= POISON_COUNT)
			{
				// ライフが毒ダメージより上だったら
				if (m_nLife > POISON_DAMAGE)
				{
					// ライフを減らす
					m_nLife -= POISON_DAMAGE;
				}
				// ライフが1より高い
				else if (m_nLife > 1)
				{
					// ライフを1にする
					m_nLife = 1;
				}
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
			m_nPoisonCount = 0;
		}
		break;
		// 混乱
	case PLAYER_BAD_STATE_CONFUSION:
		// カウントを増やす
		m_nBadStateTime++;

		// 一定時間が経ったら
		if (m_nBadStateTime >= CONFUSION_TIME)
		{
			// 状態異常を消す
			SetBadState(PLAYER_BAD_STATE_NONE);

			// 混乱の効果音を止める
			CSound::Stop(6);

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

//================================================
// 一番近いプレイヤー探す(CPU用)
//================================================
CPlayer *CPlayer::SearchPlayer(CScene *pScene)
{
	//オブジェクト情報を入れるポインタ
	CScene *pObject = NULL;
	//オブジェクト情報を保存するポインタ変数
	CScene *pSaveObject = NULL;

	float fShortDistance = 9999999.0f;
	CPlayer *pSavePlayer = NULL;

	D3DXVECTOR3 pos = pScene->GetPos();			//プレイヤーの位置

	//先頭のポインタを代入
	pObject = pObject->GetTopObj(CScene::PRIORITY_CHARA);

	while (pObject != NULL)
	{
		//現在のオブジェクトのポインタを保存
		pSaveObject = pObject;

		if (pObject->GetObjType() == CScene::OBJECTTYPE_PLAYER && pScene != pObject)
		{
			CPlayer *pPlayer = (CPlayer*)pObject;

			if (pPlayer->GetDeath() == false && pPlayer->m_state != PLAYER_STATE_DEFEAT && pPlayer->GetState() != PLAYER_STATE_BLOWAWAY)
			{
				D3DXVECTOR3 Bombpos = pPlayer->GetPos();	//対象の位置

				float fDistance = sqrtf(powf(Bombpos.x - pos.x, 2.0f) + powf(Bombpos.z - pos.z, 2.0f));
				if (fShortDistance > fDistance)
				{
					pSavePlayer = pPlayer;
					fShortDistance = fDistance;
				}
			}
		}
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}
	return pSavePlayer;
}

void CPlayer::SetBadState(PLAYER_BAD_STATE state)
{
	//混乱エフェクト
	if (m_badState != PLAYER_BAD_STATE_CONFUSION && state == PLAYER_BAD_STATE_CONFUSION)
	{
		CPresetDelaySet::Create("EDDY", m_pos, this);
	}
	m_badState = state;
	//氷生成
	if (state == PLAYER_BAD_STATE_ICE)
	{
		if (m_pPlayerIce == NULL)
		{
			m_pPlayerIce = CPlayerIce::Create(m_apModel[0]->GetMatrix());
		}
	}
	else if (m_pPlayerIce != NULL)
	{
		m_pPlayerIce->Uninit();
		m_pPlayerIce = NULL;
	}
}

//毒の泡出す
void CPlayer::PoisonBubble()
{
	D3DXMATRIX mtx = m_apModel[1]->GetMatrix();
	D3DXVECTOR3 pos = m_apModel[1]->GetPos();
	D3DXMATRIX mtxTrans, mtxWorld; //パーツ用計算用マトリックス
	D3DXMATRIX mtxParent; //親のマトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y + m_fHeadHeight, pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	//算出した各ワールドマトリックスと親(頭)のマトリックスを掛け合わせる
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtx);

	CBillboard::Create(D3DXVECTOR3(mtxWorld._41, mtxWorld._42, mtxWorld._43), D3DXVECTOR3(0.3f, 0.7f, 0.0f), D3DXVECTOR3(16.0f, 16.0f, 0.0f), 6, D3DXCOLOR(1.0f, 0.5f, 1.0f, 0.6f), 70);
}