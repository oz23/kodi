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

#include "ControlLabel.h"
#include "addons/kodi-addon-dev-kit/include/kodi/gui/ControlLabel.h"

#include "addons/AddonDll.h"
#include "guilib/GUILabelControl.h"
#include "guilib/GUIWindowManager.h"
#include "utils/log.h"

extern "C"
{
namespace ADDON
{

void Interface_GUIControlLabel::Init(AddonGlobalInterface* addonInterface)
{
  addonInterface->toKodi->kodi_gui->controlLabel.SetVisible = SetVisible;
  addonInterface->toKodi->kodi_gui->controlLabel.SetLabel = SetLabel;
  addonInterface->toKodi->kodi_gui->controlLabel.GetLabel = GetLabel;
}

void Interface_GUIControlLabel::SetVisible(void* kodiBase, void* handle, bool visible)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlLabel::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlLabel::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  static_cast<CGUILabelControl*>(handle)->SetVisible(visible);
}

void Interface_GUIControlLabel::SetLabel(void* kodiBase, void* handle, const char *label)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlLabel::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlLabel::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  CGUILabelControl* pControl = static_cast<CGUILabelControl*>(handle);

  // create message
  CGUIMessage msg(GUI_MSG_LABEL_SET, pControl->GetParentID(), pControl->GetID());
  msg.SetLabel(label);

  // send message
  g_windowManager.SendThreadMessage(msg, pControl->GetParentID());
}

void Interface_GUIControlLabel::GetLabel(void* kodiBase, void* handle, char &label, unsigned int &iMaxStringSize)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlLabel::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlLabel::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  std::string text = static_cast<CGUILabelControl*>(handle)->GetDescription(); // GetDescription = label
  strncpy(&label, text.c_str(), iMaxStringSize);
  iMaxStringSize = text.length();
}

} /* namespace ADDON */
} /* extern "C" */
