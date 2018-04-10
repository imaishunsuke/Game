#include "stdafx.h"
#include "ResultScene.h"


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

	return true;
}
void ResultScene::Update()
{

}
void ResultScene::PostRender(CRenderContext& rc)
{
	m_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
}