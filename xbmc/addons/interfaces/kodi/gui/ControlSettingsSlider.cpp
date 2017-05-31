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

#include "ControlSettingsSlider.h"
#include "addons/kodi-addon-dev-kit/include/kodi/gui/ControlSettingsSlider.h"

#include "addons/AddonDll.h"
#include "guilib/GUISettingsSliderControl.h"
#include "guilib/GUIWindowManager.h"
#include "utils/log.h"

extern "C"
{
namespace ADDON
{

void Interface_GUIControlSettingsSlider::Init(AddonGlobalInterface* addonInterface)
{
  addonInterface->toKodi->kodi_gui->controlSettingsSlider.SetVisible = SetVisible;
  addonInterface->toKodi->kodi_gui->controlSettingsSlider.SetEnabled = SetEnabled;

  addonInterface->toKodi->kodi_gui->controlSettingsSlider.SetText = SetText;
  addonInterface->toKodi->kodi_gui->controlSettingsSlider.Reset = Reset;

  addonInterface->toKodi->kodi_gui->controlSettingsSlider.SetIntRange = SetIntRange;
  addonInterface->toKodi->kodi_gui->controlSettingsSlider.SetIntValue = SetIntValue;
  addonInterface->toKodi->kodi_gui->controlSettingsSlider.GetIntValue = GetIntValue;
  addonInterface->toKodi->kodi_gui->controlSettingsSlider.SetIntInterval = SetIntInterval;

  addonInterface->toKodi->kodi_gui->controlSettingsSlider.SetPercentage = SetPercentage;
  addonInterface->toKodi->kodi_gui->controlSettingsSlider.GetPercentage = GetPercentage;

  addonInterface->toKodi->kodi_gui->controlSettingsSlider.SetFloatRange = SetFloatRange;
  addonInterface->toKodi->kodi_gui->controlSettingsSlider.SetFloatValue = SetFloatValue;
  addonInterface->toKodi->kodi_gui->controlSettingsSlider.GetFloatValue = GetFloatValue;
  addonInterface->toKodi->kodi_gui->controlSettingsSlider.SetFloatInterval = SetFloatInterval;
}

void Interface_GUIControlSettingsSlider::SetVisible(void* kodiBase, void* handle, bool visible)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSettingsSlider::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSettingsSlider::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  static_cast<CGUISettingsSliderControl*>(handle)->SetVisible(visible);
}

void Interface_GUIControlSettingsSlider::SetEnabled(void* kodiBase, void* handle, bool enabled)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSettingsSlider::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSettingsSlider::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  static_cast<CGUISettingsSliderControl*>(handle)->SetEnabled(enabled);
}

void Interface_GUIControlSettingsSlider::SetText(void* kodiBase, void* handle, const char *text)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSettingsSlider::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle || !text)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSettingsSlider::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  CGUISettingsSliderControl* pControl = static_cast<CGUISettingsSliderControl*>(handle);

  // create message
  CGUIMessage msg(GUI_MSG_LABEL_SET, pControl->GetParentID(), pControl->GetID());
  msg.SetLabel(text);

  // send message
  g_windowManager.SendThreadMessage(msg, pControl->GetParentID());
}

void Interface_GUIControlSettingsSlider::Reset(void* kodiBase, void* handle)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSettingsSlider::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSettingsSlider::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  CGUISettingsSliderControl* pControl = static_cast<CGUISettingsSliderControl*>(handle);

  CGUIMessage msg(GUI_MSG_LABEL_RESET, pControl->GetParentID(), pControl->GetID());
  g_windowManager.SendThreadMessage(msg, pControl->GetParentID());
}

void Interface_GUIControlSettingsSlider::SetIntRange(void* kodiBase, void* handle, int start, int end)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSettingsSlider::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSettingsSlider::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  CGUISettingsSliderControl* pControl = static_cast<CGUISettingsSliderControl*>(handle);
  pControl->SetType(SLIDER_CONTROL_TYPE_INT);
  pControl->SetRange(start, end);
}

void Interface_GUIControlSettingsSlider::SetIntValue(void* kodiBase, void* handle, int value)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSettingsSlider::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSettingsSlider::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  CGUISettingsSliderControl* pControl = static_cast<CGUISettingsSliderControl*>(handle);
  pControl->SetType(SLIDER_CONTROL_TYPE_INT);
  pControl->SetIntValue(value);
}

int Interface_GUIControlSettingsSlider::GetIntValue(void* kodiBase, void* handle)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSettingsSlider::%s - invalid data", __FUNCTION__);
    return -1;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSettingsSlider::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return -1;
  }

  return static_cast<CGUISettingsSliderControl*>(handle)->GetIntValue();
}

void Interface_GUIControlSettingsSlider::SetIntInterval(void* kodiBase, void* handle, int interval)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSettingsSlider::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSettingsSlider::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  static_cast<CGUISettingsSliderControl*>(handle)->SetIntInterval(interval);
}

void Interface_GUIControlSettingsSlider::SetPercentage(void* kodiBase, void* handle, float percent)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSettingsSlider::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSettingsSlider::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  CGUISettingsSliderControl* pControl = static_cast<CGUISettingsSliderControl*>(handle);
  pControl->SetType(SLIDER_CONTROL_TYPE_PERCENTAGE);
  pControl->SetPercentage(percent);
}

float Interface_GUIControlSettingsSlider::GetPercentage(void* kodiBase, void* handle)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSettingsSlider::%s - invalid data", __FUNCTION__);
    return 0.0f;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSettingsSlider::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return 0.0f;
  }

  return static_cast<CGUISettingsSliderControl*>(handle)->GetPercentage();
}

void Interface_GUIControlSettingsSlider::SetFloatRange(void* kodiBase, void* handle, float start, float end)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSettingsSlider::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSettingsSlider::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  CGUISettingsSliderControl* pControl = static_cast<CGUISettingsSliderControl*>(handle);
  pControl->SetType(SLIDER_CONTROL_TYPE_FLOAT);
  pControl->SetFloatRange(start, end);
}

void Interface_GUIControlSettingsSlider::SetFloatValue(void* kodiBase, void* handle, float value)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSettingsSlider::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSettingsSlider::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  CGUISettingsSliderControl* pControl = static_cast<CGUISettingsSliderControl*>(handle);
  pControl->SetType(SLIDER_CONTROL_TYPE_FLOAT);
  pControl->SetFloatValue(value);
}

float Interface_GUIControlSettingsSlider::GetFloatValue(void* kodiBase, void* handle)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSettingsSlider::%s - invalid data", __FUNCTION__);
    return 0.0f;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSettingsSlider::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return 0.0f;
  }

  return static_cast<CGUISettingsSliderControl*>(handle)->GetFloatValue();
}

void Interface_GUIControlSettingsSlider::SetFloatInterval(void* kodiBase, void* handle, float interval)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSettingsSlider::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSettingsSlider::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  static_cast<CGUISettingsSliderControl*>(handle)->SetFloatInterval(interval);
}

} /* namespace ADDON */
} /* extern "C" */
