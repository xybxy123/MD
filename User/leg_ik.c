#include"leg_ik.h"

static float clampf(float v, float lo, float hi)
{
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}

// 左：Size = 1   右：Size = 2
float *leg_ik(float x, float y, int Size){
    
    // x = - x ;
    

    static float angle[2];

    const float l1 = L1;
    const float l2 = L2;

    float fai, ham, shank, r; 

    r = sqrtf(x*x + y*y);

    // Avoid division by zero and floating-point spill beyond acosf domain.
    if (r < 1e-6f) {
        r = 1e-6f;
    }

    shank = acosf(clampf((r*r - l1*l1 - l2*l2) / (2 * l1 * l2), -1.0f, 1.0f));
    fai = acosf(clampf((l1*l1 + r*r - l2*l2) / (2 * l1 * r), -1.0f, 1.0f));

    if (x > 0) {
        ham = fabsf(atanf(y / x)) + fai;
    } else if (x < 0) {
        ham = PI - (atanf( y / (-x) ) - fai);
    } else {
        ham = PI - 1.5707f + fai;
    }

    angle[0] = ham * 180.0f / PI;
    angle[1] = shank * 180.0f / PI;
    
    
    angle[1] = angle[0] - angle[1];
    
    if(Size == 2)
    {
        angle[0] = 180 - angle[0];
        angle[1] = 180 - angle[1];
    }


    return angle;
}