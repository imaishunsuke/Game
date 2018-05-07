#pragma once
class LightChip : public IGameObject
{
public:
	LightChip();
	~LightChip();
	void Init(
		const wchar_t* modelFilePath,
		CVector3 pos,				//座標
		CVector3 color,				//カラー
		int distancedecay				//減衰
		);
	bool Start() override;
	void Update();
	void OnDestroy();
	void InitPointLight();			//ポイントライトの初期化

	//メンバ変数
	std::vector<prefab::CPointLight*> m_pointLightList;		//ポイントライトのリスト
};

