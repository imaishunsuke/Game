#pragma once

//CMeshColliderとCRigidBodyを使用したい場合は下記のヘッダーファイルをインクルードする必要がある。
#include "tkEngine/physics/tkMeshCollider.h"
#include "tkEngine/physics/tkRigidBody.h"

class background : public IGameObject
{
public:
	/////////////////////////////////////////////////////
	// メンバ関数など。
	/////////////////////////////////////////////////////
	background();
	~background();
	void Update();
	void Render(CRenderContext& rc);
	bool Start();
	void OnDestroy();
	/////////////////////////////////////////////////////
	// メンバ変数など。
	/////////////////////////////////////////////////////
	CSkinModelData m_skinModelData;	//スキンモデルデータ。
	CSkinModel m_skinModel;			//スキンモデル。
	CVector3 m_position = CVector3::Zero;	//座標。
	CMeshCollider m_meshCollider;	//メッシュコライダー。
	CRigidBody m_rigidBody;			//剛体。
	testMirror* m_mirror = NULL;
};

