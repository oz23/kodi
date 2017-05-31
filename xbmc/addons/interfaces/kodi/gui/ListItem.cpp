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

#include "addons/interfaces/kodi/gui/ListItem.h"
#include "General.h"

#include "FileItem.h"
#include "addons/AddonDll.h"
#include "addons/kodi-addon-dev-kit/include/kodi/gui/ListItem.h"
#include "guilib/GUIListItem.h"
#include "guilib/GUIWindowManager.h"
#include "music/tags/MusicInfoTag.h"
#include "pictures/PictureInfoTag.h"
#include "video/VideoInfoTag.h"
#include "utils/log.h"
#include "utils/StringUtils.h"
#include "utils/Variant.h"

using namespace kodi; // addon-dev-kit namespace
using namespace kodi::gui; // addon-dev-kit namespace

extern "C"
{
namespace ADDON
{

void Interface_GUIListItem::Init(AddonGlobalInterface* addonInterface)
{
  addonInterface->toKodi->kodi_gui->listItem.Create = Create;
  addonInterface->toKodi->kodi_gui->listItem.Destroy = Destroy;
  addonInterface->toKodi->kodi_gui->listItem.GetLabel = GetLabel;
  addonInterface->toKodi->kodi_gui->listItem.SetLabel = SetLabel;
  addonInterface->toKodi->kodi_gui->listItem.GetLabel2 = GetLabel2;
  addonInterface->toKodi->kodi_gui->listItem.SetLabel2 = SetLabel2;
  addonInterface->toKodi->kodi_gui->listItem.GetIconImage = GetIconImage;
  addonInterface->toKodi->kodi_gui->listItem.SetIconImage = SetIconImage;
  addonInterface->toKodi->kodi_gui->listItem.GetOverlayImage = GetOverlayImage;
  addonInterface->toKodi->kodi_gui->listItem.SetOverlayImage = SetOverlayImage;
  addonInterface->toKodi->kodi_gui->listItem.SetThumbnailImage = SetThumbnailImage;
  addonInterface->toKodi->kodi_gui->listItem.SetArt = SetArt;
  addonInterface->toKodi->kodi_gui->listItem.GetArt = GetArt;
  addonInterface->toKodi->kodi_gui->listItem.SetArtFallback = SetArtFallback;
  addonInterface->toKodi->kodi_gui->listItem.HasArt = HasArt;
  addonInterface->toKodi->kodi_gui->listItem.SetUniqueIDs = SetUniqueIDs;
  addonInterface->toKodi->kodi_gui->listItem.GetUniqueID = GetUniqueID;
  addonInterface->toKodi->kodi_gui->listItem.SetRating = SetRating;
  addonInterface->toKodi->kodi_gui->listItem.GetRating = GetRating;
  addonInterface->toKodi->kodi_gui->listItem.AddAvailableThumb = AddAvailableThumb;
  addonInterface->toKodi->kodi_gui->listItem.AddSeason = AddSeason;
  addonInterface->toKodi->kodi_gui->listItem.GetVotes = GetVotes;
  addonInterface->toKodi->kodi_gui->listItem.Select = Select;
  addonInterface->toKodi->kodi_gui->listItem.IsSelected = IsSelected;
  addonInterface->toKodi->kodi_gui->listItem.HasIcon = HasIcon;
  addonInterface->toKodi->kodi_gui->listItem.HasOverlay = HasOverlay;
  addonInterface->toKodi->kodi_gui->listItem.IsFileItem = IsFileItem;
  addonInterface->toKodi->kodi_gui->listItem.IsFolder = IsFolder;
  addonInterface->toKodi->kodi_gui->listItem.SetInfo = SetInfo;
  addonInterface->toKodi->kodi_gui->listItem.SetProperty = SetProperty;
  addonInterface->toKodi->kodi_gui->listItem.GetProperty = GetProperty;
  addonInterface->toKodi->kodi_gui->listItem.ClearProperty = ClearProperty;
  addonInterface->toKodi->kodi_gui->listItem.ClearProperties = ClearProperties;
  addonInterface->toKodi->kodi_gui->listItem.HasProperties = HasProperties;
  addonInterface->toKodi->kodi_gui->listItem.HasProperty = HasProperty;
  addonInterface->toKodi->kodi_gui->listItem.SetPath = SetPath;
  addonInterface->toKodi->kodi_gui->listItem.GetPath = GetPath;
  addonInterface->toKodi->kodi_gui->listItem.GetDuration = GetDuration;
  addonInterface->toKodi->kodi_gui->listItem.SetSubtitles = SetSubtitles;
  addonInterface->toKodi->kodi_gui->listItem.SetMimeType = SetMimeType;
  addonInterface->toKodi->kodi_gui->listItem.SetContentLookup = SetContentLookup;
  addonInterface->toKodi->kodi_gui->listItem.AddContextMenuItems = AddContextMenuItems;
  addonInterface->toKodi->kodi_gui->listItem.AddStreamInfo = AddStreamInfo;
}

void* Interface_GUIListItem::Create(void* kodiBase, const char *label, const char *label2, const char *iconImage, const char *thumbnailImage, const char *path)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid data", __FUNCTION__);
    return nullptr;
  }

  // create CFileItem
  CFileItem *pItem = new CFileItem();
  if (!pItem)
    return nullptr;

  if (label)
    pItem->SetLabel(label);
  if (label2)
    pItem->SetLabel2(label2);
  if (iconImage)
    pItem->SetIconImage(iconImage);
  if (thumbnailImage)
    pItem->SetArt("thumb", thumbnailImage);
  if (path)
    pItem->SetPath(path);

  return pItem;
}

void Interface_GUIListItem::Destroy(void* kodiBase, void* handle)
{
  // @note: Delete of CFileItem brings crash, need to check about the in related
  // window and no memleak present to confirm.
  // In old version was the same way, only the Destroy passed here to allow
  // changes and fixes without API level changes.
}

void Interface_GUIListItem::GetLabel(void* kodiBase, void* handle, char &label, unsigned int &iMaxStringSize)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid handler data (handle='%p') on addon '%s'", __FUNCTION__, handle, addon->ID().c_str());
    return;
  }

  Interface_GUIGeneral::lock();

  strncpy(&label, static_cast<CFileItem*>(handle)->GetLabel().c_str(), iMaxStringSize);
  iMaxStringSize = static_cast<CFileItem*>(handle)->GetLabel().length();

  Interface_GUIGeneral::unlock();
}

void Interface_GUIListItem::SetLabel(void* kodiBase, void* handle, const char *label)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle || !label)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid handler data (handle='%p', label='%p') on addon '%s'", __FUNCTION__, handle, label, addon->ID().c_str());
    return;
  }

  Interface_GUIGeneral::lock();

  static_cast<CFileItem*>(handle)->SetLabel(label);

  Interface_GUIGeneral::unlock();
}

void Interface_GUIListItem::GetLabel2(void* kodiBase, void* handle, char &label, unsigned int &iMaxStringSize)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid handler data (handle='%p') on addon '%s'", __FUNCTION__, handle, addon->ID().c_str());
    return;
  }

  Interface_GUIGeneral::lock();

  strncpy(&label, static_cast<CFileItem*>(handle)->GetLabel2().c_str(), iMaxStringSize);
  iMaxStringSize = static_cast<CFileItem*>(handle)->GetLabel2().length();

  Interface_GUIGeneral::unlock();
}

void Interface_GUIListItem::SetLabel2(void* kodiBase, void* handle, const char *label)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle || !label)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid handler data (handle='%p', label='%p') on addon '%s'", __FUNCTION__, handle, label, addon->ID().c_str());
    return;
  }

  Interface_GUIGeneral::lock();

  static_cast<CFileItem*>(handle)->SetLabel2(label);

  Interface_GUIGeneral::unlock();
}

void Interface_GUIListItem::GetIconImage(void* kodiBase, void* handle, char &image, unsigned int &iMaxStringSize)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid handler data (handle='%p') on addon '%s'", __FUNCTION__, handle, addon->ID().c_str());
    return;
  }

  Interface_GUIGeneral::lock();
  strncpy(&image, static_cast<CFileItem*>(handle)->GetIconImage().c_str(), iMaxStringSize);
  iMaxStringSize = static_cast<CFileItem*>(handle)->GetIconImage().length();
  Interface_GUIGeneral::unlock();
}

void Interface_GUIListItem::SetIconImage(void* kodiBase, void* handle, const char *image)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle || !image)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid handler data (handle='%p', image='%p') on addon '%s'", __FUNCTION__, handle, image, addon->ID().c_str());
    return;
  }

  Interface_GUIGeneral::lock();
  static_cast<CFileItem*>(handle)->SetIconImage(image);
  Interface_GUIGeneral::unlock();
}

void Interface_GUIListItem::GetOverlayImage(void* kodiBase, void* handle, char &image, unsigned int &iMaxStringSize)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid handler data (handle='%p') on addon '%s'", __FUNCTION__, handle, addon->ID().c_str());
    return;
  }

  Interface_GUIGeneral::lock();
  strncpy(&image, static_cast<CFileItem*>(handle)->GetOverlayImage().c_str(), iMaxStringSize);
  iMaxStringSize = static_cast<CFileItem*>(handle)->GetOverlayImage().length();
  Interface_GUIGeneral::unlock();
}

void Interface_GUIListItem::SetOverlayImage(void* kodiBase, void* handle, unsigned int image, bool bOnOff /* = false*/)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid handler data (handle='%p') on addon '%s'", __FUNCTION__, handle, addon->ID().c_str());
    return;
  }

  Interface_GUIGeneral::lock();
  static_cast<CFileItem*>(handle)->SetOverlayImage((CGUIListItem::GUIIconOverlay)image, bOnOff);
  Interface_GUIGeneral::unlock();
}

void Interface_GUIListItem::SetThumbnailImage(void* kodiBase, void* handle, const char *image)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle || !image)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid handler data (handle='%p', image='%p') on addon '%s'", __FUNCTION__, handle, image, addon->ID().c_str());
    return;
  }

  Interface_GUIGeneral::lock();
  static_cast<CFileItem*>(handle)->SetArt("thumb", image);
  Interface_GUIGeneral::unlock();
}

void Interface_GUIListItem::SetArt(void* kodiBase, void* handle, const char *type, const char *url)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle || !type || !url)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid handler data (handle='%p', type='%p', url='%p') on addon '%s'", __FUNCTION__, handle, type, url, addon->ID().c_str());
    return;
  }

  Interface_GUIGeneral::lock();
  static_cast<CFileItem*>(handle)->SetArt(type, url);
  Interface_GUIGeneral::unlock();
}

char* Interface_GUIListItem::GetArt(void* kodiBase, void* handle, const char *type)
{
  char* buffer = nullptr;

  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid data", __FUNCTION__);
    return buffer;
  }

  if (!handle || !type)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid handler data (handle='%p', type='%p') on addon '%s'", __FUNCTION__, handle, type, addon->ID().c_str());
    return buffer;
  }

  Interface_GUIGeneral::lock();
  buffer = strdup(static_cast<CFileItem*>(handle)->GetArt(type).c_str());
  Interface_GUIGeneral::unlock();
  return buffer;
}

void Interface_GUIListItem::SetArtFallback(void* kodiBase, void* handle, const char *from, const char *to)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle || !from || !to)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid handler data (handle='%p', from='%p', to='%p') on addon '%s'", __FUNCTION__, handle, from, to, addon->ID().c_str());
    return;
  }

  Interface_GUIGeneral::lock();
  static_cast<CFileItem*>(handle)->SetArtFallback(from, to);
  Interface_GUIGeneral::unlock();
}

bool Interface_GUIListItem::HasArt(void* kodiBase, void* handle, const char *type)
{
  bool ret = false;

  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid data", __FUNCTION__);
    return ret;
  }

  if (!handle || !type)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid handler data (handle='%p', type='%p') on addon '%s'", __FUNCTION__, handle, type, addon->ID().c_str());
    return ret;
  }

  Interface_GUIGeneral::lock();
  ret = static_cast<CFileItem*>(handle)->HasArt(type);
  Interface_GUIGeneral::unlock();
  return ret;
}

void Interface_GUIListItem::SetUniqueIDs(void* kodiBase, void* handle, const char** ids[2], unsigned int entries, const char* defaultrating)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid data", __FUNCTION__);
    return;
  }

  for (unsigned int i = 0; i < entries; ++i)
  {
    if (ids[i][0] == nullptr || ids[i][1] == nullptr)
    {
      CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem - %s: %s - Must pass in a list of tuples of pairs of strings. One entry in the list is empty.", __FUNCTION__, addon->Name().c_str());
      return;
    }

    std::string type = ids[i][0];
    std::string uniqueid = ids[i][1];

    Interface_GUIGeneral::lock();
    CVideoInfoTag& vtag = *static_cast<CFileItem*>(handle)->GetVideoInfoTag();
    vtag.SetUniqueID(uniqueid, type, type == defaultrating);
    Interface_GUIGeneral::unlock();
  }
}

char* Interface_GUIListItem::GetUniqueID(void* kodiBase, void* handle, const char* key)
{
  char* buffer = nullptr;
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid data", __FUNCTION__);
    return buffer;
  }

  if (!handle || !key)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid handler data (handle='%p', key='%p') on addon '%s'", __FUNCTION__, handle, key, addon->ID().c_str());
    return buffer;
  }

  Interface_GUIGeneral::lock();
  buffer = strdup(static_cast<CFileItem*>(handle)->GetVideoInfoTag()->GetUniqueID(key).c_str());
  Interface_GUIGeneral::unlock();
  return buffer;
}

void Interface_GUIListItem::SetRating(void* kodiBase, void* handle, const char* type, float rating, int votes, bool defaultt)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle || !type)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid handler data (handle='%p', type='%p') on addon '%s'", __FUNCTION__, handle, type, addon->ID().c_str());
    return;
  }
  
  Interface_GUIGeneral::lock();
  static_cast<CFileItem*>(handle)->GetVideoInfoTag()->SetRating(rating, votes, type, defaultt);
  Interface_GUIGeneral::unlock();
}

void Interface_GUIListItem::AddSeason(void* kodiBase, void* handle, int number, const char* name)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle || !name)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid handler data (handle='%p', name='%p') on addon '%s'", __FUNCTION__, handle, name, addon->ID().c_str());
    return;
  }

  Interface_GUIGeneral::lock();
  static_cast<CFileItem*>(handle)->GetVideoInfoTag()->m_namedSeasons[number] = name;
  Interface_GUIGeneral::unlock();
}

float Interface_GUIListItem::GetRating(void* kodiBase, void* handle, const char* key)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid data", __FUNCTION__);
    return 0.0f;
  }

  if (!handle || !key)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid handler data (handle='%p', key='%p') on addon '%s'", __FUNCTION__, handle, key, addon->ID().c_str());
    return 0.0f;
  }

  Interface_GUIGeneral::lock();
  float rating = static_cast<CFileItem*>(handle)->GetVideoInfoTag()->GetRating(key).rating;
  Interface_GUIGeneral::unlock();
  return rating;
}

int Interface_GUIListItem::GetVotes(void* kodiBase, void* handle, const char* key)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid data", __FUNCTION__);
    return 0;
  }

  if (!handle || !key)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid handler data (handle='%p', key='%p') on addon '%s'", __FUNCTION__, handle, key, addon->ID().c_str());
    return 0;
  }

  Interface_GUIGeneral::lock();
  int votes = static_cast<CFileItem*>(handle)->GetVideoInfoTag()->GetRating(key).votes;
  Interface_GUIGeneral::unlock();
  return votes;
}
    
void Interface_GUIListItem::Select(void* kodiBase, void* handle, bool bOnOff)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid handler data (handle='%p') on addon '%s'", __FUNCTION__, handle, addon->ID().c_str());
    return;
  }

  Interface_GUIGeneral::lock();
  static_cast<CFileItem*>(handle)->Select(bOnOff);
  Interface_GUIGeneral::unlock();
}

bool Interface_GUIListItem::IsSelected(void* kodiBase, void* handle)
{
  bool ret = false;

  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid data", __FUNCTION__);
    return ret;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid handler data (handle='%p') on addon '%s'", __FUNCTION__, handle, addon->ID().c_str());
    return ret;
  }

  Interface_GUIGeneral::lock();
  ret = static_cast<CFileItem*>(handle)->IsSelected();
  Interface_GUIGeneral::unlock();

  return ret;
}

void Interface_GUIListItem::SetInfo(void* kodiBase, void* handle, const char* type, const char** infoLabels[2], unsigned int entries)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid handler data (handle='%p') on addon '%s'", __FUNCTION__, handle, addon->ID().c_str());
    return;
  }

  /// @todo
}

bool Interface_GUIListItem::HasIcon(void* kodiBase, void* handle)
{
  bool ret = false;

  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid data", __FUNCTION__);
    return ret;
  }

  Interface_GUIGeneral::lock();
  ret = static_cast<CFileItem*>(handle)->HasIcon();
  Interface_GUIGeneral::unlock();

  return ret;
}

bool Interface_GUIListItem::HasOverlay(void* kodiBase, void* handle)
{
  bool ret = false;

  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid data", __FUNCTION__);
    return ret;
  }

  Interface_GUIGeneral::lock();
  ret = static_cast<CFileItem*>(handle)->HasOverlay();
  Interface_GUIGeneral::unlock();

  return ret;
}

bool Interface_GUIListItem::IsFileItem(void* kodiBase, void* handle)
{
  bool ret = false;

  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid data", __FUNCTION__);
    return ret;
  }

  Interface_GUIGeneral::lock();
  ret = static_cast<CFileItem*>(handle)->IsFileItem();
  Interface_GUIGeneral::unlock();
  return ret;
}

bool Interface_GUIListItem::IsFolder(void* kodiBase, void* handle)
{
  bool ret = false;

  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid data", __FUNCTION__);
    return ret;
  }

  Interface_GUIGeneral::lock();
  ret = static_cast<CFileItem*>(handle)->m_bIsFolder;
  Interface_GUIGeneral::unlock();
  return ret;
}

void Interface_GUIListItem::SetProperty(void* kodiBase, void* handle, const char *key, const char *value)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle || !key || !value)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid handler data (handle='%p', key='%p', value='%p') on addon '%s'", __FUNCTION__, handle, key, value, addon->ID().c_str());
    return;
  }

  Interface_GUIGeneral::lock();
  static_cast<CFileItem*>(handle)->SetProperty(key, value);
  Interface_GUIGeneral::unlock();
}

void Interface_GUIListItem::GetProperty(void* kodiBase, void* handle, const char *key, char &property, unsigned int &iMaxStringSize)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle || !key)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid handler data (handle='%p', key='%p') on addon '%s'", __FUNCTION__, handle, key, addon->ID().c_str());
    return;
  }

  std::string lowerKey = key;
  StringUtils::ToLower(lowerKey);

  Interface_GUIGeneral::lock();
  std::string value = static_cast<CFileItem*>(handle)->GetProperty(lowerKey).asString();
  Interface_GUIGeneral::unlock();

  strncpy(&property, value.c_str(), iMaxStringSize);
  iMaxStringSize = value.length();
}

void Interface_GUIListItem::ClearProperty(void* kodiBase, void* handle, const char *key)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle || !key)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid handler data (handle='%p', key='%p') on addon '%s'", __FUNCTION__, handle, key, addon->ID().c_str());
    return;
  }

  Interface_GUIGeneral::lock();
  static_cast<CFileItem*>(handle)->ClearProperty(key);
  Interface_GUIGeneral::unlock();
}

void Interface_GUIListItem::ClearProperties(void* kodiBase, void* handle)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid handler data (handle='%p') on addon '%s'", __FUNCTION__, handle, addon->ID().c_str());
    return;
  }

  Interface_GUIGeneral::lock();
  static_cast<CFileItem*>(handle)->ClearProperties();
  Interface_GUIGeneral::unlock();
}

bool Interface_GUIListItem::HasProperties(void* kodiBase, void* handle)
{
  bool ret = false;

  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid data", __FUNCTION__);
    return ret;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid handler data (handle='%p') on addon '%s'", __FUNCTION__, handle, addon->ID().c_str());
    return ret;
  }

  Interface_GUIGeneral::lock();
  ret = static_cast<CFileItem*>(handle)->HasProperties();
  Interface_GUIGeneral::unlock();
  return ret;
}

bool Interface_GUIListItem::HasProperty(void* kodiBase, void* handle, const char *key)
{
  bool ret = false;

  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid data", __FUNCTION__);
    return ret;
  }

  if (!handle || !key)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid handler data (handle='%p', key='%p') on addon '%s'", __FUNCTION__, handle, key, addon->ID().c_str());
    return ret;
  }

  Interface_GUIGeneral::lock();
  ret = static_cast<CFileItem*>(handle)->HasProperty(key);
  Interface_GUIGeneral::unlock();
  return ret;
}

void Interface_GUIListItem::SetPath(void* kodiBase, void* handle, const char *path)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid data", __FUNCTION__);
    return;
  }

  Interface_GUIGeneral::lock();
  static_cast<CFileItem*>(handle)->SetPath(path);
  Interface_GUIGeneral::unlock();
}

char* Interface_GUIListItem::GetPath(void* kodiBase, void* handle)
{
  char* buffer = nullptr;

  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid data", __FUNCTION__);
    return buffer;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid handler data (handle='%p') on addon '%s'", __FUNCTION__, handle, addon->ID().c_str());
    return buffer;
  }

  Interface_GUIGeneral::lock();
  buffer = strdup(static_cast<CFileItem*>(handle)->GetPath().c_str());
  Interface_GUIGeneral::unlock();
  return buffer;
}

int Interface_GUIListItem::GetDuration(void* kodiBase, void* handle)
{
  int duration = 0;

  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid data", __FUNCTION__);
    return duration;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid handler data (handle='%p') on addon '%s'", __FUNCTION__, handle, addon->ID().c_str());
    return duration;
  }

  Interface_GUIGeneral::lock();
  if (static_cast<CFileItem*>(handle)->LoadMusicTag())
    duration = static_cast<CFileItem*>(handle)->GetMusicInfoTag()->GetDuration();
  else if (static_cast<CFileItem*>(handle)->HasVideoInfoTag())
    duration = static_cast<CFileItem*>(handle)->GetVideoInfoTag()->GetDuration();
  Interface_GUIGeneral::unlock();
  return duration;
}

void Interface_GUIListItem::SetSubtitles(void* kodiBase, void* handle, const char** streams, unsigned int entries)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid data", __FUNCTION__);
    return;
  }

  Interface_GUIGeneral::lock();
  for (unsigned int i = 0; i < entries; ++i)
  {
    std::string property = StringUtils::Format("subtitle:%u", i+1);
    static_cast<CFileItem*>(handle)->SetProperty(property, streams[i]);
  }
  Interface_GUIGeneral::unlock();
}

void Interface_GUIListItem::SetMimeType(void* kodiBase, void* handle, const char* mimetype)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid data", __FUNCTION__);
    return;
  }

  Interface_GUIGeneral::lock();
  static_cast<CFileItem*>(handle)->SetMimeType(mimetype);
  Interface_GUIGeneral::unlock();
}

void Interface_GUIListItem::SetContentLookup(void* kodiBase, void* handle, bool enable)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid data", __FUNCTION__);
    return;
  }

  Interface_GUIGeneral::lock();
  static_cast<CFileItem*>(handle)->SetContentLookup(enable);
  Interface_GUIGeneral::unlock();
}

void Interface_GUIListItem::AddContextMenuItems(void* kodiBase, void* handle, const char** menus[2], unsigned int entries, bool replaceItems)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid data", __FUNCTION__);
    return;
  }

  if (handle == nullptr)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem - %s: %s - No handle", __FUNCTION__, addon->Name().c_str());
    return;
  }

  if (menus == nullptr)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem - %s: %s - Must pass a list of strings. List self is empty.", __FUNCTION__, addon->Name().c_str());
    return;
  }

  for (unsigned int i = 0; i < entries; ++i)
  {
    if (menus[i][0] == nullptr || menus[i][1] == nullptr)
    {
      CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem - %s: %s - Must pass in a list of tuples of pairs of strings. One entry in the list is empty.", __FUNCTION__, addon->Name().c_str());
      return;
    }

    std::string uText = menus[i][0];
    std::string uAction = menus[i][1];

    Interface_GUIGeneral::lock();
    std::string property = StringUtils::Format("contextmenulabel(%i)", i);
    static_cast<CFileItem*>(handle)->SetProperty(property, uText);

    property = StringUtils::Format("contextmenuaction(%i)", i);
    static_cast<CFileItem*>(handle)->SetProperty(property, uAction);
    Interface_GUIGeneral::unlock();
  }

  // set our replaceItems status
  if (replaceItems)
    static_cast<CFileItem*>(handle)->SetProperty("pluginreplacecontextitems", replaceItems);
  // end addContextMenuItems
}

void Interface_GUIListItem::AddAvailableThumb(void* kodiBase, void* handle, const char* url, const char* aspect, const char* referrer, const char* cache, bool post, bool isgze, int season)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle || !url || !aspect || !referrer || !cache)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid handler data (handle='%p', url='%p', aspect='%p', referrer='%p', cache='%p') on addon '%s'", __FUNCTION__, handle, url, aspect, referrer, cache, addon->ID().c_str());
    return;
  }

  Interface_GUIGeneral::lock();
  static_cast<CFileItem*>(handle)->GetVideoInfoTag()->m_strPictureURL.AddElement(url, aspect, referrer, cache, post, isgze, season);
  Interface_GUIGeneral::unlock();
}

void Interface_GUIListItem::AddStreamInfo(void* kodiBase, void* handle, const char* cType, const char** dictionary[2], unsigned int entries)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIListItem::%s - invalid data", __FUNCTION__);
    return;
  }

  Interface_GUIGeneral::lock();

  if (strcmpi(cType, "video") == 0)
  {
    CStreamDetailVideo* video = new CStreamDetailVideo;
    for (unsigned int i = 0; i < entries; ++i)
    {
      const std::string key = dictionary[i][0];
      const std::string value = dictionary[i][1];

      if (key == "codec")
        video->m_strCodec = value;
      else if (key == "aspect")
        video->m_fAspect = (float)atof(value.c_str());
      else if (key == "width")
        video->m_iWidth = strtol(value.c_str(), NULL, 10);
      else if (key == "height")
        video->m_iHeight = strtol(value.c_str(), NULL, 10);
      else if (key == "duration")
        video->m_iDuration = strtol(value.c_str(), NULL, 10);
      else if (key == "stereomode")
        video->m_strStereoMode = value;
    }
    static_cast<CFileItem*>(handle)->GetVideoInfoTag()->m_streamDetails.AddStream(video);
  }
  else if (strcmpi(cType, "audio") == 0)
  {
    CStreamDetailAudio* audio = new CStreamDetailAudio;
    for (unsigned int i = 0; i < entries; ++i)
    {
      const std::string key = dictionary[i][0];
      const std::string value = dictionary[i][1];

      if (key == "codec")
        audio->m_strCodec = value;
      else if (key == "language")
        audio->m_strLanguage = value;
      else if (key == "channels")
        audio->m_iChannels = strtol(value.c_str(), NULL, 10);
    }
    static_cast<CFileItem*>(handle)->GetVideoInfoTag()->m_streamDetails.AddStream(audio);
  }
  else if (strcmpi(cType, "subtitle") == 0)
  {
    CStreamDetailSubtitle* subtitle = new CStreamDetailSubtitle;
    for (unsigned int i = 0; i < entries; ++i)
    {
      const std::string key = dictionary[i][0];
      const std::string value = dictionary[i][1];

      if (key == "language")
        subtitle->m_strLanguage = value;
    }
    static_cast<CFileItem*>(handle)->GetVideoInfoTag()->m_streamDetails.AddStream(subtitle);
  }

  Interface_GUIGeneral::unlock();
}

} /* namespace ADDON */
} /* extern "C" */
