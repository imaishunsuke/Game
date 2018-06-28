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

	int GetDiser() {
		return Diser;
	}
	int GetStep() {
		return m_step;
	}
	void SetDeadStep() {
		m_step=Dead;
	}
private:
	enum Product{
		MoveCamera,				//圧死時のカメラ移動処理
		Diser,					//圧死時のディザ係数
		Dead,
		
	};
private:
	Product m_step;
	Player*m_pl = nullptr;
	GameCamera*m_camera = nullptr;
public:
	void SetProduct(Product product) {
		m_step = product;
	}
	prefab::CSoundSource* m_animeSound = nullptr;
	int soundf = 0;
};

