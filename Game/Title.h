#pragma once
class Fade;
class titletorokko;
class titlecamera;
class TitleGame;

class Title : public IGameObject
{
public:
	Title();
	~Title();
	bool Start();
	void Update();
	void OnDestroy();
	void Render(CRenderContext& rc);
	CSkinModelData m_skinModelData;
	/*CSkinModel m_skinModel;
	CVector3 m_position = CVector3::Zero;
	CQuaternion m_rotation = CQuaternion::Identity;*/
	prefab::CSkinModelRender*m_skinModelRender = nullptr;
	titletorokko* m_titletorokko = nullptr;
	titlecamera* m_titlecamera = nullptr;
	TitleGame* m_title = nullptr;
private:
	bool m_isWaitFadeout = false;
	/*CShaderResourceView m_texture;
	CSprite m_sprite;*/
	Fade* m_fade = nullptr;
	//titletorokko* m_titletorokko = nullptr;
	//titlecamera* m_titlecamera = nullptr;


};

