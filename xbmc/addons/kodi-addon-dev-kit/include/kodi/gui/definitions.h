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

#include <string>
#include <time.h>

/*
 * Internal Structures to have "C"-Style data transfer
 */
extern "C"
{

typedef struct AddonToKodiFuncTable_kodi_gui_dialogContextMenu
{
  int (*Open)(void* kodiBase, const char *heading, const char *entries[], unsigned int size);
} AddonToKodiFuncTable_kodi_gui_dialogContextMenu;
  
typedef struct AddonToKodiFuncTable_kodi_gui_dialogExtendedProgress
{ 
  void* (*New)(void* kodiBase, const char *title);
  void (*Delete)(void* kodiBase, void* handle);
  void (*Title)(void* kodiBase, void* handle, char &title, unsigned int &iMaxStringSize);
  void (*SetTitle)(void* kodiBase, void* handle, const char *title);
  void (*Text)(void* kodiBase, void* handle, char &text, unsigned int &iMaxStringSize);
  void (*SetText)(void* kodiBase, void* handle, const char *text);
  bool (*IsFinished)(void* kodiBase, void* handle);
  void (*MarkFinished)(void* kodiBase, void* handle);
  float (*Percentage)(void* kodiBase, void* handle);
  void (*SetPercentage)(void* kodiBase, void* handle, float fPercentage);
  void (*SetProgress)(void* kodiBase, void* handle, int currentItem, int itemCount);
} AddonToKodiFuncTable_kodi_gui_dialogExtendedProgress;
  
typedef struct AddonToKodiFuncTable_kodi_gui_dialogFileBrowser
{
  bool (*ShowAndGetDirectory)(void* kodiBase, const char* shares, const char* heading, char& path, unsigned int& iMaxStringSize, bool bWriteOnly);
  bool (*ShowAndGetFile)(void* kodiBase, const char* shares, const char* mask, const char* heading, char& file, unsigned int& iMaxStringSize, bool useThumbs, bool useFileDirectories);
  bool (*ShowAndGetFileFromDir)(void* kodiBase, const char* directory, const char* mask, const char* heading, char& file, unsigned int& iMaxStringSize, bool useThumbs, bool useFileDirectories, bool singleList);
  bool (*ShowAndGetFileList)(void* kodiBase, const char* shares, const char* mask, const char* heading, char**& path, unsigned int& entries, bool useThumbs, bool useFileDirectories);
  bool (*ShowAndGetSource)(void* kodiBase, char& path, unsigned int& iMaxStringSize, bool allowNetworkShares, const char* additionalShare, const char* strType);
  bool (*ShowAndGetImage)(void* kodiBase, const char* shares, const char* heading, char& path, unsigned int& iMaxStringSize);
  bool (*ShowAndGetImageList)(void* kodiBase,  const char* shares, const char* heading, char**& path, unsigned int& entries);
  void (*ClearList)(void* kodiBase, char**& path, unsigned int entries);
} AddonToKodiFuncTable_kodi_gui_dialogFileBrowser;

typedef struct AddonToKodiFuncTable_kodi_gui_dialogKeyboard
{
  bool (*ShowAndGetInputWithHead)(void* kodiBase, char &strTextString, unsigned int &iMaxStringSize, const char *heading, bool allowEmptyResult, bool hiddenInput, unsigned int autoCloseMs);
  bool (*ShowAndGetInput)(void* kodiBase, char &strTextString, unsigned int &iMaxStringSize, bool allowEmptyResult, unsigned int autoCloseMs);
  bool (*ShowAndGetNewPasswordWithHead)(void* kodiBase, char &newPassword, unsigned int &iMaxStringSize, const char *strHeading, bool allowEmptyResult, unsigned int autoCloseMs);
  bool (*ShowAndGetNewPassword)(void* kodiBase, char &strNewPassword, unsigned int &iMaxStringSize, unsigned int autoCloseMs);
  bool (*ShowAndVerifyNewPasswordWithHead)(void* kodiBase, char &strNewPassword, unsigned int &iMaxStringSize, const char *strHeading, bool allowEmpty, unsigned int autoCloseMs);
  bool (*ShowAndVerifyNewPassword)(void* kodiBase, char &strNewPassword, unsigned int &iMaxStringSize, unsigned int autoCloseMs);
  int (*ShowAndVerifyPassword)(void* kodiBase, char &strPassword, unsigned int &iMaxStringSize, const char *strHeading, int iRetries, unsigned int autoCloseMs);
  bool (*ShowAndGetFilter)(void* kodiBase, char &aTextString, unsigned int &iMaxStringSize, bool searching, unsigned int autoCloseMs);
  bool (*SendTextToActiveKeyboard)(void* kodiBase, const char *aTextString, bool closeKeyboard);
  bool (*isKeyboardActivated)(void* kodiBase);
} AddonToKodiFuncTable_kodi_gui_dialogKeyboard;
  
typedef struct AddonToKodiFuncTable_kodi_gui_dialogNumeric
{
  bool (*ShowAndVerifyNewPassword)(void* kodiBase, char &strNewPassword, unsigned int &iMaxStringSize);
  int (*ShowAndVerifyPassword)(void* kodiBase, char &strPassword, unsigned int &iMaxStringSize, const char *strHeading, int iRetries);
  bool (*ShowAndVerifyInput)(void* kodiBase, char &strPassword, unsigned int &iMaxStringSize, const char *strHeading, bool bVerifyInput);
  bool (*ShowAndGetTime)(void* kodiBase, tm &time, const char *strHeading);
  bool (*ShowAndGetDate)(void* kodiBase, tm &date, const char *strHeading);
  bool (*ShowAndGetIPAddress)(void* kodiBase, char &strIPAddress, unsigned int &iMaxStringSize, const char *strHeading);
  bool (*ShowAndGetNumber)(void* kodiBase, char &strInput, unsigned int &iMaxStringSize, const char *strHeading, unsigned int iAutoCloseTimeoutMs);
  bool (*ShowAndGetSeconds)(void* kodiBase, char &timeString, unsigned int &iMaxStringSize, const char *strHeading);
} AddonToKodiFuncTable_kodi_gui_dialogNumeric;

typedef struct AddonToKodiFuncTable_kodi_gui_dialogOK
{
  void (*show_and_get_input_single_text)(void* kodiBase, const char *heading, const char *text);
  void (*show_and_get_input_line_text)(void* kodiBase, const char *heading, const char *line0, const char *line1, const char *line2);
} AddonToKodiFuncTable_kodi_gui_dialogOK;

typedef struct AddonToKodiFuncTable_kodi_gui_dialogProgress
{
  void* (*New)(void* kodiBase);
  void (*Delete)(void* kodiBase, void* handle);
  void (*Open)(void* kodiBase, void* handle);
  void (*SetHeading)(void* kodiBase, void* handle, const char* heading);
  void (*SetLine)(void* kodiBase, void* handle, unsigned int iLine, const char* line);
  void (*SetCanCancel)(void* kodiBase, void* handle, bool bCanCancel);
  bool (*IsCanceled)(void* kodiBase, void* handle);
  void (*SetPercentage)(void* kodiBase, void* handle, int iPercentage);
  int (*GetPercentage)(void* kodiBase, void* handle);
  void (*ShowProgressBar)(void* kodiBase, void* handle, bool bOnOff);
  void (*SetProgressMax)(void* kodiBase, void* handle, int iMax);
  void (*SetProgressAdvance)(void* kodiBase, void* handle, int nSteps);
  bool (*Abort)(void* kodiBase, void* handle);
} AddonToKodiFuncTable_kodi_gui_dialogProgress;

typedef struct AddonToKodiFuncTable_kodi_gui_dialogSelect
{
  int (*Open)(void* kodiBase, const char *heading, const char *entries[], unsigned int size, int selected, bool autoclose);
} AddonToKodiFuncTable_kodi_gui_dialogSelect;

typedef struct AddonToKodiFuncTable_kodi_gui_dialogTextViewer
{
  void (*Open)(void* kodiBase, const char *heading, const char *text);
} AddonToKodiFuncTable_kodi_gui_dialogTextViewer;

typedef struct AddonToKodiFuncTable_kodi_gui_dialogYesNo
{
  bool (*ShowAndGetInputSingleText)(void* kodiBase, const char *heading, const char *text, bool &bCanceled, const char *noLabel, const char *yesLabel);
  bool (*ShowAndGetInputLineText)(void* kodiBase, const char *heading, const char *line0, const char *line1, const char *line2, const char *noLabel, const char *yesLabel);
  bool (*ShowAndGetInputLineButtonText)(void* kodiBase, const char *heading, const char *line0, const char *line1, const char *line2, bool &bCanceled, const char *noLabel, const char *yesLabel);
} AddonToKodiFuncTable_kodi_gui_dialogYesNo;

typedef struct AddonToKodiFuncTable_kodi_gui_general
{
  void (*lock)();
  void (*unlock)();
  int (*get_screen_height)(void* kodiBase);
  int (*get_screen_width)(void* kodiBase);
  int (*get_video_resolution)(void* kodiBase);
  int (*get_current_window_dialog_id)(void* kodiBase);
  int (*get_current_window_id)(void* kodiBase);
} AddonToKodiFuncTable_kodi_gui_general;

typedef struct AddonToKodiFuncTable_kodi_gui
{
  AddonToKodiFuncTable_kodi_gui_general general;
  AddonToKodiFuncTable_kodi_gui_dialogContextMenu dialogContextMenu;
  AddonToKodiFuncTable_kodi_gui_dialogExtendedProgress dialogExtendedProgress;
  AddonToKodiFuncTable_kodi_gui_dialogFileBrowser dialogFileBrowser;
  AddonToKodiFuncTable_kodi_gui_dialogKeyboard dialogKeyboard;
  AddonToKodiFuncTable_kodi_gui_dialogNumeric dialogNumeric;
  AddonToKodiFuncTable_kodi_gui_dialogOK dialogOK;
  AddonToKodiFuncTable_kodi_gui_dialogProgress dialogProgress;
  AddonToKodiFuncTable_kodi_gui_dialogSelect dialogSelect;
  AddonToKodiFuncTable_kodi_gui_dialogTextViewer dialogTextViewer;
  AddonToKodiFuncTable_kodi_gui_dialogYesNo dialogYesNo;
} AddonToKodiFuncTable_kodi_gui;

} /* extern "C" */
