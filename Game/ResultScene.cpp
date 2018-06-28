#include "stdafx.h"
#include "ResultScene.h"
#include "Goal.h"
#include "Fade.h"
#include "Title.h"
#include "Mirror.h"
#include "tkEngine/graphics/tkPresetRenderState.h"


ResultScene::ResultScene()
{
}


ResultScene::~ResultScene()
{
}
void ResultScene::OnDestroy()
{
	//DeleteGO(m_player);
	//DeleteGO(m_camera);
	//DeleteGO(m_mirror);
	DeleteGO(m_ptLight);
}
bool ResultScene::Start()
{		
	/*m_player = NewGO<ResultPlayer>(0,"ResultPlayer");
	m_camera = NewGO<ResultCamera>(0, "ResultCamera");*/
	m_texture.CreateFromDDSTextureFromFile(L"sprite/Clear.dds");
	m_sprite.Init(m_texture, 1280, 720);

	//m_position = { 0.0f,0.0f,100.0f };
	m_goal = FindGO<Goal>("Goal");
	m_player = FindGO<Player>("Player");
	//m_mirror = NewGO<Mirror>(0, "Mirror");
	m_fade = FindGO<Fade>("Fade");
	m_fade->StartFadeIn();
	
	return true;
}
void ResultScene::Update()
{
	/*if (Pad(0).IsTrigger(enButtonLB1))
	{
		ResultFlag = true;
	}*/
	//ResultFlagはゴールフラグに変える

	//if (ResultFlag == true)
	if(m_goal->GetGoalFlag())
	{
		if (m_ptLight == nullptr) {
			m_ptLight = NewGO<prefab::CPointLight>(0);
		}
		CVector3 Pos = CVector3::Zero;
		Pos.x = m_player->GetMatrix().m[2][0] * 5.0f + m_player->GetPosition().x;
		Pos.y = 7.0f;
		Pos.z = m_player->GetMatrix().m[2][2] * 5.0f + m_player->GetPosition().z;
		m_ptLight->SetPosition(Pos);

		if (colorTime <= 2.0f) {
			colorTime += GameTime().GetFrameDeltaTime();
			coloradd += 0.01;
		}
		m_ptLight->SetColor({ coloradd,coloradd,coloradd,1.0f });

		m_ptLight->SetAttn({ 40.0f,0.0f,1.0f });
		////ポイントライトの座標を指定
		//m_ptLight->SetPosition(;
		////ライトのカラーを設定
		//m_ptLight->SetColor(color);
		////ポイントライトの減衰パラメータを設定
		//CVector3 attn = CVector3::Zero;
		//attn.x = distancedecay;
		//attn.y = 1.0f;
		//ptLight->SetAttn(attn);
	}
	MainCamera().Update();
	//m_sprite.Update(m_position, m_rotation, CVector3::One);
}
void ResultScene::PostRender(CRenderContext& rc)
{
	//if (ResultFlag == true) {
		if (m_goal->GetGoalFlag() == 1) {
			//2Dの深度を設定する
		//rc.OMSetDepthStencilState(DepthStencilState::spriteRender, 0);
		m_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
		//元に戻す
		//rc.OMSetDepthStencilState(DepthStencilState::SceneRender, 0);
	}
	//}
}