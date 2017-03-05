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

typedef struct AddonToKodiFuncTable_kodi_gui_controlButton
{
  void (*SetVisible)(void* kodiBase, void* handle, bool visible);
  void (*SetEnabled)(void* kodiBase, void* handle, bool enabled);
  void (*SetLabel)(void* kodiBase, void* handle, const char *label);
  void (*GetLabel)(void* kodiBase, void* handle, char &label, unsigned int &iMaxStringSize);
  void (*SetLabel2)(void* kodiBase, void* handle, const char *label);
  void (*GetLabel2)(void* kodiBase, void* handle, char &label, unsigned int &iMaxStringSize);
} AddonToKodiFuncTable_kodi_gui_controlButton;

typedef struct AddonToKodiFuncTable_kodi_gui_controlEdit
{
  void (*SetVisible)(void* kodiBase, void* handle, bool visible);
  void (*SetEnabled)(void* kodiBase, void* handle, bool enabled);
  void (*SetLabel)(void* kodiBase, void* handle, const char *label);
  void (*GetLabel)(void* kodiBase, void* handle, char &label, unsigned int &iMaxStringSize);
  void (*SetText)(void* kodiBase, void* handle, const char *text);
  void (*GetText)(void* kodiBase, void* handle, char &text, unsigned int &iMaxStringSize);
  void (*SetCursorPosition)(void* kodiBase, void* handle, unsigned int iPosition);
  unsigned int (*GetCursorPosition)(void* kodiBase, void* handle);
  void (*SetInputType)(void* kodiBase, void* handle, int type, const char *heading);
} AddonToKodiFuncTable_kodi_gui_controlEdit;
  
typedef struct AddonToKodiFuncTable_kodi_gui_controlFadeLabel
{
  void (*SetVisible)(void* kodiBase, void* handle, bool visible);
  void (*AddLabel)(void* kodiBase, void* handle, const char *text);
  void (*GetLabel)(void* kodiBase, void* handle, char &text, unsigned int &iMaxStringSize);
  void (*SetScrolling)(void* kodiBase, void* handle, bool scroll);
  void (*Reset)(void* kodiBase, void* handle);
} AddonToKodiFuncTable_kodi_gui_controlFadeLabel;

typedef struct AddonToKodiFuncTable_kodi_gui_controlImage
{
  void (*SetVisible)(void* kodiBase, void* handle, bool visible);
  void (*SetFileName)(void* kodiBase, void* handle, const char* strFileName, const bool useCache);
  void (*SetColorDiffuse)(void* kodiBase, void* handle, uint32_t colorDiffuse);
} AddonToKodiFuncTable_kodi_gui_controlImage;

typedef struct AddonToKodiFuncTable_kodi_gui_controlLabel
{
  void (*SetVisible)(void* kodiBase, void* handle, bool visible);
  void (*SetLabel)(void* kodiBase, void* handle, const char *text);
  void (*GetLabel)(void* kodiBase, void* handle, char &text, unsigned int &iMaxStringSize);
} AddonToKodiFuncTable_kodi_gui_controlLabel;

typedef struct AddonToKodiFuncTable_kodi_gui_controlProgress
{
  void (*SetVisible)(void* kodiBase, void* handle, bool visible);
  void (*SetPercentage)(void* kodiBase, void* handle, float fPercent);
  float (*GetPercentage)(void* kodiBase, void* handle);
} AddonToKodiFuncTable_kodi_gui_controlProgress;

typedef struct AddonToKodiFuncTable_kodi_gui_controlRadioButton
{
  void (*SetVisible)(void* kodiBase, void* handle, bool yesNo);
  void (*SetEnabled)(void* kodiBase, void* handle, bool enabled);
  void (*SetLabel)(void* kodiBase, void* handle, const char *text);
  void (*GetLabel)(void* kodiBase, void* handle, char &text, unsigned int &iMaxStringSize);
  void (*SetSelected)(void* kodiBase, void* handle, bool yesNo);
  bool (*IsSelected)(void* kodiBase, void* handle);
} AddonToKodiFuncTable_kodi_gui_controlRadioButton;

typedef struct AddonToKodiFuncTable_kodi_gui_controlRendering
{
  void (*SetCallbacks)(void* kodiBase, void* handle, void* clienthandle,
      bool    (*createCB)(void*,int,int,int,int,void*),
      void    (*renderCB)(void*),
      void    (*stopCB)(void*),
      bool    (*dirtyCB)(void*));
  void (*Delete)(void *kodiBase, void* handle);
} AddonToKodiFuncTable_kodi_gui_controlRendering;

typedef struct AddonToKodiFuncTable_kodi_gui_controlSettingsSlider
{
  void (*SetVisible)(void* kodiBase, void* handle, bool yesNo);
  void (*SetEnabled)(void* kodiBase, void* handle, bool yesNo);
  void (*SetText)(void* kodiBase, void* handle, const char *label);
  void (*Reset)(void* kodiBase, void* handle);
  void (*SetIntRange)(void* kodiBase, void* handle, int iStart, int iEnd);
  void (*SetIntValue)(void* kodiBase, void* handle, int iValue);
  int (*GetIntValue)(void* kodiBase, void* handle);
  void (*SetIntInterval)(void* kodiBase, void* handle, int iInterval);
  void (*SetPercentage)(void* kodiBase, void* handle, float fPercent);
  float (*GetPercentage)(void* kodiBase, void* handle);
  void (*SetFloatRange)(void* kodiBase, void* handle, float fStart, float fEnd);
  void (*SetFloatValue)(void* kodiBase, void* handle, float fValue);
  float (*GetFloatValue)(void* kodiBase, void* handle);
  void (*SetFloatInterval)(void* kodiBase, void* handle, float fInterval);
} AddonToKodiFuncTable_kodi_gui_controlSettingsSlider;

typedef struct AddonToKodiFuncTable_kodi_gui_controlSlider
{
  void (*SetVisible)(void* kodiBase, void* handle, bool yesNo);
  void (*SetEnabled)(void* kodiBase, void* handle, bool yesNo);
  void (*Reset)(void* kodiBase, void* handle);
  void (*GetDescription)(void* kodiBase, void* handle, char &text, unsigned int &iMaxStringSize);
  void (*SetIntRange)(void* kodiBase, void* handle, int start, int end);
  void (*SetIntValue)(void* kodiBase, void* handle, int value);
  int (*GetIntValue)(void* kodiBase, void* handle);
  void (*SetIntInterval)(void* kodiBase, void* handle, int interval);
  void (*SetPercentage)(void* kodiBase, void* handle, float percent);
  float (*GetPercentage)(void* kodiBase, void* handle);
  void (*SetFloatRange)(void* kodiBase, void* handle, float start, float end);
  void (*SetFloatValue)(void* kodiBase, void* handle, float value);
  float (*GetFloatValue)(void* kodiBase, void* handle);
  void (*SetFloatInterval)(void* kodiBase, void* handle, float interval);
} AddonToKodiFuncTable_kodi_gui_controlSlider;

typedef struct AddonToKodiFuncTable_kodi_gui_controlSpin
{
  void (*SetVisible)(void* kodiBase, void* spinhandle, bool visible);
  void (*SetEnabled)(void* kodiBase, void* spinhandle, bool enabled);
  void (*SetText)(void* kodiBase, void* spinhandle, const char* text);
  void (*Reset)(void* kodiBase, void* spinhandle);
  void (*SetType)(void* kodiBase, void* handle, int type);
  void (*AddStringLabel)(void* kodiBase, void* handle, const char* label, const char* value);
  void (*SetStringValue)(void* kodiBase, void* handle, const char* value);
  void (*GetStringValue)(void* kodiBase, void* handle, char& value, unsigned int& maxStringSize);
  void (*AddIntLabel)(void* kodiBase, void* handle, const char* label, int value);
  void (*SetIntRange)(void* kodiBase, void* handle, int start, int end);
  void (*SetIntValue)(void* kodiBase, void* handle, int value);
  int (*GetIntValue)(void* kodiBase, void* handle);
  void (*SetFloatRange)(void* kodiBase, void* handle, float start, float end);
  void (*SetFloatValue)(void* kodiBase, void* handle, float value);
  float (*GetFloatValue)(void* kodiBase, void* handle);
  void (*SetFloatInterval)(void* kodiBase, void* handle, float interval);
} AddonToKodiFuncTable_kodi_gui_controlSpin;

typedef struct AddonToKodiFuncTable_kodi_gui_controlTextBox
{
  void (*SetVisible)(void* kodiBase, void* spinhandle, bool visible);
  void (*Reset)(void* kodiBase, void* handle);
  void (*SetText)(void* kodiBase, void* handle, const char* text);
  void (*GetText)(void* kodiBase, void* handle, char &text, unsigned int &iMaxStringSize);
  void (*Scroll)(void* kodiBase, void* handle, unsigned int scroll);
  void (*SetAutoScrolling)(void* kodiBase, void* handle, int delay, int time, int repeat);
} AddonToKodiFuncTable_kodi_gui_controlTextBox;

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

typedef struct AddonToKodiFuncTable_kodi_gui_listItem
{
  void* (*Create)(void* kodiBase, const char* label, const char* label2, const char* iconImage, const char* thumbnailImage, const char* path);
  void (*Destroy)(void* kodiBase, void* handle);
  void (*GetLabel)(void* kodiBase, void* handle, char& label, unsigned int &iMaxStringSize);
  void (*SetLabel)(void* kodiBase, void* handle, const char* label);
  void (*GetLabel2)(void* kodiBase, void* handle, char& label, unsigned int& iMaxStringSize);
  void (*SetLabel2)(void* kodiBase, void* handle, const char* label);
  void (*GetIconImage)(void* kodiBase, void* handle, char& image, unsigned int &iMaxStringSize);
  void (*SetIconImage)(void* kodiBase, void* handle, const char* image);
  void (*GetOverlayImage)(void* kodiInstance, void* handle, char& image, unsigned int& iMaxStringSize);
  void (*SetOverlayImage)(void* kodiInstance, void* handle, unsigned int image, bool bOnOff);
  void (*SetThumbnailImage)(void* kodiInstance, void* handle, const char* image);
  void (*SetArt)(void* kodiBase, void* handle, const char* type, const char* url);
  char* (*GetArt)(void* kodiBase, void* handle, const char* type);
  void (*SetArtFallback)(void* kodiBase, void* handle, const char* from, const char* to);
  bool (*HasArt)(void* kodiBase, void* handle, const char *type);
  void (*SetUniqueIDs)(void* kodiBase, void* handle, const char** ids[2], unsigned int entries, const char* defaultrating);
  char* (*GetUniqueID)(void* kodiBase, void* handle, const char* key);
  void (*SetRating)(void* kodiBase, void* handle, const char* type, float rating, int votes, bool defaultt);
  float (*GetRating)(void* kodiBase, void* handle, const char* key);
  void (*AddSeason)(void* kodiBase, void* handle, int number, const char* name);
  int (*GetVotes)(void* kodiBase, void* handle, const char* key);
  void (*Select)(void* kodiBase, void* handle, bool bOnOff);
  bool (*IsSelected)(void* kodiBase, void* handle);
  void (*SetInfo)(void* kodiBase, void* handle, const char* type, const char** infoLabels[2], unsigned int entries);
/// @todo void (*SetCast)(void* kodiBase, void* handle, ...);
/// @todo void (*SetAvailableFanart)(void* kodiBase, void* handle, ...);
  void (*AddAvailableThumb)(void* kodiBase, void* handle, const char* url, const char* aspect, const char* referrer, const char* cache, bool post, bool isgze, int season);
  int (*GetDuration)(void* kodiBase, void* handle);
  bool (*HasIcon)(void* kodiBase, void* handle);
  bool (*HasOverlay)(void* kodiBase, void* handle);
  bool (*IsFileItem)(void* kodiBase, void* handle);
  bool (*IsFolder)(void* kodiBase, void* handle);
  void (*SetProperty)(void* kodiBase, void* handle, const char *key, const char *value);
  void (*GetProperty)(void* kodiBase, void* handle, const char* key, char& property, unsigned int &iMaxStringSize);
  void (*ClearProperty)(void* kodiBase, void* handle, const char* key);
  void (*ClearProperties)(void* kodiBase, void* handle);
  bool (*HasProperties)(void* kodiBase, void* handle);
  bool (*HasProperty)(void* kodiBase, void* handle, const char* key);
  void (*SetPath)(void* kodiBase, void* handle, const char* path);
  char* (*GetPath)(void* kodiBase, void* handle);
  void (*SetSubtitles)(void* kodiBase, void* handle, const char** streams, unsigned int entries);
  void (*SetMimeType)(void* kodiBase, void* handle, const char* mimetype);
  void (*SetContentLookup)(void* kodiBase, void* handle, bool enable);
  void (*AddContextMenuItems)(void* kodiBase, void* handle, const char** streams[2], unsigned int entries, bool replaceItems);
  void (*AddStreamInfo)(void* kodiBase, void* handle, const char* cType, const char** dictionary[2], unsigned int entries);
} AddonToKodiFuncTable_kodi_gui_listItem;

typedef struct AddonToKodiFuncTable_kodi_gui_window
{
  void* (*New)(void* kodiBase, const char* xmlFilename, const char* defaultSkin, bool forceFallback, bool asDialog);
  void (*Delete)(void* kodiBase, void* handle);
  void (*SetCallbacks)(void* kodiBase, void* handle, void* clienthandle,
       bool (*)(void* handle),
       bool (*)(void* handle, int),
       bool (*)(void* handle, int),
       bool (*)(void* handle, int));
  bool (*Show)(void* kodiBase, void* handle);
  bool (*Close)(void* kodiBase, void* handle);
  bool (*DoModal)(void* kodiBase, void* handle);
  bool (*SetFocusId)(void* kodiBase, void* handle, int iControlId);
  int (*GetFocusId)(void* kodiBase, void* handle);
  void (*SetProperty)(void* kodiBase, void* handle, const char* key, const char* value);
  void (*SetPropertyInt)(void* kodiBase, void* handle, const char* key, int value);
  void (*SetPropertyBool)(void* kodiBase, void* handle, const char* key, bool value);
  void (*SetPropertyDouble)(void* kodiBase, void* handle, const char* key, double value);
  void (*GetProperty)(void* kodiBase, void* handle, const char *key, char &property, unsigned int &iMaxStringSize);
  int (*GetPropertyInt)(void* kodiBase, void* handle, const char  *key);
  bool (*GetPropertyBool)(void* kodiBase, void* handle, const char *key);
  double (*GetPropertyDouble)(void* kodiBase, void* handle, const char* key);
  void (*ClearProperties)(void* kodiBase, void* handle);
  void (*ClearProperty)(void* kodiBase, void* handle, const char  *key);
  int (*GetListSize)(void* kodiBase, void* handle);
  void (*ClearList)(void* kodiBase, void* handle);
  void* (*AddItem)(void* kodiBase, void* handle, void* item, int itemPosition);
  void* (*AddStringItem)(void* kodiBase, void* handle, const char  *itemName, int itemPosition);
  void (*RemoveItem)(void* kodiBase, void* handle, int itemPosition);
  void (*RemoveItemFile)(void* kodiBase, void* handle, void* fileItem);
  void* (*GetListItem)(void* kodiBase, void* handle, int listPos);
  void (*SetCurrentListPosition)(void* kodiBase, void* handle, int listPos);
  int (*GetCurrentListPosition)(void* kodiBase, void* handle);
  void (*SetControlLabel)(void* kodiBase, void* handle, int controlId, const char* label);
  void (*MarkDirtyRegion)(void* kodiBase, void* handle);

  void* (*GetControl_Button)(void* kodiBase, void* handle, int controlId);
  void* (*GetControl_Edit)(void* kodiBase, void* handle, int controlId);
  void* (*GetControl_FadeLabel)(void* kodiBase, void* handle, int controlId);
  void* (*GetControl_Image)(void* kodiBase, void* handle, int controlId);
  void* (*GetControl_Label)(void* kodiBase, void* handle, int controlId);
  void* (*GetControl_Spin)(void* kodiBase, void* handle, int controlId);
  void* (*GetControl_RadioButton)(void* kodiBase, void* handle, int controlId);
  void* (*GetControl_Progress)(void* kodiBase, void* handle, int controlId);
  void* (*GetControl_RenderAddon)(void* kodiBase, void* handle, int controlId);
  void* (*GetControl_Slider)(void* kodiBase, void* handle, int controlId);
  void* (*GetControl_SettingsSlider)(void* kodiBase, void* handle, int controlId);
  void* (*GetControl_TextBox)(void* kodiBase, void* handle, int controlId);
} AddonToKodiFuncTable_kodi_gui_window;

typedef struct AddonToKodiFuncTable_kodi_gui
{
  AddonToKodiFuncTable_kodi_gui_general general;
  AddonToKodiFuncTable_kodi_gui_controlButton controlButton;
  AddonToKodiFuncTable_kodi_gui_controlEdit controlEdit;
  AddonToKodiFuncTable_kodi_gui_controlFadeLabel controlFadeLabel;
  AddonToKodiFuncTable_kodi_gui_controlImage controlImage;
  AddonToKodiFuncTable_kodi_gui_controlLabel controlLabel;
  AddonToKodiFuncTable_kodi_gui_controlProgress controlProgress;
  AddonToKodiFuncTable_kodi_gui_controlRadioButton controlRadioButton;
  AddonToKodiFuncTable_kodi_gui_controlRendering controlRendering;
  AddonToKodiFuncTable_kodi_gui_controlSettingsSlider controlSettingsSlider;
  AddonToKodiFuncTable_kodi_gui_controlSlider controlSlider;
  AddonToKodiFuncTable_kodi_gui_controlSpin controlSpin;
  AddonToKodiFuncTable_kodi_gui_controlTextBox controlTextBox;
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
  AddonToKodiFuncTable_kodi_gui_listItem listItem;
  AddonToKodiFuncTable_kodi_gui_window window;
} AddonToKodiFuncTable_kodi_gui;

} /* extern "C" */

//============================================================================
///
/// \ingroup cpp_kodi_gui_CControlRendering_Defs cpp_kodi_gui_CWindow_Defs
/// @{
/// @brief Handle to use as independent pointer for GUI
typedef void* GUIHANDLE;
/// @}
//----------------------------------------------------------------------------

//============================================================================
///
/// \ingroup cpp_kodi_gui_CListItem_Defs
/// @{
/// @anchor kodi_gui_listitem_CastProperties
/// @brief Cast properties entry used on a list item
typedef struct CastProperties
{
  /// Cast name, e.g. Michael C. Hall
  std::string name;
  /// Cast role, e.g. Dexter
  std::string role;
  /// Thumbnail URL, e.g. http://www.someurl.com/someimage.png
  std::string thumbnail;
  /// Order number
  int order;
} CastProperties;
/// @}
//----------------------------------------------------------------------------

//============================================================================
///
/// \ingroup cpp_kodi_gui_CListItem_Defs
/// @{
/// @anchor FanartProperties
/// @brief Fanart properties entry used on a list item
typedef struct FanartProperties
{
  /// Image, e.g. http://www.someurl.com/someimage.png
  std::string image;
  /// Preview, e.g. http://www.someurl.com/somepreviewimage.png
  std::string preview;
  /// Colors (either comma separated Kodi hex values ("FFFFFFFF,DDDDDDDD") or
  /// TVDB RGB Int Triplets ("|68,69,59|69,70,58|78,78,68|"))
  std::string colors;
} FanartProperties;
/// @}
//----------------------------------------------------------------------------

//============================================================================
///
/// \ingroup cpp_kodi_gui_CControlEdit_Defs
/// @{
/// @anchor AddonGUIInputType
/// @brief Text input types used on CControlEdit
enum AddonGUIInputType
{
  /// Text inside edit control only readable
  ADDON_INPUT_TYPE_READONLY = -1,
  /// Normal text entries
  ADDON_INPUT_TYPE_TEXT = 0,
  /// To use on edit control only numeric numbers
  ADDON_INPUT_TYPE_NUMBER,
  /// To insert seconds
  ADDON_INPUT_TYPE_SECONDS,
  /// To insert time
  ADDON_INPUT_TYPE_TIME,
  /// To insert a date
  ADDON_INPUT_TYPE_DATE,
  /// Used for write in IP addresses
  ADDON_INPUT_TYPE_IPADDRESS,
  /// Text field used as password entry field with not visible text
  ADDON_INPUT_TYPE_PASSWORD,
  /// Text field used as password entry field with not visible text but
  /// returned as MD5 value
  ADDON_INPUT_TYPE_PASSWORD_MD5,
  /// Use text field for search purpose
  ADDON_INPUT_TYPE_SEARCH,
  /// Text field as filter
  ADDON_INPUT_TYPE_FILTER,
  ///
  ADDON_INPUT_TYPE_PASSWORD_NUMBER_VERIFY_NEW
};
/// @}
//----------------------------------------------------------------------------

//============================================================================
///
/// \ingroup kodi_addon_key_action_ids cpp_kodi_gui_CWindow_Defs
/// @{
/// @brief Actions that we have defined.
///
enum AddonGUIActionType
{
  ///
  ADDON_ACTION_NONE                    = 0,

  /// @brief Action string: <b><c>Left</c></b>
  ///
  /// Move left off a control.
  ///
  ADDON_ACTION_MOVE_LEFT               = 1,

  /// @brief Action string: <b><c>Right</c></b>
  ///
  /// Move right off a control.
  ADDON_ACTION_MOVE_RIGHT              = 2,

  /// @brief Action string: <b><c>Up</c></b>
  ///
  /// Move up off a control.
  ADDON_ACTION_MOVE_UP                 = 3,

  /// @brief Action string: <b><c>Down</c></b>
  ///
  /// Move down off a control.
  ADDON_ACTION_MOVE_DOWN               = 4,

  /// @brief Action string: <b><c>PageUp</c></b>
  ///
  /// Scroll up on page in a list, thumb, or text view.
  ADDON_ACTION_PAGE_UP                 = 5,

  /// @brief Action string: <b><c>PageDown</c></b>
  ///
  /// Scroll down on page in a list, thumb, or text view.
  ADDON_ACTION_PAGE_DOWN               = 6,

  /// @brief Action string: <b><c>Select</c></b>
  ///
  /// Select a button, or an item from a list of thumb view.
  ADDON_ACTION_SELECT_ITEM             = 7,

  /// @brief Action string: <b><c>Highlight</c></b>
  ///
  /// Highlight an item in a list or thumb view.
  ADDON_ACTION_HIGHLIGHT_ITEM          = 8,

  /// @brief Action string: <b><c>ParentDir</c></b>
  ///
  /// Go up a folder to the parent folder.
  ADDON_ACTION_PARENT_DIR              = 9,

  /// @brief Action string: <b><c>PreviousMenu</c></b>
  ///
  /// Go back to the previous menu screen.
  ADDON_ACTION_PREVIOUS_MENU           = 10,

  /// @brief Action string: <b><c>Info</c></b>
  ///
  /// Show the information about the currently highlighted item, or currently
  /// playing item.
  ADDON_ACTION_SHOW_INFO               = 11,

  /// @brief Action string: <b><c>Pause</c></b>
  ///
  /// Pause the currently playing item.
  ADDON_ACTION_PAUSE                   = 12,

  /// @brief Action string: <b><c>Stop</c></b>
  ///
  /// Stop the currently playing item.
  ADDON_ACTION_STOP                    = 13,

  /// @brief Action string: <b><c>SkipNext</c></b>
  ///
  /// Skip to next video in playlist. If no playlist, then skip to next chapter
  /// in video.
  ADDON_ACTION_NEXT_ITEM               = 14,

  /// @brief Action string: <b><c>SkipPrevious</c></b>
  ///
  /// Skip to previous video in playlist. If no playlist, then skip to
  /// previous chapter in video.
  ADDON_ACTION_PREV_ITEM               = 15,

  /// Can be used to specify specific action in a window, Playback control is
  /// handled in ACTION_PLAYER_*
  ADDON_ACTION_FORWARD                 = 16,

  /// Can be used to specify specific action in a window, Playback control is
  /// handled in ACTION_PLAYER_*
  ADDON_ACTION_REWIND                  = 17,


  /// @brief Action string: <b><c>Fullscreen</c></b>
  ///
  /// toggle between GUI and movie or GUI and visualisation.
  ADDON_ACTION_SHOW_GUI                = 18,

  /// @brief Action string: <b><c>AspectRatio</c></b>
  ///
  /// toggle quick-access zoom modes. Can b used in videoFullScreen.xml
  /// window id=2005
  ADDON_ACTION_ASPECT_RATIO            = 19,

  /// @brief Action string: <b><c>StepForward</c></b>
  ///
  /// seek +1% in the movie. Can b used in videoFullScreen.xml window id=2005
  ADDON_ACTION_STEP_FORWARD            = 20,

  /// @brief Action string: <b><c>StepBack</c></b>
  ///
  /// seek -1% in the movie. Can b used in videoFullScreen.xml window id=2005
  ADDON_ACTION_STEP_BACK               = 21,

  /// @brief Action string: <b><c>BigStepForward</c></b>
  ///
  /// seek +10% in the movie. Can b used in videoFullScreen.xml window id=2005
  ADDON_ACTION_BIG_STEP_FORWARD        = 22,

  /// @brief Action string: <b><c>BigStepBack</c></b>
  ///
  /// seek -10% in the movie. Can b used in videoFullScreen.xml window id=2005
  ADDON_ACTION_BIG_STEP_BACK           = 23,

  /// @brief Action string: <b><c>OSD</c></b>
  ///
  /// show/hide OSD. Can b used in videoFullScreen.xml window id=2005
  ADDON_ACTION_SHOW_OSD                = 24,

  /// @brief Action string: <b><c>ShowSubtitles</c></b>
  ///
  /// turn subtitles on/off. Can be used in videoFullScreen.xml window id=2005
  ADDON_ACTION_SHOW_SUBTITLES          = 25,

  /// @brief Action string: <b><c>NextSubtitle</c></b>
  ///
  /// switch to next subtitle of movie. Can be used in videoFullScreen.xml
  /// window id=2005
  ADDON_ACTION_NEXT_SUBTITLE           = 26,

  /// @brief Action string: <b><c>PlayerDebug</c></b>
  ///
  /// show debug info for VideoPlayer
  ADDON_ACTION_PLAYER_DEBUG            = 27,

  /// @brief Action string: <b><c>NextPicture</c></b>
  ///
  /// show next picture of slideshow. Can b used in slideshow.xml window id=2007
  ADDON_ACTION_NEXT_PICTURE            = 28,

  /// @brief Action string: <b><c>PreviousPicture</c></b>
  ///
  /// show previous picture of slideshow. Can b used in slideshow.xml window
  /// id=2007
  ADDON_ACTION_PREV_PICTURE            = 29,

  /// @brief Action string: <b><c>ZoomOut</c></b>
  ///
  /// zoom in picture during slideshow. Can b used in slideshow.xml window
  /// id=2007
  ADDON_ACTION_ZOOM_OUT                = 30,

  /// @brief Action string: <b><c>ZoomIn</c></b>
  ///
  /// zoom out picture during slideshow. Can b used in slideshow.xml window
  /// id=2007
  ADDON_ACTION_ZOOM_IN                 = 31,

  /// used to toggle between source view and destination view. Can be used in
  /// myfiles.xml window id=3
  ADDON_ACTION_TOGGLE_SOURCE_DEST      = 32,

  /// @brief Action string: <b><c>Playlist</c></b>
  ///
  /// used to toggle between current view and playlist view. Can b used in all
  /// mymusic xml files
  ADDON_ACTION_SHOW_PLAYLIST           = 33,

  /// @brief Action string: <b><c>Queue</c></b>
  ///
  /// used to queue a item to the playlist. Can b used in all mymusic xml files
  ADDON_ACTION_QUEUE_ITEM              = 34,

  /// not used anymore
  ADDON_ACTION_REMOVE_ITEM             = 35,

  /// not used anymore
  ADDON_ACTION_SHOW_FULLSCREEN         = 36,


  /// @brief Action string: <b><c>ZoomNormal</c></b>
  ///
  /// Zoom 1x picture during slideshow. Can b used in slideshow.xml window id=2007
  ADDON_ACTION_ZOOM_LEVEL_NORMAL       = 37,

  /// @brief Action string: <b><c>ZoomLevel1</c></b>
  ///
  /// Zoom 2x picture during slideshow. Can b used in slideshow.xml window id=2007
  ADDON_ACTION_ZOOM_LEVEL_1            = 38,

  /// @brief Action string: <b><c>ZoomLevel2</c></b>
  ///
  /// Zoom 3x picture during slideshow. Can b used in slideshow.xml window id=2007
  ADDON_ACTION_ZOOM_LEVEL_2            = 39,

  /// @brief Action string: <b><c>ZoomLevel3</c></b>
  ///
  /// Zoom 4x picture during slideshow. Can b used in slideshow.xml window id=2007
  ADDON_ACTION_ZOOM_LEVEL_3            = 40,

  /// @brief Action string: <b><c>ZoomLevel4</c></b>
  ///
  /// Zoom 5x picture during slideshow. Can b used in slideshow.xml window id=2007
  ADDON_ACTION_ZOOM_LEVEL_4            = 41,

  /// @brief Action string: <b><c>ZoomLevel5</c></b>
  ///
  /// Zoom 6x picture during slideshow. Can b used in slideshow.xml window id=2007
  ADDON_ACTION_ZOOM_LEVEL_5            = 42,

  /// @brief Action string: <b><c>ZoomLevel6</c></b>
  ///
  /// Zoom 7x picture during slideshow. Can b used in slideshow.xml window id=2007
  ADDON_ACTION_ZOOM_LEVEL_6            = 43,

  /// @brief Action string: <b><c>ZoomLevel7</c></b>
  ///
  /// Zoom 8x picture during slideshow. Can b used in slideshow.xml window id=2007
  ADDON_ACTION_ZOOM_LEVEL_7            = 44,

  /// @brief Action string: <b><c>ZoomLevel8</c></b>
  ///
  /// Zoom 9x picture during slideshow. Can b used in slideshow.xml window id=2007
  ADDON_ACTION_ZOOM_LEVEL_8            = 45,

  /// @brief Action string: <b><c>ZoomLevel9</c></b>
  ///
  /// Zoom 10x picture during slideshow. Can b used in slideshow.xml window id=2007
  ADDON_ACTION_ZOOM_LEVEL_9            = 46,


  /// @brief Action string: <b><c>NextCalibration</c></b>
  ///
  /// select next arrow. Can b used in: settingsScreenCalibration.xml windowid=11
  ADDON_ACTION_CALIBRATE_SWAP_ARROWS   = 47,

  /// @brief Action string: <b><c>ResetCalibration</c></b>
  ///
  /// reset calibration to defaults. Can be used in:
  /// settingsScreenCalibration.xml windowid=11/settingsUICalibration.xml
  /// windowid=10
  ADDON_ACTION_CALIBRATE_RESET         = 48,

  /// @brief Action string: <b><c>AnalogMove</c></b>
  ///
  /// analog thumbstick move. Can be used in: slideshow.xml window
  /// id=2007/settingsScreenCalibration.xml windowid=11/settingsUICalibration.xml
  /// windowid=10, see also ACTION_ANALOG_MOVE_X, ACTION_ANALOG_MOVE_Y
  ADDON_ACTION_ANALOG_MOVE             = 49,


  /// @brief Action string: <b><c>Rotate</c></b>
  ///
  /// rotate current picture clockwise during slideshow. Can be used in
  /// slideshow.xml window id=2007
  ADDON_ACTION_ROTATE_PICTURE_CW       = 50,

  /// @brief Action string: <b><c>RotateCCW</c></b>
  ///
  /// rotate current picture counterclockwise during slideshow. Can be used in
  /// slideshow.xml window id=2007
  ADDON_ACTION_ROTATE_PICTURE_CCW      = 51,


  /// @brief Action string: <b><c>SubtitleDelayMin</c></b>
  ///
  /// Decrease subtitle/movie Delay.  Can b used in videoFullScreen.xml window
  /// id=2005
  ADDON_ACTION_SUBTITLE_DELAY_MIN      = 52,

  /// @brief Action string: <b><c>SubtitleDelayPlus</c></b>
  ///
  /// Increase subtitle/movie Delay.  Can be used in videoFullScreen.xml window
  /// id=2005
  ADDON_ACTION_SUBTITLE_DELAY_PLUS     = 53,

  /// @brief Action string: <b><c>AudioDelayMinus</c></b>
  ///
  /// Increase avsync delay.  Can be used in videoFullScreen.xml window id=2005
  ADDON_ACTION_AUDIO_DELAY_MIN         = 54,

  /// @brief Action string: <b><c>AudioDelayPlus</c></b>
  ///
  /// Decrease avsync delay.  Can be used in videoFullScreen.xml window id=2005
  ADDON_ACTION_AUDIO_DELAY_PLUS        = 55,

  /// @brief Action string: <b><c>AudioNextLanguage</c></b>
  ///
  /// Select next language in movie.  Can be used in videoFullScreen.xml window
  /// id=2005
  ADDON_ACTION_AUDIO_NEXT_LANGUAGE     = 56,

  /// @brief Action string: <b><c>NextResolution</c></b>
  ///
  /// switch 2 next resolution. Can b used during screen calibration
  /// settingsScreenCalibration.xml windowid=11
  ADDON_ACTION_CHANGE_RESOLUTION       = 57,


  /// @brief Action string: <b><c>Number0</c></b>
  ///
  /// remote keys 0-9. are used by multiple windows
  ADDON_REMOTE_0                       = 58,

  /// @brief Action string: <b><c>Number1</c></b>
  ///
  /// for example in videoFullScreen.xml window id=2005 you can
  ADDON_REMOTE_1                       = 59,

  /// @brief Action string: <b><c>Number2</c></b>
  ///
  /// enter time (mmss) to jump to particular point in the movie
  ADDON_REMOTE_2                       = 60,

  /// @brief Action string: <b><c>Number3</c></b>
  ///
  ///
  ADDON_REMOTE_3                       = 61,

  /// @brief Action string: <b><c>Number4</c></b>
  ///
  /// with spincontrols you can enter 3digit number to quickly set
  ADDON_REMOTE_4                       = 62,

  /// @brief Action string: <b><c>Number5</c></b>
  ///
  /// spincontrol to desired value
  ADDON_REMOTE_5                       = 63,

  /// @brief Action string: <b><c>Number6</c></b>
  ///
  ///
  ADDON_REMOTE_6                       = 64,

  /// @brief Action string: <b><c>Number7</c></b>
  ///
  ///
  ADDON_REMOTE_7                       = 65,

  /// @brief Action string: <b><c>Number8</c></b>
  ///
  ADDON_REMOTE_8                       = 66,

  /// @brief Action string: <b><c>Number9</c></b>
  ///
  ADDON_REMOTE_9                       = 67,


  /// Unused at the moment
  ADDON_ACTION_PLAY                    = 68,

  /// @brief Action string: <b><c>PlayerProcessInfo</c></b>
  /// show player process info (video decoder, pixel format, pvr signal strength
  /// and the like
  ADDON_ACTION_PLAYER_PROCESS_INFO     = 69,

  /// @brief Action string: <b><c>SmallStepBack</c></b>
  ///
  /// jumps a few seconds back during playback of movie. Can be used in
  /// videoFullScreen.xml window id=2005
  ADDON_ACTION_SMALL_STEP_BACK         = 76,

  /// @brief Action string: <b><c>FastForward</c></b>
  ///
  /// FF in current file played. global action, can be used anywhere
  ADDON_ACTION_PLAYER_FORWARD          = 77,

  /// @brief Action string: <b><c>Rewind</c></b>
  ///
  /// RW in current file played. global action, can be used anywhere
  ADDON_ACTION_PLAYER_REWIND           = 78,

  /// @brief Action string: <b><c>Play</c></b>
  ///
  /// Play current song. Unpauses song and sets playspeed to 1x. global action,
  /// can be used anywhere
  ADDON_ACTION_PLAYER_PLAY             = 79,


  /// @brief Action string: <b><c>Delete</c></b>
  ///
  /// delete current selected item. Can be used in myfiles.xml window id=3 and
  /// in myvideoTitle.xml window id=25
  ADDON_ACTION_DELETE_ITEM             = 80,

  /// @brief Action string: <b><c>Copy</c></b>
  ///
  /// copy current selected item. Can be used in myfiles.xml window id=3
  ADDON_ACTION_COPY_ITEM               = 81,

  /// @brief Action string: <b><c>Move</c></b>
  ///
  /// move current selected item. Can be used in myfiles.xml window id=3
  ADDON_ACTION_MOVE_ITEM               = 82,

  /// @brief Action string: <b><c>Sreenshot</c></b>
  ///
  /// take a screenshot
  ADDON_ACTION_TAKE_SCREENSHOT         = 85,

  /// @brief Action string: <b><c>Rename</c></b>
  ///
  /// rename item
  ADDON_ACTION_RENAME_ITEM             = 87,


  /// @brief Action string: <b><c>VolumeUp</c></b>
  ///
  /// Increase the volume of playback.
  ADDON_ACTION_VOLUME_UP               = 88,

  /// @brief Action string: <b><c>VolumeDown</c></b>
  ///
  /// Decrease the volume of playback.
  ADDON_ACTION_VOLUME_DOWN             = 89,

  /// @brief Action string: <b><c>VolumeAmplification</c></b>
  ///
  ///
  ADDON_ACTION_VOLAMP                  = 90,

  /// @brief Action string: <b><c>Mute</c></b>
  ///
  /// Mute the volume.
  ADDON_ACTION_MUTE                    = 91,

  /// @brief Action string: <b><c>ParentDir</c></b>
  ///
  /// Go back in navigation.
  ADDON_ACTION_NAV_BACK                = 92,

  /// @brief Action string: <b><c>VolAmpUp</c></b>
  ///
  ///
  ADDON_ACTION_VOLAMP_UP               = 93,

  /// @brief Action string: <b><c>VolAmpDown</c></b>
  ///
  ///
  ADDON_ACTION_VOLAMP_DOWN             = 94,


  /// @brief Action string: <b><c>CreateEpisodeBookmark</c></b>
  ///
  /// Creates an episode bookmark on the currently playing video file
  /// containing more than one episode
  ADDON_ACTION_CREATE_EPISODE_BOOKMARK = 95,

  /// @brief Action string: <b><c>CreateBookmark</c></b>
  ///
  /// Creates a bookmark of the currently playing video file
  ADDON_ACTION_CREATE_BOOKMARK         = 96,


  /// @brief Action string: <b><c>ChapterOrBigStepForward</c></b>
  ///
  /// Goto the next chapter, if not available perform a big step forward
  ADDON_ACTION_CHAPTER_OR_BIG_STEP_FORWARD = 97,

  /// @brief Action string: <b><c></c>ChapterOrBigStepBack</b>
  ///
  /// Goto the previous chapter, if not available perform a big step back
  ADDON_ACTION_CHAPTER_OR_BIG_STEP_BACK    = 98,


  /// @brief Action string: <b><c>CycleSubtitle</c></b>
  ///
  /// switch to next subtitle of movie, but will not enable/disable the
  /// subtitles. Can be used in videoFullScreen.xml window id=2005
  ADDON_ACTION_CYCLE_SUBTITLE          = 99,


  /// @brief Action string: <b><c>LeftClick</c></b>
  ///
  ///
  ADDON_ACTION_MOUSE_LEFT_CLICK        = 100,

  /// @brief Action string: <b><c>RightClick</c></b>
  ///
  ///
  ADDON_ACTION_MOUSE_RIGHT_CLICK       = 101,

  /// @brief Action string: <b><c>MiddleClick</c></b>
  ///
  ///
  ADDON_ACTION_MOUSE_MIDDLE_CLICK      = 102,

  /// @brief Action string: <b><c>DoubleClick</c></b>
  ///
  ///
  ADDON_ACTION_MOUSE_DOUBLE_CLICK      = 103,

  /// @brief Action string: <b><c>WheelUp</c></b>
  ///
  ///
  ADDON_ACTION_MOUSE_WHEEL_UP          = 104,

  /// @brief Action string: <b><c>WheelDown</c></b>
  ///
  ///
  ADDON_ACTION_MOUSE_WHEEL_DOWN        = 105,

  /// @brief Action string: <b><c>MouseDrag</c></b>
  ///
  ///
  ADDON_ACTION_MOUSE_DRAG              = 106,

  /// @brief Action string: <b><c>MouseMove</c></b>
  ///
  ///
  ADDON_ACTION_MOUSE_MOVE              = 107,

  /// @brief Action string: <b><c>LongClick</c></b>
  ///
  ///
  ADDON_ACTION_MOUSE_LONG_CLICK        = 108,

  /// @brief Action string: <b><c>Backspace</c></b>
  ///
  /// Used in the virtual keyboards to delete one letter.
  ADDON_ACTION_BACKSPACE               = 110,

  /// @brief Action string: <b><c>ScrollUp</c></b>
  ///
  /// Variable speed scroll up for analog keys (stick or triggers)
  ADDON_ACTION_SCROLL_UP               = 111,

  /// @brief Action string: <b><c>ScrollDown</c></b>
  ///
  /// Variable speed scroll down for analog keys (stick or triggers)
  ADDON_ACTION_SCROLL_DOWN             = 112,

  /// @brief Action string: <b><c>AnalogFastForward</c></b>
  ///
  ///
  ADDON_ACTION_ANALOG_FORWARD          = 113,

  /// @brief Action string: <b><c>AnalogRewind</c></b>
  ///
  /// Variable speed rewind for analog keys (stick or triggers)
  ADDON_ACTION_ANALOG_REWIND           = 114,


  /// @brief Action string: <b><c>MoveItemUp</c></b>
  ///
  /// move item up in playlist
  ADDON_ACTION_MOVE_ITEM_UP            = 115,

  /// @brief Action string: <b><c>MoveItemDown</c></b>
  ///
  /// move item down in playlist
  ADDON_ACTION_MOVE_ITEM_DOWN          = 116,

  /// @brief Action string: <b><c>ContextMenu</c></b>
  ///
  /// pops up the context menu
  ADDON_ACTION_CONTEXT_MENU            = 117,


  /// @brief Action string: <b><c>Shift</c></b>
  ///
  /// Used in Virtual Keyboard to switch to upper or lower case letters
  ADDON_ACTION_SHIFT                   = 118,

  /// @brief Action string: <b><c>Symbols</c></b>
  ///
  /// Used in Virtual Keyboard to switch to or from symbols mode
  ADDON_ACTION_SYMBOLS                 = 119,

  /// @brief Action string: <b><c>CursorLeft</c></b>
  ///
  /// Used in Virtual Keyboard to move the current cursor point to the left
  ADDON_ACTION_CURSOR_LEFT             = 120,

  /// @brief Action string: <b><c>CursorRight</c></b>
  ///
  /// Used in Virtual Keyboard to move the current cursor point to the right
  ADDON_ACTION_CURSOR_RIGHT            = 121,


  ///
  ADDON_ACTION_BUILT_IN_FUNCTION       = 122,


  /// @brief Action string: <b><c>ShowTime</c></b>
  ///
  /// displays current time, can be used in videoFullScreen.xml window id=2005
  ADDON_ACTION_SHOW_OSD_TIME           = 123,

  /// @brief Action string: <b><c>AnalogSeekForward</c></b>
  ///
  /// seeks forward, and displays the seek bar.
  ADDON_ACTION_ANALOG_SEEK_FORWARD     = 124,

  /// @brief Action string: <b><c>AnalogSeekBack</c></b>
  ///
  /// seeks backward, and displays the seek bar.
  ADDON_ACTION_ANALOG_SEEK_BACK        = 125,


  /// @brief Action string: <b><c>ShowPreset</c></b>
  ///
  /// Shows the current visualisation preset (milkdrop/spectrum)
  ADDON_ACTION_VIS_PRESET_SHOW         = 126,

  /// @brief Action string: <b><c>NextPresent</c></b>
  ///
  /// Next visualisation preset
  ADDON_ACTION_VIS_PRESET_NEXT         = 128,

  /// @brief Action string: <b><c></c>PreviousPreset</b>
  ///
  /// Previous visualisation preset
  ADDON_ACTION_VIS_PRESET_PREV         = 129,

  /// @brief Action string: <b><c>LockPreset</c></b>
  ///
  /// Lock the current visualisation preset
  ADDON_ACTION_VIS_PRESET_LOCK         = 130,

  /// @brief Action string: <b><c>RandomPreset</c></b>
  ///
  /// Switch to a new random preset
  ADDON_ACTION_VIS_PRESET_RANDOM       = 131,

  /// @brief Action string: <b><c>IncreaseVisRating</c></b>
  ///
  /// Used to increase track rating in full screen playback (press info on
  /// track and use pageplus on keyboard/remote
  ADDON_ACTION_VIS_RATE_PRESET_PLUS    = 132,

  /// @brief Action string: <b><c>DecreaseVisRating</c></b>
  ///
  /// Used to decrease track rating in full screen playback (press info on
  /// track and use pageminus on keyboard/remote
  ADDON_ACTION_VIS_RATE_PRESET_MINUS   = 133,


  /// @brief Action string: <b><c>ShowVideoMenu</c></b>
  ///
  /// Go to the DVD Video menu when playing a DVD.
  ADDON_ACTION_SHOW_VIDEOMENU          = 134,

  /// @brief Action string: <b><c>Enter</c></b>
  ///
  /// ? (ACTION_ENTER) Not sure about all areas, but on some windows this will
  /// be the same as the "done" on screen button.
  ADDON_ACTION_ENTER                   = 135,


  /// @brief Action string: <b><c>IncreaseRating</c></b>
  ///
  /// Used to increase track rating in full screen playback (press info on
  /// track and use pageplus on keyboard/remote
  ADDON_ACTION_INCREASE_RATING         = 136,

  /// @brief Action string: <b><c>DecreaseRating</c></b>
  ///
  /// Used to decrease track rating in full screen playback (press info on
  /// track and use pageminus on keyboard/remote
  ADDON_ACTION_DECREASE_RATING         = 137,


  /// @brief Action string: <b><c>NextScene</c></b>
  ///
  /// switch to next scene/cutpoint in movie
  ADDON_ACTION_NEXT_SCENE              = 138,

  /// @brief Action string: <b><c>PreviousScene</c></b>
  ///
  /// switch to previous scene/cutpoint in movie
  ADDON_ACTION_PREV_SCENE              = 139,


  /// @brief Action string: <b><c>NextLetter</c></b>
  ///
  /// jump through a list or container by letter
  ADDON_ACTION_NEXT_LETTER             = 140,

  /// @brief Action string: <b><c>PrevLetter</c></b>
  ///
  ///
  ADDON_ACTION_PREV_LETTER             = 141,


  /// @brief Action string: <b><c>JumpSMS2</c></b>
  ///
  /// Jump through a list using SMS-style input 2 (eg press 2 twice to jump to
  /// the B's.)
  ADDON_ACTION_JUMP_SMS2               = 142,

  /// @brief Action string: <b><c>JumpSMS3</c></b>
  ///
  /// Jump through a list using SMS-style input 3 (eg press 2 twice to jump to the B's.)
  ADDON_ACTION_JUMP_SMS3               = 143,

  /// @brief Action string: <b><c>JumpSMS4</c></b>
  ///
  /// Jump through a list using SMS-style input 4 (eg press 2 twice to jump to the B's.)
  ADDON_ACTION_JUMP_SMS4               = 144,

  /// @brief Action string: <b><c>JumpSMS5</c></b>
  ///
  /// Jump through a list using SMS-style input 5 (eg press 2 twice to jump to the B's.)
  ADDON_ACTION_JUMP_SMS5               = 145,

  /// @brief Action string: <b><c>JumpSMS6</c></b>
  ///
  /// Jump through a list using SMS-style input 6 (eg press 2 twice to jump to the B's.)
  ADDON_ACTION_JUMP_SMS6               = 146,

  /// @brief Action string: <b><c>JumpSMS7</c></b>
  ///
  /// Jump through a list using SMS-style input 7 (eg press 2 twice to jump to the B's.)
  ADDON_ACTION_JUMP_SMS7               = 147,

  /// @brief Action string: <b><c>JumpSMS8</c></b>
  ///
  /// Jump through a list using SMS-style input 8 (eg press 2 twice to jump to the B's.)
  ADDON_ACTION_JUMP_SMS8               = 148,

  /// @brief Action string: <b><c>JumpSMS9</c></b>
  ///
  /// Jump through a list using SMS-style input 9 (eg press 2 twice to jump to the B's.)
  ADDON_ACTION_JUMP_SMS9               = 149,


  /// @brief Action string: <b><c>FilterClear</c></b>
  ///
  /// Filter a list in music or videos using SMS-style input.
  ADDON_ACTION_FILTER_CLEAR            = 150,

  /// @brief Action string: <b><c>FilterSMS2</c></b>
  ///
  /// Filter a list in music or videos using SMS-style input.
  ADDON_ACTION_FILTER_SMS2             = 151,

  /// @brief Action string: <b><c>FilterSMS3</c></b>
  ///
  /// Filter a list in music or videos using SMS-style input.
  ADDON_ACTION_FILTER_SMS3             = 152,

  /// @brief Action string: <b><c>FilterSMS4</c></b>
  ///
  /// Filter a list in music or videos using SMS-style input.
  ADDON_ACTION_FILTER_SMS4             = 153,

  /// @brief Action string: <b><c>FilterSMS5</c></b>
  ///
  /// Filter a list in music or videos using SMS-style input.
  ADDON_ACTION_FILTER_SMS5             = 154,

  /// @brief Action string: <b><c>FilterSMS6</c></b>
  ///
  /// Filter a list in music or videos using SMS-style input.
  ADDON_ACTION_FILTER_SMS6             = 155,

  /// @brief Action string: <b><c>FilterSMS7</c></b>
  ///
  /// Filter a list in music or videos using SMS-style input.
  ADDON_ACTION_FILTER_SMS7             = 156,

  /// @brief Action string: <b><c>FilterSMS8</c></b>
  ///
  /// Filter a list in music or videos using SMS-style input.
  ADDON_ACTION_FILTER_SMS8             = 157,

  /// @brief Action string: <b><c>FilterSMS9</c></b>
  ///
  /// Filter a list in music or videos using SMS-style input.
  ADDON_ACTION_FILTER_SMS9             = 158,


  /// @brief Action string: <b><c>FirstPage</c></b>
  ///
  ///
  ADDON_ACTION_FIRST_PAGE              = 159,

  /// @brief Action string: <b><c>LastPage</c></b>
  ///
  ///
  ADDON_ACTION_LAST_PAGE               = 160,


  /// @brief Action string: <b><c>AudioDelay</c></b>
  ///
  ///
  ADDON_ACTION_AUDIO_DELAY             = 161,

  /// @brief Action string: <b><c>SubtitleDelay</c></b>
  ///
  ///
  ADDON_ACTION_SUBTITLE_DELAY          = 162,

  /// @brief Action string: <b><c>Menu</c></b>
  ///
  ///
  ADDON_ACTION_MENU                    = 163,

  /// @brief Action string: <b><c>SetRating</c></b>
  ///
  ///
  ADDON_ACTION_SET_RATING              = 164,

  /// @brief Action string: <b><c>Record</c></b>
  ///
  /// PVR record current playing channel or selected item in windows like EPG
  ADDON_ACTION_RECORD                  = 170,


  ///
  ADDON_ACTION_PASTE                   = 180,

  ///
  ADDON_ACTION_NEXT_CONTROL            = 181,

  ///
  ADDON_ACTION_PREV_CONTROL            = 182,

  /// PVR Used to switch channel. Works only if you playback TV or radio
  ADDON_ACTION_CHANNEL_SWITCH          = 183,

  /// @brief Action string: <b><c>ChannelUp</c></b>
  ///
  /// PVR Used to switch up to the next channel. Works only if you playback TV
  /// or radio
  ADDON_ACTION_CHANNEL_UP              = 184,

  /// @brief Action string: <b><c>ChannelDown</c></b>
  ///
  /// PVR Used to switch down to the previous channel. Works only if you
  /// playback TV or radio
  ADDON_ACTION_CHANNEL_DOWN            = 185,

  /// @brief Action string: <b><c>NextChannelGroup</c></b>
  ///
  /// PVR Goes to the next channel group when using live TV. Works only within
  /// PVR windows + channel osd.
  ADDON_ACTION_NEXT_CHANNELGROUP       = 186,

  /// @brief Action string: <b><c>PreviousChannelGroup</c></b>
  ///
  /// PVR Goes to the previous channel group when using live TV. Works only
  /// within PVR windows + channel osd.
  ADDON_ACTION_PREVIOUS_CHANNELGROUP   = 187,

  /// @brief Action string: <b><c>PlayPVR</c></b>
  ///
  /// PVR Starts playback a TV or radio channel depends on the last played
  /// channel.
  ADDON_ACTION_PVR_PLAY                = 188,

  /// @brief Action string: <b><c>PlayPVRTV</c></b>
  ///
  /// PVR Starts playback a TV channel. Will playback the last played
  /// channel if available.
  ADDON_ACTION_PVR_PLAY_TV             = 189,

  /// @brief Action string: <b><c>PlayPVRRadio</c></b>
  ///
  /// PVR Starts playback a radio channel. Will playback the last played channel
  /// if available.
  ADDON_ACTION_PVR_PLAY_RADIO          = 190,

  /// @brief Action string: <b><c>ShowTimerRule</c></b>
  ///
  ADDON_ACTION_PVR_SHOW_TIMER_RULE     = 191,

  /// @brief Action string: <b><c>ToggleFullsreen</c></b>
  ///
  /// switch 2 desktop resolution
  ADDON_ACTION_TOGGLE_FULLSCREEN       = 199,

  /// @brief Action string: <b><c>ToggleWatched</c></b>
  ///
  /// Toggle watched status (videos)
  ADDON_ACTION_TOGGLE_WATCHED          = 200,

  /// @brief Action string: <b><c>ScanItem</c></b>
  ///
  /// scan item
  ADDON_ACTION_SCAN_ITEM               = 201,

  /// @brief Action string: <b><c>AudioToggleDigital</c></b>
  ///
  /// switch digital <-> analog
  ADDON_ACTION_TOGGLE_DIGITAL_ANALOG   = 202,

  /// @brief Action string: <b><c>ReloadKeymaps</c></b>
  ///
  /// reloads CButtonTranslator's keymaps
  ADDON_ACTION_RELOAD_KEYMAPS          = 203,

  /// @brief Action string: <b><c>GUIProfile</c></b>
  ///
  /// start the GUIControlProfiler running
  ADDON_ACTION_GUIPROFILE_BEGIN        = 204,


  /// @brief Action string: <b><c>Red</c></b>
  ///
  /// Teletext Color buttons to control TopText
  ADDON_ACTION_TELETEXT_RED            = 215,

  /// @brief Action string: <b><c>Green</c></b>
  ///
  /// Teletext Color buttons to control TopText
  ADDON_ACTION_TELETEXT_GREEN          = 216,

  /// @brief Action string: <b><c>Yellow</c></b>
  ///
  /// Teletext Color buttons to control TopText
  ADDON_ACTION_TELETEXT_YELLOW         = 217,

  /// @brief Action string: <b><c>Blue</c></b>
  ///
  /// Teletext Color buttons to control TopText
  ADDON_ACTION_TELETEXT_BLUE           = 218,


  /// @brief Action string: <b><c>IncreasePar</c></b>
  ///
  /// Used in video fullscreen to increase the pixel aspect ratio (stretch).
  ADDON_ACTION_INCREASE_PAR            = 219,

  /// @brief Action string: <b><c>DecreasePar</c></b>
  ///
  /// Used in video fullscreen to decrease the pixel aspect ratio (stretch).
  ADDON_ACTION_DECREASE_PAR            = 220,


  /// @brief Action string: <b><c>VerticalShiftUp</c></b>
  ///
  /// shift up video image in VideoPlayer
  ADDON_ACTION_VSHIFT_UP               = 227,

  /// @brief Action string: <b><c>VerticalShiftDown</c></b>
  ///
  /// shift down video image in VideoPlayer
  ADDON_ACTION_VSHIFT_DOWN             = 228,


  /// @brief Action string: <b><c>PlayPause</c></b>
  ///
  /// Play/pause. If playing it pauses, if paused it plays.
  ADDON_ACTION_PLAYER_PLAYPAUSE        = 229,


  /// @brief Action string: <b><c>SubtitleShiftUp</c></b>
  ///
  /// shift up subtitles in VideoPlayer
  ADDON_ACTION_SUBTITLE_VSHIFT_UP      = 230,

  /// @brief Action string: <b><c>SubtitleShiftDown</c></b>
  ///
  /// shift down subtitles in VideoPlayer
  ADDON_ACTION_SUBTITLE_VSHIFT_DOWN    = 231,

  /// @brief Action string: <b><c>SubtitleAlign</c></b>
  ///
  /// toggle vertical alignment of subtitles
  ADDON_ACTION_SUBTITLE_ALIGN          = 232,


  /// @brief Action string: <b><c>Filter</c></b>
  ///
  /// Opens the mediafilter dialog in the video and musiclibrary.
  ADDON_ACTION_FILTER                  = 233,


  /// @brief Action string: <b><c>SwitchPlayer</c></b>
  ///
  /// Select player to use, such as internal (DVDPlayer/PAPlayer),
  /// UPnP "play using" targets, external players (defined in
  /// playercorefactory.xml).
  ADDON_ACTION_SWITCH_PLAYER           = 234,


  /// @brief Action string: <b><c></c>NextStereoMode</b>
  ///
  ADDON_ACTION_STEREOMODE_NEXT         = 235,

  /// @brief Action string: <b><c>PreviousStereoMode</c></b>
  ///
  ADDON_ACTION_STEREOMODE_PREVIOUS     = 236,

  /// @brief Action string: <b><c>ToggleStereoMode</c></b>
  ///
  /// Toggle 3D/Stereoscopic mode
  ADDON_ACTION_STEREOMODE_TOGGLE       = 237,

  /// @brief Action string: <b><c>StereoMode</c></b>
  ///
  ADDON_ACTION_STEREOMODE_SELECT       = 238,

  /// @brief Action string: <b><c>StereoModeToMono</c></b>
  ///
  ADDON_ACTION_STEREOMODE_TOMONO       = 239,

  ///
  ADDON_ACTION_STEREOMODE_SET          = 240,


  /// @brief Action string: <b><c>SettingsReset</c></b>
  ///
  ///
  ADDON_ACTION_SETTINGS_RESET          = 241,

  /// @brief Action string: <b><c>SettingsLevelChange</c></b>
  ///
  ///
  ADDON_ACTION_SETTINGS_LEVEL_CHANGE   = 242,


  /// show autoclosing OSD. Can b used in videoFullScreen.xml window id=2005
  ADDON_ACTION_TRIGGER_OSD             = 243,

  ///
  ADDON_ACTION_INPUT_TEXT              = 244,

  ///
  ADDON_ACTION_VOLUME_SET              = 245,

  /// @brief Action string: <b><c>ToggleCommSkip</c></b>
  ///
  ADDON_ACTION_TOGGLE_COMMSKIP         = 246,

  /// @brief Action string: <b><c>Tap</c></b>
  ///
  /// touch actions
  ADDON_ACTION_TOUCH_TAP               = 401,

  /// To define the highest value possible for ADDON_ACTION_TOUCH_TAP
  ADDON_ACTION_TOUCH_TAP_TEN           = 410,

  /// @brief Action string: <b><c>LongPress</c></b>
  ///
  /// touch action
  ADDON_ACTION_TOUCH_LONGPRESS         = 411,

  /// To define the highest value possible for ADDON_ACTION_TOUCH_LONGPRESS
  ADDON_ACTION_TOUCH_LONGPRESS_TEN     = 420,


  ///
  ADDON_ACTION_GESTURE_NOTIFY          = 500,

  ///
  ADDON_ACTION_GESTURE_BEGIN           = 501,

  /// @brief Action string: <b><c>ZoomGesture</c></b>
  ///
  /// sendaction with point and currentPinchScale (fingers together < 1.0 -> fingers apart > 1.0)
  ADDON_ACTION_GESTURE_ZOOM            = 502,

  /// @brief Action string: <b><c>RotateGesture</c></b>
  ///
  ///
  ADDON_ACTION_GESTURE_ROTATE          = 503,

  /// @brief Action string: <b><c>PanGesture</c></b>
  ///
  ///
  ADDON_ACTION_GESTURE_PAN             = 504,


  /// @brief Action string: <b><c>SwipeLeft</c></b>
  ///
  /// To define the highest value possible for ADDON_ACTION_GESTURE_SWIPE_LEFT
  ADDON_ACTION_GESTURE_SWIPE_LEFT      = 511,
  ADDON_ACTION_GESTURE_SWIPE_LEFT_TEN  = 520,

  /// @brief Action string: <b><c>SwipeRight</c></b>
  ///
  /// To define the highest value possible for ADDON_ACTION_GESTURE_SWIPE_RIGHT
  ADDON_ACTION_GESTURE_SWIPE_RIGHT     = 521,
  ADDON_ACTION_GESTURE_SWIPE_RIGHT_TEN = 530,

  /// @brief Action string: <b><c>SwipeUp</c></b>
  ///
  /// To define the highest value possible for ADDON_ACTION_GESTURE_SWIPE_UP
  ADDON_ACTION_GESTURE_SWIPE_UP        = 531,
  ADDON_ACTION_GESTURE_SWIPE_UP_TEN    = 540,

  /// @brief Action string: <b><c>SwipeDown</c></b>
  ///
  /// To define the highest value possible for ADDON_ACTION_GESTURE_SWIPE_DOWN
  ADDON_ACTION_GESTURE_SWIPE_DOWN      = 541,
  ADDON_ACTION_GESTURE_SWIPE_DOWN_TEN  = 550,


  /// @brief Action string: <b><c>AnalogMoveX</c></b>
  ///
  /// analog thumbstick move, horizontal axis; see ACTION_ANALOG_MOVE
  ADDON_ACTION_ANALOG_MOVE_X           = 601,

  /// @brief Action string: <b><c>AnalogMoveY</c></b>
  ///
  /// analog thumbstick move, vertical axis; see ACTION_ANALOG_MOVE
  ADDON_ACTION_ANALOG_MOVE_Y           = 602,


  /// @brief Action string: <b><c>Error</c></b>
  ///
  /// ERROR action is used to play an error sound
  ADDON_ACTION_ERROR                   = 998,

  /// @brief Action string: <b><c>Noop</c></b>
  ///
  /// The NOOP action can be specified to disable an input event. This is
  /// useful in user keyboard.xml etc to disable actions specified in the
  /// system mappings.
  ADDON_ACTION_NOOP                    = 999
};
/// @}
//----------------------------------------------------------------------------
