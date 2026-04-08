#include "tim_it.h"

/**
  * @brief  TIM定时中断回调函数（TIM1每10ms触发一次）
  * @note   函数名固定，HAL库自动调用，无需手动调用
  * @param  htim：定时器句柄
  * @retval 无
  */
JOYSTICK_TypeDef PS2_Data;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM5)
  {
    AX_PS2_ScanKey(&PS2_Data);

  }
}