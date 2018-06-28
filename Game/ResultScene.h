#pragma once
#include "tkEngine/light/tkPointLight.h"
#include "Player.h"
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
	void PostRender(CRenderContext& rc);
	void OnDestroy();
	bool GetResultFlag()
	{
		return ResultFlag;
	}
private:
	CVector3 m_position = CVector3::Zero;
	CQuaternion m_rotation = CQuaternion::Identity;
	CSprite m_sprite;
	CShaderResourceView m_texture;
	Goal* m_goal = nullptr;
	Mirror* m_mirror = nullptr;
	bool m_isWaitFadeout = false;
	Fade* m_fade = nullptr;
	bool ResultFlag = false;
	prefab::CPointLight* m_ptLight = nullptr;
	Player* m_player = nullptr;
	float colorTime = 0.0f;
	float coloradd = 0.0f;
};

