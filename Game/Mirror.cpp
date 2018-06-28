#include "stdafx.h"
#include "Mirror.h"
#include"Player.h"
#include"Goal.h"
#include "tkEngine/sound/tkSoundSource.h"

Mirror::Mirror()
{
}

Mirror::~Mirror()
{
	DeleteGO(m_useMirror);
}
bool Mirror::Start()
{
	pl = FindGO<Player>("Player");

	CVector3 vector =CVector3::Zero;
	m_skinModelData.Load(L"modelData/mirror1.cmo");
	m_skinModel.Init(m_skinModelData);

	m_mtexture.CreateFromDDSTextureFromFile(L"sprite/mirror.dds");
	m_msprite.Init(m_mtexture, 80, 120);

	m_mptexture.CreateFromDDSTextureFromFile(L"sprite/mp.dds");
	m_mpsprite.Init(m_mptexture, 310, 30);
	m_mprotation.SetRotationDeg(CVector3::AxisZ, -90);

	m_mpbtexture.CreateFromDDSTextureFromFile(L"sprite/hpmp_bar.dds");
	m_mpbsprite.Init(m_mpbtexture, 330, 50);

	pl = FindGO<Player>("Player");
	m_goal = FindGO<Goal>("Goal");
	
	diff.x = pl->GetGoalPosition().x - pl->GetPosition().x;
	diff.y = pl->GetGoalPosition().y - pl->GetPosition().y;
	diff.z = pl->GetGoalPosition().z - pl->GetPosition().z;
	Mirlen = diff.Length();
	m_skinModel.Update(m_position, m_rotation, CVector3::One);
	
	m_useMirror = NewGO<prefab::CSoundSource>(0);
	return true;
}

void Mirror::Rotation() {
	m_rotation = pl->GetRotation();
	m_rot.MakeRotationFromQuaternion(pl->GetRotation());
	m_position.x = m_rot.m[2][0] * Mirlen + pl->GetPosition().x;
	m_position.y = m_rot.m[2][1] * Mirlen + pl->GetPosition().y+3.0f;
	m_position.z = m_rot.m[2][2] * Mirlen + pl->GetPosition().z;
}
void Mirror::Update()
{
	Rotation();

	if (Pad(0).IsTrigger(enButtonB) 
		&& m_isMirror == false
		&&mpflag==0
		&&pl->GetLifeCount()<5) {
		m_isMirror = true;
		prefab::CSoundSource* m_useMirror = nullptr;
		m_useMirror = NewGO<prefab::CSoundSource>(0);
		m_useMirror->Init("sound/mirroruse1.wav");
		m_useMirror->SetVolume(2.0f);
		m_useMirror->Play(false);
	}
	else if(Pad(0).IsTrigger(enButtonB) && m_isMirror == true){
		m_isMirror = false;
	}
	//スティックの入力
	CVector3 rStick = CVector3::Zero;
	rStick.x = Pad(0).GetRStickXF();
	rStick.y = -Pad(0).GetRStickYF();
	rStick.z = 0.0f;
	rStick = rStick * 5;

	//ミラーが使用中なら更新する
	if (m_isMirror == true) {
		m_skinModel.Update(m_position, m_rotation, CVector3::One);
	}
	//ミラーが使用中の時ｍｐゲージを下げる
	if (m_isMirror == true
		&&pl->GetFlag()==1
		&& mpflag == 0) {
		mpscale -= GameTime().GetFrameDeltaTime()*0.17;
	}

	if (mpscale <= 0) {
		mpscale = 0;
		mpflag = 1;
		m_isMirror = false;
	}
	if (mpflag==1)
	{
		if (pl->GetProdCount() == 0) {
			mpscale += GameTime().GetFrameDeltaTime()*0.5;
			if (mpscale >= 1) {
				mpscale = 1;
				mpflag = 0;
			}
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

	m_target.x = m_position.x + axis.m[2][0] * 20.0f;		//プレイヤーの注視点を設定
	m_target.y = m_position.y + axis.m[2][1] * 20.0f;
	m_target.z = m_position.z + axis.m[2][2] * 20.0f;
	
	m_position.x = m_position.x - axis.m[2][0] * 10.0f;		//プレイヤーの視点を設定
	m_position.z = m_position.z - axis.m[2][2] * 10.0f;
	CVector3 cameraPos = m_position;
	cameraPos.x += axis.m[2][0] * 2.0f;
	cameraPos.y += 50.0f;
	cameraPos.z += axis.m[2][2] * 2.0f;

	m_mirrorViewMatrix.MakeLookAt(m_position, m_target, { 0.0f,1.0f,0.0f });
	static float aspect = 0.6f;
	m_mirrorProjectionMatrix.MakeProjectionMatrix(CMath::PI * 0.3f, aspect, 5.0f, 10000.0f);
	if (m_isMirror == true) {
		m_skinModel.Draw(rc,
			MainCamera().GetViewMatrix(),
			MainCamera().GetProjectionMatrix(),
			m_mirrorViewMatrix,
			m_mirrorProjectionMatrix);
	}
}

void Mirror::PostRender(CRenderContext& rc) {
	
	if (m_goal->GetGoalFlag() == 0) {
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