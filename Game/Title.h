#pragma once
class Fade;
class TitlePlayer;
class titlecamera;
class Mirror;
class Player;
class EnemyBall;
class TitleEnemyball;
class TitleStar;
class Titlemirror;


class Title : public IGameObject
{
public:
	Title();
	~Title();
	bool Start();
	void Update();
	void OnDestroy();
	void Render(CRenderContext& rc);
private:
	CSkinModelData m_skinModelData;
	/*CSkinModel m_skinModel;
	CVector3 m_position = CVector3::Zero;
	CQuaternion m_rotation = CQuaternion::Identity;*/
	prefab::CSkinModelRender*m_skinModelRender = nullptr;
	TitlePlayer* m_titleplayer = nullptr;
	titlecamera* m_titlecamera = nullptr;
	Mirror* m_mirror = nullptr;
	TitleEnemyball* m_titleenemyball = nullptr;
	TitleStar* m_titlestar = nullptr;
	Titlemirror* m_titlemirror = nullptr;
	//Player* m_player = nullptr;
	float ChangeFlag = 0;
	bool m_isWaitFadeout = false;
	/*CShaderResourceView m_texture;
	CSprite m_sprite;*/
	Fade* m_fade = nullptr;
	//titletorokko* m_titletorokko = nullptr;
	//titlecamera* m_titlecamera = nullptr;
	CShaderResourceView m_texture;
	CSprite m_sprite;
	prefab::CDirectionLight* dirLight;
};

