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

u64 min(u64 a, u64 b) {
    return (a < b) ? a : b;
}

int compareFunction(const void *a, const void *b) {
    return (*(u64*)a - *(u64*)b);
}

int main(int ArgumentCount, char *ArgumentValues[]) {
    u32 NumTests;
    scanf("%d ", &NumTests);

    for(u32 TestCase = 1; TestCase <= NumTests; ++TestCase) {
        u64 EvenSize = 0; u64 Even[100000];
        u64 OddSize = 0; u64 Odd[100000];

        u64 N;
        scanf("%ld", &N);

        u8 NextOdd = 0;
        for(u64 Index = 0; Index < N; ++Index) {
            if(NextOdd) {
                scanf("%ld", Odd + OddSize++);
            } else {
                scanf("%ld", Even + EvenSize++);
            }
            NextOdd = !NextOdd;
        }

        qsort(Even, EvenSize, sizeof(*Even), compareFunction);
        qsort(Odd, OddSize, sizeof(*Odd), compareFunction);

        u64 Fail = -1;
        for(u64 IteratorIndex = 0; IteratorIndex < OddSize && Fail == -1; ++IteratorIndex) {
            if(Even[IteratorIndex] > Odd[IteratorIndex]) {
                Fail = 2*IteratorIndex;
            } else if(((IteratorIndex+1) < EvenSize) && (Odd[IteratorIndex] > Even[IteratorIndex+1])) {
                Fail = 2*IteratorIndex + 1;
            }
        }

        if(Fail == -1) {
            printf("Case #%d: OK\n", TestCase);
        } else {
            printf("Case #%d: %lu\n", TestCase, Fail);
        }
    }
}
