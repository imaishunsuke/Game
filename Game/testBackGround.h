#pragma once

#include "tkEngine/physics/tkMeshCollider.h"
#include "tkEngine/physics/tkrigidBody.h"

class testBackGround : public IGameObject
{
public:
	testBackGround();
	~testBackGround();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	void OnDestroy();
	//ƒƒ“ƒo•Ï”
	CSkinModelData m_skinModelData;
	CSkinModel m_skinModel;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_scale = { 1.5f,1.0f,1.5f };
	CMeshCollider m_meshCollider;
	CRigidBody m_rigidBody;
};

