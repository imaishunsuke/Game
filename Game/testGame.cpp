#include "stdafx.h"
#include "testGame.h"
#include "Fade.h"
#include "Title.h"
#include "Mirror.h"
#include "testGameCamera.h"
#include "testBackGround.h"
testGame::testGame()
{
}


testGame::~testGame()
{
}
void testGame::OnDestroy()
{
	DeleteGO(m_gameCamera);
	DeleteGO(m_skinModelRender);
	DeleteGO(m_mirror);
	DeleteGO(m_background);
}
bool testGame::Start()
{
	m_gameCamera = NewGO<testGameCamera>(0);
	m_background = NewGO<testBackGround>(0);
	//カメラを設定。
	//MainCamera().SetTarget({ 0.0f, 10.0f, 0.0f });
	//MainCamera().SetNear(0.1f);
	//MainCamera().SetFar(100.0f);
	//MainCamera().SetPosition({ 30.0f, 10.0f, 0.0f });
	//MainCamera().Update();

	//m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	//m_skinModelRender->Init(L"modelData/unityChan.cmo");
	//m_skinModelRender->SetScale({ 0.1f, 0.1f, 0.1f });
	m_fade = FindGO<Fade>("Fade");
	m_fade->StartFadeIn();
	m_state = enState_FadeIn;
	m_mirror = NewGO<Mirror>(0, "Mirror");
	return true;
}
void testGame::Update()
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
}
void testGame::Render(CRenderContext& rc)
{
	(void)rc;
}