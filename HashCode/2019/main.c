#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "external/meow_intrinsics.h"
#include "external/meow_hash.h"

#define arrayCount(Arr) (sizeof(Arr)/sizeof(*(Arr)))

#define alignDown(N, A) ((N) & ~((A) - 1))
#define alignUp(N, A) alignDown((N) + (A) - 1, (A))
#define alignDownPtr(P, A) ((void *)alignDown((uptr)(P), (A)))
#define alignUpPtr(P, A) ((void *)alignUp((uptr)(P), (A)))

#define getLowestBit(X) ((X) &= -(X))

#define max(A, B) ((A) > (B) ? (A) : (B))
#define min(A, B) ((A) > (B) ? (B) : (A))

#define staticAssert(Expr, ...) typedef char STATIC_ASSERTION__[(Expr)?1:-1]
#if Debug
#define assert(Expr) if(!(Expr)) { abort(); }
#else
#define assert(Expr) (void)(0)
#endif
#define invalidCodePath() assert(!"Invalid code path")
#define invalidCase(Case) case Case: { assert(!"Invalid case"); } break
#define invalidDefaultCase() default: { assert(!"Invalid default case"); } break

typedef    int8_t  s8;
typedef   uint8_t  u8;
typedef   int16_t s16;
typedef  uint16_t u16;
typedef   int32_t s32;
typedef  uint32_t u32;
typedef   int64_t s64;
typedef  uint64_t u64;
typedef     float r32;
typedef    double r64;
typedef        s8  b8;
typedef       s16 b16;
typedef       s32 b32;
typedef       s64 b64;

typedef    size_t midx;
typedef  intptr_t sptr;
typedef uintptr_t uptr;


static void *xMalloc(midx Size) {
    void *Result = malloc(Size);
    if(!Result) {
        exit(1);
    }
    return Result;
}

static void *xRealloc(void *Old, midx NewSize) {
    void *Result = realloc(Old, NewSize);
    if(!Result) {
        exit(1);
    }
    return Result;
}

enum {
    MemBlock_MinimumSize = 10*1024*1024,
};
typedef struct mem_block_hdr {
    struct mem_block_hdr *Previous;
    u8 Data[];
} mem_block_hdr;

typedef struct {
    u8 *Next;
    u8 *End;
    mem_block_hdr *CurrentBlock;
} memory_arena;

typedef enum {
    ArenaFlag_ClearToZero = 1<<0,
    // NOTE(nox): The alignment flags _need_ to have these values!
    ArenaFlag_Align2  = 1<<1,
    ArenaFlag_Align4  = 1<<2,
    ArenaFlag_Align8  = 1<<3,

    ArenaFlag_Default = ArenaFlag_Align4,
} arena_flag;

static inline midx getAlignment(arena_flag Flags) {
    Flags &= (ArenaFlag_Align2 | ArenaFlag_Align4 | ArenaFlag_Align8);
    midx Alignment = getLowestBit(Flags);
    if(!Alignment) {
        Alignment = 1;
    }

    return Alignment;
}

static inline midx getEffectiveSize(uptr Next, midx SizeQuery, midx Alignment) {
    midx EffectiveSize = SizeQuery;

    midx AlignMask = Alignment - 1;
    if(Next & AlignMask) {
        EffectiveSize += Alignment - (Next & AlignMask);
    }

    return EffectiveSize;
}

static inline void zeroSize(void *Dest, midx Size) {
    u8 *Byte = (u8 *)Dest;
    while(Size--) {
        *Byte++ = 0;
    }
}

#define pushStruct(Arena, type, Flags) (type *)pushSize_(Arena, sizeof(type), Flags)
static void *pushSize(memory_arena *Arena, midx SizeQuery, arena_flag Flags) {
    midx EffectiveSize = 0;
    if(Arena->CurrentBlock) {
        EffectiveSize = getEffectiveSize((uptr)Arena->Next, SizeQuery, getAlignment(Flags));
    }

    if(!Arena->CurrentBlock || Arena->Next + EffectiveSize > Arena->End) {
        // NOTE(nox): Need to allocate a new block and, as malloc returns aligned memory, we just check
        // at compile-time that the header size is multiple of 8 bytes.
        staticAssert((sizeof(mem_block_hdr) & (8-1)) == 0);

        EffectiveSize = SizeQuery;
        midx BlockSize = max(sizeof(mem_block_hdr)+EffectiveSize, MemBlock_MinimumSize);
        mem_block_hdr *NewBlock = xMalloc(BlockSize);

        NewBlock->Previous = Arena->CurrentBlock;
        Arena->CurrentBlock = NewBlock;
        Arena->Next = NewBlock->Data;
        Arena->End  = (u8 *)(NewBlock) + BlockSize;
    }

    assert(EffectiveSize >= SizeQuery);
    assert(Arena->Next + EffectiveSize <= Arena->End);
    Arena->Next += EffectiveSize;
    void *Result = Arena->Next - SizeQuery;

    if(Flags & ArenaFlag_ClearToZero) {
        zeroSize(Result, SizeQuery);
    }

    return Result;
}


typedef struct intern {
    midx Length;
    struct intern *Next;
    u32 TimesRepeated;
    char String[];
} intern;

enum {
    InternHashSize = 1<<15,
};

memory_arena InternArena;
intern *Interns[InternHashSize];

u64 UniqueInternCount = 0;
char *stringIntern(char *String) {
    midx Length = strlen(String);
    u64 Hash = MeowU64From(MeowHash_Accelerated(0, Length, String), 0);
    u64 Slot = Hash & (InternHashSize-1);
    intern *Intern = Interns[Slot];
    for(intern *Iterator = Intern; Iterator; Iterator = Iterator->Next) {
        if(Length == Iterator->Length && strncmp(String, Iterator->String, Length) == 0) {
            ++Iterator->TimesRepeated;
            return Iterator->String;
        }
    }

    ++UniqueInternCount;
    intern *NewIntern = pushSize(&InternArena, sizeof(intern) + Length + 1, ArenaFlag_Align8 | ArenaFlag_ClearToZero);
    NewIntern->Length = Length;
    NewIntern->Next = Intern;
    memcpy(NewIntern->String, String, Length);
    NewIntern->String[Length] = 0;

    Interns[Slot] = NewIntern;

    return NewIntern->String;
}


typedef enum {
    Orientation_Horizontal,
    Orientation_Vertical,
} orientation;

typedef struct {
    char *Tags[100];
    u8 TagCount;
    orientation Orientation;
} picture;

picture Pics[100000];
u8   PicUsed[100000];
u64 PreviousPicIndex;
u64 NumPrinted;

static inline void printSingle(FILE *Stream, u64 Index) {
    ++NumPrinted;
    PreviousPicIndex = Index;
    PicUsed[Index] = 1;
    fprintf(Stream, "%ld\n", Index);
}

static inline s64 calculateScore(u64 Idx1, u64 Idx2) {
    u32 CommonTags = 0;
    u8 TagsCommon1[100] = {};
    u8 TagsCommon2[100] = {};
    for(u32 I = 0; I < Pics[Idx1].TagCount; ++I) {
        for(u32 J = 0; J < Pics[Idx2].TagCount && !TagsCommon2[J]; ++J) {
            if(Pics[Idx1].Tags[I] == Pics[Idx2].Tags[J]) {
                TagsCommon1[I] = 1;
                TagsCommon2[J] = 1;
                ++CommonTags;
                break;
            }
        }
    }

    u32 DiffTags1 = 0;
    for(u32 I = 0; I < Pics[Idx1].TagCount; ++I) {
        DiffTags1 += !TagsCommon1[I];
    }

    u32 DiffTags2 = 0;
    for(u32 J = 0; J < Pics[Idx2].TagCount; ++J) {
        DiffTags2 += !TagsCommon1[J];
    }

    return min(min(DiffTags1, DiffTags2), CommonTags);
}

int main(int ArgCount, char *ArgVals[]) {
    if(ArgCount < 2) {
        fprintf(stderr, "Usage: %s InFile [PrintToStdout]\n", ArgVals[0]);
        exit(1);
    }

    FILE *InFile = fopen(ArgVals[1], "r");
    char OutFileName[1024] = {};
    snprintf(OutFileName, arrayCount(OutFileName), "%s.out", ArgVals[1]);
    FILE *OutFile = ArgCount >= 3 ? stdout : fopen(OutFileName, "w");
    if(!InFile || !OutFile) {
        fprintf(stderr, "Could not open files\n");
        exit(1);
    }

    u64 NumberOfPics;
    fscanf(InFile, "%lu ", &NumberOfPics);

    for(u64 I = 0; I < NumberOfPics; ++I) {
        picture *Pic = Pics + I;
        char Orientation;
        fscanf(InFile, "%c %hhd ", &Orientation, &Pic->TagCount);
        Pic->Orientation = (Orientation == 'H') ? Orientation_Horizontal : Orientation_Vertical;

        for(u64 TagI = 0; TagI < Pic->TagCount; ++TagI) {
            char Tag[64];
            fscanf(InFile, "%64s ", Tag);
            Pic->Tags[TagI] = stringIntern(Tag);
        }
    }

#if 0
    printf("Unique tag count: %ld\n", UniqueInternCount);
    for(u64 I = 0; I < arrayCount(Interns); ++I) {
        for(intern *Iterator = Interns[I]; Iterator; Iterator = Iterator->Next) {
            printf("Tag %s repeated %d times\n", Iterator->String, Iterator->TimesRepeated);
        }
    }
#endif

    fprintf(OutFile, "%lu\n", NumberOfPics);
    printSingle(OutFile, 0);
    while(NumPrinted < NumberOfPics) {
        u64 BestNextIndex = 0;
        s64 BestScore = -1;
        s64 MaxScore = Pics[PreviousPicIndex].TagCount/2;
        for(u64 I = 0; I < NumberOfPics; ++I) {
            if(!PicUsed[I]) {
                s64 Score = calculateScore(PreviousPicIndex, I);
                if(Score > BestScore || (Score == BestScore && Pics[I].TagCount < Pics[BestNextIndex].TagCount)) {
                    BestNextIndex = I;
                    BestScore = Score;
                    if(Score == MaxScore && Pics[I].TagCount <= Pics[PreviousPicIndex].TagCount) {
                        break;
                    }
                }
            }
        }
        printSingle(OutFile, BestNextIndex);
    }

    return 0;
}
