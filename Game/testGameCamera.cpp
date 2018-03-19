#include "stdafx.h"
#include "testGameCamera.h"


testGameCamera::testGameCamera()
{
}


testGameCamera::~testGameCamera()
{
}
bool testGameCamera::Start()
{
	m_toCameraPos.Set(0.0f, 15.0f, 50.0f);
	/*m_springCamera.SetPosition({ 0.0f,15.0f,50.0f });
	m_springCamera.SetTarget({ 0.0f,15.0f,0.0f });*/
	//ミラーのインスタンスを探す
	m_mirror = FindGO<testMirror>("testMirror");
	//springCamera.SetTarget(m_mirror->m_position);
	MainCamera().SetNear(1.0f);
	MainCamera().SetFar(1000.0f);
	MainCamera().SetPosition({ 0.0f, 25.0f, 70.0f });
	MainCamera().SetTarget({ 0.0f,15.0f,0.0f });
	//ばねカメラの初期化
	m_springCamera.Init(
		MainCamera(),
		1000.0f,
		true,
		5.0f
	);
	return true;
};
void testGameCamera::Update()
{
	
	CVector3 toCameraPos = CVector3::Zero;
	toCameraPos = m_springCamera.GetPosition() - m_springCamera.GetTarget();
	float height = toCameraPos.y;
	toCameraPos.y = 0.0f;
	float toCameraPosLen = toCameraPos.Length();
	toCameraPos.Normalize();
	CVector3 target = m_mirror->m_position;
	target.y += 15.0f;
	CVector3 toNewCameraPos = CVector3::Zero;
	toNewCameraPos = m_springCamera.GetPosition() - target;
	toNewCameraPos.y = 0.0f;
	float toNewCameraPosLen = toNewCameraPos.Length();
	toNewCameraPos.Normalize();

	//ちょっとずつ追尾
	float weight = 0.8f;
	toNewCameraPos = toNewCameraPos * weight + toCameraPos * (1.0f - weight);
	toNewCameraPos.Normalize();
	toNewCameraPos.x *= toCameraPosLen;
	toNewCameraPos.y *= toCameraPosLen;
	toNewCameraPos.z *= toCameraPosLen;
	toNewCameraPos.y = height;
	CVector3 pos = target + toNewCameraPos;
	m_springCamera.SetTarget(target);
	m_springCamera.SetPosition(pos);
	m_springCamera.Update();
}