// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_FILEAPI_MTP_FILE_SYSTEM_BACKEND_DELEGATE_H_
#define CHROME_BROWSER_CHROMEOS_FILEAPI_MTP_FILE_SYSTEM_BACKEND_DELEGATE_H_

#include "base/memory/scoped_ptr.h"
#include "chrome/browser/chromeos/fileapi/file_system_backend_delegate.h"

namespace base {
class FilePath;
}  // namespace base

namespace storage {
class AsyncFileUtil;
class FileSystemContext;
class FileStreamReader;
class FileSystemURL;
class FileStreamWriter;
class WatcherManager;
}  // namespace storage

class DeviceMediaAsyncFileUtil;

namespace chromeos {

// This is delegate interface to inject the MTP device file system in Chrome OS
// file API backend.
class MTPFileSystemBackendDelegate : public FileSystemBackendDelegate {
 public:
  explicit MTPFileSystemBackendDelegate(
      const base::FilePath& storage_partition_path);
  virtual ~MTPFileSystemBackendDelegate();

  // FileSystemBackendDelegate overrides.
  virtual storage::AsyncFileUtil* GetAsyncFileUtil(
      storage::FileSystemType type) OVERRIDE;
  virtual scoped_ptr<storage::FileStreamReader> CreateFileStreamReader(
      const storage::FileSystemURL& url,
      int64 offset,
      const base::Time& expected_modification_time,
      storage::FileSystemContext* context) OVERRIDE;
  virtual scoped_ptr<storage::FileStreamWriter> CreateFileStreamWriter(
      const storage::FileSystemURL& url,
      int64 offset,
      storage::FileSystemContext* context) OVERRIDE;
  virtual storage::WatcherManager* GetWatcherManager(
      const storage::FileSystemURL& url) OVERRIDE;
  virtual void GetRedirectURLForContents(
      const storage::FileSystemURL& url,
      const storage::URLCallback& callback) OVERRIDE;

 private:
  scoped_ptr<DeviceMediaAsyncFileUtil> device_media_async_file_util_;

  DISALLOW_COPY_AND_ASSIGN(MTPFileSystemBackendDelegate);
};

}  // namespace chromeos

#endif  // CHROME_BROWSER_CHROMEOS_FILEAPI_MTP_FILE_SYSTEM_BACKEND_DELEGATE_H_
