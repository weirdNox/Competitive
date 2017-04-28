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

u64 mod = 1000000007;

u64 add(u64 a, u64 b)
{
    u64 result = a + b;
    while(result > mod) result -= mod;
    return result;
}

u64 multiply(u64 a, u64 b)
{
    u64 result = a * b;
    while(result > mod) result -= mod;
    return result;
}

u64 memo[2001][2001];
u64 localGoal, externalGoal;

u64 stressFree(u64 local, u64 external)
{
    if(memo[local][external] != _UI64_MAX) return memo[local][external];

    u64 result;

    if(local > 0 && external >= local) result = 0;
    else if(external > local) result = 0;
    else if(local < localGoal && external == externalGoal) result = 1;
    else if(local == localGoal && external < externalGoal) result = 1;
    else if(local == localGoal && external == externalGoal) result = 1;
    else result = add(stressFree(local+1, external), stressFree(local, external+1));

    memo[local][external] = (s64)result;
    return result;
}

u64 stressful(u64 local, u64 external)
{
    if(memo[local][external] != _UI64_MAX) return memo[local][external];

    u64 result;

    if(local == localGoal && external == externalGoal) result = 1;
    else if(local < localGoal && external == externalGoal) result = 1;
    else if(local == localGoal && external < externalGoal) result = 0;
    else if(local > external) result = 0;
    else result = add(stressful(local+1, external), stressful(local, external+1));

    memo[local][external] = (s64)result;
    return result;
}

int main()
{
    ifstream in("in");
    ofstream out("out");

    int T;
    in >> T;

    for(int caseNum = 1; caseNum <= T; ++caseNum)
    {
        cout << "Case #" << caseNum << endl;
        out << "Case #" << caseNum << ":";

        char dash;
        in >> localGoal >> dash >> externalGoal;

        for(int i = 0; i < 2001; ++i)
        {
            for(int j = 0; j < 2001; ++j)
            {
                memo[i][j] = _UI64_MAX;
            }
        }
        u64 stressFreeRes = stressFree(0, 0);

        for(int i = 0; i < 2001; ++i)
        {
            for(int j = 0; j < 2001; ++j)
            {
                memo[i][j] = _UI64_MAX;
            }
        }
        u64 stressfulRes = stressful(0, 0);

        out << " " << stressFreeRes << " " << stressfulRes << '\n';
    }

    return 0;
}
