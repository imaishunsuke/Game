#pragma once
#include "tkEngine/physics/tkMeshCollider.h"
#include "tkEngine/physics/tkRigidBody.h"
//#include "tkEngine/character/tkCharacterController.h"
class Enemybace : public IGameObject
{
public:
	Enemybace();
	virtual ~Enemybace();
	//bool Start();
	//void Update();
	//void Render(CRenderContext& rc);
	void OnDestroy();
	struct LevelData {
		int numMapChip;
		std::wstring modelFilePath;
		CVector3 Pos = CVector3::Zero;
		CVector3 scale = CVector3::One;
		CQuaternion Rotation = CQuaternion::Identity;
	};
	
	virtual void Build(const wchar_t* fileDataPath);
	//virtual void Create();
	virtual void Init(
		const wchar_t* modelFilePath,
		CVector3 pos,
		CQuaternion rotation,
		CVector3 scale) = 0;
	

		/*virtual void CharaConCreate(float r, float height, float gravity, CVector3 Pos,
			CCharacterController::ColliderType type);*/
	//template<class T> void SetInstance(T fn) {
	//	return NewGO<T>;
	//}

	struct Enemy {
		wchar_t* modelDataFilePath = nullptr;
		Enemybace* enemy = nullptr;
	};
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
	const std::list<LevelData*> GetDataList() {		
		return m_enemyDataList;
	}
protected:
	/*std::vector<Enemybace*> m_enemyMap;
	CCharacterController m_charaCon;*/
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
	std::list<LevelData*>	m_enemyDataList;

};
