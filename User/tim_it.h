#ifndef TIM_IT_H
#define TIM_IT_H

#include "tim.h"
#include "ax_ps2.h"

extern JOYSTICK_TypeDef PS2_Data;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif
