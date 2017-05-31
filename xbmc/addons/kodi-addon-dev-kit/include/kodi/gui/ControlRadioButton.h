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
  /// \defgroup cpp_kodi_gui_CControlRadioButton Control Radio Button
  /// \ingroup cpp_kodi_gui
  /// @brief \cpp_class{ kodi::gui::CControlRadioButton }
  /// **Window control for a radio button (as used for on/off settings)**
  ///
  /// The radio  button control is used for creating push button on/off settings
  /// in Kodi. You can choose the position,  size,  and look of the button. When
  /// the user clicks on the radio button,  the state will change,  toggling the
  /// extra  textures  (textureradioon and textureradiooff).  Used  for settings
  /// controls.
  ///
  /// It has the header \ref ControlRadioButton.h "#include <kodi/gui/ControlRadioButton.h>"
  /// be included to enjoy it.
  ///
  /// Here you find the needed skin part for a \ref Radio_button_control "radio button control"
  ///
  /// @note The  call  of the  control is  only possible  from the corresponding
  /// window as its class and identification number is required.
  ///
  class CControlRadioButton
  {
  public:
    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlRadioButton
    /// @brief Construct a new control
    ///
    /// @param[in] window     related window control class
    /// @param[in] controlId  Used skin xml control id
    ///
    CControlRadioButton(CWindow* window, int controlId)
    {
      m_ControlHandle = ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->window.GetControl_RadioButton(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_Window->m_WindowHandle, controlId);
      if (!m_ControlHandle)
        kodi::Log(ADDON_LOG_FATAL, "kodi::gui::CControlRadioButton can't create control class from Kodi !!!");
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup CControlRadioButton
    /// @brief Destructor
    ///
    virtual ~CControlRadioButton() { }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlRadioButton
    /// @brief Set the control on window to visible
    ///
    /// @param[in] visible    If true visible, otherwise hidden
    ///
    void SetVisible(bool visible)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->controlRadioButton.SetVisible(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ControlHandle, visible);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlRadioButton
    /// @brief Set's the control's enabled/disabled state
    ///
    /// @param[in] enabled    If true enabled, otherwise disabled
    ///
    void SetEnabled(bool enabled)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->controlRadioButton.SetEnabled(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ControlHandle, enabled);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlRadioButton
    /// @brief To set the text string on radio button
    ///
    /// @param[in] label      Text to show
    ///
    void SetLabel(const std::string& label)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->controlRadioButton.SetLabel(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ControlHandle, label.c_str());
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlRadioButton
    /// @brief Get the used text from control
    ///
    /// @return               Text shown
    ///
    std::string GetLabel() const
    {
      std::string text;
      text.resize(1024);
      unsigned int size = (unsigned int)text.capacity();
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->controlRadioButton.GetLabel(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ControlHandle, text[0], size);
      text.resize(size);
      text.shrink_to_fit();
      return text;
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlRadioButton
    /// @brief To set radio button condition to on or off
    ///
    /// @param[in] selected   true set radio button to  selection on,  otherwise
    ///                       off
    ///
    void SetSelected(bool selected)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->controlRadioButton.SetSelected(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ControlHandle, selected);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlRadioButton
    /// @brief Get the current selected condition of radio button
    ///
    /// @return               Selected condition
    ///
    bool IsSelected() const
    {
      return ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->controlRadioButton.IsSelected(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ControlHandle);
    }
    //--------------------------------------------------------------------------

  private:
    CWindow* m_Window;
    int m_ControlId;
    void* m_ControlHandle;
  };

} /* namespace gui */
} /* namespace kodi */
