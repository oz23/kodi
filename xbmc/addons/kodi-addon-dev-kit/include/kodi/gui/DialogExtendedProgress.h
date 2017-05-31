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

#include "definitions.h"
#include "../AddonBase.h"

namespace kodi
{
namespace gui
{

  //============================================================================
  ///
  /// \defgroup cpp_kodi_gui_CDialogExtendedProgress Dialog Extended Progress
  /// \ingroup cpp_kodi_gui
  /// @brief \cpp_class{ kodi::gui::CDialogExtendedProgress }
  /// **Progress dialog shown for background work**
  ///
  /// The with \ref DialogExtendedProgress.h "#include <kodi/gui/DialogExtendedProgress.h>"
  /// given class are basically used to create Kodi's extended progress.
  ///
  ///
  /// --------------------------------------------------------------------------
  ///
  /// **Example:**
  /// ~~~~~~~~~~~~~{.cpp}
  /// #include <kodi/gui/DialogExtendedProgress.h>
  ///
  /// kodi::gui::CDialogExtendedProgress *ext_progress = new kodi::gui::CDialogExtendedProgress("Test Extended progress");
  /// ext_progress->SetText("Test progress");
  /// for (unsigned int i = 0; i < 50; i += 10)
  /// {
  ///   ext_progress->SetProgress(i, 100);
  ///   sleep(1);
  /// }
  ///
  /// ext_progress->SetTitle("Test Extended progress - Second round");
  /// ext_progress->SetText("Test progress - Step 2");
  ///
  /// for (unsigned int i = 50; i < 100; i += 10)
  /// {
  ///   ext_progress->SetProgress(i, 100);
  ///   sleep(1);
  /// }
  /// delete ext_progress;
  /// ~~~~~~~~~~~~~
  ///
  class CDialogExtendedProgress
  {
  public:
    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CDialogExtendedProgress
    /// Construct a new dialog
    ///
    /// @param[in] title  Title string
    ///
    CDialogExtendedProgress(const std::string& title = "")
    {
      m_DialogHandle = ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->dialogExtendedProgress.New(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, title.c_str());
      if (!m_DialogHandle)
        kodi::Log(ADDON_LOG_FATAL, "kodi::gui::CDialogExtendedProgress can't create window class from Kodi !!!");
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CDialogExtendedProgress
    /// Destructor
    ///
    ~CDialogExtendedProgress()
    {
      if (m_DialogHandle)
        ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->dialogExtendedProgress.Delete(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_DialogHandle);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CDialogExtendedProgress
    /// @brief Get the used title
    ///
    /// @return Title string
    ///
    std::string Title() const
    {
      std::string text;
      text.resize(1024);
      unsigned int size = (unsigned int)text.capacity();
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->dialogExtendedProgress.Title(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_DialogHandle, text[0], size);
      text.resize(size);
      text.shrink_to_fit();
      return text;
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CDialogExtendedProgress
    /// @brief To set the title of dialog
    ///
    /// @param[in] title     Title string
    ///
    void SetTitle(const std::string& title)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->dialogExtendedProgress.SetTitle(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_DialogHandle, title.c_str());
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CDialogExtendedProgress
    /// @brief Get the used text information string
    ///
    /// @return Text string
    ///
    std::string Text() const
    {
      std::string text;
      text.resize(1024);
      unsigned int size = (unsigned int)text.capacity();
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->dialogExtendedProgress.Text(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_DialogHandle, text[0], size);
      text.resize(size);
      text.shrink_to_fit();
      return text;
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CDialogExtendedProgress
    /// @brief To set the used text information string
    ///
    /// @param[in] text         information text to set
    ///
    void SetText(const std::string& text)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->dialogExtendedProgress.SetText(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_DialogHandle, text.c_str());
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CDialogExtendedProgress
    /// @brief To ask dialog is finished
    ///
    /// @return True if on end
    ///
    bool IsFinished() const
    {
      return ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->dialogExtendedProgress.IsFinished(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_DialogHandle);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CDialogExtendedProgress
    /// @brief Mark progress finished
    ///
    void MarkFinished()
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->dialogExtendedProgress.MarkFinished(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_DialogHandle);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CDialogExtendedProgress
    /// @brief Get the current progress position as percent
    ///
    /// @return Position
    ///
    float Percentage() const
    {
      return ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->dialogExtendedProgress.Percentage(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_DialogHandle);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CDialogExtendedProgress
    /// @brief To set the current progress position as percent
    ///
    /// @param[in] percentage   Position to use from 0.0 to 100.0
    ///
    void SetPercentage(float percentage)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->dialogExtendedProgress.SetPercentage(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_DialogHandle, percentage);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CDialogExtendedProgress
    /// @brief To set progress position with predefined places
    ///
    /// @param[in] currentItem    Place position to use
    /// @param[in] itemCount      Amount of used places
    ///
    void SetProgress(int currentItem, int itemCount)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->dialogExtendedProgress.SetProgress(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_DialogHandle, currentItem, itemCount);
    }
    //--------------------------------------------------------------------------

  private:
    void* m_DialogHandle;
  };

} /* namespace gui */
} /* namespace kodi */
