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
	m_goalpos = { 0.3f,0.0,192.1};
	m_goalpos1 = { 5.0,0.0,192.1};
	player = FindGO<Player>("Player");
	return true;
}
void Goal::Update() {
	if ((m_goalpos.x<=player->GetPosition().x
		&&player->GetPosition().x <=m_goalpos1.x)
		&&(m_goalpos.z <= player->GetPosition().z))
	{
		gflag = 1;
	}
	if (Pad(0).IsTrigger(enButtonStart) && gflag == 1)
	{
		TitleFlag = true;
	}
}
