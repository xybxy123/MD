// 测试函数是否正确设置舵机角度
#ifndef SERVER_DRIVE_H
#define SERVER_DRIVE_H

#include "tim.h" 
#include "delay.h"

void set_left_front_h_angle(int angle); // 90 ~ 170
void set_left_front_l_angle(int angle); // 15 ~ 55

void set_left_back_h_angle(int angle);
void set_left_back_l_angle(int angle);

void set_right_front_h_angle(int angle); // 10 ~ 90
void set_right_front_l_angle(int angle); // 135~165

void set_right_back_h_angle(int angle);
void set_right_back_l_angle(int angle);

#endif