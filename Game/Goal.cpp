#include "stdafx.h"
#include "Goal.h"
#include "Player.h"


Goal::Goal()
{
}


Goal::~Goal()
{
}

bool Goal::Start() {
	m_goalpos = { 68.0,0.0,88.0 };
	m_goalpos1 = { 91.0,0.0,88.0 };
	player = FindGO<Player>("Player");
	return true;
}
void Goal::Update() {
	//CVector3 diff=CVector3::Zero;
	//diff = m_goalpos - player->m_position;
	//len = diff.Length();
	/*if (len < 5.0) {
		gfla = 1;
	}*/
	if ((m_goalpos.x<=player->m_position.x
		&&player->m_position.x <=m_goalpos1.x)
		&&(m_goalpos.z <= player->m_position.z))
	{
		gfla = 1;
	}
}
void Goal::Render(CRenderContext& rc) {

}