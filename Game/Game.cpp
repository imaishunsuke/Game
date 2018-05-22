#include "stdafx.h"
#include "Game.h"
#include "Fade.h"
#include "Title.h"
#include "Level.h"
#include "background.h"
#include "Goal.h"
#include "Player.h"
#include "Torokko.h"
#include "GameCamera.h"
#include "Mirror.h"
#include "ResultScene.h"
#include "GameOver.h"
#include "EnemyBall.h"
#include "LightLevel.h"
#include "tkEngine/light/tkDirectionLight.h"

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
	/*DeleteGO(m_torokko);*/
	DeleteGO(m_gamecamera);
	DeleteGO(m_mirror);
	DeleteGO(m_goal);
	DeleteGO(m_result);
	DeleteGO(m_enemyball);
}
bool Game::Start()
{
	prefab::CDirectionLight* dirLight;
	dirLight = NewGO<prefab::CDirectionLight>(0);
	//ライトの方向を設定
	dirLight->SetDirection({ 0.707f,-0.707f,0.0f });
	//ライトの色を設定
	dirLight->SetColor({ 5.0f,5.0f,5.0f,0.0f });
	LightManager().SetAmbientLight({ 0.2f, 0.2f, 0.2f });
	GraphicsEngine().GetShadowMap().SetLightDirection({ 0.0,-1.0f,0.0f });
	//m_directionLightList.push_back(dirLight);
	//background作成
	m_background=NewGO<background>(0, "background");
	//EnemyBall作成
	m_enemyball = NewGO<EnemyBall>(0, "EnemyBall");
	//リザルト画面作成
	m_result = NewGO<ResultScene>(0, "Result");
	//トロッコ作成
	//m_torokko = NewGO<Torokko>(0, "Trokko");
	//プレイヤー作成
	m_player=NewGO<Player>(0,"Player");
	//カメラ作成
	m_gamecamera = NewGO<GameCamera>(0, "gamecamera");
	//ゴール作成
	m_goal = NewGO<Goal>(0, "Goal");
	
	//ミラー作成
	m_mirror = NewGO<Mirror>(0, "Mirror");
	
	m_fade = FindGO<Fade>("Fade");
	m_fade->StartFadeIn();
	m_state = enState_FadeIn;
	//m_toro = FindGO<Torokko>("Trokko");
	m_pl = FindGO<Player>("Player");
	//レベルを構築する。

	m_ptLight.ptLightBuild(L"light/ptlig_[00]_[255]_[255]_[255]_[40].tks");
	//m_dirLight.dirLightBuild(L"light/dlig_00.tks");

	m_level.Build(L"level/Block_1x2_001.tks");
	m_level.Build(L"level/Block_1x2_002.tks");
	m_level.Build(L"level/Block_1x2_003.tks");
	m_level.Build(L"level/Block_1x2_004.tks");
	//m_level.Build(L"level/plane1.tks");
	//m_ptLight.LightBuild(L"light/ptlig_[00]_[255]_[255]_[255]_[40].tks");

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
	if (m_isWaitFadeout && GameOverFlag == 1)
	{
		if (!m_fade->IsFade()) {
			NewGO<GameOver>(0, nullptr);
			DeleteGO(this);
		}
	}
	else {
		if (m_pl->lifecount == 5) {
			m_isWaitFadeout = true;
			m_fade->StartFadeOut();
			GameOverFlag = 1;
		}
	}
	
	if (m_isWaitFadeout && GameOverFlag == 0)
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
	
}
void Game::Render(CRenderContext& rc)
{
	(void)rc;
}