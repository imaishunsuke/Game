#include "stdafx.h"
#include "vrMapChip.h"
#include"Mirror.h"
#include "Player.h"
#include "GameCamera.h"

vrMapChip::vrMapChip()
{
}


vrMapChip::~vrMapChip()
{
}
void vrMapChip::OnDestroy() {
	//物理ワールドから削除。
	PhysicsWorld().RemoveRigidBody(m_rigidBody);
}
void vrMapChip::Init(
	const wchar_t* modelFilePath,
	CVector3 pos,
	CVector3 scale,
	CQuaternion rotation
) {
	m_skinModelData.Load(modelFilePath);
	m_skinModel.Init(m_skinModelData);
	m_skinModel.SetShadowReceiverFlag(true);
	m_position = pos;
	m_scale = scale;
	m_rotation = rotation;

	//メッシュコライダーを作成。
	m_meshCollider.CreateFromSkinModel(m_skinModel, nullptr);
	//剛体の情報を作成。
	RigidBodyInfo rbInfo;
	rbInfo.pos = m_position;
	rbInfo.rot = m_rotation;
	rbInfo.collider = &m_meshCollider;
	rbInfo.mass = 0.0f;							//質量を0にすると動かない剛体になる。
												//背景などの動かないオブジェクトは0を設定するとよい。
	m_rigidBody.Create(rbInfo);					//作成した情報を使って剛体を作成する。
	m_rigidBody.GetBody()->setUserIndex(enCollisionAttr_Obstacle);
	PhysicsWorld().AddRigidBody(m_rigidBody);	//作成した剛体を物理ワールドに追加する。

}
bool vrMapChip::Start()
{
	m_player = FindGO<Player>("Player");
	m_camera = FindGO<GameCamera>("gamecamera");
	return true;
}
void vrMapChip::Update()
{
	if (m_mirror == NULL) {
		m_mirror = FindGO<Mirror>("Mirror");
	}
	if (m_mirror->GetIsMirror() == true) {						//ミラーを使用中ならオブジェクトを消すフラグを０にする
		m_skinModel.SetDiscardMirror(false);
	}
	else {
		m_skinModel.SetDiscardMirror(true);
	}
	//m_skinModel.SetDiscardMirror(m_mirror->_alphaflag);
	CVector3 ditheringPos = CVector3::Zero;
	CVector3 Pos = m_camera->GetSpringCamera().GetPosition();
	CVector3 diff = m_player->GetPosition() - Pos;
	diff.Normalize();
	ditheringPos.x = Pos.x + diff.x * 20.0f;
	ditheringPos.y = Pos.y + diff.y * 20.0f;
	ditheringPos.z = Pos.z + diff.z * 20.0f;
	m_skinModel.Update(m_position, m_rotation, m_scale);
}
void vrMapChip::Render(CRenderContext& rc)
{
	m_skinModel.Draw(rc,
		MainCamera().GetViewMatrix(),
		MainCamera().GetProjectionMatrix(),
		m_mirror->GetMirrorViewMatrix(),
		m_mirror->GetMirrorProjectionMatrix());
}
