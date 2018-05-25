#include "stdafx.h"
#include "TitlePlayer.h"
//#include "titlecamera.h"

TitlePlayer::TitlePlayer()
{
}


TitlePlayer::~TitlePlayer()
{
}

bool TitlePlayer::Start()
{
	//プレイヤーモデルをロード
	m_skinModelData.Load(L"modelData/unityChan.cmo");
	m_skinModel.Init(m_skinModelData);

	//鏡のモデルロード
	//m_skinModelmirror.Load(L"modelData/.cmo");
	//m_skinModelmirror.Init(m_skinModelData);

	//m_taitlecamera = FindGO<titlecamera>("titlecamera");
	//プレイヤーの初期位置
	m_position.y = -18.0f; 
	m_position.x = -20.0f;
	CQuaternion qRot;
	m_rotation.SetRotationDeg(CVector3::AxisY, 90);
	

	return true;
}

void TitlePlayer::Update()
{
	if (m_position.x <= 40 && Flag == 0) {
		m_position.x += 0.2f;
		m_rotation.SetRotationDeg(CVector3::AxisY, 90);
	}
	if (m_position.x >- 40 && Flag==1)
	{
		m_rotation.SetRotationDeg(CVector3::AxisY, -90);
		m_position.x -= 0.2f;
	}
	//Flag管理
	if (m_position.x >= 40){
		Flag = 1;
	}
	else if (m_position.x <= -40) {
		Flag = 0;
	}
	m_skinModel.Update(m_position, m_rotation, CVector3::One);
	//m_positionmirror.z = 1;
	//m_skinModelmirror.Update(m_positionmirror, m_rotation, CVector3::One);
}

void TitlePlayer::Render(CRenderContext& rc)
{
	int alphaflag = 0;
	m_skinModel.Draw(rc,
		MainCamera().GetViewMatrix(),
		MainCamera().GetProjectionMatrix(),
		CMatrix::Identity,
		CMatrix::Identity,
		alphaflag
	);

	//m_skinModelmirror.Draw(rc,
	//	MainCamera().GetViewMatrix(),
	//	MainCamera().GetProjectionMatrix(),
	//	CMatrix::Identity,
	//	CMatrix::Identity,
	//	0
	//);
}
