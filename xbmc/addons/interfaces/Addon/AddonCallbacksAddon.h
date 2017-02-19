#pragma once
/*
 *      Copyright (C) 2012-2013 Team XBMC
 *      Copyright (C) 2015-2016 Team KODI
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

#include "addons/interfaces/AddonInterfaces.h"
#include "addons/kodi-addon-dev-kit/include/kodi/libXBMC_addon.h"

struct VFSDirEntry;

#ifdef TARGET_WINDOWS
#ifndef _SSIZE_T_DEFINED
typedef intptr_t ssize_t;
#define _SSIZE_T_DEFINED
#endif // !_SSIZE_T_DEFINED
#endif // TARGET_WINDOWS

namespace ADDON
{
  class CAddon;
};

namespace KodiAPI
{
namespace AddOn
{

class CAddonCallbacksAddon
{
public:
  CAddonCallbacksAddon(ADDON::CAddon* addon);
  virtual ~CAddonCallbacksAddon();

  /*!
   * @return The callback table.
   */
  CB_AddOnLib *GetCallbacks() { return m_callbacks; }

  static void AddOnLog(void *addonData, const ADDON::addon_log_t addonLogLevel, const char *strMessage);
  static bool GetAddonSetting(void *addonData, const char *strSettingName, void *settingValue);
  static char *TranslateSpecialProtocol(const char *strSource);
  static void QueueNotification(void *addonData, const ADDON::queue_msg_t type, const char *strMessage);
  static bool WakeOnLan(const char *mac);
  static char* UnknownToUTF8(const char *strSource);
  static char* GetLocalizedString(const void* addonData, long dwCode);
  static char* GetDVDMenuLanguage(const void* addonData);
  static void FreeString(const void* addonData, char* str);

private:
  ADDON::CAddon* m_addon; /*!< the addon */
  CB_AddOnLib  *m_callbacks; /*!< callback addresses */
};

} /* namespace AddOn */
} /* namespace KodiAPI */
