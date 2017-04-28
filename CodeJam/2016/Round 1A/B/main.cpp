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
    ifstream in("in");
    ofstream out("out");

    int T;
    in >> T;

    for(int caseNum = 1; caseNum <= T; ++caseNum)
    {
        cout << "Case #" << caseNum << endl;
        out << "Case #" << caseNum << ":";

        int n; in >> n;
        vector<vector<int>> input;
        for(int i = 0; i < 2*n-1; ++i)
        {
            input.emplace_back();
            for(int j = 0; j < n; ++j)
            {
                int a; in >> a;
                input.back().push_back(a);
            }
        }
        sort(input.begin(), input.end(),
             [](vector<int>& a, vector<int>& b)
             {
                 return a[0] < b[0];
             });


        vector<vector<int>> people;
        people.push_back(input
    }

    return 0;
}

// int main()
// {
//     ifstream in("in");
//     ofstream out("out");

//     int T;
//     in >> T;

//     for(int caseNum = 1; caseNum <= T; ++caseNum)
//     {
//         cout << "Case #" << caseNum << endl;
//         out << "Case #" << caseNum << ":";

//         int n; in >> n;
//         in.ignore();
//         vector<string> lists;
//         for(int i = 0; i < 2*n-1; ++i)
//         {
//             string newS; getline(in, newS);
//             lists.push_back(newS);
//         }
//         sort(lists.begin(), lists.end());

//         map<int, string> rows, columns;
//         rows[0] = lists[0];
//         lists.erase(lists.begin());

//         int missingRow = -1;
//         int missingColumn = -1;

//         string first = rows[0];
//         for(int i = 0; i < n; ++i)
//         {
//             char find = first[i*2];
//             bool found = false;
//             for(int j = 0; j < lists.size(); ++j)
//             {
//                 if(lists[j][0] == find)
//                 {
//                     found = true;
//                     columns[i] = lists[j];
//                     lists.erase(lists.begin() + j);
//                     break;
//                 }
//             }
//             if(!found) missingColumn = i;
//         }

//         int searchN = 0;
//         if(missingColumn != 0)
//         {
//             first = columns[0];
//         }
//         else
//         {
//             first = columns[1];
//             searchN = 2;
//         }
//         for(int i = 0; i < n; ++i)
//         {
//             char find = first[i*2];
//             bool found = false;
//             for(int j = 0; j < lists.size(); ++j)
//             {
//                 if(lists[j][searchN] == find)
//                 {
//                     found = true;
//                     rows[i] = lists[j];
//                     lists.erase(lists.begin() + j);
//                     break;
//                 }
//             }
//             if(!found) missingRow = i;
//         }

//         string answer;
//         if(missingColumn != -1)
//         {
//             cout << "col" << endl;
//             for(int i = 0; i < n; ++i)
//             {
//                 answer += string(1, ' ') + string(1, rows[i][2*missingColumn]);
//             }
//         }
//         else
//         {
//             for(int i = 0; i < n; ++i)
//             {
//                 answer += string(1, ' ') + string(1, columns[i][2*missingRow]);
//             }
//         }

//         out << answer << '\n';
//     }

//     return 0;
// }
