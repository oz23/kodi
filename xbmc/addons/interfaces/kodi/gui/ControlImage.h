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

#include <stdint.h>

extern "C"
{

struct AddonGlobalInterface;

namespace ADDON
{

  struct Interface_GUIControlImage
  {
    static void Init(AddonGlobalInterface* addonInterface);

    static void SetVisible(void* kodiBase, void* handle, bool visible);
    static void SetFileName(void* kodiBase, void* handle, const char* strFileName, const bool useCache);
    static void SetColorDiffuse(void* kodiBase, void* handle, uint32_t colorDiffuse);
  };

} /* namespace ADDON */
} /* extern "C" */
