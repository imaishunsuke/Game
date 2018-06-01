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
	m_goalpos = { -5.0,0.0,239.2};
	m_goalpos1 = { 1.0,0.0,239.2};
	player = FindGO<Player>("Player");
	return true;
}
void Goal::Update() {
	if ((m_goalpos.x<=player->m_position.x
		&&player->m_position.x <=m_goalpos1.x)
		&&(m_goalpos.z <= player->m_position.z))
	{
		gflag = 1;
	}
}
