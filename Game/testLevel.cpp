#include "stdafx.h"
#include "testLevel.h"
#include "testMapChip.h"

testLevel::testLevel()
{
}


testLevel::~testLevel()
{
	for (auto& testmapChip : m_mapChipList) {
		DeleteGO(testmapChip);
	}
}
//レベルの作成
//levelDataFilePath 読み込むレベルデータのファイルパス
void testLevel::Build(const wchar_t* levelDataFilePath)
{
	//今回は配置データとしてスケルトンを利用する
	CSkeleton skeleton;
	skeleton.Load(levelDataFilePath);
	int numMapChip = skeleton.GetNumBones();
	for (int i = 1; i < numMapChip; i++) {
		CBone* bone = skeleton.GetBone(i);
		//ボーンから拡大率、平行移動、回転を取得する
		CVector3 position, scale;
		CQuaternion rotation;
		bone->CalcWorldTRS(position, rotation, scale);
		float w = position.y;
		position.y = position.z;
		position.z = -w;

		w = rotation.y;
		rotation.y = rotation.z;
		rotation.z = -w;

		//ボーン名からモデルデータのファイルパスを作成する
		const wchar_t* boneName = bone->GetName();
		wchar_t modelDataFilePath[256];
		swprintf(modelDataFilePath, L"modelData/%s.cmo", boneName);
		testMapChip* testmapChip = NewGO<testMapChip>(0);
		testmapChip->Init(modelDataFilePath, position, CVector3::One, rotation);
		m_mapChipList.push_back(testmapChip);
	}
}

