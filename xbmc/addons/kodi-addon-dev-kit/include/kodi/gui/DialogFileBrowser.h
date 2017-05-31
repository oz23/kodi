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
  /// \defgroup cpp_kodi_gui_DialogFileBrowser Dialog File Browser
  /// \ingroup cpp_kodi_gui
  /// @brief \cpp_namespace{ kodi::gui::DialogFileBrowser }
  /// **File browser dialog**
  ///
  /// The functions listed below of the class "DialogFileBrowser" offer
  /// the possibility to select to a file by the user of the add-on.
  ///
  /// It allows all the options that are possible in Kodi itself and offers all
  /// support file types.
  ///
  /// These are pure static functions them no other initialization need.
  ///
  /// It has the header \ref DialogFileBrowser.h "#include <kodi/gui/DialogFileBrowser.h>"
  /// be included to enjoy it.
  ///
  namespace DialogFileBrowser
  {
    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_DialogFileBrowser
    /// @brief Directory selection dialog
    ///
    /// @param[in] shares       With Shares becomes the available start folders
    ///                         be set.
    /// @param[in] heading      Dialog header name
    /// @param[out] path        Return value about selected directory
    /// @param[in] writeOnly    If set only writeable folders are shown.
    /// @return                 False if selection becomes canceled.
    ///
    /// **Example:**
    /// ~~~~~~~~~~~~~{.cpp}
    /// #include <kodi/gui/DialogFileBrowser.h>
    ///
    /// /*
    ///  * Example show directory selection dialog with on 'share' (first value)
    ///  * defined directory types.
    ///  *
    ///  * If this becomes leaved empty and 'directory' is empty goes it to the
    ///  * base path of the hard disk.
    ///  *
    ///  * Also can be with path written to 'directory' before the dialog forced
    ///  * to a start place.
    ///  */
    /// std::string directory;
    /// bool ret = kodi::gui::DialogFileBrowser::ShowAndGetDirectory("local|network|removable",
    ///                                                    "Test directory selection",
    ///                                                    directory,
    ///                                                    false);
    /// fprintf(stderr, "Selected directory is : %s and was %s\n", directory.c_str(), ret ? "OK" : "Canceled");
    /// ~~~~~~~~~~~~~
    ///
    inline bool ShowAndGetDirectory(
      const std::string&      shares,
      const std::string&      heading,
      std::string&            path,
      bool                    writeOnly = false)
    {
      path.resize(1024);
      unsigned int size = (unsigned int)path.capacity();
      bool ret = ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->dialogFileBrowser.ShowAndGetDirectory(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, shares.c_str(), heading.c_str(), path[0], size, writeOnly);
      path.resize(size);
      path.shrink_to_fit();
      return ret;
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_DialogFileBrowser
    /// @brief File selection dialog
    ///
    /// @param[in] shares               With Shares becomes the available  start
    ///                                 folders be set.
    /// @param[in] mask                 The mask to filter visible  files,  e.g.
    ///                                 ".m3u|.pls|.b4s|.wpl".
    /// @param[in] heading              Dialog header name
    /// @param[out] file                Return value about selected file
    /// @param[in] useThumbs            If set show thumbs if possible on dialog.
    /// @param[in] useFileDirectories   If set also  packages  (e.g. *.zip)  are
    ///                                 handled as directories.
    /// @return                         False if selection becomes canceled.
    ///
    inline bool ShowAndGetFile(
      const std::string&      shares,
      const std::string&      mask,
      const std::string&      heading,
      std::string&            file,
      bool                    useThumbs = false,
      bool                    useFileDirectories = false)
    {
      file.resize(1024);
      unsigned int size = (unsigned int)file.capacity();;
      bool ret = ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->dialogFileBrowser.ShowAndGetFile(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, shares.c_str(), mask.c_str(), heading.c_str(), file[0], size, useThumbs, useFileDirectories);
      file.resize(size);
      file.shrink_to_fit();
      return ret;
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_DialogFileBrowser
    /// @brief File selection from a directory
    ///
    /// @param[in] directory            The  directory  name  where  the  dialog
    ///                                 start, possible  are  normal  names  and
    ///                                 kodi's special names.
    /// @param[in] mask                 The mask to filter visible  files,  e.g.
    ///                                 ".m3u|.pls|.b4s|.wpl".
    /// @param[in] heading              Dialog header name
    /// @param[out] path                Return value about selected file
    /// @param[in] useThumbs            If set show thumbs if possible on dialog.
    /// @param[in] useFileDirectories   If set also  packages  (e.g. *.zip)  are
    ///                                 handled as directories.
    /// @param[in] singleList
    /// @return                         False if selection becomes canceled.
    ///
    inline bool ShowAndGetFileFromDir(
      const std::string&      directory,
      const std::string&      mask,
      const std::string&      heading,
      std::string&            path,
      bool                    useThumbs = false,
      bool                    useFileDirectories = false,
      bool                    singleList = false)
    {
      path.resize(1024);
      unsigned int size = (unsigned int)path.capacity();
      bool ret = ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->dialogFileBrowser.ShowAndGetFileFromDir(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, directory.c_str(), mask.c_str(), heading.c_str(), path[0], size, useThumbs, useFileDirectories, singleList);
      path.resize(size);
      path.shrink_to_fit();
      return ret;
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_DialogFileBrowser
    /// @brief File selection dialog to get several in to a list
    ///
    /// @param[out] shares            With Shares becomes  the  available  start
    ///                               folders be set.
    /// @param[in] mask               The mask to  filter  visible  files,  e.g.
    ///                               ".m3u|.pls|.b4s|.wpl".
    /// @param[in] heading            Dialog header name
    /// @param[out] path              Return value about selected files
    /// @param[in] useThumbs          If set show thumbs if possible on dialog.
    /// @param[in] useFileDirectories If  set  also  packages  (e.g. *.zip)  are
    ///                               handled as directories.
    /// @return False if selection becomes canceled.
    ///
    inline bool ShowAndGetFileList(
      const std::string&      shares,
      const std::string&      mask,
      const std::string&      heading,
      std::vector<std::string> &path,
      bool                    useThumbs = false,
      bool                    useFileDirectories = false)
    {
      char** list;
      unsigned int listSize = 0;
      bool ret = ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->dialogFileBrowser.ShowAndGetFileList(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, shares.c_str(), mask.c_str(), heading.c_str(), list, listSize, useThumbs, useFileDirectories);
      if (ret)
      {
        for (unsigned int i = 0; i < listSize; ++i)
          path.push_back(list[i]);
        ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->dialogFileBrowser.ClearList(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, list, listSize);
      }
      return ret;
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_DialogFileBrowser
    /// @brief Source selection dialog
    ///
    /// @param[out] path              Return value about selected source
    /// @param[in] allowNetworkShares Allow also access to network
    /// @param[in] additionalShare    With additionalShare becomes the available
    ///                               start folders be set (optional).
    /// @param[in] type
    /// @return                       False if selection becomes canceled.
    ///
    inline bool ShowAndGetSource(
      std::string&            path,
      bool                    allowNetworkShares,
      const std::string&      additionalShare = "",
      const std::string&      type = "")
    {
      path.resize(1024);
      unsigned int size = (unsigned int)path.capacity();
      bool ret = ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->dialogFileBrowser.ShowAndGetSource(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, path[0], size, allowNetworkShares, additionalShare.c_str(), type.c_str());
      path.resize(size);
      path.shrink_to_fit();
      return ret;
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_DialogFileBrowser
    /// @brief Image selection dialog
    ///
    /// @param[in] shares     With Shares becomes the available start folders be
    ///                       set.
    /// @param[in] heading    Dialog header name
    /// @param[out] path      Return value about selected image
    /// @return               False if selection becomes canceled.
    ///
    inline bool ShowAndGetImage(
      const std::string&      shares,
      const std::string&      heading,
      std::string&            path)
    {
      path.resize(1024);
      unsigned int size = (unsigned int)path.capacity();
      bool ret = ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->dialogFileBrowser.ShowAndGetImage(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, shares.c_str(), heading.c_str(), path[0], size);
      path.resize(size);
      path.shrink_to_fit();
      return ret;
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_DialogFileBrowser
    /// @brief Image selection dialog to get several in to a list
    ///
    /// @param[in] shares       With Shares becomes the available  start folders
    ///                         be set.
    /// @param[in] heading      Dialog header name
    /// @param[out] path        Return value about selected images
    /// @return                 False if selection becomes canceled.
    ///
    inline bool ShowAndGetImageList(
      const std::string&      shares,
      const std::string&      heading,
      std::vector<std::string> &path)
    {
      char** list;
      unsigned int listSize = 0;
      bool ret = ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->dialogFileBrowser.ShowAndGetImageList(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, shares.c_str(), heading.c_str(), list, listSize);
      if (ret)
      {
        for (unsigned int i = 0; i < listSize; ++i)
          path.push_back(list[i]);
        ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->dialogFileBrowser.ClearList(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, list, listSize);
      }
      return ret;
    }
    //--------------------------------------------------------------------------
  };

} /* namespace gui */
} /* namespace kodi */
