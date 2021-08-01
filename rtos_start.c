/****************************************************************************
 * Afan SAME70 RT-Thread rtos_start.c
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
#include <peripheral_clk_config.h>

#include "rtos_config.h"

#include "rtos.h"
#include "rtos_start.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Public Data
 ****************************************************************************/

/****************************************************************************
 * Private Data
 ****************************************************************************/

static const char *led_task_name = "led task";
static rt_thread_t led_thread_id;

/****************************************************************************
 * Public Functions Prototypes
 ****************************************************************************/

/****************************************************************************
 * Private Functions Prototypes
 ****************************************************************************/

static void led_thread_entry(void *parameter);

/****************************************************************************
 * Private Functions
 ****************************************************************************/


/****************************************************************************
 * Name: led_thread_entry
 *
 * Description:
 *   Task for LED.
 *
 * Input Parameters:
 *   NONE.
 *
 * Returned Value:
 *   None.
 *
 ****************************************************************************/

static void led_thread_entry(void *parameter)
{
  (void)parameter;

  while (1)
  {
    printf("led task run\r\n");
    rtos_task_delay_ms(500);
  }
}

/*
 * Example
 */
void RT_V403X_start(void)
{
  printf("Start running RT-Thread on Microchip SAME70\r\n");

  led_thread_id = rt_thread_create(led_task_name, led_thread_entry,
                                   NULL, LEDRUN_THREAD_STKSZ,
                                   LEDRUN_THREAD_PRIO, 20);
  if(led_thread_id != RT_NULL) {

  }
}
