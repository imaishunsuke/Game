#include "stdafx.h"
#include "TitleEnemyball.h"


TitleEnemyball::TitleEnemyball()
{
}


TitleEnemyball::~TitleEnemyball()
{
}

bool TitleEnemyball::Start()
{
	//モデルをロード
	m_skinModelData.Load(L"modelData/EnemyBall.cmo");
	m_skinModel.Init(m_skinModelData);

	m_scale = m_scale * 0.1f; // 大きさの設定

	//玉の初期位置
	m_position.y = -14.0f;
	m_position.x = -30.0f;
	return true;
}

void TitleEnemyball::Update()
{
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisZ, -15.0f);
	m_rotation.Multiply(qRot);

	m_position.x += 0.2f ;
	m_skinModel.Update(m_position, m_rotation , m_scale);
}

void TitleEnemyball::Render(CRenderContext& rc)
{
	int alphaflag = 0;
	m_skinModel.Draw(rc,
		MainCamera().GetViewMatrix(),
		MainCamera().GetProjectionMatrix(),
		CMatrix::Identity,
		CMatrix::Identity,
		alphaflag
	);
}
