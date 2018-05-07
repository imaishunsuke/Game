#define _CRT_NON_CONFORMING_SWPRINTFS
#include "stdafx.h"
#include "DirectionLight.h"
#include "LightChip.h"
#include <locale.h>

DirectionLight::DirectionLight()
{
}


DirectionLight::~DirectionLight()
{
	for (auto& lightChip : m_LightList) {
		DeleteGO(lightChip);
	}
}

//ライトの作成
//lightDataFilePath　読み込むライトデータのファイルパス
void DirectionLight::LightBuild(const wchar_t* lightDataFilePath)
{
	//size_t wLen = 0;
	//char string[256];
	////ソフトで使用する言語を日本語に設定
	//setlocale(LC_ALL, "japanese");
	////wchar型をchar型に変換
	//wcstombs_s(&wLen, string, 255, lightDataFilePath, _TRUNCATE);
	//配置データとしてスケルトン使用
	CSkeleton skeleton;
	skeleton.Load(lightDataFilePath);
	int numLight = skeleton.GetNumBones();
	for (int i = 1; i < numLight; i++) {
		CBone* bone = skeleton.GetBone(i);
		//ボーンから平行移動、回転を取得
		CVector3 position, scale;
		CQuaternion rotation;
		bone->CalcWorldTRS(position, rotation, scale);
		//3dsMaxと軸が違うので、補正を入れる
		float w = position.y;
		position.y = position.x;
		position.z = -w;

		w = rotation.y;
		rotation.y = rotation.z;
		rotation.z = -w;
		rotation.SetRotationDeg(CVector3::AxisY, 90.0f);
		//ボーン名からモデルデータのファイルパスを作成
		const wchar_t* boneName = bone->GetName();
		wchar_t modelDataFilePath[256];
		swprintf(modelDataFilePath, L"modelData/%s.cmo", boneName);
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
		LightChip* lightChip = NewGO<LightChip>(0, "LightChip");
		lightChip->Init(modelDataFilePath, position, color,distanceDecay);
		m_LightList.push_back(lightChip);
	}
}