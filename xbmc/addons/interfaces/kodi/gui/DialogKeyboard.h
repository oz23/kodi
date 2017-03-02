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

extern "C"
{

struct AddonGlobalInterface;

namespace ADDON
{

  struct Interface_GUIDialogKeyboard
  {
    static void Init(AddonGlobalInterface* addonInterface);

    static bool ShowAndGetInput(void* kodiBase, char &aTextString,
                                unsigned int &maxStringSize,
                                bool allowEmptyResult,
                                unsigned int  autoCloseMs);

    static bool ShowAndGetInputWithHead(void* kodiBase, char &aTextString,
                                        unsigned int &maxStringSize,
                                        const char *heading,
                                        bool allowEmptyResult,
                                        bool hiddenInput,
                                        unsigned int autoCloseMs);

    static bool ShowAndGetNewPassword(void* kodiBase, char &strNewPassword,
                                      unsigned int &maxStringSize,
                                      unsigned int autoCloseMs);

    static bool ShowAndGetNewPasswordWithHead(void* kodiBase, 
                                              char &newPassword,
                                              unsigned int &maxStringSize,
                                              const char *strHeading,
                                              bool allowEmptyResult,
                                              unsigned int autoCloseMs);

    static bool ShowAndVerifyNewPassword(void* kodiBase,
                                         char &strNewPassword,
                                         unsigned int &maxStringSize,
                                         unsigned int autoCloseMs);

    static bool ShowAndVerifyNewPasswordWithHead(void* kodiBase, 
                                                 char &strNewPassword,
                                                 unsigned int &maxStringSize,
                                                 const char *strHeading,
                                                 bool allowEmpty,
                                                 unsigned int autoCloseMs);

    static int  ShowAndVerifyPassword(void* kodiBase, 
                                      char &strPassword,
                                      unsigned int &maxStringSize,
                                      const char *strHeading,
                                      int retries, unsigned int autoCloseMs);

    static bool ShowAndGetFilter(void* kodiBase, char &aTextString,
                                 unsigned int &maxStringSize,
                                 bool searching, unsigned int  autoCloseMs);

    static bool SendTextToActiveKeyboard(void* kodiBase, 
                                         const char *aTextString,
                                         bool closeKeyboard);

    static bool isKeyboardActivated(void* kodiBase);
  };

} /* namespace ADDON */
} /* extern "C" */
