#include "stdafx.h"
#include "vrlevel.h"
#include "vrMapChip.h"


vrlevel::vrlevel()
{
}


vrlevel::~vrlevel()
{
	for (auto& mapChip : m_mapChipList) {
		DeleteGO(mapChip);
	}
}

//レベル作成
void vrlevel::Build(const wchar_t*levelDataaFilePath) {
	//スケルトン利用して配置
	CSkeleton skelton;
	skelton.Load(levelDataaFilePath);
	int numMapChip = skelton.GetNumBones();
	for (int i = 1; i < numMapChip; i++)
	{
		CBone*bone = skelton.GetBone(i);
		//ボーンから拡大率、平行移動、回転を取得する。
		CVector3 position, scale;
		CQuaternion rotation;
		bone->CalcWorldTRS(position, rotation, scale);
		//軸補正を入れる。
		float t = position.y;
		position.y = position.z;
		position.z = -t;
		t = rotation.y;
		rotation.y = rotation.z;
		rotation.z = -t;
		//ボーン名からモデルデータのファイルパスを作成する。
		const wchar_t* boneName = bone->GetName();
		wchar_t modelDataFilePath[256];
		swprintf(modelDataFilePath, L"modelData/%s.cmo", boneName);
		vrMapChip* vrmapChip = NewGO<vrMapChip>(0);
		vrmapChip->Init(modelDataFilePath, position, CVector3::One, rotation);
		m_mapChipList.push_back(vrmapChip);
	}
}