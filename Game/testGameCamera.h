#pragma once
#include "Mirror.h"
#include "tkEngine/camera/tkSpringCamera.h"

class testGameCamera : public IGameObject
{
public:
	testGameCamera();
	~testGameCamera();
	bool Start();
	void Update();
	//ƒƒ“ƒo•Ï”
	CVector3 m_position = CVector3::Zero;
	CQuaternion m_rotation = CQuaternion::Identity;
	CSpringCamera m_springCamera;
	CVector3 m_toCameraPos = CVector3::Zero;
private:
	Mirror* m_mirror;
};

