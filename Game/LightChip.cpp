#include "stdafx.h"
#include "LightChip.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "tkEngine/light/tkPointLight.h"

LightChip::LightChip()
{
}


LightChip::~LightChip()
{
}
void LightChip::OnDestroy()
{
	for (auto ptLight : m_pointLightList)
	{
		DeleteGO(ptLight);
	}
}
void LightChip::Init(
	const wchar_t* modelDataFilePath,
	CVector3 pos,				//座標
	CVector3 color,				//カラー
	int distancedecay		//減衰距離
) {
	prefab::CPointLight* ptLight = NewGO<prefab::CPointLight>(0);
	//ポイントライトの座標を指定
	ptLight->SetPosition(pos);
	//ライトの方向を設定
	ptLight->SetColor(color);
	//ポイントライトの減衰パラメータを設定
	CVector3 attn = CVector3::Zero;
	attn.x = distancedecay;
	attn.y = 1.0f;
	ptLight->SetAttn(attn);
	//ポイントライトのリストに積む
	m_pointLightList.push_back(ptLight);
}
bool LightChip::Start()
{
	return true;
}
void LightChip::Update()
{
	//ポイントライトの座標を変更
	CVector3 addmove;
	addmove = CVector3::Zero;
	/*for (auto& pt : m_pointLightList)
	{
		CVector3 pos = pt->GetPosition();
		addmove.z = -10.0f;
		pos = pos + addmove;
		pt->SetPosition(pos);
	}*/
}