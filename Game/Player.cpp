#include "stdafx.h"
#include "Player.h"
#include"Torokko.h"
#include"Mirror.h"

Player::Player()
{
}


Player::~Player()
{
}

bool Player::Start() {
	//モデルデータのロード
	m_skinModelData.Load(L"modelData/unityChan.cmo");
	m_skinModel.Init(m_skinModelData);
	m_rotation.Multiply(m_rotation);
	m_mirror = FindGO<Mirror>("Mirror");
	toro = FindGO<Torokko>("Trokko");
	m_position = toro->m_position;
	diff.x = toro->m_gpos.x - toro->m_position.x;
	diff.y = toro->m_gpos.y - toro->m_position.y;
	diff.z = toro->m_gpos.z - toro->m_position.z;
	plposlen=diff.Length();
	m_skinModel.Update(m_position, m_rotation, CVector3::One);
	
	return true;
}
void Player::Rotation() {
	m_rot.MakeRotationFromQuaternion(toro->m_rotation);
	m_position.x = m_rot.m[2][0] * plposlen + toro->m_position.x;
	m_position.y = m_rot.m[2][1] * plposlen + toro->m_position.y;
	m_position.z = m_rot.m[2][2] * plposlen + toro->m_position.z;
	m_rotation.x = toro->m_rotation.x;
	m_rotation.y = toro->m_rotation.y;
	m_rotation.z = toro->m_rotation.z;
	m_rotation.w = toro->m_rotation.w;


	m_skinModel.Update(m_position, m_rotation, CVector3::One);
}

void Player::Update()
{
	Rotation();
	m_skinModel.Update(m_position, m_rotation, CVector3::One);

}

void Player::Render(CRenderContext& rc)
{
	m_mirror->alphaflag = 0;
	m_skinModel.Draw(rc, 
		MainCamera().GetViewMatrix(), 
		MainCamera().GetProjectionMatrix(),
		CMatrix::Identity,
		CMatrix::Identity,
		m_mirror->alphaflag);
}
