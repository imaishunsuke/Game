#pragma once
class Torokko;
class Fade;

class GameOver : public IGameObject
{
public:
	GameOver();
	~GameOver();
	bool Start();
	void Update();
	void PostRender(CRenderContext& rc);

private:
	CSprite m_sprite;
	CShaderResourceView m_texture;
	bool m_isWaitFadeout = false;
	Fade* m_fade = nullptr;
};

