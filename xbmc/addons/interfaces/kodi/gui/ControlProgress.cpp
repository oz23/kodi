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
 *  along with KODI; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "ControlProgress.h"
#include "addons/kodi-addon-dev-kit/include/kodi/gui/ControlProgress.h"

#include "addons/AddonDll.h"
#include "guilib/GUIProgressControl.h"
#include "guilib/GUIWindowManager.h"
#include "utils/log.h"

extern "C"
{
namespace ADDON
{

void Interface_GUIControlProgress::Init(AddonGlobalInterface* addonInterface)
{
  addonInterface->toKodi->kodi_gui->controlProgress.SetVisible = SetVisible;
  addonInterface->toKodi->kodi_gui->controlProgress.SetPercentage = SetPercentage;
  addonInterface->toKodi->kodi_gui->controlProgress.GetPercentage = GetPercentage;
}

void Interface_GUIControlProgress::SetVisible(void* kodiBase, void* handle, bool visible)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlProgress::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlProgress::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  static_cast<CGUIProgressControl*>(handle)->SetVisible(visible);
}

void Interface_GUIControlProgress::SetPercentage(void* kodiBase, void* handle, float percent)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlProgress::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlProgress::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  static_cast<CGUIProgressControl*>(handle)->SetPercentage(percent);
}

float Interface_GUIControlProgress::GetPercentage(void* kodiBase, void* handle)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlProgress::%s - invalid data", __FUNCTION__);
    return 0.0f;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlProgress::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return 0.0f;
  }

  return static_cast<CGUIProgressControl*>(handle)->GetPercentage();
}

} /* namespace ADDON */
} /* extern "C" */
