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

#include "ControlButton.h"
#include "addons/kodi-addon-dev-kit/include/kodi/gui/ControlButton.h"

#include "addons/AddonDll.h"
#include "guilib/GUIButtonControl.h"
#include "utils/log.h"
#include "utils/StringUtils.h"

extern "C"
{
namespace ADDON
{

void Interface_GUIControlButton::Init(AddonGlobalInterface* addonInterface)
{
  addonInterface->toKodi->kodi_gui->controlButton.SetVisible = SetVisible;
  addonInterface->toKodi->kodi_gui->controlButton.SetEnabled = SetEnabled;

  addonInterface->toKodi->kodi_gui->controlButton.SetLabel = SetLabel;
  addonInterface->toKodi->kodi_gui->controlButton.GetLabel = GetLabel;

  addonInterface->toKodi->kodi_gui->controlButton.SetLabel2 = SetLabel2;
  addonInterface->toKodi->kodi_gui->controlButton.GetLabel2 = GetLabel2;
}

void Interface_GUIControlButton::SetVisible(void* kodiBase, void* handle, bool yesNo)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlButton::%s - invalid data", __FUNCTION__);
    return;
  }

  if (handle)
    static_cast<CGUIButtonControl*>(handle)->SetVisible(yesNo);
  else
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlButton::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
}

void Interface_GUIControlButton::SetEnabled(void* kodiBase, void* handle, bool yesNo)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlButton::%s - invalid data", __FUNCTION__);
    return;
  }

  if (handle)
    static_cast<CGUIButtonControl*>(handle)->SetEnabled(yesNo);
  else
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlButton::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
}

void Interface_GUIControlButton::SetLabel(void* kodiBase, void* handle, const char *label)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlButton::%s - invalid data", __FUNCTION__);
    return;
  }

  if (handle)
    static_cast<CGUIButtonControl *>(handle)->SetLabel(label);
  else
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlButton::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
}

void Interface_GUIControlButton::GetLabel(void* kodiBase, void* handle, char &label, unsigned int &iMaxStringSize)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlButton::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlButton::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  CGUIButtonControl* pButton = static_cast<CGUIButtonControl *>(handle);
  std::string text = pButton->GetLabel();
  strncpy(&label, text.c_str(), iMaxStringSize);
  iMaxStringSize = text.length();
}

void Interface_GUIControlButton::SetLabel2(void* kodiBase, void* handle, const char *label)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlButton::%s - invalid data", __FUNCTION__);
    return;
  }

  if (handle)
    static_cast<CGUIButtonControl *>(handle)->SetLabel2(label);
  else
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlButton::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
}

void Interface_GUIControlButton::GetLabel2(void* kodiBase, void* handle, char &label, unsigned int &iMaxStringSize)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlButton::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlButton::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }


  CGUIButtonControl* pButton = static_cast<CGUIButtonControl *>(handle);
  std::string text = pButton->GetLabel2();
  strncpy(&label, text.c_str(), iMaxStringSize);
  iMaxStringSize = text.length();
}

} /* namespace ADDON */
} /* extern "C" */
