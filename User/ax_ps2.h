#ifndef AX_PS2_H
#define AX_PS2_H

#include "main.h"
#include <string.h>

// 手柄数据结构体：存储按键和摇杆状态
typedef struct
{
    uint8_t mode;      // 手柄工作模式
    uint8_t btn1;      // 第一组按键（SLCT/JOYR/JOYL/STRT/UP/RIGHT/DOWN/LEFT）
    uint8_t btn2;      // 第二组按键（L2/R2/L1/R1/Y/B/A/X）
    uint8_t RJoy_LR;   
    uint8_t RJoy_UD;   
    uint8_t LJoy_LR;   
    uint8_t LJoy_UD;   
} JOYSTICK_TypeDef;

/*
红灯时mode ：0x41      绿灯时mode：0x73    （一直保持这个值）




（下面的是按下才是这个值 不按时是0x00）
不管红灯绿灯：
左摇杆  btn1
上      0x10
右      0x20
下      0x40
左      0x80
上右    0x30
下右    0x60
下左    0xC0
上左    0x90
右摇杆不用
右边4个按键    btn2
上            0x10
右            0x20
下            0x40
左            0x80


复位：
                btn2
加速            0x04
减速            0x01
复位            0x08

*/


// 按键位定义（按下时对应位为1）
#define PS2_SLCT    (1 << 0)
#define PS2_JOYR    (1 << 1)
#define PS2_JOYL    (1 << 2)
#define PS2_STRT    (1 << 3)
#define PS2_UP      (1 << 4)
#define PS2_RIGHT   (1 << 5)
#define PS2_DOWN    (1 << 6)
#define PS2_LEFT    (1 << 7)

#define PS2_L2      (1 << 0)
#define PS2_R2      (1 << 1)
#define PS2_L1      (1 << 2)
#define PS2_R1      (1 << 3)
#define PS2_Y       (1 << 4)
#define PS2_B       (1 << 5)
#define PS2_A       (1 << 6)
#define PS2_X       (1 << 7)

// 函数声明
void AX_PS2_Init(void);                // PS2手柄初始化
void AX_PS2_ScanKey(JOYSTICK_TypeDef *JoystickStruct); // 扫描手柄数据

#endif /* AX_PS2_H */