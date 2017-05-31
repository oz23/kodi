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

#include "Window.h"
#include "General.h"
#include "ControlRendering.h"
#include "addons/kodi-addon-dev-kit/include/kodi/gui/Window.h"

#include "Application.h"
#include "FileItem.h"
#include "addons/AddonDll.h"
#include "addons/Skin.h"
#include "dialogs/GUIDialogProgress.h"
#include "filesystem/File.h"
#include "guilib/GUIWindowManager.h"
#include "guilib/TextureManager.h"
#include "input/Key.h"
#include "messaging/ApplicationMessenger.h"
#include "messaging/helpers/DialogHelper.h"
#include "utils/log.h"
#include "utils/StringUtils.h"
#include "utils/URIUtils.h"
#include "utils/Variant.h"

#define CONTROL_BTNVIEWASICONS  2
#define CONTROL_BTNSORTBY       3
#define CONTROL_BTNSORTASC      4
#define CONTROL_LABELFILES      12

using namespace ADDON;
using namespace KODI::MESSAGING;
using KODI::MESSAGING::HELPERS::DialogResponse;

using namespace kodi; // addon-dev-kit namespace
using namespace kodi::gui; // addon-dev-kit namespace

extern "C"
{
namespace ADDON
{

void Interface_GUIWindow::Init(AddonGlobalInterface* addonInterface)
{
  addonInterface->toKodi->kodi_gui->window.New = New;
  addonInterface->toKodi->kodi_gui->window.Delete = Delete;
  addonInterface->toKodi->kodi_gui->window.SetCallbacks = SetCallbacks;
  addonInterface->toKodi->kodi_gui->window.Show = Show;
  addonInterface->toKodi->kodi_gui->window.Close = Close;
  addonInterface->toKodi->kodi_gui->window.DoModal = DoModal;
  addonInterface->toKodi->kodi_gui->window.SetFocusId = SetFocusId;
  addonInterface->toKodi->kodi_gui->window.GetFocusId = GetFocusId;
  addonInterface->toKodi->kodi_gui->window.SetProperty = SetProperty;
  addonInterface->toKodi->kodi_gui->window.SetPropertyInt = SetPropertyInt;
  addonInterface->toKodi->kodi_gui->window.SetPropertyBool = SetPropertyBool;
  addonInterface->toKodi->kodi_gui->window.SetPropertyDouble = SetPropertyDouble;
  addonInterface->toKodi->kodi_gui->window.GetProperty = GetProperty;
  addonInterface->toKodi->kodi_gui->window.GetPropertyInt = GetPropertyInt;
  addonInterface->toKodi->kodi_gui->window.GetPropertyBool = GetPropertyBool;
  addonInterface->toKodi->kodi_gui->window.GetPropertyDouble = GetPropertyDouble;
  addonInterface->toKodi->kodi_gui->window.ClearProperties = ClearProperties;
  addonInterface->toKodi->kodi_gui->window.ClearProperty = ClearProperty;
  addonInterface->toKodi->kodi_gui->window.GetListSize = GetListSize;
  addonInterface->toKodi->kodi_gui->window.ClearList = ClearList;
  addonInterface->toKodi->kodi_gui->window.AddItem = AddItem;
  addonInterface->toKodi->kodi_gui->window.AddStringItem = AddStringItem;
  addonInterface->toKodi->kodi_gui->window.RemoveItem = RemoveItem;
  addonInterface->toKodi->kodi_gui->window.RemoveItemFile = RemoveItemFile;
  addonInterface->toKodi->kodi_gui->window.GetListItem = GetListItem;
  addonInterface->toKodi->kodi_gui->window.SetCurrentListPosition = SetCurrentListPosition;
  addonInterface->toKodi->kodi_gui->window.GetCurrentListPosition = GetCurrentListPosition;
  addonInterface->toKodi->kodi_gui->window.SetControlLabel = SetControlLabel;
  addonInterface->toKodi->kodi_gui->window.MarkDirtyRegion = MarkDirtyRegion;

  addonInterface->toKodi->kodi_gui->window.GetControl_Button = GetControl_Button;
  addonInterface->toKodi->kodi_gui->window.GetControl_Edit = GetControl_Edit;
  addonInterface->toKodi->kodi_gui->window.GetControl_FadeLabel = GetControl_FadeLabel;
  addonInterface->toKodi->kodi_gui->window.GetControl_Image = GetControl_Image;
  addonInterface->toKodi->kodi_gui->window.GetControl_Label = GetControl_Label;
  addonInterface->toKodi->kodi_gui->window.GetControl_Spin = GetControl_Spin;
  addonInterface->toKodi->kodi_gui->window.GetControl_RadioButton = GetControl_RadioButton;
  addonInterface->toKodi->kodi_gui->window.GetControl_Progress = GetControl_Progress;
  addonInterface->toKodi->kodi_gui->window.GetControl_RenderAddon = GetControl_RenderAddon;
  addonInterface->toKodi->kodi_gui->window.GetControl_Slider = GetControl_Slider;
  addonInterface->toKodi->kodi_gui->window.GetControl_SettingsSlider= GetControl_SettingsSlider;
  addonInterface->toKodi->kodi_gui->window.GetControl_TextBox = GetControl_TextBox;
}


void* Interface_GUIWindow::New(void* kodiBase, const char *xmlFilename,
                               const char *defaultSkin, bool forceFallback,
                               bool asDialog)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid data", __FUNCTION__);
    return nullptr;
  }

  RESOLUTION_INFO res;
  std::string strSkinPath;
  if (!forceFallback)
  {
    /* Check to see if the XML file exists in current skin. If not use
       fallback path to find a skin for the addon */
    strSkinPath = g_SkinInfo->GetSkinPath(xmlFilename, &res);
    if (!XFILE::CFile::Exists(strSkinPath))
    {
      std::string skinPath = g_SkinInfo->Path();
      StringUtils::TrimRight(skinPath, "/\\");

      /* Check for the matching folder for the skin in the fallback skins folder */
      std::string basePath = URIUtils::AddFileToFolder(
        addon->Path(),
        "resources",
        "skins",
        URIUtils::GetFileName(skinPath));
      strSkinPath = g_SkinInfo->GetSkinPath(xmlFilename, &res, basePath);
      if (!XFILE::CFile::Exists(strSkinPath))
      {
        /* Finally fallback to the DefaultSkin as it didn't exist in either the
           XBMC Skin folder or the fallback skin folder */
        forceFallback = true;
      }
    }
  }

  if (forceFallback)
  {
    //FIXME make this static method of current skin?
    std::string str("none");
    ADDON::AddonInfoPtr addonInfo = std::make_shared<ADDON::CAddonInfo>(str, ADDON::ADDON_SKIN);
    addonInfo->SetPath(URIUtils::AddFileToFolder(
      addon->Path(),
      "resources",
      "skins",
      defaultSkin));

    CSkinInfo skinInfo(addonInfo);
    skinInfo.Start();
    strSkinPath = skinInfo.GetSkinPath(xmlFilename, &res, addonInfo->Path());

    if (!XFILE::CFile::Exists(strSkinPath))
    {
      CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow - New:: %s/%s - XML File '%s' for Window is missing, contact Developer '%s' of this AddOn",
                            CAddonInfo::TranslateType(addon->MainType()).c_str(), addon->Name().c_str(), strSkinPath.c_str(), addon->Author().c_str());
      return nullptr;
    }
  }

  // window id's 14000 - 14100 are reserved for addons
  // get first window id that is not in use
  int id = WINDOW_ADDON_START;
  // if window 14099 is in use it means addon can't create more windows
  Interface_GUIGeneral::lock();
  if (g_windowManager.GetWindow(WINDOW_ADDON_END))
  {
    Interface_GUIGeneral::unlock();
    throw std::logic_error(StringUtils::Format("ADDON::Interface_GUIWindow - %s: %s - maximum number of windows reached",
                __FUNCTION__,
                addon->Name().c_str()).c_str());
  }
  while(id < WINDOW_ADDON_END && g_windowManager.GetWindow(id) != nullptr) id++;
  Interface_GUIGeneral::unlock();

  CGUIWindow *window;
  if (!asDialog)
    window = new CGUIAddonWindow(id, strSkinPath, addon);
  else
    window = new CGUIAddonWindowDialog(id, strSkinPath, addon);

  Interface_GUIGeneral::lock();
  g_windowManager.Add(window);
  Interface_GUIGeneral::unlock();

  window->SetCoordsRes(res);
  return window;
}

void Interface_GUIWindow::Delete(void* kodiBase, void* handle)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    throw std::logic_error(StringUtils::Format("ADDON::Interface_GUIWindow - %s: %s - No Window",
                __FUNCTION__,
                addon->Name().c_str()).c_str());
  }

  CGUIAddonWindow *pAddonWindow = (CGUIAddonWindow*)handle;
  CGUIWindow *pWindow = (CGUIWindow*)g_windowManager.GetWindow(pAddonWindow->m_iWindowId);
  if (!pWindow)
    return;

  Interface_GUIGeneral::lock();
  // first change to an existing window
  if (g_windowManager.GetActiveWindow() == pAddonWindow->m_iWindowId && !g_application.m_bStop)
  {
    if(g_windowManager.GetWindow(pAddonWindow->m_iOldWindowId))
      g_windowManager.ActivateWindow(pAddonWindow->m_iOldWindowId);
    else // old window does not exist anymore, switch to home
      g_windowManager.ActivateWindow(WINDOW_HOME);
  }
  // Free any window properties
  pAddonWindow->ClearProperties();
  // free the window's resources and unload it (free all guicontrols)
  pAddonWindow->FreeResources(true);

  g_windowManager.Remove(pAddonWindow->GetID());
  delete pAddonWindow;
  Interface_GUIGeneral::unlock();
}

void Interface_GUIWindow::SetCallbacks(void* kodiBase, void* handle, void* clienthandle,
                                bool (*initCB)(void*), bool (*clickCB)(void*, int),
                                bool (*focusCB)(void*, int), bool (*onActionCB)(void* handle, int))
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - No Window on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  CGUIAddonWindow *pAddonWindow = (CGUIAddonWindow*)handle;

  Interface_GUIGeneral::lock();
  pAddonWindow->m_clientHandle = clienthandle;
  pAddonWindow->CBOnInit = initCB;
  pAddonWindow->CBOnClick = clickCB;
  pAddonWindow->CBOnFocus = focusCB;
  pAddonWindow->CBOnAction = onActionCB;
  Interface_GUIGeneral::unlock();
}

bool Interface_GUIWindow::Show(void* kodiBase, void* handle)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid data", __FUNCTION__);
    return false;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - No Window on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return false;
  }

  CGUIAddonWindow *pAddonWindow = (CGUIAddonWindow*)handle;
  CGUIWindow *pWindow = (CGUIWindow*)g_windowManager.GetWindow(pAddonWindow->m_iWindowId);
  if (!pWindow)
    return false;

  if (pAddonWindow->m_iOldWindowId != pAddonWindow->m_iWindowId && pAddonWindow->m_iWindowId != g_windowManager.GetActiveWindow())
    pAddonWindow->m_iOldWindowId = g_windowManager.GetActiveWindow();

  Interface_GUIGeneral::lock();
  if (pAddonWindow->IsDialog())
    ((CGUIAddonWindowDialog*)pAddonWindow)->Show();
  else
    g_windowManager.ActivateWindow(pAddonWindow->m_iWindowId);
  Interface_GUIGeneral::unlock();

  return true;
}

bool Interface_GUIWindow::Close(void* kodiBase, void* handle)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid data", __FUNCTION__);
    return false;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - No Window on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return false;
  }

  CGUIAddonWindow *pAddonWindow = (CGUIAddonWindow*)handle;
  CGUIWindow      *pWindow = (CGUIWindow*)g_windowManager.GetWindow(pAddonWindow->m_iWindowId);
  if (!pWindow)
    return false;

  pAddonWindow->m_bModal = false;
  if (pAddonWindow->IsDialog())
    ((CGUIAddonWindowDialog*)pAddonWindow)->PulseActionEvent();
  else
    ((CGUIAddonWindow*)pAddonWindow)->PulseActionEvent();

  Interface_GUIGeneral::lock();
  // if it's a dialog, we have to close it a bit different
  if (pAddonWindow->IsDialog())
    ((CGUIAddonWindowDialog*)pAddonWindow)->Show(false);
  else
    g_windowManager.ActivateWindow(pAddonWindow->m_iOldWindowId);
  pAddonWindow->m_iOldWindowId = 0;

  Interface_GUIGeneral::unlock();

  return true;
}

bool Interface_GUIWindow::DoModal(void* kodiBase, void* handle)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid data", __FUNCTION__);
    return false;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - No Window on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return false;
  }

  CGUIAddonWindow *pAddonWindow = (CGUIAddonWindow*)handle;
  CGUIWindow      *pWindow = (CGUIWindow*)g_windowManager.GetWindow(pAddonWindow->m_iWindowId);
  if (!pWindow)
    return false;

  pAddonWindow->m_bModal = true;

  if (pAddonWindow->m_iWindowId != g_windowManager.GetActiveWindow())
    Show(kodiBase, handle);

  return true;
}

bool Interface_GUIWindow::SetFocusId(void* kodiBase, void* handle, int iControlId)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid data", __FUNCTION__);
    return false;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - No Window on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return false;
  }

  CGUIAddonWindow *pAddonWindow = (CGUIAddonWindow*)handle;
  CGUIWindow      *pWindow = (CGUIWindow*)g_windowManager.GetWindow(pAddonWindow->m_iWindowId);
  if (!pWindow)
    return false;

  if (!pWindow->GetControl(iControlId))
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow - %s: %s - Control does not exist in window",
                __FUNCTION__,
                addon->Name().c_str());
    return false;
  }

  Interface_GUIGeneral::lock();
  CGUIMessage msg = CGUIMessage(GUI_MSG_SETFOCUS, pAddonWindow->m_iWindowId, iControlId);
  pWindow->OnMessage(msg);
  Interface_GUIGeneral::unlock();

  return true;
}

int Interface_GUIWindow::GetFocusId(void* kodiBase, void* handle)
{
  int iControlId = -1;

  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid data", __FUNCTION__);
    return iControlId;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - No Window on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return iControlId;
  }

  CGUIAddonWindow *pAddonWindow = (CGUIAddonWindow*)handle;
  CGUIWindow      *pWindow = (CGUIWindow*)g_windowManager.GetWindow(pAddonWindow->m_iWindowId);
  if (!pWindow)
    return iControlId;

  Interface_GUIGeneral::lock();
  iControlId = pWindow->GetFocusedControlID();
  Interface_GUIGeneral::unlock();

  if (iControlId == -1)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow - %s: %s - No control in this window has focus", __FUNCTION__, addon->Name().c_str());
    return iControlId;
  }

  return iControlId;
}

void Interface_GUIWindow::SetProperty(void* kodiBase, void* handle, const char *key, const char *value)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle || !key || !value)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - No Window or nullptr key or value on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  CGUIAddonWindow *pAddonWindow = (CGUIAddonWindow*)handle;
  CGUIWindow *pWindow = (CGUIWindow*)g_windowManager.GetWindow(pAddonWindow->m_iWindowId);
  if (!pWindow)
    return;

  std::string lowerKey = key;
  StringUtils::ToLower(lowerKey);

  Interface_GUIGeneral::lock();
  pWindow->SetProperty(lowerKey, value);
  Interface_GUIGeneral::unlock();
}

void Interface_GUIWindow::SetPropertyInt(void* kodiBase, void* handle, const char *key, int value)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle || !key)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  CGUIAddonWindow *pAddonWindow = (CGUIAddonWindow*)handle;
  CGUIWindow      *pWindow = (CGUIWindow*)g_windowManager.GetWindow(pAddonWindow->m_iWindowId);
  if (!pWindow)
    return;

  std::string lowerKey = key;
  StringUtils::ToLower(lowerKey);

  Interface_GUIGeneral::lock();
  pWindow->SetProperty(lowerKey, value);
  Interface_GUIGeneral::unlock();
}

void Interface_GUIWindow::SetPropertyBool(void* kodiBase, void* handle, const char *key, bool value)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle || !key)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  CGUIAddonWindow *pAddonWindow = (CGUIAddonWindow*)handle;
  CGUIWindow      *pWindow = (CGUIWindow*)g_windowManager.GetWindow(pAddonWindow->m_iWindowId);
  if (!pWindow)
    return;

  std::string lowerKey = key;
  StringUtils::ToLower(lowerKey);

  Interface_GUIGeneral::lock();
  pWindow->SetProperty(lowerKey, value);
  Interface_GUIGeneral::unlock();
}

void Interface_GUIWindow::SetPropertyDouble(void* kodiBase, void* handle, const char *key, double value)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle || !key)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  CGUIAddonWindow *pAddonWindow = (CGUIAddonWindow*)handle;
  CGUIWindow      *pWindow = (CGUIWindow*)g_windowManager.GetWindow(pAddonWindow->m_iWindowId);
  if (!pWindow)
    return;

  std::string lowerKey = key;
  StringUtils::ToLower(lowerKey);

  Interface_GUIGeneral::lock();
  pWindow->SetProperty(lowerKey, value);
  Interface_GUIGeneral::unlock();
}

void Interface_GUIWindow::GetProperty(void* kodiBase, void* handle, const char *key, char &property, unsigned int &iMaxStringSize)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle || !key)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  CGUIAddonWindow *pAddonWindow = (CGUIAddonWindow*)handle;
  CGUIWindow      *pWindow = (CGUIWindow*)g_windowManager.GetWindow(pAddonWindow->m_iWindowId);
  if (!pWindow)
    return;

  std::string lowerKey = key;
  StringUtils::ToLower(lowerKey);

  Interface_GUIGeneral::lock();
  std::string value = pWindow->GetProperty(lowerKey).asString();
  Interface_GUIGeneral::unlock();

  strncpy(&property, value.c_str(), iMaxStringSize);
  iMaxStringSize = value.length();
}

int Interface_GUIWindow::GetPropertyInt(void* kodiBase, void* handle, const char *key)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid data", __FUNCTION__);
    return -1;
  }

  if (!handle || !key)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return -1;
  }

  CGUIAddonWindow *pAddonWindow = (CGUIAddonWindow*)handle;
  CGUIWindow      *pWindow = (CGUIWindow*)g_windowManager.GetWindow(pAddonWindow->m_iWindowId);
  if (!pWindow)
    return -1;

  std::string lowerKey = key;
  StringUtils::ToLower(lowerKey);

  Interface_GUIGeneral::lock();
  int value = (int)pWindow->GetProperty(lowerKey).asInteger();
  Interface_GUIGeneral::unlock();

  return value;
}

bool Interface_GUIWindow::GetPropertyBool(void* kodiBase, void* handle, const char *key)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid data", __FUNCTION__);
    return false;
  }

  if (!handle || !key)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return false;
  }

  CGUIAddonWindow *pAddonWindow = (CGUIAddonWindow*)handle;
  CGUIWindow *pWindow = (CGUIWindow*)g_windowManager.GetWindow(pAddonWindow->m_iWindowId);
  if (!pWindow)
    return false;

  std::string lowerKey = key;
  StringUtils::ToLower(lowerKey);

  Interface_GUIGeneral::lock();
  bool value = pWindow->GetProperty(lowerKey).asBoolean();
  Interface_GUIGeneral::unlock();

  return value;
}

double Interface_GUIWindow::GetPropertyDouble(void* kodiBase, void* handle, const char *key)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid data", __FUNCTION__);
    return 0.0;
  }

  if (!handle || !key)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return 0.0;
  }

  CGUIAddonWindow *pAddonWindow = (CGUIAddonWindow*)handle;
  CGUIWindow *pWindow = (CGUIWindow*)g_windowManager.GetWindow(pAddonWindow->m_iWindowId);
  if (!pWindow)
    return 0.0;

  std::string lowerKey = key;
  StringUtils::ToLower(lowerKey);

  Interface_GUIGeneral::lock();
  double value = pWindow->GetProperty(lowerKey).asDouble();
  Interface_GUIGeneral::unlock();

  return value;
}

void Interface_GUIWindow::ClearProperties(void* kodiBase, void* handle)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  CGUIAddonWindow *pAddonWindow = (CGUIAddonWindow*)handle;
  CGUIWindow *pWindow = (CGUIWindow*)g_windowManager.GetWindow(pAddonWindow->m_iWindowId);
  if (!pWindow)
    return;

  Interface_GUIGeneral::lock();
  pWindow->ClearProperties();
  Interface_GUIGeneral::unlock();
}

void Interface_GUIWindow::ClearProperty(void* kodiBase, void* handle, const char *key)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  CGUIAddonWindow *pAddonWindow = (CGUIAddonWindow*)handle;
  CGUIWindow *pWindow = (CGUIWindow*)g_windowManager.GetWindow(pAddonWindow->m_iWindowId);
  if (!pWindow)
    return;

  std::string lowerKey = key;
  StringUtils::ToLower(lowerKey);
  Interface_GUIGeneral::lock();
  pWindow->SetProperty(lowerKey, "");
  Interface_GUIGeneral::unlock();
}

int Interface_GUIWindow::GetListSize(void* kodiBase, void* handle)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid data", __FUNCTION__);
    return -1;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return -1;
  }

  Interface_GUIGeneral::lock();
  int listSize = static_cast<CGUIAddonWindow*>(handle)->GetListSize();
  Interface_GUIGeneral::unlock();

  return listSize;
}

void Interface_GUIWindow::ClearList(void* kodiBase, void* handle)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  Interface_GUIGeneral::lock();
  static_cast<CGUIAddonWindow*>(handle)->ClearList();
  Interface_GUIGeneral::unlock();
}

void* Interface_GUIWindow::AddItem(void* kodiBase, void* handle, void* item, int itemPosition)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid data", __FUNCTION__);
    return nullptr;
  }

  if (!handle || !item)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return nullptr;
  }

  CFileItemPtr pItem((CFileItem*)item);
  Interface_GUIGeneral::lock();
  static_cast<CGUIAddonWindow*>(handle)->AddItem(pItem, itemPosition);
  Interface_GUIGeneral::unlock();

  return item;
}

void* Interface_GUIWindow::AddStringItem(void* kodiBase, void* handle, const char *itemName, int itemPosition)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid data", __FUNCTION__);
    return nullptr;
  }

  if (!handle || !itemName)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return nullptr;
  }

  CFileItemPtr item(new CFileItem(itemName));
  Interface_GUIGeneral::lock();
  static_cast<CGUIAddonWindow*>(handle)->AddItem(item, itemPosition);
  Interface_GUIGeneral::unlock();

  return item.get();
}

void Interface_GUIWindow::RemoveItem(void* kodiBase, void* handle, int itemPosition)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  Interface_GUIGeneral::lock();
  static_cast<CGUIAddonWindow*>(handle)->RemoveItem(itemPosition);
  Interface_GUIGeneral::unlock();
}

void Interface_GUIWindow::RemoveItemFile(void* kodiBase, void* handle, void* fileItem)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  Interface_GUIGeneral::lock();
  static_cast<CGUIAddonWindow*>(handle)->RemoveItem((CFileItem*)fileItem);
  Interface_GUIGeneral::unlock();
}

void* Interface_GUIWindow::GetListItem(void* kodiBase, void* handle, int listPos)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid data", __FUNCTION__);
    return nullptr;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return nullptr;
  }

  CGUIAddonWindow *pAddonWindow = (CGUIAddonWindow*)handle;

  Interface_GUIGeneral::lock();
  CFileItemPtr fi = pAddonWindow->GetListItem(listPos);
  if (fi == nullptr)
  {
    Interface_GUIGeneral::unlock();
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow - %s: %s - Index out of range",
                __FUNCTION__,
                addon->Name().c_str());
    return nullptr;
  }
  Interface_GUIGeneral::unlock();

  return fi.get();
}

void Interface_GUIWindow::SetCurrentListPosition(void* kodiBase, void* handle, int listPos)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  CGUIAddonWindow *pAddonWindow = static_cast<CGUIAddonWindow*>(handle);

  Interface_GUIGeneral::lock();
  pAddonWindow->SetCurrentListPosition(listPos);
  Interface_GUIGeneral::unlock();
}

int Interface_GUIWindow::GetCurrentListPosition(void* kodiBase, void* handle)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid data", __FUNCTION__);
    return -1;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return -1;
  }

  CGUIAddonWindow *pAddonWindow = static_cast<CGUIAddonWindow*>(handle);

  Interface_GUIGeneral::lock();
  int listPos = pAddonWindow->GetCurrentListPosition();
  Interface_GUIGeneral::unlock();

  return listPos;
}

void Interface_GUIWindow::SetControlLabel(void* kodiBase, void* handle, int controlId, const char *label)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  CGUIAddonWindow *pAddonWindow = static_cast<CGUIAddonWindow*>(handle);

  CGUIMessage msg(GUI_MSG_LABEL_SET, pAddonWindow->m_iWindowId, controlId);
  msg.SetLabel(label);
  pAddonWindow->OnMessage(msg);
}

void Interface_GUIWindow::MarkDirtyRegion(void* kodiBase, void* handle)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  static_cast<CGUIAddonWindow*>(handle)->MarkDirtyRegion();
}

void* Interface_GUIWindow::GetControl_Button(void* kodiBase, void* handle, int controlId)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid data", __FUNCTION__);
    return nullptr;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return nullptr;
  }

  return static_cast<CGUIAddonWindow*>(handle)->GetAddonControl(controlId, CGUIControl::GUICONTROL_BUTTON, "button");
}

void* Interface_GUIWindow::GetControl_FadeLabel(void* kodiBase, void* handle, int controlId)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid data", __FUNCTION__);
    return nullptr;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return nullptr;
  }

  return static_cast<CGUIAddonWindow*>(handle)->GetAddonControl(controlId, CGUIControl::GUICONTROL_FADELABEL, "fade label");
}

void* Interface_GUIWindow::GetControl_Label(void* kodiBase, void* handle, int controlId)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid data", __FUNCTION__);
    return nullptr;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return nullptr;
  }

  return static_cast<CGUIAddonWindow*>(handle)->GetAddonControl(controlId, CGUIControl::GUICONTROL_LABEL, "label");
}

void* Interface_GUIWindow::GetControl_Image(void* kodiBase, void* handle, int controlId)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid data", __FUNCTION__);
    return nullptr;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return nullptr;
  }

  return static_cast<CGUIAddonWindow*>(handle)->GetAddonControl(controlId, CGUIControl::GUICONTROL_IMAGE, "image");
}

void* Interface_GUIWindow::GetControl_RadioButton(void* kodiBase, void* handle, int controlId)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid data", __FUNCTION__);
    return nullptr;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return nullptr;
  }

  return static_cast<CGUIAddonWindow*>(handle)->GetAddonControl(controlId, CGUIControl::GUICONTROL_RADIO, "radio button");
}

void* Interface_GUIWindow::GetControl_Edit(void* kodiBase, void* handle, int controlId)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid data", __FUNCTION__);
    return nullptr;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return nullptr;
  }

  return static_cast<CGUIAddonWindow*>(handle)->GetAddonControl(controlId, CGUIControl::GUICONTROL_EDIT, "edit");
}

void* Interface_GUIWindow::GetControl_Progress(void* kodiBase, void* handle, int controlId)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid data", __FUNCTION__);
    return nullptr;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return nullptr;
  }

  return static_cast<CGUIAddonWindow*>(handle)->GetAddonControl(controlId, CGUIControl::GUICONTROL_PROGRESS, "progress");
}

void* Interface_GUIWindow::GetControl_Spin(void* kodiBase, void* handle, int controlId)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid data", __FUNCTION__);
    return nullptr;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return nullptr;
  }

  return static_cast<CGUIAddonWindow*>(handle)->GetAddonControl(controlId, CGUIControl::GUICONTROL_SPINEX, "spin");
}

void* Interface_GUIWindow::GetControl_RenderAddon(void* kodiBase, void* handle, int controlId)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid data", __FUNCTION__);
    return nullptr;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return nullptr;
  }

  CGUIControl* pGUIControl = static_cast<CGUIAddonWindow*>(handle)->GetAddonControl(controlId, CGUIControl::GUICONTROL_RENDERADDON, "renderaddon");
  if (!pGUIControl)
    return nullptr;

  CGUIAddonRenderingControl *pRenderControl = new CGUIAddonRenderingControl((CGUIRenderingControl*)pGUIControl);
  return pRenderControl;
}

void* Interface_GUIWindow::GetControl_Slider(void* kodiBase, void* handle, int controlId)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid data", __FUNCTION__);
    return nullptr;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return nullptr;
  }

  return static_cast<CGUIAddonWindow*>(handle)->GetAddonControl(controlId, CGUIControl::GUICONTROL_SLIDER, "slider");
}

void* Interface_GUIWindow::GetControl_SettingsSlider(void* kodiBase, void* handle, int controlId)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid data", __FUNCTION__);
    return nullptr;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return nullptr;
  }

  return static_cast<CGUIAddonWindow*>(handle)->GetAddonControl(controlId, CGUIControl::GUICONTROL_SETTINGS_SLIDER, "settings slider");
}

void* Interface_GUIWindow::GetControl_TextBox(void* kodiBase, void* handle, int controlId)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid data", __FUNCTION__);
    return nullptr;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIWindow::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return nullptr;
  }

  return static_cast<CGUIAddonWindow*>(handle)->GetAddonControl(controlId, CGUIControl::GUICONTROL_TEXTBOX, "textbox");
}

CGUIAddonWindow::CGUIAddonWindow(int id, const std::string& strXML, CAddonDll* addon)
 : CGUIMediaWindow(id, strXML.c_str()),
   CBOnInit{nullptr},
   CBOnFocus{nullptr},
   CBOnClick{nullptr},
   CBOnAction{nullptr},
   m_clientHandle{nullptr},
   m_iWindowId(id),
   m_iOldWindowId(0),
   m_bModal(false),
   m_bIsDialog(false),
   m_actionEvent(true),
   m_addon(addon)
{
  m_loadType = LOAD_ON_GUI_INIT;
}

CGUIAddonWindow::~CGUIAddonWindow(void)
{
}

CGUIControl* CGUIAddonWindow::GetAddonControl(int controlId, CGUIControl::GUICONTROLTYPES type, std::string typeName)
{
  CGUIControl* pGUIControl = dynamic_cast<CGUIControl*>(GetControl(controlId));
  if (!pGUIControl)
  {
    CLog::Log(LOGERROR, "CGUIAddonGUI_Window::%s: %s - Requested GUI control Id '%i' for '%s' not present!",
                __FUNCTION__,
                m_addon->Name().c_str(),
                controlId, typeName.c_str());
    return nullptr;
  }
  else if (pGUIControl->GetControlType() != type)
  {
    CLog::Log(LOGERROR, "CGUIAddonGUI_Window::%s: %s - Requested GUI control Id '%i' not the type '%s'!",
                __FUNCTION__,
                m_addon->Name().c_str(),
                controlId, typeName.c_str());
    return nullptr;
  }

  return pGUIControl;
}

bool CGUIAddonWindow::OnAction(const CAction &action)
{
  // Let addon decide whether it wants to hande action first
  if (CBOnAction && CBOnAction(m_clientHandle, GetAddonGUIActionType(action.GetID())))
    return true;

  return CGUIWindow::OnAction(action);
}

bool CGUIAddonWindow::OnMessage(CGUIMessage& message)
{
  // TODO: We shouldn't be dropping down to CGUIWindow in any of this ideally.
  //       We have to make up our minds about what python should be doing and
  //       what this side of things should be doing
  switch (message.GetMessage())
  {
    case GUI_MSG_WINDOW_DEINIT:
    {
      return CGUIMediaWindow::OnMessage(message);
    }
    break;

    case GUI_MSG_WINDOW_INIT:
    {
      CGUIMediaWindow::OnMessage(message);
      if (CBOnInit)
      {
        CBOnInit(m_clientHandle);
      }
      return true;
    }
    break;

    case GUI_MSG_SETFOCUS:
    {
      if (m_viewControl.HasControl(message.GetControlId()) && m_viewControl.GetCurrentControl() != (int)message.GetControlId())
      {
        m_viewControl.SetFocused();
        return true;
      }
      // check if our focused control is one of our category buttons
      int iControl = message.GetControlId();
      if (CBOnFocus)
      {
        CBOnFocus(m_clientHandle, iControl);
      }
    }
    break;

    case GUI_MSG_FOCUSED:
    {
      if (HasID(message.GetSenderId()) && CBOnFocus)
      {
        CBOnFocus(m_clientHandle, message.GetControlId());
      }
    }
    break;

    case GUI_MSG_CLICKED:
    {
      int iControl=message.GetSenderId();
      // Handle Sort/View internally. Scripters shouldn't use ID 2, 3 or 4.
      if (iControl == CONTROL_BTNSORTASC) // sort asc
      {
        CLog::Log(LOGINFO, "WindowXML: Internal asc/dsc button not implemented");
        /*if (m_guiState.get())
          m_guiState->SetNextSortOrder();
        UpdateFileList();*/
        return true;
      }
      else if (iControl == CONTROL_BTNSORTBY) // sort by
      {
        CLog::Log(LOGINFO, "WindowXML: Internal sort button not implemented");
        /*if (m_guiState.get())
          m_guiState->SetNextSortMethod();
        UpdateFileList();*/
        return true;
      }

      if (CBOnClick && iControl && iControl != (int)this->GetID())
      {
        CGUIControl* controlClicked = (CGUIControl*)this->GetControl(iControl);

        // The old python way used to check list AND SELECITEM method or if its a button, checkmark.
        // Its done this way for now to allow other controls without a python version like togglebutton to still raise a onAction event
        if (controlClicked) // Will get problems if we the id is not on the window and we try to do GetControlType on it. So check to make sure it exists
        {
          if ((controlClicked->IsContainer() && (message.GetParam1() == ACTION_SELECT_ITEM ||
                                                 message.GetParam1() == ACTION_MOUSE_LEFT_CLICK)) ||
                                                 !controlClicked->IsContainer())
          {
            return CBOnClick(m_clientHandle, iControl);
          }
          else if (controlClicked->IsContainer() && message.GetParam1() == ACTION_MOUSE_RIGHT_CLICK)
          {
//            PyXBMCAction* inf = new PyXBMCAction;
//            inf->pObject = Action_FromAction(CAction(ACTION_CONTEXT_MENU));
//            inf->pCallbackWindow = pCallbackWindow;
//
//            // aquire lock?
//            PyXBMC_AddPendingCall(Py_XBMC_Event_OnAction, inf);
//            PulseActionEvent();
          }
        }
      }
    }
    break;
  }

  return CGUIMediaWindow::OnMessage(message);
}

void CGUIAddonWindow::AllocResources(bool forceLoad /*= FALSE */)
{
  std::string tmpDir = URIUtils::GetDirectory(GetProperty("xmlfile").asString());
  std::string fallbackMediaPath;
  URIUtils::GetParentPath(tmpDir, fallbackMediaPath);
  URIUtils::RemoveSlashAtEnd(fallbackMediaPath);
  m_mediaDir = fallbackMediaPath;

  //CLog::Log(LOGDEBUG, "CGUIPythonWindowXML::AllocResources called: %s", fallbackMediaPath.c_str());
  g_TextureManager.AddTexturePath(m_mediaDir);
  CGUIMediaWindow::AllocResources(forceLoad);
  g_TextureManager.RemoveTexturePath(m_mediaDir);
}

void CGUIAddonWindow::FreeResources(bool forceUnLoad /*= FALSE */)
{
  CGUIMediaWindow::FreeResources(forceUnLoad);
}

void CGUIAddonWindow::Render()
{
  g_TextureManager.AddTexturePath(m_mediaDir);
  CGUIMediaWindow::Render();
  g_TextureManager.RemoveTexturePath(m_mediaDir);
}

void CGUIAddonWindow::Update()
{
}

void CGUIAddonWindow::AddItem(CFileItemPtr fileItem, int itemPosition)
{
  if (itemPosition == -1 || itemPosition > m_vecItems->Size())
  {
    m_vecItems->Add(fileItem);
  }
  else if (itemPosition <  -1 &&  !(itemPosition-1 < m_vecItems->Size()))
  {
    m_vecItems->AddFront(fileItem,0);
  }
  else
  {
    m_vecItems->AddFront(fileItem, itemPosition);
  }
  m_viewControl.SetItems(*m_vecItems);
  UpdateButtons();
}

void CGUIAddonWindow::RemoveItem(int itemPosition)
{
  m_vecItems->Remove(itemPosition);
  m_viewControl.SetItems(*m_vecItems);
  UpdateButtons();
}

void CGUIAddonWindow::RemoveItem(CFileItem* fileItem)
{
  m_vecItems->Remove(fileItem);
  m_viewControl.SetItems(*m_vecItems);
  UpdateButtons();
}

int CGUIAddonWindow::GetCurrentListPosition()
{
  return m_viewControl.GetSelectedItem();
}

void CGUIAddonWindow::SetCurrentListPosition(int item)
{
  m_viewControl.SetSelectedItem(item);
}

int CGUIAddonWindow::GetListSize()
{
  return m_vecItems->Size();
}

CFileItemPtr CGUIAddonWindow::GetListItem(int position)
{
  if (position < 0 || position >= m_vecItems->Size()) return CFileItemPtr();
  return m_vecItems->Get(position);
}

void CGUIAddonWindow::ClearList()
{
  ClearFileItems();

  m_viewControl.SetItems(*m_vecItems);
  UpdateButtons();
}

void CGUIAddonWindow::GetContextButtons(int itemNumber, CContextButtons &buttons)
{
  // maybe on day we can make an easy way to do this context menu
  // with out this method overriding the MediaWindow version, it will display 'Add to Favorites'
}

void CGUIAddonWindow::WaitForActionEvent(unsigned int timeout)
{
  m_actionEvent.WaitMSec(timeout);
  m_actionEvent.Reset();
}

void CGUIAddonWindow::PulseActionEvent()
{
  m_actionEvent.Set();
}

bool CGUIAddonWindow::OnClick(int iItem, const std::string &player)
{
  // Hook Over calling  CGUIMediaWindow::OnClick(iItem) results in it trying to PLAY the file item
  // which if its not media is BAD and 99 out of 100 times undesireable.
  return false;
}

// SetupShares();
/*
 CGUIMediaWindow::OnWindowLoaded() calls SetupShares() so override it
and just call UpdateButtons();
*/
void CGUIAddonWindow::SetupShares()
{
  UpdateButtons();
}


CGUIAddonWindowDialog::CGUIAddonWindowDialog(int id, const std::string& strXML, CAddonDll* addon)
: CGUIAddonWindow(id,strXML,addon)
{
  m_bRunning = false;
  m_bIsDialog = true;
}

CGUIAddonWindowDialog::~CGUIAddonWindowDialog(void)
{
}

bool CGUIAddonWindowDialog::OnMessage(CGUIMessage &message)
{
  if (message.GetMessage() == GUI_MSG_WINDOW_DEINIT)
    return CGUIWindow::OnMessage(message);

  return CGUIAddonWindow::OnMessage(message);
}

void CGUIAddonWindowDialog::Show(bool show /* = true */)
{
  unsigned int iCount = g_graphicsContext.exit();
  CApplicationMessenger::GetInstance().SendMsg(TMSG_GUI_ADDON_DIALOG, 0, show ? 1 : 0, static_cast<void*>(this));
  g_graphicsContext.restore(iCount);
}

void CGUIAddonWindowDialog::Show_Internal(bool show /* = true */)
{
  if (show)
  {
    m_bModal = true;
    m_bRunning = true;
    g_windowManager.RegisterDialog(this);

    // active this window...
    CGUIMessage msg(GUI_MSG_WINDOW_INIT, 0, 0, WINDOW_INVALID, m_iWindowId);
    OnMessage(msg);

    // this dialog is derived from GUiMediaWindow
    // make sure it is rendered last
    m_renderOrder = RENDER_ORDER_DIALOG;
    while (m_bRunning && !g_application.m_bStop)
    {
      ProcessRenderLoop();
    }
  }
  else // hide
  {
    m_bRunning = false;

    CGUIMessage msg(GUI_MSG_WINDOW_DEINIT, 0, 0);
    OnMessage(msg);

    g_windowManager.RemoveDialog(GetID());
  }
}

} /* namespace ADDON */
} /* extern "C" */
