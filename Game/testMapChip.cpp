#include "stdafx.h"
#include "testMapChip.h"


testMapChip::testMapChip()
{
}


testMapChip::~testMapChip()
{
}
void testMapChip::OnDestroy()
{
	//物理ワールドから削除
	PhysicsWorld().RemoveRigidBody(m_rigidBody);
}
void testMapChip::Init(
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

	//メッシュコライダーを作成
	m_meshCollider.CreateFromSkinModel(m_skinModel, nullptr);

	//剛体情報を作成
	RigidBodyInfo rbInfo;
	rbInfo.pos = m_position;
	rbInfo.rot = m_rotation;
	rbInfo.collider = &m_meshCollider;
	rbInfo.mass = 0.0f;

	m_rigidBody.Create(rbInfo);
	PhysicsWorld().AddRigidBody(m_rigidBody);
}
bool testMapChip::Start()
{
	return true;
}
void testMapChip::Update()
{
	m_skinModel.Update(m_position, m_rotation, m_scale);
}
extern CMatrix g_mirrorViewMatrix;
extern CMatrix g_mirrorProjectionMatrix;
void testMapChip::Render(CRenderContext& rc)
{
	m_skinModel.Draw(
		rc, 
		MainCamera().GetViewMatrix(), 
		MainCamera().GetProjectionMatrix(),
		g_mirrorViewMatrix,
		g_mirrorProjectionMatrix);
}