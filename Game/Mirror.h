#pragma once

#include "tkEngine/character/tkCharacterController.h"

class Mirror : public IGameObject
{
public:
	Mirror();
	~Mirror();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	//ƒƒ“ƒo•Ï”
	CSkinModel m_skinModel;
	CSkinModelData m_skinModelData;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_moveSpeed = CVector3::Zero;
	CQuaternion m_rotation=CQuaternion::Identity;
	CVector3 m_scale = { 0.2f,0.2f,0.2f };
	CCharacterController m_charaCon;
};

