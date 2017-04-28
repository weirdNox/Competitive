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

        std::unordered_map<char, int> symbolsValue;
        uint64_t answer = 0;
        char line[100];
        int values[100];
        int lineSize;

        in >> line;

        for(int i = 0; i < 100; ++i)
        {
            if(line[i] == '\0')
            {
                lineSize = i;
                break;
            }

            if(symbolsValue.find(line[i]) == symbolsValue.end())
            {
                if(symbolsValue.size() == 0)
                {
                    symbolsValue[line[i]] = 1;
                }
                else if(symbolsValue.size() == 1)
                {
                    symbolsValue[line[i]] = 0;
                }
                else
                {
                    symbolsValue[line[i]] = (int)symbolsValue.size();
                }

                values[i] = symbolsValue[line[i]];
            }
            else
            {
                values[i] = symbolsValue[line[i]];
            }
        }

        int base = std::max((int)symbolsValue.size(), 2);
        for(int i = 0; i < lineSize; ++i)
        {
            answer *= base;
            answer += values[i];
        }

        out << answer << '\n';
    }

    return 0;
}


