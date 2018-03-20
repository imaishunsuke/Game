#include "stdafx.h"
#include "MapChip.h"


MapChip::MapChip()
{
}


MapChip::~MapChip()
{
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

	//���b�V���R���C�_�[���쐬�B
	m_meshCollider.CreateFromSkinModel(m_skinModel, nullptr);
	//���̂̏����쐬�B
	RigidBodyInfo rbInfo;
	rbInfo.pos = m_position;
	rbInfo.rot = m_rotation;
	rbInfo.collider = &m_meshCollider;
	rbInfo.mass = 0.0f;							//���ʂ�0�ɂ���Ɠ����Ȃ����̂ɂȂ�B
												//�w�i�Ȃǂ̓����Ȃ��I�u�W�F�N�g��0��ݒ肷��Ƃ悢�B
	m_rigidBody.Create(rbInfo);					//�쐬���������g���č��̂��쐬����B
	PhysicsWorld().AddRigidBody(m_rigidBody);	//�쐬�������̂𕨗����[���h�ɒǉ�����B

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
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix(), CMatrix::Identity, CMatrix::Identity);
}