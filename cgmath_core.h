#ifndef CGMATH_CORE_H
#define CGMATH_CORE_H
#if !defined(CGMATH_H)
#error "Never include cgmath core directly!"
#endif

static inline float _cgmath_invsqrt(float f)
{
        int i;
        float x;
        float x2;

        x = f;

        x2 = 0.5 * x;
        i = *(int*)&x;
        i = 0x5f3759df - (i >> 1);
        x = *(float*)&i;
        x = x * (1.5f - x2 * x * x);
        return x;
}

static inline float _cgmath_absf(float f)
{
        if(f < 0.0f) {
                return -f;
        }
        return f;
}

#endif

