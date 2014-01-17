// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/ui/views/frame/opaque_browser_frame_view_linux.h"

#include "base/command_line.h"
#include "chrome/browser/ui/views/frame/opaque_browser_frame_view.h"
#include "chrome/browser/ui/views/frame/opaque_browser_frame_view_layout.h"
#include "chrome/common/chrome_switches.h"
#include "ui/views/linux_ui/linux_ui.h"

///////////////////////////////////////////////////////////////////////////////
// OpaqueBrowserFrameViewLinux, public:

OpaqueBrowserFrameViewLinux::OpaqueBrowserFrameViewLinux(
    OpaqueBrowserFrameView* view,
    OpaqueBrowserFrameViewLayout* layout)
    : view_(view),
      layout_(layout) {
  views::LinuxUI* ui = views::LinuxUI::instance();
  if (ui)
    ui->AddWindowButtonOrderObserver(this);
}

OpaqueBrowserFrameViewLinux::~OpaqueBrowserFrameViewLinux() {
  views::LinuxUI* ui = views::LinuxUI::instance();
  if (ui)
    ui->RemoveWindowButtonOrderObserver(this);
}

///////////////////////////////////////////////////////////////////////////////
// OpaqueBrowserFrameViewLinux,
//     OpaqueBrowserFrameViewPlatformSpecific implementation:

bool OpaqueBrowserFrameViewLinux::ShouldShowCaptionButtons() const {
  // Do not show caption buttons if the system title bar is being used.
  if (CommandLine::ForCurrentProcess()->HasSwitch(switches::kUseSystemTitleBar))
    return false;

  // On Ubuntu Unity, if the window is maximized, the system will provide
  // caption buttons, so Chrome should not add its own.
  views::LinuxUI* ui = views::LinuxUI::instance();
  return !(view_->IsMaximized() && ui && ui->UnityIsRunning());
}

bool OpaqueBrowserFrameViewLinux::ShouldShowTitleBar() const {
  // On Ubuntu Unity, if the window is maximized, the system will provide
  // a title bar, so Chrome should not add its own.
  views::LinuxUI* ui = views::LinuxUI::instance();
  return !(view_->IsMaximized() && ui && ui->UnityIsRunning());
}

///////////////////////////////////////////////////////////////////////////////
// OpaqueBrowserFrameViewLinux,
//     views::WindowButtonOrderObserver implementation:

void OpaqueBrowserFrameViewLinux::OnWindowButtonOrderingChange(
    const std::vector<views::FrameButton>& leading_buttons,
    const std::vector<views::FrameButton>& trailing_buttons) {
  layout_->SetButtonOrdering(leading_buttons, trailing_buttons);

  // We can receive OnWindowButtonOrderingChange events before we've been added
  // to a Widget. We need a Widget because layout crashes due to dependencies
  // on a ui::ThemeProvider().
  if (view_->GetWidget()) {
    view_->Layout();
    view_->SchedulePaint();
  }
}

///////////////////////////////////////////////////////////////////////////////
// OpaqueBrowserFrameViewObserver:

// static
OpaqueBrowserFrameViewPlatformSpecific*
OpaqueBrowserFrameViewPlatformSpecific::Create(
      OpaqueBrowserFrameView* view,
      OpaqueBrowserFrameViewLayout* layout) {
  return new OpaqueBrowserFrameViewLinux(view, layout);
}
