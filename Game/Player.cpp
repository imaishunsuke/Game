#include "stdafx.h"
#include "Player.h"
#include"Mirror.h"
#include"Game.h"
#include"Goal.h"
#include"GameOverProd.h"
#include"Game.h"
#include "ResultScene.h"
#include "tkEngine/sound/tkSoundSource.h"
//#include"tkEngine/bulletPhysics/src/LinearMath/btConvexHull.h"
//#include"tkEngine/DirectXTK/Inc/SimpleMath.h"
Player::Player()
{
}


Player::~Player()
{
	DeleteGO(m_Prod);
	DeleteGO(m_bgm);
	DeleteGO(m_wind);
	DeleteGO(m_animeSound);
}

bool Player::Start() {
	//モデルデータのロード
	m_skinModelData.Load(L"modelData/FemaleMage.cmo");
	m_skinModel.Init(m_skinModelData);
	////法線マップとスペキュラマップをロード
	//m_specularMap.CreateFromDDSTextureFromFile(L"sprite/utc_spec.dds");
	//m_normalMap.CreateFromDDSTextureFromFile(L"sprite/utc_normal.dds");
	//m_skinModel.FindMaterial([&](auto material) {
	//	material->SetNormalMap(m_normalMap.GetBody());
	//	//material->SetSpecularMap(m_specularMap.GetBody());
	//});

	m_animClip[enAnimationClip_walk].Load(L"animData/walk.tka");
	for (auto& animClip : m_animClip) {
		animClip.SetLoopFlag(true);
	}
	m_animation.Init(m_skinModel, m_animClip,enAnimationClip_num);
	m_animation.Play(enAnimationClip_walk, 0.2f);
	m_animeSound = NewGO<prefab::CSoundSource>(0);
	m_animeSound->Init("sound/walk2.wav");
	m_animeSound->SetVolume(2.0);
	m_animeSound->Play(true);


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
	m_position.y = -1.5;
	//線分初期化
	m_sen = m_position;
	m_position = { 0.0f,10.0f,10.0f };
	m_charaCon.Init(
		2.0,		//半径
		1.0f,		//高さ
		-220,
		m_position,	//初期位置
		m_collidertype
	);
	flag = 0;
	count = 0;
	scale = 3.0f;
	WindCall = 4.0f;
	m_gpos = m_position;
	m_game = FindGO<Game>("Game");
	m_enemyball = FindGO<EnemyBall>("EnemyBall");
	m_mirror = FindGO<Mirror>("Mirror");
	m_goal = FindGO<Goal>("Goal");

	m_testResult = FindGO<ResultScene>("Result");

	m_skinModel.Update(m_position, m_rotation,CVector3::One);
	m_skinModel.SetShadowCasterFlag(true);

	m_bgm = NewGO<prefab::CSoundSource>(0);
	m_bgm->Init("sound/game_dangeon.wav");
	m_bgm->SetVolume(vo);
	m_bgm->Play(true);
	m_wind = NewGO<prefab::CSoundSource>(0);
	return true;
}
void Player::InitPoly() {
	int numMesh = 0;
	for (auto& mapChip : m_game->m_level.GetMapList()) {
		const auto& mWorld = mapChip->GetSkinModel().GetWorldMatrix();
		mapChip->GetSkinModel().FindMesh([&](const auto& mesh) {
			numMesh++;
			ID3D11DeviceContext* deviceContext = GraphicsEngine().GetD3DDeviceContext();
			//頂点バッファをロック
			D3D11_MAPPED_SUBRESOURCE subresource;
			deviceContext->Map(mesh->vertexBuffer.Get(), 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &subresource);
			//頂点バッファの定義を取得。
			D3D11_BUFFER_DESC bufferDesc;
			mesh->vertexBuffer->GetDesc(&bufferDesc);

			//頂点バッファの先頭アドレスを取得。
			char* pVertexData = reinterpret_cast<char*>(subresource.pData);
			//インデックスバッファをロック。
			deviceContext->Map(mesh->indexBuffer.Get(), 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &subresource);
			bufferDesc;
			mesh->indexBuffer->GetDesc(&bufferDesc);
			int stride = 2;
			int indexCount = bufferDesc.ByteWidth / stride;
			//インデックスバッファにアクセスする。
			unsigned short* pIndex = reinterpret_cast<unsigned short*>(subresource.pData);
			int numTri = indexCount / 3;
			for (int triNo = 0; triNo < numTri; triNo++) {
				Spoly Poly;
				CVector3 *p1, *p2, *p3;
				p1 = (CVector3*)(pVertexData + pIndex[0] * mesh->vertexStride);
				p2 = (CVector3*)(pVertexData + pIndex[1] * mesh->vertexStride);
				p3 = (CVector3*)(pVertexData + pIndex[2] * mesh->vertexStride);
				//次の三角形。
				pIndex += 3;
				Poly.m_triVertex[0] = *p1;
				Poly.m_triVertex[1] = *p2;
				Poly.m_triVertex[2] = *p3;
				//ワールド空間に変換。
				mWorld.Mul(Poly.m_triVertex[0]);
				mWorld.Mul(Poly.m_triVertex[1]);
				mWorld.Mul(Poly.m_triVertex[2]);
				//平面の法線を計算する。
				CVector3 v1, v2;
				v1 = Poly.m_triVertex[0] - Poly.m_triVertex[1];
				v2 = Poly.m_triVertex[2] - Poly.m_triVertex[1];

				Poly.m_normal.Cross(v1, v2);
				Poly.m_normal.Normalize();
				m_polypool.push_back(Poly);
			}
			//インデックスバッファをアンロック。
			deviceContext->Unmap(mesh->indexBuffer.Get(), 0);

			//頂点バッファをアンロック
			deviceContext->Unmap(mesh->vertexBuffer.Get(), 0);
		});
	}
}
void Player::Move()
{
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
	/*m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;*/
	cameraForward *=lStick_y * 50.0f*GameTime().GetFrameDeltaTime();	//奥方向への移動速度を代入。	
	cameraRight *= lStick_x * 50.0f*GameTime().GetFrameDeltaTime();	//右方向への移動速度を加算。
	
	if (Pad(0).IsTrigger(enButtonA) && m_charaCon.IsOnGround() == true) {
		m_moveSpeed.y += 60.0f;
	}
	//摩擦
	CVector3 masa = m_moveSpeed;
	if (m_charaCon.IsJump()) {
		//ジャンプ中
		masa *= -1.0f;
	}
	else {
		//その他
		masa *= -3.0f;
	}

	m_moveSpeed.x += masa.x * GameTime().GetFrameDeltaTime();
	m_moveSpeed.z += masa.z * GameTime().GetFrameDeltaTime();

	m_moveSpeed += cameraForward;
	m_moveSpeed += cameraRight;
	
	m_rot.MakeRotationFromQuaternion(m_rotation);
	m_position = m_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_moveSpeed, m_collidertype);
}

void Player::Rotation() {

	m_rot.MakeRotationFromQuaternion(m_rotation);
	if (fabsf(m_moveSpeed.x) < 0.001f
		&& fabsf(m_moveSpeed.z) < 0.001f) {
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
	float angle = atan2(m_moveSpeed.x, m_moveSpeed.z);
	m_rotation.SetRotation(CVector3::AxisY, angle);
}

void Player::Dead(CRenderContext& rc) {
	CVector3 vStart = m_position;
	vStart.y *= 3.0f;
	CVector3 vEnd = vStart + CVector3(0.0f, 0.0f, 20.0f);

	float fNearPlaneLength = FLT_MAX;		//一番近い平面までの距離。
	CVector3 vNearPlaneNormal = CVector3::Zero; //一番近い平面の法線。
	bool isHit = false;
	
	 CVector3 Poly0, Poly1, Poly2,normalc;
	 for(std::vector<Spoly>::const_iterator itr = m_polypool.begin();itr != m_polypool.end ();itr++){
				//三角形の頂点からレイの始点へのベクトルを計算する。
				CVector3 vertToStart = vStart - itr->m_triVertex[0];
				//三角形の頂点からレイの終点へのベクトルを計算する。
				CVector3 vertToEnd = vEnd - itr->m_triVertex[0];
	
				float d1 = itr->m_normal.Dot(vertToStart);
				float d2 = itr->m_normal.Dot(vertToEnd);

				if (d1 * d2 < 0.0f) {

					//交点を求める。
					float absD1 = fabsf(d1);
					float absD2 = fabsf(d2);
					float rayLengthInNormal = absD1 + absD2;
					CVector3 crossPoint = (vStart * (absD1 / rayLengthInNormal))
						+ (vEnd * (absD2 / rayLengthInNormal));
					//無限平面と衝突したので、次は三角形の内外判定を行う。
					CVector3 vert0ToCrossPoint = crossPoint - itr->m_triVertex[0];
					vert0ToCrossPoint.Normalize();
					CVector3 vert1ToCrossPoint = crossPoint - itr->m_triVertex[1];
					vert1ToCrossPoint.Normalize();
					CVector3 vert2ToCrossPoint = crossPoint - itr->m_triVertex[2];
					vert2ToCrossPoint.Normalize();

					CVector3 vert0ToVert1 = itr->m_triVertex[1] - itr->m_triVertex[0];
					vert0ToVert1.Normalize();

					CVector3 vert1ToVert2 = itr->m_triVertex[2] - itr->m_triVertex[1];
					vert1ToVert2.Normalize();

					CVector3 vert2ToVert0 = itr->m_triVertex[0] - itr->m_triVertex[2];
					vert2ToVert0.Normalize();

					CVector3 vWork[3];
					vWork[0].Cross(vert0ToVert1, vert0ToCrossPoint);
					vWork[0].Normalize();

					vWork[1].Cross(vert1ToVert2, vert1ToCrossPoint);
					vWork[1].Normalize();

					vWork[2].Cross(vert2ToVert0, vert2ToCrossPoint);
					vWork[2].Normalize();

					if (vWork[0].Dot(vWork[1]) > 0.0f 
						&& vWork[0].Dot(vWork[2]) > 0.0f){
						//交点は三角形の内側にいる。
						isHit = true;
						CVector3 diff = vStart - crossPoint;
						float len = diff.LengthSq();
						if (len < fNearPlaneLength) {
							//この平面のほうが近いので、距離と法線を更新する。
							fNearPlaneLength = len;
							vNearPlaneNormal = itr->m_normal;
						}
					}
				}
				if (isHit == true) {
					break;
				}
			}
	if (isHit == true) {
		CVector3 vRayDir = vEnd - vStart;
		vRayDir.Normalize();
		if (vRayDir.Dot(vNearPlaneNormal) > 0.0f) {
			Dcount++;
			//閉じたメッシュの内側にいる？
		}
	}

}

void Player::Update()
{
	//if (m_goal->GetGoalFlag()) {
	//	Result();
	//	return;
	//}
	SoundEngine().SetListenerPosition(MainCamera().GetPosition());
	CVector3 frontXZ = MainCamera().GetForward();
	frontXZ.y = 0.0f;
	frontXZ.Normalize();
	SoundEngine().SetListenerFront(frontXZ);

	if (flag == 1 
		&& m_goal->GetGoalFlag() == 0 
		&& m_prodcount == 0) {

		//移動
		Move();
		//回転
		Rotation();
		if (hpdscale <= 0.0)
		{
			Dcount = 5;
		}
		Windtimer = Windtimer + GameTime().GetFrameDeltaTime();
		CVector3 epos, diff;
		epos = m_enemyball->GetEnePos();
		diff.x = m_position.x - epos.x;
		diff.y = m_position.y - epos.y;
		diff.z = m_position.z - epos.z;
		if (diff.Length()<=5.0) {
			dameflag = 1;
			//エフェクトを作成。
			prefab::CEffect* effect = NewGO<prefab::CEffect>(0);
			//エフェクトを再生。
			effect->Play(L"effect/dame.efk");
			CVector3 emitPos = m_position;
			CVector3 emitScale = { 0.7,0.7,0.7 };
			emitPos.y += 2.0;
			effect->SetPosition(emitPos);
			effect->SetScale(emitScale);
			CVector3 MovePos;
			MovePos.x = m_enemyball->GetMoveSpeed().x * 10;
			MovePos.z = m_enemyball->GetMoveSpeed().z * 10;
			MovePos.y = m_enemyball->GetMoveSpeed().y * 10;
			m_position = m_charaCon.Execute(GameTime().GetFrameDeltaTime(), MovePos, m_collidertype);
			if (dameflag == 1) {
				if (dameflag == 1) {
					if ((lifecount == 0 && nlcount == 0)
						|| (lifecount == 1 && nlcount == 0)
						|| (lifecount == 2 && nlcount == 0)
						|| (lifecount == 3 && nlcount == 0)
						|| (lifecount == 4 && nlcount == 0))
					{
						hpscale = hpscale - 0.12;
					}
				if (nlcount <= 0) {
					nlcount = 0.0;
				}
				//lifecountが5になったらゲームオーバー
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
			}
		}
		m_wind->SetVolume(1.5);
		if (WindCall <= Windtimer) {
			prefab::CSoundSource* m_wind = nullptr;
				m_wind = NewGO<prefab::CSoundSource>(0);
				m_wind->Init("sound/kaze2_.wav");
				m_wind->SetVolume(1.5);
				m_wind->Play(false);
			if (vo > 0.6) {
				vo -= 0.09;
				if (vo < 0.6)
				{
					vo = 0.6;
				}
			}
			m_bgm->SetVolume(vo);
			Windtimer = 0.0f;
			if (WindCall<=4.0) {
				WindCall = 7.0f;
			}
			else
			{
				WindCall = 4.0f;
			}
			if (Dcount >= 5
				&& m_wind->IsPlaying() == true) {
				m_wind->Pause();
			}
		}
	}

	//if (dameflag == 1) {
	//	if (nlcount <= 0) {
	//		nlcount = 0.01;
	//	}
	//	//lifecountが5になったらゲームオーバー
	//	if ((lifecount == 0 && hpscale <= 0.8)
	//		|| (lifecount == 1 && hpscale <= 0.6)
	//		|| (lifecount == 2 && hpscale <= 0.4)
	//		|| (lifecount == 3 && hpscale <= 0.2)
	//		|| (lifecount == 4 && hpscale <= 0.0))
	//	{
	//		lifecount = lifecount + 1;
	//	}
	//	dameflag = 0;
	//}
	//	//２秒間無敵
	//	if (nlcount > 0) {
	//		nlcount = nlcount + GameTime().GetFrameDeltaTime();
	//		if (2 <= nlcount) {
	//			nlcount = 0;
	//			dameflag = 0;
	//		}
	//	}
	//	if (dameflag == 1) {
	//		if ((lifecount == 0 && nlcount == 0)
	//			|| (lifecount == 1 && nlcount == 0)
	//			|| (lifecount == 2 && nlcount == 0)
	//			|| (lifecount == 3 && nlcount == 0)
	//			|| (lifecount == 4 && nlcount == 0))
	//		{
	//			hpscale = hpscale - 0.1;
	//		}

	//	}
		if (hpdscale > hpscale) {
			hpdscale = hpdscale - 0.02;
			m_hdsprite.Update(m_hpdosition = { -625.0,345.0,0 }, CQuaternion::Identity, CVector3{ hpdscale,1.0,1.0 }, { 0.0,1.0 });
		}

		m_skinModel.Update(m_position, m_rotation, CVector3::One);
		m_hsprite.Update(m_hposition = { -625.0,345.0,0 }, CQuaternion::Identity, CVector3{ hpscale,1.0,1.0 }, { 0.0,1.0 });
		m_hdsprite.Update(m_hpdosition = { -625.0,345.0,0 }, CQuaternion::Identity, CVector3{ hpdscale,1.0,1.0 }, { 0.0,1.0 });
		m_hbsprite.Update(m_hbposition = { -640.0,360.0,0 }, CQuaternion::Identity, CVector3::One, { 0.0,1.0 });
}
void Player::Render(CRenderContext& rc)
{
	//圧死
	if (Dcount >= 5) {
		if (m_prodcount==0) {
			m_Prod = NewGO<GameOverProd>(0, "Prod");
			hpscale = 0.0f;
			PressFlag = 1;
			m_prodcount = 1;
			m_bgm->Pause();
			m_animeSound->Pause();
			if (m_wind->IsPlaying() == true) {
				m_wind->Pause();
			}
		}
	}

	if ((flag==1)
		&&(m_mirror->GetIsMirror() == false)) {
		Dtime += GameTime().GetFrameDeltaTime();
		if (/*DEndPosC<=5*/Dtime <= 1.0f) {
			Dead(rc);
		}
	}
 if(m_mirror->GetIsMirror() == true)
	{
		Dtime = 0.0f;
		Dcount = 0;
	}
	//プレイヤー描画
	m_skinModel.Draw(rc, 
		MainCamera().GetViewMatrix(), 
		MainCamera().GetProjectionMatrix(),
		CMatrix::Identity,
		CMatrix::Identity
	);	
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
			if (poflag == 0) {
				InitPoly();
				poflag = 1;
			}
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
	
		if (m_goal->GetGoalFlag() == 0) {
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
void Player::Result()
{
	//CVector3 Goalvec = { 0.0f,0.0f,-1.0f };
	//CQuaternion qRot = CQuaternion::Identity;
	//qRot.Multiply(Goalvec);
	m_rotation.SetRotationDeg(CVector3::AxisY, 180.0f);
	m_rot.MakeRotationFromQuaternion(m_rotation);
	m_skinModel.Update(m_position, m_rotation, CVector3::One);
}