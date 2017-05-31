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

#include "DialogNumeric.h"
#include "addons/kodi-addon-dev-kit/include/kodi/gui/DialogNumeric.h"

#include "XBDateTime.h"
#include "addons/AddonDll.h"
#include "dialogs/GUIDialogNumeric.h"
#include "utils/log.h"

extern "C"
{
namespace ADDON
{

void Interface_GUIDialogNumeric::Init(AddonGlobalInterface* addonInterface)
{
  addonInterface->toKodi->kodi_gui->dialogNumeric.ShowAndVerifyNewPassword = ShowAndVerifyNewPassword;
  addonInterface->toKodi->kodi_gui->dialogNumeric.ShowAndVerifyPassword = ShowAndVerifyPassword;
  addonInterface->toKodi->kodi_gui->dialogNumeric.ShowAndVerifyInput = ShowAndVerifyInput;
  addonInterface->toKodi->kodi_gui->dialogNumeric.ShowAndGetTime = ShowAndGetTime;
  addonInterface->toKodi->kodi_gui->dialogNumeric.ShowAndGetDate = ShowAndGetDate;
  addonInterface->toKodi->kodi_gui->dialogNumeric.ShowAndGetIPAddress = ShowAndGetIPAddress;
  addonInterface->toKodi->kodi_gui->dialogNumeric.ShowAndGetNumber = ShowAndGetNumber;
  addonInterface->toKodi->kodi_gui->dialogNumeric.ShowAndGetSeconds = ShowAndGetSeconds;
}

bool Interface_GUIDialogNumeric::ShowAndVerifyNewPassword(void* kodiBase, char &newPassword, unsigned int &maxStringSize)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogNumeric::%s - invalid data", __FUNCTION__);
    return false;
  }

  std::string str = &newPassword;
  bool bRet = CGUIDialogNumeric::ShowAndVerifyNewPassword(str);
  if (bRet)
    strncpy(&newPassword, str.c_str(), maxStringSize);
  maxStringSize = str.length();
  return bRet;
}

int Interface_GUIDialogNumeric::ShowAndVerifyPassword(void* kodiBase, char &password, unsigned int &maxStringSize, const char *heading, int retries)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogNumeric::%s - invalid data", __FUNCTION__);
    return -1;
  }

  std::string str = &password;
  int bRet = CGUIDialogNumeric::ShowAndVerifyPassword(str, heading, retries);
  if (bRet)
    strncpy(&password, str.c_str(), maxStringSize);
  maxStringSize = str.length();
  return bRet;
}

bool Interface_GUIDialogNumeric::ShowAndVerifyInput(void* kodiBase, char &toVerify, unsigned int &maxStringSize, const char *heading, bool verifyInput)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogNumeric::%s - invalid data", __FUNCTION__);
    return false;
  }

  std::string str = &toVerify;
  bool bRet = CGUIDialogNumeric::ShowAndVerifyInput(str, heading, verifyInput);
  if (bRet)
    strncpy(&toVerify, str.c_str(), maxStringSize);
  maxStringSize = str.length();
  return bRet;
}

bool Interface_GUIDialogNumeric::ShowAndGetTime(void* kodiBase, tm &time, const char *heading)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogNumeric::%s - invalid data", __FUNCTION__);
    return false;
  }

  SYSTEMTIME systemTime;
  CDateTime dateTime(time);
  dateTime.GetAsSystemTime(systemTime);
  if (CGUIDialogNumeric::ShowAndGetTime(systemTime, heading))
  {
    dateTime = systemTime;
    dateTime.GetAsTm(time);
    return true;
  }
  return false;
}

bool Interface_GUIDialogNumeric::ShowAndGetDate(void* kodiBase, tm &date, const char *heading)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogNumeric::%s - invalid data", __FUNCTION__);
    return false;
  }

  SYSTEMTIME systemTime;
  CDateTime dateTime(date);
  dateTime.GetAsSystemTime(systemTime);
  if (CGUIDialogNumeric::ShowAndGetDate(systemTime, heading))
  {
    dateTime = systemTime;
    dateTime.GetAsTm(date);
    return true;
  }
  return false;
}

bool Interface_GUIDialogNumeric::ShowAndGetIPAddress(void* kodiBase, char &ipAddress, unsigned int &maxStringSize, const char *heading)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogNumeric::%s - invalid data", __FUNCTION__);
    return false;
  }

  std::string strIP = &ipAddress;
  bool bRet = CGUIDialogNumeric::ShowAndGetIPAddress(strIP, heading);
  if (bRet)
    strncpy(&ipAddress, strIP.c_str(), maxStringSize);
  maxStringSize = strIP.length();
  return bRet;
}

bool Interface_GUIDialogNumeric::ShowAndGetNumber(void* kodiBase, char &strInput, unsigned int &maxStringSize, const char *heading, unsigned int iAutoCloseTimeoutMs)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogNumeric::%s - invalid data", __FUNCTION__);
    return false;
  }

  std::string str = &strInput;
  bool bRet = CGUIDialogNumeric::ShowAndGetNumber(str, heading, iAutoCloseTimeoutMs);
  if (bRet)
    strncpy(&strInput, str.c_str(), maxStringSize);
  maxStringSize = str.length();
  return bRet;
}

bool Interface_GUIDialogNumeric::ShowAndGetSeconds(void* kodiBase, char &timeString, unsigned int &maxStringSize, const char *heading)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogNumeric::%s - invalid data", __FUNCTION__);
    return false;
  }

  std::string str = &timeString;
  bool bRet = CGUIDialogNumeric::ShowAndGetSeconds(str, heading);
  if (bRet)
    strncpy(&timeString, str.c_str(), maxStringSize);
  maxStringSize = str.length();
  return bRet;
}

} /* namespace ADDON */
} /* extern "C" */
