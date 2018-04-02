#include "stdafx.h"
#include "GameCamera.h"


GameCamera::GameCamera()
{
}


GameCamera::~GameCamera()
{
}

bool GameCamera::Start()
{
	m_player = FindGO<Player>("Player");

	//カメラのニアクリップとファークリップを設定する。
	MainCamera().SetTarget({ 0.0f,-5.0f, -5.0f });
	MainCamera().SetNear(1.0f);
	MainCamera().SetFar(1000.0f);
	MainCamera().SetPosition({ 0.0f,-5.0f, -25.0f });
	
	//ばねカメラの初期化。
	m_springCamera.Init(
		MainCamera(),		//ばねカメラの処理を行うカメラを指定する。
		1000.0f,			//カメラの移動速度の最大値。
		true,				//カメラと地形とのあたり判定を取るかどうかのフラグ。trueだとあたり判定を行う。
		5.0f				//カメラに設定される球体コリジョンの半径。第３引数がtrueの時に有効になる。
	);
	return true;
}
void GameCamera::Update()
{
	m_player = FindGO<Player>("Player");
	CVector3 toCameraPos = CVector3::Zero;
	toCameraPos = m_springCamera.GetPosition() - m_springCamera.GetTarget();
	float height = toCameraPos.y;
	toCameraPos.y = 0.0f;
	float toCameraPosLen = toCameraPos.Length();
	toCameraPos.Normalize();
	CVector3 target = m_player->m_position;
	target.y += 10.0f;
	CVector3 toNewCameraPos = CVector3::Zero;
	toNewCameraPos = m_springCamera.GetPosition() - target;
	toNewCameraPos.y = 0.0f;
	float toNewCameraPosLen = toNewCameraPos.Length();
	toNewCameraPos.Normalize();

	//ちょっとずつ追尾
	float weight = 3.0f;
	toNewCameraPos = toNewCameraPos * weight + toCameraPos * (1.0f - weight);
	toNewCameraPos.Normalize();
	toNewCameraPos.x *= toCameraPosLen;
	toNewCameraPos.y *= toCameraPosLen;
	toNewCameraPos.z *= toCameraPosLen;
	toNewCameraPos.y = height;
	CVector3 pos = target + toNewCameraPos;
	m_springCamera.SetTarget(target);
	m_springCamera.SetPosition(pos);
	CVector3 toCameraPosOld = toNewCameraPos;
	//パッドの入力を使ってカメラを回す
	float x = Pad(0).GetRStickXF();
	float y = Pad(0).GetRStickYF();
	//Y軸周りの回転
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY, 2.0f*x);
	qRot.Multiply(toNewCameraPos);
	//x軸周りの回転
	CVector3 axisX;
	axisX.Cross(CVector3::AxisY, toNewCameraPos);
	axisX.Normalize();
	//任意の軸に回転させる
	qRot.SetRotationDeg(axisX, 2.0f*y);
	qRot.Multiply(toNewCameraPos);
	//カメラの回転の上限を設定
	CVector3 toPosDir = toNewCameraPos;
	toPosDir.Normalize();
	if (toPosDir.y < -0.5f) {
		//カメラの上を制御
		toNewCameraPos = toCameraPosOld;
	}
	else if (toPosDir.y > 0.8f) {
		//カメラの下を制御
		toNewCameraPos = toCameraPosOld;
	}
	pos = CVector3::Zero;
	//視点を計算する
	if (!(x == 0 && y == 0)) {
		pos = target + toNewCameraPos;
		m_springCamera.SetTarget(target);
		m_springCamera.SetPosition(pos);
	}
	////バネカメラの更新。
	m_springCamera.Update();
}