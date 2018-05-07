#include "stdafx.h"
#include "EnemyBall.h"
#include "Player.h"
#include "Torokko.h"


EnemyBall::EnemyBall()
{
}
EnemyBall::~EnemyBall()
{
}
bool EnemyBall::Start() 
{
	m_player = FindGO<Player>("Player");
	toro = FindGO<Torokko>("Trokko");
	m_skinModelData.Load(L"modelData/EnemyBall.cmo");
	m_skinModel.Init(m_skinModelData);
	//CapsuleType type

	m_charaCon.Init(
		4.0f,
		0.0f,
		m_position,
		m_collidertype
	);
	diff = m_player->m_position - m_position;
	return true;
}
void EnemyBall::Update()
{
	if (m_charaCon.IsOnGround() == false) {
		m_moveSpeed.y -= 4.8f * GameTime().GetFrameDeltaTime();					//�d�́@�ύX����
	}
	CVector3 scale = { 0.1f,0.1f,0.1f };
	if (m_charaCon.IsHitWall() == true) {
		diff = m_player->m_position - m_position;
	}
	diff.y = 0.0f;							//Y���͕K�v�Ȃ��̂�
	//if (diff.Length() > 10.0f) {						//��������苗���ȓ��Ȃ�ǂ�������
		diff.Normalize();
		m_moveSpeed.x = diff.x * 20.0f;				//�v���C���[�̈ړ����x�����肵���璲������//////////////////////
		m_moveSpeed.z = diff.z * 20.0f;
		m_axisX.Cross(diff, up);
		m_axisX.Normalize();
		CQuaternion qRot;
		qRot.SetRotationDeg(m_axisX, -15.0f);
		m_rotation.Multiply(qRot);
	//}
	/*if (diff.Length() <= 10.0f) {
		m_moveSpeed.x = OldDiff.x * 20.0f;
		m_moveSpeed.z = OldDiff.z * 20.0f;
	}*/
	m_position = m_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_moveSpeed,m_collidertype);
	m_skinModel.Update(m_position,m_rotation,scale);
}
void EnemyBall::Render(CRenderContext& rc)
{
	int alphaflag = 1;
	m_skinModel.Draw(rc,
		MainCamera().GetViewMatrix(), 
		MainCamera().GetProjectionMatrix(),
		CMatrix::Identity,
		CMatrix::Identity,
		alphaflag
	);
}