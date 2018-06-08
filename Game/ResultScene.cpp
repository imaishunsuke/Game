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
}
bool ResultScene::Start()
{		
	/*m_player = NewGO<ResultPlayer>(0,"ResultPlayer");
	m_camera = NewGO<ResultCamera>(0, "ResultCamera");*/
	m_texture.CreateFromDDSTextureFromFile(L"sprite/Title.dds");
	m_sprite.Init(m_texture, 1280, 720);

	//m_position = { 0.0f,0.0f,100.0f };
	m_goal = FindGO<Goal>("Goal");
	//m_mirror = NewGO<Mirror>(0, "Mirror");
	m_fade = FindGO<Fade>("Fade");
	m_fade->StartFadeIn();
	
	return true;
}
void ResultScene::Update()
{
	MainCamera().Update();
	//m_sprite.Update(m_position, m_rotation, CVector3::One);
}
void ResultScene::Render(CRenderContext& rc)
{
	if (m_goal->GetGoalFlag() == 1) {
		//2DÇÃê[ìxÇê›íËÇ∑ÇÈ
		rc.OMSetDepthStencilState(DepthStencilState::spriteRender, 0);
		m_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
		//å≥Ç…ñﬂÇ∑
		rc.OMSetDepthStencilState(DepthStencilState::SceneRender, 0);
	}
}