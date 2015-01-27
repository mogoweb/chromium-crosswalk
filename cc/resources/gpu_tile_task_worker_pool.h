// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CC_RESOURCES_GPU_TILE_TASK_WORKER_POOL_H_
#define CC_RESOURCES_GPU_TILE_TASK_WORKER_POOL_H_

#include "base/memory/weak_ptr.h"
#include "cc/resources/tile_task_runner.h"
#include "cc/resources/tile_task_worker_pool.h"

namespace cc {
class ResourceProvider;

class CC_EXPORT GpuTileTaskWorkerPool : public TileTaskWorkerPool,
                                        public TileTaskRunner,
                                        public TileTaskClient {
 public:
  ~GpuTileTaskWorkerPool() override;

  static scoped_ptr<TileTaskWorkerPool> Create(
      base::SequencedTaskRunner* task_runner,
      TaskGraphRunner* task_graph_runner,
      ResourceProvider* resource_provider);

  // Overridden from TileTaskWorkerPool:
  TileTaskRunner* AsTileTaskRunner() override;

  // Overridden from TileTaskRunner:
  void SetClient(TileTaskRunnerClient* client) override;
  void Shutdown() override;
  void ScheduleTasks(TileTaskQueue* queue) override;
  void CheckForCompletedTasks() override;
  ResourceFormat GetResourceFormat() override;

  // Overridden from TileTaskClient:
  scoped_ptr<RasterBuffer> AcquireBufferForRaster(
      const Resource* resource) override;
  void ReleaseBufferForRaster(scoped_ptr<RasterBuffer> buffer) override;

 private:
  GpuTileTaskWorkerPool(base::SequencedTaskRunner* task_runner,
                        TaskGraphRunner* task_graph_runner,
                        ResourceProvider* resource_provider);

  void OnTaskSetFinished(TaskSet task_set);
  void CompleteTasks(const Task::Vector& tasks);

  scoped_refptr<base::SequencedTaskRunner> task_runner_;
  TaskGraphRunner* task_graph_runner_;
  const NamespaceToken namespace_token_;
  TileTaskRunnerClient* client_;
  ResourceProvider* resource_provider_;

  TaskSetCollection tasks_pending_;

  scoped_refptr<TileTask> task_set_finished_tasks_[kNumberOfTaskSets];

  // Task graph used when scheduling tasks and vector used to gather
  // completed tasks.
  TaskGraph graph_;
  Task::Vector completed_tasks_;

  base::WeakPtrFactory<GpuTileTaskWorkerPool>
      task_set_finished_weak_ptr_factory_;

  base::WeakPtrFactory<GpuTileTaskWorkerPool> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(GpuTileTaskWorkerPool);
};

}  // namespace cc

#endif  // CC_RESOURCES_GPU_TILE_TASK_WORKER_POOL_H_
