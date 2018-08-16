/******************************************************************************
 *
 *  Copyright (C) 2014 Google, Inc.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at:
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 ******************************************************************************/
#include <assert.h>

#include "buffer_allocator.h"
#include "bt_common.h"

//M: host trigger FW assert
#ifdef MTK_BT_COMMON
#define LOG_TAG "buffer_allocator"

#include "bt_vendor_lib.h"
#include "osi/include/log.h"
#include "vendor.h"
#endif
//M: END

static void *buffer_alloc(size_t size) {
//M: host trigger FW assert
#ifdef MTK_BT_COMMON
  if ((int)size > BT_DEFAULT_BUFFER_SIZE) {
    static int b_trig_coredump = false;
    int stack_trigger_reason;

    LOG_INFO(LOG_TAG, "%s Stack triggers firmware coredump - size(%zu) > GKI_MAX_BUF_SIZE", __func__, size);
    stack_trigger_reason = 31; /* 31 for host assert */
    if (0 == vendor_get_interface()->send_command(VENDOR_SET_FW_ASSERT, &stack_trigger_reason)) {
      LOG_INFO(LOG_TAG, "%s Act FW Coredump Success!", __func__);
      b_trig_coredump = true;
    } else {
      LOG_WARN(LOG_TAG, "%s Act FW Coredump Fails!", __func__);
      assert(size <= BT_DEFAULT_BUFFER_SIZE);
    }
  }
#else
  assert(size <= BT_DEFAULT_BUFFER_SIZE);
#endif

  return osi_malloc(size);
}

static const allocator_t interface = {
  buffer_alloc,
  osi_free
};

const allocator_t *buffer_allocator_get_interface() {
  return &interface;
}
