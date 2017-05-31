/*
 *      Copyright (C) 2005-2017 Team Kodi
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
 *  along with Kodi; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "Screensaver.h"

#include "filesystem/SpecialProtocol.h"
#include "guilib/GUIWindowManager.h"
#include "utils/log.h"
#ifdef HAS_DX
#include "windowing/windows/WinSystemWin32DX.h"
#endif


namespace ADDON
{

CScreenSaver::CScreenSaver(AddonInfoPtr addonInfo)
  : IAddonInstanceHandler(ADDON_SCREENSAVER, addonInfo)
{
  m_struct = { 0 };

  // Setup new screensaver instance
  m_name = Name();
  m_presets = CSpecialProtocol::TranslatePath(Path());
  m_profile = CSpecialProtocol::TranslatePath(Profile());

#ifdef HAS_DX
  m_struct.props.device = g_Windowing.Get3D11Context();
#else
  m_struct.props.device = nullptr;
#endif
  m_struct.props.x = 0;
  m_struct.props.y = 0;
  m_struct.props.width = g_graphicsContext.GetWidth();
  m_struct.props.height = g_graphicsContext.GetHeight();
  m_struct.props.pixelRatio = g_graphicsContext.GetResInfo().fPixelRatio;
  m_struct.props.name = m_name.c_str();
  m_struct.props.presets = m_presets.c_str();
  m_struct.props.profile = m_profile.c_str();
  m_struct.toKodi.kodiInstance = this;

  /* Open the class "kodi::addon::CInstanceScreensaver" on add-on side */
  if (!CreateInstance(ADDON_INSTANCE_SCREENSAVER, &m_struct))
    CLog::Log(LOGFATAL, "Screensaver: failed to create instance for '%s' and not usable!", addonInfo->ID().c_str());
}

CScreenSaver::~CScreenSaver()
{
  /* Destroy the class "kodi::addon::CInstanceScreensaver" on add-on side */
  DestroyInstance();
}

bool CScreenSaver::Start()
{
  if (m_struct.toAddon.Start)
    return m_struct.toAddon.Start(&m_struct);
  return false;
}

void CScreenSaver::Stop()
{
  if (m_struct.toAddon.Stop)
    m_struct.toAddon.Stop(&m_struct);
}

void CScreenSaver::Render()
{
  if (m_struct.toAddon.Render)
    m_struct.toAddon.Render(&m_struct);
}

} /* namespace ADDON */
