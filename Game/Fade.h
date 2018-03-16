#pragma once
class Fade : public IGameObject
{
public:
	Fade();
	~Fade();
	bool Start() override;
	void Update() override;
	void PostRender(CRenderContext& rc) override;
	void StartFadeIn()
	{
		m_state = enState_FadeIn;
	}
	void StartFadeOut()
	{
		m_state = enState_FadeOut;
	}
	bool IsFade() const
	{
		return m_state != enState_Idle;
	}
	float GetCurrentAlpha() const
	{
		return m_currentAlpha;
	}
private:
	enum Enstate {
		enState_FadeIn,
		enState_FadeOut,
		enState_Idle
	};
	CShaderResourceView m_texture;
	CSprite m_sprite;
	Enstate m_state = enState_Idle;
	float m_currentAlpha = 1.0f;
};

