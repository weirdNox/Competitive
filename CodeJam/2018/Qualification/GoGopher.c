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

u32 getAvailable(u8 Map[3][1000], u32 Row, u32 Column) {
    u32 Available = 0;
    for(u32 RowTest = Row-1; RowTest <= Row+1; ++RowTest) {
        for(u32 ColumnTest = Column-1; ColumnTest <= Column+1; ++ColumnTest) {
            if(!Map[Row][Column]) {
                ++Available;
            }
        }
    }

    return Available;
}

int main(int ArgumentCount, char *ArgumentValues[])
{
    u32 NumTests;
    scanf("%d ", &NumTests);

    for(u32 TestCase = 1; TestCase <= NumTests; ++TestCase) {
        u32 Area;
        scanf("%d", &Area);

        u32 SendToRow = 1;
        u32 SendToColumn = 1;
        u32 CurrentArea = 0;
        u8 Map[3][1000] = {};

        u32 NumberOfTries = 0;
        for(;;) {
            if(Map[0][SendToColumn-1] &&
               Map[1][SendToColumn-1] &&
               Map[2][SendToColumn-1] &&
               CurrentArea + getAvailable(Map, SendToRow, SendToColumn) < Area)
            {
                ++SendToColumn;
            } else {
                ++NumberOfTries;
                printf("%d %d\n", SendToRow+1, SendToColumn+1);
                fflush(stdout);

                s32 Row, Column;
                scanf("%d %d", &Row, &Column);
                if(Row == -1 || Column == -1) {
                    fprintf(stderr, "A problem occurred, was at %d tries\n", NumberOfTries);
                    exit(-1);
                } else if(Row == 0 && Column == 0) {
                    fprintf(stderr, "Finished with %d tries\n", NumberOfTries);
                    break;
                } else {
                    --Row; --Column;
                }

                if(!Map[Row][Column]) {
                    ++CurrentArea;
                    Map[Row][Column] = 1;
                }
            }
        }
    }

    return 0;
}
