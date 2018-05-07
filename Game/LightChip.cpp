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
	for (auto dirLight : m_directionLightList);
}
void LightChip::ptLightInit(
	const wchar_t* modelDataFilePath,
	CVector3 pos,				//座標
	CVector3 color,				//カラー
	int distancedecay		//減衰距離
) {
	prefab::CPointLight* ptLight = NewGO<prefab::CPointLight>(0);
	//ポイントライトの座標を指定
	ptLight->SetPosition(pos);
	//ライトのカラーを設定
	ptLight->SetColor(color);
	//ポイントライトの減衰パラメータを設定
	CVector3 attn = CVector3::Zero;
	attn.x = distancedecay;
	attn.y = 1.0f;
	ptLight->SetAttn(attn);
	//ポイントライトのリストに積む
	m_pointLightList.push_back(ptLight);
}
void LightChip::dirLightInit(
	const wchar_t* modelFilePath,
	CVector3 color
	) {
	prefab::CDirectionLight* dirLight;
	dirLight = NewGO<prefab::CDirectionLight>(0);
	//ライトの方向を設定
	dirLight->SetDirection({ 0.707f,-0.707f,0.0f });
	//ライトの色を設定
	dirLight->SetColor(color);
	GraphicsEngine().GetShadowMap().SetLightDirection({ 0.0,-1.0f,0.0f });
	m_directionLightList.push_back(dirLight);
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