/*
 *  Copyright (C) 2005-2018 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "GUIAudioManager.h"
#include "GUIComponent.h"
#include "GUIColorManager.h"
#include "GUIInfoManager.h"
#include "GUILargeTextureManager.h"
#include "GUIWindowManager.h"
#include "ServiceBroker.h"
#include "StereoscopicsManager.h"
#include "TextureManager.h"
#include "GUIMessage.h"
#include "URL.h"
#include "dialogs/GUIDialogYesNo.h"

CGUIComponent::CGUIComponent()
{
  m_pWindowManager.reset(new CGUIWindowManager(this));
  m_pTextureManager.reset(new CGUITextureManager());
  m_pLargeTextureManager.reset(new CGUILargeTextureManager());
  m_stereoscopicsManager.reset(new CStereoscopicsManager());
  m_guiInfoManager.reset(new CGUIInfoManager());
  m_guiColorManager.reset(new CGUIColorManager());
  m_guiAudioManager.reset(new CGUIAudioManager());
}

CGUIComponent::~CGUIComponent()
{
  Deinit();
}

void CGUIComponent::Init()
{
  m_pWindowManager->Initialize();
  m_stereoscopicsManager->Initialize();
  m_guiInfoManager->Initialize();

  AddMsgTarget(m_stereoscopicsManager.get());

  CServiceBroker::RegisterGUI(this);
}

void CGUIComponent::Deinit()
{
  CServiceBroker::UnregisterGUI();

  m_pWindowManager->DeInitialize();
}

CGUIWindowManager& CGUIComponent::GetWindowManager()
{
  return *m_pWindowManager;
}

CGUITextureManager& CGUIComponent::GetTextureManager()
{
  return *m_pTextureManager;
}

CGUILargeTextureManager& CGUIComponent::GetLargeTextureManager()
{
  return *m_pLargeTextureManager;
}

CStereoscopicsManager &CGUIComponent::GetStereoscopicsManager()
{
  return *m_stereoscopicsManager;
}

CGUIInfoManager &CGUIComponent::GetInfoManager()
{
  return *m_guiInfoManager;
}

CGUIColorManager &CGUIComponent::GetColorManager()
{
  return *m_guiColorManager;
}

CGUIAudioManager &CGUIComponent::GetAudioManager()
{
  return *m_guiAudioManager;
}

bool CGUIComponent::ConfirmDelete(std::string path)
{
  CGUIDialogYesNo* pDialog = GetWindowManager().GetWindow<CGUIDialogYesNo>(WINDOW_DIALOG_YES_NO);
  if (pDialog)
  {
    pDialog->SetHeading(CVariant{122});
    pDialog->SetLine(0, CVariant{125});
    pDialog->SetLine(1, CVariant{CURL(path).GetWithoutUserDetails()});
    pDialog->SetLine(2, CVariant{""});
    pDialog->Open();
    if (pDialog->IsConfirmed())
      return true;
  }
  return false;
}

void CGUIComponent::AddMsgTarget(IMsgTargetCallback* pMsgTarget)
{
  if (std::find(m_msgTargets.begin(), m_msgTargets.end(), pMsgTarget) == m_msgTargets.end())
    m_msgTargets.emplace_back(pMsgTarget);
}

bool CGUIComponent::ProcessMsgHooks(CGUIMessage& message)
{
  bool handled = false;

  for (const auto& target : m_msgTargets)
  {
    if (target->OnMessage(message))
      handled = true;
  }
  return handled;
}
