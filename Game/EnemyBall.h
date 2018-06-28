#pragma once
#include "Enemybace.h"
//#include "tkEngine/physics/tkRigidBody.h"
//#include "tkEngine/physics/tkSphereCollider.h"
#include "tkEngine/character/tkCharacterController.h"
#include "tkEngine/physics/tkMeshCollider.h"
#include "tkEngine/physics/tkRigidBody.h"
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
		//void OnDestroy();
		//void Build(const wchar_t* fileDataPath);
		void Init(const wchar_t* modelFilePath, CVector3 pos, CQuaternion rotation, CVector3 scale);
		void Create();
		const CVector3& Physics(CVector3& moveSpeed, float DeltaTime);

	private:
		//メンバ変数
		CSkinModel m_skinModel;
		CSkinModelData m_skinModelData;
		CVector3 m_startPosition = CVector3::Zero;
		CVector3 m_position = CVector3::Zero;/*{-100.0f,28.0f,0.0f }*/;
		CVector3 m_moveSpeed = CVector3::Zero;
		CVector3 up = CVector3::Up;							//上方向
		CVector3 m_axisX;									//任意の回転軸
		CVector3 m_scale = CVector3::One;
		CQuaternion m_rotation = CQuaternion::Identity;
		Player* m_player = nullptr;
		Goal* m_goal = nullptr;
		CVector3 diff = CVector3::Zero;
		//EnemyBall* m_enemy = nullptr;
		//CSphereCollider m_collider;
		//CRigidBody m_rigidBody;
		//CCharacterController m_charaCon;

		//CCharacterController::ColliderType m_collidertype = CCharacterController::ColliderType::Sphere;

		float r = 2.0f;									//半径
		Mirror* m_mirror = NULL;
		//std::map<wchar_t,EnemyBall*> m_enemyMapChip
		std::list<EnemyBall*> m_enemyBallList;
		CRigidBody m_rigidBody;
		CSphereCollider m_collider;
		prefab::CSoundSource* m_enemySound = nullptr;

		bool 				m_isJump = false;				//ジャンプ中？
		bool				m_isOnGround = true;			//地面の上にいる？
		float				m_radius = 0.0f;
		bool				m_isHitWall = true;
	};


