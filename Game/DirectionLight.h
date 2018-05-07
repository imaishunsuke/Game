#pragma once
#include "LightChip.h"

class DirectionLight : public IGameObject
{
public:
	DirectionLight();
	~DirectionLight();
	
	void LightBuild(const wchar_t* lightDataFilePath);

	std::list<LightChip*> m_LightList;
	/*
	ディレクションライト構成
		dlig_[ライト番号]_[ライトのr成分の強さ]_[ライトのg成分の強さ]_[ライトのb成分の強さ]
	*/
	//メンバ変数
	wchar_t degit[32];
	int lightnum;							//ライトナンバー
	CVector3 color = CVector3::Zero;		//カラー
	int distanceDecay;						//減衰距離
};

