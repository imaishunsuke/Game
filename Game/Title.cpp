#include "stdafx.h"
#include "Title.h"
#include "Fade.h"
#include "Game.h"
#include "testGame.h"
//#include"tkEngine/graphics/tkPresetRenderState.h"
#include "titletorokko.h"
#include "titlecamera.h"
#include "TitleGame.h"

Title::Title()
{
}


Title::~Title()
{
}
void Title::OnDestroy()
{
	/*DeleteGO(m_titletorokko);
	DeleteGO(m_titlecamera);*/
	DeleteGO(m_titletorokko);
	DeleteGO(m_titlecamera);
	DeleteGO(m_title);
	
}
bool Title::Start()
{
	m_title = NewGO<TitleGame>(0,"TitleGame");
	m_titletorokko = NewGO<titletorokko>(0, "titletorokko");
	m_titlecamera = NewGO<titlecamera>(0, "titledamera");
	/*MainCamera().SetTarget({ 0.0f,0.0f,0.0f });
	MainCamera().SetNear(1.0f);
	MainCamera().SetFar(5000.0f);
	MainCamera().SetPosition({ 0.0f, 0.0f, -50.0f });*/

	//m_texture.CreateFromDDSTextureFromFile(L"sprite/title.dds");
	//m_sprite.Init(m_texture,1280,720/* GraphicsEngine().Get2DSpaceScreenWidth(), GraphicsEngine().Get2DSpaceScreenHeight()*/);

	////モデルをロード
	//m_skinModelData.Load(L"modelData/titletorokko.cmo");
	//m_skinModel.Init(m_skinModelData);
	
	/*m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/titletorokko.cmo");
	m_skinModelRender->SetScale({ 1.0,1.0,1.0 });*/
	m_fade = FindGO<Fade>("Fade");
	m_fade->StartFadeIn();
	return true;
}
void Title::Update()
{
	//////メインカメラに注視点と視点を設定する。
	//CVector3 target = { 0,0,0 };
	//CVector3 pos = { 0,0,-50 };
	//MainCamera().SetTarget(target);
	//MainCamera().SetPosition(pos);

	////カメラの更新。
	//MainCamera().Update();

	if (m_isWaitFadeout) {
		if (!m_fade->IsFade()) {
			NewGO<Game>(0, "Game");
			DeleteGO(this);
		}
	}
	else {
		if (Pad(0).IsTrigger(enButtonStart)) {
			m_isWaitFadeout = true;
			m_fade->StartFadeOut();
		}
	}
	///////////////////////////////////////////////////////////////////////////////////////
	//テスト
	if (GetAsyncKeyState(VK_SPACE)) {
		NewGO<testGame>(0, "testGame");				//鏡処理のテスト用、後で消す
		DeleteGO(this);
	}
	///////////////////////////////////////////////////////////////////////////////////////
	/*if (m_titlecamera == nullptr && m_titletorokko == nullptr) {
		m_titlecamera = NewGO<titlecamera>(0, "titlecamera");
		m_titletorokko = NewGO<titletorokko>(0, "titletorokko");
	}*/
	
	//m_sprite.Update(CVector3::Zero, CQuaternion::Identity, CVector3::One);
	//m_skinModel.Update(m_position, m_rotation, CVector3::One);
}
void Title::Render(CRenderContext& rc)
{
	(void)rc;
	/*rc.OMSetDepthStencilState(DepthStencilState::spriteRender, 0);
	m_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
	rc.OMSetDepthStencilState(DepthStencilState::spriteRender, 0);*/
/*
	int alphaflag = 0;
	m_skinModel.Draw(rc,
		MainCamera().GetViewMatrix(),
		MainCamera().GetProjectionMatrix(),
		CMatrix::Identity,
		CMatrix::Identity,
		alphaflag);*/
	
}