#include "ax_ps2.h"
#include "delay.h"

// ********** 你的引脚定义 **********
#define DI()        HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6)        // 数据输入
#define CMD_H()     HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET)  // CMD置高
#define CMD_L()     HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET)// CMD置低
#define CS_H()      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET)  // CS置高
#define CS_L()      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET)// CS置低
#define CLK_H()     HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET)  // CLK置高
#define CLK_L()     HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET)// CLK置低

// PS2通信命令：请求读取手柄数据
const uint8_t PS2_cmnd[9] = {0x01, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
// 接收数据缓存
static uint8_t PS2_data[9] = {0};

/**
 * @brief  PS2手柄初始化（HAL库版本）
 * @note   CubeMX已配置GPIO，此处仅初始化默认电平
 * @param  无
 * @retval 无
 */
void AX_PS2_Init(void)
{
    CS_H();  // 关闭PS2通信（默认高电平）
    CMD_H(); // CMD引脚默认高电平
    CLK_H(); // CLK引脚默认高电平
}

/**
 * @brief  PS2单字节数据读写（核心通信函数）
 * @param  cmd: 要发送的命令字节
 * @retval 读取到的字节数据
 */
static uint8_t PS2_ReadWriteData(uint8_t cmd)
{
    volatile uint8_t res = 0;
    volatile uint8_t ref;

    // 逐位收发（8位），严格遵循PS2通信时序
    for(ref = 0x01; ref > 0x00; ref <<= 1)
    {
        // 1. 输出1位命令到CMD引脚
        if(ref & cmd)
            CMD_H();
        else
            CMD_L();

        // 2. 拉低时钟，准备读写
        CLK_L();
        delay_us(16);  // 延时保证时序稳定（F401适配）

        // 3. 读取DI引脚的1位数据
        if(DI())
            res |= ref;

        // 4. 拉高时钟，完成一位通信
        CLK_H();
        delay_us(16);
    }

    return res;
}

/**
 * @brief  扫描PS2手柄所有按键和摇杆数据
 * @param  JoystickStruct: 存储数据的结构体指针
 * @retval 无
 */
void AX_PS2_ScanKey(JOYSTICK_TypeDef *JoystickStruct)
{
    uint8_t i;
    CS_L();
    for(i = 0; i < 9; i++)
    {
        PS2_data[i] = PS2_ReadWriteData(PS2_cmnd[i]);
    }

    CS_H();

    // 解析数据时仅保留低8位，避免取反后高位干扰
    JoystickStruct->mode = PS2_data[1];
    JoystickStruct->btn1 = ~PS2_data[3] & 0xFF;
    JoystickStruct->btn2 = ~PS2_data[4] & 0xFF;
    JoystickStruct->RJoy_LR = PS2_data[5];
    JoystickStruct->RJoy_UD = PS2_data[6];
    JoystickStruct->LJoy_LR = PS2_data[7];
    JoystickStruct->LJoy_UD = PS2_data[8];
}