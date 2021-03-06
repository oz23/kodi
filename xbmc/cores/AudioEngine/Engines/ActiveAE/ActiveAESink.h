/*
 *  Copyright (C) 2010-2018 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "cores/AudioEngine/AESinkFactory.h"
#include "cores/AudioEngine/Engines/ActiveAE/ActiveAEBuffer.h"
#include "cores/AudioEngine/Interfaces/AE.h"
#include "cores/AudioEngine/Interfaces/AESink.h"
#include "threads/Event.h"
#include "threads/Thread.h"
#include "utils/ActorProtocol.h"

class CAEBitstreamPacker;

namespace ActiveAE
{
using namespace Actor;

class CEngineStats;

struct SinkConfig
{
  AEAudioFormat format;
  CEngineStats *stats;
  const std::string *device;
};

struct SinkReply
{
  AEAudioFormat format;
  float cacheTotal;
  float latency;
  bool hasVolume;
};

class CSinkControlProtocol : public Protocol
{
public:
  CSinkControlProtocol(std::string name, CEvent* inEvent, CEvent *outEvent) : Protocol(name, inEvent, outEvent) {};
  enum OutSignal
  {
    CONFIGURE,
    UNCONFIGURE,
    STREAMING,
    APPFOCUSED,
    VOLUME,
    FLUSH,
    TIMEOUT,
    SETSILENCETIMEOUT,
    SETNOISETYPE,
    SYNC,
  };
  enum InSignal
  {
    ACC,
    ERR,
    STATS,
  };
};

class CSinkDataProtocol : public Protocol
{
public:
  CSinkDataProtocol(std::string name, CEvent* inEvent, CEvent *outEvent) : Protocol(name, inEvent, outEvent) {};
  enum OutSignal
  {
    SAMPLE = 0,
    DRAIN,
  };
  enum InSignal
  {
    RETURNSAMPLE,
    ACC,
  };
};

class CSinkInternalProtocol : public Protocol
{
public:
  CSinkInternalProtocol(std::string name, CEvent* inEvent, CEvent *outEvent) : Protocol(name, inEvent, outEvent) {};
  enum OutSignal
  {
    REQUESTDATA = 0
  };
};

class CActiveAESink : private CThread
{
public:
  explicit CActiveAESink(CEvent *inMsgEvent);
  void EnumerateSinkList(bool force, std::string driver);
  void EnumerateOutputDevices(AEDeviceList &devices, bool passthrough);
  void Start();
  void Dispose();
  AEDeviceType GetDeviceType(const std::string &device);
  bool HasPassthroughDevice();
  bool SupportsFormat(const std::string &device, AEAudioFormat &format);
  bool DeviceExist(std::string driver, std::string device);
  CSinkControlProtocol m_controlPort;
  CSinkDataProtocol m_dataPort;

protected:
  void Process() override;
  void StateMachine(int signal, Protocol *port, Message *msg);
  void PrintSinks(std::string& driver);
  void GetDeviceFriendlyName(std::string &device);
  void OpenSink();
  void ReturnBuffers();
  void SetSilenceTimer();
  bool NeedIECPacking();

  unsigned int OutputSamples(CSampleBuffer* samples);
  unsigned int OutputSilence(unsigned int millis);
  void SwapInit(CSampleBuffer* samples);

  void GenerateNoise();
  void RequestData();

  CSinkInternalProtocol m_internalPort;
  CEvent m_outMsgEvent;
  CEvent *m_inMsgEvent;
  int m_state;
  bool m_bStateMachineSelfTrigger;
  int m_extTimeout;
  int m_silenceTimeOut;
  bool m_extError;
  unsigned int m_extSilenceTimeout;
  bool m_extAppFocused;
  bool m_extStreaming;
  XbmcThreads::EndTime m_extSilenceTimer;
  int m_syncTime;

  CSampleBuffer m_sampleOfSilence;
  enum
  {
    CHECK_SWAP,
    NEED_CONVERT,
    NEED_BYTESWAP,
    SKIP_SWAP,
  } m_swapState;

  std::string m_deviceFriendlyName;
  std::string m_device;
  std::vector<AE::AESinkInfo> m_sinkInfoList;
  IAESink *m_sink;
  AEAudioFormat m_sinkFormat, m_requestedFormat;
  CEngineStats *m_stats;
  float m_volume;
  int m_sinkLatency;
  CAEBitstreamPacker *m_packer;
  bool m_needIecPack;
  bool m_streamNoise;
  std::deque<CSampleBuffer*> m_soundSamples;
  std::deque<CSampleBuffer*> m_streamSamples;
};

}
