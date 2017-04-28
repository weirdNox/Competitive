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

std::vector<std::string> getFlips(const std::string &device, const std::vector<std::string> &outlets)
{
    std::vector<std::string> ret;

    for(auto &outlet : outlets)
    {
        std::string flips;
        for(int i = 0; i < device.length(); ++i)
        {
            if(device[i] == outlet[i]) flips += '0';
            else flips += '1';
        }
        ret.push_back(flips);
    }

    return ret;
}

int main()
{
    //    auto time = std::chrono::steady_clock::now();

    std::ifstream in("in");
    std::ofstream out("out");

    int T;
    in >> T;

    int n, l;
    for(int caseNum = 1; caseNum <= T; ++caseNum)
    {
        std::cout << "Case #" << caseNum << std::endl;
        out << "Case #" << caseNum << ": ";

        in >> n >> l;

        std::vector<std::string> outlets(n);
        std::vector<std::string> devices(n);
        for(short i = 0; i < n; ++i)
        {
            in >> outlets[i];
        }
        for(short i = 0; i < n; ++i)
        {
            in >> devices[i];
        }

        std::vector<std::vector<std::string>> allFlips;
        for(auto &device : devices)
        {
            auto flips = getFlips(device, outlets);
            std::sort(flips.begin(), flips.end());
            allFlips.push_back(flips);
        }

        std::vector<std::string> intersect = allFlips[0];
        for(size_t i = 1; i < allFlips.size(); ++i)
        {
            std::vector<std::string> temp;
            std::set_intersection(intersect.begin(), intersect.end(), allFlips[i].begin(), allFlips[i].end(), std::back_inserter(temp));
            intersect = temp;
        }

        int answer = std::numeric_limits<int>::max();

        for(auto &flip : intersect)
        {
            answer = std::min(answer, std::count(flip.begin(), flip.end(), '1'));
        }

        if(intersect.size()) out << answer << '\n';
        else out << "NOT POSSIBLE" << '\n';
    }

    //    std::cout << "Execution time: " << std::chrono::duration_cast<std::chrono::milliseconds>
    //                 (std::chrono::steady_clock::now() - time).count() / 1000.f << " seconds" << std::endl;

    return 0;
}


