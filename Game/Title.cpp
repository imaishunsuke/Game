#include "stdafx.h"
#include "Title.h"
#include "Fade.h"
#include "Game.h"
#include "testGame.h"
#include"tkEngine/graphics/tkPresetRenderState.h"
#include "TitlePlayer.h"
#include "titlecamera.h"
#include "Mirror.h"
#include "Player.h"
#include "TitleEnemyball.h"
#include "TitleStar.h"
#include "Titlemirror.h"
#include"tkEngine/light/tkDirectionLight.h"
#include "tkEngine/sound/tkSoundSource.h"

Title::Title()
{
}


Title::~Title()
{
	DeleteGO(m_Stitle);
}
void Title::OnDestroy()
{
	/*DeleteGO(m_titletorokko);
	DeleteGO(m_titlecamera);*/
	DeleteGO(m_mirror);
	//DeleteGO(m_player);
	DeleteGO(m_titlecamera);
	DeleteGO(m_titleplayer);
	DeleteGO(m_titleenemyball);
	DeleteGO(m_titlestar);
	DeleteGO(dirLight);
	DeleteGO(m_titlemirror);
}
bool Title::Start()
{
	m_Stitle = NewGO<prefab::CSoundSource>(0);
	m_Stitle->Init("sound/title1.wav");
	m_Stitle->Play(true);
	dirLight = NewGO<prefab::CDirectionLight>(0);
	//ライトの方向を設定
	dirLight->SetDirection({ 0.707f,-0.707f,0.0f });
	//ライトの色を設定
	dirLight->SetColor({ 10.0f,10.0f,10.0f,1.0f });
	GraphicsEngine().GetShadowMap().SetLightDirection({ 0.0,-1.0f,0.0f });
	
	m_titleplayer = NewGO<TitlePlayer>(0, "TitlePlayer");
	//m_mirror = NewGO<Mirror>(0, "Mirror");
	m_titlecamera = NewGO<titlecamera>(0, "titlecamera");
	m_titleenemyball = NewGO<TitleEnemyball>(0, "TitleEnemyball");
	m_titlestar = NewGO<TitleStar>(0, "TitleStar");
	m_titlemirror = NewGO<Titlemirror>(0, "Titlemirror");
	m_texture.CreateFromDDSTextureFromFile(L"sprite/title.dds");
	m_sprite.Init(m_texture, 1280, 720);
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
		m_Stitle->SetVolume(1.0);
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
	//(void)rc;
	rc.OMSetDepthStencilState(DepthStencilState::spriteRender, 0);
	m_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
	rc.OMSetDepthStencilState(DepthStencilState::SceneRender, 0);
/*
	int alphaflag = 0;
	m_skinModel.Draw(rc,
		MainCamera().GetViewMatrix(),
		MainCamera().GetProjectionMatrix(),
		CMatrix::Identity,
		CMatrix::Identity,
		alphaflag);*/
	
}