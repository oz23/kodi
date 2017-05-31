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
  /// \defgroup cpp_kodi_gui_CControlSpin Control Spin
  /// \ingroup cpp_kodi_gui
  /// @brief \cpp_class{ kodi::gui::CControlSpin }
  /// **Window control used for cycling up/down controls**
  ///
  /// The settings spin control is used in the settings  screens for when a list
  /// of options  can be chosen  from using  up/down arrows.  You can choose the
  /// position,  size,  and look of  the spin control.  It is basically  a cross
  /// between  the button  control and a spin control.  It has a label and focus
  /// and non focus textures, as well as a spin control on the right.
  ///
  /// It has the header \ref ControlSpin.h "#include <kodi/gui/ControlSpin.h>"
  /// be included to enjoy it.
  ///
  /// Here you find the needed skin part for a \ref Spin_Control "spin control"
  ///
  /// @note The  call of  the  control is  only possible from  the corresponding
  /// window as its class and identification number is required.
  ///


  //============================================================================
  ///
  /// \ingroup cpp_kodi_gui_CControlSpin
  /// @anchor AddonGUISpinControlType
  /// @brief The values here defines the used value format for steps on
  /// spin control.
  ///
  typedef enum AddonGUISpinControlType
  {
    /// One spin step interpreted as integer
    ADDON_SPIN_CONTROL_TYPE_INT    = 1,
    /// One spin step interpreted as floating point value
    ADDON_SPIN_CONTROL_TYPE_FLOAT  = 2,
    /// One spin step interpreted as text string
    ADDON_SPIN_CONTROL_TYPE_TEXT   = 3,
    /// One spin step interpreted as a page change value
    ADDON_SPIN_CONTROL_TYPE_PAGE   = 4
  } AddonGUISpinControlType;
  //----------------------------------------------------------------------------

  class CControlSpin
  {
  public:
    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlSpin
    /// @brief Construct a new control
    ///
    /// @param[in] window               related window control class
    /// @param[in] controlId            Used skin xml control id
    ///
    CControlSpin(CWindow* window, int controlId)
      : m_Window(window),
        m_ControlId(controlId)
    {
      m_ControlHandle = ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->window.GetControl_Spin(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_Window->m_WindowHandle, controlId);
      if (!m_ControlHandle)
        kodi::Log(ADDON_LOG_FATAL, "kodi::gui::CControlSpin can't create control class from Kodi !!!");
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlSpin
    /// @brief Destructor
    ///
    virtual ~CControlSpin() { }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlSpin
    /// @brief Set the control on window to visible
    ///
    /// @param[in] visible              If true visible, otherwise hidden
    ///
    void SetVisible(bool visible)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->controlSpin.SetVisible(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ControlHandle, visible);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlSpin
    /// @brief Set's the control's enabled/disabled state
    ///
    /// @param[in] enabled              If true enabled, otherwise disabled
    ///
    void SetEnabled(bool enabled)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->controlSpin.SetEnabled(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ControlHandle, enabled);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlSpin
    /// @brief To set the text string on spin control
    ///
    /// @param[in] text                Text to show as name for spin
    ///
    void SetText(const std::string& text)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->controlSpin.SetText(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ControlHandle, text.c_str());
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlSpin
    /// @brief To reset spin control to defaults
    ///
    void Reset()
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->controlSpin.Reset(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ControlHandle);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlSpin
    /// @brief To set the with SpinControlType defined types of spin.
    ///
    /// @param[in] type                 The type to use
    ///
    /// @note See description of \ref AddonGUISpinControlType for available types.
    ///
    void SetType(AddonGUISpinControlType type)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->controlSpin.SetType(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ControlHandle, (int)type);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlSpin
    /// @brief To add a label entry in spin defined with a value as string.
    ///
    /// Format must be set to ADDON_SPIN_CONTROL_TYPE_TEXT to use this function.
    ///
    /// @param[in] label                Label string to view on skin
    /// @param[in] value                String value to use for selection
    ///                                 of them.
    ///
    void AddLabel(const std::string& label, const std::string& value)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->controlSpin.AddStringLabel(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ControlHandle, label.c_str(), value.c_str());
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlSpin
    /// @brief To add a label entry in spin defined with a value as integer.
    ///
    /// Format must be set to ADDON_SPIN_CONTROL_TYPE_INT to use this function.
    ///
    /// @param[in] label                Label string to view on skin
    /// @param[in] value                Integer value to use for selection
    ///                                 of them.
    ///
    void AddLabel(const std::string& label, int value)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->controlSpin.AddIntLabel(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ControlHandle, label.c_str(), value);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlSpin
    /// @brief To change the spin to position with them string as value.
    ///
    /// Format must be set to ADDON_SPIN_CONTROL_TYPE_TEXT to use this function.
    ///
    /// @param[in] value                 String value to change to
    ///
    void SetStringValue(const std::string& value)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->controlSpin.SetStringValue(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ControlHandle, value.c_str());
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlSpin
    /// @brief To get the current spin control position with text string value.
    ///
    /// Format must be set to ADDON_SPIN_CONTROL_TYPE_TEXT to use this function.
    ///
    /// @return                         Currently selected string value
    ///
    std::string GetStringValue() const
    {
      std::string text;
      text.resize(1024);
      unsigned int size = (unsigned int)text.capacity();
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->controlSpin.GetStringValue(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ControlHandle, text[0], size);
      text.resize(size);
      text.shrink_to_fit();
      return text;
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlSpin
    /// @brief To set the the range as integer of slider, e.g. -10 is the slider
    /// start and e.g. +10 is the from here defined position where it reach  the
    /// end.
    ///
    /// Ad default is the range from 0 to 100.
    ///
    /// @param[in] start                Integer start value
    /// @param[in] end                  Integer end value
    ///
    /// @note Percent, floating point or  integer are alone possible.  Combining
    /// these  different  values  can be not together and can,  therefore,  only
    /// one each can be used and must be defined with \ref SetType before.
    ///
    void SetIntRange(int start, int end)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->controlSpin.SetIntRange(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ControlHandle, start, end);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlSpin
    /// @brief Set the slider  position with the given integer value.  The Range
    /// must be defined with a call from \ref SetIntRange before.
    ///
    /// @param[in] value                Position in range to set with integer
    ///
    /// @note Percent, floating point or  integer are alone possible.  Combining
    /// these different  values can  be not  together  and can, therefore,  only
    /// one each can be used and must be defined with \ref SetType before.
    ///
    void SetIntValue(int value)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->controlSpin.SetIntValue(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ControlHandle, value);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlSpin
    /// @brief To get the current position as integer value.
    ///
    /// @return                         The position as integer
    ///
    /// @note Percent,  floating point or integer are alone possible.  Combining
    /// these different values  can be not  together  and can,  therefore,  only
    /// one each can be used and must be defined with \ref SetType before.
    ///
    int GetIntValue() const
    {
      return ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->controlSpin.GetIntValue(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ControlHandle);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlSpin
    /// @brief To set the  the range as  float of spin,  e.g. -25.0 is  the spin
    /// start and e.g. +25.0 is the from  here defined  position where  it reach
    /// the end.
    ///
    /// As default is the range 0.0 to 1.0.
    ///
    /// The float interval is as default 0.1 and can be changed with
    /// @ref SetFloatInterval.
    ///
    /// @param[in] start                Integer start value
    /// @param[in] end                  Integer end value
    ///
    /// @note Percent, floating point  or integer are alone possible.  Combining
    /// these different  values can be  not together  and can,  therefore,  only
    /// one each can be used and must be defined with \ref SetType before.
    ///
    void SetFloatRange(float start, float end)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->controlSpin.SetFloatRange(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ControlHandle, start, end);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlSpin
    /// @brief Set  the spin  position with  the given float  value.  The  Range
    /// can be defined with a call from  \ref SetIntRange before, as  default it
    /// is 0.0 to 1.0.
    ///
    /// @param[in] value                Position in range to set with float
    ///
    /// @note Percent, floating point or integer are  alone possible.  Combining
    /// these different  values can  be not together  and can,  therefore,  only
    /// one each can be used and must be defined with \ref SetType before.
    ///
    void SetFloatValue(float value)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->controlSpin.SetFloatValue(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ControlHandle, value);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlSpin
    /// @brief To get the current position as float value.
    ///
    /// @return                         The position as float
    ///
    float GetFloatValue() const
    {
      return ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->controlSpin.GetFloatValue(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ControlHandle);
    }
    //--------------------------------------------------------------------------

    //==========================================================================
    ///
    /// \ingroup cpp_kodi_gui_CControlSpin
    /// @brief To set the  interval steps of spin,  as default  is it 0.1  If it
    /// becomes  changed  with this  function will  a step of the  user with the
    /// value fixed here be executed.
    ///
    /// @param[in] interval             Intervall step to set.
    ///
    /// @note Percent, floating point  or integer are alone possible.  Combining
    /// these  different values  can  be not together and can,  therefore,  only
    /// one each can be used and must be defined with \ref SetType before.
    ///
    void SetFloatInterval(float interval)
    {
      ::kodi::addon::CAddonBase::m_interface->toKodi->kodi_gui->controlSpin.SetFloatInterval(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase, m_ControlHandle, interval);
    }
    //--------------------------------------------------------------------------

  private:
    CWindow* m_Window;
    int m_ControlId;
    void* m_ControlHandle;
  };

} /* namespace gui */
} /* namespace kodi */
