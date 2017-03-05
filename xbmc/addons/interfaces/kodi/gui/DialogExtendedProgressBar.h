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

  struct Interface_GUIDialogExtendedProgress
  {
    static void Init(AddonGlobalInterface* addonInterface);

    static void* New(void* kodiBase, const char *title);
    static void Delete(void* kodiBase, void* handle);
    static void Title(void* kodiBase, void* handle, char &title, unsigned int &iMaxStringSize);
    static void SetTitle(void* kodiBase, void* handle, const char *title);
    static void Text(void* kodiBase, void* handle, char &text, unsigned int &iMaxStringSize);
    static void SetText(void* kodiBase, void* handle, const char *text);
    static bool IsFinished(void* kodiBase, void* handle);
    static void MarkFinished(void* kodiBase, void* handle);
    static float Percentage(void* kodiBase, void* handle);
    static void SetPercentage(void* kodiBase, void* handle, float fPercentage);
    static void SetProgress(void* kodiBase, void* handle, int currentItem, int itemCount);
  };

} /* namespace ADDON */
} /* extern "C" */
