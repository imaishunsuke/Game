#pragma once
#include "tkEngine/character/tkCharacterController.h"
using namespace tkEngine;

class Torokko;

class Mirror : public tkEngine::IGameObject
{
public:
	Mirror();
	~Mirror();
	bool Start();
	void Rotation();
	void Update();
	void Render(CRenderContext& rc);
	//メンバ変数
	CMatrix m_rot;
	CMatrix m_mirrorforwardMatrix;
	CVector3 diff = CVector3::Zero;
	float Mirlen;
	CSkinModel m_skinModel;
	CSkinModelData m_skinModelData;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_moveSpeed = CVector3::Zero;
	CVector3 m_target = CVector3::Zero;
	CVector3 m_mirtarget = CVector3::Zero;
	CVector3 mirrorfront = CVector3::Zero;
	CVector3 OldMirrorFront = CVector3::Zero;
	CVector3 mirrorfronty = CVector3::Zero;
	CVector3 m_vMirrorFront = CVector3::Zero;
	CVector3 m_vTorokkoFront = CVector3::Zero;
	CQuaternion m_rotation=CQuaternion::Identity;
	CQuaternion m_rotation1 = CQuaternion::Identity;//保管
	CQuaternion m_vRotation = CQuaternion::Identity;//ミラー制御の角度を求めるための保管
	CQuaternion m_vTorokkoRotation = CQuaternion::Identity;
	CVector3 mirrormaefront = CVector3::Zero;
	int fl = 0;//保管フラグ
	float angleX = 0.0f;
	float angleY = 0.0f;
	float m_vAngle = 0.0f;		//仮想の角度
	float anglex = 0.0f;
	int a = 1, b= 1,c=1,d=1;
	//testMirror* m_mirror = NULL;
	CMatrix m_mirrorViewMatrix;
	CMatrix m_mirrorProjectionMatrix;

	//CCharacterController m_charaCon;
	CQuaternion qRot = CQuaternion::Identity;
	CQuaternion qRot2 = CQuaternion::Identity; //鏡だけの回転
	
	int  alphaflag = 1;									//ミラーに写っている物体を消すフラグ
	bool m_isMirror = false;							//ミラーを使用しているかのフラグ

	static Mirror& GetInstance()
	{
		static Mirror* instance = nullptr;
		if (instance == nullptr) {
			instance = new Mirror;
		}
		return *instance;
	}
	Torokko* toro = NULL;
	float angle = 0;
};

