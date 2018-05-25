#include "stdafx.h"
#include "Titlemirror.h"
#include "TitlePlayer.h"

Titlemirror::Titlemirror()
{
}


Titlemirror::~Titlemirror()
{
}

bool Titlemirror::Start()
{
	//ÉÇÉfÉãÇÉçÅ[Éh
	m_skinModelData.Load(L"modelData/mirror.cmo");
	m_skinModel.Init(m_skinModelData);
							 
	m_position.y = -14.5f;
	m_position.x = -21.0f;
	pl = FindGO<TitlePlayer>("TitlePlayer");
	return true;
}

void Titlemirror::Update()
{
	m_position = pl->m_position;
	m_position.z += -1;
	m_position.y += 2.0f;
	m_rotation.SetRotationDeg(CVector3::AxisY, -90);
	m_skinModel.Update(m_position, m_rotation, CVector3::One);
}

void Titlemirror::Render(CRenderContext& rc)
{
	if (pl->Flag == 1 && m_position.x < -10 && m_position.x > -25) {
		m_skinModel.Draw(rc,
			MainCamera().GetViewMatrix(),
			MainCamera().GetProjectionMatrix(),
			CMatrix::Identity,
			CMatrix::Identity,
			0
		);
	}
}