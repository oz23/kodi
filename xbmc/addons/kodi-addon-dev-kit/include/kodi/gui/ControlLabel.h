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
  /// \defgroup cpp_kodi_gui_CControlLabel Control Label
  /// \ingroup cpp_kodi_gui
  /// @brief \cpp_class{ kodi::gui::CControlLabel }
  /// **Window control used to show some lines of text.**
  ///
  /// The  label control  is used for  displaying text  in Kodi.  You can choose
  /// the font, size, colour, location and contents of the text to be displayed.
  ///
  /// It has the header \ref ControlLabel.h "#include <kodi/gui/ControlLabel.h>"
  /// be included to enjoy it.
  ///
  /// Here you find the needed skin part for a \ref Label_Control "label control"
  ///
  /// @note The  call  of the control  is only possible  from the  corresponding
  /// window as its class and identification number is required.
  ///
  class CControlLabel
  {
  public:
    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlLabel
    /// @brief Construct a new control
    ///
    /// @param[in] window               related window control class
    /// @param[in] controlId            Used skin xml control id
    ///
    CControlLabel(CWindow* window, int controlId)
      : m_Window(window),
        m_ControlId(controlId)
    {
      m_ControlHandle = ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->window.GetControl_Label(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_Window->m_WindowHandle, controlId);
      if (!m_ControlHandle)
        kodi::Log(ADDON_LOG_FATAL, "kodi::gui::CControlLabel can't create control class from Kodi !!!");
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlLabel
    /// @brief Destructor
    ///
    virtual ~CControlLabel() { }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlLabel
    /// @brief Set the control on window to visible
    ///
    /// @param[in] visible              If true visible, otherwise hidden
    ///
    void SetVisible(bool visible)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->controlLabel.SetVisible(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ControlHandle, visible);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlLabel
    /// @brief To set the text string on label
    ///
    /// @param[in] text                 Text to show
    ///
    void SetLabel(const std::string& text)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->controlLabel.SetLabel(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ControlHandle, text.c_str());
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlLabel
    /// @brief Get the used text from control
    ///
    /// @return                         Used text on label control
    ///
    std::string GetLabel() const
    {
      std::string text;
      text.resize(1024);
      unsigned int size = (unsigned int)text.capacity();
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->controlLabel.GetLabel(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ControlHandle, text[0], size);
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
