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

struct Leaf
{
    u64 number;
    u64 n;
};

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

        u64 goal; in >> goal;

        map<u64, bool> visited;
        queue<Leaf> q;
        q.push({1, 1});

        s64 answer = 0;
        while(!q.empty())
        {
            Leaf current = q.front();
            q.pop();

            if(visited.find(current.number) != visited.end())
            {
                continue;
            }
            else
            {
                visited[current.number] = true;
            }

            if(current.number == goal)
            {
                answer = current.n;
                break;
            }

            Leaf next;
            next.n = current.n + 1;
            next.number = current.number + 1;
            q.push(next);
            next.number = 0;
            while(current.number > 0)
            {
                next.number = next.number * 10 + (current.number % 10);
                current.number /= 10;
            }
            q.push(next);
        }

        out << " " << answer << '\n';
    }

    return 0;
}
