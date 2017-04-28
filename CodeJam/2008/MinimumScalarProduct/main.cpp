#include <algorithm>
#include <array>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

int main()
{
    std::ifstream in("in");
    std::ofstream out("out");

    int T;
    in >> T;

    int n;
    for(int caseNum = 1; caseNum <= T; ++caseNum)
    {
        out << "Case #" << caseNum << ": ";

        in >> n;
        std::vector<int> vec1(n);
        std::vector<int> vec2(n);

        for(int i = 0; i < n; ++i)
        {
            in >> vec1[i];
        }
        for(int i = 0; i < n; ++i)
        {
            in >> vec2[i];
        }

        std::sort(vec1.begin(), vec1.end());
        std::sort(vec2.begin(), vec2.end(), std::greater<int>());

        long long sum = 0;
        for(size_t i = 0; i < vec1.size(); ++i)
        {
            sum += (long long)(vec1[i]) * vec2[i];
        }

        out << sum << '\n';
    }

    return 0;
}

