#define _CRT_NON_CONFORMING_SWPRINTFS
#include "stdafx.h"
#include "LightLevel.h"
#include "LightChip.h"
#include "tkEngine/util/tkLocData.h"
#include <locale.h>

LightLevel::LightLevel()
{
}


LightLevel::~LightLevel()
{
	for (auto& pointLig : m_ptLightList) {
		DeleteGO(pointLig);
	}
	/*for (auto& directionLig : m_dirLightList) {
		DeleteGO(directionLig);
	}*/
}

//ライトの作成
//lightDataFilePath　読み込むライトデータのファイルパス
void LightLevel::ptLightBuild(const wchar_t* lightDataFilePath)
{
	CLocData ligLoc;
	ligLoc.Load(lightDataFilePath);
	const wchar_t* boneName;
	wchar_t modelDataFilePath[256];
	for (int i = 0; i < ligLoc.GetNumObject(); i++) {
		boneName = ligLoc.GetObjectName(i);
		swprintf(modelDataFilePath,boneName);
		int j = 0;
		int count = 0;
		int DiscoveryCnt = 0;			//指定した文字を発見した
		while (modelDataFilePath[count] != NULL)
		{
			if (modelDataFilePath[count] == '[') {
				count++;
				while (modelDataFilePath[count] != ']') {
					degit[j] = modelDataFilePath[count];
					count++;
					j++;
				}
			}
			if (modelDataFilePath[count] == ']')
			{
				DiscoveryCnt++;
			}
			if (DiscoveryCnt == 1) {
				for (int i = 0; i < j; i++) {
					lightnum = _wtoi(degit);
				}
			}
			if (DiscoveryCnt == 2) {
				for (int i = 0; i < j; i++) {
					color.x = _wtoi(degit);
				}
			}
			if (DiscoveryCnt == 3) {
				for (int i = 0; i < j; i++) {
					color.y = _wtoi(degit);
				}
			}
			if (DiscoveryCnt == 4) {
				for (int i = 0; i < j; i++) {
					color.z = _wtoi(degit);
				}
			}
			if (DiscoveryCnt == 5) {
				for (int i = 0; i < j; i++) {
					distanceDecay = _wtoi(degit);
				}
			}
			count++;
			j = 0;
		}
	 pointLig = NewGO<LightChip>(0, "LightChip");
		pointLig->ptLightInit(lightDataFilePath,lightnum,ligLoc.GetObjectPosition(i),color,distanceDecay);
		m_ptLightList.push_back(pointLig);
	}
	//size_t wLen = 0;
	//char string[256];
	////ソフトで使用する言語を日本語に設定
	//setlocale(LC_ALL, "japanese");
	////wchar型をchar型に変換
	//wcstombs_s(&wLen, string, 255, lightDataFilePath, _TRUNCATE);
	//配置データとしてスケルトン使用
	//CSkeleton skeleton;
	//skeleton.Load(lightDataFilePath);
	//int numLight = skeleton.GetNumBones();
	//for (int i = 1; i < numLight; i++) {
	//	CBone* bone = skeleton.GetBone(i);
	//	//ボーンから平行移動、回転を取得
	//	CVector3 position, scale;
	//	CQuaternion rotation;
	//	bone->CalcWorldTRS(position, rotation, scale);
	//	//3dsMaxと軸が違うので、補正を入れる
	//	float w = position.y;
	//	position.y = position.x;
	//	position.z = -w;

	//	w = rotation.y;
	//	rotation.y = rotation.z;
	//	rotation.z = -w;
	//	rotation.SetRotationDeg(CVector3::AxisY, 90.0f);
	//	//ボーン名からモデルデータのファイルパスを作成
	//	const wchar_t* boneName = bone->GetName();
	//	wchar_t modelDataFilePath[256];
	//	swprintf(modelDataFilePath, L"modelData/%s.cmo", boneName);
	//	int j = 0;
	//	int count = 0;
	//	int DiscoveryCnt = 0;			//指定した文字を発見した
	//	while (modelDataFilePath[count] != NULL)
	//	{
	//		if (modelDataFilePath[count] == '[') {
	//			count++;
	//			while (modelDataFilePath[count] != ']') {
	//				degit[j] = modelDataFilePath[count];
	//				count++;
	//				j++;
	//			}
	//		}
	//		if (modelDataFilePath[count] == ']')
	//		{
	//			DiscoveryCnt++;
	//		}
	//		if (DiscoveryCnt == 1) {
	//			for (int i = 0; i < j; i++) {
	//				lightnum = _wtoi(degit);
	//			}
	//		}
	//		if (DiscoveryCnt == 2) {
	//			for (int i = 0; i < j; i++) {
	//				color.x = _wtoi(degit);
	//			}
	//		}
	//		if (DiscoveryCnt == 3) {
	//			for (int i = 0; i < j; i++) {
	//				color.y = _wtoi(degit);
	//			}
	//		}
	//		if (DiscoveryCnt == 4) {
	//			for (int i = 0; i < j; i++) {
	//				color.z = _wtoi(degit);
	//			}
	//		}
	//		if (DiscoveryCnt == 5) {
	//			for (int i = 0; i < j; i++) {
	//				distanceDecay = _wtoi(degit);
	//			}
	//		}
	//		count++;
	//		j = 0;
	//	}
	//	LightChip* lightChip = NewGO<LightChip>(0, "LightChip");
	//	lightChip->ptLightInit(modelDataFilePath, position, color,distanceDecay);
	//	m_ptLightList.push_back(lightChip);
	//}
}
void LightLevel::dirLightBuild(const wchar_t* dirlightDataFilePath)
{
	CLocData ligLoc;
	ligLoc.Load(dirlightDataFilePath);
	const wchar_t* boneName;
	wchar_t modelDataFilePath[256];
	for (int i = 0; i < ligLoc.GetNumObject(); i++) {
		boneName = ligLoc.GetObjectName(i);
		swprintf(modelDataFilePath, boneName);
		int j = 0;
		int count = 0;
		int DiscoveryCnt = 0;			//指定した文字を発見した
		while (modelDataFilePath[count] != NULL)
		{
			if (modelDataFilePath[count] == '[') {
				count++;
				while (modelDataFilePath[count] != ']') {
					degit[j] = modelDataFilePath[count];
					count++;
					j++;
				}
			}
			if (modelDataFilePath[count] == ']')
			{
				DiscoveryCnt++;
			}
			if (DiscoveryCnt == 1) {
				for (int i = 0; i < j; i++) {
					lightnum = _wtoi(degit);
				}
			}
			if (DiscoveryCnt == 2) {
				for (int i = 0; i < j; i++) {
					color.x = _wtoi(degit);
				}
			}
			if (DiscoveryCnt == 3) {
				for (int i = 0; i < j; i++) {
					color.y = _wtoi(degit);
				}
			}
			if (DiscoveryCnt == 4) {
				for (int i = 0; i < j; i++) {
					color.z = _wtoi(degit);
				}
			}
			count++;
			j = 0;
		}
		LightChip* directionLig = NewGO<LightChip>(0, "LightChip");
		directionLig->dirLightInit(dirlightDataFilePath,lightnum,ligLoc.GetObjectRotation(i), color);
		//m_dirLightList.push_back(directionLig);
	}
}