#include "stdafx.h"
#include "MapChip.h"
#include"Mirror.h"

MapChip::MapChip()
{
}


MapChip::~MapChip()
{
}
void MapChip::OnDestroy()
{
	//物理ワールドから削除
	PhysicsWorld().RemoveRigidBody(m_rigidBody);
}
void MapChip::Init(
	const wchar_t* modelFilePath,
	CVector3 pos,
	CVector3 scale,
	CQuaternion rotation
) {
	m_skinModelData.Load(modelFilePath);
	m_skinModel.Init(m_skinModelData);
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
bool MapChip::Start()
{
	return true;
}
void MapChip::Update()
{
	m_skinModel.Update(m_position, m_rotation, m_scale);
}
void MapChip::Render(CRenderContext& rc)
{
	if (m_mirror == NULL) {
		m_mirror = FindGO<Mirror>("Mirror");
	}
	if (m_mirror->m_isMirror == true) {						//ミラーを使用中ならオブジェクトを消すフラグを０にする
		m_mirror->alphaflag = 0;
	}
	else {
		m_mirror->alphaflag = 1;
	}
	m_skinModel.Draw(rc,
		MainCamera().GetViewMatrix(),
		MainCamera().GetProjectionMatrix(),
		m_mirror->m_mirrorViewMatrix,
		m_mirror->m_mirrorProjectionMatrix,
		m_mirror->alphaflag);
}
