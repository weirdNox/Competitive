#include <assert.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main() {
    u32 NumTests;
    scanf("%d ", &NumTests);

    for(u32 TestCase = 1; TestCase <= NumTests; ++TestCase) {
        u32 FlavorCount[200] = {};
        u8 FlavorServed[200] = {};
        u32 N;
        scanf("%d ", &N);
        for(u32 I = 0; I < N; ++I) {
            u32 D;
            scanf("%d", &D);
            s32 BestFlavor = -1;
            for(u32 F = 0; F < D; ++F) {
                u32 Flavor;
                scanf("%d", &Flavor);
                ++FlavorCount[Flavor];
                if(!FlavorServed[Flavor] && (BestFlavor == -1 || FlavorCount[Flavor] < FlavorCount[BestFlavor])) {
                    BestFlavor = Flavor;
                }
            }
            if(BestFlavor != -1) {
                FlavorServed[BestFlavor] = 1;
            }
            printf("%d\n", BestFlavor);
            fflush(stdout);
        }
    }
}
