#include "server_drive.h"
#define STEP_INTERVAL_MS   100000   // 步进间隔100ms
#define STEP_ANGLE         5     // 每次步进5°
#define L_H_ANGLE 176
#define L_L_ANGLE 12
#define R_H_ANGLE 4
#define R_L_ANGLE 168
#define ERROR 9

/*

TIM2 左
通道12前 34后

TIM3 右 
通道12前 34后

1 3 上   2 4 下

*/


void set_left_front_h_angle(int angle) {
    if (angle < 90) angle = 90;
    else if (angle > 170) angle = 170;

    uint8_t target = (uint8_t)angle;

    // while (current_angle != target) {
    //     if (current_angle < target) {
    //         current_angle += STEP_ANGLE;
    //         if (current_angle > target) current_angle = target;
    //     } else {
    //         current_angle -= STEP_ANGLE;
    //         if (current_angle < target) current_angle = target;
    //     }
        uint32_t pwmVal = (target * 125) / 180 + 31;
        __HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1, pwmVal);
    //    delay_us(STEP_INTERVAL_MS); // 假设你有 delay_ms 函数
    // }
}

void set_left_front_l_angle(int angle) {

    if (angle < 15) angle = 15;
    else if (angle > 55) angle = 55;

    uint8_t target = (uint8_t)angle;

    // while (current_angle != target) {
    //     if (current_angle < target) {
    //         current_angle += STEP_ANGLE;
    //         if (current_angle > target) current_angle = target;
    //     } else {
    //         current_angle -= STEP_ANGLE;
    //         if (current_angle < target) current_angle = target;
    //     }
        uint32_t pwmVal = (target * 125) / 180 + 31;
        __HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, pwmVal);
    //     delay_us(STEP_INTERVAL_MS); // 假设你有 delay_ms 函数
    // }
}

void set_right_front_l_angle(int angle) {

    if (angle < 135) angle = 135;
    else if (angle > 165) angle = 165;

    uint8_t target =  (uint8_t)angle;
    
    // while (current_angle != target) {
    //     if (current_angle < target) {
    //         current_angle += STEP_ANGLE;
    //         if (current_angle > target) current_angle = target;
    //     } else {
    //         current_angle -= STEP_ANGLE;
    //         if (current_angle < target) current_angle = target;
    //     }
         uint32_t pwmVal = (target * 125) / 180 + 31;
        __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_2, pwmVal);
    //     delay_us(STEP_INTERVAL_MS); // 100ms
    // }
}

void set_right_front_h_angle(int angle) {
    if (angle < 10) angle = 10;
    else if (angle > 90) angle = 90;

    uint8_t target =  (uint8_t)angle;

    // while (current_angle != target) {
    //     if (current_angle < target) {
    //         current_angle += STEP_ANGLE;
    //         if (current_angle > target) current_angle = target;
    //     } else {
    //         current_angle -= STEP_ANGLE;
    //         if (current_angle < target) current_angle = target;
    //     }
        uint32_t pwmVal = (target * 125) / 180 + 31;
        __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, pwmVal);
    //     delay_us(STEP_INTERVAL_MS);
    // }
}

void set_left_back_h_angle(int angle){

    if (angle < 90) angle = 90;
    else if (angle > 170) angle = 170;

    uint8_t target = (uint8_t)angle;
    // while (current_angle != target) {
    //     if (current_angle < target) {
    //         current_angle += STEP_ANGLE;
    //         if (current_angle > target) current_angle = target;
    //     } else {
    //         current_angle -= STEP_ANGLE;
    //         if (current_angle < target) current_angle = target;
    //     }
    uint32_t pwmVal = (target * 125) / 180 + 31;
    __HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, pwmVal);
    // delay_us(STEP_INTERVAL_MS);
    // }
    return;
}

void set_left_back_l_angle(int angle){

    if (angle < 15) angle = 15;
    else if (angle > 55) angle = 55;
    
    uint8_t target = (uint8_t)angle;
    // while (current_angle != target) {
    //     if (current_angle < target) {
    //         current_angle += STEP_ANGLE;
    //         if (current_angle > target) current_angle = target;
    //     } else {
    //         current_angle -= STEP_ANGLE;
    //         if (current_angle < target) current_angle = target;
    //     }
    uint32_t pwmVal = (target * 125) / 180 + 31;
    __HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4, pwmVal);
    // delay_us(STEP_INTERVAL_MS);
    // }
    return;
}

void set_right_back_l_angle(int angle){

    if (angle < 135) angle = 135;
    else if (angle > 165) angle = 165;

    uint8_t target = (uint8_t)angle;
    // while (current_angle != target) {
    //     if (current_angle < target) {
    //         current_angle += STEP_ANGLE;
    //         if (current_angle > target) current_angle = target;
    //     } else {
    //         current_angle -= STEP_ANGLE;
    //         if (current_angle < target) current_angle = target;
    //     }
    uint32_t pwmVal = (target * 125) / 180 + 31;
    __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_4, pwmVal);
    // delay_us(STEP_INTERVAL_MS);
    // }
    return;
}

void set_right_back_h_angle(int angle){

    if (angle < 10) angle = 10;
    else if (angle > 90) angle = 90;
    
    static uint8_t current_angle = R_H_ANGLE;
    uint8_t target = (uint8_t)angle;
    //  while (current_angle != target) {
    //     if (current_angle < target) {
    //         current_angle += STEP_ANGLE;
    //         if (current_angle > target) current_angle = target;
    //     } else {
    //         current_angle -= STEP_ANGLE;
    //         if (current_angle < target) current_angle = target;
    //     }
    uint32_t pwmVal = (target * 125) / 180 + 31;
    __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3, pwmVal);
    // delay_us(STEP_INTERVAL_MS);
    // }
    return;
}
