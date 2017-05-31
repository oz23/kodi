/*
 *      Copyright (C) 2015-2016 Team KODI
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

#include "DialogProgress.h"
#include "addons/kodi-addon-dev-kit/include/kodi/gui/DialogProgress.h"

#include "addons/AddonDll.h"
#include "dialogs/GUIDialogProgress.h"
#include "guilib/GUIWindowManager.h"
#include "utils/log.h"
#include "utils/Variant.h"

namespace ADDON
{
extern "C"
{

void Interface_GUIDialogProgress::Init(AddonGlobalInterface* addonInterface)
{
  addonInterface->toKodi->kodi_gui->dialogProgress.New = New;
  addonInterface->toKodi->kodi_gui->dialogProgress.Delete = Delete;
  addonInterface->toKodi->kodi_gui->dialogProgress.Open = Open;
  addonInterface->toKodi->kodi_gui->dialogProgress.SetHeading = SetHeading;
  addonInterface->toKodi->kodi_gui->dialogProgress.SetLine = SetLine;
  addonInterface->toKodi->kodi_gui->dialogProgress.SetCanCancel = SetCanCancel;
  addonInterface->toKodi->kodi_gui->dialogProgress.IsCanceled = IsCanceled;
  addonInterface->toKodi->kodi_gui->dialogProgress.SetPercentage = SetPercentage;
  addonInterface->toKodi->kodi_gui->dialogProgress.GetPercentage = GetPercentage;
  addonInterface->toKodi->kodi_gui->dialogProgress.ShowProgressBar = ShowProgressBar;
  addonInterface->toKodi->kodi_gui->dialogProgress.SetProgressMax = SetProgressMax;
  addonInterface->toKodi->kodi_gui->dialogProgress.SetProgressAdvance = SetProgressAdvance;
  addonInterface->toKodi->kodi_gui->dialogProgress.Abort = Abort;
}

void* Interface_GUIDialogProgress::New(void *kodiBase)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogProgress::%s - invalid data", __FUNCTION__);
    return nullptr;
  }

  CGUIDialogProgress *dialog = dynamic_cast<CGUIDialogProgress*>(g_windowManager.GetWindow(WINDOW_DIALOG_PROGRESS));
  if (!dialog)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogProgress::%s - invalid handler data (dialog='%p') on addon '%s'", __FUNCTION__, dialog, addon->ID().c_str());
    return nullptr;
  }

  return dialog;
}

void Interface_GUIDialogProgress::Delete(void *kodiBase, void* handle)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogProgress::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogProgress::%s - invalid add-on data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  static_cast<CGUIDialogProgress*>(handle)->Close();
}

void Interface_GUIDialogProgress::Open(void *kodiBase, void* handle)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogProgress::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogProgress::%s - invalid add-on data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  static_cast<CGUIDialogProgress*>(handle)->Open();
}

void Interface_GUIDialogProgress::SetHeading(void *kodiBase, void* handle, const char *heading)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogProgress::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle || !heading)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogProgress::%s - invalid handler data (handle='%p', heading='%p') on addon '%s'", __FUNCTION__, handle, heading, addon->ID().c_str());
    return;
  }

  static_cast<CGUIDialogProgress*>(handle)->SetHeading(heading);
}

void Interface_GUIDialogProgress::SetLine(void *kodiBase, void* handle, unsigned int iLine, const char *line)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogProgress::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle || !line)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogProgress::%s - invalid handler data (handle='%p', line='%p') on addon '%s'", __FUNCTION__, handle, line, addon->ID().c_str());
    return;
  }

  static_cast<CGUIDialogProgress*>(handle)->SetLine(iLine, line);
}

void Interface_GUIDialogProgress::SetCanCancel(void *kodiBase, void* handle, bool canCancel)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogProgress::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogProgress::%s - invalid handler data (handle='%p') on addon '%s'", __FUNCTION__, handle, addon->ID().c_str());
    return;
  }

  static_cast<CGUIDialogProgress*>(handle)->SetCanCancel(canCancel);
}

bool Interface_GUIDialogProgress::IsCanceled(void *kodiBase, void* handle)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogProgress::%s - invalid data", __FUNCTION__);
    return false;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogProgress::%s - invalid handler data (handle='%p') on addon '%s'", __FUNCTION__, handle, addon->ID().c_str());
    return false;
  }

  return static_cast<CGUIDialogProgress*>(handle)->IsCanceled();
}

void Interface_GUIDialogProgress::SetPercentage(void *kodiBase, void* handle, int percentage)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogProgress::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogProgress::%s - invalid handler data (handle='%p') on addon '%s'", __FUNCTION__, handle, addon->ID().c_str());
    return;
  }

  static_cast<CGUIDialogProgress*>(handle)->SetPercentage(percentage);
}

int Interface_GUIDialogProgress::GetPercentage(void *kodiBase, void* handle)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogProgress::%s - invalid data", __FUNCTION__);
    return 0;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogProgress::%s - invalid handler data (handle='%p') on addon '%s'", __FUNCTION__, handle, addon->ID().c_str());
    return 0;
  }

  return static_cast<CGUIDialogProgress*>(handle)->GetPercentage();
}

void Interface_GUIDialogProgress::ShowProgressBar(void *kodiBase, void* handle, bool onOff)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogProgress::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogProgress::%s - invalid handler data (handle='%p') on addon '%s'", __FUNCTION__, handle, addon->ID().c_str());
    return;
  }

  static_cast<CGUIDialogProgress*>(handle)->ShowProgressBar(onOff);
}

void Interface_GUIDialogProgress::SetProgressMax(void *kodiBase, void* handle, int max)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogProgress::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogProgress::%s - invalid handler data (handle='%p') on addon '%s'", __FUNCTION__, handle, addon->ID().c_str());
    return;
  }

  static_cast<CGUIDialogProgress*>(handle)->SetProgressMax(max);
}

void Interface_GUIDialogProgress::SetProgressAdvance(void *kodiBase, void* handle, int nSteps)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogProgress::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogProgress::%s - invalid handler data (handle='%p') on addon '%s'", __FUNCTION__, handle, addon->ID().c_str());
    return;
  }

  static_cast<CGUIDialogProgress*>(handle)->SetProgressAdvance(nSteps);
}

bool Interface_GUIDialogProgress::Abort(void* kodiBase, void* handle)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogProgress::%s - invalid data", __FUNCTION__);
    return false;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogProgress::%s - invalid handler data (handle='%p') on addon '%s'", __FUNCTION__, handle, addon->ID().c_str());
    return false;
  }

  return static_cast<CGUIDialogProgress*>(handle)->Abort();
}

} /* extern "C" */
} /* namespace ADDON */
