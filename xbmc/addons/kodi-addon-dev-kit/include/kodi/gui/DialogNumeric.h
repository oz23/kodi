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
  /// \defgroup cpp_kodi_gui_DialogNumeric Dialog Numeric
  /// \ingroup cpp_kodi_gui
  /// @{
  /// @brief \cpp_namespace{ kodi::gui::DialogNumeric }
  /// **Numeric dialogs**
  ///
  /// The functions listed below have to be permitted by the user for the
  /// representation of a numeric keyboard around an input.
  ///
  /// The class supports several kinds, from an easy number choice up to the
  /// passport Word production and their confirmation for add-on.
  ///
  /// These are pure static functions them no other initialization need.
  ///
  /// It has the header \ref DialogNumeric.h "#include <kodi/gui/DialogNumeric.h>"
  /// be included to enjoy it.
  ///
  namespace DialogNumeric
  {
    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_DialogNumeric
    /// @brief Use dialog to get numeric new password
    ///
    /// @param[out] newPassword        String to preload into the keyboard
    ///                                accumulator. Overwritten with user input
    ///                                if return=true.
    /// @return                        true if successful display and user
    ///                                input entry/re-entry.
    ///                                false if unsuccessful display, no user
    ///                                input, or canceled editing.
    ///
    inline bool ShowAndVerifyNewPassword(std::string& newPassword)
    {
      newPassword.reserve(1024);
      unsigned int size = (unsigned int)newPassword.capacity();
      bool ret = ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->dialogNumeric.ShowAndVerifyNewPassword(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, newPassword[0], size);
      newPassword.resize(size);
      newPassword.shrink_to_fit();
      return ret;
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_DialogNumeric
    /// @brief Use dialog to verify numeric password.
    ///
    /// @param[out] password            Overwritten with user input if return=true
    /// @param[in] heading              Heading to display
    /// @param[in] iRetries             If greater than 0, shows "Incorrect
    ///                                 password, %d retries left" on dialog
    ///                                 line 2, else line 2 is blank.
    /// @return                         Possible values:
    ///                                 - 0 if successful display and user input.
    ///                                 - 1 if unsuccessful input.
    ///                                 - -1 if no user input or canceled editing.
    ///
    ///
    ///-------------------------------------------------------------------------
    ///
    /// **Example:**
    /// ~~~~~~~~~~~~~{.cpp}
    /// #include <stdio.h>      /* fprintf */
    /// #include <kodi/addon/General.h>
    /// #include <kodi/gui/DialogNumeric.h>
    ///
    /// /*
    ///  * The example below shows the complete use of keyboard dialog for password
    ///  * check. If only one check from add-on needed can be function with retries
    ///  * set to '0' called alone.
    ///  *
    ///  * The use of MD5 translated password is always required for the check on Kodi!
    ///  */
    ///
    /// /*
    ///  * Get from Kodi's global settings the maximum allowed retries for passwords.
    ///  */
    /// int maxretries = 0;
    /// if (KodiAPI::AddOn::General::GetSettingInt("masterlock.maxretries", maxretries, true))
    /// {
    ///   /*
    ///    * Password names need to be send as md5 sum to kodi.
    ///    */
    ///   std::string password;
    ///   CAddonLib_General::GetMD5("1234", password);
    ///
    ///   /*
    ///    * To the loop about password checks.
    ///    */
    ///   int ret;
    ///   for (unsigned int i = 0; i < maxretries; i++)
    ///   {
    ///     /*
    ///      * Ask the user about the password.
    ///      */
    ///     ret = kodi::gui::DialogNumeric::ShowAndVerifyPassword(password, "Demo numeric password call for PW '1234'", i);
    ///     if (ret == 0)
    ///     {
    ///       fprintf(stderr, "Numeric password successfull confirmed after '%i' tries\n", i+1);
    ///       break;
    ///     }
    ///     else if (ret < 0)
    ///     {
    ///       fprintf(stderr, "Canceled editing on try '%i'\n", i+1);
    ///       break;
    ///     }
    ///     else /* if (ret > 0) */
    ///     {
    ///       fprintf(stderr, "Wrong numeric password entered on try '%i'\n", i+1);
    ///      }
    ///   }
    /// }
    /// else
    ///   fprintf(stderr, "Requested global setting value 'masterlock.maxretries' not present!");
    /// ~~~~~~~~~~~~~
    ///
    inline int ShowAndVerifyPassword(
      std::string&            password,
      const std::string&      heading,
      int                     iRetries)
    {
      password.resize(1024);
      unsigned int size = (unsigned int)password.capacity();
      bool ret = ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->dialogNumeric.ShowAndVerifyPassword(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, password[0], size, heading.c_str(), iRetries);
      password.resize(size);
      password.shrink_to_fit();
      return ret;
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_DialogNumeric
    /// @brief Use dialog to verify numeric password
    ///
    /// @param[out] toVerify            Value to compare against user input.
    /// @param[in] heading              Heading to display
    /// @param[in] verifyInput          If set as true we verify the users input
    ///                                 versus toVerify.
    /// @return                         true if successful display and user
    ///                                 input. false if unsuccessful display, no
    ///                                 user input, or canceled editing.
    ///
    inline bool ShowAndVerifyInput(
      std::string&            toVerify,
      const std::string&      heading,
      bool                    verifyInput)
    {
      toVerify.resize(1024);
      unsigned int size = (unsigned int)toVerify.capacity();
      bool ret = ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->dialogNumeric.ShowAndVerifyInput(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, toVerify[0], size, heading.c_str(), verifyInput);
      toVerify.resize(size);
      toVerify.shrink_to_fit();
      return ret;
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_DialogNumeric
    /// @brief Use dialog to get time value.
    ///
    /// @param[out] time                Overwritten with user input if
    ///                                 return=true and time inserted.
    /// @param[in] heading              Heading to display.
    /// @return                         true if successful display and user
    ///                                 input. false if unsuccessful display, no
    ///                                 user input, or canceled editing.
    ///
    ///
    ///-------------------------------------------------------------------------
    ///
    /// **Example:**
    /// ~~~~~~~~~~~~~{.cpp}
    /// #include <stdio.h>      /* printf */
    /// #include <time.h>       /* time_t, struct tm, time, localtime, strftime */
    /// #include <kodi/gui/DialogNumeric.h>
    ///
    /// time_t rawtime;
    /// struct tm * timeinfo;
    /// char buffer [10];
    ///
    /// time (&rawtime);
    /// timeinfo = localtime(&rawtime);
    /// bool bRet = kodi::gui::DialogNumeric::ShowAndGetTime(*timeinfo, "Selected time test call");
    /// strftime(buffer, sizeof(buffer), "%H:%M.", timeinfo);
    /// printf("Selected time it's %s and was on Dialog %s\n", buffer, bRet ? "OK" : "Canceled");
    /// ~~~~~~~~~~~~~
    ///
    inline bool ShowAndGetTime(
      tm&                     time,
      const std::string&      heading)
    {
      return ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->dialogNumeric.ShowAndGetTime(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, time, heading.c_str());
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_DialogNumeric
    /// @brief Use dialog to get date value.
    ///
    /// @param[out] date                Overwritten with user input if
    ///                                 return=true and date inserted.
    /// @param[in] heading              Heading to display
    /// @return                         true if successful display and user
    ///                                 input. false if unsuccessful display, no
    ///                                 user input, or canceled editing.
    ///
    ///
    ///-------------------------------------------------------------------------
    ///
    /// **Example:**
    /// ~~~~~~~~~~~~~{.cpp}
    /// #include <stdio.h>      /* printf */
    /// #include <time.h>       /* time_t, struct tm, time, localtime, strftime */
    /// #include <kodi/gui/DialogNumeric.h>
    ///
    /// time_t rawtime;
    /// struct tm * timeinfo;
    /// char buffer [20];
    ///
    /// time (&rawtime);
    /// timeinfo = localtime(&rawtime);
    /// bool bRet = kodi::gui::DialogNumeric::ShowAndGetDate(*timeinfo, "Selected date test call");
    /// strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeinfo);
    /// printf("Selected date it's %s and was on Dialog %s\n", buffer, bRet ? "OK" : "Canceled");
    /// ~~~~~~~~~~~~~
    ///
    inline bool ShowAndGetDate(
      tm&                     date,
      const std::string&      heading)
    {
      return ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->dialogNumeric.ShowAndGetDate(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, date, heading.c_str());
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_DialogNumeric
    /// @brief Use dialog to get a IP
    ///
    /// @param[out] ipAddress           Overwritten with user input if
    ///                                 return=true and IP address inserted.
    /// @param[in] heading              Heading to display.
    /// @return                         true if successful display and
    ///                                 user input. false if unsuccessful
    ///                                 display, no user input, or canceled
    ///                                 editing.
    ///
    inline bool ShowAndGetIPAddress(
      std::string&            ipAddress,
      const std::string&      heading)
    {
      ipAddress.resize(1024);
      unsigned int size = (unsigned int)ipAddress.capacity();
      bool ret = ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->dialogNumeric.ShowAndGetIPAddress(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, ipAddress[0], size, heading.c_str());
      ipAddress.resize(size);
      ipAddress.shrink_to_fit();
      return ret;
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_DialogNumeric
    /// @brief Use dialog to get normal number.
    ///
    /// @param[out] input               Overwritten with user input if
    ///                                 return=true and time in seconds inserted
    /// @param[in] heading              Heading to display
    /// @param[in] autoCloseTimeoutMs   To close the dialog after a specified
    ///                                 time, in milliseconds, default is 0
    ///                                 which keeps the dialog open
    ///                                 indefinitely.
    /// @return                         true if successful display and user
    ///                                 input. false if unsuccessful display, no
    ///                                 user input, or canceled editing.
    ///
    ///
    ///-------------------------------------------------------------------------
    ///
    /// **Example:**
    /// ~~~~~~~~~~~~~{.cpp}
    ///   #include <stdio.h>      /* printf */
    ///   #include <stdlib.h>     /* strtoull (C++11) */
    ///   #include <kodi/gui/DialogNumeric.h>
    ///
    ///   std::string number;
    ///   bool bRet = kodi::gui::DialogNumeric::ShowAndGetNumber(number, "Number test call");
    ///   printf("Written number input is : %llu and was %s\n",
    ///                  strtoull(number.c_str(), nullptr, 0), bRet ? "OK" : "Canceled");
    /// ~~~~~~~~~~~~~
    ///
    inline bool ShowAndGetNumber(
      std::string&            input,
      const std::string&      heading,
      unsigned int            autoCloseTimeoutMs = 0)
    {
      input.resize(1024);
      unsigned int size = (unsigned int)input.capacity();
      bool ret = ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->dialogNumeric.ShowAndGetNumber(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, input[0], size, heading.c_str(), autoCloseTimeoutMs);
      input.resize(size);
      input.shrink_to_fit();
      return ret;
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_DialogNumeric
    /// @brief Show numeric keypad to get seconds.
    ///
    /// @param[out] time        Overwritten with user input if return=true and
    ///                         time in seconds inserted.
    /// @param[in] heading      Heading to display
    /// @return                 true if successful display and user input. false
    ///                         if unsuccessful display, no user input, or
    ///                         canceled editing.
    ///
    inline bool ShowAndGetSeconds(
      std::string&            time,
      const std::string&      heading)
    {
      time.resize(1024);
      unsigned int size = (unsigned int)time.capacity();
      bool ret = ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->dialogNumeric.ShowAndGetSeconds(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, time[0], size, heading.c_str());
      time.resize(size);
      time.shrink_to_fit();
      return ret;
    }
    //--------------------------------------------------------------------------
  };
  /// @}

} /* namespace gui */
} /* namespace kodi */
