#pragma once
class titlecamera;

class TitlePlayer : public IGameObject 
{
public:
	TitlePlayer();
	~TitlePlayer();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	bool GetMoveFlag(){
		return Flag;
	}
	CVector3 GetPosition(){
		return m_position;
	}
private:
	bool Flag = false; // 移動の管理
	CSkinModel m_skinModel;			//スキンモデル。
	CSkinModelData m_skinModelData;	//スキンモデルデータ。
	CSkinModel m_skinModelmirror;
	CSkinModelData m_skinModelmirrorData;
	CVector3 m_position = CVector3::Zero;
	CQuaternion m_rotation = CQuaternion::Identity;
	CVector3 m_positionmirror = CVector3::Zero;
	titlecamera* m_taitlecamera = nullptr;
};

