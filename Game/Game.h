#pragma once
#include"Level.h"
#include "tkEngine/graphics/effect/tkEffect.h"

class Fade;
class background;
class Player;
class Torokko;
class GameCamera;
class Mirror;

class Game : public IGameObject
{
public:
	Game();
	~Game();
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
	Level m_level;
	background*m_background = nullptr;
	Player*m_player = nullptr;
	Torokko*m_torokko = nullptr;
	GameCamera*m_gamecamera = nullptr;
	CVector3 m_position= { 30.0f, 10.0f, 0.0f };
	Mirror* m_mirror = nullptr;
};