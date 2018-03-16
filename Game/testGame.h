#pragma once

#include "tkEngine/graphics/effect/tkEffect.h"

class Fade;
class Mirror;
class testGameCamera;
class testBackGround;

class testGame : public IGameObject
{
public:
	testGame();
	~testGame();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	void OnDestroy();
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//スキンモデルレンダラー。
	CAnimationClip m_animClip[1];							//アニメーションクリップ。
	CAnimation m_animation;
	CVector3 m_pos = CVector3::Zero;
private:
	enum EnState {
		enState_FadeIn, //フェードイン中
		enState_InGame, //インゲーム中
	};
	EnState m_state = enState_FadeIn;
	Fade* m_fade = nullptr;
	bool m_isWaitFadeout = false;
	float m_waitTimer = 0.0f;
	Mirror* m_mirror = nullptr;
	testGameCamera* m_gameCamera = nullptr;
	testBackGround* m_background = nullptr;
};

