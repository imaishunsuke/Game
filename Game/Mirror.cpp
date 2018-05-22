#include "stdafx.h"
#include "Mirror.h"
#include"Player.h"
#include"Goal.h"

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

	m_mtexture.CreateFromDDSTextureFromFile(L"sprite/mirror.dds");
	m_msprite.Init(m_mtexture, 80, 120);

	m_mptexture.CreateFromDDSTextureFromFile(L"sprite/mp.dds");
	m_mpsprite.Init(m_mptexture, 310, 30);
	m_mprotation.SetRotationDeg(CVector3::AxisZ, -90);

	m_mpbtexture.CreateFromDDSTextureFromFile(L"sprite/hpmp_bar.dds");
	m_mpbsprite.Init(m_mpbtexture, 330, 50);
	
	
	
	/*m_charaCon.Init(
		6.0f,
		3.0f,
		m_position
	);*/

	pl = FindGO<Player>("Player");
	m_goal = FindGO<Goal>("Goal");
	m_position = pl->m_position;
	diff.x = pl->m_gpos.x - pl->m_position.x;
	diff.y = pl->m_gpos.y - pl->m_position.y;
	diff.z = pl->m_gpos.z - pl->m_position.z;
	Mirlen = diff.Length();
	m_skinModel.Update(m_position, m_rotation, CVector3::One);
	
	
	
	return true;
}

void Mirror::Rotation() {
	m_rot.MakeRotationFromQuaternion(pl->m_rotation);
	m_position.x = m_rot.m[2][0] * Mirlen + pl->m_position.x;
	m_position.y = m_rot.m[2][1] * Mirlen + pl->m_position.y;
	m_position.z = m_rot.m[2][2] * Mirlen + pl->m_position.z;

}
void Mirror::Update()
{
	Rotation();

	if (Pad(0).IsTrigger(enButtonB) && m_isMirror == false&&mpflag==0) {
		m_isMirror = true;
	}
	else if(Pad(0).IsTrigger(enButtonB) && m_isMirror == true){
		m_isMirror = false;
	}
	////スティックの入力
	//CVector3 rStick = CVector3::Zero;
	//rStick.x = Pad(0).GetRStickXF();
	//rStick.y = -Pad(0).GetRStickYF();
	//rStick.z = 0.0f;
	//rStick = rStick * 5;

	//qRot = CQuaternion::Identity;
	//qRot.SetRotationDeg(CVector3::AxisY, rStick.x);
	//m_rotation.Multiply(qRot);
	//qRot2.Multiply(qRot);
	//CMatrix miraxis = CMatrix::Identity;									//プレイヤーの任意の軸周りの回転行列を作成
	//miraxis.MakeRotationFromQuaternion(m_rotation);
	////鏡の回転行列
	//CMatrix mirroraxis = CMatrix::Identity;							
	//mirroraxis.MakeRotationFromQuaternion(m_rotation);

	//CVector3 mirrorfront = CVector3::Zero;

	////Xの範囲
	//m_rot.MakeRotationFromQuaternion(toro->m_rotation);
	////鏡の前方向
	//mirrorfront.x = mirroraxis.m[2][0];		
	//mirrorfront.y = 0.0f;
	//mirrorfront.z = mirroraxis.m[2][2];
	//mirrorfront.Normalize();
	////トロッコの前方向
	//CVector3 torokkofront = CVector3::Zero;
	//torokkofront.x = m_rot.m[2][0];
	//torokkofront.y = 0.0f;
	//torokkofront.z = m_rot.m[2][2];
	//torokkofront.Normalize();
	//float anglex = 0.0f;
	//anglex = acosf(torokkofront.Dot(mirrorfront));
	//anglex = 180 / 3.14159 * anglex;


	////Yの範囲
	//if (70<=anglex&& rStick.x != 0)
	//{
	//	qRot = CQuaternion::Identity;
	//	if (rStick.x>0)
	//	qRot.SetRotationDeg(CVector3::AxisY,70.0f);
	//	else
	//		qRot.SetRotationDeg(CVector3::AxisY, -70.0f);
	//	m_rotation=qRot;
	//	qRot2.Multiply(qRot);
	//}
	////鏡の前方向
	//mirrorfront.x = mirroraxis.m[2][0];
	//mirrorfront.y = mirroraxis.m[2][1];
	//mirrorfront.z = 0.0f;
	//mirrorfront.Normalize();
	////トロッコの前方向
	//torokkofront.x = m_rot.m[2][0];
	//torokkofront.y = m_rot.m[2][1];
	//torokkofront.z = 0.0f;
	//torokkofront.Normalize();
	//float angley = 0.0f;
	//angley = acosf(torokkofront.Dot(mirrorfront));
	//angley = 180 / 3.14159 * angley;
	//if (angley < -45) {
	//	rStick.y = 0.0f;
	//	angley = -45;
	//}
	//if (angley > 45) {
	//	rStick.y = 0.0f;
	//	angley = 45;
	//}
	//if (angley >= -45 && angley <= 45)
	//{
	//	//加算
	//	qRot.SetRotationDeg(CVector3::AxisX, rStick.y);
	//	m_rotation.Multiply(qRot);
	//	qRot2.Multiply(qRot);
	//}
	//if (Pad(0).GetRStickXF()) {
	//	m_rotation1 = qRot2;
	//	fl = 0;
	//	
	//}
	
	float x = Pad(0).GetLStickXF();
	if (Pad(0).GetLStickXF()) {
		m_rotation = pl->m_rotation ;
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
	if (m_isMirror == true) {

		m_skinModel.Update(m_position, m_rotation, CVector3::One);
	}
	if (m_isMirror == true&&pl->flag==1&& mpflag == 0) {
		mpscale -= GameTime().GetFrameDeltaTime()*0.5;
	}

	if (mpscale <= 0) {
		mpscale = 0;
		mpflag = 1;
		m_isMirror = false;
	}
	if (mpflag==1)
	{
		mpscale += GameTime().GetFrameDeltaTime()*0.5;
		if (mpscale >= 1) {
			mpscale = 1;
			mpflag = 0;
		}
	}
	m_msprite.Update({640.0,100.0,0.0 }, CQuaternion::Identity, CVector3{ 1.0,1.0,1.0 }, { 1.0,1.0 });
	m_mpsprite.Update({ 615.0,-350.0,0.0 }, m_mprotation, CVector3{ mpscale,1.0,1.0 }, { 1.0,1.0 });
	m_mpbsprite.Update({ 625.0,-360.0,0.0 }, m_mprotation, CVector3{ 1.0,1.0,1.0 }, { 1.0,1.0 });
}
void Mirror::Render(CRenderContext& rc)
{
	CMatrix axis = CMatrix::Identity;						//プレイヤーの任意の軸周りの回転行列を作成
	axis.MakeRotationFromQuaternion(m_rotation);

	m_target.x = m_position.x + axis.m[2][0] * 10.0f;		//プレイヤーの注視点を設定
	m_target.y = m_position.y + axis.m[2][1] * 10.0f;
	m_target.z = m_position.z + axis.m[2][2] * 10.0f;
	
	m_position.x = m_position.x - axis.m[2][0] * 20.0f;		//プレイヤーの注視点を設定
	m_position.z = m_position.z - axis.m[2][2] * 20.0f;
	CVector3 cameraPos = m_position;
	cameraPos.x += axis.m[2][0] * 2.0f;
	cameraPos.y += 50.0f;
	cameraPos.z += axis.m[2][2] * 2.0f;

	m_mirrorViewMatrix.MakeLookAt(m_position, m_target, { 0.0f,1.0f,0.0f });
	m_mirrorProjectionMatrix.MakeProjectionMatrix(CMath::PI * 0.3f, 1.0f, 0.1f, 10000.0f);
	if (m_isMirror == true) {
		m_skinModel.Draw(rc,
			MainCamera().GetViewMatrix(),
			MainCamera().GetProjectionMatrix(),
			m_mirrorViewMatrix,
			m_mirrorProjectionMatrix);
	}
}

void Mirror::PostRender(CRenderContext& rc) {
	if (m_goal->gflag == 0) {
		m_msprite.Draw(rc,
			MainCamera2D().GetViewMatrix(),
			MainCamera2D().GetProjectionMatrix());
		m_mpbsprite.Draw(rc,
			MainCamera2D().GetViewMatrix(),
			MainCamera2D().GetProjectionMatrix());
		m_mpsprite.Draw(rc,
			MainCamera2D().GetViewMatrix(),
			MainCamera2D().GetProjectionMatrix());
	}
}