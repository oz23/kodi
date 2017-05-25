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
#include "../StreamCrypto.h"
#include "../StreamCodec.h"

#ifdef BUILD_KODI_ADDON
#include "../DVDDemuxPacket.h"
#else
#include "cores/VideoPlayer/DVDDemuxers/DVDDemuxPacket.h"
#endif

namespace kodi { namespace addon { class CInstanceInputStream; }}

extern "C"
{

  /*!
   * @brief InputStream add-on capabilities. All capabilities are set to "false" as default.
   */
  typedef struct INPUTSTREAM_CAPABILITIES
  {
    enum MASKTYPE: uint32_t
    {
      /// supports interface IDemux
      SUPPORTSIDEMUX = (1 << 0),

      /// supports interface IPosTime
      SUPPORTSIPOSTIME = (1 << 1),

      /// supports interface IDisplayTime
      SUPPORTSIDISPLAYTIME = (1 << 2),

      /// supports seek
      SUPPORTSSEEK = (1 << 3),

      /// supports pause
      SUPPORTSPAUSE = (1 << 4)
    };

    /// set of supported capabilities
    uint32_t m_mask;
  } INPUTSTREAM_CAPABILITIES;

  /*!
   * @brief structure of key/value pairs passed to addon on Open()
   */
  typedef struct INPUTSTREAM
  {
    static const unsigned int MAX_INFO_COUNT = 8;

    const char *m_strURL;

    unsigned int m_nCountInfoValues;
    struct LISTITEMPROPERTY
    {
      const char *m_strKey;
      const char *m_strValue;
    } m_ListItemProperties[MAX_INFO_COUNT];

    const char *m_libFolder;
    const char *m_profileFolder;
  } INPUTSTREAM;

  /*!
   * @brief Array of stream IDs
   */
  typedef struct INPUTSTREAM_IDS
  {
    static const unsigned int MAX_STREAM_COUNT = 32;
    unsigned int m_streamCount;
    unsigned int m_streamIds[MAX_STREAM_COUNT];
  } INPUTSTREAM_IDS;

  /*!
   * @brief stream properties
   */
  typedef struct INPUTSTREAM_INFO
  {
    enum STREAM_TYPE
    {
      TYPE_NONE,
      TYPE_VIDEO,
      TYPE_AUDIO,
      TYPE_SUBTITLE,
      TYPE_TELETEXT
    } m_streamType;

    enum Codec_FEATURES
    {
      FEATURE_DECODE = 1
    };
    unsigned int m_features;

    char m_codecName[32];                /*!< @brief (required) name of codec according to ffmpeg */
    char m_codecInternalName[32];        /*!< @brief (optional) internal name of codec (selectionstream info) */
    kodi::addon::CODEC_PROFILE m_codecProfile; /*!< @brief (optional) bandwidth of the stream (selectionstream info) */
    unsigned int m_pID;                  /*!< @brief (required) physical index */

    const uint8_t *m_ExtraData;
    unsigned int m_ExtraSize;

    char m_language[4];                  /*!< @brief ISO 639 3-letter language code (empty string if undefined) */

    unsigned int m_FpsScale;             /*!< @brief Scale of 1000 and a rate of 29970 will result in 29.97 fps */
    unsigned int m_FpsRate;
    unsigned int m_Height;               /*!< @brief height of the stream reported by the demuxer */
    unsigned int m_Width;                /*!< @brief width of the stream reported by the demuxer */
    float m_Aspect;                      /*!< @brief display aspect of stream */

    unsigned int m_Channels;             /*!< @brief (required) amount of channels */
    unsigned int m_SampleRate;           /*!< @brief (required) sample rate */
    unsigned int m_BitRate;              /*!< @brief (required) bit rate */
    unsigned int m_BitsPerSample;        /*!< @brief (required) bits per sample */
    unsigned int m_BlockAlign;

    CRYPTO_INFO m_cryptoInfo;
  } INPUTSTREAM_INFO;


  // this are properties given to the addon on create
  // at this time we have no parameters for the addon
  typedef struct AddonProps_InputStream /* internal */
  {
    int dummy;
  } AddonProps_InputStream;

  typedef struct AddonToKodiFuncTable_InputStream /* internal */
  {
    KODI_HANDLE kodiInstance;
    void (*FreeDemuxPacket)(void* kodiInstanceBase, DemuxPacket* pPacket);
    DemuxPacket* (*AllocateDemuxPacket)(void* kodiInstanceBase, int iDataSize);
    DemuxPacket* (*AllocateEncryptedDemuxPacket)(void* kodiInstanceBase, unsigned int iDataSize, unsigned int encryptedSubsampleCount);
  } AddonToKodiFuncTable_InputStream;

  struct AddonInstance_InputStream;
  typedef struct KodiToAddonFuncTable_InputStream /* internal */
  {
    kodi::addon::CInstanceInputStream* addonInstance;

    bool (__cdecl* Open)(AddonInstance_InputStream* instance, INPUTSTREAM&);
    void (__cdecl* Close)(AddonInstance_InputStream* instance);
    void (__cdecl* GetCapabilities)(AddonInstance_InputStream* instance, INPUTSTREAM_CAPABILITIES*);

    // IDemux
    struct INPUTSTREAM_IDS (__cdecl* GetStreamIds)(AddonInstance_InputStream* instance);
    struct INPUTSTREAM_INFO (__cdecl* GetStream)(AddonInstance_InputStream* instance, int);
    void (__cdecl* EnableStream)(AddonInstance_InputStream* instance, int, bool);
    void (__cdecl* DemuxReset)(AddonInstance_InputStream* instance);
    void (__cdecl* DemuxAbort)(AddonInstance_InputStream* instance);
    void (__cdecl* DemuxFlush)(AddonInstance_InputStream* instance);
    DemuxPacket* (__cdecl* DemuxRead)(AddonInstance_InputStream* instance);
    bool (__cdecl* DemuxSeekTime)(AddonInstance_InputStream* instance, double, bool, double*);
    void (__cdecl* DemuxSetSpeed)(AddonInstance_InputStream* instance, int);
    void (__cdecl* SetVideoResolution)(AddonInstance_InputStream* instance, int, int);

    // IDisplayTime
    int (__cdecl* GetTotalTime)(AddonInstance_InputStream* instance);
    int (__cdecl* GetTime)(AddonInstance_InputStream* instance);

    // IPosTime
    bool (__cdecl* PosTime)(AddonInstance_InputStream* instance, int);

    // Seekable (mandatory)
    bool (__cdecl* CanPauseStream)(AddonInstance_InputStream* instance);
    bool (__cdecl* CanSeekStream)(AddonInstance_InputStream* instance);

    int (__cdecl* ReadStream)(AddonInstance_InputStream* instance, uint8_t*, unsigned int);
    int64_t(__cdecl* SeekStream)(AddonInstance_InputStream* instance, int64_t, int);
    int64_t (__cdecl* PositionStream)(AddonInstance_InputStream* instance);
    int64_t (__cdecl* LengthStream)(AddonInstance_InputStream* instance);
    void (__cdecl* PauseStream)(AddonInstance_InputStream* instance, double);
    bool (__cdecl* IsRealTimeStream)(AddonInstance_InputStream* instance);
  } KodiToAddonFuncTable_InputStream;

  typedef struct AddonInstance_InputStream /* internal */
  {
    AddonProps_InputStream props;
    AddonToKodiFuncTable_InputStream toKodi;
    KodiToAddonFuncTable_InputStream toAddon;
  } AddonInstance_InputStream;

} /* extern "C" */

namespace kodi
{
namespace addon
{

  class CInstanceInputStream : public IAddonInstance
  {
  public:
    CInstanceInputStream(KODI_HANDLE instance)
      : IAddonInstance(ADDON_INSTANCE_INPUTSTREAM)
    {
      if (CAddonBase::m_interface->globalSingleInstance != nullptr)
        throw std::logic_error("kodi::addon::CInstanceInputStream: Creation of multiple together with single instance way is not allowed!");

      SetAddonStruct(instance);
    }

    virtual ~CInstanceInputStream() { }

    /*!
    * Open a stream.
    * @param props
    * @return True if the stream has been opened successfully, false otherwise.
    * @remarks
    */
    virtual bool Open(INPUTSTREAM& props) = 0;

    /*!
    * Close an open stream.
    * @remarks
    */
    virtual void Close() = 0;

    /*!
    * Get Capabilities of this addon.
    * @param capabilities The add-on's capabilities.
    * @remarks
    */
    virtual void GetCapabilities(INPUTSTREAM_CAPABILITIES& capabilities) = 0;

    /*!
    * Get IDs of available streams
    * @remarks
    */
    virtual INPUTSTREAM_IDS GetStreamIds() = 0;

    /*!
    * Get stream properties of a stream.
    * @param streamId unique id of stream
    * @return struc of stream properties
    * @remarks
    */
    virtual INPUTSTREAM_INFO GetStream(int streamid) = 0;

    /*!
    * Enable or disable a stream.
    * A disabled stream does not send demux packets
    * @param streamId unique id of stream
    * @param enable true for enable, false for disable
    * @remarks
    */
    virtual void EnableStream(int streamid, bool enable) = 0;

    /*!
    * Reset the demultiplexer in the add-on.
    * @remarks Required if bHandlesDemuxing is set to true.
    */
    virtual void DemuxReset() { }

    /*!
    * Abort the demultiplexer thread in the add-on.
    * @remarks Required if bHandlesDemuxing is set to true.
    */
    virtual void DemuxAbort() { }

    /*!
    * Flush all data that's currently in the demultiplexer buffer in the add-on.
    * @remarks Required if bHandlesDemuxing is set to true.
    */
    virtual void DemuxFlush() { }

    /*!
    * Read the next packet from the demultiplexer, if there is one.
    * @return The next packet.
    *         If there is no next packet, then the add-on should return the
    *         packet created by calling AllocateDemuxPacket(0) on the callback.
    *         If the stream changed and Kodi's player needs to be reinitialised,
    *         then, the add-on should call AllocateDemuxPacket(0) on the
    *         callback, and set the streamid to DMX_SPECIALID_STREAMCHANGE and
    *         return the value.
    *         The add-on should return NULL if an error occured.
    * @remarks Return NULL if this add-on won't provide this function.
    */
    virtual DemuxPacket* DemuxRead() { return nullptr; }

    /*!
    * Notify the InputStream addon/demuxer that Kodi wishes to seek the stream by time
    * Demuxer is required to set stream to an IDR frame
    * @param time The absolute time since stream start
    * @param backwards True to seek to keyframe BEFORE time, else AFTER
    * @param startpts can be updated to point to where display should start
    * @return True if the seek operation was possible
    * @remarks Optional, and only used if addon has its own demuxer.
    */
    virtual bool DemuxSeekTime(double time, bool backwards, double &startpts) { return false; }

    /*!
    * Notify the InputStream addon/demuxer that Kodi wishes to change playback speed
    * @param speed The requested playback speed
    * @remarks Optional, and only used if addon has its own demuxer.
    */
    virtual void DemuxSetSpeed(int speed) { }

    /*!
    * Sets desired width / height
    * @param width / hight
    */
    virtual void SetVideoResolution(int width, int height) { }

    /*!
    * Totel time in ms
    * @remarks
    */
    virtual int GetTotalTime() { return -1; }

    /*!
    * Playing time in ms
    * @remarks
    */
    virtual int GetTime() { return -1; }

    /*!
    * Positions inputstream to playing time given in ms
    * @remarks
    */
    virtual bool PosTime(int ms) { return false; }


    /*!
    * Check if the backend support pausing the currently playing stream
    * This will enable/disable the pause button in Kodi based on the return value
    * @return false if the InputStream addon/backend does not support pausing, true if possible
    */
    virtual bool CanPauseStream() { return false; }

    /*!
    * Check if the backend supports seeking for the currently playing stream
    * This will enable/disable the rewind/forward buttons in Kodi based on the return value
    * @return false if the InputStream addon/backend does not support seeking, true if possible
    */
    virtual bool CanSeekStream() { return false; }

    
    /*!
    * Read from an open stream.
    * @param buffer The buffer to store the data in.
    * @param bufferSize The amount of bytes to read.
    * @return The amount of bytes that were actually read from the stream.
    * @remarks Return -1 if this add-on won't provide this function.
    */
    virtual int ReadStream(uint8_t* buffer, unsigned int bufferSize) { return -1; }

    /*!
    * Seek in a stream.
    * @param position The position to seek to.
    * @param whence ?
    * @return The new position.
    * @remarks Return -1 if this add-on won't provide this function.
    */
    virtual int64_t SeekStream(int64_t position, int whence = SEEK_SET) { return -1; }

    /*!
    * @return The position in the stream that's currently being read.
    * @remarks Return -1 if this add-on won't provide this function.
    */
    virtual int64_t PositionStream() { return -1; }

    /*!
    * @return The total length of the stream that's currently being read.
    * @remarks Return -1 if this add-on won't provide this function.
    */
    virtual int64_t LengthStream() { return -1; }


    /*!
    * @brief Notify the InputStream addon that Kodi (un)paused the currently playing stream
    */
    virtual void PauseStream(double time) { }


    /*!
    *  Check for real-time streaming
    *  @return true if current stream is real-time
    */
    virtual bool IsRealTimeStream() { return true; }

    /*!
    * @brief Allocate a demux packet. Free with FreeDemuxPacket
    * @param iDataSize The size of the data that will go into the packet
    * @return The allocated packet
    */
    DemuxPacket* AllocateDemuxPacket(int dataSize)
    {
      return m_instanceData->toKodi.AllocateDemuxPacket(m_instanceData->toKodi.kodiInstance, dataSize);
    }

    /*!
    * @brief Allocate a demux packet with crypto data. Free with FreeDemuxPacket
    * @param iDataSize The size of the data that will go into the packet
    * @param encryptedSubsampleCount The number of encrypted subSamples that will go into the packet
    * @return The allocated packet
    */
    DemuxPacket* AllocateEncryptedDemuxPacket(unsigned int dataSize, unsigned int encryptedSubsampleCount)
    {
      return m_instanceData->toKodi.AllocateEncryptedDemuxPacket(m_instanceData->toKodi.kodiInstance, dataSize, encryptedSubsampleCount);
    }

    /*!
    * @brief Free a packet that was allocated with AllocateDemuxPacket
    * @param pPacket The packet to free
    */
    void FreeDemuxPacket(DemuxPacket* packet)
    {
      return m_instanceData->toKodi.FreeDemuxPacket(m_instanceData->toKodi.kodiInstance, packet);
    }

  private:
    void SetAddonStruct(KODI_HANDLE instance)
    {
      if (instance == nullptr)
        throw std::logic_error("kodi::addon::CInstanceInputStream: Creation with empty addon structure not allowed, table must be given from Kodi!");

      m_instanceData = static_cast<AddonInstance_InputStream*>(instance);
      m_instanceData->toAddon.addonInstance = this;
      m_instanceData->toAddon.Open = ADDON_Open;
      m_instanceData->toAddon.Close = ADDON_Close;
      m_instanceData->toAddon.GetCapabilities = ADDON_GetCapabilities;

      m_instanceData->toAddon.GetStreamIds = ADDON_GetStreamIds;
      m_instanceData->toAddon.GetStream = ADDON_GetStream;
      m_instanceData->toAddon.EnableStream = ADDON_EnableStream;
      m_instanceData->toAddon.DemuxReset = ADDON_DemuxReset;
      m_instanceData->toAddon.DemuxAbort = ADDON_DemuxAbort;
      m_instanceData->toAddon.DemuxFlush = ADDON_DemuxFlush;
      m_instanceData->toAddon.DemuxRead = ADDON_DemuxRead;
      m_instanceData->toAddon.DemuxSeekTime = ADDON_DemuxSeekTime;
      m_instanceData->toAddon.DemuxSetSpeed = ADDON_DemuxSetSpeed;
      m_instanceData->toAddon.SetVideoResolution = ADDON_SetVideoResolution;

      m_instanceData->toAddon.GetTotalTime = ADDON_GetTotalTime;
      m_instanceData->toAddon.GetTime = ADDON_GetTime;

      m_instanceData->toAddon.PosTime = ADDON_PosTime;

      m_instanceData->toAddon.CanPauseStream = ADDON_CanPauseStream;
      m_instanceData->toAddon.CanSeekStream = ADDON_CanSeekStream;

      m_instanceData->toAddon.ReadStream = ADDON_ReadStream;
      m_instanceData->toAddon.SeekStream = ADDON_SeekStream;
      m_instanceData->toAddon.PositionStream = ADDON_PositionStream;
      m_instanceData->toAddon.LengthStream = ADDON_LengthStream;
      m_instanceData->toAddon.PauseStream = ADDON_PauseStream;
      m_instanceData->toAddon.IsRealTimeStream = ADDON_IsRealTimeStream;
    }

    inline static bool ADDON_Open(AddonInstance_InputStream* instance, INPUTSTREAM& props)
    {
      return instance->toAddon.addonInstance->Open(props);
    }

    inline static void ADDON_Close(AddonInstance_InputStream* instance)
    {
      instance->toAddon.addonInstance->Close();
    }

    inline static void ADDON_GetCapabilities(AddonInstance_InputStream* instance, INPUTSTREAM_CAPABILITIES* capabilities)
    {
      instance->toAddon.addonInstance->GetCapabilities(*capabilities);
    }
    

    // IDemux
    inline static struct INPUTSTREAM_IDS ADDON_GetStreamIds(AddonInstance_InputStream* instance)
    {
      return instance->toAddon.addonInstance->GetStreamIds();
    }

    inline static struct INPUTSTREAM_INFO ADDON_GetStream(AddonInstance_InputStream* instance, int streamid)
    {
      return instance->toAddon.addonInstance->GetStream(streamid);
    }

    inline static void ADDON_EnableStream(AddonInstance_InputStream* instance, int streamid, bool enable)
    {
      instance->toAddon.addonInstance->EnableStream(streamid, enable);
    }

    inline static void ADDON_DemuxReset(AddonInstance_InputStream* instance)
    {
      instance->toAddon.addonInstance->DemuxReset();
    }

    inline static void ADDON_DemuxAbort(AddonInstance_InputStream* instance)
    {
      instance->toAddon.addonInstance->DemuxAbort();
    }

    inline static void ADDON_DemuxFlush(AddonInstance_InputStream* instance)
    {
      instance->toAddon.addonInstance->DemuxFlush();
    }

    inline static DemuxPacket* ADDON_DemuxRead(AddonInstance_InputStream* instance)
    {
      return instance->toAddon.addonInstance->DemuxRead();
    }

    inline static bool ADDON_DemuxSeekTime(AddonInstance_InputStream* instance, double time, bool backwards, double *startpts)
    {
      return instance->toAddon.addonInstance->DemuxSeekTime(time, backwards, *startpts);
    }

    inline static void ADDON_DemuxSetSpeed(AddonInstance_InputStream* instance, int speed)
    {
      instance->toAddon.addonInstance->DemuxSetSpeed(speed);
    }

    inline static void ADDON_SetVideoResolution(AddonInstance_InputStream* instance, int width, int height)
    {
      instance->toAddon.addonInstance->SetVideoResolution(width, height);
    }


    // IDisplayTime
    inline static int ADDON_GetTotalTime(AddonInstance_InputStream* instance)
    {
      return instance->toAddon.addonInstance->GetTotalTime();
    }

    inline static int ADDON_GetTime(AddonInstance_InputStream* instance)
    {
      return instance->toAddon.addonInstance->GetTime();
    }


    // IPosTime
    inline static bool ADDON_PosTime(AddonInstance_InputStream* instance, int ms)
    {
      return instance->toAddon.addonInstance->PosTime(ms);
    }

    // Seekable (mandatory)
    inline static bool ADDON_CanPauseStream(AddonInstance_InputStream* instance)
    {
      return instance->toAddon.addonInstance->CanPauseStream();
    }

    inline static bool ADDON_CanSeekStream(AddonInstance_InputStream* instance)
    {
      return instance->toAddon.addonInstance->CanSeekStream();
    }


    inline static int ADDON_ReadStream(AddonInstance_InputStream* instance, uint8_t* buffer, unsigned int bufferSize)
    {
      return instance->toAddon.addonInstance->ReadStream(buffer, bufferSize);
    }

    inline static int64_t ADDON_SeekStream(AddonInstance_InputStream* instance, int64_t position, int whence)
    {
      return instance->toAddon.addonInstance->SeekStream(position, whence);
    }

    inline static int64_t ADDON_PositionStream(AddonInstance_InputStream* instance)
    {
      return instance->toAddon.addonInstance->PositionStream();
    }

    inline static int64_t ADDON_LengthStream(AddonInstance_InputStream* instance)
    {
      return instance->toAddon.addonInstance->LengthStream();
    }

    inline static void ADDON_PauseStream(AddonInstance_InputStream* instance, double time)
    {
      instance->toAddon.addonInstance->PauseStream(time);
    }

    inline static bool ADDON_IsRealTimeStream(AddonInstance_InputStream* instance)
    {
      return instance->toAddon.addonInstance->IsRealTimeStream();
    }

    AddonInstance_InputStream* m_instanceData;
  };

} /* namespace addon */
} /* namespace kodi */
