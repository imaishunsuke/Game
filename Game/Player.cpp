#include "stdafx.h"
#include "Player.h"
//#include"Torokko.h"
#include"Mirror.h"
#include"Goal.h"

Player::Player()
{
}


Player::~Player()
{
}

bool Player::Start() {
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
	//hpテクスチャ
	m_htexture.CreateFromDDSTextureFromFile(L"sprite/hp.dds");
	m_hsprite.Init(m_htexture, 460, 40);
	//hpdテクスチャ
	m_hdtexture.CreateFromDDSTextureFromFile(L"sprite/hpd.dds");
	m_hdsprite.Init(m_hdtexture, 460, 40);
	//hp barテクスチャ
	m_hbtexture.CreateFromDDSTextureFromFile(L"sprite/hpmp_bar.dds");
	m_hbsprite.Init(m_hbtexture, 490, 70);
	
	m_charaCon.Init(
		3.0,		//半径
		1.0f,		//高さ
		-220,
		m_position,	//初期位置
		m_collidertype
	);
	flag = 0;
	count = 0;
	scale = 3.0f;
	m_gpos = { 0.0,0.0,5.0 };
	m_mirror = FindGO<Mirror>("Mirror");
	/*toro = FindGO<Torokko>("Trokko");*/
	m_goal = FindGO<Goal>("Goal");
	/*m_position = toro->m_position;
	diff.x = toro->m_gpos.x - toro->m_position.x;
	diff.y = toro->m_gpos.y - toro->m_position.y;
	diff.z = toro->m_gpos.z - toro->m_position.z;
	plposlen=diff.Length();*/
	m_skinModel.Update(m_position, m_rotation, CVector3::One);
	m_skinModel.SetShadowCasterFlag(true);
	return true;
}
void Player::Move() {
	x = Pad(0).GetLStickXF();
}
void Player::Rotation() {
	/*m_rot.MakeRotationFromQuaternion(toro->m_rotation);
	m_position.x = m_rot.m[2][0] * plposlen + toro->m_position.x;
	m_position.y = m_rot.m[2][1] * plposlen + toro->m_position.y;
	m_position.z = m_rot.m[2][2] * plposlen + toro->m_position.z;
	m_rotation.x = toro->m_rotation.x;
	m_rotation.y = toro->m_rotation.y;
	m_rotation.z = toro->m_rotation.z;
	m_rotation.w = toro->m_rotation.w;*/


	m_skinModel.Update(m_position, m_rotation, CVector3::One);
}
void Player::Dead() {
	//圧死判定
	if (Pad(0).IsTrigger(enButtonX)) {
		//toro->lifecount = 5;
	}
}
void Player::Update()
{
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
		if ((lifecount==0 && nlcount==0)
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
	m_position = m_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_moveSpeed, m_collidertype);
	m_skinModel.Update(m_position, m_rotation, CVector3::One);
	m_hsprite.Update(m_hposition = { -625.0,345.0,0 }, CQuaternion::Identity, CVector3{hpscale,1.0,1.0 }, { 0.0,1.0 });
	m_hdsprite.Update(m_hpdosition = { -625.0,345.0,0 }, CQuaternion::Identity, CVector3{hpdscale,1.0,1.0}, { 0.0,1.0 });
	m_hbsprite.Update(m_hbposition = { -640.0,360.0,0 }, CQuaternion::Identity, CVector3::One, { 0.0,1.0 });
}

void Player::Render(CRenderContext& rc)
{
	//プレイヤー描画
	m_mirror->alphaflag = 0;
	m_skinModel.Draw(rc, 
		MainCamera().GetViewMatrix(), 
		MainCamera().GetProjectionMatrix(),
		CMatrix::Identity,
		CMatrix::Identity,
		m_mirror->alphaflag);
		
}

void Player::PostRender(CRenderContext& rc) {
	//スタート
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