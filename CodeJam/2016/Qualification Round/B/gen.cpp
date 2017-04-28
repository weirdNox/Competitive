#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef float r32;
typedef double r64;

int main()
{
    ofstream out("test");

    out << 100 << '\n';
    for(int caseNum = 1; caseNum <= 100; ++caseNum)
    {
        int randNum = rand() % 100 + 1;
        for(int i = 0; i < randNum; ++i)
        {
            if(rand() % 2) out << "+";
            else out << "-";
        }
        out << '\n';
    }

    return 0;
}
