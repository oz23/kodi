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

  struct Interface_GUIDialogProgress
  {
    static void Init(AddonGlobalInterface* addonInterface);

    static void* New(void* kodiBase);
    static void Delete(void* kodiBase, void* handle);
    static void Open(void* kodiBase, void* handle);
    static void SetHeading(void* kodiBase, void* handle, const char *heading);
    static void SetLine(void* kodiBase, void* handle, unsigned int iLine, const char *line);
    static void SetCanCancel(void* kodiBase, void* handle, bool canCancel);
    static bool IsCanceled(void* kodiBase, void* handle);
    static void SetPercentage(void* kodiBase, void* handle, int percentage);
    static int GetPercentage(void* kodiBase, void* handle);
    static void ShowProgressBar(void* kodiBase, void* handle, bool bOnOff);
    static void SetProgressMax(void* kodiBase, void* handle, int max);
    static void SetProgressAdvance(void* kodiBase, void* handle, int nSteps);
    static bool Abort(void* kodiBase, void* handle);
  };

} /* namespace ADDON */
} /* extern "C" */
