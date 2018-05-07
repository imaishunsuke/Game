#pragma once
class LightChip : public IGameObject
{
public:
	LightChip();
	~LightChip();
	void ptLightInit(
		const wchar_t* modelFilePath,
		CVector3 pos,				//座標
		CVector3 color,				//カラー
		int distancedecay				//減衰
	);
	void dirLightInit(
		const wchar_t* modelFilePath,
		CVector3 color
		);
	bool Start() override;
	void Update();
	void OnDestroy();

	//メンバ変数
	std::vector<prefab::CPointLight*> m_pointLightList;		//ポイントライトのリスト
	std::vector<prefab::CDirectionLight*>	m_directionLightList;	//ディレクションライトのリスト
};

