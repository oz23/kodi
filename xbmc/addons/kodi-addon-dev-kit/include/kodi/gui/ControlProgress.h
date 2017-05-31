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
  /// \defgroup cpp_kodi_gui_CControlProgress Control Progress
  /// \ingroup cpp_kodi_gui
  /// @brief \cpp_class{ kodi::gui::CControlProgress }
  /// **Window control to show the progress of a particular operation**
  ///
  /// The progress control is used to show the progress of an item that may take
  /// a long time,  or to show how far  through a movie you are.  You can choose
  /// the position, size, and look of the progress control.
  ///
  /// It has the header \ref ControlProgress.h "#include <kodi/gui/ControlProgress.h>"
  /// be included to enjoy it.
  ///
  /// Here you find the needed skin part for a \ref Progress_Control "progress control"
  ///
  /// @note The call of the control is only possible from the corresponding
  /// window as its class and identification number is required.
  ///
  class CControlProgress
  {
  public:
    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlProgress
    /// @brief Construct a new control
    ///
    /// @param[in] window               related window control class
    /// @param[in] controlId            Used skin xml control id
    ///
    CControlProgress(CWindow* window, int controlId)
   : m_Window(window),
     m_ControlId(controlId)
  {
    m_ControlHandle = ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->window.GetControl_Progress(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_Window->m_WindowHandle, controlId);
    if (!m_ControlHandle)
      kodi::Log(ADDON_LOG_FATAL, "kodi::gui::CControlProgress can't create control class from Kodi !!!");
  }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlProgress
    /// @brief Destructor
    ///
    virtual ~CControlProgress() { }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlProgress
    /// @brief Set the control on window to visible
    ///
    /// @param[in] visible              If true visible, otherwise hidden
    ///
    void SetVisible(bool visible)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->controlProgress.SetVisible(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ControlHandle, visible);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlProgress
    /// @brief To set Percent position of control
    ///
    /// @param[in] percent              The percent position to use
    ///
    void SetPercentage(float percent)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->controlProgress.SetPercentage(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ControlHandle, percent);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlProgress
    /// @brief Get the active percent position of progress bar
    ///
    /// @return                         Progress position as percent
    ///
    float GetPercentage() const
    {
      return ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->controlProgress.GetPercentage(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ControlHandle);
    }
    //--------------------------------------------------------------------------

  private:
    CWindow* m_Window;
    int m_ControlId;
    void* m_ControlHandle;
  };

} /* namespace gui */
} /* namespace kodi */
