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

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

int main()
{
    std::ifstream in("in");
    std::ofstream out("out");

    int T;
    in >> T;

    int n, m;
    for(int caseNum = 1; caseNum <= T; ++caseNum)
    {
        std::cout << "Case #" << caseNum << std::endl;
        out << "Case #" << caseNum << ": ";

        in >> n >> m;
        std::vector<std::string> existing(n);
        std::vector<std::string> toCreate(m);
        for(int i = 0; i < n; ++i)
        {
            in >> existing[i];
        }
        for(int i = 0; i < m; ++i)
        {
            in >> toCreate[i];
        }

        int answer = 0;
        for(auto &path : toCreate)
        {
            std::vector<std::string> parts = split(path, '/');
            parts.erase(parts.begin());
            std::string tempPath;
            for(int i = 0; i < parts.size(); ++i)
            {
                tempPath += "/" + parts[i];
                if(std::find(existing.begin(), existing.end(), tempPath) == existing.end())
                {
                    answer += parts.size() - i;
                    existing.push_back(tempPath);
                    for(int j = i + 1; j < parts.size(); ++j)
                    {
                        tempPath += "/" + parts[j];
                        existing.push_back(tempPath);
                    }
                    break;
                }
            }
        }

        out << answer << '\n';
    }

    return 0;
}


