#pragma once
class  Player;
class Goal :public IGameObject
{
public:
	Goal();
	~Goal();
	bool Start();
	void Update();
	int GetGoalFlag() {
		return gflag;
	}
private:
	CVector3 m_goalpos = CVector3::Zero;				//座標。
	CVector3 m_goalpos1 = CVector3::Zero;				//座標。
	Player* player = nullptr;
	int gflag = 0;										//ゴールフラグ
};

