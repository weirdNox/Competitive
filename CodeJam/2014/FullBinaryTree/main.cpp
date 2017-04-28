#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

int main()
{
    std::ifstream in("in");
    std::ofstream out("out");

    int T;
    in >> T;

    for(int caseNum = 1; caseNum <= T; ++caseNum)
    {
        std::cout << "Case #" << caseNum << std::endl;
        out << "Case #" << caseNum << ": ";

        int n;
        std::map<int, int> connections;

        in >> n;
        for(int i = 0; i < n-1; ++i)
        {
            short first;
            in >> first;
            in >> connections[first];
        }

        for(int i = 1; i <= connections.size(); ++i)
        {
            for(int j = i+1; j <= connections.size(); ++j)
            {
                int dist = 0;
                int currentPoint = i;
                std::stack<std::pair<int, int>> branches; // other point, dist to point
                while(currentPoint != j)
                {
                    auto keyItr = connections.find(i);
                    auto valueItr = connections.begin();
                    for(; valueItr != connections.end(); ++valueItr)
                    {
                        if(valueItr->second == i)
                        {
                            break;
                        }
                    }

                    if(keyItr != connections.end() && valueItr != connections.end()) // branch
                    {
                        branches.push(std::make_pair(valueItr->first, 1));
                        currentPoint = keyItr->second;
                        ++dist;
                    }
                }
            }
        }

        out << "ANSWER HERE" << '\n';
    }

    return 0;
}


