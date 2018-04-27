#include "stdafx.h"
#include "Player.h"
#include"Torokko.h"
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
	m_mirror = FindGO<Mirror>("Mirror");
	toro = FindGO<Torokko>("Trokko");
	m_goal = FindGO<Goal>("Goal");
	m_position = toro->m_position;
	diff.x = toro->m_gpos.x - toro->m_position.x;
	diff.y = toro->m_gpos.y - toro->m_position.y;
	diff.z = toro->m_gpos.z - toro->m_position.z;
	plposlen=diff.Length();
	m_skinModel.Update(m_position, m_rotation, CVector3::One);
	
	return true;
}
void Player::Rotation() {
	m_rot.MakeRotationFromQuaternion(toro->m_rotation);
	m_position.x = m_rot.m[2][0] * plposlen + toro->m_position.x;
	m_position.y = m_rot.m[2][1] * plposlen + toro->m_position.y;
	m_position.z = m_rot.m[2][2] * plposlen + toro->m_position.z;
	m_rotation.x = toro->m_rotation.x;
	m_rotation.y = toro->m_rotation.y;
	m_rotation.z = toro->m_rotation.z;
	m_rotation.w = toro->m_rotation.w;


	m_skinModel.Update(m_position, m_rotation, CVector3::One);
}
void Player::Dead() {
	//圧死判定
	if (Pad(0).IsTrigger(enButtonX)) {
		toro->lifecount = 5;
	}
}
void Player::Update()
{
	Rotation();
	Dead();
	if (toro->dameflag == 1) {
		if ((toro->lifecount==0 && toro->nlcount==0)
			|| (toro->lifecount == 1 && toro->nlcount == 0)
			|| (toro->lifecount == 2 && toro->nlcount == 0)
			|| (toro->lifecount == 3 && toro->nlcount == 0)
			|| (toro->lifecount == 4 && toro->nlcount == 0))
		{
			hpscale = hpscale - 0.1;
		}
	
	}
	if (hpdscale > hpscale) {
		hpdscale = hpdscale - 0.01;
		m_hdsprite.Update(m_hpdosition = { -625.0,345.0,0 }, CQuaternion::Identity, CVector3{ hpdscale,1.0,1.0 }, { 0.0,1.0 });
	}
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