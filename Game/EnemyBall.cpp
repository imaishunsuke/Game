#include "stdafx.h"
#include "EnemyBall.h"
#include "Player.h"
#include "Goal.h"
#include"Mirror.h"
#include "tkEngine/sound/tkSoundSource.h"

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
		m_enemy->Init(level->modelFilePath.c_str(),level->Pos,level->Rotation,CVector3::One);
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
		 m_position = pos;
		 m_rotation = rotation;
		 m_scale = scale;
		 //メッシュコライダーを作成。
		 m_meshCollider.CreateFromSkinModel(m_skinModel, nullptr);
		 //剛体の情報を作成。
		 RigidBodyInfo rbInfo;
		 rbInfo.pos = m_position;
		 rbInfo.rot = m_rotation;
		 rbInfo.collider = &m_meshCollider;
		 rbInfo.mass = 10.0f;							//質量を0にすると動かない剛体になる。
														//背景などの動かないオブジェクトは0を設定するとよい。
		 m_rigidBody.Create(rbInfo);					//作成した情報を使って剛体を作成する。
		 m_rigidBody.GetBody()->setUserIndex(enCollisionAttr_Obstacle);
		 PhysicsWorld().AddRigidBody(m_rigidBody);	//作成した剛体を物理ワールドに追加する。
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
	m_enemySound = NewGO<prefab::CSoundSource>(0);
	m_enemySound->Init("sound/Rock.wav", true);
	m_enemySound->SetPosition(m_position);
	m_enemySound->SetVolume(3.0);
	m_enemySound->Play(true);
	return true;
}
void EnemyBall::Update()
{
	//for (int i = 1; i < it->numMapChip; i++) {
		//if (m_charaCon.IsHitWall() == true) {
			CVector3 plPos = m_player->GetPosition();
			diff = plPos - m_position;
		//}
		diff.y = 0.0f;							//Y軸は必要ないので
		//if (diff.Length() > 10.0f) {						//距離が一定距離以内なら追いかける

	m_enemySound->SetPosition(m_position);

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
