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
	//ÉÅÉìÉoïœêî
	CSkinModelData m_skinModelData;
	CSkinModel m_skinModel;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_scale = CVector3::One;
	CMeshCollider m_meshCollider;
	CRigidBody m_rigidBody;
	testMirror* m_mirror = NULL;
};

