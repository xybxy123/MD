#include "dog_control.h"
#include <math.h>

/************************* 步态参数 *************************/
#define BASE_HEIGHT    0.12f
#define STEP_HEIGHT    0.02f
#define STRIDE         0.03f

/************************* 四条腿独立高度变量（DEBUG可实时修改）*************************/
// 腿编号：1=左前  2=左后  3=右前  4=右后
float leg_height[5] = {
    0.0f,             // [0] 不用
    BASE_HEIGHT - 0.000f,  // [1] 左前
    BASE_HEIGHT + 0.000f,  // [2] 左后
    BASE_HEIGHT + 0.000f,  // [3] 右前
    BASE_HEIGHT + 0.015f   // [4] 右后
};

/************************* 单腿执行 *************************/
static void leg_execute(uint8_t leg, float h_angle, float l_angle)
{
    switch(leg)
    {
        case 1: set_left_front_h_angle((int)h_angle); set_left_front_l_angle((int)l_angle); break;
        case 2: set_left_back_h_angle((int)h_angle);  set_left_back_l_angle((int)l_angle);  break;
        case 3: set_right_front_h_angle((int)h_angle);set_right_front_l_angle((int)l_angle);break;
        case 4: set_right_back_h_angle((int)h_angle); set_right_back_l_angle((int)l_angle); break;
        default: break;
    }
}

/************************* 通用IK执行 *************************/
static void leg_ik_execute(uint8_t leg, float x, float y, int type)
{
    float *angle = leg_ik(x, y, type);
    leg_execute(leg, angle[0], angle[1]);
}

/************************* 站立（使用变量高度）*************************/
void Stand(void)
{
    leg_ik_execute(1, 0, leg_height[1], 1);
    leg_ik_execute(2, 0, leg_height[2], 1);
    leg_ik_execute(3, 0, leg_height[3], 2);
    leg_ik_execute(4, 0, leg_height[4], 2);
}

/************************* 同侧行走 *************************/
void Walk(float t, int dir)
{
    float x, y;
    float stride = STRIDE * dir;

    // 左前
    if(t < 0.5f){
        x = stride*(t*2);
        y = leg_height[1] - STEP_HEIGHT*sinf(t*2*PI);
    }else{
        x = stride*(2-2*t);
        y = leg_height[1];
    }
    leg_ik_execute(1, x, y, 1);

    // 左后
    if(t < 0.5f){
        x = stride*(t*2);
        y = leg_height[2] - STEP_HEIGHT*sinf(t*2*PI);
    }else{
        x = stride*(2-2*t);
        y = leg_height[2];
    }
    leg_ik_execute(2, x, y, 1);

    // 右前
    if(t >= 0.5f){
        x = stride*(2*t-1);
        y = leg_height[3] - STEP_HEIGHT*sinf((2*t-1)*PI);
    }else{
        x = stride*(1-2*t);
        y = leg_height[3];
    }
    leg_ik_execute(3, x, y, 2);

    // 右后
    if(t >= 0.5f){
        x = stride*(2*t-1);
        y = leg_height[4] - STEP_HEIGHT*sinf((2*t-1)*PI);
    }else{
        x = stride*(1-2*t);
        y = leg_height[4];
    }
    leg_ik_execute(4, x, y, 2);
}

/************************* 对角小跑 *************************/
void Trot(float t, int dir)
{
    float x, y;
    float stride = STRIDE * dir;

    // 左前
    if(t < 0.5f){
        x = stride*(t*2);
        y = leg_height[1] - STEP_HEIGHT*sinf(t*2*PI);
    }else{
        x = stride*(2-2*t);
        y = leg_height[1];
    }
    leg_ik_execute(1, x, y, 1);

    // 右后
    if(t < 0.5f){
        x = stride*(t*2);
        y = leg_height[4] - STEP_HEIGHT*sinf(t*2*PI);
    }else{
        x = stride*(2-2*t);
        y = leg_height[4];
    }
    leg_ik_execute(4, x, y, 2);

    // 左后
    if(t >= 0.5f){
        x = stride*(2*t-1);
        y = leg_height[2] - STEP_HEIGHT*sinf((2*t-1)*PI);
    }else{
        x = stride*(1-2*t);
        y = leg_height[2];
    }
    leg_ik_execute(2, x, y, 1);

    // 右前
    if(t >= 0.5f){
        x = stride*(2*t-1);
        y = leg_height[3] - STEP_HEIGHT*sinf((2*t-1)*PI);
    }else{
        x = stride*(1-2*t);
        y = leg_height[3];
    }
    leg_ik_execute(3, x, y, 2);
}

/************************* 转向 *************************/
static void Turn(float inner, float outer)
{
    leg_ik_execute(1, inner, leg_height[1], 1);
    leg_ik_execute(2, inner, leg_height[2], 1);
    leg_ik_execute(3, outer, leg_height[3], 2);
    leg_ik_execute(4, outer, leg_height[4], 2);
}

void TurnLeft(int speed)  { Turn(STRIDE*0.3f, STRIDE*0.8f); }
void TurnRight(int speed) { Turn(STRIDE*0.8f, STRIDE*0.3f); }