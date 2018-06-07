#pragma once
class Goal;
class Fade;
class Mirror;
class ResultScene : public IGameObject
{
public:
	ResultScene();
	~ResultScene();

	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	void OnDestroy();

	CVector3 m_position = CVector3::Zero;
	CQuaternion m_rotation = CQuaternion::Identity;
	CSprite m_sprite;
	CShaderResourceView m_texture;
	Goal* m_goal = nullptr;
	Mirror* m_mirror = nullptr;
private:
	bool m_isWaitFadeout = false;
	Fade* m_fade = nullptr;
};

