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

#include "ControlFadeLabel.h"
#include "addons/kodi-addon-dev-kit/include/kodi/gui/ControlFadeLabel.h"

#include "addons/AddonDll.h"
#include "guilib/GUIFadeLabelControl.h"
#include "guilib/GUIWindowManager.h"
#include "utils/log.h"

extern "C"
{
namespace ADDON
{

void Interface_GUIControlFadeLabel::Init(AddonGlobalInterface* addonInterface)
{
  addonInterface->toKodi->kodi_gui->controlFadeLabel.SetVisible = SetVisible;
  addonInterface->toKodi->kodi_gui->controlFadeLabel.AddLabel = AddLabel;
  addonInterface->toKodi->kodi_gui->controlFadeLabel.GetLabel = GetLabel;
  addonInterface->toKodi->kodi_gui->controlFadeLabel.SetScrolling = SetScrolling;
  addonInterface->toKodi->kodi_gui->controlFadeLabel.Reset = Reset;
}

void Interface_GUIControlFadeLabel::SetVisible(void *kodiBase, void* handle, bool visible)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlFadeLabel::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlFadeLabel::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  static_cast<CGUIFadeLabelControl*>(handle)->SetVisible(visible);
}

void Interface_GUIControlFadeLabel::AddLabel(void *kodiBase, void* handle, const char *label)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlFadeLabel::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle || !label)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlFadeLabel::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  CGUIMessage msg(GUI_MSG_LABEL_ADD, static_cast<CGUIFadeLabelControl*>(handle)->GetParentID(), static_cast<CGUIFadeLabelControl*>(handle)->GetID());
  msg.SetLabel(label);
  static_cast<CGUIFadeLabelControl*>(handle)->OnMessage(msg);
}

void Interface_GUIControlFadeLabel::GetLabel(void *kodiBase, void* handle, char &label, unsigned int &maxStringSize)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlFadeLabel::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlFadeLabel::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  CGUIMessage msg(GUI_MSG_ITEM_SELECTED, static_cast<CGUIFadeLabelControl*>(handle)->GetParentID(), static_cast<CGUIFadeLabelControl*>(handle)->GetID());
  static_cast<CGUIFadeLabelControl*>(handle)->OnMessage(msg);
  std::string text = msg.GetLabel();
  strncpy(&label, text.c_str(), maxStringSize);
  maxStringSize = text.length();
}

void Interface_GUIControlFadeLabel::SetScrolling(void *kodiBase, void* handle, bool scroll)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlFadeLabel::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlFadeLabel::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  static_cast<CGUIFadeLabelControl*>(handle)->SetScrolling(scroll);
}

void Interface_GUIControlFadeLabel::Reset(void *kodiBase, void* handle)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlFadeLabel::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlFadeLabel::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  CGUIMessage msg(GUI_MSG_LABEL_RESET, static_cast<CGUIFadeLabelControl*>(handle)->GetParentID(), static_cast<CGUIFadeLabelControl*>(handle)->GetID());
  static_cast<CGUIFadeLabelControl*>(handle)->OnMessage(msg);
}

} /* namespace ADDON */
} /* extern "C" */
