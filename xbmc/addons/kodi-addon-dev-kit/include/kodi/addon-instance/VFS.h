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

namespace kodi { namespace addon { class CInstanceVFS; }}

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

  struct AddonInstance_VFSEntry;
  typedef struct KodiToAddonFuncTable_VFSEntry
  {
    kodi::addon::CInstanceVFS* addonInstance;

    void* (__cdecl* Open) (AddonInstance_VFSEntry* instance, VFSURL* url);
    void* (__cdecl* OpenForWrite) (AddonInstance_VFSEntry* instance, VFSURL* url, bool bOverWrite);
    ssize_t (__cdecl* Read) (AddonInstance_VFSEntry* instance, void* context, void* buffer, size_t uiBufSize);
    ssize_t (__cdecl* Write) (AddonInstance_VFSEntry* instance, void* context, const void* buffer, size_t uiBufSize);
    int64_t (__cdecl* Seek) (AddonInstance_VFSEntry* instance, void* context, int64_t position, int whence);
    int (__cdecl* Truncate) (AddonInstance_VFSEntry* instance, void* context, int64_t size);
    int64_t (__cdecl* GetLength) (AddonInstance_VFSEntry* instance, void* context);
    int64_t (__cdecl* GetPosition) (AddonInstance_VFSEntry* instance, void* context);
    int (__cdecl* GetChunkSize) (AddonInstance_VFSEntry* instance, void* context);
    int (__cdecl* IoControl) (AddonInstance_VFSEntry* instance, void* context, XFILE::EIoControl request, void* param);
    int (__cdecl* Stat) (AddonInstance_VFSEntry* instance, VFSURL* url, struct __stat64* buffer);
    bool (__cdecl* Close) (AddonInstance_VFSEntry* instance, void* context);
    bool (__cdecl* Exists) (AddonInstance_VFSEntry* instance, VFSURL* url);
    void (__cdecl* ClearOutIdle) (AddonInstance_VFSEntry* instance);
    void (__cdecl* DisconnectAll) (AddonInstance_VFSEntry* instance);
    bool (__cdecl* Delete) (AddonInstance_VFSEntry* instance, VFSURL* url);
    bool (__cdecl* Rename) (AddonInstance_VFSEntry* instance, VFSURL* url, VFSURL* url2);
    bool (__cdecl* DirectoryExists) (AddonInstance_VFSEntry* instance, VFSURL* url);
    bool (__cdecl* RemoveDirectory) (AddonInstance_VFSEntry* instance, VFSURL* url);
    bool (__cdecl* CreateDirectory) (AddonInstance_VFSEntry* instance, VFSURL* url);
    bool (__cdecl* GetDirectory) (AddonInstance_VFSEntry* instance,
                                  VFSURL* url,
                                  VFSDirEntry** entries,
                                  int* num_entries,
                                  VFSCallbacks* callbacks);
    bool (__cdecl* ContainsFiles) (AddonInstance_VFSEntry* instance,
                                   VFSURL* url,
                                   VFSDirEntry** entries,
                                   int* num_entries,
                                   char* rootpath);
    void (__cdecl* FreeDirectory) (AddonInstance_VFSEntry* instance, VFSDirEntry* entries, int num_entries);
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
  class CInstanceVFS : public IAddonInstance
  {
  public:
    CInstanceVFS(KODI_HANDLE instance)
      : IAddonInstance(ADDON_INSTANCE_VFS)
    {
      if (CAddonBase::m_interface->globalSingleInstance != nullptr)
        throw std::logic_error("kodi::addon::CInstanceVFS: Creation of multiple together with single instance way is not allowed!");

      SetAddonStruct(instance);
    }

    virtual ~CInstanceVFS() { }

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

    //! \brief Close a file
    //! \param context The context of the file
    //! \return True on success, false on failure
    //! \sa IFile::Close
    virtual bool Close(void* context) { return false; }

    //! \brief Stat a file
    //! \param url The URL of the file
    //! \param buffer The buffer to store results in
    //! \return -1 on error, 0 otherwise
    //! \sa IFile::Stat
    virtual int Stat(VFSURL* url, struct __stat64* buffer) { return 0; }

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
    virtual bool GetDirectory(VFSURL* url,
                              std::vector<kodi::vfs::CDirEntry>& entries,
                              VFSCallbacks* callbacks) { return false; }

    //! \brief Check if file should be presented as a directory (multiple streams)
    //! \param url The URL of the file
    //! \param entries The entries in the directory
    //! \param num_entries Number of entries in the directory
    //! \param rootpath Path to root directory if multiple entries
    //! \return Context for the directory listing
    //! \sa IFileDirectory::ContainsFiles, FreeDirectory
    virtual bool ContainsFiles(VFSURL* url,
                               std::vector<kodi::vfs::CDirEntry>& entries,
                               std::string& rootPath) { return false; }
  private:
    void SetAddonStruct(KODI_HANDLE instance)
    {
      if (instance == nullptr)
        throw std::logic_error("kodi::addon::CInstanceVFS: Creation with empty addon structure not allowed, table must be given from Kodi!");

      m_instanceData = static_cast<AddonInstance_VFSEntry*>(instance);
      m_instanceData->toAddon.addonInstance = this;
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

    inline static void* ADDON_Open(AddonInstance_VFSEntry* instance, VFSURL* url)
    {
      return instance->toAddon.addonInstance->Open(url);
    }

    inline static void* ADDON_OpenForWrite(AddonInstance_VFSEntry* instance, VFSURL* url, bool bOverWrite)
    {
      return instance->toAddon.addonInstance->OpenForWrite(url, bOverWrite);
    }

    inline static ssize_t ADDON_Read(AddonInstance_VFSEntry* instance, void* context, void* buffer, size_t uiBufSize)
    {
      return instance->toAddon.addonInstance->Read(context, buffer, uiBufSize);
    }

    inline static ssize_t ADDON_Write(AddonInstance_VFSEntry* instance, void* context, const void* buffer, size_t uiBufSize)
    {
      return instance->toAddon.addonInstance->Write(context, buffer, uiBufSize);
    }

    inline static int64_t ADDON_Seek(AddonInstance_VFSEntry* instance, void* context, int64_t position, int whence)
    {
      return instance->toAddon.addonInstance->Seek(context, position, whence);
    }

    inline static int ADDON_Truncate(AddonInstance_VFSEntry* instance, void* context, int64_t size)
    {
      return instance->toAddon.addonInstance->Truncate(context, size);
    }

    inline static int64_t ADDON_GetLength(AddonInstance_VFSEntry* instance, void* context)
    {
      return instance->toAddon.addonInstance->GetLength(context);
    }

    inline static int64_t ADDON_GetPosition(AddonInstance_VFSEntry* instance, void* context)
    {
      return instance->toAddon.addonInstance->GetPosition(context);
    }

    inline static int ADDON_GetChunkSize(AddonInstance_VFSEntry* instance, void* context)
    {
      return instance->toAddon.addonInstance->GetChunkSize(context);
    }

    inline static int ADDON_IoControl(AddonInstance_VFSEntry* instance, void* context, XFILE::EIoControl request, void* param)
    {
      return instance->toAddon.addonInstance->IoControl(context, request, param);
    }

    inline static int ADDON_Stat(AddonInstance_VFSEntry* instance, VFSURL* url, struct __stat64* buffer)
    {
      return instance->toAddon.addonInstance->Stat(url, buffer);
    }

    inline static bool ADDON_Close(AddonInstance_VFSEntry* instance, void* context)
    {
      return instance->toAddon.addonInstance->Close(context);
    }

    inline static bool ADDON_Exists(AddonInstance_VFSEntry* instance, VFSURL* url)
    {
      return instance->toAddon.addonInstance->Exists(url);
    }

    inline static void ADDON_ClearOutIdle(AddonInstance_VFSEntry* instance)
    {
      return instance->toAddon.addonInstance->ClearOutIdle();
    }

    inline static void ADDON_DisconnectAll(AddonInstance_VFSEntry* instance)
    {
      return instance->toAddon.addonInstance->DisconnectAll();
    }

    inline static bool ADDON_Delete(AddonInstance_VFSEntry* instance, VFSURL* url)
    {
      return instance->toAddon.addonInstance->Delete(url);
    }

    inline static bool ADDON_Rename(AddonInstance_VFSEntry* instance, VFSURL* url, VFSURL* url2)
    {
      return instance->toAddon.addonInstance->Rename(url, url2);
    }

    inline static bool ADDON_DirectoryExists(AddonInstance_VFSEntry* instance, VFSURL* url)
    {
      return instance->toAddon.addonInstance->DirectoryExists(url);
    }

    inline static bool ADDON_RemoveDirectory(AddonInstance_VFSEntry* instance, VFSURL* url)
    {
      return instance->toAddon.addonInstance->RemoveDirectory(url);
    }

    inline static bool ADDON_CreateDirectory(AddonInstance_VFSEntry* instance, VFSURL* url)
    {
      return instance->toAddon.addonInstance->CreateDirectory(url);
    }

    inline static bool ADDON_GetDirectory(AddonInstance_VFSEntry* instance,
                                   VFSURL* url,
                                   VFSDirEntry** retEntries,
                                   int* num_entries,
                                   VFSCallbacks* callbacks)
    {
      std::vector<kodi::vfs::CDirEntry> addonEntries;
      bool ret = instance->toAddon.addonInstance->GetDirectory(url, addonEntries, callbacks);
      if (ret)
      {
        VFSDirEntry* entries = (VFSDirEntry*)malloc(sizeof(VFSDirEntry) * addonEntries.size());
        for (unsigned int i = 0; i < addonEntries.size(); ++i)
        {
          entries[i].label = strdup(addonEntries[i].Label().c_str());
          entries[i].title = strdup(addonEntries[i].Title().c_str());
          entries[i].path = strdup(addonEntries[i].Path().c_str());
          entries[i].folder = addonEntries[i].IsFolder();
          entries[i].size = addonEntries[i].Size();

          entries[i].num_props = 0;
          const std::map<std::string, std::string>& props = addonEntries[i].GetProperties();
          if (!props.empty())
          {
            entries[i].properties = (VFSProperty*)malloc(sizeof(VFSProperty)*props.size());
            for (const auto& prop : props)
            {
              entries[i].properties[entries[i].num_props].name = strdup(prop.first.c_str());
              entries[i].properties[entries[i].num_props].val = strdup(prop.second.c_str());
              ++entries[i].num_props;
            }
          }
          else
            entries[i].properties = nullptr;
        }
        *retEntries = entries;
        *num_entries = addonEntries.size();
      }
      return ret;
    }

    inline static void ADDON_FreeDirectory(AddonInstance_VFSEntry* instance, VFSDirEntry* entries, int num_entries)
    {
      for (int i = 0; i < num_entries; ++i)
      {
        free(entries[i].label);
        if (entries[i].properties)
        {
          for (unsigned int j=0; j < entries[i].num_props; ++j)
          {
            free(entries[i].properties[j].name);
            free(entries[i].properties[j].val);
          }
          free(entries[i].properties);
        }
        free(entries[i].path);
      }
      free(entries);
    }

    inline static bool ADDON_ContainsFiles(AddonInstance_VFSEntry* instance,
                                           VFSURL* url,
                                           VFSDirEntry** retEntries,
                                           int* num_entries,
                                           char* rootpath)
    {
      std::string cppRootPath; 
      std::vector<kodi::vfs::CDirEntry> addonEntries;
      bool ret = instance->toAddon.addonInstance->ContainsFiles(url, addonEntries, cppRootPath);
      if (ret)
      {
        strncpy(rootpath, cppRootPath.c_str(), ADDON_STANDARD_STRING_LENGTH);

        VFSDirEntry* entries = (VFSDirEntry*)malloc(sizeof(VFSDirEntry) * addonEntries.size());
        for (unsigned int i = 0; i < addonEntries.size(); ++i)
        {
          entries[i].label = strdup(addonEntries[i].Label().c_str());
          entries[i].title = strdup(addonEntries[i].Title().c_str());
          entries[i].path = strdup(addonEntries[i].Path().c_str());
          entries[i].folder = addonEntries[i].IsFolder();
          entries[i].size = addonEntries[i].Size();

          entries[i].num_props = 0;
          const std::map<std::string, std::string>& props = addonEntries[i].GetProperties();
          if (!props.empty())
          {
            entries[i].properties = (VFSProperty*)malloc(sizeof(VFSProperty)*props.size());
            for (const auto& prop : props)
            {
              entries[i].properties[entries[i].num_props].name = strdup(prop.first.c_str());
              entries[i].properties[entries[i].num_props].val = strdup(prop.second.c_str());
              ++entries[i].num_props;
            }
          }
          else
            entries[i].properties = nullptr;
        }
        *retEntries = entries;
        *num_entries = addonEntries.size();
      }
      return ret;
    }

    AddonInstance_VFSEntry* m_instanceData;
  };

} /* namespace addon */
} /* namespace kodi */
