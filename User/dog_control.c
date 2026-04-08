#include "dog_control.h"

/************************* 配置 *************************/
#define BASE_HEIGHT    0.14f
#define STEP_HEIGHT    0.02f
#define STRIDE         0.03f

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

/************************* 站立 *************************/
void Stand(void)
{
    set_left_back_h_angle(155);   set_left_back_l_angle(23);
    set_right_back_h_angle(35);   set_right_back_l_angle(165);
    set_left_front_h_angle(155);  set_left_front_l_angle(25);
    set_right_front_h_angle(35);  set_right_front_l_angle(165);
}

/************************* 同侧行走（前进/后退合并）*************************/
void Walk(float t, int dir)
{
    float x, y;
    float stride = STRIDE * dir;

    // 左前+左后
    if(t < 0.5f)
    {
        x = stride * (t*2);
        y = BASE_HEIGHT - STEP_HEIGHT * sinf(t*2*PI);
    }
    else
    {
        x = stride * (2 - 2*t);
        y = BASE_HEIGHT;
    }
    leg_ik_execute(1, x, y, 1);
    leg_ik_execute(2, x, y, 1);

    // 右前+右后
    if(t >= 0.5f)
    {
        x = stride * (2*t - 1);
        y = BASE_HEIGHT - STEP_HEIGHT * sinf((2*t-1)*PI);
    }
    else
    {
        x = stride * (1 - 2*t);
        y = BASE_HEIGHT;
    }
    leg_ik_execute(3, x, y, 2);
    leg_ik_execute(4, x, y, 2);
}

/************************* 对角小跑（前进/后退合并）*************************/
void Trot(float t, int dir)
{
    float x, y;
    float stride = STRIDE * dir;

    // 左前 + 右后
    if(t < 0.5f)
    {
        x = stride * (t*2);
        y = BASE_HEIGHT - STEP_HEIGHT * sinf(t*2*PI);
    }
    else
    {
        x = stride * (2 - 2*t);
        y = BASE_HEIGHT;
    }
    leg_ik_execute(1, x, y, 1);
    leg_ik_execute(4, x, y, 2);

    // 左后 + 右前
    if(t >= 0.5f)
    {
        x = stride * (2*t - 1);
        y = BASE_HEIGHT - STEP_HEIGHT * sinf((2*t-1)*PI);
    }
    else
    {
        x = stride * (1 - 2*t);
        y = BASE_HEIGHT;
    }
    leg_ik_execute(2, x, y, 1);
    leg_ik_execute(3, x, y, 2);
}

/************************* 转向合并逻辑 *************************/
static void Turn(float inner, float outer)
{
    leg_ik_execute(1, inner, BASE_HEIGHT, 1);
    leg_ik_execute(2, inner, BASE_HEIGHT, 1);
    leg_ik_execute(3, outer, BASE_HEIGHT, 2);
    leg_ik_execute(4, outer, BASE_HEIGHT, 2);
}

void TurnLeft(int speed)  { Turn(STRIDE*0.3f, STRIDE*0.8f); }
void TurnRight(int speed) { Turn(STRIDE*0.8f, STRIDE*0.3f); }