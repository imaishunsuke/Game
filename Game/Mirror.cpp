#include "stdafx.h"
#include "Mirror.h"
#include"Torokko.h"

Mirror::Mirror()
{
}

Mirror::~Mirror()
{
}
bool Mirror::Start()
{
	m_skinModelData.Load(L"modelData/mirror.cmo");
	m_skinModel.Init(m_skinModelData);
	/*m_charaCon.Init(
		6.0f,
		3.0f,
		m_position
	);*/

	Torokko*toro = FindGO<Torokko>("Trokko");
	m_position = toro->m_position;
	diff.x = toro->m_gpos.x - toro->m_position.x;
	diff.y = toro->m_gpos.y - toro->m_position.y;
	diff.z = toro->m_gpos.z - toro->m_position.z;
	Mirlen = diff.Length();
	m_skinModel.Update(m_position, m_rotation, CVector3::One);
	return true;
}

void Mirror::Rotation() {
	Torokko*toro = FindGO<Torokko>("Trokko");
	m_rot.MakeRotationFromQuaternion(toro->m_rotation);
	m_position.x = m_rot.m[2][0] * Mirlen + toro->m_position.x;
	m_position.y = m_rot.m[2][1] * Mirlen + toro->m_position.y;
	m_position.z = m_rot.m[2][2] * Mirlen + toro->m_position.z;

	/*CVector3 torokkoforward;
	torokkoforward.x = m_rot.m[2][0];
	torokkoforward.y = m_rot.m[2][1];
	torokkoforward.z = m_rot.m[2][2];
	m_mirrorforwardMatrix.MakeRotationFromQuaternion(m_rotation);
	CVector3 mirrorLength;
	mirrorLength.x = m_mirrorforwardMatrix.m[2][0];
	mirrorLength.y = m_mirrorforwardMatrix.m[2][1];
	mirrorLength.z = m_mirrorforwardMatrix.m[2][2];
	
	float to=torokkoforward.Dot(mirrorLength);
	float len=torokkoforward.Length() * mirrorLength.Length();
	angle= acosf(to);*/
	//qRot.x = toro->m_rotation.x;
	//qRot.y = toro->m_rotation.y;
	//qRot.z = toro->m_rotation.z;
	//qRot.w = toro->m_rotation.w;
	/* CQuaternion OldRot = CQuaternion::Identity;

	OldRot.SetRotation(CVector3::AxisY, angle);
	m_rotation.Multiply(OldRot);*/
	//m_rotation.Multiply(OldRot);
	//m_skinModel.Update(m_position, m_rotation, CVector3::One);
}
void Mirror::Update()
{
	Rotation();
	if (Pad(0).IsPress(enButtonUp)) {
		m_moveSpeed.z = 5.0f;
	}else if (Pad(0).IsPress(enButtonLeft)) {
		m_moveSpeed.x = -5.0f;
	}else if (Pad(0).IsPress(enButtonRight)) {
		m_moveSpeed.x = 5.0f;
	}
	else if (Pad(0).IsPress(enButtonDown)) {
		m_moveSpeed.z = -5.0f;
	}else {
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 0.0f;
	}

	//m_position = m_moveSpeed;
	if (Pad(0).IsTrigger(enButtonB) && m_isMirror == false) {
		m_isMirror = true;
	}
	else if(Pad(0).IsTrigger(enButtonB) && m_isMirror == true){
		m_isMirror = false;
	}
	//スティックの入力
	CVector3 rStick = CVector3::Zero;
	rStick.x = Pad(0).GetRStickXF();
	rStick.y = -Pad(0).GetRStickYF();
	rStick.z = 0.0f;
	rStick = rStick * 10.0f;

	////回転の上限
	if (angleX > 50.0f)
	{
		angleX = 50.0f;
	}
	if (angleX < -50.0f)
	{
		angleX = -50.0f;
	}
	if (angleY > 50.0f)
	{
		angleY = 50.0f;
	}
	if (angleY < -50.0f)
	{
		angleY = -50.0f;
	}
	angleX += rStick.x;
	angleY += rStick.y;
	//m_rotation.Multiply(qRot);
	qRot = CQuaternion::Identity;
	if (angleX <= 50.0f && angleX >= -50.0f) {
		qRot.SetRotationDeg(CVector3::AxisY, rStick.x);
		m_rotation.Multiply(qRot);
		qRot2.Multiply(qRot);
		
	}
	if (angleY <= 50.0f && angleY >= -50.0f) {
		qRot.SetRotationDeg(CVector3::AxisX,rStick.y);
		m_rotation.Multiply(qRot);
		qRot2.Multiply(qRot);
	}
	if (Pad(0).GetRStickXF()) {
		Torokko*toro = FindGO<Torokko>("Trokko");
		m_rotation1 = qRot2;
		fl = 0;
		
	}
	
	float x = Pad(0).GetLStickXF();
	if (Pad(0).GetLStickXF()) {
		Torokko*toro = FindGO<Torokko>("Trokko");
		m_rotation = toro->m_rotation ;
		m_rotation.Multiply(m_rotation1);
	}
	//回転行列の作成
	CMatrix forwardMatrix;
	forwardMatrix.MakeRotationFromQuaternion(qRot);

	//鏡の前方向
	CVector3 target=CVector3::Zero;
	target = { forwardMatrix.m[2][0],forwardMatrix.m[2][1] ,forwardMatrix.m[2][2] };
	
	//カメラ行列の作成
	CMatrix mirrorCamera;
	CVector3 up = { 0.0f,1.0f,0.0f };
	mirrorCamera.MakeLookAt(m_position, target, up);
	//m_position = m_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_moveSpeed);
	m_skinModel.Update(m_position, m_rotation, CVector3::One);
}
void Mirror::Render(CRenderContext& rc)
{
	CMatrix axis = CMatrix::Identity;									//プレイヤーの任意の軸周りの回転行列を作成
	axis.MakeRotationFromQuaternion(m_rotation);

	m_target.x = m_position.x + axis.m[2][0] * 10.0f;		//プレイヤーの注視点を設定
	m_target.y = m_position.y + axis.m[2][1] * 10.0f;
	m_target.z = m_position.z + axis.m[2][2] * 10.0f;
	
	m_position.x = m_position.x - axis.m[2][0] * 20.0f;		//プレイヤーの注視点を設定
	/*m_position.y = m_position.y - axis.m[2][1] * 20.0f;*/
	m_position.z = m_position.z - axis.m[2][2] * 20.0f;
	CVector3 cameraPos = m_position;
	cameraPos.x += axis.m[2][0] * 2.0f;
	cameraPos.y += 50.0f;
	cameraPos.z += axis.m[2][2] * 2.0f;

	m_mirrorViewMatrix.MakeLookAt(m_position, m_target, { 0.0f,1.0f,0.0f });
	m_mirrorProjectionMatrix.MakeProjectionMatrix(CMath::PI * 0.3f, 1.0f, 0.1f, 10000.0f);
	/*if (m_mirror == NULL) {
		m_mirror = FindGO<testMirror>("testMirror");
	}*/
	alphaflag = 1;
	m_skinModel.Draw(rc,
		MainCamera().GetViewMatrix(),
		MainCamera().GetProjectionMatrix(),
		m_mirrorViewMatrix,
		m_mirrorProjectionMatrix,
		alphaflag);
}