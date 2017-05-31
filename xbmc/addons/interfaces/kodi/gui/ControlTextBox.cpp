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

#include "ControlTextBox.h"
#include "addons/kodi-addon-dev-kit/include/kodi/gui/ControlTextBox.h"

#include "addons/AddonDll.h"
#include "guilib/GUITextBox.h"
#include "guilib/GUIWindowManager.h"
#include "utils/log.h"

extern "C"
{
namespace ADDON
{

void Interface_GUIControlTextBox::Init(AddonGlobalInterface* addonInterface)
{
  addonInterface->toKodi->kodi_gui->controlTextBox.SetVisible = SetVisible;
  addonInterface->toKodi->kodi_gui->controlTextBox.Reset = Reset;
  addonInterface->toKodi->kodi_gui->controlTextBox.SetText = SetText;
  addonInterface->toKodi->kodi_gui->controlTextBox.GetText = GetText;
  addonInterface->toKodi->kodi_gui->controlTextBox.Scroll = Scroll;
  addonInterface->toKodi->kodi_gui->controlTextBox.SetAutoScrolling = SetAutoScrolling;
}

void Interface_GUIControlTextBox::SetVisible(void* kodiBase, void* handle, bool visible)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlTextBox::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlTextBox::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  static_cast<CGUITextBox*>(handle)->SetVisible(visible);
}

void Interface_GUIControlTextBox::Reset(void* kodiBase, void* handle)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlTextBox::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlTextBox::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  CGUITextBox* textBox = static_cast<CGUITextBox*>(handle);

  CGUIMessage msg(GUI_MSG_LABEL_RESET, textBox->GetParentID(), textBox->GetID());
  g_windowManager.SendThreadMessage(msg, textBox->GetParentID());
}

void Interface_GUIControlTextBox::SetText(void* kodiBase, void* handle, const char *text)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlTextBox::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle || !text)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlTextBox::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  CGUITextBox* textBox = static_cast<CGUITextBox*>(handle);

  // create message
  CGUIMessage msg(GUI_MSG_LABEL_SET, textBox->GetParentID(), textBox->GetID());
  msg.SetLabel(text);

  // send message
  g_windowManager.SendThreadMessage(msg, textBox->GetParentID());
}

void Interface_GUIControlTextBox::GetText(void* kodiBase, void* handle, char &text, unsigned int &maxStringSize)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlTextBox::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlTextBox::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  std::string tmpText = static_cast<CGUITextBox*>(handle)->GetDescription();
  strncpy(&text, tmpText.c_str(), maxStringSize);
  maxStringSize = tmpText.size();
}

void Interface_GUIControlTextBox::Scroll(void* kodiBase, void* handle, unsigned int position)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlTextBox::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlTextBox::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  static_cast<CGUITextBox*>(handle)->Scroll(position);
}

void Interface_GUIControlTextBox::SetAutoScrolling(void* kodiBase, void* handle, int delay, int time, int repeat)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlTextBox::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlTextBox::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  static_cast<CGUITextBox*>(handle)->SetAutoScrolling(delay, time, repeat);
}

} /* namespace ADDON */
} /* extern "C" */
