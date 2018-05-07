/*!
 * @brief	キャラクタコントローラー。
 */

#pragma once
class Mirror;
class Player;

#include "tkEngine/Physics/tkSphereCollider.h"
#include "tkEngine/Physics/tkCapsuleCollider.h"
#include "tkEngine/Physics/tkRigidBody.h"

namespace tkEngine{
	/*!
	 * @brief	キャラクタコントローラー。
	 */
	class CCharacterController{
	public:
		CCharacterController() {

		}
		~CCharacterController()
		{
			RemoveRigidBoby();
		}
		enum ColliderType {
			Capsule,				//カプセルコライダー
			Sphere					//球コライダー
		};
		/*!
		 * @brief	初期化。
		 *@param[in]	radius		カプセルコライダーの半径。
		 *@param[in]	height		カプセルコライダーの高さ。
		 *@param[in]	gravity		重力。
		 *@param[in]	position	初期位置。
		 *@param[in]	type		コライダーの種類。
		 */
		void Init(float radius, float height,float gravity, const CVector3& position ,ColliderType type);
		/*!
		 * @brief	実行。
		 *@param[in]	deltaTime		経過時間。単位は秒。
		 *@param[in, out]	moveSpeed		移動速度。内部で重力加速が計算され、その結果がmoveSpeedに反映されます。
		 *@return 移動後のキャラクターの座標。
		 */
		const CVector3& Execute(float deltaTime, CVector3& moveSpeed,ColliderType type);
		/*!
		 * @brief	座標を取得。
		 */
		const CVector3& GetPosition() const
		{
			return m_position;
		}
		/*!
		 * @brief	座標を設定。
		 */
		void SetPosition(const CVector3& pos)
		{
			m_position = pos;
		}
		
		/*!
		 * @brief	ジャンプさせる。
		 */
		void Jump( )
		{
			m_isJump = true;
			m_isOnGround = false;
		}
		/*!
		 * @brief	ジャンプ中か判定
		 */
		bool IsJump() const
		{
			return m_isJump;
		}
		/*!
		* @brief	地面上にいるか判定。
		*/
		bool IsOnGround() const
		{
			return m_isOnGround;
		}
		/*!
		* @brief	壁に当たっているか判定。
		*/
		bool IsHitWall() const
		{
			return m_isHitWall;
		}
		/*!
		* @brief	コライダーを取得。
		*/
		CCapsuleCollider* GetCollider()
		{
			return &m_collider;
		}
		/*!
		* @brief	重力を取得。
		*/
		void SetGravity(float gravity)
		{
			m_gravity = gravity;
		}
		/*!
		* @brief	剛体を取得。
		*/
		CRigidBody* GetRigidBody()
		{
			return &m_rigidBody;
		}
		/*!
		* @brief	剛体を物理エンジンから削除。。
		*/
		void RemoveRigidBoby();

		//int flag = 0;
		void AddIgnoreCollisionAttr(EnCollisionAttr attr)
		{
			m_ignoreCollisionAttrs |= 1 << attr;
		}
		/*void RemoveIgnoreCollisionAttr(EnCollisionAttr attr)
		{
			m_ignoreCollisionAttrs ~= (m_ignoreCollisionAttrs & 1 << attr);
		}*/
	private:
		CVector3 			m_position = CVector3::Zero;	//座標。
		bool 				m_isJump = false;				//ジャンプ中？
		bool				m_isOnGround = true;			//地面の上にいる？
		bool				m_isHitWall = true;
		CCapsuleCollider	m_collider;						//コライダー。
		float				m_radius = 0.0f;
		float				m_height = 0.0f;		
		CSphereCollider		m_sphereCollider;
		CRigidBody			m_rigidBody;					//剛体。
		int					m_ignoreCollisionAttrs = 2;		//ビットが立っている属性のコリジョンとのあたり判定を無視する。
		float				m_gravity = -9.8f;
		Player* m_player = nullptr;
		Mirror* m_mirror = nullptr;
	};
}