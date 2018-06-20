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
}
//レベル作成
void EnemyBall::Build(const wchar_t* fileDataPath) {
	//スケルトン利用して配置
	CSkeleton skelton;
	skelton.Load(fileDataPath);
	int numMapChip = skelton.GetNumBones();
	for (int i = 1; i < numMapChip; i++)
	{
		CBone*bone = skelton.GetBone(i);
		//ボーンから拡大率、平行移動、回転を取得する。
		CVector3 position, scale;
		CQuaternion rotation;
		bone->CalcWorldTRS(position, rotation, scale);
		//軸補正を入れる。
		float t = position.y;
		position.y = position.z;
		position.z = -t;
		t = rotation.y;
		rotation.y = rotation.z;
		rotation.z = -t;
		//ボーン名からモデルデータのファイルパスを作成する。
		const wchar_t* boneName = bone->GetName();
		wchar_t modelDataFilePath[256];
		swprintf(modelDataFilePath, L"modelData/%s.cmo", boneName);
		EnemyBall* enemyChip = NewGO<EnemyBall>(0);
		enemyChip->Init(modelDataFilePath, position, CVector3::One, rotation);
		auto it = FindEnemyMapChip(modelDataFilePath);
		if (it == EndEnemyMapChip()) {
			SetEnemyMapChip(modelDataFilePath, enemyChip);
		}
	}
}
void EnemyBall::Init(
	const wchar_t* modelFilePath,
	CVector3 pos,
	CVector3 scale,
	CQuaternion rotation) {
	m_skinModelData.Load(modelFilePath);
	m_skinModel.Init(m_skinModelData);
	m_skinModel.SetShadowReceiverFlag(true);
	m_position = pos;
	m_scale = scale;
	m_rotation = rotation;
	m_charaCon.Init(
		r,			//半径
		0.0f,			//高さ
		-220,			//重力
		m_position,
		m_collidertype	//コライダーのタイプ
	);
}
bool EnemyBall::Start() 
{
	m_player = FindGO<Player>("Player");
	m_goal = FindGO<Goal>("Goal");
	m_position = { 0.0,18.0,200.0 };
	CVector3 plPos = m_player->GetPosition();
	diff = plPos - m_position;
	m_enemySound = NewGO<prefab::CSoundSource>(0);
	m_enemySound->Init("sound/Rock.wav", true);
	m_enemySound->SetPosition(m_position);
	m_enemySound->SetVolume(15.0);
	m_enemySound->Play(true);
	return true;
}
void EnemyBall::Update()
{
	m_enemySound->SetPosition(m_position);

	if (m_charaCon.IsHitWall() == true) {
		CVector3 plPos = m_player->GetPosition();
		diff = plPos - m_position;
	}
	diff.y = 0.0f;							//Y軸は必要ないので
	//if (diff.Length() > 10.0f) {						//距離が一定距離以内なら追いかける
		diff.Normalize();
	//プレイヤーの移動速度が決定したら調整する----------------------------------
		m_moveSpeed.x = diff.x * 20.0f;				
		m_moveSpeed.z = diff.z * 20.0f;
	//--------------------------------------------------------------------------	
		m_axisX.Cross(diff, up);
		m_axisX.Normalize();
		CQuaternion qRot;
		qRot.SetRotationDeg(m_axisX,-(CMath::PI * (r * 2.0f)/m_moveSpeed.Length()));
		m_rotation.Multiply(qRot);
	//}
	/*if (diff.Length() <= 10.0f) {
		m_moveSpeed.x = OldDiff.x * 20.0f;
		m_moveSpeed.z = OldDiff.z * 20.0f;
	}*/
	//m_position = m_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_moveSpeed,m_collidertype);
	m_skinModel.Update(m_position, m_rotation, m_scale);
}
void EnemyBall::Render(CRenderContext& rc)
{
	//if (m_goal == 0)
	//{
		if (m_mirror == NULL) {
			m_mirror = FindGO<Mirror>("Mirror");
		}
		if (m_mirror->GetIsMirror() == true) {						//ミラーを使用中ならオブジェクトを消すフラグを０にする
			m_skinModel.SetDiscardMirror(false);
		}
		else {
			m_skinModel.SetDiscardMirror(true);
		}
		m_skinModel.Draw(rc,
			MainCamera().GetViewMatrix(),
			MainCamera().GetProjectionMatrix(),
			CMatrix::Identity,
			CMatrix::Identity
		);
	//}
}
