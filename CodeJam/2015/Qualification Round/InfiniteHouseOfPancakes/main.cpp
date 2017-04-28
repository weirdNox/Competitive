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

        int d;
        in >> d;

        int max = 0;
        vector<int> plates;
        for(int i = 0;
            i < d;
            ++i)
        {
            int n;
            in >> n;
            plates.push_back(n);
            if(n > max)
            {
                max = n;
            }
        }

        int t = max;

        for(int timeAfterMoves = 1;
            timeAfterMoves < max;
            ++timeAfterMoves)
        {
            int totalMoves = 0;
            for(int p : plates)
            {
                totalMoves += (p-1)/timeAfterMoves;
            }
            t = min(t, totalMoves + timeAfterMoves);
        }

        out << t << '\n';
    }

    return 0;
}
