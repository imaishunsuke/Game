#pragma once

class Player;
class GameCamera;
class GameOverProd:public IGameObject
{
public:
	GameOverProd();
	~GameOverProd();
	bool Start();
	void Update();
private:
	enum Product{
		MoveCamera,				//圧死時のカメラ移動処理
		Diser,					//圧死時のディザ係数
		Dead,
		
	};
	Product m_step;
	Player*m_pl = nullptr;
	GameCamera*m_camera = nullptr;
};

