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
	/*m_target = { 0.0f,0.0f,5.0f };
	CVector3 toPos;
	toPos = m_target - m_position;
	toPosLen = toPos.Length();*/
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
	if (!(lStick_x == 0 && lStick_y == 0)) {
		m_rotation.SetRotation(CVector3::AxisY, angle);
	}
	
	m_position = m_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_moveSpeed);
	
	
	m_skinModel.Update(m_position, m_rotation, m_scale);
}
CMatrix g_mirrorViewMatrix;
CMatrix g_mirrorProjectionMatrix;
void testMirror::Render(CRenderContext& rc)
{
	CMatrix axis = CMatrix::Identity;									//プレイヤーの任意の軸周りの回転行列を作成
	axis.MakeRotationFromQuaternion(m_rotation);

	m_target.x = m_position.x + axis.m[2][0] * 10.0f;		//プレイヤーの注視点を設定
	m_target.y = m_position.y + axis.m[2][1] * 10.0f;
	m_target.z = m_position.z + axis.m[2][2] * 10.0f;

	CVector3 cameraPos = m_position;
	cameraPos.x += axis.m[2][0] * 2.0f;
	cameraPos.y += 50.0f;
	cameraPos.z += axis.m[2][2] * 2.0f;

	m_mirrorViewMatrix.MakeLookAt(m_position, m_target, { 0.0f,1.0f,0.0f });
	m_mirrorProjectionMatrix.MakeProjectionMatrix(CMath::PI * 0.3f, 1.0f, 0.1f, 10000.0f);
	g_mirrorViewMatrix = m_mirrorViewMatrix;
	g_mirrorProjectionMatrix = m_mirrorProjectionMatrix;
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix(),m_mirrorViewMatrix,m_mirrorProjectionMatrix);
}