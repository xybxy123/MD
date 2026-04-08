#include "init.h"

extern JOYSTICK_TypeDef PS2_Data;
extern uint8_t dog_state;
float angle1, angle2, angle3, angle4, angle5, angle6, angle7, angle8;

typedef enum {
    STATE_STAND = 0,
    STATE_WALK_FORWARD,
    STATE_WALK_BACK,
    STATE_TROT_FORWARD,
    STATE_TROT_BACK
} DogState;

DogState current_state = STATE_STAND;

void All_init(){
    HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_4);
    HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_4);

    HAL_TIM_Base_Start_IT(&htim5);
    AX_PS2_Init();

    // 初始姿态
	// 上电先保持站立
	Stand();



}


void test(void)
{

    switch (current_state)
    {
    case STATE_STAND:
        Stand();
        break;
    
    default:
        break;
    }

    // if(PS2_Data.btn1 == 0x10) dog_state = 1;
    // else if(PS2_Data.btn1 == 0x40) dog_state = 2;
    // else if(PS2_Data.btn1 == 0x80) dog_state = 3;
    // else if(PS2_Data.btn1 == 0x20) dog_state = 4;

    // if(PS2_Data.btn2 == 0x10) dog_state = 0;

}

