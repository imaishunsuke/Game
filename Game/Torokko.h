#pragma once
#include "tkEngine/character/tkCharacterController.h"

class Torokko:public IGameObject
{
public:
	Torokko();
	~Torokko();
	void Update();
	void Render(CRenderContext& rc);
	void PostRender(CRenderContext& rc)override;
	bool Start();
	//アニメーションを初期化。
	void InitAnimation();
	//アニメーション制御。
	void AnimationControl();
	//移動処理。
	void Move();
	void Rotation();

	//メンバ変数
	float x;
	float count = 1;
	int flag = 1;
	int MoveFlag = 0;									//スタート時の加速のフラグ
	int dameflag = 0;									//ダメージフラグ
	float scale;
	int scalefg = 0;
	CMatrix m_rot;
	CVector3 diff;
	float posl;
	CSkinModelData m_skinModelData;						//スキンモデルデータ。
	CSkinModel m_skinModel;								//スキンモデル。
	CSkinModelData m_skinModelData1;					//ダメージ1データ	
	CSkinModel m_skinModel1;								
	CSkinModelData m_skinModelData2;
	CSkinModel m_skinModel2;
	CSkinModelData m_skinModelData3;
	CSkinModel m_skinModel3;
	CSkinModelData m_skinModelData4;
	CSkinModel m_skinModel4;
	
	CVector3 m_position = CVector3::Zero;				//座標。
	CCharacterController m_charaCon;					//キャラクターコントローラー。
	CVector3 m_moveSpeed = CVector3::Zero;				//移動速度。
	CQuaternion qRot = CQuaternion::Identity;
	CQuaternion m_rotation = CQuaternion::Identity;		//回転
	CVector3 m_gpos = CVector3::Zero;
	CFont m_font;
	Mirror* m_mirror = NULL;
};

