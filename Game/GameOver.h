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

	CSprite m_sprite;
	CShaderResourceView m_texture;
	Torokko* m_toro = nullptr;
private:
	bool m_isWaitFadeout = false;
	Fade* m_fade = nullptr;
};

