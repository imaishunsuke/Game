#include "stdafx.h"
#include "ResultScene.h"
#include "Goal.h"
#include "tkEngine/graphics/tkPresetRenderState.h"

ResultScene::ResultScene()
{
}


ResultScene::~ResultScene()
{
}
bool ResultScene::Start()
{
	m_texture.CreateFromDDSTextureFromFile(L"sprite/Result.dds");
	m_sprite.Init(m_texture, 1280, 720);
	//m_position = { 0.0f,0.0f,100.0f };
	m_goal = FindGO<Goal>("Goal");
	return true;
}
void ResultScene::Update()
{
	m_sprite.Update(m_position, m_rotation, CVector3::One);
}
void ResultScene::Render(CRenderContext& rc)
{
	//2D‚Ì[“x‚ðÝ’è‚·‚é
	rc.OMSetDepthStencilState(DepthStencilState::spriteRender, 0);
	if (m_goal->gflag == 1) {
		m_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
	}
	//Œ³‚É–ß‚·
	rc.OMSetDepthStencilState(DepthStencilState::SceneRender, 0);
}