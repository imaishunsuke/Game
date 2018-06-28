#include "stdafx.h"
#include "GameCamera.h"
#include "Goal.h"
#include "ResultScene.h"

GameCamera::GameCamera()
{
}


GameCamera::~GameCamera()
{
}

bool GameCamera::Start()
{
	testScene = FindGO<ResultScene>("Result");
	m_player = FindGO<Player>("Player");
	m_goal = FindGO<Goal>("Goal");
	//カメラのニアクリップとファークリップを設定する。
	MainCamera().SetTarget(m_player->GetPosition()/*{ 0.0f,-5.0f, -5.0f }*/);
	MainCamera().SetNear(1.0f);
	MainCamera().SetFar(1000.0f);
	CVector3 CamPos=CVector3::Zero;
	CamPos=m_player->GetPosition();
	CamPos.z -= 25.0f;
	//カメラのポジション
	MainCamera().SetPosition(CamPos/*{ 0.0f,-5.0f, -25.0f }*/);
	
	//ばねカメラの初期化。
	m_springCamera.Init(
		MainCamera(),		//ばねカメラの処理を行うカメラを指定する。
		500.0f,			//カメラの移動速度の最大値。
		true,				//カメラと地形とのあたり判定を取るかどうかのフラグ。trueだとあたり判定を行う。
		1.0f				//カメラに設定される球体コリジョンの半径。第３引数がtrueの時に有効になる。
	);
	MainCamera().SetUpdateProjMatrixFunc(CCamera::enUpdateProjMatrixFunc_Perspective);
	return true;
}
void GameCamera::Update()
{
	if (m_goal->GetGoalFlag() == 0 && testScene->GetResultFlag() == false/*&& m_player->PressFlag == 0*/) {							//ゴールしていないなら
		//m_player = FindGO<Player>("Player");
		CVector3 toCameraPos = CVector3::Zero;
		toCameraPos = m_springCamera.GetPosition() - m_springCamera.GetTarget();
		float height = toCameraPos.y;
		toCameraPos.y = 0.0f;
		float toCameraPosLen = toCameraPos.Length();
		toCameraPos.Normalize();
		CVector3 target = m_player->GetPosition();
		target.y += 10.0f;
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

		m_rot.MakeRotationFromQuaternion(qRot);

		//視点を計算する
		if (!(x == 0 && y == 0)) {
			pos = target + toNewCameraPos;
			m_springCamera.SetTarget(target);
			m_springCamera.SetPosition(pos);
		}
	}
	if (m_goal->GetGoalFlag()==1 ) {					//ゴール用カメラ
	//if(testScene->GetResultFlag() == true){
	//ばねカメラの初期化。
		if (ClearCameraFlag == false) {
			m_springCamera.Init(
				MainCamera(),		//ばねカメラの処理を行うカメラを指定する。
				500.0f,			//カメラの移動速度の最大値。
				false,				//カメラと地形とのあたり判定を取るかどうかのフラグ。trueだとあたり判定を行う。
				0.0f				//カメラに設定される球体コリジョンの半径。第３引数がtrueの時に有効になる。
			);
			ClearCameraFlag = true;
		}
		m_player->Result();

		float toPoslen = 2.5f; //ターゲットの場所を決めるための長さ
		CVector3 ForwordPos = CVector3::Zero;
		ForwordPos.x = m_player->GetMatrix().m[2][0]/* + m_player->GetPosition().x*/;
		ForwordPos.y = 0.0f;
		ForwordPos.z = m_player->GetMatrix().m[2][2]/* + m_player->GetPosition().z*/;
		CVector3 target = CVector3::Zero;
		target.Cross(CVector3::Up,ForwordPos);
		target.x = -target.x;
		target.y = -target.y;
		target.z = -target.z;
		target.Normalize();
		target.x *= toPoslen;
		target.y = 0.0f;
		target.z *= toPoslen;

		float toCameraPoslen = 9.5f;//カメラの位置を決めるための長さ
		//ForwordPos.Normalize();
		ForwordPos.x *= toCameraPoslen;
		ForwordPos.y = 4.0f;
		ForwordPos.z *= toCameraPoslen;
		CVector3 pos = CVector3::Zero;
		pos = target + ForwordPos + m_player->GetPosition();
		target.y = 3.0f;
		target.x = target.x+m_player->GetPosition().x;
		target.z = target.z+m_player->GetPosition().z;

		m_springCamera.SetTarget(target);
		m_springCamera.SetPosition(pos);
		m_springCamera.SetDampingRate(2.0f);
		//m_springCamera.SetFar(20.0f);
		m_springCamera.SetViewAngle(CMath::DegToRad(40.0f));
	}

	if (m_player->GetPressFlag() == 1 && testScene->GetResultFlag() == false)
	{
		if (Flag == 0) {
			CVector3 target = m_player->GetPosition();
			m_springCamera.SetTarget(target);
			CQuaternion qRot;
			qRot.SetRotationDeg(CVector3::AxisY, 150.0f);
			CVector3 toPos = m_springCamera.GetPosition() - m_springCamera.GetTarget();
			toPos.y = 0.0f;
			toPos.Normalize();
			qRot.Multiply(toPos);

			toPos *= 20.0f;
			CVector3 pos = target + toPos;
			pos.y = 20.0f;
			m_springCamera.SetPosition(pos);
			Flag = 1;
		}
		if (//m_springCamera.GetMoveSpeed().x <= 0.2
			/*&&*/ m_springCamera.GetMoveSpeed().y <= 0.2
			/*&& m_springCamera.GetMoveSpeed().z <= 0.2*/)
		{
			Flag = 2;
		}
	}
	//バネカメラの更新。
	m_springCamera.Update();
}