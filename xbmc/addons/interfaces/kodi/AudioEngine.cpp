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

#include "AudioEngine.h"

#include "ServiceBroker.h"
#include "addons/kodi-addon-dev-kit/include/kodi/General.h"
#include "cores/AudioEngine/Interfaces/AE.h"
#include "cores/AudioEngine/Interfaces/AEStream.h"
#include "cores/AudioEngine/Utils/AEChannelData.h"
#include "utils/log.h"

using namespace kodi; // addon-dev-kit namespace
using namespace kodi::audioengine; // addon-dev-kit namespace

namespace ADDON
{

void Interface_AudioEngine::Init(AddonGlobalInterface* funcTable)
{
  funcTable->toKodi.kodi_audioengine = (AddonToKodiFuncTable_kodi_audioengine*)malloc(sizeof(AddonToKodiFuncTable_kodi_audioengine));

  // write KODI audio DSP specific add-on function addresses to callback table
  funcTable->toKodi.kodi_audioengine->MakeStream = AudioEngine_MakeStream;
  funcTable->toKodi.kodi_audioengine->FreeStream = AudioEngine_FreeStream;
  funcTable->toKodi.kodi_audioengine->GetCurrentSinkFormat = AudioEngine_GetCurrentSinkFormat;

  // AEStream add-on function callback table
  funcTable->toKodi.kodi_audioengine->AEStream_GetSpace = AEStream_GetSpace;
  funcTable->toKodi.kodi_audioengine->AEStream_AddData = AEStream_AddData;
  funcTable->toKodi.kodi_audioengine->AEStream_GetDelay = AEStream_GetDelay;
  funcTable->toKodi.kodi_audioengine->AEStream_IsBuffering = AEStream_IsBuffering;
  funcTable->toKodi.kodi_audioengine->AEStream_GetCacheTime = AEStream_GetCacheTime;
  funcTable->toKodi.kodi_audioengine->AEStream_GetCacheTotal = AEStream_GetCacheTotal;
  funcTable->toKodi.kodi_audioengine->AEStream_Pause = AEStream_Pause;
  funcTable->toKodi.kodi_audioengine->AEStream_Resume = AEStream_Resume;
  funcTable->toKodi.kodi_audioengine->AEStream_Drain = AEStream_Drain;
  funcTable->toKodi.kodi_audioengine->AEStream_IsDraining = AEStream_IsDraining;
  funcTable->toKodi.kodi_audioengine->AEStream_IsDrained = AEStream_IsDrained;
  funcTable->toKodi.kodi_audioengine->AEStream_Flush = AEStream_Flush;
  funcTable->toKodi.kodi_audioengine->AEStream_GetVolume = AEStream_GetVolume;
  funcTable->toKodi.kodi_audioengine->AEStream_SetVolume = AEStream_SetVolume;
  funcTable->toKodi.kodi_audioengine->AEStream_GetAmplification = AEStream_GetAmplification;
  funcTable->toKodi.kodi_audioengine->AEStream_SetAmplification = AEStream_SetAmplification;
  funcTable->toKodi.kodi_audioengine->AEStream_GetFrameSize = AEStream_GetFrameSize;
  funcTable->toKodi.kodi_audioengine->AEStream_GetChannelCount = AEStream_GetChannelCount;
  funcTable->toKodi.kodi_audioengine->AEStream_GetSampleRate = AEStream_GetSampleRate;
  funcTable->toKodi.kodi_audioengine->AEStream_GetDataFormat = AEStream_GetDataFormat;
  funcTable->toKodi.kodi_audioengine->AEStream_GetResampleRatio = AEStream_GetResampleRatio;
  funcTable->toKodi.kodi_audioengine->AEStream_SetResampleRatio = AEStream_SetResampleRatio;
}

void Interface_AudioEngine::DeInit(AddonGlobalInterface* funcTable)
{
  if (funcTable->toKodi.kodi_audioengine)
  {
    free(funcTable->toKodi.kodi_audioengine);
    funcTable->toKodi.kodi_audioengine = nullptr;
  }
}

AEStreamHandle* Interface_AudioEngine::AudioEngine_MakeStream(AudioEngineFormat StreamFormat, unsigned int options)
{
  AEAudioFormat format;
  format.m_dataFormat = StreamFormat.m_dataFormat;
  format.m_sampleRate = StreamFormat.m_sampleRate;
  format.m_channelLayout = StreamFormat.m_channels;

  /* Translate addon options to kodi's options */
  int kodiOption = 0;
  if (options & AUDIO_STREAM_FORCE_RESAMPLE)
    kodiOption |= AESTREAM_FORCE_RESAMPLE;
  if (options & AUDIO_STREAM_PAUSED)
    kodiOption |= AESTREAM_PAUSED;
  if (options & AUDIO_STREAM_AUTOSTART)
    kodiOption |= AESTREAM_AUTOSTART;
  if (options & AUDIO_STREAM_BYPASS_ADSP)
    kodiOption |= AESTREAM_BYPASS_ADSP;

  return CServiceBroker::GetActiveAE().MakeStream(format, kodiOption);
}

void Interface_AudioEngine::AudioEngine_FreeStream(AEStreamHandle *handle)
{
  if (!handle)
  {
    CLog::Log(LOGERROR, "Interface_AudioEngine::%s - invalid stream data", __FUNCTION__);
    return;
  }

  CServiceBroker::GetActiveAE().FreeStream(static_cast<IAEStream*>(handle));
}

bool Interface_AudioEngine::AudioEngine_GetCurrentSinkFormat(void *kodiInstance, AudioEngineFormat *format)
{
  if (!kodiInstance || !format)
  {
    CLog::Log(LOGERROR, "Interface_AudioEngine::%s - invalid input data!", __FUNCTION__);
    return false;
  }

  AEAudioFormat sinkFormat;
  if (!CServiceBroker::GetActiveAE().GetCurrentSinkFormat(sinkFormat))
  {
    CLog::Log(LOGERROR, "Interface_AudioEngine::%s - failed to get current sink format from AE!", __FUNCTION__);
    return false;
  }

  format->m_channelCount = sinkFormat.m_channelLayout.Count();
  for (unsigned int ch = 0; ch < format->m_channelCount; ch++)
  {
    format->m_channels[ch] = sinkFormat.m_channelLayout[ch];
  }

  format->m_dataFormat = sinkFormat.m_dataFormat;
  format->m_sampleRate = sinkFormat.m_sampleRate;
  format->m_frames = sinkFormat.m_frames;
  format->m_frameSize = sinkFormat.m_frameSize;

  return true;
}

unsigned int Interface_AudioEngine::AEStream_GetSpace(void *kodiInstance, AEStreamHandle *handle)
{
  if (!kodiInstance || !handle)
  {
    CLog::Log(LOGERROR, "Interface_AudioEngine::%s - invalid stream data", __FUNCTION__);
    return 0;
  }

  return static_cast<IAEStream*>(handle)->GetSpace();
}

unsigned int Interface_AudioEngine::AEStream_AddData(void *kodiInstance, AEStreamHandle *handle, uint8_t* const *Data, unsigned int Offset, unsigned int Frames)
{
  if (!kodiInstance || !handle)
  {
    CLog::Log(LOGERROR, "Interface_AudioEngine::%s - invalid stream data", __FUNCTION__);
    return 0;
  }

  return static_cast<IAEStream*>(handle)->AddData(Data, Offset, Frames);
}

double Interface_AudioEngine::AEStream_GetDelay(void *kodiInstance, AEStreamHandle *handle)
{
  if (!kodiInstance || !handle)
  {
    CLog::Log(LOGERROR, "Interface_AudioEngine::%s - invalid stream data", __FUNCTION__);
    return -1.0;
  }

  return static_cast<IAEStream*>(handle)->GetDelay();
}

bool Interface_AudioEngine::AEStream_IsBuffering(void *kodiInstance, AEStreamHandle *handle)
{
  if (!kodiInstance || !handle)
  {
    CLog::Log(LOGERROR, "Interface_AudioEngine::%s - invalid stream data", __FUNCTION__);
    return false;
  }

  return static_cast<IAEStream*>(handle)->IsBuffering();
}

double Interface_AudioEngine::AEStream_GetCacheTime(void *kodiInstance, AEStreamHandle *handle)
{
  if (!kodiInstance || !handle)
  {
    CLog::Log(LOGERROR, "Interface_AudioEngine::%s - invalid stream data", __FUNCTION__);
    return -1.0;
  }

  return static_cast<IAEStream*>(handle)->GetCacheTime();
}

double Interface_AudioEngine::AEStream_GetCacheTotal(void *kodiInstance, AEStreamHandle *handle)
{
  if (!kodiInstance || !handle)
  {
    CLog::Log(LOGERROR, "Interface_AudioEngine::%s - invalid stream data", __FUNCTION__);
    return -1.0;
  }

  return static_cast<IAEStream*>(handle)->GetCacheTotal();
}

void Interface_AudioEngine::AEStream_Pause(void *kodiInstance, AEStreamHandle *handle)
{
  if (!kodiInstance || !handle)
  {
    CLog::Log(LOGERROR, "Interface_AudioEngine::%s - invalid stream data", __FUNCTION__);
    return;
  }

  static_cast<IAEStream*>(handle)->Pause();
}

void Interface_AudioEngine::AEStream_Resume(void *kodiInstance, AEStreamHandle *handle)
{
  if (!kodiInstance || !handle)
  {
    CLog::Log(LOGERROR, "Interface_AudioEngine::%s - invalid stream data", __FUNCTION__);
    return;
  }

  static_cast<IAEStream*>(handle)->Resume();
}

void Interface_AudioEngine::AEStream_Drain(void *kodiInstance, AEStreamHandle *handle, bool Wait)
{
  if (!kodiInstance || !handle)
  {
    CLog::Log(LOGERROR, "Interface_AudioEngine::%s - invalid stream data", __FUNCTION__);
    return;
  }

  static_cast<IAEStream*>(handle)->Drain(Wait);
}

bool Interface_AudioEngine::AEStream_IsDraining(void *kodiInstance, AEStreamHandle *handle)
{
  if (!kodiInstance || !handle)
  {
    CLog::Log(LOGERROR, "Interface_AudioEngine::%s - invalid stream data", __FUNCTION__);
    return false;
  }

  return static_cast<IAEStream*>(handle)->IsDraining();
}

bool Interface_AudioEngine::AEStream_IsDrained(void *kodiInstance, AEStreamHandle *handle)
{
  if (!kodiInstance || !handle)
  {
    CLog::Log(LOGERROR, "Interface_AudioEngine::%s - invalid stream data", __FUNCTION__);
    return false;
  }

  return static_cast<IAEStream*>(handle)->IsDrained();
}

void Interface_AudioEngine::AEStream_Flush(void *kodiInstance, AEStreamHandle *handle)
{
  if (!kodiInstance || !handle)
  {
    CLog::Log(LOGERROR, "Interface_AudioEngine::%s - invalid stream data", __FUNCTION__);
    return;
  }

  static_cast<IAEStream*>(handle)->Flush();
}

float Interface_AudioEngine::AEStream_GetVolume(void *kodiInstance, AEStreamHandle *handle)
{
  if (!kodiInstance || !handle)
  {
    CLog::Log(LOGERROR, "Interface_AudioEngine::%s - invalid stream data", __FUNCTION__);
    return -1.0f;
  }

  return static_cast<IAEStream*>(handle)->GetVolume();
}

void  Interface_AudioEngine::AEStream_SetVolume(void *kodiInstance, AEStreamHandle *handle, float Volume)
{
  if (!kodiInstance || !handle)
  {
    CLog::Log(LOGERROR, "Interface_AudioEngine::%s - invalid stream data", __FUNCTION__);
    return;
  }

  static_cast<IAEStream*>(handle)->SetVolume(Volume);
}

float Interface_AudioEngine::AEStream_GetAmplification(void *kodiInstance, AEStreamHandle *handle)
{
  if (!kodiInstance || !handle)
  {
    CLog::Log(LOGERROR, "Interface_AudioEngine::%s - invalid stream data", __FUNCTION__);
    return -1.0f;
  }

  return static_cast<IAEStream*>(handle)->GetAmplification();
}

void Interface_AudioEngine::AEStream_SetAmplification(void *kodiInstance, AEStreamHandle *handle, float Amplify)
{
  if (!kodiInstance || !handle)
  {
    CLog::Log(LOGERROR, "Interface_AudioEngine::%s - invalid stream data", __FUNCTION__);
    return;
  }

  static_cast<IAEStream*>(handle)->SetAmplification(Amplify);
}

const unsigned int Interface_AudioEngine::AEStream_GetFrameSize(void *kodiInstance, AEStreamHandle *handle)
{
  if (!kodiInstance || !handle)
  {
    CLog::Log(LOGERROR, "Interface_AudioEngine::%s - invalid stream data", __FUNCTION__);
    return 0;
  }

  return static_cast<IAEStream*>(handle)->GetFrameSize();
}

const unsigned int Interface_AudioEngine::AEStream_GetChannelCount(void *kodiInstance, AEStreamHandle *handle)
{
  if (!kodiInstance || !handle)
  {
    CLog::Log(LOGERROR, "Interface_AudioEngine::%s - invalid stream data", __FUNCTION__);
    return 0;
  }

  return static_cast<IAEStream*>(handle)->GetChannelCount();
}

const unsigned int Interface_AudioEngine::AEStream_GetSampleRate(void *kodiInstance, AEStreamHandle *handle)
{
  if (!kodiInstance || !handle)
  {
    CLog::Log(LOGERROR, "Interface_AudioEngine::%s - invalid stream data", __FUNCTION__);
    return 0;
  }

  return static_cast<IAEStream*>(handle)->GetSampleRate();
}

const AEDataFormat Interface_AudioEngine::AEStream_GetDataFormat(void *kodiInstance, AEStreamHandle *handle)
{
  if (!kodiInstance || !handle)
  {
    CLog::Log(LOGERROR, "Interface_AudioEngine::%s - invalid stream data", __FUNCTION__);
    return AE_FMT_INVALID;
  }

  return static_cast<IAEStream*>(handle)->GetDataFormat();
}

double Interface_AudioEngine::AEStream_GetResampleRatio(void *kodiInstance, AEStreamHandle *handle)
{
  if (!kodiInstance || !handle)
  {
    CLog::Log(LOGERROR, "Interface_AudioEngine::%s - invalid stream data", __FUNCTION__);
    return -1.0f;
  }

  return static_cast<IAEStream*>(handle)->GetResampleRatio();
}

void Interface_AudioEngine::AEStream_SetResampleRatio(void *kodiInstance, AEStreamHandle *handle, double Ratio)
{
  if (!kodiInstance || !handle)
  {
    CLog::Log(LOGERROR, "Interface_AudioEngine::%s - invalid stream data", __FUNCTION__);
    return;
  }

  static_cast<IAEStream*>(handle)->SetResampleRatio(Ratio);
}

} /* namespace ADDON */
