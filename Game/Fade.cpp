#include "stdafx.h"
#include "Fade.h"

#include "tkEngine/graphics/tkPresetRenderState.h"

Fade::Fade()
{
}


Fade::~Fade()
{
}

bool Fade::Start()
{
	m_texture.CreateFromDDSTextureFromFile(L"sprite/fade.dds");
	m_sprite.Init(m_texture,1280,720 /*GraphicsEngine().Get2DSpaceScreenWidth(), GraphicsEngine().Get2DSpaceScreenHeight()*/);
	return true;
}
void Fade::Update()
{
	switch (m_state) {
	case enState_FadeIn:
		m_currentAlpha -= 2.0f * GameTime().GetFrameDeltaTime();
		if (m_currentAlpha <= 0.0f) {
			m_currentAlpha = 0.0f;
			m_state = enState_Idle;
		}
		break;
	case enState_FadeOut:
		m_currentAlpha += 2.0f * GameTime().GetFrameDeltaTime();
		if (m_currentAlpha >= 1.0f) {
			m_currentAlpha = 1.0f;
			m_state = enState_Idle;
		}
		break;
	case enState_Idle:
		break;
	}
	m_sprite.Update(CVector3::Zero, CQuaternion::Identity, CVector3::One);
}
void Fade::PostRender(CRenderContext& rc)
{
	if (m_currentAlpha > 0.0f) {
		m_sprite.SetMulColor({ 1.0f,1.0f,1.0f,m_currentAlpha });
		m_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetViewProjectionMatrix());
	}
}