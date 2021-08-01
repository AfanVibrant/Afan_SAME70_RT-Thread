/****************************************************************************
 * Afan SAME70 RT-Thread board/board.c
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

#include <atmel_start.h>
#include "same70q21b.h"
#include "peripheral_clk_config.h"

#include <rtthread.h>
#include "board.h"

static struct io_descriptor* g_stdio;

void rt_hw_console_output(const char *str)
{
    io_write(g_stdio, (uint8_t *)str, strlen(str));
}
RTM_EXPORT(rt_hw_console_output);

static inline void hw_board_init_usart(void)
{
	usart_sync_get_io_descriptor(&TARGET_IO, &g_stdio);
}

/**
 * This is the timer interrupt service routine.
 *
 */
void SysTick_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}

static inline void SCB_MpuNoCacheRegion(void)
{    
	MPU->RBAR = 0x2045E000 | ((0x01UL << MPU_RBAR_VALID_Pos)) | 0x0B;

	MPU->RASR = (0x03UL  << MPU_RASR_AP_Pos) 
                   |  ((0x01UL << MPU_RASR_TEX_Pos)  | (0x00 << MPU_RASR_C_Pos) | (0x0 << MPU_RASR_B_Pos) | (0x01UL << MPU_RASR_S_Pos))
                   |   (0x0CUL << MPU_RASR_SIZE_Pos) | (0x01 << MPU_RASR_ENABLE_Pos);
}

static inline void SCB_EnableDcacheW(void)
{
    volatile uint32_t  dat32U = (*(volatile uint32_t *)(0xe000e000 + 0x0f9c));
    
    dat32U |= (0x1UL << 2);
    (*(volatile uint32_t *)(0xe000e000 + 0x0f9c)) = dat32U;
}

/**
 * This function will initial STM32 board.
 */
void rt_hw_board_init(void)
{ 
  /* Initializes MCU, drivers and middleware */
  atmel_start_init();

  /* Disable the watchdog */
  WDT->WDT_MR = WDT_MR_WDDIS;

  SCB_EnableICache();
    
//  SCB_MpuNoCacheRegion();
    
//    SCB_EnableDcacheW();
//    SCB_EnableDCache();

  /* enable USART stdout module */
  hw_board_init_usart();
    
  /* init systick */
  SysTick_Config(CONF_CPU_FREQUENCY / RT_TICK_PER_SECOND);
    
  /* set pend exception priority */
  NVIC_SetPriority(PendSV_IRQn, (1 << __NVIC_PRIO_BITS) - 1);

#ifdef RT_USING_HEAP
    #if defined(__CC_ARM) || defined(__CLANG_ARM)
        rt_system_heap_init((void*)&Image$$RW_IRAM1$$ZI$$Limit, (void*)HEAP_END);
    #elif __ICCARM__
        rt_system_heap_init((void*)HEAP_BEGIN, (void*)HEAP_END);
    #else
        /* init memory system */
        rt_system_heap_init((void*)&__bss_end, (void*)HEAP_END);
    #endif
#endif
        
#ifdef RT_USING_COMPONENTS_INIT
  rt_components_board_init();
#endif

#ifdef RT_USING_CONSOLE
//  rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
}

/*@}*/
