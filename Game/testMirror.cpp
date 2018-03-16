#include "stdafx.h"
#include "testMirror.h"


testMirror::testMirror()
{
}


testMirror::~testMirror()
{
}
bool testMirror::Start()
{
	m_skinModelData.Load(L"modelData/unityChan.cmo");
	m_skinModel.Init(m_skinModelData);
	//キャラクターコントローラーの初期化
	m_charaCon.Init(
		3.0f,
		7.0f,
		m_position
	);
	return true;
}
void testMirror::Update()
{
	m_moveSpeed.y += -20.0f;
	float lStick_x = Pad(0).GetLStickXF();
	float lStick_y = Pad(0).GetLStickYF();
	//カメラの前方向と右方向を取得
	CVector3 cameraForward = MainCamera().GetForward();
	CVector3 cameraRight = MainCamera().GetRight();
	cameraForward.y = 0.0f;
	cameraForward.Normalize();
	cameraRight.y = 0.0f;
	cameraRight.Normalize();
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	m_moveSpeed += cameraForward * lStick_y * 50.0f;
	m_moveSpeed += cameraRight * lStick_x * 50.0f;
	//キャラクターを任意の方向に向かせるための変数
	float angle = 0;
	angle = atan2f(m_moveSpeed.x, m_moveSpeed.z);
	CQuaternion qRot;
	m_rotation.SetRotation(CVector3::AxisY, angle);
	m_position = m_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_moveSpeed);
	m_skinModel.Update(m_position, m_rotation, m_scale);
}
void testMirror::Render(CRenderContext& rc)
{
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
}