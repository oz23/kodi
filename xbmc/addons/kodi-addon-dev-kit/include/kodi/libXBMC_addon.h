#pragma once
/*
 *      Copyright (C) 2005-2013 Team XBMC
 *      http://xbmc.org
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
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include <string>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>

#include "versions.h"
#if defined(BUILD_KODI_ADDON)
#include "IFileTypes.h"
#else
#include "filesystem/IFileTypes.h"
#endif

struct VFSDirEntry;
struct __stat64;

#ifdef _WIN32                   // windows
#ifndef _SSIZE_T_DEFINED
typedef intptr_t      ssize_t;
#define _SSIZE_T_DEFINED
#endif // !_SSIZE_T_DEFINED

#if defined(BUILD_KODI_ADDON)
#include "p8-platform/windows/dlfcn-win32.h"
#endif
#else // windows
#include <dlfcn.h>              // linux+osx
#endif

#ifdef LOG_DEBUG
#undef LOG_DEBUG
#endif
#ifdef LOG_INFO
#undef LOG_INFO
#endif
#ifdef LOG_NOTICE
#undef LOG_NOTICE
#endif
#ifdef LOG_ERROR
#undef LOG_ERROR
#endif

typedef void* (*KODIAddOnLib_RegisterMe)(void *addonData);
typedef void (*KODIAddOnLib_UnRegisterMe)(void *addonData, void *cbTable);
typedef void* (*KODIAudioEngineLib_RegisterMe)(void *addonData);
typedef void (*KODIAudioEngineLib_UnRegisterMe)(void *addonData, void *cbTable);
typedef void* (*KODIGUILib_RegisterMe)(void *addonData);
typedef void (*KODIGUILib_UnRegisterMe)(void *addonData, void *cbTable);
typedef void* (*KODIPVRLib_RegisterMe)(void *addonData);
typedef void (*KODIPVRLib_UnRegisterMe)(void *addonData, void *cbTable);
typedef void* (*KODIADSPLib_RegisterMe)(void *addonData);
typedef void (*KODIADSPLib_UnRegisterMe)(void *addonData, void *cbTable);
typedef void* (*KODICodecLib_RegisterMe)(void *addonData);
typedef void (*KODICodecLib_UnRegisterMe)(void *addonData, void *cbTable);
typedef void* (*KODIINPUTSTREAMLib_RegisterMe)(void *addonData);
typedef void (*KODIINPUTSTREAMLib_UnRegisterMe)(void *addonData, void *cbTable);
typedef void* (*KODIGameLib_RegisterMe)(void *addonData);
typedef void (*KODIGameLib_UnRegisterMe)(void *addonData, void *cbTable);

typedef struct AddonCB
{
  const char* libBasePath;  ///< Never, never change this!!!
  void*       addonData;
  KODIAddOnLib_RegisterMe           AddOnLib_RegisterMe;
  KODIAddOnLib_UnRegisterMe         AddOnLib_UnRegisterMe;
  KODIAudioEngineLib_RegisterMe     AudioEngineLib_RegisterMe;
  KODIAudioEngineLib_UnRegisterMe   AudioEngineLib_UnRegisterMe;
  KODICodecLib_RegisterMe           CodecLib_RegisterMe;
  KODICodecLib_UnRegisterMe         CodecLib_UnRegisterMe;
  KODIGUILib_RegisterMe             GUILib_RegisterMe;
  KODIGUILib_UnRegisterMe           GUILib_UnRegisterMe;
  KODIPVRLib_RegisterMe             PVRLib_RegisterMe;
  KODIPVRLib_UnRegisterMe           PVRLib_UnRegisterMe;
  KODIADSPLib_RegisterMe            ADSPLib_RegisterMe;
  KODIADSPLib_UnRegisterMe          ADSPLib_UnRegisterMe;
  KODIINPUTSTREAMLib_RegisterMe     INPUTSTREAMLib_RegisterMe;
  KODIINPUTSTREAMLib_UnRegisterMe   INPUTSTREAMLib_UnRegisterMe;
  KODIGameLib_RegisterMe            GameLib_RegisterMe;
  KODIGameLib_UnRegisterMe          GameLib_UnRegisterMe;
} AddonCB;

namespace ADDON
{
  typedef enum addon_log
  {
    LOG_DEBUG,
    LOG_INFO,
    LOG_NOTICE,
    LOG_ERROR
  } addon_log_t;

  typedef enum queue_msg
  {
    QUEUE_INFO,
    QUEUE_WARNING,
    QUEUE_ERROR
  } queue_msg_t;
}

namespace KodiAPI
{
namespace AddOn
{
typedef struct CB_AddOn
{
  void (*Log)(void *addonData, const ADDON::addon_log_t loglevel, const char *msg);
  void (*QueueNotification)(void *addonData, const ADDON::queue_msg_t type, const char *msg);
  bool (*WakeOnLan)(const char* mac);
  bool (*GetSetting)(void *addonData, const char *settingName, void *settingValue);
  char* (*TranslateSpecialProtocol)(const char *strSource);
  char* (*UnknownToUTF8)(const char *sourceDest);
  char* (*GetLocalizedString)(const void* addonData, long dwCode);
  char* (*GetDVDMenuLanguage)(const void* addonData);
  void (*FreeString)(const void* addonData, char* str);
} CB_AddOnLib;

} /* namespace AddOn */
} /* namespace KodiAPI */

namespace ADDON
{
  class CHelper_libXBMC_addon
  {
  public:
    CHelper_libXBMC_addon()
    {
      m_Handle = nullptr;
      m_Callbacks = nullptr;
    }

    ~CHelper_libXBMC_addon()
    {
      if (m_Handle && m_Callbacks)
      {
        m_Handle->AddOnLib_UnRegisterMe(m_Handle->addonData, m_Callbacks);
      }
    }

    bool RegisterMe(void *handle)
    {
      m_Handle = static_cast<AddonCB*>(handle);
      if (m_Handle)
        m_Callbacks = (KodiAPI::AddOn::CB_AddOnLib*)m_Handle->AddOnLib_RegisterMe(m_Handle->addonData);
      if (!m_Callbacks)
        fprintf(stderr, "libXBMC_addon-ERROR: AddOnLib_RegisterMe can't get callback table from Kodi !!!\n");
    
      return m_Callbacks != nullptr;
    }

    /*!
     * @brief Add a message to XBMC's log.
     * @param loglevel The log level of the message.
     * @param format The format of the message to pass to XBMC.
     */
    void Log(const addon_log_t loglevel, const char *format, ... )
    {
      char buffer[16384];
      va_list args;
      va_start (args, format);
      vsprintf (buffer, format, args);
      va_end (args);
      m_Callbacks->Log(m_Handle->addonData, loglevel, buffer);
    }

    /*!
     * @brief Get a settings value for this add-on.
     * @param settingName The name of the setting to get.
     * @param settingValue The value.
     * @return True if the settings was fetched successfully, false otherwise.
     */
    bool GetSetting(const char* settingName, void *settingValue)
    {
      return m_Callbacks->GetSetting(m_Handle->addonData, settingName, settingValue);
    }

    /*!
    * @brief Translates a special protocol folder.
    * @param source The file / folder to translate.
    * @return The string translated to resolved path. Must be freed by calling FreeString() when done.
    */
    char *TranslateSpecialProtocol(const char *source)
    {
      return m_Callbacks->TranslateSpecialProtocol(source);
    }

    /*!
     * @brief Queue a notification in the GUI.
     * @param type The message type.
     * @param format The format of the message to pass to display in XBMC.
     */
    void QueueNotification(const queue_msg_t type, const char *format, ... )
    {
      char buffer[16384];
      va_list args;
      va_start (args, format);
      vsprintf (buffer, format, args);
      va_end (args);
      m_Callbacks->QueueNotification(m_Handle->addonData, type, buffer);
    }

    /*!
     * @brief Send WakeOnLan magic packet.
     * @param mac Network address of the host to wake.
     * @return True if the magic packet was successfully sent, false otherwise.
     */
    bool WakeOnLan(const char* mac)
    {
      return m_Callbacks->WakeOnLan(mac);
    }

    /*!
     * @brief Translate a string with an unknown encoding to UTF8.
     * @param str The string to translate.
     * @return The string translated to UTF8. Must be freed by calling FreeString() when done.
     */
    char* UnknownToUTF8(const char* str)
    {
      return m_Callbacks->UnknownToUTF8(str);
    }

    /*!
     * @brief Get a localised message.
     * @param dwCode The code of the message to get.
     * @return The message. Must be freed by calling FreeString() when done.
     */
    char* GetLocalizedString(int dwCode)
    {
      return m_Callbacks->GetLocalizedString(m_Handle->addonData, dwCode);
    }

    /*!
     * @brief Get the DVD menu language.
     * @return The language. Must be freed by calling FreeString() when done.
     */
    char* GetDVDMenuLanguage()
    {
      return m_Callbacks->GetDVDMenuLanguage(m_Handle->addonData);
    }

    /*!
     * @brief Free the memory used by str
     * @param str The string to free
     */
    void FreeString(char* str)
    {
      m_Callbacks->FreeString(m_Handle->addonData, str);
    }

  private:
    AddonCB* m_Handle;
    KodiAPI::AddOn::CB_AddOnLib *m_Callbacks;
  };
};
