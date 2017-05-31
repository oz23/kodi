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
  /// \defgroup cpp_kodi_gui_CControlButton Control Button
  /// \ingroup cpp_kodi_gui
  /// @brief \cpp_class{ kodi::gui::CControlButton }
  /// **Standard push button control for window**
  ///
  /// The  button  control  is used for creating push buttons  in Kodi.  You can
  /// choose the position,  size,  and look of the button,  as well as  choosing
  /// what action(s) should be performed when pushed.
  ///
  /// It has the header \ref ControlButton.h "#include <kodi/gui/ControlButton.h>"
  /// be included to enjoy it.
  ///
  /// Here you find the needed skin part for a \ref skin_Button_control "button control"
  ///
  /// @note The call of the control is  only  possible  from  the  corresponding
  /// window as its class and identification number is required.
  ///
  class CControlButton
  {
  public:
    //==========================================================================
    ///
    /// @ingroup cpp_kodi_gui_CControlButton
    /// @brief Construct a new control
    ///
    /// @param[in] window               related window control class
    /// @param[in] controlId            Used skin xml control id
    ///
    CControlButton(CWindow* window, int controlId)
      : m_Window(window),
        m_ControlId(controlId)
    {
      m_ControlHandle = ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->window.GetControl_Button(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_Window->m_WindowHandle, controlId);
      if (!m_ControlHandle)
        kodi::Log(ADDON_LOG_FATAL, "kodi::gui::CControlButton can't create control class from Kodi !!!");
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_gui_CControlButton
    /// @brief Destructor
    ///
    virtual ~CControlButton()
    {
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_gui_CControlButton
    /// @brief Set the control on window to visible
    ///
    /// @param[in] visible              If true visible, otherwise hidden
    ///
    void SetVisible(bool visible)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->controlButton.SetVisible(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ControlHandle, visible);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_gui_CControlButton
    /// @brief Set's the control's enabled/disabled state
    ///
    /// @param[in] enabled              If true enabled, otherwise disabled
    ///
    void SetEnabled(bool enabled)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->controlButton.SetEnabled(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ControlHandle, enabled);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_gui_CControlButton
    /// @brief To set the text string on button
    ///
    /// @param[in] text                 Text to show
    ///
    void SetLabel(const std::string& text)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->controlButton.SetLabel(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ControlHandle, text.c_str());
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_gui_CControlButton
    /// @brief Get the used text from button
    ///
    /// @return                         Text shown
    ///
    std::string GetLabel() const
    {
      std::string text;
      text.resize(1024);
      unsigned int size = (unsigned int)text.capacity();
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->controlButton.GetLabel(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ControlHandle, text[0], size);
      text.resize(size);
      text.shrink_to_fit();
      return text;
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_gui_CControlButton
    /// @brief If two labels are used for button becomes it set with them
    ///
    /// @param[in] text                 Text for second label
    ///
    void SetLabel2(const std::string& text)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->controlButton.SetLabel2(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ControlHandle, text.c_str());
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// @ingroup cpp_kodi_gui_CControlButton
    /// @brief Get the second label if present
    ///
    /// @return                         Second label
    ///
    std::string GetLabel2() const
    {
      std::string text;
      text.resize(1024);
      unsigned int size = (unsigned int)text.capacity();
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->controlButton.GetLabel2(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ControlHandle, text[0], size);
      text.resize(size);
      text.shrink_to_fit();
      return text;
    }
    //--------------------------------------------------------------------------

  private:
    CWindow* m_Window;
    int m_ControlId;
    void* m_ControlHandle;
  };

} /* namespace gui */
} /* namespace kodi */
