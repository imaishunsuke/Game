#pragma once
class TitlePlayer;

class Titlemirror : public IGameObject
{
public:
	Titlemirror();
	~Titlemirror();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	TitlePlayer* pl = nullptr;

private:
	CSkinModel m_skinModel;			//スキンモデル。
	CSkinModelData m_skinModelData;	//スキンモデルデータ。
	CVector3 m_position = CVector3::Zero;
	CQuaternion m_rotation = CQuaternion::Identity;
};

