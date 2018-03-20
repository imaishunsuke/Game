#pragma once

class Mirror : public IGameObject
{
public:
	Mirror();
	~Mirror();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	//ƒƒ“ƒo•Ï”
	CSkinModel m_skinModel;
	CSkinModelData m_skinModelData;
	CVector3 m_position = CVector3::Zero;
	CQuaternion m_rotation=CQuaternion::Identity;
	float angleX = 0.0f;
	float angleY = 0.0f;
};

