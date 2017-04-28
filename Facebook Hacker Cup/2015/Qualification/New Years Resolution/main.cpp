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

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;
typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;
typedef float real32;
typedef double real64;

#define MAXN 20
int gp, gc, gf;
int p[MAXN], c[MAXN], f[MAXN];
int n;

bool go(int k, int currP, int currC, int currF) {
    if(k == n) return currP == gp && currC == gc && currF == gf;

    return go(k + 1, currP, currC, currF) ||
        go(k + 1, currP + p[k], currC + c[k], currF + f[k]);
}

int main()
{
    ifstream in("in");
    ofstream out("out");

    int T;
    in >> T;

    for(int caseNum = 1; caseNum <= T; ++caseNum)
    {
        clock_t start = clock();

        cout << "Case #" << caseNum << endl;
        out << "Case #" << caseNum << ": ";

        in >> gp >> gc >> gf >> n;

        for(int i = 0;
            i < n;
            ++i)
        {
            in >> p[i] >> c[i] >> f[i];
        }

#if 1
        uint32 bitmap = 1;
        bool possible = false;
        for(int i = 0;
            i < 1<<n;
            ++i)
        {
            int testP = 0, testC = 0, testF = 0;
            for(int j = 0;
                j < n;
                ++j)
            {
                if(bitmap & 1<<j)
                {
                    testP += p[j];
                    testC += c[j];
                    testF += f[j];
                }
            }

            possible = (testP == gp && testC == gc && testF == gf);
            if(possible) break;
            ++bitmap;
        }

        out << (possible ? "yes" : "no") << '\n';
#else
        out << (go(0, 0, 0, 0) ? "yes" : "no") << endl;
#endif
        cout << "Time: " << (clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << endl;
    }

    return 0;
}
