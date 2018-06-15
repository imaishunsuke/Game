#include "stdafx.h"
#include "GameOverProd.h"
#include "Player.h"
#include"GameCamera.h"
#include "tkEngine/sound/tkSoundSource.h"


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
	m_animeSound = NewGO<prefab::CSoundSource>(0);
	return true;
}
void GameOverProd::Update() {
	switch (m_step)
	{
	//圧死カメラ移動
	case MoveCamera:
		m_pl->SetLifeCount(5);
		//m_pl->lifecount = 5;
		if (m_camera->GetFlag() == 2)
		{
			m_step = Diser;
		}
		break;
	case Diser:
		if (soundf == 0) {
			//キャーと言うサウンド
			m_animeSound->Init("sound/si.wav");
			m_animeSound->SetVolume(2.0f);
			m_animeSound->Play(false);
			soundf = 1;
		}
		break;
	case Dead:
		m_pl->SetLifeCount(6);
		break;
	default:
		break;
	}
}