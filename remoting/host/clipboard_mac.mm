// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "remoting/host/clipboard.h"

#include "base/logging.h"

namespace remoting {

class ClipboardMac : public Clipboard {
 public:
  ClipboardMac();

  // Must be called on the UI thread.
  virtual void Start(
      scoped_ptr<protocol::ClipboardStub> client_clipboard) OVERRIDE;
  virtual void InjectClipboardEvent(
      const protocol::ClipboardEvent& event) OVERRIDE;
  virtual void Stop() OVERRIDE;

 private:
  DISALLOW_COPY_AND_ASSIGN(ClipboardMac);
};

void ClipboardMac::Start(
    scoped_ptr<protocol::ClipboardStub> client_clipboard) {
  NOTIMPLEMENTED();
}

void ClipboardMac::InjectClipboardEvent(
    const protocol::ClipboardEvent& event) {
  NOTIMPLEMENTED();
}

void ClipboardMac::Stop() {
  NOTIMPLEMENTED();
}

scoped_ptr<Clipboard> Clipboard::Create() {
  return scoped_ptr<Clipboard>(new ClipboardMac());
}

}  // namespace remoting
