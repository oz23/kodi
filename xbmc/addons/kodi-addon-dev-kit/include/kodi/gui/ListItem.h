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
#include "definitions.h"

extern "C"
{
namespace kodi
{
namespace gui
{

  ///
  /// \ingroup cpp_kodi_gui_CListItem
  /// \defgroup cpp_kodi_gui_CListItem_MusicInfoTag Functions - Music info tag
  ///

  ///
  /// \ingroup cpp_kodi_gui_CListItem
  /// \defgroup cpp_kodi_gui_CListItem_VideoInfoTag Functions - Video info tag
  ///

  ///
  /// \ingroup cpp_kodi_gui_CListItem
  /// \defgroup cpp_kodi_gui_CListItem_PictureInfoTag Functions - Picture info tag
  ///

  //============================================================================
  ///
  /// \defgroup cpp_kodi_gui_CListItem List Item
  /// \ingroup cpp_kodi_gui
  /// @brief \cpp_class{ kodi::gui::CListItem }
  /// **Selectable window list item**
  ///
  /// The list item control is used for creating item lists in Kodi
  ///
  /// The with \ref ListItem.h "#include <kodi/gui/ListItem.h>" given
  /// class is used to create a item entry for a list on window and to support it's
  /// control.
  ///

  //============================================================================
  ///
  /// \defgroup cpp_kodi_gui_CListItem_Defs Definitions, structures and enumerators
  /// \ingroup cpp_kodi_gui_CListItem
  /// @brief **Library definition values**
  ///

  class CListItem
  {
  public:
    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CListItem
    /// @brief Class constructor with parameters
    ///
    /// @param[in] label                Item label
    /// @param[in] label2               Second Item label (if needed)
    /// @param[in] iconImage            Item icon image (if needed)
    /// @param[in] thumbnailImage       Thumbnail Image of item (if needed)
    /// @param[in] path                 Path to where item is defined
    ///
    CListItem(
      const std::string& label,
      const std::string& label2,
      const std::string& iconImage,
      const std::string& thumbnailImage,
      const std::string& path)
    {
      m_ListItemHandle = ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->listItem.Create(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, label.c_str(),
                                                label2.c_str(), iconImage.c_str(),
                                                thumbnailImage.c_str(), path.c_str());
    }

    CListItem(GUIHANDLE listItemHandle)
    {
      m_ListItemHandle = listItemHandle;
    }

    ///
    /// \ingroup cpp_kodi_gui_CListItem
    /// @brief Class destructor
    ///
    virtual ~CListItem()
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->listItem.Destroy(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ListItemHandle);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CListItem
    /// @brief Returns the listitem label.
    ///
    /// @return                       Label of item
    ///
    std::string GetLabel()
    {
      std::string label;
      label.resize(1024);
      unsigned int size = (unsigned int)label.capacity();
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->listItem.GetLabel(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ListItemHandle, label[0], size);
      label.resize(size);
      label.shrink_to_fit();
      return label.c_str();
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CListItem
    /// @brief Sets the listitem label.
    ///
    /// @param[in] label              string or unicode - text string.
    ///
    void SetLabel(const std::string& label)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->listItem.SetLabel(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ListItemHandle, label.c_str());
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CListItem
    /// @brief Returns the second listitem label.
    ///
    /// @return                       Second label of item
    ///
    std::string GetLabel2()
    {
      std::string label;
      label.resize(1024);
      unsigned int size = (unsigned int)label.capacity();
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->listItem.GetLabel2(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ListItemHandle, label[0], size);
      label.resize(size);
      label.shrink_to_fit();
      return label.c_str();
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CListItem
    /// @brief Sets the listitem's label2.
    ///
    /// @param[in] label              string or unicode - text string.
    ///
    void SetLabel2(const std::string& label)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->listItem.SetLabel2(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ListItemHandle, label.c_str());
    }
    //--------------------------------------------------------------------------
    
    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CListItem
    /// @brief To get current icon image of entry
    ///
    /// @return The current icon image path (if present)
    ///
    std::string GetIconImage()
    {
      std::string image;
      image.resize(1024);
      unsigned int size = (unsigned int)image.capacity();
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->listItem.GetIconImage(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ListItemHandle, image[0], size);
      image.resize(size);
      image.shrink_to_fit();
      return image.c_str();
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CListItem
    /// @brief To set icon image of entry
    ///
    /// @param image                    The image to use for.
    ///
    /// @note Alternative can be \ref SetArt used
    ///
    ///
    void SetIconImage(const std::string& image)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->listItem.SetIconImage(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ListItemHandle, image.c_str());
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CListItem
    /// @brief To get current overlay image of entry
    ///
    /// @return The current overlay image path (if present)
    ///
    std::string GetOverlayImage()
    {
      std::string image;
      image.resize(1024);
      unsigned int size = (unsigned int)image.capacity();
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->listItem.GetOverlayImage(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ListItemHandle, image[0], size);
      image.resize(size);
      image.shrink_to_fit();
      return image.c_str();
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CListItem
    /// @brief To set overlay image of entry
    ///
    /// @param image                    The image to use for.
    /// @param bOnOff                   To switch image view on (true) or off (false)
    ///
    void SetOverlayImage(unsigned int image, bool bOnOff = false)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->listItem.SetOverlayImage(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ListItemHandle, image, bOnOff);
    }
    //--------------------------------------------------------------------------


    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CListItem
    /// @brief To set thumbnail image of entry
    ///
    /// @warning Deprecated. Use setArt
    ///
    ///
    void SetThumbnailImage(const std::string& image)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->listItem.SetThumbnailImage(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ListItemHandle, image.c_str());
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CListItem
    /// @brief Sets the listitem's art
    ///
    /// @param[in] type                 Type of Art to set
    /// @param[in] url                  The url to use for Art
    ///  - Some default art values (any string possible):
    ///  | value (type)  | Type                                              |
    ///  |:-------------:|:--------------------------------------------------|
    ///  | thumb         | string - image filename
    ///  | poster        | string - image filename
    ///  | banner        | string - image filename
    ///  | fanart        | string - image filename
    ///  | clearart      | string - image filename
    ///  | clearlogo     | string - image filename
    ///  | landscape     | string - image filename
    ///  | icon          | string - image filename
    ///
    void SetArt(const std::string& type, const std::string& url)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->listItem.SetArt(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ListItemHandle, type.c_str(), url.c_str());
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CListItem
    /// @brief Sets the listitem's art
    ///
    /// @param[in] type                 Type of Art to set
    ///  - Some default art values (any string possible):
    ///  | value (type)  | Type                                              |
    ///  |:-------------:|:--------------------------------------------------|
    ///  | thumb         | string - image filename
    ///  | poster        | string - image filename
    ///  | banner        | string - image filename
    ///  | fanart        | string - image filename
    ///  | clearart      | string - image filename
    ///  | clearlogo     | string - image filename
    ///  | landscape     | string - image filename
    ///  | icon          | string - image filename
    /// @return                         The url to use for Art
    ///
    std::string GetArt(const std::string& type)
    {
      std::string strReturn;
      char* strMsg = ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->listItem.GetArt(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ListItemHandle, type.c_str());
      if (strMsg != nullptr)
      {
        if (std::strlen(strMsg))
          strReturn = strMsg;
        ::kodi::addon::CAddonBase::m_interface->toKodi->free_string(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, strMsg);
      }
      return strReturn;
    }
    //--------------------------------------------------------------------------
        
    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CListItem
    /// @brief Set a fallback image for art
    ///
    /// @param[in] from the type to fallback from
    /// @param[in] to the type to fallback to
    /// \sa SetArt
    void SetArtFallback(const std::string& from, const std::string& to)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->listItem.SetArtFallback(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ListItemHandle, from.c_str(), to.c_str());
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CListItem
    /// @brief
    ///
    /// @return                         true if present,, false if not
    ///
    bool HasArt(const std::string& type)
    {
      return ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->listItem.HasArt(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ListItemHandle, type.c_str());
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CListItem
    /// @brief Check item about presence of Icon
    ///
    /// @return                         true if present,, false if not
    ///
    bool HasIcon()
    {
      return ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->listItem.HasIcon(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ListItemHandle);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CListItem
    /// @brief To check item for presence of a Overlay image
    ///
    /// @return                         true if present, false if not
    ///
    bool HasOverlay()
    {
      return ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->listItem.HasOverlay(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ListItemHandle);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CListItem
    /// @brief To check item is a File
    ///
    /// @return                         true if is a file, false if not
    ///
    bool IsFileItem()
    {
      return ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->listItem.IsFileItem(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ListItemHandle);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CListItem
    /// @brief To check item is a Folder
    ///
    /// @return                         true if yes, false if not
    ///
    bool IsFolder()
    {
      return ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->listItem.IsFolder(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ListItemHandle);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CListItem
    /// @brief Sets the listitem's uniqueID
    ///
    /// @param[in] items                Type of Art to set
    ///  - Some example values (any string possible):
    ///  | Label         | Type                                              |
    ///  |:-------------:|:--------------------------------------------------|
    ///  | imdb          | string - uniqueid name
    ///  | tvdb          | string - uniqueid name
    ///  | tmdb          | string - uniqueid name
    ///  | anidb         | string - uniqueid name
    /// @param[in] defaultrating        [opt] the name of default rating.
    ///
    void SetUniqueIDs(const std::vector<std::pair<std::string, std::string> >& items, const std::string& defaultrating = "")
    {
      const char*** entries = nullptr;
      unsigned int size = items.size();
      if (size != 0)
      {
        entries = (const char***)malloc(size*sizeof(const char***));
        for (unsigned int i = 0; i < size; ++i)
        {
          entries[i][0] = items.at(i).first.c_str();
          entries[i][1] = items.at(i).second.c_str();
        }
      }

      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->listItem.SetUniqueIDs(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ListItemHandle, entries, size, defaultrating.c_str());
      if (entries)
        free(entries);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CListItem
    /// @brief Returns a listitem uniqueID as a string, similar to an infolabel.
    ///
    /// @param key            string - uniqueID name.
    /// - Some default uniqueID values (any string possible):
    ///  | Label         | Type                                             |
    ///  |---------------|--------------------------------------------------|
    ///  | imdb          | string - uniqueid name
    ///  | tvdb          | string - uniqueid name
    ///  | tmdb          | string - uniqueid name
    ///  | anidb         | string - uniqueid name
    ///
    ///
    ///
    ///-----------------------------------------------------------------------
    ///
    /// **Example:**
    /// ~~~~~~~~~~~~~{.cpp}
    /// ...
    /// ...
    /// ~~~~~~~~~~~~~
    ///
    std::string GetUniqueID(const std::string& key)
    {
      std::string strReturn;
      char* strMsg = ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->listItem.GetUniqueID(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ListItemHandle, key.c_str());
      if (strMsg != nullptr)
      {
        if (std::strlen(strMsg))
          strReturn = strMsg;
        ::kodi::addon::CAddonBase::m_interface->toKodi->free_string(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, strMsg);
      }
      return strReturn;
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CListItem
    /// @brief Sets a listitem's rating. It needs at least type and rating param
    ///
    /// @param[in] type       string - the type of the rating. Any string.
    /// @param[in] rating     float - the value of the rating.
    /// @param[in] votes      int - the number of votes. Default 0.
    /// @param[in] defaultt   bool - is the default rating?. Default False.
    ///  - Some example type (any string possible):
    ///  | Label         | Type                                              |
    ///  |:-------------:|:--------------------------------------------------|
    ///  | imdb          | string - rating type
    ///  | tvdb          | string - rating type
    ///  | tmdb          | string - rating type
    ///  | anidb         | string - rating type
    ///
    ///
    ///
    ///-----------------------------------------------------------------------
    ///
    /// **Example:**
    /// ~~~~~~~~~~~~~{.cpp}
    /// ...
    /// ...
    /// ~~~~~~~~~~~~~
    ///
    void SetRating(std::string type, float rating, int votes = 0, bool defaultt = false)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->listItem.SetRating(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ListItemHandle, type.c_str(), rating, votes, defaultt);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CListItem
    /// @brief Returns a listitem rating as a float.
    ///
    /// @param key            string - rating type.
    /// - Some default key values (any string possible):
    ///  | Label         | Type                                             |
    ///  |---------------|--------------------------------------------------|
    ///  | imdb          | string - type name
    ///  | tvdb          | string - type name
    ///  | tmdb          | string - type name
    ///  | anidb         | string - type name
    ///
    ///
    ///
    ///-----------------------------------------------------------------------
    ///
    /// **Example:**
    /// ~~~~~~~~~~~~~{.cpp}
    /// ...
    /// ...
    /// ~~~~~~~~~~~~~
    ///
    float GetRating(const std::string& key)
    {
      return ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->listItem.GetRating(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ListItemHandle, key.c_str());
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CListItem
    /// @brief Add a season with name to a listitem. It needs at least the season number
    ///
    /// @param[in] number     the number of the season.
    /// @param[in] name       the name of the season. Default "".
    ///
    ///-----------------------------------------------------------------------
    ///
    /// **Example:**
    /// ~~~~~~~~~~~~~{.cpp}
    /// ...
    /// ...
    /// ~~~~~~~~~~~~~
    ///
    void AddSeason(int number, const std::string& name = "")
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->listItem.AddSeason(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ListItemHandle, number, name.c_str());
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CListItem
    /// @brief Returns a listitem votes as a integer.\n
    ///
    /// @param key            string - rating type.
    /// - Some default key values (any string possible):
    ///  | Label         | Type                                             |
    ///  |---------------|--------------------------------------------------|
    ///  | imdb          | string - type name
    ///  | tvdb          | string - type name
    ///  | tmdb          | string - type name
    ///  | anidb         | string - type name
    ///
    ///
    ///
    ///-----------------------------------------------------------------------
    ///
    /// **Example:**
    /// ~~~~~~~~~~~~~{.cpp}
    /// ...
    /// ...
    /// ~~~~~~~~~~~~~
    ///
    int GetVotes(const std::string& key)
    {
      return ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->listItem.GetVotes(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ListItemHandle, key.c_str());
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CListItem
    /// @brief To control selection of item in list (also multiple selection,
    /// in list on serveral items possible).
    ///
    /// @param[in] selected             if true becomes set as selected
    ///
    void Select(bool selected)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->listItem.Select(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ListItemHandle, selected);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CListItem
    /// @brief Returns the listitem's selected status.
    ///
    /// @return                         true if selected, otherwise false
    ///
    bool IsSelected()
    {
      return ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->listItem.IsSelected(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ListItemHandle);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CListItem
    /// @brief Sets the listitem's infoLabels.
    ///
    /// @param type               string - type of
    /// @param infoLabels         dictionary - pairs of `{ label: value }`
    ///
    /// __Available types__
    /// | Command name | Description           |
    /// |:------------:|:----------------------|
    /// | video        | Video information
    /// | music        | Music information
    /// | pictures     | Pictures informanion
    /// | game         | Game information
    ///
    /// @note To set pictures exif info, prepend `exif:` to the label. Exif values must be passed
    ///       as strings, separate value pairs with a comma. <b>(eg. <c>{'exif:resolution': '720,480'}</c></b>
    ///       See \ref kodi_pictures_infotag for valid strings.\n
    ///       \n
    ///       You can use the above as keywords for arguments and skip certain optional arguments.
    ///       Once you use a keyword, all following arguments require the keyword.
    ///
    /// __General Values__ (that apply to all types):
    /// | Info label    | Description                                        |
    /// |--------------:|:---------------------------------------------------|
    /// | count         | integer (12) - can be used to store an id for later, or for sorting purposes
    /// | size          | long (1024) - size in bytes
    /// | date          | string (%d.%m.%Y / 01.01.2009) - file date
    ///
    /// __Video Values__:
    /// | Info label    | Description                                        |
    /// |--------------:|:---------------------------------------------------|
    /// | genre         | string (Comedy) or list of strings (["Comedy", "Animation", "Drama"])
    /// | country       | string (Germany) or list of strings (["Germany", "Italy", "France"])
    /// | year          | integer (2009)
    /// | episode       | integer (4)
    /// | season        | integer (1)
    /// | sortepisode   | integer (4)
    /// | sortseason    | integer (1)
    /// | episodeguide  | string (Episode guide)
    /// | showlink      | string (Battlestar Galactica) or list of strings (["Battlestar Galactica", "Caprica"])
    /// | top250        | integer (192)
    /// | setid         | integer (14)
    /// | tracknumber   | integer (3)
    /// | rating        | float (6.4) - range is 0..10
    /// | userrating    | integer (9) - range is 1..10 (0 to reset)
    /// | watched       | depreciated - use playcount instead
    /// | playcount     | integer (2) - number of times this item has been played
    /// | overlay       | integer (2) - range is `0..7`.  See \ref kodi_guilib_listitem_iconoverlay "Overlay icon types" for values
    /// | cast          | list (["Michal C. Hall","Jennifer Carpenter"]) - if provided a list of tuples cast will be interpreted as castandrole
    /// | castandrole   | list of tuples ([("Michael C. Hall","Dexter"),("Jennifer Carpenter","Debra")])
    /// | director      | string (Dagur Kari) or list of strings (["Dagur Kari", "Quentin Tarantino", "Chrstopher Nolan"])
    /// | mpaa          | string (PG-13)
    /// | plot          | string (Long Description)
    /// | plotoutline   | string (Short Description)
    /// | title         | string (Big Fan)
    /// | originaltitle | string (Big Fan)
    /// | sorttitle     | string (Big Fan)
    /// | duration      | integer (245) - duration in seconds
    /// | studio        | string (Warner Bros.) or list of strings (["Warner Bros.", "Disney", "Paramount"])
    /// | tagline       | string (An awesome movie) - short description of movie
    /// | writer        | string (Robert D. Siegel) or list of strings (["Robert D. Siegel", "Jonathan Nolan", "J.K. Rowling"])
    /// | tvshowtitle   | string (Heroes)
    /// | premiered     | string (2005-03-04)
    /// | status        | string (Continuing) - status of a TVshow
    /// | set           | string (Batman Collection) - name of the collection
    /// | setoverview   | string (All Batman movies) - overview of the collection
    /// | tag           | string (cult) or list of strings (["cult", "documentary", "best movies"]) - movie tag
    /// | imdbnumber    | string (tt0110293) - IMDb code
    /// | code          | string (101) - Production code
    /// | aired         | string (2008-12-07)
    /// | credits       | string (Andy Kaufman) or list of strings (["Dagur Kari", "Quentin Tarantino", "Chrstopher Nolan"]) - writing credits
    /// | lastplayed    | string (%Y-%m-%d %h:%m:%s = 2009-04-05 23:16:04)
    /// | album         | string (The Joshua Tree)
    /// | artist        | list (['U2'])
    /// | votes         | string (12345 votes)
    /// | path          | string (/home/user/movie.avi)
    /// | trailer       | string (/home/user/trailer.avi)
    /// | dateadded     | string (%Y-%m-%d %h:%m:%s = 2009-04-05 23:16:04)
    /// | mediatype     | string - "video", "movie", "tvshow", "season", "episode" or "musicvideo"
    /// | dbid          | integer (23) - Only add this for items which are part of the local db. You also need to set the correct 'mediatype'!
    ///
    /// __Music Values__:
    /// | Info label               | Description                                        |
    /// |-------------------------:|:---------------------------------------------------|
    /// | tracknumber              | integer (8)
    /// | discnumber               | integer (2)
    /// | duration                 | integer (245) - duration in seconds
    /// | year                     | integer (1998)
    /// | genre                    | string (Rock)
    /// | album                    | string (Pulse)
    /// | artist                   | string (Muse)
    /// | title                    | string (American Pie)
    /// | rating                   | float - range is between 0 and 10
    /// | userrating               | integer - range is 1..10
    /// | lyrics                   | string (On a dark desert highway...)
    /// | playcount                | integer (2) - number of times this item has been played
    /// | lastplayed               | string (%Y-%m-%d %h:%m:%s = 2009-04-05 23:16:04)
    /// | mediatype                | string - "music", "song", "album", "artist"
    /// | dbid                     | integer (23) - Only add this for items which are part of the local db. You also need to set the correct 'mediatype'!
    /// | listeners                | integer (25614)
    /// | musicbrainztrackid       | string (cd1de9af-0b71-4503-9f96-9f5efe27923c)
    /// | musicbrainzartistid      | string (d87e52c5-bb8d-4da8-b941-9f4928627dc8)
    /// | musicbrainzalbumid       | string (24944755-2f68-3778-974e-f572a9e30108)
    /// | musicbrainzalbumartistid | string (d87e52c5-bb8d-4da8-b941-9f4928627dc8)
    /// | comment                  | string (This is a great song)
    ///
    /// __Picture Values__:
    /// | Info label    | Description                                        |
    /// |--------------:|:---------------------------------------------------|
    /// | title         | string (In the last summer-1)
    /// | picturepath   | string (`/home/username/pictures/img001.jpg`)
    /// | exif*         | string (See \ref kodi_pictures_infotag for valid strings)
    ///
    /// __Game Values__:
    /// | Info label    | Description                                        |
    /// |--------------:|:---------------------------------------------------|
    /// | title         | string (Super Mario Bros.)
    /// | platform      | string (Atari 2600)
    /// | genres        | list (["Action","Strategy"])
    /// | publisher     | string (Nintendo)
    /// | developer     | string (Square)
    /// | overview      | string (Long Description)
    /// | year          | integer (1980)
    /// | gameclient    | string (game.libretro.fceumm)
    ///
    ///
    ///-----------------------------------------------------------------------
    ///
    /// **Example:**
    /// ~~~~~~~~~~~~~{.cpp}
    /// ...
    /// ...
    /// ~~~~~~~~~~~~~
    ///
    void SetInfo(const std::string& type, const std::vector<std::pair<std::string, std::string> >& infoLabels)
    {
      const char*** entries = nullptr;
      unsigned int size = infoLabels.size();
      if (size != 0)
      {
        entries = (const char***)malloc(size*sizeof(const char***));
        for (unsigned int i = 0; i < size; ++i)
        {
          entries[i][0] = infoLabels.at(i).first.c_str();
          entries[i][1] = infoLabels.at(i).second.c_str();
        }
      }

      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->listItem.SetInfo(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ListItemHandle, type.c_str(), entries, size);
      if (entries)
        free(entries);
    }
    //--------------------------------------------------------------------------
     
    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CListItem
    /// @brief Set cast including thumbnails
    ///
    /// @param actors            list of dictionaries (see below for relevant keys)
    ///
    /// - Keys:
    /// | Label         | Description                                     |
    /// |--------------:|:------------------------------------------------|
    /// | name          | string (Michael C. Hall)
    /// | role          | string (Dexter)
    /// | thumbnail     | string (http://www.someurl.com/someimage.png)
    /// | order         | integer (1)
    ///
    ///
    ///-----------------------------------------------------------------------
    ///
    /// **Example:**
    /// ~~~~~~~~~~~~~{.cpp}
    /// ...
    /// ...
    /// ~~~~~~~~~~~~~
    ///
    void SetCast(const std::vector<CastProperties>& actors)
    {
      /// @todo !!!!
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CListItem
    /// @brief Set available images (needed for scrapers)
    ///
    /// @param images            list of dictionaries (see below for relevant keys)
    ///
    /// - Keys:
    /// | Label         | Description                                     |
    /// |--------------:|:------------------------------------------------|
    /// | image         | string (http://www.someurl.com/someimage.png)
    /// | preview       | [opt] string (http://www.someurl.com/somepreviewimage.png)
    /// | colors        | [opt] string (either comma separated Kodi hex values ("FFFFFFFF,DDDDDDDD") or TVDB RGB Int Triplets ("|68,69,59|69,70,58|78,78,68|"))
    ///
    ///
    ///-----------------------------------------------------------------------
    ///
    /// **Example:**
    /// ~~~~~~~~~~~~~{.cpp}
    /// ...
    /// ...
    /// ~~~~~~~~~~~~~
    ///
    void SetAvailableFanart(const std::vector<FanartProperties>& images)
    {
      /// @todo !!!!
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CListItem
    /// @brief Add a thumb to available thumbs (needed for scrapers)
    ///
    /// @param url            string (image path url)
    /// @param aspect         [opt] string (image type)
    /// @param referrer       [opt] string (referr url)
    /// @param cache          [opt] string (filename in cache)
    /// @param post           [opt] bool (use post to retrieve the image, default false)
    /// @param isgz           [opt] bool (use gzip to retrieve the image, default false)
    /// @param season         [opt] integer (number of season in case of season thumb)
    ///
    ///-----------------------------------------------------------------------
    ///
    /// **Example:**
    /// ~~~~~~~~~~~~~{.cpp}
    /// ...
    /// ...
    /// ~~~~~~~~~~~~~
    ///
    void AddAvailableThumb(const std::string& url, const std::string& aspect = "",
                           const std::string& referrer = "", const std::string& cache = "",
                           bool post = false, bool isgz = false, int season = -1)
    {
      using namespace ::kodi::addon;
      CAddonBase::m_interface->toKodi->kodi_gui->listItem.AddAvailableThumb(CAddonBase::m_interface->toKodi->kodiBase, m_ListItemHandle, url.c_str(), aspect.c_str(), referrer.c_str(), cache.c_str(), post, isgz, season);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CListItem
    /// @brief Add a stream with details.
    ///
    /// @param[in] type               string - type of stream(video/audio/subtitle).
    /// @param[in] dictionary         dictionary - pairs of { label: value }.
    /// - Video Values:
    ///  | Label       | Type          | Example value     |
    ///  |:-----------:|:-------------:|:------------------|
    ///  | codec       | string        | h264
    ///  | aspect      | float         | 1.78
    ///  | width       | integer       | 1280
    ///  | height      | integer       | 720
    ///  | duration    | integer       | seconds
    ///
    /// - Audio Values:
    ///  | Label       | Type          | Example value     |
    ///  |:-----------:|:-------------:|:------------------|
    ///  | codec       | string        | dts
    ///  | language    | string        | en
    ///  | channels    | integer       | 2
    ///
    /// - Subtitle Values:
    ///  | Label       | Type          | Example value    |
    ///  |:-----------:|:-------------:|:-----------------|
    ///  | language    | string        | en
    ///
    ///
    ///
    ///-----------------------------------------------------------------------
    ///
    /// **Example:**
    /// ~~~~~~~~~~~~~{.cpp}
    /// ...
    /// ...
    /// ~~~~~~~~~~~~~
    ///
    void AddStreamInfo(const std::string& type, const std::vector<std::pair<std::string, std::string> >& dictionary)
    {
      const char*** entries = nullptr;
      unsigned int size = dictionary.size();
      if (size == 0)
        return;

      entries = (const char***)malloc(size*sizeof(const char***));
      for (unsigned int i = 0; i < size; ++i)
      {
        entries[i][0] = dictionary.at(i).first.c_str();
        entries[i][1] = dictionary.at(i).second.c_str();
      }

      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->listItem.AddStreamInfo(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ListItemHandle, type.c_str(), entries, size);
      free(entries);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CListItem
    /// @brief Adds item(s) to the context menu for media lists.
    ///
    /// @param[in] items              list - <b><c>[(label, action,)*]</c></b> A list of tuples consisting of label and action pairs.
    ///                               - `label`          : string or unicode - item's label.
    ///                               - `action`         : string or unicode - any built-in function to perform.
    /// @param[in] replaceItems       [opt] bool - True=only your items will show/False=your items will be added to context menu(Default).
    ///
    /// [List of built-in functions](http://kodi.wiki/view/List_of_Built_In_Functions)
    ///
    /// @note You can use the above as keywords for arguments and skip certain
    ///       optional arguments.\n
    ///       Once you use a keyword, all following arguments require the
    ///       keyword.
    ///
    ///
    ///-----------------------------------------------------------------------
    ///
    /// **Example:**
    /// ~~~~~~~~~~~~~{.cpp}
    /// ...
    /// ...
    /// ~~~~~~~~~~~~~
    ///
    void AddContextMenuItems(const std::vector<std::pair<std::string, std::string> >& items, bool replaceItems = false)
    {
      const char*** entries = nullptr;
      unsigned int size = items.size();
      if (size != 0)
      {
        entries = (const char***)malloc(size*sizeof(const char***));
        for (unsigned int i = 0; i < size; ++i)
        {
          entries[i][0] = items.at(i).first.c_str();
          entries[i][1] = items.at(i).second.c_str();
        }
      }

      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->listItem.AddContextMenuItems(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ListItemHandle, entries, size, replaceItems);
      if (entries)
        free(entries);
    }
    //--------------------------------------------------------------------------
    
    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CListItem
    /// @brief Sets a listitem property, similar to an infolabel.
    ///
    /// @param[in] key            string - property name.
    /// @param[in] value          string or unicode - value of property.
    ///
    /// @note Key is NOT case sensitive.
    ///       You can use the above as keywords for arguments and skip certain\n
    ///       optional arguments.\n
    ///       Once you use a keyword, all following arguments require the
    ///       keyword.
    ///
    /// Some of these are treated internally by Kodi, such as the
    /// <b>'StartOffset'</b> property, which is the offset in seconds at which to
    /// start playback of an item.  Others may be used in the skin to add
    /// extra information, such as <b>'WatchedCount'</b> for tvshow items
    ///
    void SetProperty(const std::string& key, const std::string& value)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->listItem.SetProperty(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ListItemHandle, key.c_str(), value.c_str());
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CListItem
    /// @brief Returns a listitem property as a string, similar to an infolabel.
    ///
    /// @param[in] key                string - property name.
    /// @return                       string - List item property
    ///
    /// @note Key is NOT case sensitive.\n
    ///       You can use the above as keywords for arguments and skip certain
    ///       optional arguments.\n
    ///       Once you use a keyword, all following arguments require the
    ///       keyword.
    ///
    std::string GetProperty(const std::string& key)
    {
      std::string property;
      property.resize(1024);
      unsigned int size = (unsigned int)property.capacity();
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->listItem.GetProperty(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ListItemHandle, key.c_str(), property[0], size);
      property.resize(size);
      property.shrink_to_fit();
      return property;
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CListItem
    /// @brief Clears the specific window property.
    ///
    /// @param[in] key                string - property name.
    ///
    /// @note Key is NOT case sensitive. Equivalent to setProperty(key,'')
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
    /// ..
    /// ~~~~~~~~~~~~~
    ///
    void ClearProperty(const std::string& key)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->listItem.ClearProperty(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ListItemHandle, key.c_str());
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CListItem
    /// @brief Clears all window properties.
    ///
    ///
    ///-----------------------------------------------------------------------
    ///
    /// **Example:**
    /// ~~~~~~~~~~~~~{.cpp}
    /// ..
    /// ..
    /// ~~~~~~~~~~~~~
    ///
    void ClearProperties()
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->listItem.ClearProperties(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ListItemHandle);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CListItem
    /// @brief To check list item about presence of properties
    ///
    /// @return                         true if properties present
    ///
    bool HasProperties()
    {
      return ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->listItem.HasProperties(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ListItemHandle);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CListItem
    /// @brief To check list item about presence of searched key by name
    ///
    /// @param[in] key                  Property to check
    /// @return                         true if properties present
    ///
    bool HasProperty(const std::string& key)
    {
      return ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->listItem.HasProperty(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ListItemHandle, key.c_str());
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CListItem
    /// @brief Sets the listitem's path.
    ///
    /// @param[in] path               string or unicode - path, activated when
    ///                               item is clicked.
    ///
    /// @note You can use the above as keywords for arguments.
    ///
    void SetPath(const std::string& path)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->listItem.SetPath(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ListItemHandle, path.c_str());
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CListItem
    /// @brief Returns the path / filename of this listitem.
    ///
    /// @return                       Path string
    ///
    std::string GetPath()
    {
      std::string strReturn;
      char* strMsg = ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->listItem.GetPath(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ListItemHandle);
      if (strMsg != nullptr)
      {
        if (std::strlen(strMsg))
          strReturn = strMsg;
        ::kodi::addon::CAddonBase::m_interface->toKodi->free_string(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, strMsg);
      }
      return strReturn;
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CListItem
    /// @brief Sets the listitem's mimetype if known.
    ///
    /// @param[in] mimetype           string or unicode - mimetype.
    ///
    /// If known prehand, this can (but does not have to) avoid HEAD requests
    /// being sent to HTTP servers to figure out file type.
    ///
    void SetMimeType(const std::string& mimetype)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->listItem.SetMimeType(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ListItemHandle, mimetype.c_str());
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CListItem
    /// @brief Enable or disable content lookup for item.
    ///
    /// If disabled, HEAD requests to e.g. determine mime type will not be
    /// sent.
    ///
    /// @param[in] enable             bool - True = enable, False = disable
    ///
    void SetContentLookup(bool enable)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->listItem.SetContentLookup(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ListItemHandle, enable);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CListItem
    /// @brief Sets subtitles for this listitem.
    ///
    /// @param[in] subtitleFiles      string - List of subtitles to add
    ///
    ///
    ///-----------------------------------------------------------------------
    ///
    /// **Example:**
    /// ~~~~~~~~~~~~~{.cpp}
    /// ...
    /// ...
    /// ~~~~~~~~~~~~~
    ///
    void SetSubtitles(const std::vector<std::string>& subtitleFiles)
    {
      unsigned int size = subtitleFiles.size();
      if (size == 0)
        return;

      const char** subtitles = (const char**)malloc(size);
      for (unsigned int i = 0; i < size; ++i)
        subtitles[i] = subtitleFiles[i].c_str();

      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->listItem.SetSubtitles(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ListItemHandle, subtitles, size);
      free(subtitles);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CListItem
    /// @brief Returns the duration of this listitem
    ///
    /// @return                       Duration of item as integer
    ///
    int GetDuration() const
    {
      return ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->listItem.GetDuration(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ListItemHandle);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CListItem
    /// @brief  Returns the VideoInfoTag for this item.
    ///
    /// @return     video info tag
    ///-----------------------------------------------------------------------
    ///
//    xbmc::InfoTagVideo* getVideoInfoTag();
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CListItem
    /// @brief Returns the MusicInfoTag for this item.
    ///
    /// @return     music info tag
    ///-----------------------------------------------------------------------
    ///
//    xbmc::InfoTagMusic* getMusicInfoTag();
    //--------------------------------------------------------------------------
      
    const void* GetListItemHandle() const
    {
      return m_ListItemHandle;
    }

  protected:
    void* m_ListItemHandle;

  private:
    friend class CWindow;
  };

} /* namespace gui */
} /* namespace kodi */
} /* extern "C" */
