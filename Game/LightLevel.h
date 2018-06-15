#pragma once
#include "LightChip.h"

class LightLevel : public IGameObject
{
public:
	LightLevel();
	~LightLevel();
	/*
	ポイントライト構成
	ptlig_[ライト番号]_[ライトのr成分の強さ]_[ライトのg成分の強さ]_[ライトのb成分の強さ]_[減衰距離]
	*/
	void ptLightBuild(const wchar_t* lightDataFilePath);
/*
	ディレクションライト構成
		dlig_[ライト番号]_[ライトのr成分の強さ]_[ライトのg成分の強さ]_[ライトのb成分の強さ]
	*/
	void dirLightBuild(const wchar_t* dirlightDataFilePath);
private:
	//メンバ変数
	wchar_t degit[32];
	int lightnum;							//ライトナンバー
	CVector3 color = CVector3::Zero;		//カラー
	int distanceDecay;						//減衰距離
	LightChip* pointLig;
	std::list<LightChip*> m_ptLightList;	//ポイントライトのリスト
	std::list<LightChip*> m_dirLightList;	//ディレクションライトのリスト
};

