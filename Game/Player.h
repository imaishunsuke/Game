#pragma once
#include "tkEngine/character/tkCharacterController.h"

class Torokko;
class Goal;

class Game;
class GameOverProd;

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
	void Line();
	void Rotation();
	void Dead(CRenderContext& rc);
	
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
	CVector3 m_position = {0.0,10.0,0.0} /*= CVector3::Zero*/;				//座標。
	CVector3 diff = CVector3::Zero;
	CQuaternion qRot = CQuaternion::Identity;
	CQuaternion m_rotation = CQuaternion::Identity;		//回転
	CQuaternion m_rotation2 = CQuaternion::Identity;		//回転
	CFont m_font;										//文字
	CVector3 m_gpos = CVector3::Zero;
	CVector3 m_cf = CVector3::Zero;
	CVector3 m_sen = CVector3::Zero;					//線分
	CSkinModelData m_skinModelData1;						//スキンモデルデータ。


	float x;
	float y;
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
	int Dcount = 0;										//デッドカウンター
	int DEndPosC = 0;									//デッドエンドポジションカウンター
	float Dtime = 0.0f;									//ミラーを使って1秒間タイマー
	int m_prodcount=0;
	float PressFlag = 0;
	Mirror* m_mirror = NULL;
	Torokko*toro = nullptr;
	Goal* m_goal = nullptr;
	float ChangeFlag = 0;
	/*Game* m_game = nullptr;
	title* m_title = nullptr;*/
	Game*m_game=nullptr;
	GameOverProd* m_Prod=nullptr;
	enum EnAnimationClip {
		enAnimationClip_walk,
		enAnimationClip_num
	};
	CAnimationClip m_animClip[enAnimationClip_num];
	CAnimation m_animation;
private:
	void InitPoly();
private:
	struct Spoly
	{
		CVector3 m_triVertex[3];
		CVector3 m_normal;
	};
	int a = 0;
	int poflag = 0;
	std::vector<Spoly> m_polypool;
	std::vector<Spoly>::iterator itr;
};
