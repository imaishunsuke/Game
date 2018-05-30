#pragma once
class TitlePlayer;

class TitleStar : public IGameObject
{
public:
	TitleStar();
	~TitleStar();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);

	CSkinModel m_skinModelstar;			//スキンモデル。
	CSkinModelData m_skinModelDatastar;	//スキンモデルデータ。
	CSkinModel m_skinModelbrock;
	CSkinModelData m_skinModelDatabrock;
	CVector3 m_positionbrock = CVector3::Zero;
	CVector3 m_positionstar = CVector3::Zero;
	CQuaternion m_rotationstar = CQuaternion::Identity;
	TitlePlayer* pl = nullptr;
};

