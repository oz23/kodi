#pragma once
/*
 *      Copyright (C) 2015 Team Kodi
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

#include "../AddonBase.h"
#include "../Filesystem.h"

#ifdef BUILD_KODI_ADDON
#include "../IFileTypes.h"
#else
#include "filesystem/IFileTypes.h"
#include "PlatformDefs.h"
#endif

namespace kodi { namespace addon { class CInstanceExternVFS; }}

extern "C"
{

  struct VFSURL
  {
    const char* url;
    const char* domain;
    const char* hostname;
    const char* filename;
    unsigned int port;
    const char* options;
    const char* username;
    const char* password;
    const char* redacted;
    const char* sharename;
  };

  struct VFSCallbacks
  {
    //! \brief Require keyboard input
    //! \param heading The heading of the keyboard dialog
    //! \param input A pointer to the resulting string. Must be free'd by caller.
    //! \return True if input was received, false otherwise
    bool (__cdecl* GetKeyboardInput)(void* ctx, const char* heading, char** input);

    //! \brief Display an error dialog
    //! \param heading The heading of the error dialog
    //! \param line1 The first line of the error dialog
    //! \param line2 The second line of the error dialog. Can be NULL
    //! \param line3 The third line of the error dialog. Can be NULL
    void (__cdecl* SetErrorDialog)(void* ctx, const char* heading, const char* line1, const char* line2, const char* line3);

    //! \brief Prompt the user for authentication of a URL
    //! \param url The URL
    void (__cdecl* RequireAuthentication)(void* ctx, const char* url);

    //! \brief The context to be passed to the callbacks
    void* ctx;
  };

  typedef struct AddonProps_VFSEntry
  {
    int dummy;
  } AddonProps_VFSEntry;

  typedef struct AddonToKodiFuncTable_VFSEntry
  {
    KODI_HANDLE kodiInstance;
  } AddonToKodiFuncTable_VFSEntry;

  typedef struct KodiToAddonFuncTable_VFSEntry
  {
    void* (__cdecl* Open) (kodi::addon::CInstanceExternVFS* addonInstance, VFSURL* url);
    void* (__cdecl* OpenForWrite) (kodi::addon::CInstanceExternVFS* addonInstance, VFSURL* url, bool bOverWrite);
    ssize_t (__cdecl* Read) (kodi::addon::CInstanceExternVFS* addonInstance, void* context, void* buffer, size_t uiBufSize);
    ssize_t (__cdecl* Write) (kodi::addon::CInstanceExternVFS* addonInstance, void* context, const void* buffer, size_t uiBufSize);
    int64_t (__cdecl* Seek) (kodi::addon::CInstanceExternVFS* addonInstance, void* context, int64_t position, int whence);
    int (__cdecl* Truncate) (kodi::addon::CInstanceExternVFS* addonInstance, void* context, int64_t size);
    int64_t (__cdecl* GetLength) (kodi::addon::CInstanceExternVFS* addonInstance, void* context);
    int64_t (__cdecl* GetPosition) (kodi::addon::CInstanceExternVFS* addonInstance, void* context);
    int (__cdecl* GetChunkSize) (kodi::addon::CInstanceExternVFS* addonInstance, void* context);
    int (__cdecl* IoControl) (kodi::addon::CInstanceExternVFS* addonInstance, void* context, XFILE::EIoControl request, void* param);
    int (__cdecl* Stat) (kodi::addon::CInstanceExternVFS* addonInstance, VFSURL* url, struct __stat64* buffer);
    bool (__cdecl* Close) (kodi::addon::CInstanceExternVFS* addonInstance, void* context);
    bool (__cdecl* Exists) (kodi::addon::CInstanceExternVFS* addonInstance, VFSURL* url);
    void (__cdecl* ClearOutIdle) (kodi::addon::CInstanceExternVFS* addonInstance);
    void (__cdecl* DisconnectAll) (kodi::addon::CInstanceExternVFS* addonInstance);
    bool (__cdecl* Delete) (kodi::addon::CInstanceExternVFS* addonInstance, VFSURL* url);
    bool (__cdecl* Rename) (kodi::addon::CInstanceExternVFS* addonInstance, VFSURL* url, VFSURL* url2);
    bool (__cdecl* DirectoryExists) (kodi::addon::CInstanceExternVFS* addonInstance, VFSURL* url);
    bool (__cdecl* RemoveDirectory) (kodi::addon::CInstanceExternVFS* addonInstance, VFSURL* url);
    bool (__cdecl* CreateDirectory) (kodi::addon::CInstanceExternVFS* addonInstance, VFSURL* url);
    void* (__cdecl* GetDirectory) (kodi::addon::CInstanceExternVFS* addonInstance,
                                   VFSURL* url,
                                   VFSDirEntry** entries,
                                   int* num_entries,
                                   VFSCallbacks* callbacks);
    void (__cdecl* FreeDirectory) (kodi::addon::CInstanceExternVFS* addonInstance, void* ctx);
    void* (__cdecl* ContainsFiles) (kodi::addon::CInstanceExternVFS* addonInstance,
                                    VFSURL* url,
                                    VFSDirEntry** entries,
                                    int* num_entries,
                                    char* rootpath);
  } KodiToAddonFuncTable_VFSEntry;

  typedef struct AddonInstance_VFSEntry
  {
    AddonProps_VFSEntry props;
    AddonToKodiFuncTable_VFSEntry toKodi;
    KodiToAddonFuncTable_VFSEntry toAddon;
  } AddonInstance_VFSEntry;

} /* extern "C" */

namespace kodi
{
namespace addon
{
  class CInstanceExternVFS : public IAddonInstance
  {
  public:
    CInstanceExternVFS(KODI_HANDLE instance)
      : IAddonInstance(ADDON_INSTANCE_VFS)
    {
      if (CAddonBase::m_interface->globalSingleInstance != nullptr)
        throw std::logic_error("kodi::addon::CInstanceExternVFS: Creation of multiple together with single instance way is not allowed!");

      SetAddonStruct(instance);
    }

    virtual ~CInstanceExternVFS() { }

    //! \brief Open a file for input
    //! \param url The URL of the file
    //! \return Context for the opened file
    //! \sa IFile::Open
    virtual void* Open(VFSURL* url) { return nullptr; }

    //! \brief Open a file for output
    //! \param url The URL of the file
    //! \param bOverwrite Whether or not to overwrite an existing file
    //! \return Context for the opened file
    //! \sa IFile::OpenForWrite
    virtual void* OpenForWrite(VFSURL* url, bool bOverWrite) { return nullptr; }

    //! \brief Read from a file
    //! \param context The context of the file
    //! \param buffer The buffer to read data into
    //! \param uiBufSize Number of bytes to read
    //! \return Number of bytes read
    //! \sa IFile::Read
    virtual ssize_t Read(void* context, void* buffer, size_t uiBufSize) { return -1; }

    //! \brief Write to a file
    //! \param context The context of the file
    //! \param buffer The buffer to read data from
    //! \param uiBufSize Number of bytes to write
    //! \return Number of bytes written
    //! \sa IFile::Write
    virtual ssize_t Write(void* context, const void* buffer, size_t uiBufSize) { return -1; }

    //! \brief Seek in a file
    //! \param context The context of the file
    //! \param position The position to seek to
    //! \param whence Position in file 'position' is relative to (SEEK_CUR, SEEK_SET, SEEK_END)
    //! \return Offset in file after seek
    //! \sa IFile::Seek
    virtual int64_t Seek(void* context, int64_t position, int whence) { return -1; }

    //! \brief Truncate a file
    //! \param context The context of the file
    //! \param size The size to truncate the file to
    //! \return 0 on success, -1 on error
    //! \sa IFile::Truncate
    virtual int Truncate(void* context, int64_t size) { return -1; }

    //! \brief Get total size of a file
    //! \param context The context of the file
    //! \return Total file size
    //! \sa IFile::GetLength
    virtual int64_t GetLength(void* context) { return 0; }

    //! \brief Get current position in a file
    //! \param context The context of the file
    //! \return Current position
    //! \sa IFile::GetPosition
    virtual int64_t GetPosition(void* context) { return 0; }

    //! \brief Get chunk size of a file
    //! \param context The context of the file
    //! \return Chunk size
    //! \sa IFile::GetChunkSize()
    virtual int GetChunkSize(void* context) { return 1; }

    //! \brief Perform an IO-control on the file
    //! \param context The context of the file
    //! \param request The requested IO-control
    //! \param param Parameter attached to the IO-control
    //! \return -1 on error, >= 0 on success
    //! \sa IFile::IoControl
    virtual int IoControl(void* context, XFILE::EIoControl request, void* param) { return -1; }

    //! \brief Stat a file
    //! \param url The URL of the file
    //! \param buffer The buffer to store results in
    //! \return -1 on error, 0 otherwise
    //! \sa IFile::Stat
    virtual int Stat(VFSURL* url, struct __stat64* buffer) { return 0; }

    //! \brief Close a file
    //! \param context The context of the file
    //! \return True on success, false on failure
    //! \sa IFile::Close
    virtual bool Close(void* context) { return false; }

    //! \brief Check for file existence
    //! \param url The URL of the file
    //! \return True if file exists, false otherwise
    //! \sa IFile::Exists
    virtual bool Exists(VFSURL* url) { return false; }

    //! \brief Clear out any idle connections
    virtual void ClearOutIdle() { }

    //! \brief Disconnect all connections
    virtual void DisconnectAll() { }

    //! \brief Delete a file
    //! \param url The URL of the file
    //! \return True if deletion was successful, false otherwise
    //! \sa IFile::Delete
    virtual bool Delete(VFSURL* url) { return false; }

    //! \brief Rename a file
    //! \param url The URL of the source file
    //! \param url2 The URL of the destination file
    //! \return True if deletion was successful, false otherwise
    //! \sa IFile::Rename
    virtual bool Rename(VFSURL* url, VFSURL* url2) { return false; }

    //! \brief Check for directory existence
    //! \param url The URL of the file
    //! \return True if directory exists, false otherwise
    //! \sa IDirectory::Exists
    virtual bool DirectoryExists(VFSURL* url) { return false; }

    //! \brief Remove a directory
    //! \param url The URL of the directory
    //! \return True if removal was successful, false otherwise
    //! \sa IDirectory::Remove
    virtual bool RemoveDirectory(VFSURL* url) { return false; }

    //! \brief Create a directory
    //! \param url The URL of the file
    //! \return True if creation was successful, false otherwise
    //! \sa IDirectory::Create
    virtual bool CreateDirectory(VFSURL* url) { return false; }

    //! \brief List a directory
    //! \param url The URL of the directory
    //! \param entries The entries in the directory
    //! \param num_entries Number of entries in the directory
    //! \param callbacks A callback structure
    //! \return Context for the directory listing
    //! \sa IDirectory::GetDirectory
    virtual void* GetDirectory(VFSURL* url,
                               VFSDirEntry** entries,
                               int* num_entries,
                               VFSCallbacks* callbacks) { return nullptr; }

    //! \brief Free up resources after listing a directory
    virtual void FreeDirectory(void* ctx) { }

    //! \brief Check if file should be presented as a directory (multiple streams)
    //! \param url The URL of the file
    //! \param entries The entries in the directory
    //! \param num_entries Number of entries in the directory
    //! \param rootpath Path to root directory if multiple entries
    //! \return Context for the directory listing
    //! \sa IFileDirectory::ContainsFiles, FreeDirectory
    virtual void* ContainsFiles(VFSURL* url,
                                VFSDirEntry** entries,
                                int* num_entries,
                                char* rootpath) { return nullptr; }
  private:
    void SetAddonStruct(KODI_HANDLE instance)
    {
      if (instance == nullptr)
        throw std::logic_error("kodi::addon::CInstanceExternVFS: Creation with empty addon structure not allowed, table must be given from Kodi!");

      m_instanceData = static_cast<AddonInstance_VFSEntry*>(instance);

      m_instanceData->toAddon.Open = ADDON_Open;
      m_instanceData->toAddon.OpenForWrite = ADDON_OpenForWrite;
      m_instanceData->toAddon.Read = ADDON_Read;
      m_instanceData->toAddon.Write = ADDON_Write;
      m_instanceData->toAddon.Seek = ADDON_Seek;
      m_instanceData->toAddon.Truncate = ADDON_Truncate;
      m_instanceData->toAddon.GetLength = ADDON_GetLength;
      m_instanceData->toAddon.GetPosition = ADDON_GetPosition;
      m_instanceData->toAddon.GetChunkSize = ADDON_GetChunkSize;
      m_instanceData->toAddon.IoControl = ADDON_IoControl;
      m_instanceData->toAddon.Stat = ADDON_Stat;
      m_instanceData->toAddon.Close = ADDON_Close;
      m_instanceData->toAddon.Exists = ADDON_Exists;
      m_instanceData->toAddon.ClearOutIdle = ADDON_ClearOutIdle;
      m_instanceData->toAddon.DisconnectAll = ADDON_DisconnectAll;
      m_instanceData->toAddon.Delete = ADDON_Delete;
      m_instanceData->toAddon.Rename = ADDON_Rename;
      m_instanceData->toAddon.DirectoryExists = ADDON_DirectoryExists;
      m_instanceData->toAddon.RemoveDirectory = ADDON_RemoveDirectory;
      m_instanceData->toAddon.CreateDirectory = ADDON_CreateDirectory;
      m_instanceData->toAddon.GetDirectory = ADDON_GetDirectory;
      m_instanceData->toAddon.FreeDirectory = ADDON_FreeDirectory;
      m_instanceData->toAddon.ContainsFiles = ADDON_ContainsFiles;
    }

    inline static void* ADDON_Open(kodi::addon::CInstanceExternVFS* addonInstance, VFSURL* url)
    {
      return addonInstance->Open(url);
    }

    inline static void* ADDON_OpenForWrite(kodi::addon::CInstanceExternVFS* addonInstance, VFSURL* url, bool bOverWrite)
    {
      return addonInstance->OpenForWrite(url, bOverWrite);
    }

    inline static ssize_t ADDON_Read(kodi::addon::CInstanceExternVFS* addonInstance, void* context, void* buffer, size_t uiBufSize)
    {
      return addonInstance->Read(context, buffer, uiBufSize);
    }

    inline static ssize_t ADDON_Write(kodi::addon::CInstanceExternVFS* addonInstance, void* context, const void* buffer, size_t uiBufSize)
    {
      return addonInstance->Write(context, buffer, uiBufSize);
    }

    inline static int64_t ADDON_Seek(kodi::addon::CInstanceExternVFS* addonInstance, void* context, int64_t position, int whence)
    {
      return addonInstance->Seek(context, position, whence);
    }

    inline static int ADDON_Truncate(kodi::addon::CInstanceExternVFS* addonInstance, void* context, int64_t size)
    {
      return addonInstance->Truncate(context, size);
    }

    inline static int64_t ADDON_GetLength(kodi::addon::CInstanceExternVFS* addonInstance, void* context)
    {
      return addonInstance->GetLength(context);
    }

    inline static int64_t ADDON_GetPosition(kodi::addon::CInstanceExternVFS* addonInstance, void* context)
    {
      return addonInstance->GetPosition(context);
    }

    inline static int ADDON_GetChunkSize(kodi::addon::CInstanceExternVFS* addonInstance, void* context)
    {
      return addonInstance->GetChunkSize(context);
    }

    inline static int ADDON_IoControl(kodi::addon::CInstanceExternVFS* addonInstance, void* context, XFILE::EIoControl request, void* param)
    {
      return addonInstance->IoControl(context, request, param);
    }

    inline static int ADDON_Stat(kodi::addon::CInstanceExternVFS* addonInstance, VFSURL* url, struct __stat64* buffer)
    {
      return addonInstance->Stat(url, buffer);
    }

    inline static bool ADDON_Close(kodi::addon::CInstanceExternVFS* addonInstance, void* context)
    {
      return addonInstance->Close(context);
    }

    inline static bool ADDON_Exists(kodi::addon::CInstanceExternVFS* addonInstance, VFSURL* url)
    {
      return addonInstance->Exists(url);
    }

    inline static void ADDON_ClearOutIdle(kodi::addon::CInstanceExternVFS* addonInstance)
    {
      return addonInstance->ClearOutIdle();
    }

    inline static void ADDON_DisconnectAll(kodi::addon::CInstanceExternVFS* addonInstance)
    {
      return addonInstance->DisconnectAll();
    }

    inline static bool ADDON_Delete(kodi::addon::CInstanceExternVFS* addonInstance, VFSURL* url)
    {
      return addonInstance->Delete(url);
    }

    inline static bool ADDON_Rename(kodi::addon::CInstanceExternVFS* addonInstance, VFSURL* url, VFSURL* url2)
    {
      return addonInstance->Rename(url, url2);
    }

    inline static bool ADDON_DirectoryExists(kodi::addon::CInstanceExternVFS* addonInstance, VFSURL* url)
    {
      return addonInstance->DirectoryExists(url);
    }

    inline static bool ADDON_RemoveDirectory(kodi::addon::CInstanceExternVFS* addonInstance, VFSURL* url)
    {
      return addonInstance->RemoveDirectory(url);
    }

    inline static bool ADDON_CreateDirectory(kodi::addon::CInstanceExternVFS* addonInstance, VFSURL* url)
    {
      return addonInstance->CreateDirectory(url);
    }

    inline static void* ADDON_GetDirectory(kodi::addon::CInstanceExternVFS* addonInstance,
                                   VFSURL* url,
                                   VFSDirEntry** entries,
                                   int* num_entries,
                                   VFSCallbacks* callbacks)
    {
      return addonInstance->GetDirectory(url, entries, num_entries, callbacks);
    }

    inline static void ADDON_FreeDirectory(kodi::addon::CInstanceExternVFS* addonInstance, void* ctx)
    {
      addonInstance->FreeDirectory(ctx);
    }

    inline static void* ADDON_ContainsFiles(kodi::addon::CInstanceExternVFS* addonInstance,
                                    VFSURL* url,
                                    VFSDirEntry** entries,
                                    int* num_entries,
                                    char* rootpath)
    {
      return addonInstance->ContainsFiles(url, entries, num_entries, rootpath);
    }

    AddonInstance_VFSEntry* m_instanceData;
  };

} /* namespace addon */
} /* namespace kodi */
