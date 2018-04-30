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

int main(int ArgumentCount, char *ArgumentValues[]) {
    u32 NumTests;
    scanf("%d ", &NumTests);

    for(u32 TestCase = 1; TestCase <= NumTests; ++TestCase) {
        u32 R, C, H, V;
        u32 Total = 0;

        char Waffle[100][100] = {};
        u32 CumulativeRows[100] = {};
        u32 CumulativeColumns[100]= {};

        scanf("%d %d %d %d ", &R, &C, &H, &V);
        for(u32 Row = 0; Row < R; ++Row) {
            for(u32 Column = 0; Column < C; ++Column) {
                scanf("%c", &Waffle[Row][Column]);
                if(Waffle[Row][Column] == '@') {
                    ++CumulativeRows[Row];
                    ++CumulativeColumns[Column];
                    ++Total;
                }
            }
            scanf(" ");
        }


        for(u32 Row = 1; Row < R; ++Row) {
            CumulativeRows[Row] += CumulativeRows[Row-1];
        }
        for(u32 Column = 1; Column < C; ++Column) {
            CumulativeColumns[Column] += CumulativeColumns[Column-1];
        }

        if((Total % ((H+1)*(V+1))) || (Total % (H+1)) || (Total % (V+1))) {
            printf("Case #%d: IMPOSSIBLE\n", TestCase);
        } else {
            u32 NumberOfChipPerH = (Total / (H+1));
            u32 NextHCut = 1;
            u32 HCuts[102] = {};
            u32 NumberOfChipPerV = (Total / (V+1));
            u32 NextVCut = 1;
            u32 VCuts[102] = {};

            for(u32 Row = 0; Row < R; ++Row) {
                if(CumulativeRows[Row] == NextHCut * NumberOfChipPerH) {
                    HCuts[NextHCut-1] = Row+1;
                    ++NextHCut;
                } else if(CumulativeRows[Row] > NextHCut * NumberOfChipPerH) {
                    NextHCut = -1;
                    break;
                }
            }
            for(u32 Column = 0; Column < C; ++Column) {
                if(CumulativeColumns[Column] == NextVCut * NumberOfChipPerV) {
                    VCuts[NextVCut-1] = Column+1;
                    ++NextVCut;
                } else if(CumulativeColumns[Column] > NextVCut * NumberOfChipPerV) {
                    NextVCut = -1;
                    break;
                }
            }

            HCuts[H+1] = R;
            VCuts[V+1] = C;

            if(NextHCut == -1 || NextVCut == -1) {
                printf("Case #%d: IMPOSSIBLE\n", TestCase);
            } else {
                u32 HStart = 0;
                for(u32 HCut = 0; HCut < H+1; ++HCut) {
                    u32 VStart = 0;
                    for(u32 VCut = 0; VCut < V+1; ++VCut) {
                        u32 NumberOfChips = 0;
                        for(u32 Row = HStart; Row < HCuts[HCut]; ++Row) {
                            for(u32 Column = VStart; Column < VCuts[VCut]; ++Column) {
                                if(Waffle[Row][Column] == '@') {
                                    ++NumberOfChips;
                                }
                            }
                        }
                        if(NumberOfChips != Total / ((H+1)*(V+1))) {
                            goto impossible;
                        }
                        VStart = VCuts[VCut];
                    }
                    HStart = HCuts[HCut];
                }
                if(0) {
            impossible:
                    printf("Case #%d: IMPOSSIBLE\n", TestCase);
                } else {
                    printf("Case #%d: POSSIBLE\n", TestCase);
                }
            }
        }
    }
}
