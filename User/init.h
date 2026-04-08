#ifndef INIT_H
#define INIT_H


#include "server_drive.h"

#include "leg_ik.h"
#include "dog_control.h"

#include "ax_ps2.h"
#include "delay.h"

#include <math.h>

// #include "stm32f4xx_hal.h"
// #include "tim.h"
// #include "rtc.h"

#include <stdint.h> 

void All_init();
void test();// 测试代码
void Dog_Run(void);

#endif