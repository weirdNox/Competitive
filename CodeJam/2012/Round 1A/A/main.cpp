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

    int judges[300];

    for(int caseNum = 1; caseNum <= T; ++caseNum)
    {
        cout << "Case #" << caseNum << endl;
        out << "Case #" << caseNum << ": ";

        int n;
        in >> n;

        long sum = 0;
        for(int i = 0;
            i < n;
            ++i)
        {
            in >> judges[i];
            sum += judges[i];
        }

        for(int i = 0;
            i < n;
            ++i)
        {
            double min = 0;
            double max = 1;
            double audienceFrac = 0;
            while(max-min > 1e-9)
            {
                audienceFrac = (min+max)*0.5;
                double score = judges[i] + sum*audienceFrac;
                double used = audienceFrac;

                for(int j = 0;
                    j < n;
                    ++j)
                {
                    if(i == j) continue;

                    if(score > judges[j]) used += (score - judges[j])/sum;
                }

                if(used > 1) max = audienceFrac;
                else if(used < 1) min = audienceFrac;
                else break;
            }

            out << audienceFrac*100 << " ";
        }

        out << "\n";
    }

    return 0;
}


/* #include <algorithm> */
/* #include <cctype> */
/* #include <cmath> */
/* #include <cstdio> */
/* #include <cstdlib> */
/* #include <fstream> */
/* #include <iostream> */
/* #include <map> */
/* #include <queue> */
/* #include <set> */
/* #include <sstream> */
/* #include <stack> */
/* #include <string> */
/* #include <unordered_map> */
/* #include <utility> */
/* #include <vector> */
/* using namespace std; */

/* int main() */
/* { */
/*     ifstream in("in"); */
/*     ofstream out("out"); */

/*     int T; */
/*     in >> T; */

/*     int judges[300]; */

/*     for(int caseNum = 1; caseNum <= T; ++caseNum) */
/*     { */
/*         cout << "Case #" << caseNum << endl; */
/*         out << "Case #" << caseNum << ": "; */

/*         int n; */
/*         in >> n; */

/*         long sum = 0; */
/*         for(int i = 0; */
/*             i < n; */
/*             ++i) */
/*         { */
/*             in >> judges[i]; */
/*             sum += judges[i]; */
/*         } */

/*         double min = 0; */
/*         double max = 20100; */
/*         double safeScore = 0; */
/*         double percentages[300]; */
/*         while(max-min > 1e-9) */
/*         { */
/*             safeScore = (min + max)/2; */

/*             double testSum = 0; */
/*             for(int j = 0; */
/*                 j < n; */
/*                 ++j) */
/*             { */
/*                 percentages[j] = (double)(safeScore - judges[j]) / sum; */
/*                 if(percentages[j] < 0) percentages[j] = 0; */
/*                 testSum += percentages[j]; */
/*             } */

/*             if(testSum > 1) max = safeScore; */
/*             else if(testSum < 1) min = safeScore; */
/*             else break; */
/*         } */

/*         cout << safeScore; */

/*         for(int i = 0; */
/*             i < n; */
/*             ++i) */
/*         { */
/*             out << percentages[i]*100 << " "; */
/*         } */

/*         out << "\n"; */
/*     } */

/*     return 0; */
/* } */

