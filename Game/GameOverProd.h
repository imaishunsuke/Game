#pragma once

class Player;

class GameOverProd:public IGameObject
{
public:
	GameOverProd();
	~GameOverProd();
	bool Start();
	void Update();
	enum Product{
		MoveCamera,				//圧死時のカメラ移動処理
		Diser,					//圧死時のディザ係数
		
	};
	Product m_step;
	Player*m_pl = nullptr;
};

