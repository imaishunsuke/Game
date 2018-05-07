#pragma once
#include "tkEngine/character/tkCharacterController.h"
using namespace tkEngine;

class Player;

class Mirror : public tkEngine::IGameObject
{
public:
	Mirror();
	~Mirror();
	bool Start();
	void Rotation();
	void Update();
	void Render(CRenderContext& rc);
	void PostRender(CRenderContext& rc);
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
	CQuaternion m_rotation=CQuaternion::Identity;
	CQuaternion m_rotation1 = CQuaternion::Identity;//保管
	CVector3 mirrormaefront = CVector3::Zero;

	CSprite m_mpsprite;									//スプライト
	CShaderResourceView m_mptexture;					//ミラーMPテクスチャ。
	CSprite m_mpbsprite;									//スプライト
	CQuaternion m_mprotation = CQuaternion::Identity;
	CShaderResourceView m_mpbtexture;					//ミラーMPbarテクスチャ。
	CSprite m_msprite;									//スプライト
	CQuaternion m_mpbrotation = CQuaternion::Identity;
	CShaderResourceView m_mtexture;						//ミラーMirrorテクスチャ。
	float mpscale=1.0;
	int fl = 0;//保管フラグ
	int mpflag = 0;
	float angleX = 0.0f;
	float angleY = 0.0f;
	//testMirror* m_mirror = NULL;
	CMatrix m_mirrorViewMatrix;
	CMatrix m_mirrorProjectionMatrix;

	//CCharacterController m_charaCon;
	CQuaternion qRot = CQuaternion::Identity;
	CQuaternion qRot2 = CQuaternion::Identity;
	
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
	Player* pl = NULL;
	float angle = 0;
};

