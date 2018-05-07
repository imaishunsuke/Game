#include "stdafx.h"
#include "Torokko.h"
#include "Player.h"
#include "Mirror.h"
#include"Goal.h"

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
	m_skinModelData1.Load(L"modelData/prottro1.cmo");
	m_skinModel1.Init(m_skinModelData1);
	m_skinModelData2.Load(L"modelData/prottro2.cmo");
	m_skinModel2.Init(m_skinModelData2);
	m_skinModelData3.Load(L"modelData/prottro3.cmo");
	m_skinModel3.Init(m_skinModelData3);
	m_skinModelData4.Load(L"modelData/prottro4.cmo");
	m_skinModel4.Init(m_skinModelData4);

	m_rotation.Multiply(m_rotation);
	m_position = { 0.0, 0.0, 0.0 };
	m_gpos = { 0.0,0.0,5.0 };
	m_skinModel.Update(m_position, m_rotation, CVector3::One);
	
	count = 0;
	flag = 0;
	scale = 3.0f;
	m_charaCon.Init(
		3.0,		//半径
		1.0f,		//高さ
		m_position,	//初期位置
		m_collidertype
	);
	m_mirror = FindGO<Mirror>("Mirror");
	m_player = FindGO<Player>("Player");
	m_goal = FindGO<Goal>("Goal");
	return true;
}

void Torokko::Move() {
	m_rot.MakeRotationFromQuaternion(m_rotation);
	if (flag == 1) {
		x=Pad(0).GetLStickXF();
	if (x<1)
		{
		//スタートの加速
		if (MoveFlag == 0) {
			
			m_moveSpeed.x += m_rot.m[2][0] * 1;
			m_moveSpeed.y = m_rot.m[2][1];
			m_moveSpeed.z += m_rot.m[2][2] * 1;
		}
		if (MoveFlag==0
			&&m_moveSpeed.x >= 49.0 
			|| m_moveSpeed.z >= 49.0)
		{
			MoveFlag = 1;
		}
		if (MoveFlag == 1) {
			m_moveSpeed.x = m_rot.m[2][0] * 50;
			m_moveSpeed.y = m_rot.m[2][1];
			m_moveSpeed.z = m_rot.m[2][2] * 50;
		}
	}
		//移動速度最大値
		if (m_moveSpeed.z >= 50.0) {
			
			m_moveSpeed.z = 50.0;
		}
		if (m_moveSpeed.x >= 20.0)
		{
			m_moveSpeed.x = 50.0;
		}
		if (m_moveSpeed.z <= -50.0)
		{
			m_moveSpeed.z = -50.0;
		}
		if (m_moveSpeed.x <= -50.0) {
			m_moveSpeed.x = -50.0;
		}
	if (x >= 1) {
		m_moveSpeed.x = m_rot.m[2][0]* 15;
		m_moveSpeed.y = m_rot.m[2][1];
		m_moveSpeed.z = m_rot.m[2][2] * 15;
	}
	m_position = m_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_moveSpeed,m_collidertype);
	}
}

void Torokko::Update()
{
	if (dameflag == 1) {
		if (nlcount<=0) {	
			nlcount = 0.01;
		}
		//lifecountが5になったらゲームオーバー
		if ((lifecount == 0 && m_player->hpscale <= 0.8)
			||(lifecount == 1 && m_player->hpscale <= 0.6)
			|| (lifecount == 2 && m_player->hpscale <= 0.4)
			|| (lifecount == 3 && m_player->hpscale <= 0.2)
			|| (lifecount == 4 && m_player->hpscale <= 0.0))
		{
			lifecount = lifecount + 1;
		}
		dameflag = 0;
	}
	//２秒間無敵
	if (nlcount > 0) {
		nlcount = nlcount + GameTime().GetFrameDeltaTime();
		if (2 <= nlcount) {
			nlcount = 0;
			dameflag = 0;
		}
	}
	if (flag==1) {
		Move();
	}
	float x = Pad(0).GetLStickXF();
	if (m_goal->gflag == 0) {

		if (Pad(0).GetLStickXF()) {
			qRot.SetRotationDeg(CVector3::AxisY, 5.0f*x);
			m_rotation.Multiply(qRot);
		}
	}
	m_position.y = 0;
	if (lifecount == 0) {
		m_skinModel.Update(m_position, m_rotation, CVector3::One);
	}
	if (lifecount == 1) {
		m_skinModel1.Update(m_position, m_rotation, CVector3::One);
	}
	if (lifecount == 2) {
		m_skinModel2.Update(m_position, m_rotation, CVector3::One);
	}
	if (lifecount == 3) {
		m_skinModel3.Update(m_position, m_rotation, CVector3::One);
	}
	if (lifecount == 4) {
		m_skinModel4.Update(m_position, m_rotation, CVector3::One);
	}
}

void Torokko::Render(CRenderContext& rc)
{
	if (m_mirror == NULL) {
	}
	m_mirror->alphaflag = 0;
	if (lifecount == 0) {
		m_skinModel.Draw(rc,
			MainCamera().GetViewMatrix(),
			MainCamera().GetProjectionMatrix(),
			CMatrix::Identity,
			CMatrix::Identity,
			m_mirror->alphaflag);
	}
	if (lifecount == 1) {
		m_skinModel1.Draw(rc,
			MainCamera().GetViewMatrix(),
			MainCamera().GetProjectionMatrix(),
			CMatrix::Identity,
			CMatrix::Identity,
			m_mirror->alphaflag);
	}
	if (lifecount == 2) {
		m_skinModel2.Draw(rc,
			MainCamera().GetViewMatrix(),
			MainCamera().GetProjectionMatrix(),
			CMatrix::Identity,
			CMatrix::Identity,
			m_mirror->alphaflag);
	}
	if (lifecount == 3) {
		m_skinModel3.Draw(rc,
			MainCamera().GetViewMatrix(),
			MainCamera().GetProjectionMatrix(),
			CMatrix::Identity,
			CMatrix::Identity,
			m_mirror->alphaflag);
	}
	if (lifecount == 4) {
		m_skinModel4.Draw(rc,
			MainCamera().GetViewMatrix(),
			MainCamera().GetProjectionMatrix(),
			CMatrix::Identity,
			CMatrix::Identity,
			m_mirror->alphaflag);
	}
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