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

#include "ControlSlider.h"
#include "addons/kodi-addon-dev-kit/include/kodi/gui/ControlSlider.h"

#include "addons/AddonDll.h"
#include "guilib/GUISliderControl.h"
#include "guilib/GUIWindowManager.h"
#include "utils/log.h"

extern "C"
{
namespace ADDON
{

void Interface_GUIControlSlider::Init(AddonGlobalInterface* addonInterface)
{
  addonInterface->toKodi->kodi_gui->controlSlider.SetVisible = SetVisible;
  addonInterface->toKodi->kodi_gui->controlSlider.SetEnabled = SetEnabled;

  addonInterface->toKodi->kodi_gui->controlSlider.Reset = Reset;
  addonInterface->toKodi->kodi_gui->controlSlider.GetDescription = GetDescription;

  addonInterface->toKodi->kodi_gui->controlSlider.SetIntRange = SetIntRange;
  addonInterface->toKodi->kodi_gui->controlSlider.SetIntValue = SetIntValue;
  addonInterface->toKodi->kodi_gui->controlSlider.GetIntValue = GetIntValue;
  addonInterface->toKodi->kodi_gui->controlSlider.SetIntInterval = SetIntInterval;

  addonInterface->toKodi->kodi_gui->controlSlider.SetPercentage = SetPercentage;
  addonInterface->toKodi->kodi_gui->controlSlider.GetPercentage = GetPercentage;

  addonInterface->toKodi->kodi_gui->controlSlider.SetFloatRange = SetFloatRange;
  addonInterface->toKodi->kodi_gui->controlSlider.SetFloatValue = SetFloatValue;
  addonInterface->toKodi->kodi_gui->controlSlider.GetFloatValue = GetFloatValue;
  addonInterface->toKodi->kodi_gui->controlSlider.SetFloatInterval = SetFloatInterval;
}

void Interface_GUIControlSlider::SetVisible(void* kodiBase, void* handle, bool visible)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSlider::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSlider::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  static_cast<CGUISliderControl*>(handle)->SetVisible(visible);
}

void Interface_GUIControlSlider::SetEnabled(void* kodiBase, void* handle, bool enabled)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSlider::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSlider::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  static_cast<CGUISliderControl*>(handle)->SetEnabled(enabled);
}

void Interface_GUIControlSlider::Reset(void* kodiBase, void* handle)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSlider::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSlider::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  CGUISliderControl* pControl = static_cast<CGUISliderControl*>(handle);

  CGUIMessage msg(GUI_MSG_LABEL_RESET, pControl->GetParentID(), pControl->GetID());
  g_windowManager.SendThreadMessage(msg, pControl->GetParentID());
}

void Interface_GUIControlSlider::GetDescription(void* kodiBase, void* handle, char &label, unsigned int &maxStringSize)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSlider::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSlider::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  std::string text = static_cast<CGUISliderControl*>(handle)->GetDescription();
  strncpy(&label, text.c_str(), maxStringSize);
  maxStringSize = text.length();
}

void Interface_GUIControlSlider::SetIntRange(void* kodiBase, void* handle, int iStart, int iEnd)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSlider::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSlider::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  CGUISliderControl* pControl = static_cast<CGUISliderControl *>(handle);
  pControl->SetType(SLIDER_CONTROL_TYPE_INT);
  pControl->SetRange(iStart, iEnd);
}

void Interface_GUIControlSlider::SetIntValue(void* kodiBase, void* handle, int value)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSlider::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSlider::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  CGUISliderControl* pControl = static_cast<CGUISliderControl *>(handle);
  pControl->SetType(SLIDER_CONTROL_TYPE_INT);
  pControl->SetIntValue(value);
}

int Interface_GUIControlSlider::GetIntValue(void* kodiBase, void* handle)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSlider::%s - invalid data", __FUNCTION__);
    return 0;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSlider::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return 0;
  }

  return static_cast<CGUISliderControl*>(handle)->GetIntValue();
}

void Interface_GUIControlSlider::SetIntInterval(void* kodiBase, void* handle, int interval)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSlider::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSlider::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  static_cast<CGUISliderControl*>(handle)->SetIntInterval(interval);
}

void Interface_GUIControlSlider::SetPercentage(void* kodiBase, void* handle, float percent)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSlider::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSlider::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  CGUISliderControl* pControl = static_cast<CGUISliderControl *>(handle);
  pControl->SetType(SLIDER_CONTROL_TYPE_PERCENTAGE);
  pControl->SetPercentage(percent);
}

float Interface_GUIControlSlider::GetPercentage(void* kodiBase, void* handle)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSlider::%s - invalid data", __FUNCTION__);
    return 0.0f;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSlider::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return 0.0f;
  }

  return static_cast<CGUISliderControl*>(handle)->GetPercentage();
}

void Interface_GUIControlSlider::SetFloatRange(void* kodiBase, void* handle, float start, float end)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSlider::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSlider::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  CGUISliderControl* pControl = static_cast<CGUISliderControl *>(handle);
  pControl->SetType(SLIDER_CONTROL_TYPE_FLOAT);
  pControl->SetFloatRange(start, end);
}

void Interface_GUIControlSlider::SetFloatValue(void* kodiBase, void* handle, float value)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSlider::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSlider::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  CGUISliderControl* pControl = static_cast<CGUISliderControl *>(handle);
  pControl->SetType(SLIDER_CONTROL_TYPE_FLOAT);
  pControl->SetFloatValue(value);
}

float Interface_GUIControlSlider::GetFloatValue(void* kodiBase, void* handle)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSlider::%s - invalid data", __FUNCTION__);
    return 0.0f;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSlider::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return 0.0f;
  }

  return static_cast<CGUISliderControl*>(handle)->GetFloatValue();
}

void Interface_GUIControlSlider::SetFloatInterval(void* kodiBase, void* handle, float interval)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSlider::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlSlider::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  static_cast<CGUISliderControl*>(handle)->SetFloatInterval(interval);
}

} /* namespace ADDON */
} /* extern "C" */
