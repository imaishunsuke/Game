#include "stdafx.h"
#include "GameOverProd.h"
#include "Player.h"


GameOverProd::GameOverProd()
{
}


GameOverProd::~GameOverProd()
{
}

bool GameOverProd::Start() {
	m_step = MoveCamera;
	m_pl = FindGO<Player>("Player");
	return true;
}
void GameOverProd::Update() {
	switch (m_step)
	{
	//圧死カメラ移動
	case MoveCamera:
		m_pl->lifecount = 5;
		break;
	default:
		break;
	}
}