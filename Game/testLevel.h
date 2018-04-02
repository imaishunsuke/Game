#pragma once

#include "testMapChip.h"

class testLevel
{
public:
	testLevel();
	~testLevel();
	//レベルの構築
	void Build(const wchar_t* levelDataFilePath);

	//メンバ変数
	std::list<testMapChip*> m_mapChipList;		//マップチップ
};

