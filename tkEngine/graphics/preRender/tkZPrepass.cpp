/*!
 *@brief	ZPrepass
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/preRender/tkZPrepass.h"
#include "tkEngine/graphics/tkCamera.h"
#include "Game/Mirror.h"

//extern tkEngine::CMatrix g_mirrorViewMatrix;
//extern tkEngine::CMatrix g_mirrorProjectionMatrix;
namespace tkEngine{
	namespace {
		static const int RESERVE_SKIN_MODEL_LIST = 512;
	}
	CZPrepass::CZPrepass()
	{
		m_skinModels.reserve(RESERVE_SKIN_MODEL_LIST);
	}
	CZPrepass::~CZPrepass()
	{
	}
	void CZPrepass::Init()
	{
		CGraphicsEngine& ge = GraphicsEngine();
		//深度値書き込み用のレンダリングターゲットの作成。
		
		m_depthBuffer.Create(
			ge.GetFrameBufferWidth(),
			ge.GetFrameBufferHeight(),
			1,
			1,
			DXGI_FORMAT_R32_FLOAT,
			DXGI_FORMAT_UNKNOWN,	//Zバッファは作らない。
			ge.GetMainRenderTargetMSAADesc()
		);
		//Zバッファはメインレンダリングターゲットのものを使用する。
		m_depthBuffer.SetDepthStencilView(
			ge.GetMainRenderTarget().GetDepthStencilView()
		);
	}
	void CZPrepass::Render(CRenderContext& rc) 
	{
		BeginGPUEvent(L"enRenderStep_ZPrepass");
		rc.PSUnsetShaderResource(8);
		rc.SetRenderStep(enRenderStep_ZPrepass);
		//現在のレンダリングターゲットをバックアップする。
		CRenderTarget* oldRenderTargets[MRT_MAX];
		unsigned int numRenderTargetViews;
		rc.OMGetRenderTargets(numRenderTargetViews, oldRenderTargets);
		//レンダリングターゲットを変更する。
		CRenderTarget* renderTargets[] = {
			&m_depthBuffer
		};
		rc.OMSetRenderTargets(1, renderTargets);
		float ClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; //red,green,blue,alpha
		rc.ClearRenderTargetView(0, ClearColor);

		//今井　FindGOを追加
		if (m_mirror == NULL) {
			m_mirror = FindGO<Mirror>("Mirror");
		}
		//　今井　引数を追加した
		for (auto skinModel : m_skinModels) {
			skinModel->Draw(
				rc,
				MainCamera().GetViewMatrix(),
				MainCamera().GetProjectionMatrix(),
				m_mirror->m_mirrorViewMatrix,
				m_mirror->m_mirrorProjectionMatrix,
				Mirror::GetInstance().alphaflag
			);
		}
		m_skinModels.clear();
		//レンダリングターゲットを差し戻す。
		rc.OMSetRenderTargets(numRenderTargetViews, oldRenderTargets);
		EndGPUEvent();
		//MSAAリゾルブ。
		m_depthBuffer.ResovleMSAATexture(rc);

		rc.PSSetShaderResource(8, m_depthBuffer.GetRenderTargetSRV());
	}
}