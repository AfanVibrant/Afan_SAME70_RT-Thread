/****************************************************************************
 * Afan SAME70 RT-Thread port/rtos.h
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

#ifndef PORT_RTOS_H
#define PORT_RTOS_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <rthw.h>
#include <rtthread.h>
#include <rtconfig.h>

#include <stdio.h>
#include <stdbool.h>
#include <compiler.h>

#include "rtos_config.h"

#define rtos_irq_enter()          rt_interrupt_enter()
#define rtos_irq_exit()           rt_interrupt_leave()

#define rtos_enter_critical()     rt_base_t level;\
                                   level = rt_hw_interrupt_disable()
#define rtos_exit_critical()      rt_hw_interrupt_enable(level)

typedef rt_sem_t                  rtos_sem_t;
typedef rt_mutex_t                rtos_mutex_t;
typedef rt_mailbox_t              rtos_mbox_t;
typedef rt_uint8_t                rtos_thread_t;
typedef rt_timer_t                rtos_timer_t;
typedef unsigned int              rtos_prot_t;

#define RTOS_TICK_PER_SECOND      RT_TICK_PER_SECOND
#define RTOS_USEC_PER_TICK        (1000000/RTOS_TICK_PER_SECOND)

#define rtos_task_delay(n)        rt_thread_delay(n)
#define rtos_task_delay_ms(n)     rtos_task_delay(1000*n/RTOS_USEC_PER_TICK)
#define rtos_task_delay_us(n)     uint32_t tick = (n > RTOS_USEC_PER_TICK) ? \
                                                  (n + 1)/RTOS_USEC_PER_TICK : 1; \
                                  rtos_task_delay(tick)

#define RTOS_MBOX_NULL            (rtos_mbox_t *)0
#define RTOS_SEM_NULL             (rtos_sem_t  *)0

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PORT_RTOS_H */
