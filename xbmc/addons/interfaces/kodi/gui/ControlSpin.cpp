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

#include "ControlSpin.h"
#include "addons/kodi-addon-dev-kit/include/kodi/gui/ControlSpin.h"

#include "addons/AddonDll.h"
#include "guilib/GUISpinControlEx.h"
#include "guilib/GUIWindowManager.h"
#include "utils/log.h"

extern "C"
{
namespace ADDON
{

void Interface_GUIControlSpin::Init(AddonGlobalInterface* addonInterface)
{
  addonInterface->toKodi->kodi_gui->controlSpin.SetVisible = SetVisible;
  addonInterface->toKodi->kodi_gui->controlSpin.SetEnabled = SetEnabled;

  addonInterface->toKodi->kodi_gui->controlSpin.SetText = SetText;
  addonInterface->toKodi->kodi_gui->controlSpin.Reset = Reset;
  addonInterface->toKodi->kodi_gui->controlSpin.SetType = SetType;

  addonInterface->toKodi->kodi_gui->controlSpin.AddStringLabel = AddStringLabel;
  addonInterface->toKodi->kodi_gui->controlSpin.SetStringValue = SetStringValue;
  addonInterface->toKodi->kodi_gui->controlSpin.GetStringValue = GetStringValue;

  addonInterface->toKodi->kodi_gui->controlSpin.AddIntLabel = AddIntLabel;
  addonInterface->toKodi->kodi_gui->controlSpin.SetIntRange = SetIntRange;
  addonInterface->toKodi->kodi_gui->controlSpin.SetIntValue = SetIntValue;
  addonInterface->toKodi->kodi_gui->controlSpin.GetIntValue = GetIntValue;

  addonInterface->toKodi->kodi_gui->controlSpin.SetFloatRange = SetFloatRange;
  addonInterface->toKodi->kodi_gui->controlSpin.SetFloatValue = SetFloatValue;
  addonInterface->toKodi->kodi_gui->controlSpin.GetFloatValue = GetFloatValue;
  addonInterface->toKodi->kodi_gui->controlSpin.SetFloatInterval = SetFloatInterval;
}

void Interface_GUIControlSpin::SetVisible(void* kodiBase, void* handle, bool visible)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSpin::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSpin::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  static_cast<CGUISpinControlEx*>(handle)->SetVisible(visible);
}

void Interface_GUIControlSpin::SetEnabled(void* kodiBase, void* handle, bool enabled)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSpin::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSpin::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  static_cast<CGUISpinControlEx*>(handle)->SetEnabled(enabled);
}

void Interface_GUIControlSpin::SetText(void* kodiBase, void* handle, const char *text)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSpin::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle || !text)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSpin::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  CGUISpinControlEx* pControl = static_cast<CGUISpinControlEx*>(handle);

  // create message
  CGUIMessage msg(GUI_MSG_LABEL_SET, pControl->GetParentID(), pControl->GetID());
  msg.SetLabel(text);

  // send message
  g_windowManager.SendThreadMessage(msg, pControl->GetParentID());
}

void Interface_GUIControlSpin::Reset(void* kodiBase, void* handle)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSpin::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSpin::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  CGUISpinControlEx* pControl = static_cast<CGUISpinControlEx*>(handle);

  CGUIMessage msg(GUI_MSG_LABEL_RESET, pControl->GetParentID(), pControl->GetID());
  g_windowManager.SendThreadMessage(msg, pControl->GetParentID());
}

void Interface_GUIControlSpin::SetType(void* kodiBase, void* handle, int type)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSpin::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSpin::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  static_cast<CGUISpinControlEx*>(handle)->SetType(type);
}


void Interface_GUIControlSpin::AddStringLabel(void* kodiBase, void* handle, const char* label, const char* value)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSpin::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle || !label || !value)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSpin::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  static_cast<CGUISpinControlEx*>(handle)->AddLabel(std::string(label), std::string(value));
}

void Interface_GUIControlSpin::SetStringValue(void* kodiBase, void* handle, const char* value)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSpin::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle || !value)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSpin::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  static_cast<CGUISpinControlEx*>(handle)->SetStringValue(std::string(value));
}

void Interface_GUIControlSpin::GetStringValue(void* kodiBase, void* handle, char &value, unsigned int &maxStringSize)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSpin::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSpin::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  std::string text = static_cast<CGUISpinControlEx*>(handle)->GetStringValue();
  strncpy(&value, text.c_str(), maxStringSize);
  maxStringSize = text.length();
}

void Interface_GUIControlSpin::AddIntLabel(void* kodiBase, void* handle, const char* label, int value)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSpin::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle || !label)
    throw std::logic_error(StringUtils::Format("ADDON::Interface_GUIControlSpin::%s - invalid handler data", __FUNCTION__).c_str());

  static_cast<CGUISpinControlEx*>(handle)->AddLabel(std::string(label), value);
}

void Interface_GUIControlSpin::SetIntRange(void* kodiBase, void* handle, int start, int end)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSpin::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSpin::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  static_cast<CGUISpinControlEx*>(handle)->SetRange(start, end);
}

void Interface_GUIControlSpin::SetIntValue(void* kodiBase, void* handle, int value)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSpin::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSpin::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  static_cast<CGUISpinControlEx*>(handle)->SetValue(value);
}

int Interface_GUIControlSpin::GetIntValue(void* kodiBase, void* handle)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSpin::%s - invalid data", __FUNCTION__);
    return 0;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSpin::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return 0;
  }

  return static_cast<CGUISpinControlEx*>(handle)->GetValue();
}

void Interface_GUIControlSpin::SetFloatRange(void* kodiBase, void* handle, float start, float end)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSpin::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSpin::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  static_cast<CGUISpinControlEx*>(handle)->SetFloatRange(start, end);
}

void Interface_GUIControlSpin::SetFloatValue(void* kodiBase, void* handle, float value)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSpin::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSpin::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  static_cast<CGUISpinControlEx*>(handle)->SetFloatValue(value);
}

float Interface_GUIControlSpin::GetFloatValue(void* kodiBase, void* handle)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSpin::%s - invalid data", __FUNCTION__);
    return 0.0f;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSpin::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return 0.0f;
  }

  return static_cast<CGUISpinControlEx*>(handle)->GetFloatValue();
}

void Interface_GUIControlSpin::SetFloatInterval(void* kodiBase, void* handle, float interval)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSpin::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSpin::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  static_cast<CGUISpinControlEx*>(handle)->SetFloatInterval(interval);
}

} /* namespace ADDON */
} /* extern "C" */
