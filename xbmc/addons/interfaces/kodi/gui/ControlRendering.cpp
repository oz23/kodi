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

#include "ControlRendering.h"
#include "General.h"
#include "addons/kodi-addon-dev-kit/include/kodi/gui/ControlRendering.h"

#include "addons/AddonDll.h"
#include "guilib/GUIRenderingControl.h"
#include "utils/log.h"

extern "C"
{
namespace ADDON
{

void Interface_GUIControlAddonRendering::Init(AddonGlobalInterface* addonInterface)
{
  addonInterface->toKodi->kodi_gui->controlRendering.SetCallbacks = SetCallbacks;
  addonInterface->toKodi->kodi_gui->controlRendering.Delete = Delete;
}

void Interface_GUIControlAddonRendering::SetCallbacks(
                            void* kodiBase, void* handle, void* clienthandle,
                            bool (*createCB)(void*,int,int,int,int,void*),
                            void (*renderCB)(void*), void (*stopCB)(void*), bool (*dirtyCB)(void*))
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "Interface_GUIControlAddonRendering::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlAddonRendering::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  CGUIAddonRenderingControl* pAddonControl = static_cast<CGUIAddonRenderingControl*>(handle);

  Interface_GUIGeneral::lock();
  pAddonControl->m_clientHandle = clienthandle;
  pAddonControl->CBCreate = createCB;
  pAddonControl->CBRender = renderCB;
  pAddonControl->CBStop = stopCB;
  pAddonControl->CBDirty = dirtyCB;
  pAddonControl->m_addon = addon;
  Interface_GUIGeneral::unlock();

  pAddonControl->m_pControl->InitCallback(pAddonControl);
}

void Interface_GUIControlAddonRendering::Delete(void* kodiBase, void* handle)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "Interface_GUIControlAddonRendering::%s - invalid data", __FUNCTION__);
    return;
  }

  if (!handle)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIControlAddonRendering::%s - invalid handler data on addon '%s'", __FUNCTION__, addon->ID().c_str());
    return;
  }

  Interface_GUIGeneral::lock();
  static_cast<CGUIAddonRenderingControl*>(handle)->Delete();
  Interface_GUIGeneral::unlock();
}


CGUIAddonRenderingControl::CGUIAddonRenderingControl(CGUIRenderingControl *pControl)
  : CBCreate{nullptr},
    CBRender{nullptr},
    CBStop{nullptr},
    CBDirty{nullptr},
    m_clientHandle{nullptr},
    m_addon{nullptr},
    m_pControl{pControl},
    m_refCount{1}
{
}

bool CGUIAddonRenderingControl::Create(int x, int y, int w, int h, void *device)
{
  if (CBCreate)
  {
    if (CBCreate(m_clientHandle, x, y, w, h, device))
    {
      ++m_refCount;
      return true;
    }
  }
  return false;
}

void CGUIAddonRenderingControl::Render()
{
  if (CBRender)
  {
    CBRender(m_clientHandle);
  }
}

void CGUIAddonRenderingControl::Stop()
{
  if (CBStop)
  {
    CBStop(m_clientHandle);
  }

  --m_refCount;
  if (m_refCount <= 0)
    delete this;
}

void CGUIAddonRenderingControl::Delete()
{
  --m_refCount;
  if (m_refCount <= 0)
    delete this;
}

bool CGUIAddonRenderingControl::IsDirty()
{
  bool ret = true;
  if (CBDirty)
  {
    ret = CBDirty(m_clientHandle);
  }
  return ret;
}

} /* namespace ADDON */
} /* extern "C" */
