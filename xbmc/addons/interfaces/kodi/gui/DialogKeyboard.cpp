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

#include "DialogKeyboard.h"
#include "addons/kodi-addon-dev-kit/include/kodi/gui/DialogKeyboard.h"

#include "addons/AddonDll.h"
#include "guilib/GUIKeyboardFactory.h"
#include "utils/log.h"
#include "utils/Variant.h"

namespace ADDON
{
extern "C"
{

void Interface_GUIDialogKeyboard::Init(AddonGlobalInterface* addonInterface)
{
  addonInterface->toKodi->kodi_gui->dialogKeyboard.ShowAndGetInputWithHead = ShowAndGetInputWithHead;
  addonInterface->toKodi->kodi_gui->dialogKeyboard.ShowAndGetInput = ShowAndGetInput;
  addonInterface->toKodi->kodi_gui->dialogKeyboard.ShowAndGetNewPasswordWithHead = ShowAndGetNewPasswordWithHead;
  addonInterface->toKodi->kodi_gui->dialogKeyboard.ShowAndGetNewPassword = ShowAndGetNewPassword;
  addonInterface->toKodi->kodi_gui->dialogKeyboard.ShowAndVerifyNewPasswordWithHead = ShowAndVerifyNewPasswordWithHead;
  addonInterface->toKodi->kodi_gui->dialogKeyboard.ShowAndVerifyNewPassword = ShowAndVerifyNewPassword;
  addonInterface->toKodi->kodi_gui->dialogKeyboard.ShowAndVerifyPassword = ShowAndVerifyPassword;
  addonInterface->toKodi->kodi_gui->dialogKeyboard.ShowAndGetFilter = ShowAndGetFilter;
  addonInterface->toKodi->kodi_gui->dialogKeyboard.SendTextToActiveKeyboard = SendTextToActiveKeyboard;
  addonInterface->toKodi->kodi_gui->dialogKeyboard.isKeyboardActivated   = isKeyboardActivated;
}

bool Interface_GUIDialogKeyboard::ShowAndGetInputWithHead(void* kodiBase, char &aTextString, unsigned int &maxStringSize, const char *strHeading, bool allowEmptyResult, bool hiddenInput, unsigned int autoCloseMs)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogKeyboard::%s - invalid data", __FUNCTION__);
    return false;
  }

  std::string str = &aTextString;
  bool bRet = CGUIKeyboardFactory::ShowAndGetInput(str, CVariant{strHeading}, allowEmptyResult, hiddenInput, autoCloseMs);
  if (bRet)
    strncpy(&aTextString, str.c_str(), maxStringSize);
  maxStringSize = str.length();
  return bRet;
}

bool Interface_GUIDialogKeyboard::ShowAndGetInput(void* kodiBase, char &aTextString, unsigned int &maxStringSize, bool allowEmptyResult, unsigned int autoCloseMs)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogKeyboard::%s - invalid data", __FUNCTION__);
    return false;
  }

  std::string str = &aTextString;
  bool bRet = CGUIKeyboardFactory::ShowAndGetInput(str, allowEmptyResult, autoCloseMs);
  if (bRet)
    strncpy(&aTextString, str.c_str(), maxStringSize);
  maxStringSize = str.length();
  return bRet;
}

bool Interface_GUIDialogKeyboard::ShowAndGetNewPasswordWithHead(void* kodiBase, char &strNewPassword, unsigned int &maxStringSize, const char *strHeading, bool allowEmptyResult, unsigned int autoCloseMs)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogKeyboard::%s - invalid data", __FUNCTION__);
    return false;
  }

  std::string str = &strNewPassword;
  bool bRet = CGUIKeyboardFactory::ShowAndGetNewPassword(str, strHeading, allowEmptyResult, autoCloseMs);
  if (bRet)
    strncpy(&strNewPassword, str.c_str(), maxStringSize);
  maxStringSize = str.length();
  return bRet;
}

bool Interface_GUIDialogKeyboard::ShowAndGetNewPassword(void* kodiBase, char &strNewPassword, unsigned int &maxStringSize, unsigned int autoCloseMs)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogKeyboard::%s - invalid data", __FUNCTION__);
    return false;
  }

  std::string str = &strNewPassword;
  bool bRet = CGUIKeyboardFactory::ShowAndGetNewPassword(str, autoCloseMs);
  if (bRet)
    strncpy(&strNewPassword, str.c_str(), maxStringSize);
  maxStringSize = str.length();
  return bRet;
}

bool Interface_GUIDialogKeyboard::ShowAndVerifyNewPasswordWithHead(void* kodiBase, char &strNewPassword, unsigned int &maxStringSize, const char *strHeading, bool allowEmptyResult, unsigned int autoCloseMs)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogKeyboard::%s - invalid data", __FUNCTION__);
    return false;
  }

  std::string str = &strNewPassword;
  bool bRet = CGUIKeyboardFactory::ShowAndVerifyNewPassword(str, strHeading, allowEmptyResult, autoCloseMs);
  if (bRet)
    strncpy(&strNewPassword, str.c_str(), maxStringSize);
  maxStringSize = str.length();
  return bRet;
}

bool Interface_GUIDialogKeyboard::ShowAndVerifyNewPassword(void* kodiBase, char &strNewPassword, unsigned int &maxStringSize, unsigned int autoCloseMs)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogKeyboard::%s - invalid data", __FUNCTION__);
    return false;
  }

  std::string str = &strNewPassword;
  bool bRet = CGUIKeyboardFactory::ShowAndVerifyNewPassword(str, autoCloseMs);
  if (bRet)
    strncpy(&strNewPassword, str.c_str(), maxStringSize);
  maxStringSize = str.length();
  return bRet;
}

int Interface_GUIDialogKeyboard::ShowAndVerifyPassword(void* kodiBase, char &strPassword, unsigned int &maxStringSize, const char *strHeading, int iRetries, unsigned int autoCloseMs)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogKeyboard::%s - invalid data", __FUNCTION__);
    return false;
  }

  std::string str = &strPassword;
  int iRet = CGUIKeyboardFactory::ShowAndVerifyPassword(str, strHeading, iRetries, autoCloseMs);
  if (iRet)
    strncpy(&strPassword, str.c_str(), maxStringSize);
  maxStringSize = str.length();
  return iRet;
}

bool Interface_GUIDialogKeyboard::ShowAndGetFilter(void* kodiBase, char &aTextString, unsigned int &maxStringSize, bool searching, unsigned int autoCloseMs)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogKeyboard::%s - invalid data", __FUNCTION__);
    return false;
  }

  std::string str = &aTextString;
  bool bRet = CGUIKeyboardFactory::ShowAndGetFilter(str, searching, autoCloseMs);
  if (bRet)
    strncpy(&aTextString, str.c_str(), maxStringSize);
  maxStringSize = str.length();
  return bRet;
}

bool Interface_GUIDialogKeyboard::SendTextToActiveKeyboard(void* kodiBase, const char *aTextString, bool closeKeyboard)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogKeyboard::%s - invalid data", __FUNCTION__);
    return false;
  }

  return CGUIKeyboardFactory::SendTextToActiveKeyboard(aTextString, closeKeyboard);
}

bool Interface_GUIDialogKeyboard::isKeyboardActivated(void* kodiBase)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogKeyboard::%s - invalid data", __FUNCTION__);
    return false;
  }

  return CGUIKeyboardFactory::isKeyboardActivated();
}

} /* extern "C" */
} /* namespace ADDON */
