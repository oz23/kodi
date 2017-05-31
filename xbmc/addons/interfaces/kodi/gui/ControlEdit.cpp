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

#include "ControlEdit.h"
#include "addons/kodi-addon-dev-kit/include/kodi/gui/ControlEdit.h"

#include "addons/AddonDll.h"
#include "guilib/GUIEditControl.h"
#include "guilib/GUIWindowManager.h"
#include "utils/log.h"

extern "C"
{
namespace ADDON
{

void Interface_GUIControlEdit::Init(AddonGlobalInterface* addonInterface)
{
  addonInterface->toKodi->kodi_gui->controlEdit.SetVisible = SetVisible;
  addonInterface->toKodi->kodi_gui->controlEdit.SetEnabled = SetEnabled;
  addonInterface->toKodi->kodi_gui->controlEdit.SetLabel = SetLabel;
  addonInterface->toKodi->kodi_gui->controlEdit.GetLabel = GetLabel;
  addonInterface->toKodi->kodi_gui->controlEdit.SetText = SetText;
  addonInterface->toKodi->kodi_gui->controlEdit.GetText = GetText;
  addonInterface->toKodi->kodi_gui->controlEdit.SetCursorPosition = SetCursorPosition;
  addonInterface->toKodi->kodi_gui->controlEdit.GetCursorPosition = GetCursorPosition;
  addonInterface->toKodi->kodi_gui->controlEdit.SetInputType = SetInputType;
}

void Interface_GUIControlEdit::SetVisible(void* kodiBase, void* handle, bool yesNo)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlEdit::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlEdit::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  static_cast<CGUIEditControl*>(handle)->SetVisible(yesNo);
}

void Interface_GUIControlEdit::SetEnabled(void* kodiBase, void* handle, bool yesNo)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlEdit::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlEdit::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  static_cast<CGUIEditControl*>(handle)->SetEnabled(yesNo);
}

void Interface_GUIControlEdit::SetLabel(void* kodiBase, void* handle, const char *label)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlEdit::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlEdit::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  static_cast<CGUIEditControl*>(handle)->SetLabel(label);
}

void Interface_GUIControlEdit::GetLabel(void* kodiBase, void* handle, char &label, unsigned int &maxStringSize)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlEdit::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlEdit::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  std::string text = static_cast<CGUIEditControl*>(handle)->GetLabel();
  strncpy(&label, text.c_str(), maxStringSize);
  maxStringSize = text.length();
}

void Interface_GUIControlEdit::SetText(void* kodiBase, void* handle, const char* text)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlEdit::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlEdit::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  static_cast<CGUIEditControl*>(handle)->SetLabel2(text);
}

void Interface_GUIControlEdit::GetText(void* kodiBase, void* handle, char& text, unsigned int &maxStringSize)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlEdit::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlEdit::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  std::string textTmp = static_cast<CGUIEditControl*>(handle)->GetLabel2();
  strncpy(&text, textTmp.c_str(), maxStringSize);
  maxStringSize = textTmp.length();
}

unsigned int Interface_GUIControlEdit::GetCursorPosition(void* kodiBase, void* handle)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlEdit::%s - invalid data", __FUNCTION__);
    return 0;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlEdit::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return 0;
  }

  return static_cast<CGUIEditControl*>(handle)->GetCursorPosition();
}

void Interface_GUIControlEdit::SetCursorPosition(void* kodiBase, void* handle, unsigned int position)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlEdit::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlEdit::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  static_cast<CGUIEditControl*>(handle)->SetCursorPosition(position);
}

void Interface_GUIControlEdit::SetInputType(void* kodiBase, void* handle, int type, const char *heading)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlEdit::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlEdit::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  CGUIEditControl::INPUT_TYPE kodiType;
  switch (type)
  {
    case ADDON_INPUT_TYPE_TEXT:
      kodiType = CGUIEditControl::INPUT_TYPE_TEXT;
      break;
    case ADDON_INPUT_TYPE_NUMBER:
      kodiType = CGUIEditControl::INPUT_TYPE_NUMBER;
      break;
    case ADDON_INPUT_TYPE_SECONDS:
      kodiType = CGUIEditControl::INPUT_TYPE_SECONDS;
      break;
    case ADDON_INPUT_TYPE_TIME:
      kodiType = CGUIEditControl::INPUT_TYPE_TIME;
      break;
    case ADDON_INPUT_TYPE_DATE:
      kodiType = CGUIEditControl::INPUT_TYPE_DATE;
      break;
    case ADDON_INPUT_TYPE_IPADDRESS:
      kodiType = CGUIEditControl::INPUT_TYPE_IPADDRESS;
      break;
    case ADDON_INPUT_TYPE_PASSWORD:
      kodiType = CGUIEditControl::INPUT_TYPE_PASSWORD;
      break;
    case ADDON_INPUT_TYPE_PASSWORD_MD5:
      kodiType = CGUIEditControl::INPUT_TYPE_PASSWORD_MD5;
      break;
    case ADDON_INPUT_TYPE_SEARCH:
      kodiType = CGUIEditControl::INPUT_TYPE_SEARCH;
      break;
    case ADDON_INPUT_TYPE_FILTER:
      kodiType = CGUIEditControl::INPUT_TYPE_FILTER;
      break;
    case ADDON_INPUT_TYPE_READONLY:
    default:
      kodiType = CGUIEditControl::INPUT_TYPE_PASSWORD_NUMBER_VERIFY_NEW;
  }

  static_cast<CGUIEditControl*>(handle)->SetInputType(kodiType, heading);
}

} /* namespace ADDON */
} /* extern "C" */
