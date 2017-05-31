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

#include "DialogFileBrowser.h"
#include "addons/kodi-addon-dev-kit/include/kodi/gui/DialogFileBrowser.h"

#include "URL.h"
#include "addons/AddonDll.h"
#include "dialogs/GUIDialogFileBrowser.h"
#include "settings/MediaSourceSettings.h"
#include "storage/MediaManager.h"
#include "utils/log.h"
#include "utils/URIUtils.h"

extern "C"
{
namespace ADDON
{

void Interface_GUIDialogFileBrowser::Init(AddonGlobalInterface* addonInterface)
{
  addonInterface->toKodi->kodi_gui->dialogFileBrowser.ShowAndGetDirectory = ShowAndGetDirectory;
  addonInterface->toKodi->kodi_gui->dialogFileBrowser.ShowAndGetFile = ShowAndGetFile;
  addonInterface->toKodi->kodi_gui->dialogFileBrowser.ShowAndGetFileFromDir = ShowAndGetFileFromDir;
  addonInterface->toKodi->kodi_gui->dialogFileBrowser.ShowAndGetFileList = ShowAndGetFileList;
  addonInterface->toKodi->kodi_gui->dialogFileBrowser.ShowAndGetSource = ShowAndGetSource;
  addonInterface->toKodi->kodi_gui->dialogFileBrowser.ShowAndGetImage = ShowAndGetImage;
  addonInterface->toKodi->kodi_gui->dialogFileBrowser.ShowAndGetImageList = ShowAndGetImageList;
  addonInterface->toKodi->kodi_gui->dialogFileBrowser.ClearList = ClearList;
}

bool Interface_GUIDialogFileBrowser::ShowAndGetDirectory(void* kodiBase, const char *shares, const char *heading, char &path, unsigned int &maxStringSize, bool writeOnly)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogFileBrowser::%s - invalid data", __FUNCTION__);
    return false;
  }

  if (!shares || !heading)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogFileBrowser::%s - invalid handler data (shares='%p', heading='%p') on addon '%s'", __FUNCTION__, shares, heading, addon->ID().c_str());
    return false;
  }

  std::string strPath = &path;

  VECSOURCES vecShares;
  GetVECShares(vecShares, shares, strPath);
  bool bRet = CGUIDialogFileBrowser::ShowAndGetDirectory(vecShares, heading, strPath, writeOnly);
  if (bRet)
    strncpy(&path, strPath.c_str(), maxStringSize);
  maxStringSize = strPath.length();
  return bRet;
}

bool Interface_GUIDialogFileBrowser::ShowAndGetFile(void* kodiBase, const char *shares, const char *mask, const char *heading, char &path, unsigned int &maxStringSize, bool useThumbs, bool useFileDirectories)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogFileBrowser::%s - invalid data", __FUNCTION__);
    return false;
  }

  if (!shares || !mask || !heading)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogFileBrowser::%s - invalid handler data (shares='%p', mask='%p', heading='%p') on addon '%s'", __FUNCTION__, shares, mask, heading, addon->ID().c_str());
    return false;
  }

  std::string strPath = &path;

  VECSOURCES vecShares;
  GetVECShares(vecShares, shares, strPath);
  bool bRet = CGUIDialogFileBrowser::ShowAndGetFile(vecShares, mask, heading, strPath, useThumbs, useFileDirectories);
  if (bRet)
    strncpy(&path, strPath.c_str(), maxStringSize);
  maxStringSize = strPath.length();
  return bRet;
}

bool Interface_GUIDialogFileBrowser::ShowAndGetFileFromDir(void* kodiBase, const char *directory, const char *mask, const char *heading, char &path, unsigned int &maxStringSize, bool useThumbs, bool useFileDirectories, bool singleList)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogFileBrowser::%s - invalid data", __FUNCTION__);
    return false;
  }

  if (!directory || !mask || !heading)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogFileBrowser::%s - invalid handler data (directory='%p', mask='%p', heading='%p') on addon '%s'", __FUNCTION__, directory, mask, heading, addon->ID().c_str());
    return false;
  }

  std::string strPath = &path;
  bool bRet = CGUIDialogFileBrowser::ShowAndGetFile(directory, mask, heading, strPath, useThumbs, useFileDirectories, singleList);
  if (bRet)
    strncpy(&path, strPath.c_str(), maxStringSize);
  maxStringSize = strPath.length();
  return bRet;
}

bool Interface_GUIDialogFileBrowser::ShowAndGetFileList(void* kodiBase, const char* shares, const char* mask, const char* heading, char**& path, unsigned int& entries, bool useThumbs, bool useFileDirectories)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogFileBrowser::%s - invalid data", __FUNCTION__);
    return false;
  }

  if (!shares || !mask || !heading)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogFileBrowser::%s - invalid handler data (shares='%p', mask='%p', heading='%p') on addon '%s'", __FUNCTION__, shares, mask, heading, addon->ID().c_str());
    return false;
  }

  VECSOURCES vecShares;
  GetVECShares(vecShares, shares, "");

  std::vector<std::string> pathsInt;
  bool bRet = CGUIDialogFileBrowser::ShowAndGetFileList(vecShares, mask, heading, pathsInt, useThumbs, useFileDirectories);
  if (bRet)
  {
    entries = pathsInt.size();
    path = (char**)malloc(entries*sizeof(char*));
    for (unsigned int i = 0; i < entries; ++i)
      path[i] = strdup(pathsInt[i].c_str());
  }
  else
    entries = 0;
  return bRet;
}

bool Interface_GUIDialogFileBrowser::ShowAndGetSource(void* kodiBase, char &path, unsigned int &maxStringSize, bool allowNetworkShares, const char *additionalShare, const char *strType)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogFileBrowser::%s - invalid data", __FUNCTION__);
    return false;
  }

  if (!strType || !additionalShare)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogFileBrowser::%s - invalid handler data (additionalShare='%p', strType='%p') on addon '%s'", __FUNCTION__, additionalShare, strType, addon->ID().c_str());
    return false;
  }

  std::string strPath = &path;

  VECSOURCES vecShares;
  if (additionalShare)
    GetVECShares(vecShares, additionalShare, strPath);
  bool bRet = CGUIDialogFileBrowser::ShowAndGetSource(strPath, allowNetworkShares, &vecShares, strType);
  if (bRet)
    strncpy(&path, strPath.c_str(), maxStringSize);
  maxStringSize = strPath.length();
  return bRet;
}

bool Interface_GUIDialogFileBrowser::ShowAndGetImage(void* kodiBase, const char *shares, const char *heading, char &path, unsigned int &maxStringSize)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogFileBrowser::%s - invalid data", __FUNCTION__);
    return false;
  }

  if (!shares || !heading)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogFileBrowser::%s - invalid handler data (shares='%p', heading='%p') on addon '%s'", __FUNCTION__, shares, heading, addon->ID().c_str());
    return false;
  }

  std::string strPath = &path;

  VECSOURCES vecShares;
  GetVECShares(vecShares, shares, strPath);
  bool bRet = CGUIDialogFileBrowser::ShowAndGetImage(vecShares, heading, strPath);
  if (bRet)
    strncpy(&path, strPath.c_str(), maxStringSize);
  maxStringSize = strPath.length();
  return bRet;
}

bool Interface_GUIDialogFileBrowser::ShowAndGetImageList(void* kodiBase, const char* shares, const char* heading, char**& path, unsigned int& entries)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogFileBrowser::%s - invalid data", __FUNCTION__);
    return false;
  }

  if (!shares || !heading)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogFileBrowser::%s - invalid handler data (shares='%p', heading='%p') on addon '%s'", __FUNCTION__, shares, heading, addon->ID().c_str());
    return false;
  }

  VECSOURCES vecShares;
  GetVECShares(vecShares, shares, "");

  std::vector<std::string> pathsInt;
  bool bRet = CGUIDialogFileBrowser::ShowAndGetImageList(vecShares, heading, pathsInt);
  if (bRet)
  {
    entries = pathsInt.size();
    path = (char**)malloc(entries*sizeof(char*));
    for (unsigned int i = 0; i < entries; ++i)
      path[i] = strdup(pathsInt[i].c_str());
  }
  else
    entries = 0;
  return bRet;
}

void Interface_GUIDialogFileBrowser::ClearList(void* kodiBase, char**& path, unsigned int entries)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogFileBrowser::%s - invalid data", __FUNCTION__);
    return;
  }

  if (path)
  {
    for (unsigned int i = 0; i < entries; ++i)
    {
      if (path[i])
        free(path[i]);
    }
    free(path);
  }
  else
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogFileBrowser::%s - invalid handler data (path='%p') on addon '%s'", __FUNCTION__, path, addon->ID().c_str());
}

void Interface_GUIDialogFileBrowser::GetVECShares(VECSOURCES &vecShares, std::string strShares, std::string strPath)
{
  std::size_t found;
  found = strShares.find("local");
  if (found!=std::string::npos)
    g_mediaManager.GetLocalDrives(vecShares);
  found = strShares.find("network");
  if (found!=std::string::npos)
    g_mediaManager.GetNetworkLocations(vecShares);
  found = strShares.find("removable");
  if (found!=std::string::npos)
    g_mediaManager.GetRemovableDrives(vecShares);
  found = strShares.find("programs");
  if (found!=std::string::npos)
  {
    VECSOURCES *sources = CMediaSourceSettings::GetInstance().GetSources("programs");
    if (sources != nullptr)
      vecShares.insert(vecShares.end(), sources->begin(), sources->end());
  }
  found = strShares.find("files");
  if (found!=std::string::npos)
  {
    VECSOURCES *sources = CMediaSourceSettings::GetInstance().GetSources("files");
    if (sources != nullptr)
      vecShares.insert(vecShares.end(), sources->begin(), sources->end());
  }
  found = strShares.find("music");
  if (found!=std::string::npos)
  {
    VECSOURCES *sources = CMediaSourceSettings::GetInstance().GetSources("music");
    if (sources != nullptr)
      vecShares.insert(vecShares.end(), sources->begin(), sources->end());
  }
  found = strShares.find("video");
  if (found!=std::string::npos)
  {
    VECSOURCES *sources = CMediaSourceSettings::GetInstance().GetSources("video");
    if (sources != nullptr)
      vecShares.insert(vecShares.end(), sources->begin(), sources->end());
  }
  found = strShares.find("pictures");
  if (found!=std::string::npos)
  {
    VECSOURCES *sources = CMediaSourceSettings::GetInstance().GetSources("pictures");
    if (sources != nullptr)
      vecShares.insert(vecShares.end(), sources->begin(), sources->end());
  }

  if (vecShares.empty())
  {
    CMediaSource share;
    std::string basePath = strPath;
    std::string tempPath;
    while (URIUtils::GetParentPath(basePath, tempPath))
      basePath = tempPath;
    share.strPath = basePath;
    // don't include the user details in the share name
    CURL url(share.strPath);
    share.strName = url.GetWithoutUserDetails();
    vecShares.push_back(share);
  }
}

} /* namespace ADDON */
} /* extern "C" */
