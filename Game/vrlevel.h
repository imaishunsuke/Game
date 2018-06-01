#pragma once
#include"vrMapChip.h"
class vrlevel
{
public:
	vrlevel();
	~vrlevel();

	//レベル構成
	void Build(const wchar_t*levelDataFilePath);

	//メンバ変数
	std::list<vrMapChip*>m_mapChipList;		//マップチップのリスト
};