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
	/*for (auto ptLight : m_pointLightList)
	{
		DeleteGO(ptLight);
	}
	for (auto dirLight : m_directionLightList);*/
}
void LightChip::ptLightInit(
	const wchar_t* modelDataFilePath,
	int number,
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
	auto it = m_ptLightMap.find(number);
	if (it == m_ptLightMap.end()) {
		m_ptLightMap.insert({ number,ptLight });
	}

	//m_pointLightList.push_back(ptLight);
}
void LightChip::dirLightInit(
	const wchar_t* modelFilePath,
	int number,
	CQuaternion rotation,
	CVector3 color
	) {
	prefab::CDirectionLight* dirLight;
	dirLight = NewGO<prefab::CDirectionLight>(0);
	CVector3 direction;
	CMatrix rot;
	//クォータニオンからオイラー角を抽出
	rot.MakeRotationFromQuaternion(rotation);
	float sinX;
	sinX = rot.m[2][1];
	if (!(fabsf(sinX) == 1)) {
		direction.x = asinf(rot.m[2][1]);
		direction.y = atan2f(-rot.m[2][0], rot.m[2][2]);
		direction.z = atan2f(-rot.m[0][1], rot.m[1][1]);
	}
	else if (sinX == 1) {
		direction.x = CMath::PI / 2.0f;
		direction.y = 0.0f;
		direction.z = atan2f(rot.m[1][0],rot.m[0][0]);
	}
	else if (sinX == -1) {
		direction.x = -CMath::PI / 2.0f;
		direction.y = 0.0f;
		direction.z = atan2f(rot.m[1][0], rot.m[0][0]);
	}
	//direction = Multiply(CVector4 rotation);
	//ライトの方向を設定
	dirLight->SetDirection(direction);
	//ライトの色を設定
	dirLight->SetColor(color);
	GraphicsEngine().GetShadowMap().SetLightDirection({ 0.0,-1.0f,0.0f });
	auto it = m_dirLightMap.find(number);
	if (it == m_dirLightMap.end()) {
		m_dirLightMap.insert({ number,dirLight });
	}
	//m_directionLightList.push_back(dirLight);
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
	//ライトの調整方法---------------------------------------------
	//auto it = m_ptLightMap.find(00);
	//prefab::CPointLight* pt;
	////ライトのナンバーは００～　始まる
	//pt = GetptLight(00);
	//pt->SetColor({ 0.0f,0.0f,0.0f,1.0f });
	//--------------------------------------------------------------
	/*for (auto& pt : m_pointLightList)
	{
		CVector3 pos = pt->GetPosition();
		addmove.z = -10.0f;
		pos = pos + addmove;
		pt->SetPosition(pos);
	}*/
}
prefab::CPointLight* LightChip::GetptLight(int num)
{
	auto it = m_ptLightMap.find(num);
	if (it == m_ptLightMap.end()) {
		return NULL;
	}	
	return it->second;
}
prefab::CDirectionLight* LightChip::GetdirLight(int num)
{
	auto it = m_dirLightMap.find(num);
	if (it == m_dirLightMap.end()) {
		return NULL;
	}
	return it->second;
}