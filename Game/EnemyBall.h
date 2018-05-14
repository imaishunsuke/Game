#pragma once
#include "Enemybace.h"
//#include "tkEngine/physics/tkRigidBody.h"
//#include "tkEngine/physics/tkSphereCollider.h"
#include "tkEngine/character/tkCharacterController.h"
class Player;
class Goal;

class EnemyBall : public Enemybace
{
public:
	EnemyBall();
	~EnemyBall();

	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	

	//ƒƒ“ƒo•Ï”
	CSkinModel m_skinModel;
	CSkinModelData m_skinModelData;
	CVector3 m_position = {-100.0f,28.0f,0.0f };
	CVector3 m_moveSpeed = CVector3::Zero;
	CVector3 up = CVector3::Up;							//ã•ûŒü
	CVector3 m_axisX;									//”CˆÓ‚Ì‰ñ“]²
	CQuaternion m_rotation = CQuaternion::Identity;
	Player* m_player = nullptr;
	Goal* m_goal = nullptr;
	CVector3 diff = CVector3::Zero;
	/*CSphereCollider m_collider;
	CRigidBody m_rigidBody;*/
	CCharacterController m_charaCon;
	CCharacterController::ColliderType m_collidertype = CCharacterController::Sphere;
	float r = 20.0f;									//”¼Œa
};


