#ifndef DOG_CONTROL_H
#define DOG_CONTROL_H

#include "server_drive.h"
#include "leg_ik.h"
#include <math.h>
#include <stdint.h>

#define L1      0.09f
#define L2      0.10630f

#ifndef PI
#define PI      3.1415926535f
#endif

typedef struct {
    float x1, x2, x3, x4;
    float y1, y2, y3, y4;
} TrotOutput;

void Stand(void);
void TurnLeft(int speed);
void TurnRight(int speed);

// 合并冗余函数，只保留通用接口
void Walk(float t, int dir);    // dir:1前进 -1后退
void Trot(float t, int dir);    // dir:1前进 -1后退

// 保留原名兼容旧代码
#define WalkForward(t) Walk(t, 1)
#define WalkBack(t)    Walk(t, -1)
#define TrotForward(t) Trot(t, 1)
#define TrotBack(t)    Trot(t, -1)

#endif