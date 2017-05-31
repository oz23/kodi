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
  /// \defgroup cpp_kodi_gui_CControlImage Control Image
  /// \ingroup cpp_kodi_gui
  /// @brief \cpp_class{ kodi::gui::CControlImage }
  /// **Window control used to show an image.**
  ///
  /// The  image control is used  for displaying  images in Kodi. You can choose
  /// the position, size, transparency and contents of the image to be displayed.
  ///
  /// It has the header \ref ControlImage.h "#include <kodi/gui/ControlImage.h>"
  /// be included to enjoy it.
  ///
  /// Here you find the needed skin part for a \ref Image_Control "image control"
  ///
  /// @note The  call of  the control is  only possible  from the  corresponding
  /// window as its class and identification number is required.
  ///
  class CControlImage
  {
  public:
    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlImage
    /// @brief Construct a new control
    ///
    /// @param[in] window               related window control class
    /// @param[in] controlId            Used skin xml control id
    ///
    CControlImage(CWindow* window, int controlId)
    {
      m_ControlHandle = ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->window.GetControl_Image(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_Window->m_WindowHandle, controlId);
      if (!m_ControlHandle)
        kodi::Log(ADDON_LOG_FATAL, "kodi::gui::CControlImage can't create control class from Kodi !!!");
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlImage
    /// @brief Destructor
    ///
    virtual ~CControlImage() { }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlImage
    /// @brief Set the control on window to visible
    ///
    /// @param[in] visible              If true visible, otherwise hidden
    ///
    void SetVisible(bool visible)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->controlImage.SetVisible(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ControlHandle, visible);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlImage
    /// @brief To set the filename used on image control.
    ///
    /// @param[in] strFileName          Image file to use
    /// @param[in] useCache             To define  storage of image,  default is
    ///                                 in  cache,  if false  becomes it  loaded
    ///                                 always on changes again
    ///
    void SetFileName(const std::string& strFileName, const bool useCache = true)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->controlImage.SetFileName(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ControlHandle, strFileName.c_str(), useCache);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlImage
    /// @brief To set set the diffuse color on image.
    ///
    /// @param[in] colorDiffuse         Color to use for diffuse
    ///
    void SetColorDiffuse(uint32_t colorDiffuse)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->controlImage.SetColorDiffuse(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ControlHandle, colorDiffuse);
    }
    //--------------------------------------------------------------------------

  private:
    CWindow* m_Window;
    int m_ControlId;
    void* m_ControlHandle;
  };

} /* namespace gui */
} /* namespace kodi */
