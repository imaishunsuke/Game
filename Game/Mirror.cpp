#include "stdafx.h"
#include "Mirror.h"
#include "Torokko.h"


Mirror::Mirror()
{
}

Mirror::~Mirror()
{
}
bool Mirror::Start()
{
	CVector3 vector =CVector3::Zero;
	m_skinModelData.Load(L"modelData/mirror.cmo");
	m_skinModel.Init(m_skinModelData);
	
	return true;
}
void Mirror::Update()
{

	Torokko*toro = FindGO<Torokko>("Trokko");
	//スティックの入力
	CVector3 rStick = CVector3::Zero;
	rStick.x = Pad(0).GetRStickXF();
	rStick.y = -Pad(0).GetRStickYF();
	rStick.z = 0.0f;
	rStick = rStick * 5;
	
	CMatrix miraxis = CMatrix::Identity;									//プレイヤーの任意の軸周りの回転行列を作成
	miraxis.MakeRotationFromQuaternion(m_rotation);

	

	CQuaternion qRot = CQuaternion::Identity;
	
	//鏡の回転行列
	CMatrix mirroraxis = CMatrix::Identity;							
	mirroraxis.MakeRotationFromQuaternion(m_rotation);

	CVector3 mirrorfront = CVector3::Zero;

	//Xの範囲

	//鏡の前方向
	mirrorfront.x = mirroraxis.m[2][0];		
	mirrorfront.y = 0.0f;
	mirrorfront.z = mirroraxis.m[2][2];
	mirrorfront.Normalize();
	//トロッコの前方向
	CVector3 torokkofront = CVector3::Zero;
	torokkofront.x = toro->m_rot.m[2][0];
	torokkofront.y = 0.0f;
	torokkofront.z = toro->m_rot.m[2][2];
	torokkofront.Normalize();
	float anglex = 0.0f;
	anglex = acosf(torokkofront.Dot(mirrorfront));
	anglex = 180 / 3.14159 * anglex;
	if (anglex > -90 && anglex < 90)
	{
		//加算
		qRot.SetRotationDeg(CVector3::AxisY, rStick.x);
		m_rotation.Multiply(qRot);
	}
	//Xの範囲

	//鏡の前方向
	mirrorfront.x = mirroraxis.m[2][0];
	mirrorfront.y = mirroraxis.m[2][1];
	mirrorfront.z = 0.0f;
	mirrorfront.Normalize();
	//トロッコの前方向
	torokkofront.x = toro->m_rot.m[2][0];
	torokkofront.y = toro->m_rot.m[2][1];
	torokkofront.z = 0.0f;
	torokkofront.Normalize();
	float angley = 0.0f;
	angley = acosf(torokkofront.Dot(mirrorfront));
	angley = 180 / 3.14159 * angley;
	if (angley > -45 && angley < 45)
	{
		//加算
		qRot.SetRotationDeg(CVector3::AxisX, rStick.y);
		m_rotation.Multiply(qRot);
	}


	m_skinModel.Update(m_position, m_rotation, CVector3::One);
}
void Mirror::Render(CRenderContext& rc)
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