// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef LIBRARIES_NACL_IO_EVENT_EMITTER_TCP_H_
#define LIBRARIES_NACL_IO_EVENT_EMITTER_TCP_H_

#include "nacl_io/event_emitter_stream.h"
#include "nacl_io/fifo_char.h"

#include "sdk_util/macros.h"
#include "sdk_util/scoped_ref.h"

namespace nacl_io {

class EventEmitterTCP;
typedef sdk_util::ScopedRef<EventEmitterTCP> ScopedEventEmitterTCP;

class EventEmitterTCP : public EventEmitterStream {
 public:
  EventEmitterTCP(size_t rsize, size_t wsize);

  uint32_t ReadIn_Locked(char* buffer, uint32_t len);
  uint32_t WriteIn_Locked(const char* buffer, uint32_t len);

  uint32_t ReadOut_Locked(char* buffer, uint32_t len);
  uint32_t WriteOut_Locked(const char* buffer, uint32_t len);

  virtual FIFOChar* in_fifo() { return &in_fifo_; }
  virtual FIFOChar* out_fifo() { return &out_fifo_; }

protected:
  FIFOChar in_fifo_;
  FIFOChar out_fifo_;
  DISALLOW_COPY_AND_ASSIGN(EventEmitterTCP);
};

}  // namespace nacl_io

#endif  // LIBRARIES_NACL_IO_EVENT_EMITTER_TCP_H_

