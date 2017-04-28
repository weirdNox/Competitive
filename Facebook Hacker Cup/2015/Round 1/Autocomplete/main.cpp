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

#define AVAILABLE_NODES 1000050
int tries[AVAILABLE_NODES][26];
char s[1000001];

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

        int n;
        in >> n;
        u64 answer = 0;

        int nextAvailable = 1;
        for(int j = 0; j < n; ++j)
        {
            in >> s;
            int count = 0, t = 0;
            bool end = false;
            for(int i = 0; s[i]; ++i)
            {
                int c = s[i] - 'a';
                if(!end) ++count;
                if(!tries[t][c])
                {
                    tries[t][c] = nextAvailable++;
                    end = true;
                }

                t = tries[t][c];
            }
            answer += count;
        }

        cout << nextAvailable << endl;

        memset(tries, 0, sizeof(tries));

        out << " " << answer << '\n';
    }

    return 0;
}
