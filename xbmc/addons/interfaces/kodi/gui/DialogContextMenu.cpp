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
 *  along with KODI; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "DialogContextMenu.h"
#include "addons/kodi-addon-dev-kit/include/kodi/gui/DialogContextMenu.h"

#include "addons/AddonDll.h"
#include "dialogs/GUIDialogContextMenu.h"
#include "guilib/GUIWindowManager.h"
#include "utils/log.h"
#include "utils/Variant.h"

extern "C"
{
namespace ADDON
{

void Interface_GUIDialogContextMenu::Init(AddonGlobalInterface* addonInterface)
{
  addonInterface->toKodi->kodi_gui->dialogContextMenu.Open = Open;
}

int Interface_GUIDialogContextMenu::Open(void* kodiBase, const char *heading, const char *entries[], unsigned int size)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogContextMenu::Open - invalid kodi base data");
    return -1;
  }

  CGUIDialogContextMenu* dialog = dynamic_cast<CGUIDialogContextMenu*>(g_windowManager.GetWindow(WINDOW_DIALOG_CONTEXT_MENU));

  if (!heading || !entries || !dialog)
  {
    CLog::Log(LOGERROR, "ADDON::Interface_GUIDialogContextMenu::Open - invalid handler data (heading='%p', entries='%p', dialog='%p') on addon '%s'", heading, entries, dialog, addon->ID().c_str());
    return -1;
  }

  CContextButtons choices;
  for (unsigned int i = 0; i < size; ++i)
    choices.Add(i, entries[i]);

  return dialog->Show(choices);
}

} /* namespace ADDON */
} /* extern "C" */
