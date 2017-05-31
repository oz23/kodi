#pragma once
/*
 *      Copyright (C) 2005-2017 Team KODI
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
#include "Window.h"

namespace kodi
{
namespace gui
{

  //============================================================================
  ///
  /// \defgroup cpp_kodi_gui_CControlEdit Control Edit
  /// \ingroup cpp_kodi_gui
  /// @brief \cpp_class{ kodi::gui::CControlEdit }
  /// **Editable window text control used as an input control for the osd keyboard
  /// and other input fields**
  ///
  /// The edit control  allows a user to  input text in Kodi. You can choose the
  /// font, size, colour, location and header of the text to be displayed.
  ///
  /// It has the header \ref ControlEdit.h "#include <kodi/gui/ControlEdit.h>"
  /// be included to enjoy it.
  ///
  /// Here  you  find  the   needed  skin  part  for  a   \ref skin_Edit_control
  /// "edit control".
  ///
  /// @note The  call of the  control is only possible  from  the  corresponding
  /// window as its class and identification number is required.
  ///

  //============================================================================
  // see gui/definition.h for use of group "cpp_kodi_gui_CControlEdit_Defs"
  ///
  /// \defgroup cpp_kodi_gui_CControlEdit_Defs Definitions, structures and enumerators
  /// \ingroup cpp_kodi_gui_CControlEdit
  /// @brief **Library definition values**
  ///

  class CControlEdit
  {
  public:
    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlEdit
    /// @brief Construct a new control
    ///
    /// @param[in] window               related window control class
    /// @param[in] controlId            Used skin xml control id
    ///
    CControlEdit(CWindow* window, int controlId)
      : m_Window(window),
        m_ControlId(controlId)
    {
      m_ControlHandle = ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->window.GetControl_Edit(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_Window->m_WindowHandle, controlId);
      if (!m_ControlHandle)
        kodi::Log(ADDON_LOG_FATAL, "kodi::gui::CControlEdit can't create control class from Kodi !!!");
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlEdit
    /// @brief Destructor
    ///
    virtual ~CControlEdit()
    {
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlEdit
    /// @brief Set the control on window to visible
    ///
    /// @param[in] visible              If true visible, otherwise hidden
    ///
    void SetVisible(bool visible)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->controlEdit.SetVisible(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ControlHandle, visible);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlEdit
    /// @brief Set's the control's enabled/disabled state
    ///
    /// @param[in] enabled              If true enabled, otherwise disabled
    ///
    void SetEnabled(bool enabled)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->controlEdit.SetEnabled(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ControlHandle, enabled);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlEdit
    /// @brief To set the text string on edit control
    ///
    /// @param[in] label                Text to show
    ///
    void SetLabel(const std::string& label)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->controlEdit.SetLabel(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ControlHandle, label.c_str());
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlEdit
    /// @brief Returns the text heading for this edit control.
    ///
    /// @return                         Heading text
    ///
    std::string GetLabel() const
    {
      std::string text;
      text.resize(1024);
      unsigned int size = (unsigned int)text.capacity();
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->controlEdit.GetLabel(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ControlHandle, text[0], size);
      text.resize(size);
      text.shrink_to_fit();
      return text;
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlEdit
    /// @brief Set's text heading for this edit control.
    ///
    /// @param[in] text                 string or unicode - text string.
    ///
    void SetText(const std::string& text)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->controlEdit.SetText(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ControlHandle, text.c_str());
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlEdit
    /// @brief Returns the text value for this edit control.
    ///
    /// @return                         Text value of control
    ///
    std::string GetText() const
    {
      std::string text;
      text.resize(1024);
      unsigned int size = (unsigned int)text.capacity();
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->controlEdit.GetText(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ControlHandle, text[0], size);
      text.resize(size);
      text.shrink_to_fit();
      return text;
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlEdit
    /// @brief Set the cursor position on text.
    ///
    /// @param[in] iPosition            The position to set
    ///
    void SetCursorPosition(unsigned int iPosition)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->controlEdit.SetCursorPosition(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ControlHandle, iPosition);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlEdit
    /// @brief To get current cursor position on text field
    ///
    /// @return                         The current cursor position
    ///
    unsigned int GetCursorPosition()
    {
      return ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->controlEdit.GetCursorPosition(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ControlHandle);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlEdit
    /// @brief To set field input type which are defined on \ref AddonGUIInputType
    ///
    /// @param[in] type                 The   \ref AddonGUIInputType "Add-on input type"
    ///                                 to use
    /// @param[in] heading              The heading  text for  related  keyboard
    ///                                 dialog
    ///
    void SetInputType(AddonGUIInputType type, const std::string& heading)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->controlEdit.SetInputType(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ControlHandle, type, heading.c_str());
    }
    //--------------------------------------------------------------------------

  private:
    CWindow* m_Window;
    int m_ControlId;
    void* m_ControlHandle;
  };

} /* namespace gui */
} /* namespace kodi */
