// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/common/chrome_paths_internal.h"

#include "base/files/file_path.h"
#include "base/logging.h"
#include "base/path_service.h"
#include "content/public/common/content_switches.h"

namespace chrome {

void GetUserCacheDirectory(const base::FilePath& profile_dir,
                           base::FilePath* result) {
  if (!PathService::Get(base::DIR_CACHE, result))
    *result = profile_dir;
}

bool GetDefaultUserDataDirectory(base::FilePath* result) {
  return PathService::Get(base::DIR_ANDROID_APP_DATA, result);
}

bool GetUserDocumentsDirectory(base::FilePath* result) {
  if (!GetDefaultUserDataDirectory(result))
    return false;
  *result = result->Append("Documents");
  return true;
}

bool GetUserDownloadsDirectory(base::FilePath* result) {
  if (!GetDefaultUserDataDirectory(result))
    return false;
  *result = result->Append("Downloads");
  return true;
}

bool GetUserMusicDirectory(base::FilePath* result) {
  NOTIMPLEMENTED();
  return false;
}

bool GetUserPicturesDirectory(base::FilePath* result) {
  NOTIMPLEMENTED();
  return false;
}

bool GetUserVideosDirectory(base::FilePath* result) {
  NOTIMPLEMENTED();
  return false;
}

bool ProcessNeedsProfileDir(const std::string& process_type) {
  // SELinux prohibits accessing the data directory for isolated services.
  if (process_type == switches::kRendererProcess)
    return false;

  return true;
}

}  // namespace chrome
