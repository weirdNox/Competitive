#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
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

string getStr(string in, bool max)
{
    for(int i = 0; i < in.length() - 1; ++i)
    {
        int bestIndex = i;
        for(int j = in.length() - 1; j > i; --j)
        {
            if(i == 0 && in[j] == '0') continue;

            if(!max && in[j] < in[bestIndex] ||
               max && in[j] > in[bestIndex])
            {
                bestIndex = j;
            }
        }

        if(bestIndex != i)
        {
            swap(in[i], in[bestIndex]);
            break;
        }
    }

    return in;
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
        out << "Case #" << caseNum << ": ";

        string n;
        in >> n;

        out << getStr(n, false) << " " << getStr(n, true) << '\n';
    }

    return 0;
}
