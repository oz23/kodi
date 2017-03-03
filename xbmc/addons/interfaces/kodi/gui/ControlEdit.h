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

  struct Interface_GUIControlEdit
  {
    static void Init(AddonGlobalInterface* addonInterface);

    static void SetVisible(void* kodiBase, void* handle, bool visible);
    static void SetEnabled(void* kodiBase, void* handle, bool enabled);

    static void SetInputType(void* kodiBase, void* handle, int type, const char* heading);

    static void SetLabel(void* kodiBase, void* handle, const char* label);
    static void GetLabel(void* kodiBase, void* handle, char& label, unsigned int& maxStringSize);

    static void SetText(void* kodiBase, void* handle, const char* text);
    static void GetText(void* kodiBase, void* handle, char& text, unsigned int& maxStringSize);

    static unsigned int GetCursorPosition(void* kodiBase, void* handle);
    static void SetCursorPosition(void* kodiBase, void* handle, unsigned int position);
  };

} /* namespace ADDON */
} /* extern "C" */
