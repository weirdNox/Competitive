#include <stdio.h>
#include <stdint.h>
#include <assert.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

int main(int ArgumentCount, char *ArgumentValues[]) {
    u32 NumTests;
    scanf("%d ", &NumTests);

    for(u32 TestCase = 1; TestCase <= NumTests; ++TestCase) {
        u32 MaxDamage;
        char Program[1000];
        scanf("%d %s", &MaxDamage, Program);

        u32 ProgramSize = 0;
        u32 CurrentDamage = 0;
        u32 NumberOfS = 0;

        {
            u32 DamagePerS = 1;
            for(char *Iterator = Program; *Iterator; ++Iterator) {
                ++ProgramSize;
                if(*Iterator == 'S') {
                    CurrentDamage += DamagePerS;
                    ++NumberOfS;
                } else {
                    DamagePerS *= 2;
                }
            }
        }

        if(NumberOfS > MaxDamage) {
            printf("Case #%d: IMPOSSIBLE\n", TestCase);
        } else {
            u32 NumberOfMovements = 0;
            while(CurrentDamage > MaxDamage) {
                ++NumberOfMovements;
                char Previous = 0;
                u32 DamagePerS = 1;
                char *Best = 0;
                u32 BestDamage;
                for(char *Iterator = Program; *Iterator; ++Iterator) {
                    if(*Iterator == 'C') {
                        DamagePerS *= 2;
                    } else if(Previous == 'C') {
                        Best = Iterator;
                        BestDamage = DamagePerS;
                    }

                    Previous = *Iterator;
                }
                assert(Best);
                CurrentDamage -= BestDamage/2;
                *(Best-1) = 'S';
                *(Best) = 'C';
            }

            printf("Case #%d: %d\n", TestCase, NumberOfMovements);
        }
    }
}
