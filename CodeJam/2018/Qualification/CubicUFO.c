#include <assert.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef float r32;
typedef double r64;

typedef struct {
    r64 X;
    r64 Y;
    r64 Z;
} point;

double Pi = 3.141592653589793238462643383279502884;

void RotateOverX(point *P, r64 Angle) {
    r64 Y = P->Y;
    r64 Z = P->Z;
    P->Y = cos(Angle)*Y - sin(Angle)*Z;
    P->Z = sin(Angle)*Y + cos(Angle)*Z;
}

void RotateOverZ(point *P, r64 Angle) {
    r64 X = P->X;
    r64 Y = P->Y;
    P->X = cos(Angle)*X - sin(Angle)*Y;
    P->Y = sin(Angle)*X + cos(Angle)*Y;
}

int main(int ArgumentCount, char *ArgumentValues[])
{
    u32 NumTests;
    scanf("%d ", &NumTests);

    for(u32 TestCase = 1; TestCase <= NumTests; ++TestCase) {
        r64 Area;
        scanf("%lf", &Area);

        point Point1 = {0.5, 0  , 0  };
        point Point2 = {0  , 0.5, 0  };
        point Point3 = {0  , 0  , 0.5};

        // NOTE(nox): It can be proven that the area of a unit cube projection on the XZ
        // plane is equal to its projection on the Y axis (MaxY - MinY)
        //
        // The definition of Projected Area helps in the proof:
        // https://en.wikipedia.org/wiki/Projected_area

        if(Area <= sqrt(2)) {
            r64 Angle = asin(fmin(Area/sqrt(2), 1.0)) - Pi/4.0;
            fprintf(stderr, "Over X: %.16lf rad\n", Angle);
            RotateOverX(&Point1, Angle);
            RotateOverX(&Point2, Angle);
            RotateOverX(&Point3, Angle);
        } else {
            fprintf(stderr, "Over X: %.16lf rad\n", Pi/4);
            RotateOverX(&Point1, Pi/4);
            RotateOverX(&Point2, Pi/4);
            RotateOverX(&Point3, Pi/4);

            r64 Angle = asin(fmin(Area/sqrt(3), 1.0)) - atan(sqrt(2));
            fprintf(stderr, "Over Z: %.16lf rad\n", Angle);
            RotateOverZ(&Point1, Angle);
            RotateOverZ(&Point2, Angle);
            RotateOverZ(&Point3, Angle);
        }

        printf("Case #%d:\n", TestCase);
        printf("%.16lf %.16lf %.16lf\n", Point1.X, Point1.Y, Point1.Z);
        printf("%.16lf %.16lf %.16lf\n", Point2.X, Point2.Y, Point2.Z);
        printf("%.16lf %.16lf %.16lf\n", Point3.X, Point3.Y, Point3.Z);
    }
}
