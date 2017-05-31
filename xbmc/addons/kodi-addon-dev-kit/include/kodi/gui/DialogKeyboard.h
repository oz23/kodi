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
  /// \defgroup cpp_kodi_gui_DialogKeyboard Dialog Keyboard
  /// \ingroup cpp_kodi_gui
  /// @brief \cpp_namespace{ kodi::gui::DialogKeyboard }
  /// **Keyboard dialogs**
  ///
  /// The functions listed below have to be permitted by the user for the
  /// representation of a keyboard around an input.
  ///
  /// The class supports several kinds, from an easy text choice up to the
  /// passport Word production and their confirmation for add-on.
  ///
  /// These are pure static functions them no other initialization need.
  ///
  /// It has the header \ref DialogKeyboard.h "#include <kodi/gui/DialogKeyboard.h>"
  /// be included to enjoy it.
  ///
  namespace DialogKeyboard
  {
    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_DialogKeyboard
    /// @brief Show keyboard with initial value `text` and replace with  result
    /// string.
    ///
    /// @param[out] text             Overwritten with user input if return=true.
    /// @param[in] heading           String shown on dialog title.
    /// @param[in] allowEmptyResult  Whether a blank password is valid or not.
    /// @param[in] hiddenInput       The inserted input is not shown as text.
    /// @param[in] autoCloseMs       To  close  the  dialog  after  a  specified
    ///                              time, in milliseconds, default is  0  which
    ///                              keeps the dialog open indefinitely.
    /// @return                      true if successful display and user  input.
    ///                              false  if  unsuccessful  display,  no  user
    ///                              input, or canceled editing.
    ///
    ///
    ///-------------------------------------------------------------------------
    ///
    /// **Example:**
    /// ~~~~~~~~~~~~~{.cpp}
    /// #include <kodi/gui/DialogKeyboard.h>
    ///
    /// /*
    ///  * The example shows the display of keyboard call dialog at Kodi from the add-on.
    ///  * Below all values are set, however, can last two (hidden input = false and autoCloseMs = 0)
    ///  * to be released if not needed.
    ///  */
    /// std::string text = "Please change me to them want you want"; /*< It can be leaved empty or a
    ///                                                                  entry text added */
    /// bool bRet = ::kodi::gui::DialogKeyboard::ShowAndGetInput(text,
    ///                                                      "Demonstration text entry",
    ///                                                      true,
    ///                                                      false,
    ///                                                      0);
    /// fprintf(stderr, "Written keyboard input is : %s and was %s\n",
    ///                   text.c_str(), bRet ? "OK" : "Canceled");
    /// ~~~~~~~~~~~~~
    ///
    inline bool ShowAndGetInput(
      std::string&            text,
      const std::string&      heading,
      bool                    allowEmptyResult,
      bool                    hiddenInput = false,
      unsigned int            autoCloseMs = 0)
    {
      text.resize(1024);
      unsigned int size = (unsigned int)text.capacity();
      bool ret = ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->dialogKeyboard.ShowAndGetInputWithHead(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, text[0], size, heading.c_str(), allowEmptyResult, hiddenInput, autoCloseMs);
      text.resize(size);
      text.shrink_to_fit();
      return ret;
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_DialogKeyboard
    /// @brief The example shows the display of keyboard  call dialog  at  Kodi
    /// from the add-on.
    ///
    /// @param[out] text            Overwritten with user input if return=true.
    /// @param[in] allowEmptyResult If  set  to true  keyboard can  also  exited
    ///                             without entered text.
    /// @param[in] autoCloseMs      To close the dialog after a specified  time,
    ///                             in milliseconds,  default is  0 which  keeps
    ///                             the dialog open indefinitely.
    /// @return                     true if successful display and user input.
    ///                             false  if  unsuccessful   display,  no  user
    ///                             input, or canceled editing.
    ///
    inline bool ShowAndGetInput(
      std::string&            text,
      bool                    allowEmptyResult,
      unsigned int            autoCloseMs = 0)
    {
      text.resize(1024);
      unsigned int size = (unsigned int)text.capacity();
      bool ret = ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->dialogKeyboard.ShowAndGetInput(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, text[0], size, allowEmptyResult, autoCloseMs);
      text.resize(size);
      text.shrink_to_fit();
      return ret;
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_DialogKeyboard
    /// @brief Shows  keyboard  and  prompts  for  a  password.   Differs  from
    /// `ShowAndVerifyNewPassword()` in that no second verification
    ///
    /// @param[out] newPassword      Overwritten with user input if return=true.
    /// @param[in] heading           String shown on dialog title.
    /// @param[in] allowEmptyResult  Whether a blank password is valid or not.
    /// @param[in] autoCloseMs       To close the dialog after a specified time,
    ///                              in milliseconds, default is  0  which keeps
    ///                              the dialog open indefinitely.
    /// @return                      true if successful display  and user input.
    ///                              false  if  unsuccessful  display,  no  user
    ///                              input, or canceled editing.
    ///
    inline bool ShowAndGetNewPassword(
      std::string&            newPassword,
      const std::string&      heading,
      bool                    allowEmptyResult,
      unsigned int            autoCloseMs = 0)
    {
      newPassword.resize(1024);
      unsigned int size = (unsigned int)newPassword.capacity();
      bool ret = ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->dialogKeyboard.ShowAndGetNewPasswordWithHead(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, newPassword[0], size, heading.c_str(), allowEmptyResult, autoCloseMs);
      newPassword.resize(size);
      newPassword.shrink_to_fit();
      return ret;
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_DialogKeyboard
    /// @brief Shows keyboard and prompts for a password. Differs from
    /// `ShowAndVerifyNewPassword()` in that no second verification
    ///
    /// @param[out] newPassword    Overwritten with user input if  return=true.
    /// @param[in] autoCloseMs     To close the dialog after a  specified  time,
    ///                            in milliseconds, default  is  0  which  keeps
    ///                            the dialog open indefinitely.
    /// @return                    true if successful display  and  user  input.
    ///                            false  if  unsuccessful  display,   no  user
    ///                            input, or canceled editing.
    ///
    inline bool ShowAndGetNewPassword(
      std::string&            newPassword,
      unsigned int            autoCloseMs = 0)
    {
      newPassword.resize(1024);
      unsigned int size = (unsigned int)newPassword.capacity();
      bool ret = ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->dialogKeyboard.ShowAndGetNewPassword(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, newPassword[0], size, autoCloseMs);
      newPassword.resize(size);
      newPassword.shrink_to_fit();
      return ret;
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_DialogKeyboard
    /// @brief Show keyboard twice to  get and confirm a  user-entered  password
    /// string.
    ///
    /// @param[out] newPassword    Overwritten with user input if return=true.
    /// @param[in] heading         String shown on dialog title.
    /// @param[in] allowEmptyResult
    /// @param[in] autoCloseMs     To close the dialog after a  specified  time,
    ///                            in milliseconds,  default  is 0  which  keeps
    ///                            the dialog open indefinitely.
    /// @return                    true if successful display  and  user  input.
    ///                            false  if  unsuccessful   display,   no  user
    ///                            input, or canceled editing.
    ///
    ///
    ///-------------------------------------------------------------------------
    ///
    /// **Example:**
    /// ~~~~~~~~~~~~~{.cpp}
    /// #include <kodi/General.h>
    /// #include <kodi/gui/DialogKeyboard.h>
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
    ///   kodi::GetMD5("kodi", password);
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
    ///     ret = ::kodi::gui::DialogKeyboard::ShowAndVerifyPassword(password, "Demo password call for PW 'kodi'", i, 0);
    ///     if (ret == 0)
    ///     {
    ///       fprintf(stderr, "Password successfull confirmed after '%i' tries\n", i+1);
    ///       break;
    ///     }
    ///     else if (ret < 0)
    ///     {
    ///       fprintf(stderr, "Canceled editing on try '%i'\n", i+1);
    ///       break;
    ///     }
    ///     else /* if (ret > 0) */
    ///     {
    ///       fprintf(stderr, "Wrong password entered on try '%i'\n", i+1);
    ///     }
    ///   }
    /// }
    /// else
    ///   fprintf(stderr, "Requested global setting value 'masterlock.maxretries' not present!");
    /// ~~~~~~~~~~~~~
    ///
    inline bool ShowAndVerifyNewPassword(
      std::string&            newPassword,
      const std::string&      heading,
      bool                    allowEmptyResult,
      unsigned int            autoCloseMs = 0)
    {
      newPassword.resize(1024);
      unsigned int size = (unsigned int)newPassword.capacity();
      bool ret = ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->dialogKeyboard.ShowAndGetNewPasswordWithHead(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, newPassword[0], size, heading.c_str(), allowEmptyResult, autoCloseMs);
      newPassword.resize(size);
      newPassword.shrink_to_fit();
      return ret;
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_DialogKeyboard
    /// @brief Show keyboard twice to get and confirm  a user-entered  password
    /// string.
    ///
    /// @param[out] newPassword    Overwritten with user input if return=true.
    /// @param[in] autoCloseMs     To close the dialog after a specified   time,
    ///                            in milliseconds, default  is  0  which  keeps
    ///                            the dialog open indefinitely.
    /// @return                    true if successful display  and  user  input.
    ///                            false  if  unsuccessful   display,   no  user
    ///                            input, or canceled editing.
    ///
    inline bool ShowAndVerifyNewPassword(
      std::string&            newPassword,
      unsigned int            autoCloseMs = 0)
    {
      newPassword.resize(1024);
      unsigned int size = (unsigned int)newPassword.capacity();
      bool ret = ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->dialogKeyboard.ShowAndVerifyNewPassword(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, newPassword[0], size, autoCloseMs);
      newPassword.resize(size);
      newPassword.shrink_to_fit();
      return ret;
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_DialogKeyboard
    /// @brief Show keyboard and verify user input against `password`.
    ///
    /// @param[out] password       Value to compare against user input.
    /// @param[in] heading         String shown on dialog title.
    /// @param[in] retries         If   greater   than   0,   shows   "Incorrect
    ///                            password,  %d retries left" on dialog line 2,
    ///                            else line 2 is blank.
    /// @param[in] autoCloseMs     To close the dialog  after a specified  time,
    ///                            in milliseconds,  default is  0  which  keeps
    ///                            the dialog open indefinitely.
    /// @return                    0 if successful display  and user input. 1 if
    ///                            unsuccessful input. -1 if no user  input  or
    ///                            canceled editing.
    ///
    inline int ShowAndVerifyPassword(
      std::string&            password,
      const std::string&      heading,
      int                     retries,
      unsigned int            autoCloseMs = 0)
    {
      password.resize(1024);
      unsigned int size = (unsigned int)password.capacity();
      int ret = ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->dialogKeyboard.ShowAndVerifyPassword(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, password[0], size, heading.c_str(), retries, autoCloseMs);
      password.resize(size);
      password.shrink_to_fit();
      return ret;
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_DialogKeyboard
    /// @brief Shows a filter related keyboard
    ///
    /// @param[out] text           Overwritten with user input if  return=true.
    /// @param[in] searching       Use dialog for  search and  send  our  search
    ///                            message in safe way (only  the active  window
    ///                            needs it)
    ///  - header name if true is "Enter search string"
    ///  - header name if false is "Enter value"
    /// @param autoCloseMs         To close the dialog after  a specified  time,
    ///                            in milliseconds, default  is  0  which  keeps
    ///                            the dialog open indefinitely.
    /// @return                    true if successful display  and  user  input.
    ///                            false   if  unsuccessful  display,   no  user
    ///                            input, or canceled editing.
    ///
    inline bool ShowAndGetFilter(
      std::string&            text,
      bool                    searching,
      unsigned int            autoCloseMs = 0)
    {
      text.resize(1024);
      unsigned int size = (unsigned int)text.capacity();
      bool ret = ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->dialogKeyboard.ShowAndGetFilter(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, text[0], size, searching, autoCloseMs);
      text.resize(size);
      text.shrink_to_fit();
      return ret;
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_DialogKeyboard
    /// @brief Send a text to a visible keyboard
    ///
    /// @param[in] text            Overwritten with user input if  return=true.
    /// @param[in] closeKeyboard   The open dialog is if also closed on 'true'.
    /// @return                    true   if    successful   done,    false   if
    ///                            unsuccessful or keyboard not present.
    ///
    inline bool SendTextToActiveKeyboard(
      const std::string&      text,
      bool                    closeKeyboard = false)
    {
      return ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->dialogKeyboard.SendTextToActiveKeyboard(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, text.c_str(), closeKeyboard);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_DialogKeyboard
    /// @brief Check for visible keyboard on GUI
    ///
    /// @return  true if keyboard present, false if not present
    ///
    inline bool IsKeyboardActivated()
    {
      return ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->dialogKeyboard.isKeyboardActivated(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase);
    }
    //--------------------------------------------------------------------------
  };

} /* namespace gui */
} /* namespace kodi */
