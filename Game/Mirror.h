#pragma once


class Mirror : public IGameObject
{
public:
	Mirror();
	~Mirror();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	void MakeRotationFromQuaternion(const CQuaternion& q);
	//ƒƒ“ƒo•Ï”
	CSkinModel m_skinModel;
	CSkinModelData m_skinModelData;
	float m_anglex = 0;
	float m_angley = 0;
	CQuaternion m_rotation = CQuaternion:: Identity;
	CVector3 m_position = CVector3::Zero;
	
};

