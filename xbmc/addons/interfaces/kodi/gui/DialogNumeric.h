#pragma once
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

#include <time.h>

extern "C"
{

struct AddonGlobalInterface;

namespace ADDON
{

  struct Interface_GUIDialogNumeric
  {
    static void Init(AddonGlobalInterface* addonInterface);

    static bool ShowAndVerifyNewPassword(void* kodiBase,
                                         char &newPassword,
                                         unsigned int &maxStringSize);

    static int  ShowAndVerifyPassword(void* kodiBase, char &password,
                                      unsigned int &maxStringSize,
                                      const char *heading,
                                      int retries);

    static bool ShowAndVerifyInput(void* kodiBase, char &toVerify,
                                   unsigned int &maxStringSize,
                                   const char *heading,
                                   bool verifyInput);

    static bool ShowAndGetTime(void* kodiBase, tm &time, const char* heading);

    static bool ShowAndGetDate(void* kodiBase, tm &date, const char* heading);

    static bool ShowAndGetIPAddress(void* kodiBase, char& ipAddress,
                                    unsigned int &maxStringSize, const char* heading);

    static bool ShowAndGetNumber(void* kodiBase, char& input,
                                 unsigned int &maxStringSize, const char *heading,
                                 unsigned int autoCloseTimeoutMs);

    static bool ShowAndGetSeconds(void* kodiBase, char &timeString,
                                  unsigned int &maxStringSize, const char* heading);
  };

} /* namespace ADDON */
} /* extern "C" */
