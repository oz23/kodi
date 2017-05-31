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

#include "DialogExtendedProgressBar.h"
#include "addons/kodi-addon-dev-kit/include/kodi/gui/DialogExtendedProgress.h"

#include "addons/AddonDll.h"
#include "dialogs/GUIDialogExtendedProgressBar.h"
#include "guilib/GUIWindowManager.h"
#include "utils/log.h"

extern "C"
{
namespace ADDON
{

void Interface_GUIDialogExtendedProgress::Init(AddonGlobalInterface* addonInterface)
{
  addonInterface->toKodi->kodi_gui->dialogExtendedProgress.New  = New;
  addonInterface->toKodi->kodi_gui->dialogExtendedProgress.Delete = Delete;
  addonInterface->toKodi->kodi_gui->dialogExtendedProgress.Title = Title;
  addonInterface->toKodi->kodi_gui->dialogExtendedProgress.SetTitle = SetTitle;
  addonInterface->toKodi->kodi_gui->dialogExtendedProgress.Text = Text;
  addonInterface->toKodi->kodi_gui->dialogExtendedProgress.SetText = SetText;
  addonInterface->toKodi->kodi_gui->dialogExtendedProgress.IsFinished = IsFinished;
  addonInterface->toKodi->kodi_gui->dialogExtendedProgress.MarkFinished = MarkFinished;
  addonInterface->toKodi->kodi_gui->dialogExtendedProgress.Percentage = Percentage;
  addonInterface->toKodi->kodi_gui->dialogExtendedProgress.SetPercentage = SetPercentage;
  addonInterface->toKodi->kodi_gui->dialogExtendedProgress.SetProgress = SetProgress;
}

void* Interface_GUIDialogExtendedProgress::New(void* kodiBase, const char *title)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogExtendedProgress::%s - invalid kodi base data", __FUNCTION__);
    return nullptr;
  }

  // setup the progress dialog
  CGUIDialogExtendedProgressBar* dialog = dynamic_cast<CGUIDialogExtendedProgressBar*>(g_windowManager.GetWindow(WINDOW_DIALOG_EXT_PROGRESS));
  if (!title || !dialog)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogExtendedProgress::%s - invalid handler data (title='%p', dialog='%p') on addon '%s'", __FUNCTION__, title, dialog, addon->ID().c_str());
    return nullptr;
  }

  CGUIDialogProgressBarHandle* dlgProgressHandle = dialog->GetHandle(title);
  return dlgProgressHandle;
}

void Interface_GUIDialogExtendedProgress::Delete(void* kodiBase, void* handle)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogExtendedProgress::%s - invalid kodi base data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogExtendedProgress::%s - invalid handler data (handle='%p') on addon '%s'", __FUNCTION__, handle, addon->ID().c_str());
    return;
  }

  CGUIDialogProgressBarHandle* dlgProgressHandle = static_cast<CGUIDialogProgressBarHandle *>(handle);
  dlgProgressHandle->MarkFinished();
}

void Interface_GUIDialogExtendedProgress::Title(void* kodiBase, void* handle, char &title, unsigned int &maxStringSize)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogExtendedProgress::%s - invalid kodi base data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogExtendedProgress::%s - invalid handler data (handle='%p') on addon '%s'", __FUNCTION__, handle, addon->ID().c_str());
    return;
  }

  CGUIDialogProgressBarHandle* dlgProgressHandle = static_cast<CGUIDialogProgressBarHandle *>(handle);
  strncpy(&title, dlgProgressHandle->Title().c_str(), maxStringSize);
  maxStringSize = dlgProgressHandle->Title().length();
}

void Interface_GUIDialogExtendedProgress::SetTitle(void* kodiBase, void* handle, const char *title)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogExtendedProgress::%s - invalid kodi base data", __FUNCTION__);
    return;
  }

  if (!handle || !title)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogExtendedProgress::%s - invalid handler data (handle='%p', title='%p') on addon '%s'", __FUNCTION__, handle, title, addon->ID().c_str());
    return;
  }

  CGUIDialogProgressBarHandle* dlgProgressHandle = static_cast<CGUIDialogProgressBarHandle *>(handle);
  dlgProgressHandle->SetTitle(title);
}

void Interface_GUIDialogExtendedProgress::Text(void* kodiBase, void* handle, char &text, unsigned int &maxStringSize)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogExtendedProgress::%s - invalid kodi base data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogExtendedProgress::%s - invalid add-on data (handle='%p') on addon '%s'", __FUNCTION__, handle, addon->ID().c_str());
    return;
  }

  CGUIDialogProgressBarHandle* dlgProgressHandle = static_cast<CGUIDialogProgressBarHandle *>(handle);
  strncpy(&text, dlgProgressHandle->Text().c_str(), maxStringSize);
  maxStringSize = dlgProgressHandle->Text().length();
}

void Interface_GUIDialogExtendedProgress::SetText(void* kodiBase, void* handle, const char *text)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogExtendedProgress::%s - invalid kodi base data", __FUNCTION__);
    return;
  }

  if (!handle || !text)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogExtendedProgress::%s - invalid handler data (handle='%p', text='%p') on addon '%s'", __FUNCTION__, handle, text, addon->ID().c_str());
    return;
  }

  CGUIDialogProgressBarHandle* dlgProgressHandle = static_cast<CGUIDialogProgressBarHandle *>(handle);
  dlgProgressHandle->SetText(text);
}

bool Interface_GUIDialogExtendedProgress::IsFinished(void* kodiBase, void* handle)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogExtendedProgress::%s - invalid kodi base data", __FUNCTION__);
    return false;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogExtendedProgress::%s - invalid add-on data (handle='%p') on addon '%s'", __FUNCTION__, handle, addon->ID().c_str());
    return false;
  }

  CGUIDialogProgressBarHandle* dlgProgressHandle = static_cast<CGUIDialogProgressBarHandle *>(handle);
  return dlgProgressHandle->IsFinished();
}

void Interface_GUIDialogExtendedProgress::MarkFinished(void* kodiBase, void* handle)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogExtendedProgress::%s - invalid kodi base data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogExtendedProgress::%s - invalid add-on data (handle='%p') on addon '%s'", __FUNCTION__, handle, addon->ID().c_str());
    return;
  }

  CGUIDialogProgressBarHandle* dlgProgressHandle = static_cast<CGUIDialogProgressBarHandle *>(handle);
  dlgProgressHandle->MarkFinished();
}

float Interface_GUIDialogExtendedProgress::Percentage(void* kodiBase, void* handle)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogExtendedProgress::%s - invalid kodi base data", __FUNCTION__);
    return 0.0f;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogExtendedProgress::%s - invalid add-on data (handle='%p') on addon '%s'", __FUNCTION__, handle, addon->ID().c_str());
    return 0.0f;
  }

  CGUIDialogProgressBarHandle* dlgProgressHandle = static_cast<CGUIDialogProgressBarHandle *>(handle);
  return dlgProgressHandle->Percentage();
}

void Interface_GUIDialogExtendedProgress::SetPercentage(void* kodiBase, void* handle, float percentage)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogExtendedProgress::%s - invalid kodi base data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogExtendedProgress::%s - invalid add-on data (handle='%p') on addon '%s'", __FUNCTION__, handle, addon->ID().c_str());
    return;
  }

  CGUIDialogProgressBarHandle* dlgProgressHandle = static_cast<CGUIDialogProgressBarHandle *>(handle);
  dlgProgressHandle->SetPercentage(percentage);
}

void Interface_GUIDialogExtendedProgress::SetProgress(void* kodiBase, void* handle, int currentItem, int itemCount)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogExtendedProgress::%s - invalid kodi base data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogExtendedProgress::%s - invalid add-on data (handle='%p') on addon '%s'", __FUNCTION__, handle, addon->ID().c_str());
    return;
  }

  CGUIDialogProgressBarHandle* dlgProgressHandle = static_cast<CGUIDialogProgressBarHandle *>(handle);
  dlgProgressHandle->SetProgress(currentItem, itemCount);
}

} /* namespace ADDON */
} /* extern "C" */
