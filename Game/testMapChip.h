#pragma once
#include "tkEngine/physics/tkMeshCollider.h"
#include "tkEngine/physics/tkRigidBody.h"

class testMapChip  : public IGameObject
{
public:
	testMapChip();
	~testMapChip();
	void Init(
		const wchar_t* modeFilePath,
		CVector3 pos,
		CVector3 scale,
		CQuaternion rotation);
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	void OnDestroy();

	//ÉÅÉìÉoïœêî
	CSkinModelData m_skinModelData;
	CSkinModel m_skinModel;
	CVector3 m_position;
	CVector3 m_scale;
	CQuaternion m_rotation;
	CMeshCollider m_meshCollider;
	CRigidBody m_rigidBody;
};

