#pragma once


class Player:public IGameObject
{
public:
	Player();
	~Player();

	void Update();
	void Render(CRenderContext& rc);
	bool Start();
	//アニメーションを初期化。
	void InitAnimation();
	//アニメーション制御。
	void AnimationControl();
	//移動処理。
	void Move();
	void Turn();
	void Rotation();
	
	//メンバ変数
	CMatrix m_rot;
	CSkinModel m_skinModel;								//スキンモデル。
	CSkinModelData m_skinModelData;						//スキンモデルデータ。
	CVector3 m_position = CVector3::Zero;				//座標。
	CVector3 diff = CVector3::Zero;
	CQuaternion qRot = CQuaternion::Identity;
	CQuaternion m_rotation = CQuaternion::Identity;		//回転
	CQuaternion m_rotation2 = CQuaternion::Identity;		//回転
	float plposlen;
	float angle;
};
