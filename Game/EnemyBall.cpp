#include "stdafx.h"
#include "EnemyBall.h"
#include "Player.h"
#include "Goal.h"
#include "Mirror.h"
#include "tkEngine/sound/tkSoundSource.h"

#include "tkEngine/tkEnginePreCompile.h"
//#include "tkEngine/character/tkCharacterController.h"
#include "tkEngine/Physics/tkCollisionAttr.h"
#include "tkEngine/tkEngine.h"



		//衝突したときに呼ばれる関数オブジェクト(地面用)
		struct SweepResultGround : public btCollisionWorld::ConvexResultCallback
		{
			bool isHit = false;									//衝突フラグ。
			CVector3 hitPos = CVector3(0.0f, -FLT_MAX, 0.0f);	//衝突点。
			CVector3 startPos = CVector3::Zero;					//レイの始点。
			CVector3 hitNormal = CVector3::Zero;				//衝突点の法線。
			btCollisionObject* me = nullptr;					//自分自身。自分自身との衝突を除外するためのメンバ。
			float dist = FLT_MAX;								//衝突点までの距離。一番近い衝突点を求めるため。FLT_MAXは単精度の浮動小数点が取りうる最大の値。
			int ignoreCollisionAttr;				//無視するコリジョン属性のビットパターン。
			Mirror* m_mirror = nullptr;
			//衝突したときに呼ばれるコールバック関数。
			virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
			{
				if (convexResult.m_hitCollisionObject == me
					|| convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Character
					) {
					//自分に衝突した。or キャラクタ属性のコリジョンと衝突した。
					return 0.0f;
				}
					//衝突点の法線を引っ張ってくる。
					CVector3 hitNormalTmp = *(CVector3*)&convexResult.m_hitNormalLocal;
					//上方向と法線のなす角度を求める。
					float angle = hitNormalTmp.Dot(CVector3::Up);
					angle = fabsf(acosf(angle));
					if (angle < CMath::PI * 0.3f		//地面の傾斜が54度より小さいので地面とみなす。
						|| convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Ground //もしくはコリジョン属性が地面と指定されている。
						) {
						//衝突している。
						isHit = true;
						CVector3 hitPosTmp = *(CVector3*)&convexResult.m_hitPointLocal;
						//衝突点の距離を求める。。
						CVector3 vDist;
						vDist.Subtract(hitPosTmp, startPos);
						float distTmp = vDist.Length();
						if (dist > distTmp) {
							//この衝突点の方が近いので、最近傍の衝突点を更新する。
							hitPos = hitPosTmp;
							hitNormal = *(CVector3*)&convexResult.m_hitNormalLocal;
							dist = distTmp;
						}
					}
					return 0.0f;
			}
		};
		//衝突したときに呼ばれる関数オブジェクト(壁用)
		struct SweepResultWall : public btCollisionWorld::ConvexResultCallback
		{
			bool isHit = false;						//衝突フラグ。
			CVector3 hitPos = CVector3::Zero;		//衝突点。
			CVector3 startPos = CVector3::Zero;		//レイの始点。
			float dist = FLT_MAX;					//衝突点までの距離。一番近い衝突点を求めるため。FLT_MAXは単精度の浮動小数点が取りうる最大の値。
			CVector3 hitNormal = CVector3::Zero;	//衝突点の法線。
			btCollisionObject* me = nullptr;		//自分自身。自分自身との衝突を除外するためのメンバ。
			int ignoreCollisionAttr;				//無視するコリジョン属性のビットパターン。
			Player* pl = nullptr;
			Mirror* m_mirror = nullptr;
			//衝突したときに呼ばれるコールバック関数。
			virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
			{
	/*			if (ignoreCollisionAttr & (1 << convexResult.m_hitCollisionObject->getUserIndex())) {
					return 0.0f;
				}*/
				if (convexResult.m_hitCollisionObject == me
					/*|| (convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Obstacle)*/
					)
				{
					//自分に衝突した。or 障害物に衝突した。
					//toro->dameflag = 0;
					return 0.0f;
				}
				//衝突点の法線を引っ張ってくる。
				CVector3 hitNormalTmp;
				hitNormalTmp.Set(convexResult.m_hitNormalLocal);
				//上方向と衝突点の法線のなす角度を求める。
				float angle = fabsf(acosf(hitNormalTmp.Dot(CVector3::Up)));
				if (angle >= CMath::PI * 0.3f		//地面の傾斜が54度以上なので壁とみなす。
					|| convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Character	//もしくはコリジョン属性がキャラクタなので壁とみなす。
					) {
					isHit = true;
					pl->SetDamageFlag(1);
					CVector3 hitPosTmp;
					hitPosTmp.Set(convexResult.m_hitPointLocal);
					//交点との距離を調べる。
					CVector3 vDist;
					vDist.Subtract(hitPosTmp, startPos);
					vDist.y = 0.0f;
					float distTmp = vDist.Length();
					if (distTmp < dist) {
						//この衝突点の方が近いので、最近傍の衝突点を更新する。
						hitPos = hitPosTmp;
						dist = distTmp;
						hitNormal = hitNormalTmp;
					}
				}
				return 0.0f;
			}
		};

	EnemyBall::EnemyBall()
	{
	}
	EnemyBall::~EnemyBall()
	{
		//PhysicsWorld().RemoveRigidBody(m_rigidBody);
		for (auto& m_enemy : m_enemyBallList)
		{
			//PhysicsWorld().RemoveRigidBody(*m_enemy->m_charaCon.GetRigidBody());

			PhysicsWorld().RemoveRigidBody(m_enemy->m_rigidBody);
			DeleteGO(m_enemy);
		}
	}
	//void EnemyBall::OnDestroy() {
	//
	//	//m_charaCon.RemoveRigidBoby();
	//}
	//レベル作成
	//void EnemyBall::Build(const wchar_t* fileDataPath) {
	//	//スケルトン利用して配置
	//	CSkeleton skelton;
	//	skelton.Load(fileDataPath);
	//	int numMapChip = skelton.GetNumBones();
	//	for (int i = 1; i < numMapChip; i++)
	//	{
	//		CBone*bone = skelton.GetBone(i);
	//		//ボーンから拡大率、平行移動、回転を取得する。
	//		CVector3 position, scale;
	//		CQuaternion rotation;
	//		bone->CalcWorldTRS(position, rotation, scale);
	//		//軸補正を入れる。
	//		float t = position.y;
	//		position.y = position.z;
	//		position.z = -t;
	//		t = rotation.y;
	//		rotation.y = rotation.z;
	//		rotation.z = -t;
	//		//ボーン名からモデルデータのファイルパスを作成する。
	//		const wchar_t* boneName = bone->GetName();
	//		wchar_t modelDataFilePath[256];
	//		swprintf(modelDataFilePath, L"modelData/%s.cmo", boneName);
	//		EnemyBall* enemyChip = NewGO<EnemyBall>(0);
	//		enemyChip->Init(modelDataFilePath, position, CVector3::One, rotation);
	//		auto it = FindEnemyMapChip(modelDataFilePath);
			//if (it == EndEnemyMapChip()) {
	//			SetEnemyMapChip(modelDataFilePath, enemyChip);
	//		}
	//		//m_enemyBallList.emplace_back(enemyChip);
	//	}
	//}
	void EnemyBall::Create()
	{
		LevelData* level = new LevelData();
		level = GetDataList().front();

		//std::vector<LevelData*> it = GetDataList();
		int num = level->numMapChip;
		for (int i = 1; i < num; i++) {
			EnemyBall* m_enemy = NewGO<EnemyBall>(0);
			m_enemy->Init(level->modelFilePath.c_str(), level->Pos, level->Rotation, CVector3::One);
			m_enemyBallList.emplace_back(m_enemy);
		}
		delete level;
	}
	void EnemyBall::Init(const wchar_t* modelFilePath,
		CVector3 pos,
		CQuaternion rotation,
		CVector3 scale)/*std::vector<LevelData*> m_enemyDataList) */
	{
		//	while (it != GetDataList().end()) {
		//if (itr != GetDataList().end()) {
			/*CSkinModelData m_skinModelData;*/
		//wchar_t modelDataFilePath[256];
		//swprintf(modelDataFilePath, L"modelData/%s.cmo", modelFilePath);
		m_skinModelData.Load(modelFilePath);
		m_skinModel.Init(m_skinModelData);
		m_skinModel.SetShadowReceiverFlag(true);
		m_startPosition = pos;
		m_position = pos;
		m_rotation = rotation;
		m_scale = scale;
		//コライダーを作成。
		m_radius = 2.3f;
		m_collider.Create(m_radius);
		//剛体の情報を作成。
		RigidBodyInfo rbInfo;
		rbInfo.pos = m_position;
		rbInfo.rot = m_rotation;
		rbInfo.collider = &m_collider;
		rbInfo.mass = 30.0f;						//質量を0にすると動かない剛体になる。
													//背景などの動かないオブジェクトは0を設定するとよい。
		m_rigidBody.Create(rbInfo);					//作成した情報を使って剛体を作成する。
		btTransform& trans = m_rigidBody.GetBody()->getWorldTransform();
		//剛体の位置を更新。
		trans.setOrigin(btVector3(pos.x, pos.y, pos.z));


		m_rigidBody.GetBody()->setUserIndex(enCollisionAttr_throughEnemy);
		m_rigidBody.GetBody()->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
		PhysicsWorld().AddRigidBody(m_rigidBody);	//作成した剛体を物理ワールドに追加する。
		//CharaConCreate(r, 0.0f, -220.0f, m_position, m_collidertype);
		//m_charaCon.Init(
		//	r,			//半径
		//	0.0f,			//高さ
		//	-220,			//重力
		//	m_position,
		//	m_collidertype	//コライダーのタイプ
		//);
		m_skinModel.Update(m_position, m_rotation, m_scale);
		//}
				//it->numMapChip;
		//	}
		//it->numMapChip;
	}
	//void EnemyBall::Init(
	//	const wchar_t* modelFilePath,
	//	CVector3 pos,
	//	CVector3 scale,
	//	CQuaternion rotation) {
	//	m_skinModelData.Load(modelFilePath);
	//	m_skinModel.Init(m_skinModelData);
	//	m_skinModel.SetShadowReceiverFlag(true);
	//	m_position = pos;
	//	m_scale = scale;
	//	m_rotation = rotation;

	//}
	bool EnemyBall::Start()
	{
		m_player = FindGO<Player>("Player");
		m_goal = FindGO<Goal>("Goal");

		CVector3 plPos = m_player->GetPosition();
		diff = plPos - m_position;
		//	m_enemySound = NewGO<prefab::CSoundSource>(0);
		//	m_enemySound->Init("sound/Rock.wav", true);
		//	m_enemySound->SetPosition(m_position);
		//	m_enemySound->SetVolume(3.0);
		//	m_enemySound->Play(true);
			//m_charaCon.Init(
			//	r,			//半径
			//	0.0f,			//高さ
			//	-220,			//重力
			//	m_position,
			//	m_collidertype	//コライダーのタイプ
			//);
		return true;
	}
	void EnemyBall::Update()
	{
		m_moveSpeed.y -= 98.0f * GameTime().GetFrameDeltaTime();
		//for (int i = 1; i < it->numMapChip; i++) {
			if (m_isHitWall == true) {
		CVector3 plPos = m_player->GetPosition();
		diff = plPos - m_position;
		}
		diff.y = 0.0f;							//Y軸は必要ないので
		//if (diff.Length() > 10.0f) {						//距離が一定距離以内なら追いかける

//	m_enemySound->SetPosition(m_position);

	//if (m_charaCon.IsHitWall() == true) {
	//	CVector3 plPos = m_player->GetPosition();
	//	diff = plPos - m_position;
	//}
	//diff.y = 0.0f;							//Y軸は必要ないので
	////if (diff.Length() > 10.0f) {						//距離が一定距離以内なら追いかける

		diff.Normalize();
		//プレイヤーの移動速度が決定したら調整する----------------------------------
		m_moveSpeed.x = diff.x * 20.0f;
		m_moveSpeed.z = diff.z * 20.0f;
		//--------------------------------------------------------------------------	
		m_axisX.Cross(diff, up);
		m_axisX.Normalize();
		CQuaternion qRot;
		qRot.SetRotationDeg(m_axisX, -(CMath::PI * (r * 2.0f) / m_moveSpeed.Length()));
		m_rotation.Multiply(qRot);
		//}
		/*if (diff.Length() <= 10.0f) {
			m_moveSpeed.x = OldDiff.x * 20.0f;
			m_moveSpeed.z = OldDiff.z * 20.0f;
		}*/
		//m_position = m_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_moveSpeed, m_collidertype);
		m_position = Physics(m_moveSpeed, GameTime().GetFrameDeltaTime());

		m_skinModel.Update(m_position, m_rotation, m_scale);
		//}
	}
	void EnemyBall::Render(CRenderContext& rc)
	{
		//if (m_goal == 0)
		//{
			//if (m_mirror == NULL) {
			//	m_mirror = FindGO<Mirror>("Mirror");
			//}
			//if (m_mirror->GetIsMirror() == true) {						//ミラーを使用中ならオブジェクトを消すフラグを０にする
			//	m_skinModel.SetDiscardMirror(false);
			//}
			//else {
			//	m_skinModel.SetDiscardMirror(true);
			//}
		m_skinModel.Draw(rc,
			MainCamera().GetViewMatrix(),
			MainCamera().GetProjectionMatrix(),
			CMatrix::Identity,
			CMatrix::Identity
		);
		//}
	}
	const CVector3& EnemyBall::Physics(CVector3& moveSpeed, float DeltaTime)
	{
		if (m_player == nullptr)
		{
			m_player = FindGO<Player>("Player");
		}
		//次の移動先となる座標を計算する。
		CVector3 nextPosition = m_startPosition;
		//速度からこのフレームでの移動量を求める。オイラー積分。
		CVector3 addPos = moveSpeed;
		addPos.Scale(DeltaTime);
		nextPosition.Add(addPos);
		addPos.Subtract(nextPosition, m_startPosition);
		CVector3 originalXZDir = addPos;
		originalXZDir.y = 0.0f;
		originalXZDir.Normalize();
		//XZ平面での衝突検出と衝突解決を行う。
		{
			int loopCount = 0;
			while (true) {
				//現在の座標から次の移動先へ向かうベクトルを求める。
				CVector3 addPos;
				addPos.Subtract(nextPosition, m_startPosition);
				CVector3 addPosXZ = addPos;
				addPosXZ.y = 0.0f;
				if (addPosXZ.Length() < FLT_EPSILON) {
					//XZ平面で動きがないので調べる必要なし。
					//FLT_EPSILONは1より大きい、最小の値との差分を表す定数。
					//とても小さい値のことです。
					break;
				}
				CVector3 posTmp = m_startPosition;
				//レイを作成。
				btTransform start, end;
				//球コライダーの中心座標 + 高さ*0.1の座標をposTmpに求める。
				//CVector3 posTmp = m_position;
				posTmp.y += m_startPosition.y * 0.1f;
				//レイを作成。
				//btTransform start, end;
				start.setIdentity();
				end.setIdentity();
				//始点は球コライダーの中心座標 + 0.2の座標をposTmpに求める。
				start.setOrigin(btVector3(posTmp.x, posTmp.y, posTmp.z));
				//終点は次の移動先。XZ平面での衝突を調べるので、yはposTmp.yを設定する。
				end.setOrigin(btVector3(nextPosition.x, posTmp.y, nextPosition.z));

				SweepResultWall callback;
				callback.me = m_rigidBody.GetBody();
				callback.startPos = posTmp;
				callback.pl = m_player;
				//callback.ignoreCollisionAttr = m_ignoreCollisionAttrs;
				//衝突検出。
				PhysicsWorld().ConvexSweepTest((const btConvexShape*)m_collider.GetBody(), start, end, callback);

				//壁に当たっていなければ
				m_isHitWall = false;
				if (callback.isHit) {
					//当たった。
					//壁。
					m_isHitWall = true;
					CVector3 vT0, vT1;
					//XZ平面上での移動後の座標をvT0に、交点の座標をvT1に設定する。
					vT0.Set(nextPosition.x, 0.0f, nextPosition.z);
					vT1.Set(callback.hitPos.x, 0.0f, callback.hitPos.z);
					//めり込みが発生している移動ベクトルを求める。
					CVector3 vMerikomi;
					vMerikomi.Subtract(vT0, vT1);
					//XZ平面での衝突した壁の法線を求める。。
					CVector3 hitNormalXZ = callback.hitNormal;
					hitNormalXZ.y = 0.0f;
					hitNormalXZ.Normalize();
					//めり込みベクトルを壁の法線に射影する。
					float fT0 = hitNormalXZ.Dot(vMerikomi);
					//押し戻し返すベクトルを求める。
					//押し返すベクトルは壁の法線に射影されためり込みベクトル+半径。
					CVector3 vOffset;
					vOffset = hitNormalXZ;
					vOffset.Scale(-fT0 + m_radius);
					nextPosition.Add(vOffset);
					CVector3 currentDir;
					currentDir.Subtract(nextPosition, m_startPosition);
					currentDir.y = 0.0f;
					currentDir.Normalize();
					if (currentDir.Dot(originalXZDir) < 0.0f) {
						//角に入った時のキャラクタの振動を防止するために、
						//移動先が逆向きになったら移動をキャンセルする。
						nextPosition.x = m_startPosition.x;
						nextPosition.z = m_startPosition.z;
						break;
					}
				}
				else {
					//どことも当たらないので終わり。
					break;
				}
				loopCount++;
				if (loopCount == 5) {
					break;
				}
			}
		}
	
		//XZの移動は確定。
		m_startPosition.x = nextPosition.x;
		m_startPosition.z = nextPosition.z;

		{
			CVector3 addPos;
			addPos.Subtract(nextPosition, m_position);

			m_startPosition = nextPosition;	//移動の仮確定。
										//レイを作成する。
			btTransform start, end;
			start.setIdentity();
			end.setIdentity();
			//始点はカプセルコライダーの中心。
			start.setOrigin(btVector3(m_startPosition.x, m_startPosition.y, m_startPosition.z));

			//終点は地面上にいない場合は1m下を見る。
			//地面上にいなくてジャンプで上昇中の場合は上昇量の0.01倍下を見る。
			//地面上にいなくて降下中の場合はそのまま落下先を調べる。
			CVector3 endPos;
			endPos.Set(start.getOrigin());
			if (m_isOnGround == false) {
				if (addPos.y > 0.0f) {
					//ジャンプ中とかで上昇中。
					//上昇中でもXZに移動した結果めり込んでいる可能性があるので下を調べる。
					endPos.y -= addPos.y * 0.01f;
				}
				else {
					//落下している場合はそのまま下を調べる。
					endPos.y += addPos.y;
				}
			}
			else {
				//地面上にいない場合は1m下を見る。
				endPos.y -= 1.0f;
			}
			end.setOrigin(btVector3(endPos.x, endPos.y, endPos.z));
			SweepResultGround callback;
			callback.me = m_rigidBody.GetBody();
			callback.startPos.Set(start.getOrigin());
			if (fabsf(endPos.y - callback.startPos.y) > FLT_EPSILON) {
				PhysicsWorld().ConvexSweepTest((const btConvexShape*)m_collider.GetBody(), start, end, callback);
			}
			if (callback.isHit)
			{
				//当たった。
				moveSpeed.y = 0.0f;
				m_isJump = false;
				m_isOnGround = true;
				nextPosition.y = callback.hitPos.y + m_radius;
			}
			else {
				//地面上にいない。
				m_isOnGround = false;

			}
		}
		//移動確定
		m_startPosition = nextPosition;
		btRigidBody* btBody = m_rigidBody.GetBody();
		//剛体を動かす。
		btBody->setActivationState(DISABLE_DEACTIVATION);
		btTransform& trans = btBody->getWorldTransform();
		//剛体の位置を更新。
		trans.setOrigin(btVector3(m_startPosition.x, m_startPosition.y, m_startPosition.z));
		//@todo 未対応。 trans.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z));
		return m_startPosition;
	}
