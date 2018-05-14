#pragma once
#include "tkEngine/light/tkDirectionLight.h"
#include "tkEngine/light/tkPointLight.h"
class LightChip : public IGameObject
{
public:
	LightChip();
	~LightChip();
	void ptLightInit(
		const wchar_t* modelFilePath,
		int number,
		CVector3 pos,				//座標
		CVector3 color,				//カラー
		int distancedecay				//減衰
	);
	void dirLightInit(
		const wchar_t* modelFilePath,
		int number,
		CQuaternion rotation,
		CVector3 color
		);
	prefab::CDirectionLight* GetdirLight(int num);
	prefab::CPointLight* GetptLight(int num);

	bool Start() override;
	void Update();
	void OnDestroy();

	//メンバ変数
	//std::list<prefab::CPointLight*> m_pointLightList;		//ポイントライトのリスト
	//std::list<prefab::CDirectionLight*>	m_directionLightList;	//ディレクションライトのリスト
	std::map<int,prefab::CPointLight*> m_ptLightMap;
	std::map<int, prefab::CDirectionLight*> m_dirLightMap;
};

