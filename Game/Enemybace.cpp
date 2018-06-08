#include "stdafx.h"
#include "Enemybace.h"

Enemybace::Enemybace()
{
}


Enemybace::~Enemybace()
{
}
////レベル作成
//void Enemybace::Build(const wchar_t* fileDataPath) {
//	//スケルトン利用して配置
//	CSkeleton skelton;
//	skelton.Load(fileDataPath);
//	int numMapChip = skelton.GetNumBones();
//	for (int i = 1; i < numMapChip; i++)
//	{
//		CBone*bone = skelton.GetBone(i);
//		//ボーンから拡大率、平行移動、回転を取得する。
//		CVector3 position, scale;
//		CQuaternion rotation;
//		bone->CalcWorldTRS(position, rotation, scale);
//		//軸補正を入れる。
//		float t = position.y;
//		position.y = position.z;
//		position.z = -t;
//		t = rotation.y;
//		rotation.y = rotation.z;
//		rotation.z = -t;
//		//ボーン名からモデルデータのファイルパスを作成する。
//		const wchar_t* boneName = bone->GetName();
//		wchar_t modelDataFilePath[256];
//		swprintf(modelDataFilePath, L"modelData/%s.cmo", boneName);
//		Enemybace* enemyChip = NewGO<Enemybace>(0);
//		enemyChip->Init(modelDataFilePath, position, CVector3::One, rotation);
//		auto it = m_enemyChipMap.find(boneName);
//		if (it == m_enemyChipMap.end()) {
//			m_enemyChipMap.insert({ boneName,enemyChip });
//		}
//		//m_enemyChipMap.push_back(enemyChip);
//	}
//}
//void Enemybace::Init(
//	const wchar_t* modelFilePath,
//	CVector3 pos,
//	CVector3 scale,
//	CQuaternion rotation
//) {
//	m_skinModelData.Load(modelFilePath);
//	m_skinModel.Init(m_skinModelData);
//	m_skinModel.SetShadowReceiverFlag(true);
//	SetPosition(pos);
//	SetScale(scale);
//	SetRotation(rotation);
//	//m_position = pos;
//	//m_scale = scale;
//	//m_rotation = rotation;
//
//	//メッシュコライダーを作成。
//	m_meshCollider.CreateFromSkinModel(m_skinModel, nullptr);
//	//剛体の情報を作成。
//	RigidBodyInfo rbInfo;
//	rbInfo.pos = GetPosition();
//	rbInfo.rot = GetRotation();
//	rbInfo.collider = &m_meshCollider;
//	rbInfo.mass = 0.0f;							//質量を0にすると動かない剛体になる。
//												//背景などの動かないオブジェクトは0を設定するとよい。
//	m_rigidBody.Create(rbInfo);					//作成した情報を使って剛体を作成する。
//	m_rigidBody.GetBody()->setUserIndex(enCollisionAttr_Obstacle);
//	PhysicsWorld().AddRigidBody(m_rigidBody);	//作成した剛体を物理ワールドに追加する。
//}
bool Enemybace::Start()
{
	return true;
}
void Enemybace::Update()
{
	//m_skinModel.Update(m_position, m_rotation, m_scale);
}
void Enemybace::Render(CRenderContext& rc)
{
	//m_skinModel.Draw(rc,
	//	MainCamera().GetViewMatrix(),
	//	MainCamera().GetProjectionMatrix(),
	//	CMatrix::Identity,
	//	CMatrix::Identity
	//);
}