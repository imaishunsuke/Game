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
	

	//メンバ変数
	CSkinModel m_skinModel;
	CSkinModelData m_skinModelData;
	CVector3 m_position = { 0.0f,4.0f,15.0f };
	CVector3 m_moveSpeed = CVector3::Zero;
	CVector3 up = CVector3::Up;							//上方向
	CVector3 m_axisX;									//任意の回転軸
	CQuaternion m_rotation = CQuaternion::Identity;
	Player* m_player = nullptr;
	Goal* m_goal = nullptr;
	CVector3 diff = CVector3::Zero;
	/*CSphereCollider m_collider;
	CRigidBody m_rigidBody;*/
	CCharacterController m_charaCon;
	CCharacterController::ColliderType m_collidertype = CCharacterController::Sphere;
};


