#ifndef LEG_IK_H
#define LEG_IK_H

#include <math.h> 
#include <stdint.h> 
#include <stdio.h>
#include <string.h>

#define L1 0.09f // 大腿
#define L2 0.10630f // 小腿

#ifndef PI
#define PI      3.1415926535f
#endif

// 输入 ： 以大腿舵机为原点 倒过来的 x y 
// 输出 ： 两个舵机的角度  angle[0]为大腿舵机角度 angle[1]为小腿舵机角度
float *leg_ik(float x, float y, int Size);

#endif