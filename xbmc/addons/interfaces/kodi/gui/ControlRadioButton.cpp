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

#include "ControlRadioButton.h"
#include "addons/kodi-addon-dev-kit/include/kodi/gui/ControlRadioButton.h"

#include "addons/AddonDll.h"
#include "guilib/GUIRadioButtonControl.h"
#include "utils/log.h"

extern "C"
{
namespace ADDON
{

void Interface_GUIControlRadioButton::Init(AddonGlobalInterface* addonInterface)
{
  addonInterface->toKodi->kodi_gui->controlRadioButton.SetVisible = SetVisible;
  addonInterface->toKodi->kodi_gui->controlRadioButton.SetEnabled = SetEnabled;

  addonInterface->toKodi->kodi_gui->controlRadioButton.SetLabel = SetLabel;
  addonInterface->toKodi->kodi_gui->controlRadioButton.GetLabel = GetLabel;

  addonInterface->toKodi->kodi_gui->controlRadioButton.SetSelected = SetSelected;
  addonInterface->toKodi->kodi_gui->controlRadioButton.IsSelected = IsSelected;
}

void Interface_GUIControlRadioButton::SetVisible(void* kodiBase, void* handle, bool visible)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlRadioButton::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlRadioButton::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  static_cast<CGUIRadioButtonControl*>(handle)->SetVisible(visible);
}

void Interface_GUIControlRadioButton::SetEnabled(void* kodiBase, void* handle, bool enabled)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlRadioButton::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlRadioButton::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  static_cast<CGUIRadioButtonControl*>(handle)->SetEnabled(enabled);
}

void Interface_GUIControlRadioButton::SetLabel(void* kodiBase, void* handle, const char *label)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlRadioButton::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle || !label)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlRadioButton::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  static_cast<CGUIRadioButtonControl*>(handle)->SetLabel(label);
}

void Interface_GUIControlRadioButton::GetLabel(void* kodiBase, void* handle, char &text, unsigned int &maxStringSize)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlRadioButton::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlRadioButton::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  CGUIRadioButtonControl* pRadioButton = static_cast<CGUIRadioButtonControl *>(handle);
  strncpy(&text, pRadioButton->GetLabel().c_str(), maxStringSize);
  maxStringSize = pRadioButton->GetLabel().length();
}

void Interface_GUIControlRadioButton::SetSelected(void* kodiBase, void* handle, bool selected)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlRadioButton::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlRadioButton::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  static_cast<CGUIRadioButtonControl*>(handle)->SetSelected(selected);
}

bool Interface_GUIControlRadioButton::IsSelected(void* kodiBase, void* handle)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlRadioButton::%s - invalid data", __FUNCTION__);
    return false;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlRadioButton::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return false;
  }

  return static_cast<CGUIRadioButtonControl *>(handle)->IsSelected();
}

} /* namespace ADDON */
} /* extern "C" */
