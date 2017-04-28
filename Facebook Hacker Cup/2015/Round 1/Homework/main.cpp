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

#define minimum(a, b) ((a < b) ? (a) : (b))
#define maximum(a, b) ((a > b) ? (a) : (b))

int primacity[10000001];

int main()
{
    ifstream in("in");
    ofstream out("out");

    int T;
    in >> T;

    memset(primacity, 0, sizeof(primacity));
    for(u64 i = 2; i <= 1e7; ++i)
    {
        if(primacity[i] == 0)
        {
            for(s64 j = i; j <= 1e7; j += i)
            {
                ++primacity[j];
            }
        }
    }

    for(int caseNum = 1; caseNum <= T; ++caseNum)
    {
        cout << "Case #" << caseNum << endl;
        out << "Case #" << caseNum << ":";

        s64 a, b, k;
        in >> a >> b >> k;
        int number = 0;
        for(s64 i = a; i <= b; ++i)
        {
            if(primacity[i] == k)
            {
                ++number;
            }
        }

        out << " " << number << '\n';
    }

    return 0;
}
