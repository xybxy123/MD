#include "delay.h"

// 基于SysTick的us级延时（适配STM32F4系列，168MHz/84MHz通用）
void delay_us(uint32_t us)
{
    uint32_t ticks;
    uint32_t told, tnow, tcnt = 0;
    uint32_t reload = SysTick->LOAD & 0x00FFFFFF; // 仅保留24位重装值

    // 计算需要的节拍数（SystemCoreClock需正确配置为实际主频）
    ticks = us * (SystemCoreClock / 1000000);
    if (ticks == 0) return; // 避免0延时的无效循环

    told = SysTick->VAL & 0x00FFFFFF; // 屏蔽高8位，仅取24位有效值
    while(1)
    {
        tnow = SysTick->VAL & 0x00FFFFFF;
        if(tnow != told)
        {
            if(tnow < told) 
                tcnt += told - tnow; // 正常向下计数
            else 
                tcnt += reload - tnow + 1 + told; // 溢出后计数（补+1）
            told = tnow;
            if(tcnt >= ticks) break; // 延时时间到，退出循环
        }
    }
}