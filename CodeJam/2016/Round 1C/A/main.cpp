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

        int p[30] = {};
        int n; in >> n;
        int total = 0;
        for(int i = 0; i < n; ++i)
        {
            in >> p[i];
            total += p[i];
        }

        int biggest[2] = {};
        int biggestP[2] = {-1, -1};
        for(int i = 0; i < n; ++i)
        {
            if(p[i] > biggest[0])
            {
                if(biggestP[0] != -1)
                {
                    biggest[1] = biggest[0];
                    biggestP[1] = biggestP[0];
                }
                biggest[0] = p[i];
                biggestP[0] = i;
            }
            else if(p[i] > biggest[1])
            {
                biggest[1] = p[i];
                biggestP[1] = i;
            }
        }

        while(total)
        {
            if(n == 2)
            {
                total -= 2;
                out << " " << string(1, 'A' + biggestP[0]) << string(1, 'A' + biggestP[1]);
            }
            else
            {
                if(p[biggestP[0]] != p[biggestP[1]])
                {
                    --total;
                    --p[biggestP[0]];
                    out << " " << string(1, 'A' + biggestP[0]);
                }
                else
                {
                    for(int i = 0; i < 30; ++i)
                    {
                        if(p[i] != 0 && i != biggestP[0] && i != biggestP[1])
                        {
                            --total;
                            --p[i];
                            if(p[i] == 0)
                            {
                                --n;
                            }
                            out << " " << string(1, 'A' + i);
                            break;
                        }
                    }
                }
            }
        }

        out << '\n';
    }

    return 0;
}
