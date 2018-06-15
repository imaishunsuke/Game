#include "stdafx.h"
#include "GameOverProd.h"
#include "Player.h"
#include"GameCamera.h"


GameOverProd::GameOverProd()
{
}


GameOverProd::~GameOverProd()
{
}

bool GameOverProd::Start() {
	m_step = MoveCamera;
	m_pl = FindGO<Player>("Player");
	m_camera= FindGO<GameCamera>("gamecamera");
	return true;
}
void GameOverProd::Update() {
	switch (m_step)
	{
	//ˆ³Ž€ƒJƒƒ‰ˆÚ“®
	case MoveCamera:
		m_pl->SetLifeCount(5);
		//m_pl->lifecount = 5;
		if (m_camera->GetFlag()==2)
		{
			m_step = Diser;
		}
		break;
	case Diser:
		break;
	case Dead:
		m_pl->SetLifeCount(6);
		break;
	default:
		break;
	}
}