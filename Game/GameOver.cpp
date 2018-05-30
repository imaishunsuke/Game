#include "stdafx.h"
#include "GameOver.h"
#include "Title.h"
#include "Fade.h"

GameOver::GameOver()
{
}
GameOver::~GameOver()
{
}
bool GameOver:: Start()
{
	//GameOverテクスチャ
	m_texture.CreateFromDDSTextureFromFile(L"sprite/GameOver.dds");
	m_sprite.Init(m_texture, 1280, 720);
	m_fade = FindGO<Fade>("Fade");
	m_fade->StartFadeIn();
	return true;
}
void GameOver::Update()
{
	if (m_isWaitFadeout) {
		if (!m_fade->IsFade()) {
			NewGO<Title>(0, "Title");
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
void GameOver::PostRender(CRenderContext& rc)
{
		m_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
}