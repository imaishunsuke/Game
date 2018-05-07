#pragma once
#include "Enemybace.h"
//#include "tkEngine/physics/tkRigidBody.h"
//#include "tkEngine/physics/tkSphereCollider.h"
#include "tkEngine/character/tkCharacterController.h"
class Player;
class Torokko;

class EnemyBall : public Enemybace
{
public:
	EnemyBall();
	~EnemyBall();

	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	

	//�����o�ϐ�
	CSkinModel m_skinModel;
	CSkinModelData m_skinModelData;
	CVector3 m_position = { 0.0f,4.0f,15.0f };
	CVector3 m_moveSpeed = CVector3::Zero;
	CVector3 up = CVector3::Up;							//�����
	CVector3 m_axisX;									//�C�ӂ̉�]��
	CQuaternion m_rotation = CQuaternion::Identity;
	Player* m_player = nullptr;
	Torokko* toro = nullptr;							//�v���C���[�ɗv�ύX
	CVector3 diff = CVector3::Zero;
	/*CSphereCollider m_collider;
	CRigidBody m_rigidBody;*/
	CCharacterController m_charaCon;
	CCharacterController::ColliderType m_collidertype = CCharacterController::Sphere;
};

