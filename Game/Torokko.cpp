#include "stdafx.h"
#include "Torokko.h"
#include "Player.h"


Torokko::Torokko()
{
}


Torokko::~Torokko()
{
}

bool Torokko::Start() {
	//モデルデータのロード
	m_skinModelData.Load(L"modelData/prottro.cmo");
	m_skinModel.Init(m_skinModelData);
	m_rotation.Multiply(m_rotation);
	m_position = { 0.0, 0.0, 0.0 };
	m_gpos = { 0.0,0.0,5.0 };
	m_skinModel.Update(m_position, m_rotation, CVector3::One);
	
	count = 0;
	flag = 0;
	scale = 3.0f;
	m_charaCon.Init(
		9.5,		//半径
		1.0f,		//高さ
		m_position	//初期位置
	);
	
	return true;
}

void Torokko::Move() {
	if (flag == 1) {
		x=Pad(0).GetLStickXF();
	if (x<1)
		{
		//スタートの加速
		if (MoveFlag == 0) {
			m_rot.MakeRotationFromQuaternion(m_rotation);
			m_moveSpeed.x += m_rot.m[2][0] * 1;
			m_moveSpeed.y = m_rot.m[2][1];
			m_moveSpeed.z += m_rot.m[2][2] * 1;
		}
		if (MoveFlag==0
			&&m_moveSpeed.x >= 19.0 
			|| m_moveSpeed.z >= 19.0)
		{
			MoveFlag = 1;
		}
		if (MoveFlag == 1) {
			m_rot.MakeRotationFromQuaternion(m_rotation);
			m_moveSpeed.x = m_rot.m[2][0] * 20;
			m_moveSpeed.y = m_rot.m[2][1];
			m_moveSpeed.z = m_rot.m[2][2] * 20;
		}
	}
		//移動速度最大値
		if (m_moveSpeed.z >= 20.0) {
			
			m_moveSpeed.z = 20.0;
		}
		if (m_moveSpeed.x >= 20.0)
		{
			m_moveSpeed.x = 20.0;
		}
		if (m_moveSpeed.z <= -20.0)
		{
			m_moveSpeed.z = -20.0;
		}
		if (m_moveSpeed.x <= -20.0) {
			m_moveSpeed.x = -20.0;
		}
	if (x >= 1) {
		m_moveSpeed.x = m_rot.m[2][0]* 15;
		m_moveSpeed.y = m_rot.m[2][1];
		m_moveSpeed.z = m_rot.m[2][2] * 15;
	}
		m_position = m_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_moveSpeed);
	}
}

void Torokko::Update()
{
	if (flag==1) {
		Move();
	}
	float x = Pad(0).GetLStickXF();
	if (Pad(0).GetLStickXF()) {
		qRot.SetRotationDeg(CVector3::AxisY, 5.0f*x);
		m_rotation.Multiply(qRot);
	}
	m_skinModel.Update(m_position, m_rotation, CVector3::One);

}

void Torokko::Render(CRenderContext& rc)
{
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
}
void Torokko::PostRender(CRenderContext& rc) {
	if (flag == 0&&count==0)
	{
		m_font.Begin(rc);
		m_font.Draw(L"PRESS ANY KEY", { 640.0f, -270.0f }, { 234.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 255.0f }, 0.0f, 1.5f);
		m_font.End(rc);
	}
	else if(flag==0)
	{
		count = count + GameTime().GetFrameDeltaTime();
		if (count>=0&&count<=1)
		{
			if (scalefg == 0) {
				scale = 3;
				scalefg = 1;
			}
			m_font.Begin(rc);
			m_font.Draw(L"3", { 640.0f, -270.0f }, { 234.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 255.0f }, 0.0f, scale);
			m_font.End(rc);
			scale=scale-count*0.2;
		}
		if (count > 1 && count<=2)
		{
			if (scalefg == 1) {
				scale = 3;
				scalefg = 0;
			}
			m_font.Begin(rc);
			m_font.Draw(L"2", { 640.0f, -270.0f }, { 234.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 255.0f }, 0.0f, scale);
			m_font.End(rc);
			scale = scale - (count-1)*0.2;
		}
		if (count > 2 && count<=3)
		{
			if (scalefg == 0) {
				scale = 3;
				scalefg = 1;
			}
			m_font.Begin(rc);
			m_font.Draw(L"1", { 640.0f, -270.0f }, { 234.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 255.0f }, 0.0f, scale);
			m_font.End(rc);
			scale = scale - (count-2)*0.2;
		}
		if (count >3 && count <= 3.3)
		{
			if (scalefg == 1) {
				scale = 1;
				scalefg = 0;
			}
			m_font.Begin(rc);
			m_font.Draw(L"GO!", { 640.0f, -270.0f }, { 234.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 255.0f }, 0.0f, scale);
			m_font.End(rc);
			scale = scale + (count - 3)*3;
		}
		if (count>3.3)
		{
			flag = 1;
		}
	}
	 if (Pad(0).IsPressAnyKey()) {

		count = count+GameTime().GetFrameDeltaTime();
	}
}