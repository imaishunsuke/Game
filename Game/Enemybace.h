#pragma once
class Enemybace : public IGameObject
{
public:
	Enemybace();
	~Enemybace();

	CVector3 m_position;
	CQuaternion m_rotation;

};
