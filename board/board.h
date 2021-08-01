/****************************************************************************
 * Afan SAME70 RT-Thread board/board.h
 * Author : Afan Vibrant (AfanVibrant@outlook.com)
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

#ifndef __BOARD_H__
#define __BOARD_H__

#include <same70q21b.h>

// <o> Internal SRAM memory size[Kbytes] <256-384>
//  <i>Default: 384
#define SAMV71_SRAM_SIZE   384
#define SAMV71_SRAM_END   (0x20400000 + SAMV71_SRAM_SIZE * 1024)

#if defined(__CC_ARM) || defined(__CLANG_ARM)
extern int Image$$RW_IRAM1$$ZI$$Limit;
#define HEAP_BEGIN    (&Image$$RW_IRAM1$$ZI$$Limit)
#elif __ICCARM__
#pragma section="HEAP"
#define HEAP_BEGIN    (__segment_begin("HEAP"))
#define HEAP_END      (__segment_end("HEAP"))
#else
extern int __bss_end;
#define HEAP_BEGIN    (&__bss_end)
#define HEAP_END      SAMV71_SRAM_END
#endif

void rt_hw_board_init(void);

#endif

