#pragma once

//class TitlePlayer;

class titlecamera : public IGameObject
{
public:
	titlecamera();
	~titlecamera();
	bool Start();
	void Update();
private:
	CVector3 m_toCameraPos = CVector3::Zero;
	CVector3 pos = CVector3::Zero;
	//TitlePlayer* tplayer = nullptr; 
};

