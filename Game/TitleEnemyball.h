#pragma once
class TitleEnemyball : public IGameObject

{
public:
	TitleEnemyball();
	~TitleEnemyball();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);

private:
	CSkinModel m_skinModel;			//スキンモデル。
	CSkinModelData m_skinModelData;	//スキンモデルデータ。
	CVector3 m_position = CVector3::Zero;
	CVector3 m_scale = CVector3::One;
	CQuaternion m_rotation = CQuaternion::Identity;
};

