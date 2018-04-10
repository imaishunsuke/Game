#pragma once
class ResultScene : public IGameObject
{
public:
	ResultScene();
	~ResultScene();

	bool Start();
	void Update();
	void PostRender(CRenderContext& rc);

	CVector3 m_position = CVector3::Zero;
	CSprite m_sprite;
	CShaderResourceView m_texture;
};

