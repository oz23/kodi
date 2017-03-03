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

  struct Interface_GUIListItem
  {
    static void Init(AddonGlobalInterface* addonInterface);

    static void* Create(void* kodiBase, const char *label, const char *label2, const char *iconImage, const char *thumbnailImage, const char *path);
    static void Destroy(void* kodiBase, void* handle);
    static void GetLabel(void* kodiBase, void* handle, char &label, unsigned int &iMaxStringSize);
    static void SetLabel(void* kodiBase, void* handle, const char *label);
    static void GetLabel2(void* kodiBase, void* handle, char &label, unsigned int &iMaxStringSize);
    static void SetLabel2(void* kodiBase, void* handle, const char *label);
    static void GetIconImage(void* kodiBase, void* handle, char &image, unsigned int &iMaxStringSize);
    static void SetIconImage(void* kodiBase, void* handle, const char *image);
    static void GetOverlayImage(void* kodiBase, void* handle, char &image, unsigned int &iMaxStringSize);
    static void SetOverlayImage(void* kodiBase, void* handle, unsigned int image, bool bOnOff /* = false*/);
    static void SetThumbnailImage(void* kodiBase, void* handle, const char *image);
    static void SetArt(void* kodiBase, void* handle, const char *type, const char *url);
    static char* GetArt(void* kodiBase, void* handle, const char *type);
    static void SetArtFallback(void* kodiBase, void* handle, const char *from, const char *to);
    static bool HasArt(void* kodiBase, void* handle, const char *type);
    static void SetUniqueIDs(void* kodiBase, void* handle, const char** ids[2], unsigned int entries, const char* defaultrating);
    static char* GetUniqueID(void* kodiBase, void* handle, const char* key);
    static void SetRating(void* kodiBase, void* handle, const char* type, float rating, int votes, bool defaultt);
    static float GetRating(void* kodiBase, void* handle, const char* key);
    static void AddAvailableThumb(void* kodiBase, void* handle, const char* url, const char* aspect, const char* referrer, const char* cache, bool post, bool isgze, int season);
    static void AddSeason(void* kodiBase, void* handle, int number, const char* name);
    static int GetVotes(void* kodiBase, void* handle, const char* key);
    static void Select(void* kodiBase, void* handle, bool bOnOff);
    static bool IsSelected(void* kodiBase, void* handle);
    static void SetInfo(void* kodiBase, void* handle, const char* type, const char** infoLabels[2], unsigned int entries);
    static bool HasIcon(void* kodiBase, void* handle);
    static bool HasOverlay(void* kodiBase, void* handle);
    static bool IsFileItem(void* kodiBase, void* handle);
    static bool IsFolder(void* kodiBase, void* handle);
    static void SetProperty(void* kodiBase, void* handle, const char *key, const char *value);
    static void GetProperty(void* kodiBase, void* handle, const char *key, char &property, unsigned int &iMaxStringSize);
    static void ClearProperty(void* kodiBase, void* handle, const char *key);
    static void ClearProperties(void* kodiBase, void* handle);
    static bool HasProperties(void* kodiBase, void* handle);
    static bool HasProperty(void* kodiBase, void* handle, const char *key);
    static void SetPath(void* kodiBase, void* handle, const char *path);
    static char* GetPath(void* kodiBase, void* handle);
    static int GetDuration(void* kodiBase, void* handle);
    static void SetSubtitles(void* kodiBase, void* handle, const char** streams, unsigned int entries);
    static void SetMimeType(void* kodiBase, void* handle, const char* mimetype);
    static void SetContentLookup(void* kodiBase, void* handle, bool enable);
    static void AddContextMenuItems(void* kodiBase, void* handle, const char** menus[2], unsigned int entries, bool replaceItems);
    static void AddStreamInfo(void* kodiBase, void* handle, const char* cType, const char** dictionary[2], unsigned int entries);
  };

} /* namespace ADDON */
} /* extern "C" */
