#pragma once
class Goal;
class ResultScene : public IGameObject
{
public:
	ResultScene();
	~ResultScene();

	bool Start();
	void Update();
	void Render(CRenderContext& rc);

	CVector3 m_position = CVector3::Zero;
	CQuaternion m_rotation = CQuaternion::Identity;
	CSprite m_sprite;
	CShaderResourceView m_texture;
	Goal* m_goal = nullptr;
};

