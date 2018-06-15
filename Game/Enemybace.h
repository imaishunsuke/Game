#pragma once
#include "tkEngine/physics/tkMeshCollider.h"
#include "tkEngine/physics/tkRigidBody.h"
class Enemybace : public IGameObject
{
public:
	Enemybace();
	~Enemybace();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	virtual void Build(const wchar_t* fileDataPath) = 0;
	virtual void Init(
		const wchar_t* modelFilePath,
		CVector3 pos,
		CVector3 scale,
		CQuaternion rotation
	) = 0;
	/*virtual void SetPosition(CVector3 pos) {
		m_position = pos;
	}
	virtual void SetScale(CVector3 scale) {
		m_scale = scale;
	}
	virtual void SetRotation(CQuaternion rotation) {
		m_rotation = rotation;
	}
	virtual CVector3 GetPosition() {
		return m_position;
	}
	virtual CQuaternion GetRotation() {
		return m_rotation;
	}*/
	const CSkinModel& GetModel() {
		return m_skinModel;
	}
	std::map<wchar_t*, Enemybace*>::iterator FindEnemyMapChip(wchar_t* modelDataFilePath) {
		return m_enemyMapChip.find(modelDataFilePath);;
	}
	std::map<wchar_t*, Enemybace*>::iterator EndEnemyMapChip()
	{
		return m_enemyMapChip.end();
	}
	void SetEnemyMapChip(wchar_t* modelDataFilePath,Enemybace* enemy) 
	{
		m_enemyMapChip.insert({modelDataFilePath,enemy });
	}
private:
	CSkinModel m_skinModel;				//スキンモデル
	CSkinModelData m_skinModelData;		//スキンモデルデータ
	//CVector3 m_position;				//座標
	//CQuaternion m_rotation;				//回転
	//CVector3 m_scale;					//拡大。
	//CQuaternion m_rotation;				//回転。
	//CMeshCollider m_meshCollider;		//メッシュコライダー。
	//CRigidBody m_rigidBody;				//剛体。
	std::map<wchar_t*, Enemybace*> m_enemyMapChip;
};
