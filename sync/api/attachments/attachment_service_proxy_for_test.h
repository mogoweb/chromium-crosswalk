// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_API_ATTACHMENTS_ATTACHMENT_SERVICE_PROXY_FOR_TEST_H_
#define SYNC_API_ATTACHMENTS_ATTACHMENT_SERVICE_PROXY_FOR_TEST_H_

#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "sync/api/attachments/attachment_service_proxy.h"
#include "sync/base/sync_export.h"

namespace syncer {

// An self-contained AttachmentServiceProxy to reduce boilerplate code in tests.
//
// Constructs and owns an AttachmentService suitable for use in tests.  Assumes
// the current thread has a MessageLoop.
class SYNC_EXPORT AttachmentServiceProxyForTest
    : public AttachmentServiceProxy {
 public:
  static AttachmentServiceProxy Create();
  virtual ~AttachmentServiceProxyForTest();

 private:
  // A Core that owns the wrapped AttachmentService.
  class OwningCore : public AttachmentServiceProxy::Core {
   public:
    OwningCore(
        scoped_ptr<AttachmentService>,
        scoped_ptr<base::WeakPtrFactory<AttachmentService> > weak_ptr_factory);

   private:
    scoped_ptr<AttachmentService> wrapped_;
    // WeakPtrFactory for wrapped_.  See Create() for why this is a scoped_ptr.
    scoped_ptr<base::WeakPtrFactory<AttachmentService> > weak_ptr_factory_;

    virtual ~OwningCore();

    DISALLOW_COPY_AND_ASSIGN(OwningCore);
  };

  AttachmentServiceProxyForTest(
      const scoped_refptr<base::SequencedTaskRunner>& wrapped_task_runner,
      const scoped_refptr<Core>& core);
};

}  // namespace syncer

#endif  // SYNC_API_ATTACHMENTS_ATTACHMENT_SERVICE_PROXY_FOR_TEST_H_
