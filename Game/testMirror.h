#pragma once
#include "tkEngine/character/tkCharacterController.h"
using namespace tkEngine;

class testMirror : public tkEngine::IGameObject
{
public:
	testMirror();
	~testMirror();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	//メンバ変数
	CSkinModel m_skinModel;
	CSkinModelData m_skinModelData;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_target = CVector3::Zero;
	CVector3 m_moveSpeed = CVector3::Zero;
	CQuaternion m_rotation = CQuaternion::Identity;
	CVector3 m_scale = { 0.2f,0.2f,0.2f };
	CCharacterController m_charaCon;
	CMatrix m_mirrorViewMatrix;
	CMatrix m_mirrorProjectionMatrix;
	int  alphaflag = 1;									//ミラーに写っている物体を消すフラグ
	Mirror* m_mirror = NULL;
	static testMirror& GetInstance()
	{
		static testMirror* instance = nullptr;
		if (instance == nullptr) {
			instance = new testMirror;
		}
		return *instance;
	}
};
