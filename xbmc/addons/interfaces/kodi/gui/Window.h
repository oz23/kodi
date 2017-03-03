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

#include "threads/Event.h"
#include "windows/GUIMediaWindow.h"

extern "C"
{

struct AddonGlobalInterface;

namespace ADDON
{
  class CAddonDll;

  struct Interface_GUIWindow
  {
    static void Init(AddonGlobalInterface* addonInterface);

    static void*    New(void* kodiBase, const char *xmlFilename, const char *defaultSkin, bool forceFallback, bool asDialog);
    static void     Delete(void* kodiBase, void* handle);
    static void     SetCallbacks(void* kodiBase,
                                 void* handle,
                                 void* clienthandle,
                                 bool (*initCB)(void*),
                                 bool (*clickCB)(void*, int),
                                 bool (*focusCB)(void*, int),
                                 bool (*onActionCB)(void* handle, int));
    static bool     Show(void* kodiBase, void* handle);
    static bool     Close(void* kodiBase, void* handle);
    static bool     DoModal(void* kodiBase, void* handle);
    static bool     SetFocusId(void* kodiBase, void* handle, int iControlId);
    static int      GetFocusId(void* kodiBase, void* handle);
    static void     SetProperty(void* kodiBase, void* handle, const char *key, const char *value);
    static void     SetPropertyInt(void* kodiBase, void* handle, const char *key, int value);
    static void     SetPropertyBool(void* kodiBase, void* handle, const char *key, bool value);
    static void     SetPropertyDouble(void* kodiBase, void* handle, const char *key, double value);
    static void     GetProperty(void* kodiBase, void* handle, const char *key,char &property, unsigned int &iMaxStringSize);
    static int      GetPropertyInt(void* kodiBase, void* handle, const char *key);
    static bool     GetPropertyBool(void* kodiBase, void* handle, const char *key);
    static double   GetPropertyDouble(void* kodiBase, void* handle, const char *key);
    static void     ClearProperties(void* kodiBase, void* handle);
    static void     ClearProperty(void* kodiBase, void* handle, const char *key);
    static int      GetListSize(void* kodiBase, void* handle);
    static void     ClearList(void* kodiBase, void* handle);
    static void*    AddItem(void* kodiBase, void* handle, void* item, int itemPosition);
    static void*    AddStringItem(void* kodiBase, void* handle, const char *itemName, int itemPosition);
    static void     RemoveItem(void* kodiBase, void* handle, int itemPosition);
    static void     RemoveItemFile(void* kodiBase, void* handle, void* fileItem);
    static void*    GetListItem(void* kodiBase, void* handle, int listPos);
    static void     SetCurrentListPosition(void* kodiBase, void* handle, int listPos);
    static int      GetCurrentListPosition(void* kodiBase, void* handle);
    static void     SetControlLabel(void* kodiBase, void* handle, int controlId, const char *label);
    static void     MarkDirtyRegion(void* kodiBase, void* handle);

    static void*    GetControl_Button(void* kodiBase, void* handle, int controlId);
    static void*    GetControl_Edit(void* kodiBase, void* handle, int controlId);
    static void*    GetControl_FadeLabel(void* kodiBase, void* handle, int controlId);
    static void*    GetControl_Image(void* kodiBase, void* handle, int controlId);
    static void*    GetControl_Label(void* kodiBase, void* handle, int controlId);
    static void*    GetControl_Spin(void* kodiBase, void* handle, int controlId);
    static void*    GetControl_RadioButton(void* kodiBase, void* handle, int controlId);
    static void*    GetControl_Progress(void* kodiBase, void* handle, int controlId);
    static void*    GetControl_RenderAddon(void* kodiBase, void* handle, int controlId);
    static void*    GetControl_Slider(void* kodiBase, void* handle, int controlId);
    static void*    GetControl_SettingsSlider(void* kodiBase, void* handle, int controlId);
    static void*    GetControl_TextBox(void* kodiBase, void* handle, int controlId);
  };

  class CGUIAddonWindow : public CGUIMediaWindow
  {
  friend struct Interface_GUIWindow;

  public:
    CGUIAddonWindow(int id, const std::string& strXML, ADDON::CAddonDll* addon);
    virtual ~CGUIAddonWindow(void);

    bool OnMessage(CGUIMessage& message) override;
    bool OnAction(const CAction &action) override;
    void AllocResources(bool forceLoad = false) override;
    void FreeResources(bool forceUnLoad = false) override;
    void Render() override;
    void WaitForActionEvent(unsigned int timeout);
    void PulseActionEvent();
    void AddItem(CFileItemPtr fileItem, int itemPosition);
    void RemoveItem(int itemPosition);
    void RemoveItem(CFileItem* fileItem);
    void ClearList();
    CFileItemPtr GetListItem(int position);
    int GetListSize();
    int GetCurrentListPosition();
    void SetCurrentListPosition(int item);
    bool OnClick(int iItem, const std::string &player) override;

    CGUIControl* GetAddonControl(int controlId, CGUIControl::GUICONTROLTYPES type, std::string typeName);

  protected:
    void Update();
    void GetContextButtons(int itemNumber, CContextButtons &buttons) override;
    void SetupShares() override;

    bool (*CBOnInit)(void* cbhdl);
    bool (*CBOnFocus)(void* cbhdl, int controlId);
    bool (*CBOnClick)(void* cbhdl, int controlId);
    bool (*CBOnAction)(void* cbhdl, int);

    void* m_clientHandle;
    const int m_iWindowId;
    int m_iOldWindowId;
    bool m_bModal;
    bool m_bIsDialog;

  private:
    CEvent m_actionEvent;
    ADDON::CAddonDll* m_addon;
    std::string m_mediaDir;
  };

  class CGUIAddonWindowDialog : public CGUIAddonWindow
  {
  public:
    CGUIAddonWindowDialog(int id, const std::string& strXML, ADDON::CAddonDll* addon);
    virtual ~CGUIAddonWindowDialog(void);

    void  Show(bool show = true);
    virtual bool OnMessage(CGUIMessage &message);
    virtual bool IsDialogRunning() const { return m_bRunning; }
    virtual bool IsDialog() const { return true;};
    virtual bool IsModalDialog() const { return true; };
    virtual bool IsMediaWindow() const { return false; };

    void Show_Internal(bool show = true);

  private:
    bool m_bRunning;
  };

} /* namespace ADDON */
} /* extern "C" */
