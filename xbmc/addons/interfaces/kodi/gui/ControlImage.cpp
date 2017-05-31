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

#include "ControlImage.h"
#include "addons/kodi-addon-dev-kit/include/kodi/gui/ControlImage.h"

#include "addons/AddonDll.h"
#include "guilib/GUIImage.h"
#include "utils/log.h"

extern "C"
{
namespace ADDON
{

void Interface_GUIControlImage::Init(AddonGlobalInterface* addonInterface)
{
  addonInterface->toKodi->kodi_gui->controlImage.SetVisible = SetVisible;
  addonInterface->toKodi->kodi_gui->controlImage.SetFileName = SetFileName;
  addonInterface->toKodi->kodi_gui->controlImage.SetColorDiffuse = SetColorDiffuse;
}

void Interface_GUIControlImage::SetVisible(void *kodiBase, void* handle, bool visible)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlImage::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlImage::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  static_cast<CGUIImage*>(handle)->SetVisible(visible);
}

void Interface_GUIControlImage::SetFileName(void *kodiBase, void* handle, const char* strFileName, const bool useCache)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlImage::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle || !strFileName)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlImage::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  static_cast<CGUIImage*>(handle)->SetFileName(strFileName, false, useCache);
}

void Interface_GUIControlImage::SetColorDiffuse(void *kodiBase, void* handle, uint32_t colorDiffuse)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlImage::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlImage::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  static_cast<CGUIImage*>(handle)->SetColorDiffuse(colorDiffuse);
}

} /* namespace ADDON */
} /* extern "C" */
