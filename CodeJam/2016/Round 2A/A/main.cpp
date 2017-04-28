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


    unordered_map<int, string> numbers;
    numbers[0] = "ZERO";
    numbers[1] = "ONE";
    numbers[2] = "TWO";
    numbers[3] = "THREE";
    numbers[4] = "FOUR";
    numbers[5] = "FIVE";
    numbers[6] = "SIX";
    numbers[7] = "SEVEN";
    numbers[8] = "EIGHT";
    numbers[9] = "NINE";

    for(int caseNum = 1; caseNum <= T; ++caseNum)
    {
        cout << "Case #" << caseNum << endl;
        out << "Case #" << caseNum << ":";

        string s; in >> s;

        vector<int> phone;

        for(int i = 0; i < 10; ++i)
        {
            cout << i << endl;
            string test = numbers[i];
            bool exists = true;
            vector<u64> used;
            for(int j = 0; j < test.length(); ++j)
            {
                u64 testIndex = 0;
                bool done = false;
                while(!done)
                {
                    testIndex = s.find(test[j], testIndex);
                    if(testIndex == string::npos)
                    {
                        exists = false;
                        break;
                    }
                    auto found = find(used.begin(), used.end(), testIndex);
                    if(found == used.end())
                        done = true;
                    else
                        testIndex += 1;
                }
                used.push_back(testIndex);
                if(used.back() == string::npos)
                {
                    exists = false;
                    break;
                }
            }

            if(exists)
            {
                phone.push_back(i);
                --i;
                for(int j = 0; j < test.length(); ++j)
                {
                    u64 testIndex = s.find(test[j]);
                    s.erase(testIndex, 1);
                }
            }
        }

        sort(phone.begin(), phone.end());

        out << " ";
        for(auto &i : phone)
        {
            cout << i;
            out << i;
        }

        out << '\n';
    }

    return 0;
}
