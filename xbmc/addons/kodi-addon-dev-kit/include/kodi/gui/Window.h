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

#include "../AddonBase.h"
#include "ListItem.h"

extern "C"
{
namespace kodi
{
namespace gui
{

  class CListItem;

  //============================================================================
  ///
  /// \defgroup cpp_kodi_gui_CWindow Window
  /// \ingroup cpp_kodi_gui
  /// @brief \cpp_class{ kodi::gui::CWindow }
  /// **Main window control class**
  ///
  /// The with  \ref Window.h "#include <kodi/gui/Window.h>"
  /// included file brings support to create a window or dialog on Kodi.
  ///
  /// --------------------------------------------------------------------------
  ///
  /// On functions defined input variable <b><tt>controlId</tt> (GUI control identifier)</b>
  /// is the on window.xml defined value behind type added with <tt><b>id="..."</b></tt> and
  /// used to identify for changes there and on callbacks.
  ///
  /// ~~~~~~~~~~~~~{.xml}
  ///  <control type="label" id="31">
  ///    <description>Title Label</description>
  ///    ...
  ///  </control>
  ///  <control type="progress" id="32">
  ///    <description>progress control</description>
  ///    ...
  ///  </control>
  /// ~~~~~~~~~~~~~
  ///
  ///

  //============================================================================
  ///
  /// \defgroup cpp_kodi_gui_CWindow_Defs Definitions, structures and enumerators
  /// \ingroup cpp_kodi_gui_CWindow
  /// @brief <b>Library definition values</b>
  ///

  class CWindow
  {
  public:
    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CWindow
    /// @brief Class constructor with needed values for window / dialog.
    ///
    /// Creates a new Window class.
    ///
    /// @param[in] xmlFilename          XML file for the skin
    /// @param[in] defaultSkin          default skin to use if needed not available
    /// @param[in] forceFallback        If set becomes always default skin used (todo: check correct descr.)
    /// @param[in] asDialog             Use window as dialog if set
    ///
    ///
    CWindow(const std::string& xmlFilename, const std::string& defaultSkin, bool forceFallback, bool asDialog)
    {
      m_WindowHandle = ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->window.New(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, xmlFilename.c_str(),
                            defaultSkin.c_str(), forceFallback, asDialog);
      if (!m_WindowHandle)
        kodi::Log(ADDON_LOG_FATAL, "kodi::gui::CControlButton can't create window class from Kodi !!!");

      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->window.SetCallbacks(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_WindowHandle, this,
                                OnInitCB, OnClickCB, OnFocusCB, OnActionCB);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup CWindow
    /// @brief Class destructor
    ///
    ///
    ///
    virtual ~CWindow()
    {
      if (m_WindowHandle)
        ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->window.Delete(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_WindowHandle);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CWindow
    /// @brief Show this window.
    ///
    /// Shows this window by activating it, calling close() after it wil activate the
    /// current window again.
    ///
    /// @note If your Add-On ends this window will be closed to. To show it forever,
    /// make a loop at the end of your Add-On or use doModal() instead.
    ///
    /// @return                         Return true if call and show is successed,
    ///                                 if false was something failed to get needed
    ///                                 skin parts.
    ///
    bool Show()
    {
      return ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->window.Show(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_WindowHandle);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CWindow
    /// @brief Closes this window.
    ///
    /// Closes this window by activating the old window.
    /// @note The window is not deleted with this method.
    ///
    void Close()
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->window.Close(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_WindowHandle);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CWindow
    /// @brief Display this window until close() is called.
    ///
    void DoModal()
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->window.DoModal(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_WindowHandle);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CWindow
    /// @brief Gives the control with the supplied focus.
    ///
    /// @param[in] iControlId           On skin defined id of control
    /// @return                         Return true if call and focus is successed,
    ///                                 if false was something failed to get needed
    ///                                 skin parts.
    ///
    ///
    bool SetFocusId(int iControlId)
    {
      return ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->window.SetFocusId(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_WindowHandle, iControlId);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CWindow
    /// @brief Returns the id of the control which is focused.
    ///
    /// @return                         Focused control id
    ///
    ///
    int GetFocusId()
    {
      return ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->window.GetFocusId(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_WindowHandle);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CWindow
    /// @brief To set the used label on given control id
    ///
    /// @param[in] controlId            Control id where label need to set
    /// @param[in] label                Label to use
    ///
    ///
    void SetControlLabel(int controlId, const std::string& label)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->window.SetControlLabel(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_WindowHandle, controlId, label.c_str());
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CWindow
    /// @brief Sets a window property, similar to an infolabel.
    ///
    /// @param[in] key                  string - property name.
    /// @param[in] value                string or unicode - value of property.
    ///
    /// @note  Key is NOT case sensitive. Setting value to an empty string is
    ///        equivalent to clearProperty(key).\n
    ///        You can use the above as keywords for arguments and skip certain
    ///        optional arguments.\n
    ///        Once you use a keyword, all following arguments require the keyword.
    ///
    void SetProperty(const std::string& key, const std::string& value)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->window.SetProperty(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_WindowHandle, key.c_str(), value.c_str());
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CWindow
    /// @brief Returns a window property as a string, similar to an infolabel.
    ///
    /// @param[in] key 	                string - property name.
    /// @return                         The property as strin (if present)
    ///
    /// @note  Key is NOT case sensitive. Setting value to an empty string is
    ///        equivalent to clearProperty(key).\n
    ///        You can use the above as keywords for arguments and skip certain
    ///        optional arguments.\n
    ///        Once you use a keyword, all following arguments require the keyword.
    ///
    ///
    std::string GetProperty(const std::string& key) const
    {
      std::string label;
      label.resize(1024);
      unsigned int size = (unsigned int)label.capacity();
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->window.GetProperty(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_WindowHandle, key.c_str(), label[0], size);
      label.resize(size);
      label.shrink_to_fit();
      return label.c_str();
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CWindow
    /// @brief Sets a window property with integer value
    ///
    /// @param[in] key 	                string - property name.
    /// @param[in] value                integer value to set
    ///
    ///
    void SetPropertyInt(const std::string& key, int value)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->window.SetPropertyInt(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_WindowHandle, key.c_str(), value);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CWindow
    /// @brief Returns a window property with integer value
    ///
    /// @param[in] key 	                string - property name.
    /// @return                         integer value of property
    ///
    int GetPropertyInt(const std::string& key) const
    {
      return ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->window.GetPropertyInt(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_WindowHandle, key.c_str());
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CWindow
    /// @brief Sets a window property with boolean value
    ///
    /// @param[in] key 	                string - property name.
    /// @param[in] value                boolean value to set
    ///
    ///
    void SetPropertyBool(const std::string& key, bool value)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->window.SetPropertyBool(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_WindowHandle, key.c_str(), value);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CWindow
    /// @brief Returns a window property with boolean value
    ///
    /// @param[in] key 	                string - property name.
    /// @return                         boolean value of property
    ///
    bool GetPropertyBool(const std::string& key) const
    {
      return ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->window.GetPropertyBool(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_WindowHandle, key.c_str());
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CWindow
    /// @brief Sets a window property with double value
    ///
    /// @param[in] key 	                string - property name.
    /// @param[in] value                double value to set
    ///
    ///
    void SetPropertyDouble(const std::string& key, double value)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->window.SetPropertyDouble(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_WindowHandle, key.c_str(), value);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CWindow
    /// @brief Returns a window property with double value
    ///
    /// @param[in] key 	                string - property name.
    /// @return                         double value of property
    ///
    ///
    double GetPropertyDouble(const std::string& key) const
    {
      return ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->window.GetPropertyDouble(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_WindowHandle, key.c_str());
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CWindow
    /// @brief Remove all present properties from window
    ///
    ///
    ///
    void ClearProperties()
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->window.ClearProperties(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_WindowHandle);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CWindow
    /// @brief Clears the specific window property.
    ///
    /// @param[in] key                string - property name.
    ///
    /// @note Key is NOT case sensitive. Equivalent to SetProperty(key, "")
    ///       You can use the above as keywords for arguments and skip certain
    ///       optional arguments.
    ///       Once you use a keyword, all following arguments require the
    ///       keyword.
    ///
    ///
    ///-----------------------------------------------------------------------
    ///
    /// **Example:**
    /// ~~~~~~~~~~~~~{.cpp}
    /// ..
    /// ClearProperty('Category')
    /// ..
    /// ~~~~~~~~~~~~~
    ///
    void ClearProperty(const std::string& key)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->window.ClearProperty(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_WindowHandle, key.c_str());
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CWindow
    /// @brief Add a string named item to the integrated list.
    ///
    /// @note On delete of "CListItem" is item not removed from list on window.
    ///
    ///
    /// @warning Class need to be deleted after it is not used anymore
    ///
    /// @param[in] name                 Name of the item to add
    /// @param[in] itemPosition         [opt] The position for item, default is on end
    /// @return
    ///
    ///
    CListItem* AddStringItem(const std::string& name, int itemPosition = -1)
    {
      GUIHANDLE handle = ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->window.AddStringItem(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_WindowHandle, name.c_str(), itemPosition);
      if (handle)
        return new CListItem(handle);

      kodi::Log(ADDON_LOG_FATAL, "cGUIWindow Failed to get control on list ṕosition %i !!!", itemPosition);
      return nullptr;
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CWindow
    /// @brief To add a list item in the on window integrated list.
    ///
    /// @param[in] item                 List item to add
    /// @param[in] itemPosition         [opt] The position for item, default is on end
    ///
    ///
    void AddItem(CListItem* item, int itemPosition = -1)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->window.AddItem(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_WindowHandle, item->m_ListItemHandle, itemPosition);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CWindow
    /// @brief Remove list item on position.
    ///
    /// @param[in] itemPosition         List position to remove
    ///
    ///
    void RemoveItem(int itemPosition)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->window.RemoveItem(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_WindowHandle, itemPosition);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CWindow
    /// @brief Remove item with given control class from list.
    ///
    /// @note Related control class is not deleted.
    ///
    /// @param[in] item                 List item control class to remove
    ///
    ///
    void RemoveItem(CListItem* item)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->window.RemoveItemFile(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_WindowHandle, item->m_ListItemHandle);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CWindow
    /// @brief To get list item control class on wanted position.
    ///
    /// @param[in] listPos              Position from where control is needed
    /// @return                         The list item control class or null if not found
    ///
    /// @warning Function returns a new generated **CListItem** class, which
    /// to delete. Every call of this generare a new class!
    ///
    CListItem* GetListItem(int listPos)
    {
      GUIHANDLE handle = ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->window.GetListItem(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_WindowHandle, listPos);
      if (handle)
        return new CListItem(handle);

      kodi::Log(ADDON_LOG_FATAL, "cGUIWindow Failed to get control on list ṕosition %i !!!", listPos);
      return nullptr;
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CWindow
    /// @brief To set position of selected part in list.
    ///
    /// @param[in] listPos              Position to use
    ///
    ///
    void SetCurrentListPosition(int listPos)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->window.SetCurrentListPosition(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_WindowHandle, listPos);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CWindow
    /// @brief To get current selected position in list
    ///
    /// @return                         Current list position
    ///
    ///
    int GetCurrentListPosition()
    {
      return ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->window.GetCurrentListPosition(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_WindowHandle);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CWindow
    /// @brief To get the amount of entries in the list.
    ///
    /// @return                         Size of in window integrated control class
    ///
    ///
    int GetListSize()
    {
      return ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->window.GetListSize(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_WindowHandle);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CWindow
    /// @brief Function delete all entries in integrated list.
    ///
    ///
    ///
    void ClearList()
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->window.ClearList(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_WindowHandle);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CWindow
    /// @brief To inform Kodi that it need to render region new.
    ///
    ///
    ///
    void MarkDirtyRegion()
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->window.MarkDirtyRegion(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_WindowHandle);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    //
    /// @defgroup cpp_kodi_gui_CWindow_callbacks Callback functions from Kodi to add-on
    /// \ingroup cpp_kodi_gui_CWindow
    /// @{
    /// @brief <b>GUI window callback functions.</b>
    ///
    /// Functions to handle control callbacks from Kodi
    ///
    /// ------------------------------------------------------------------------
    ///
    /// @link cpp_kodi_gui_CWindow Go back to normal functions from CWindow@endlink
    //

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CWindow_callbacks
    /// @brief OnInit method.
    ///
    /// @return                         Return true if initialize was done successful
    ///
    ///
    virtual bool OnInit() { return false; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CWindow_callbacks
    /// @brief OnFocus method.
    ///
    /// @param[in] controlId            GUI control identifier
    /// @return                         Return true if focus condition was handled there or false to handle them by Kodi itself
    ///
    ///
    virtual bool OnFocus(int controlId) { return false; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CWindow_callbacks
    /// @brief OnClick method.
    ///
    /// @param[in] controlId            GUI control identifier
    /// @return                         Return true if click was handled there
    ///                                 or false to handle them by Kodi itself
    ///
    ///
    virtual bool OnClick(int controlId) { return false; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CWindow_callbacks
    /// @brief OnAction method.
    ///
    /// @param[in] actionId             The action id to perform, see
    ///                                 \ref kodi_key_action_ids to get list of
    ///                                 them
    /// @return                         Return true if action was handled there
    ///                                 or false to handle them by Kodi itself
    ///
    ///
    /// This method will receive all actions that the main program will send
    /// to this window.
    ///
    /// @note
    /// - By default, only the \c PREVIOUS_MENU and \c NAV_BACK actions are handled.
    /// - Overwrite this method to let your code handle all actions.
    /// - Don't forget to capture \c ADDON_ACTION_PREVIOUS_MENU or \c ADDON_ACTION_NAV_BACK, else the user can't close this window.
    ///
    ///
    ///--------------------------------------------------------------------------
    ///
    /// **Example:**
    /// ~~~~~~~~~~~~~{.cpp}
    /// ..
    /// /* Window used with parent / child way */
    /// bool cYOUR_CLASS::OnAction(int actionId)
    /// {
    ///   switch (action)
    ///   {
    ///     case ADDON_ACTION_PREVIOUS_MENU:
    ///     case ADDON_ACTION_NAV_BACK:
    ///       printf("action recieved: previous");
    ///       Close();
    ///       return true;
    ///     case ADDON_ACTION_SHOW_INFO:
    ///       printf("action recieved: show info");
    ///       break;
    ///     case ADDON_ACTION_STOP:
    ///       printf("action recieved: stop");
    ///       break;
    ///     case ADDON_ACTION_PAUSE:
    ///       printf("action recieved: pause");
    ///       break;
    ///     default:
    ///       break;
    ///   }
    ///   return false;
    /// }
    /// ..
    /// ~~~~~~~~~~~~~
    ///
    virtual bool OnAction(int actionId) { return false; }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CWindow_callbacks
    /// @brief **Set independent callbacks**
    ///
    /// If the class is used independent (with "new CWindow") and
    /// not as parent (with "cCLASS_own : CWindow") from own must be the
    /// callback from Kodi to add-on overdriven with own functions!
    ///
    /// @param[in] cbhdl                The pointer to own handle data
    ///                                 structure / class
    /// @param[in] CBOnInit             Own defined window init function
    /// @param[in] CBOnFocus            Own defined focus function
    /// @param[in] CBOnClick            Own defined click function
    /// @param[in] CBOnAction           Own defined action function
    ///
    ///
    ///--------------------------------------------------------------------------
    ///
    /// **Example:**
    /// ~~~~~~~~~~~~~{.cpp}
    /// ...
    ///
    /// bool OnInit(GUIHANDLE cbhdl)
    /// {
    ///   ...
    ///   return true;
    /// }
    ///
    /// bool OnFocus(GUIHANDLE cbhdl)
    /// {
    ///   ...
    ///   return true;
    /// }
    ///
    /// bool OnClick(GUIHANDLE cbhdl)
    /// {
    ///   ...
    ///   return true;
    /// }
    ///
    /// bool OnAction(GUIHANDLE cbhdl)
    /// {
    ///   ...
    ///   return true;
    /// }
    ///
    /// ...
    /// /* Somewhere where you create the window */
    /// CWindow myWindow = new CWindow;
    /// myWindow->SetIndependentCallbacks(myWindow, OnInit, OnFocus, OnClick, OnAction);
    /// ...
    /// ~~~~~~~~~~~~~
    ///
    void SetIndependentCallbacks(
      GUIHANDLE             cbhdl,
      bool    (*CBOnInit)  (GUIHANDLE cbhdl),
      bool    (*CBOnFocus) (GUIHANDLE cbhdl, int controlId),
      bool    (*CBOnClick) (GUIHANDLE cbhdl, int controlId),
      bool    (*CBOnAction)(GUIHANDLE cbhdl, int actionId)
    )
    {
      if (!cbhdl ||
          !CBOnInit || !CBOnFocus || !CBOnClick || !CBOnAction)
      {
          fprintf(stderr, "libKODI_gui-ERROR: SetIndependentCallbacks called with nullptr !!!\n");
          return;
      }

      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->window.SetCallbacks(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_WindowHandle, cbhdl,
                                CBOnInit, CBOnFocus, CBOnClick, CBOnAction);
    }
    //--------------------------------------------------------------------------
    /// @}

    protected:
      void* m_WindowHandle;

    private:
      static bool OnInitCB(void* cbhdl)
      {
        return static_cast<CWindow*>(cbhdl)->OnInit();
      }

      static bool OnClickCB(void* cbhdl, int controlId)
      {
        return static_cast<CWindow*>(cbhdl)->OnClick(controlId);
      }

      static bool OnFocusCB(void* cbhdl, int controlId)
      {
        return static_cast<CWindow*>(cbhdl)->OnFocus(controlId);
      }

      static bool OnActionCB(void* cbhdl, int actionId)
      {
        return static_cast<CWindow*>(cbhdl)->OnAction(actionId);
      }

      friend class CControlButton;
      friend class CControlEdit;
      friend class CControlImage;
      friend class CControlFadeLabel;
      friend class CControlLabel;
      friend class CControlSpin;
      friend class CControlProgress;
      friend class CControlRadioButton;
      friend class CControlRendering;
      friend class CControlSlider;
      friend class CControlSettingsSlider;
      friend class CControlTextBox;
  };

} /* namespace gui */
} /* namespace kodi */
} /* extern "C" */
