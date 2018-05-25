#pragma once
#include"Player.h"
#include"Goal.h"
#include"Player.h"
//ばねカメラを使用したい場合はtkSpringCamera.hをインクルードする必要がある。
#include "tkEngine/camera/tkSpringCamera.h"

class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();

	CMatrix m_rot = CMatrix::Identity;
	CVector3 m_position = CVector3::Zero;
	CQuaternion m_rotation = CQuaternion::Identity;
	CSpringCamera m_springCamera;
	CVector3 m_toCameraPos = CVector3::Zero;
	Player*m_player=nullptr;
	Goal* m_goal = nullptr;
	int Flag = 0;
};