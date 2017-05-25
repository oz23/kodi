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

/*
 * Parts with a comment named "internal" are only used inside header and not
 * used or accessed direct during add-on development!
 */

#include "../AddonBase.h"

namespace kodi { namespace addon { class CInstanceVisualization; }}

extern "C"
{

typedef enum VIS_ACTION /* internal */
{ 
  VIS_ACTION_NONE = 0,
  VIS_ACTION_NEXT_PRESET,
  VIS_ACTION_PREV_PRESET,
  VIS_ACTION_LOAD_PRESET,
  VIS_ACTION_RANDOM_PRESET,
  VIS_ACTION_LOCK_PRESET,
  VIS_ACTION_RATE_PRESET_PLUS,
  VIS_ACTION_RATE_PRESET_MINUS,
  VIS_ACTION_UPDATE_ALBUMART,
  VIS_ACTION_UPDATE_TRACK
} VIS_ACTION;

struct VIS_INFO /* internal */
{
  bool bWantsFreq;
  int iSyncDelay;
};

typedef struct AddonProps_Visualization /* internal */
{
  void *device;
  int x;
  int y;
  int width;
  int height;
  float pixelRatio;
  const char *name;
  const char *presets;
  const char *profile;
} AddonProps_Visualization;

typedef struct AddonToKodiFuncTable_Visualization /* internal */
{
  KODI_HANDLE kodiInstance;
  void (__cdecl* transfer_preset) (void* kodiInstance, const char* preset);
} AddonToKodiFuncTable_Visualization;

struct AddonInstance_Visualization;

typedef struct KodiToAddonFuncTable_Visualization /* internal */
{
  kodi::addon::CInstanceVisualization* addonInstance;

  bool (__cdecl* Start)(AddonInstance_Visualization* addonInstance, int channels, int samplesPerSec, int bitsPerSample, const char* songName);
  void (__cdecl* Stop)(AddonInstance_Visualization* addonInstance);
  void (__cdecl* AudioData)(AddonInstance_Visualization* addonInstance, const float* audioData, int audioDataLength, float *freqData, int freqDataLength);
  bool (__cdecl* IsDirty) (AddonInstance_Visualization* addonInstance);
  void (__cdecl* Render) (AddonInstance_Visualization* addonInstance);
  void (__cdecl* GetInfo)(AddonInstance_Visualization* addonInstance, VIS_INFO *info);
  bool (__cdecl* OnAction)(AddonInstance_Visualization* addonInstance, VIS_ACTION action, const void *param);
  bool (__cdecl* HasPresets)(AddonInstance_Visualization* addonInstance);
  unsigned int (__cdecl *GetPresets)(AddonInstance_Visualization* addonInstance);
  unsigned int (__cdecl *GetPreset)(AddonInstance_Visualization* addonInstance);
  unsigned int (__cdecl *GetSubModules)(AddonInstance_Visualization* addonInstance, char ***modules);
  bool (__cdecl* IsLocked)(AddonInstance_Visualization* addonInstance);
} KodiToAddonFuncTable_Visualization;

typedef struct AddonInstance_Visualization /* internal */
{
  AddonProps_Visualization props;
  AddonToKodiFuncTable_Visualization toKodi;
  KodiToAddonFuncTable_Visualization toAddon;
} AddonInstance_Visualization;

} /* extern "C" */

namespace kodi
{
namespace addon
{

  class VisTrack
  {
  public:
    VisTrack()
    {
      title = artist = album = albumArtist = nullptr;
      genre = comment = lyrics = reserved1 = reserved2 = nullptr;
      trackNumber = discNumber = duration = year = 0;
      rating = 0;
      reserved3 = reserved4 = 0;
    }

    const char *title;
    const char *artist;
    const char *album;
    const char *albumArtist;
    const char *genre;
    const char *comment;
    const char *lyrics;
    const char *reserved1;
    const char *reserved2;

    int trackNumber;
    int discNumber;
    int duration;
    int year;
    char rating;
    int reserved3;
    int reserved4;
  };

  class CInstanceVisualization : public IAddonInstance
  {
  public:
    CInstanceVisualization()
      : IAddonInstance(ADDON_INSTANCE_VISUALIZATION),
        m_presetLockedByUser(false)
    {
      if (CAddonBase::m_interface->globalSingleInstance != nullptr)
        throw std::logic_error("kodi::addon::CInstanceVisualization: Creation of more as one in single instance way is not allowed!");

      SetAddonStruct(CAddonBase::m_interface->firstKodiInstance);
      CAddonBase::m_interface->globalSingleInstance = this;
    }

    CInstanceVisualization(KODI_HANDLE instance)
      : IAddonInstance(ADDON_INSTANCE_VISUALIZATION),
        m_presetLockedByUser(false)
    {
      if (CAddonBase::m_interface->globalSingleInstance != nullptr)
        throw std::logic_error("kodi::addon::CInstanceVisualization: Creation of multiple together with single instance way is not allowed!");

      SetAddonStruct(instance);
    }

    virtual ~CInstanceVisualization() { }

    virtual bool Start(int channels, int samplesPerSec, int bitsPerSample, std::string songName) { return true; }
    virtual void Stop() {}
    virtual void AudioData(const float* audioData, int audioDataLength, float* freqData, int freqDataLength) {}
    virtual bool IsDirty() { return true; }
    virtual void Render() {}
    virtual void GetInfo(bool& wantsFreq, int& syncDelay) { wantsFreq = false; syncDelay = 0; }
    virtual bool HasPresets() { return false; }
    virtual bool GetPresets(std::vector<std::string>& presets) { return false; }
    virtual unsigned int GetPreset() { return 0; }
    virtual bool IsLocked() { return false; }
    virtual bool PrevPreset() { return false; }
    virtual bool NextPreset() { return false; }
    virtual bool LoadPreset(int select) { return false; }
    virtual bool RandomPreset() { return false; }
    virtual bool LockPreset(bool lockUnlock) { return false; }
    virtual bool RatePreset(bool plusMinus) { return false; }
    virtual bool UpdateAlbumart(std::string albumart) { return false; }
    virtual bool UpdateTrack(const kodi::addon::VisTrack &track) { return false; }

    inline void* Device() { return m_instanceData->props.device; }
    inline int X() { return m_instanceData->props.x; }
    inline int Y() { return m_instanceData->props.y; }
    inline int Width() { return m_instanceData->props.width; }
    inline int Height() { return m_instanceData->props.height; }
    inline float PixelRatio() { return m_instanceData->props.pixelRatio; }
    inline std::string Name() { return m_instanceData->props.name; }
    inline std::string Presets() { return m_instanceData->props.presets; }
    inline std::string Profile() { return m_instanceData->props.profile; }

  private:
    void SetAddonStruct(KODI_HANDLE instance)
    {
      if (instance == nullptr)
        throw std::logic_error("kodi::addon::CInstanceVisualization: Creation with empty addon structure not allowed, table must be given from Kodi!");

      m_instanceData = static_cast<AddonInstance_Visualization*>(instance);
      m_instanceData->toAddon.addonInstance = this;
      m_instanceData->toAddon.Start = ADDON_Start;
      m_instanceData->toAddon.Stop = ADDON_Stop;
      m_instanceData->toAddon.AudioData = ADDON_AudioData;
      m_instanceData->toAddon.Render = ADDON_Render;
      m_instanceData->toAddon.GetInfo = ADDON_GetInfo;
      m_instanceData->toAddon.OnAction = ADDON_OnAction;
      m_instanceData->toAddon.HasPresets = ADDON_HasPresets;
      m_instanceData->toAddon.GetPresets = ADDON_GetPresets;
      m_instanceData->toAddon.GetPreset = ADDON_GetPreset;
      m_instanceData->toAddon.IsLocked = ADDON_IsLocked;
    }

    inline static bool ADDON_Start(AddonInstance_Visualization* addonInstance, int channels, int samplesPerSec, int bitsPerSample, const char* songName)
    {
      return addonInstance->toAddon.addonInstance->Start(channels, samplesPerSec, bitsPerSample, songName);
    }

    inline static void ADDON_Stop(AddonInstance_Visualization* addonInstance)
    {
      addonInstance->toAddon.addonInstance->Stop();
    }

    inline static void ADDON_AudioData(AddonInstance_Visualization* addonInstance, const float* audioData, int audioDataLength, float *freqData, int freqDataLength)
    {
      addonInstance->toAddon.addonInstance->AudioData(audioData, audioDataLength, freqData, freqDataLength);
    }

    inline static bool ADDON_IsDirty(AddonInstance_Visualization* addonInstance)
    {
      return addonInstance->toAddon.addonInstance->IsDirty();
    }

    inline static void ADDON_Render(AddonInstance_Visualization* addonInstance)
    {
      addonInstance->toAddon.addonInstance->Render();
    }

    inline static void ADDON_GetInfo(AddonInstance_Visualization* addonInstance, VIS_INFO *info)
    {
      addonInstance->toAddon.addonInstance->GetInfo(info->bWantsFreq, info->iSyncDelay);
    }

    inline static bool ADDON_OnAction(AddonInstance_Visualization* addonInstance, VIS_ACTION action, const void *param)
    {
      switch (action)
      {
        case VIS_ACTION_NEXT_PRESET:
          return addonInstance->toAddon.addonInstance->NextPreset();
        case VIS_ACTION_PREV_PRESET:
          return addonInstance->toAddon.addonInstance->PrevPreset();
        case VIS_ACTION_LOAD_PRESET:
          return addonInstance->toAddon.addonInstance->LoadPreset(*(int*)param);
        case VIS_ACTION_RANDOM_PRESET:
          return addonInstance->toAddon.addonInstance->RandomPreset();
        case VIS_ACTION_LOCK_PRESET:
          addonInstance->toAddon.addonInstance->m_presetLockedByUser = !addonInstance->toAddon.addonInstance->m_presetLockedByUser;
          return addonInstance->toAddon.addonInstance->LockPreset(addonInstance->toAddon.addonInstance->m_presetLockedByUser);
        case VIS_ACTION_RATE_PRESET_PLUS:
          return addonInstance->toAddon.addonInstance->RatePreset(true);
        case VIS_ACTION_RATE_PRESET_MINUS:
          return addonInstance->toAddon.addonInstance->RatePreset(false);
        case VIS_ACTION_UPDATE_ALBUMART:
          return addonInstance->toAddon.addonInstance->UpdateAlbumart(static_cast<const char*>(param));
        case VIS_ACTION_UPDATE_TRACK:
          return addonInstance->toAddon.addonInstance->UpdateTrack(*static_cast<const VisTrack*>(param));
        case VIS_ACTION_NONE:
        default:
          break;
      }
      return false;
    }

    inline static bool ADDON_HasPresets(AddonInstance_Visualization* addonInstance)
    {
      return addonInstance->toAddon.addonInstance->HasPresets();
    }

    inline static unsigned int ADDON_GetPresets(AddonInstance_Visualization* addonInstance)
    {
      AddonInstance_Visualization* addon = addonInstance;
      std::vector<std::string> presets;
      if (addonInstance->toAddon.addonInstance->GetPresets(presets))
      {
        for (auto it : presets)
          addonInstance->toKodi.transfer_preset(addonInstance->toKodi.kodiInstance, it.c_str());
      }

      return presets.size();
    }

    inline static unsigned int ADDON_GetPreset(AddonInstance_Visualization* addonInstance)
    {
      return addonInstance->toAddon.addonInstance->GetPreset();
    }

    inline static bool ADDON_IsLocked(AddonInstance_Visualization* addonInstance)
    {
      return addonInstance->toAddon.addonInstance->IsLocked();
    }

    bool m_presetLockedByUser;
    AddonInstance_Visualization* m_instanceData;
  };

} /* namespace addon */
} /* namespace kodi */
