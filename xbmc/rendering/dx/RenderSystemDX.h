/*
 *      Copyright (C) 2005-2013 Team XBMC
 *      http://kodi.tv
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#ifndef RENDER_SYSTEM_DX_H
#define RENDER_SYSTEM_DX_H

#pragma once

#include "DeviceResources.h"
#include "threads/Condition.h"
#include "threads/CriticalSection.h"
#include "utils/Color.h"
#include "rendering/RenderSystem.h"

#include <vector>
#include <wrl.h>
#include <wrl/client.h>

enum PCI_Vendors
{
  PCIV_ATI    = 0x1002,
  PCIV_nVidia = 0x10DE,
  PCIV_Intel  = 0x8086
};

class ID3DResource;
class CGUIShaderDX;
enum AVPixelFormat;
enum AVPixelFormat;

class CRenderSystemDX : public CRenderSystemBase, DX::IDeviceNotify
{
public:
  CRenderSystemDX();
  virtual ~CRenderSystemDX();

  // CRenderBase overrides
  bool InitRenderSystem() override;
  bool DestroyRenderSystem() override;
  bool BeginRender() override;
  bool EndRender() override;
  void PresentRender(bool rendered, bool videoLayer) override;
  bool ClearBuffers(UTILS::Color color) override;
  void SetViewPort(const CRect& viewPort) override;
  void GetViewPort(CRect& viewPort) override;
  void RestoreViewPort() override;
  CRect ClipRectToScissorRect(const CRect &rect) override;
  bool ScissorsCanEffectClipping() override;
  void SetScissors(const CRect &rect) override;
  void ResetScissors() override;
  void CaptureStateBlock() override;
  void ApplyStateBlock() override;
  void SetCameraPosition(const CPoint &camera, int screenWidth, int screenHeight, float stereoFactor = 0.f) override;
  void SetStereoMode(RENDER_STEREO_MODE mode, RENDER_STEREO_VIEW view) override;
  bool SupportsStereo(RENDER_STEREO_MODE mode) const override;
  bool TestRender() override;
  void Project(float &x, float &y, float &z) override;
  bool SupportsNPOT(bool dxt) const override;

  // IDeviceNotify overrides
  void OnDXDeviceLost() override;
  void OnDXDeviceRestored() override;

  // CRenderSystemDX methods
  CGUIShaderDX* GetGUIShader() const { return m_pGUIShader; }
  bool Interlaced() const { return m_interlaced; }
  bool IsFormatSupport(DXGI_FORMAT format, unsigned int usage) const;
  CRect GetBackBufferRect();
  CD3DTexture* GetBackBuffer();

  void FlushGPU() const;
  void SetAlphaBlendEnable(bool enable);
  HANDLE GetContexMutex() const;

  // empty overrides
  bool IsExtSupported(const char* extension) const override { return false; };
  void ApplyHardwareTransform(const TransformMatrix &matrix) override {};
  void RestoreHardwareTransform() override {};
  bool ResetRenderSystem(int width, int height) override { return true; };

  std::vector<AVPixelFormat> m_processorFormats;
  std::vector<AVPixelFormat> m_sharedFormats;
  std::vector<AVPixelFormat> m_shaderFormats;

protected:
  virtual void PresentRenderImpl(bool rendered) = 0;

  bool CreateStates();
  bool InitGUIShader();
  void OnResize();
  void CheckInterlacedStereoView(void);
  void CheckDeviceCaps();

  CCriticalSection m_resourceSection;
  CCriticalSection m_decoderSection;

  // our adapter could change as we go
  bool m_interlaced;
  bool m_inScene{ false }; ///< True if we're in a BeginScene()/EndScene() block
  bool m_BlendEnabled{ false };
  bool m_ScissorsEnabled{ false };
  D3D11_VIEWPORT m_viewPort;
  CRect m_scissor;
  CGUIShaderDX* m_pGUIShader{ nullptr };
  Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_depthStencilState;
  Microsoft::WRL::ComPtr<ID3D11BlendState> m_BlendEnableState;
  Microsoft::WRL::ComPtr<ID3D11BlendState> m_BlendDisableState;
  Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_RSScissorDisable;
  Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_RSScissorEnable;
  // stereo interlaced/checkerboard intermediate target
  CD3DTexture m_rightEyeTex;

  std::shared_ptr<DX::DeviceResources> m_deviceResources;
};

#endif // RENDER_SYSTEM_DX
