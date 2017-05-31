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
  /// \defgroup cpp_kodi_gui_CControlFadeLabel Control Fade Label
  /// \ingroup cpp_kodi_gui
  /// @brief \cpp_class{ kodi::gui::CControlFadeLabel }
  /// **Window control used to show multiple pieces of text in the same position,
  /// by fading from one to the other**
  ///
  /// The fade label  control is used for displaying multiple pieces  of text in
  /// the same  space in  Kodi. You can choose  the font, size, colour, location
  /// and contents  of the text to be displayed.  The first piece of information
  /// to display fades in over 50 frames, then scrolls off to the left.  Once it
  /// is  finished scrolling off screen,  the second piece  of information fades
  /// in and  the process repeats.  A fade label  control is not  supported in a
  /// list container.
  ///
  /// It has the header \ref ControlFadeLabel.h "#include <kodi/gui/ControlFadeLabel.h>"
  /// be included to enjoy it.
  ///
  /// Here you find the needed skin part for a \ref Fade_Label_Control "fade label control"
  ///
  /// @note The  call of the  control is only  possible from  the  corresponding
  /// window as its class and identification number is required.
  ///
  class CControlFadeLabel
  {
  public:
    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlFadeLabel
    /// @brief Construct a new control.
    ///
    /// @param[in] window     related window control class
    /// @param[in] controlId  Used skin xml control id
    ///
    CControlFadeLabel(CWindow* window, int controlId)
      : m_Window(window),
        m_ControlId(controlId)
    {
      m_ControlHandle = ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->window.GetControl_FadeLabel(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_Window->m_WindowHandle, controlId);
      if (!m_ControlHandle)
        kodi::Log(ADDON_LOG_FATAL, "kodi::gui::CControlFadeLabel can't create control class from Kodi !!!");
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlFadeLabel
    /// @brief Destructor.
    ///
    virtual ~CControlFadeLabel() { }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlFadeLabel
    /// @brief Set the control on window to visible.
    ///
    /// @param[in] visible    If true visible, otherwise hidden
    ///
    void SetVisible(bool visible)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->controlFadeLabel.SetVisible(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ControlHandle, visible);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlFadeLabel
    /// @brief To add additional text string on fade label.
    ///
    /// @param[in] label      Text to show
    ///
    void AddLabel(const std::string& label)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->controlFadeLabel.AddLabel(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ControlHandle, label.c_str());
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlFadeLabel
    /// @brief Get the used text from button
    ///
    /// @return               Text shown
    ///
    std::string GetLabel() const
    {
      std::string text;
      text.resize(1024);
      unsigned int size = (unsigned int)text.capacity();
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->controlFadeLabel.GetLabel(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ControlHandle, text[0], size);
      text.resize(size);
      text.shrink_to_fit();
      return text;
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlFadeLabel
    /// @brief To enable or disable scrolling on fade label
    ///
    /// @param[in] scroll     To  enable scrolling  set  to true,  otherwise  is
    ///                       disabled
    ///
    void SetScrolling(bool scroll)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->controlFadeLabel.SetScrolling(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ControlHandle, scroll);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlFadeLabel
    /// @brief To reset al inserted labels.
    ///
    void Reset()
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->controlFadeLabel.Reset(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ControlHandle);
    }
    //--------------------------------------------------------------------------

  private:
    CWindow* m_Window;
    int m_ControlId;
    void* m_ControlHandle;
  };

} /* namespace gui */
} /* namespace kodi */
