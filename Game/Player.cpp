#include "stdafx.h"
#include "Player.h"
//#include"Torokko.h"
#include"Mirror.h"
#include"Goal.h"
#include"Game.h"

Player::Player()
{
}


Player::~Player()
{
}

bool Player::Start() {
	{
		//モデルデータのロード
		m_skinModelData.Load(L"modelData/unityChan.cmo");
		m_skinModel.Init(m_skinModelData);
		////法線マップとスペキュラマップをロード
		//m_specularMap.CreateFromDDSTextureFromFile(L"sprite/utc_spec.dds");
		//m_normalMap.CreateFromDDSTextureFromFile(L"sprite/utc_normal.dds");
		//m_skinModel.FindMaterial([&](auto material) {
		//	material->SetNormalMap(m_normalMap.GetBody());
		//	//material->SetSpecularMap(m_specularMap.GetBody());
		//});
		m_rotation.Multiply(m_rotation);
		m_goal = FindGO<Goal>("Goal");
			//hpテクスチャ
			m_htexture.CreateFromDDSTextureFromFile(L"sprite/hp.dds");
			m_hsprite.Init(m_htexture, 460, 40);
			//hpdテクスチャ
			m_hdtexture.CreateFromDDSTextureFromFile(L"sprite/hpd.dds");
			m_hdsprite.Init(m_hdtexture, 460, 40);
			//hp barテクスチャ
			m_hbtexture.CreateFromDDSTextureFromFile(L"sprite/hpmp_bar.dds");
			m_hbsprite.Init(m_hbtexture, 490, 70);
			m_mirror = FindGO<Mirror>("Mirror");
			//toro = FindGO<Torokko>("Trokko");
			m_goal = FindGO<Goal>("Goal");
			//m_position = toro->m_position;


			m_charaCon.Init(
				3.0,		//半径
				1.0f,		//高さ
				0,
				m_position,	//初期位置
				m_collidertype
			);
			flag = 0;
			count = 0;
			scale = 3.0f;
			m_gpos = { 0.0,0.0,5.0 };
			m_mirror = FindGO<Mirror>("Mirror");
			/*toro = FindGO<Torokko>("Trokko");*/
			
			/*m_position = toro->m_position;
			diff.x = toro->m_gpos.x - toro->m_position.x;
			diff.y = toro->m_gpos.y - toro->m_position.y;
			diff.z = toro->m_gpos.z - toro->m_position.z;
			plposlen=diff.Length();*/
			m_skinModel.Update(m_position, m_rotation, CVector3::One);
			m_skinModel.SetShadowCasterFlag(true);
		}
	

		return true;
	
}
void Player::Move() {
	//m_moveSpeed.y -= 98.0f * GameTime().GetFrameDeltaTime();					//重力　変更する
	
	//左スティックの入力量を受け取る。
	float lStick_x = Pad(0).GetLStickXF();
	float lStick_y = Pad(0).GetLStickYF();
	//カメラの前方方向と右方向を取得。
	CVector3 cameraForward = MainCamera().GetForward();
	CVector3 cameraRight = MainCamera().GetRight();
	//XZ平面での前方方向、右方向に変換する。
	cameraForward.y = 0.0f;
	cameraForward.Normalize();
	cameraRight.y = 0.0f;
	cameraRight.Normalize();
	//XZ成分の移動速度をクリア。
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	m_moveSpeed += cameraForward * lStick_y * 100.0f;	//奥方向への移動速度を代入。
	m_moveSpeed += cameraRight * lStick_x * 100.0f;		//右方向への移動速度を加算。
	if (Pad(0).IsTrigger(enButtonA) && m_charaCon.IsOnGround() == true) {
		m_moveSpeed.y += 98.0f;
	}

	if (ChangeFlag == 1) {
		m_charaCon.SetGravity(-224);
	}
		m_position = m_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_moveSpeed, m_collidertype);
}
void Player::Rotation() {

	m_rot.MakeRotationFromQuaternion(m_rotation);
	/*m_position.x = m_rot.m[2][0] * plposlen + toro->m_position.x;
	m_position.y = m_rot.m[2][1] * plposlen + toro->m_position.y;
	m_position.z = m_rot.m[2][2] * plposlen + toro->m_position.z;
	m_rotation.x = toro->m_rotation.x;
	m_rotation.y = toro->m_rotation.y;
	m_rotation.z = toro->m_rotation.z;
	m_rotation.w = toro->m_rotation.w;*/
	
	if (fabsf(m_moveSpeed.x) < 0.001f
		&& fabsf(m_moveSpeed.z) < 0.001f) {
		//m_moveSpeed.xとm_moveSpeed.zの絶対値がともに0.001以下ということは
		//このフレームではキャラは移動していないので旋回する必要はない。
		return;
	}
	//atan2はtanθの値を角度(ラジアン単位)に変換してくれる関数。
	//m_moveSpeed.x / m_moveSpeed.zの結果はtanθになる。
	//atan2を使用して、角度を求めている。
	//これが回転角度になる。
	//	float angle = atan2(m_moveSpeed.x, m_moveSpeed.z);
	//atanが返してくる角度はラジアン単位なので
	//SetRotationDegではなくSetRotationを使用する。
	//m_rotation.SetRotation(CVector3::AxisY, angle);

	//m_skinModel.Update(m_position, m_rotation, CVector3::One);
}
void Player::Dead() {
	//圧死判定
	if (Pad(0).IsTrigger(enButtonX)) {
		//toro->lifecount = 5;
		PressFlag = 1;
	}
}
void Player::Update()
{
	if (m_goal != NULL) {
		ChangeFlag = 1;
	}
		Move();
		Rotation();
		Dead();


		if (dameflag == 1) {
			if (nlcount <= 0) {
				nlcount = 0.01;
			}
			//lifecountが5になったらゲームオーバー
			if ((lifecount == 0 && hpscale <= 0.8)
				|| (lifecount == 1 && hpscale <= 0.6)
				|| (lifecount == 2 && hpscale <= 0.4)
				|| (lifecount == 3 && hpscale <= 0.2)
				|| (lifecount == 4 && hpscale <= 0.0))
			{
				lifecount = lifecount + 1;
			}
			dameflag = 0;
		}
		//２秒間無敵
		if (nlcount > 0) {
			nlcount = nlcount + GameTime().GetFrameDeltaTime();
			if (2 <= nlcount) {
				nlcount = 0;
				dameflag = 0;
			}
		}
		if (dameflag == 1) {
			if ((lifecount == 0 && nlcount == 0)
				|| (lifecount == 1 && nlcount == 0)
				|| (lifecount == 2 && nlcount == 0)
				|| (lifecount == 3 && nlcount == 0)
				|| (lifecount == 4 && nlcount == 0))
			{
				hpscale = hpscale - 0.1;
			}

		}
		if (hpdscale > hpscale) {
			hpdscale = hpdscale - 0.01;
			m_hdsprite.Update(m_hpdosition = { -625.0,345.0,0 }, CQuaternion::Identity, CVector3{ hpdscale,1.0,1.0 }, { 0.0,1.0 });
		}

		m_skinModel.Update(m_position, m_rotation, CVector3::One);
		m_hsprite.Update(m_hposition = { -625.0,345.0,0 }, CQuaternion::Identity, CVector3{ hpscale,1.0,1.0 }, { 0.0,1.0 });
		m_hdsprite.Update(m_hpdosition = { -625.0,345.0,0 }, CQuaternion::Identity, CVector3{ hpdscale,1.0,1.0 }, { 0.0,1.0 });
		m_hbsprite.Update(m_hbposition = { -640.0,360.0,0 }, CQuaternion::Identity, CVector3::One, { 0.0,1.0 });

		
}

void Player::Render(CRenderContext& rc)
{
	//プレイヤー描画
	m_skinModel.Draw(rc, 
		MainCamera().GetViewMatrix(), 
		MainCamera().GetProjectionMatrix(),
		CMatrix::Identity,
		CMatrix::Identity,
		 0
	);	
}
void Player::PostRender(CRenderContext& rc) {
	//スタート
	if (ChangeFlag == 1) {
	if (flag == 0 && count == 0)
	{
		m_font.Begin(rc);
		m_font.Draw(L"PRESS ANY KEY", { 640.0f, -270.0f }, { 234.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 255.0f }, 0.0f, 1.5f);
		m_font.End(rc);
	}
	else if (flag == 0)
	{
		count = count + GameTime().GetFrameDeltaTime();
		if (count >= 0 && count <= 1)
		{
			if (scalefg == 0) {
				scale = 3;
				scalefg = 1;
			}
			m_font.Begin(rc);
			m_font.Draw(L"3", { 640.0f, -270.0f }, { 234.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 255.0f }, 0.0f, scale);
			m_font.End(rc);
			scale = scale - count*0.2;
		}
		if (count > 1 && count <= 2)
		{
			if (scalefg == 1) {
				scale = 3;
				scalefg = 0;
			}
			m_font.Begin(rc);
			m_font.Draw(L"2", { 640.0f, -270.0f }, { 234.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 255.0f }, 0.0f, scale);
			m_font.End(rc);
			scale = scale - (count - 1)*0.2;
		}
		if (count > 2 && count <= 3)
		{
			if (scalefg == 0) {
				scale = 3;
				scalefg = 1;
			}
			m_font.Begin(rc);
			m_font.Draw(L"1", { 640.0f, -270.0f }, { 234.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 255.0f }, 0.0f, scale);
			m_font.End(rc);
			scale = scale - (count - 2)*0.2;
		}
		if (count >3 && count <= 3.3)
		{
			if (scalefg == 1) {
				scale = 1;
				scalefg = 0;
			}
			m_font.Begin(rc);
			m_font.Draw(L"GO!", { 640.0f, -270.0f }, { 234.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 255.0f }, 0.0f, scale);
			m_font.End(rc);
			scale = scale + (count - 3) * 3;
		}
		if (count>3.3)
		{
			flag = 1;
		}
	}
	if (Pad(0).IsPressAnyKey()) {

		count = count + GameTime().GetFrameDeltaTime();
	}
	
		if (m_goal->gflag == 0) {
			//HP barテクスチャ描画
			m_hbsprite.Draw(rc,
				MainCamera2D().GetViewMatrix(),
				MainCamera2D().GetProjectionMatrix());

			//HPダメージ時テクスチャ描画
			m_hdsprite.Draw(rc,
				MainCamera2D().GetViewMatrix(),
				MainCamera2D().GetProjectionMatrix());
			//HPテクスチャ描画
			m_hsprite.Draw(rc,
				MainCamera2D().GetViewMatrix(),
				MainCamera2D().GetProjectionMatrix());

		}
	}
}