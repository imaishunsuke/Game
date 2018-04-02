#include "stdafx.h"
#include "Game.h"
#include "Fade.h"
#include "Title.h"
#include"Level.h"
#include"background.h"
#include"Player.h"
#include"Torokko.h"
#include"GameCamera.h"
//#include "Mirror.h"


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
	DeleteGO(m_player);
	DeleteGO(m_torokko);
	DeleteGO(m_gamecamera);
}
bool Game::Start()
{
	
	//トロッコ作成
	m_torokko = NewGO<Torokko>(0, "Trokko");
	//プレイヤー作成
	m_player=NewGO<Player>(0,"Player");
	//カメラ作成
	m_gamecamera = NewGO<GameCamera>(0, "gamecamera");
	m_fade = FindGO<Fade>("Fade");
	m_fade->StartFadeIn();
	m_state = enState_FadeIn;
	//background作成
	m_background=NewGO<background>(0, "background");
	//レベルを構築する。
	m_level.Build(L"level/protobj1.tks");
	m_level.Build(L"level/protobj2.tks");
	m_level.Build(L"level/protobj3.tks");
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
	//if (Pad(0).IsPress(enButtonUp)) {
	//	m_position += {0.0,1.0,0.0};
	//}
	//if (Pad(0).IsPress(enButtonDown)) {
	//	m_position -= {0.0, 1.0, 0.0};
	//}
	//MainCamera().SetPosition(m_position);
	//MainCamera().Update();
}
void Game::Render(CRenderContext& rc)
{
	(void)rc;
}