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

int oneStar[1005];
int twoStar[1005];

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

        int n; in >> n;

        for(int i = 0; i < n; ++i)
        {
            in >> oneStar[i];
            in >> twoStar[i];
        }

        int answer = 0;
        int currentStars = 0;
        for(;;)
        {
            bool anything = false;
            int max = -1;
            int place = -1;
            for(int i = 0; i < n; ++i)
            {
                if(twoStar[i] != -1 && currentStars >= twoStar[i])
                {
                    anything = true;
                    twoStar[i] = -1;
                    if(oneStar[i] != -1)
                    {
                        oneStar[i] = -1;
                        currentStars += 2;
                    }
                    else currentStars += 1;
                    ++answer;
                }
                if(oneStar[i] != -1 && oneStar[i] <= currentStars && max < twoStar[i])
                {
                    max = twoStar[i];
                    place = i;
                }
            }
            if(anything) continue;

            if(place != -1)
            {
                oneStar[place] = -1;
                currentStars += 1;
                ++answer;
                continue;
            }

            break;
        }


        for(int i = 0; i < n; ++i)
        {
            if(twoStar[i] != -1)
            {
                answer = -1;
                break;
            }
        }

        if(answer == -1) out << " Too Bad\n";
        else out << " " << answer << '\n';
    }

    return 0;
}
