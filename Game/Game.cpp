#include "stdafx.h"
#include "Game.h"
#include "Fade.h"
#include "Title.h"
#include"Level.h"
#include"background.h"
#include "Mirror.h"


Game::Game()
{
}


Game::~Game()
{
}
void Game::OnDestroy()
{
	DeleteGO(m_skinModelRender);
	DeleteGO(m_background);
	DeleteGO(m_mirror);
}
bool Game::Start()
{
	//カメラを設定。
	MainCamera().SetTarget({ 0.0f, 10.0f, 0.0f });
	MainCamera().SetNear(0.1f);
	MainCamera().SetFar(1000.0f);
	MainCamera().SetPosition({ 30.0f, 10.0f, 0.0f });
	MainCamera().Update();

	/*m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/unityChan.cmo");
	m_skinModelRender->SetScale({ 0.1f, 0.1f, 0.1f });*/
	m_fade = FindGO<Fade>("Fade");
	m_fade->StartFadeIn();
	m_state = enState_FadeIn;
	//background作成
	m_background=NewGO<background>(0, "background");
	//レベルを構築する。
	m_level.Build(L"level/protobj1.tks");
	m_level.Build(L"level/protobj2.tks");
	m_level.Build(L"level/protobj3.tks");
	//ミラー作成
	m_mirror = NewGO<Mirror>(0, "Mirror");
	return true;
}
void Game::Update()
{
	switch (m_state) {
	case enState_FadeIn:
		GraphicsEngine().GetTonemap().Reset();
		if (!m_fade->IsFade()) {
			m_state = enState_InGame;
		}
		break;
	case enState_InGame: {
		m_waitTimer += GameTime().GetFrameDeltaTime();
		if (m_waitTimer < 0.1f) {
			//ゲームが開始して0.1秒経過するまでトーンマップの明暗順応はしない
			GraphicsEngine().GetTonemap().Reset();
		}
	}
		 break;
	}
	if (m_isWaitFadeout)
	{
		if (!m_fade->IsFade()) {
			NewGO<Title>(0, nullptr);
			DeleteGO(this);
		}
	}
	else {
		if (Pad(0).IsTrigger(enButtonStart)) {
			m_isWaitFadeout = true;
			m_fade->StartFadeOut();
		}
	}
	if (Pad(0).IsPress(enButtonUp)) {
		m_position += {0.0,1.0,0.0};
	}
	MainCamera().SetPosition(m_position);
	MainCamera().Update();
}
void Game::Render(CRenderContext& rc)
{
	(void)rc;
}