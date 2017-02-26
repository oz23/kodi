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
 *  along with Kodi; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "addons/kodi-addon-dev-kit/include/kodi/addon-instance/Screensaver.h"
#include "addons/AddonDll.h"

namespace ADDON
{

class CInstanceScreensaver : public IAddonInstanceHandler
{
public:
  CInstanceScreensaver(AddonInfoPtr addonInfo);
  virtual ~CInstanceScreensaver();

  bool Start();
  void Stop();
  void Render();

private:
  std::string m_name; /*!< To add-on sended name */
  std::string m_presets; /*!< To add-on sended preset path */
  std::string m_profile; /*!< To add-on sended profile path */

  AddonInstance_Screensaver m_struct; /*! Interface table who contains function addresses and fixed values */
  kodi::addon::CInstanceScreensaver* m_addonInstance; /*! class from addon side, @warning not to use on Kodi itself! */

  /*!
  * @brief Info about kodi::addon::CInstanceScreensaver above
  *
  * This class pointer is only be used to store the part of add-on here to have
  * it on "C" calls to them.
  *
  * In normal cases this should not be accessed from Kodi! During development if
  * add-on and Kodi is compiled with the same can it be used for test purpose.
  *
  * Reason to have add-on class and Kodi class complete independent is to prevent
  * compatibility failures on C++ if compiled on different Versions or different
  * build types (Debug, Release...), normally it works but it can never guaranted
  * that addon and Kodi side are compatible!
  *
  * Thats why still the "C" interface becomes used.
  */
};

} /* namespace ADDON */
