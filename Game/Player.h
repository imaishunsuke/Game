#pragma once
#include "tkEngine/character/tkCharacterController.h"

class Torokko;
class Goal;

class Player:public IGameObject
{
public:
	Player();
	~Player();

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
	void Turn();
	void Rotation();
	void Dead();
	
	//メンバ変数
	CMatrix m_rot;
	CSkinModel m_skinModel;								//スキンモデル。
	CSkinModelData m_skinModelData;						//スキンモデルデータ。
	CShaderResourceView m_specularMap;
	CShaderResourceView m_normalMap;
	CCharacterController m_charaCon;					//キャラクターコントローラー。
	CCharacterController::ColliderType m_collidertype = CCharacterController::Capsule;
	CVector3 m_moveSpeed = CVector3::Zero;				//移動速度。
	CSprite m_hsprite;									//スプライト
	CShaderResourceView m_htexture;						//HPテクスチャ。
	CVector3	m_hposition = CVector3::Zero;			//座標。
	CSprite m_hdsprite;									//スプライト
	CShaderResourceView m_hdtexture;					//HPダメージ時テクスチャ。
	CVector3	m_hpdosition = CVector3::Zero;			//座標。
	CSprite m_hbsprite;									//スプライト
	CShaderResourceView m_hbtexture;					//HP barテクスチャ。
	CVector3	m_hbposition = CVector3::Zero;			//座標。
	CVector3 m_position = CVector3::Zero;				//座標。
	CVector3 diff = CVector3::Zero;
	CQuaternion qRot = CQuaternion::Identity;
	CQuaternion m_rotation = CQuaternion::Identity;		//回転
	CQuaternion m_rotation2 = CQuaternion::Identity;		//回転
	CFont m_font;										//文字
	CVector3 m_gpos = CVector3::Zero;

	float x;
	float plposlen;
	float angle;
	float hpscale=1;
	float hpdscale=1;
	int lifecount = 0;									//ライフカウンタ(モデル差し替え)
	int dameflag = 0;									//ダメージフラグ
	int flag = 0;
	float nlcount = 1;									//無敵カウンタ
	float scale;										//文字の拡大率
	int scalefg = 0;									//文字拡大フラグ
	float count = 1;									//文字カウンター
	Mirror* m_mirror = NULL;
	Torokko*toro = nullptr;
	Goal* m_goal = nullptr;
};
