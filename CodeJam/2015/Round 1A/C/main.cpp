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

struct Point
{
    Point()
    {}
    Point(double x, double y) :
        x(x),
        y(y)
    {}

    bool operator==(const Point &rhs)
    {
        return x == rhs.x && y == rhs.y;
    }

    double x = 0;
    double y = 0;
};

int main()
{
    std::ifstream in("in");
    std::ofstream out("out");

    int T;
    in >> T;

    int n;
    for(int caseNum = 1; caseNum <= T; ++caseNum)
    {
        std::cout << "Case #" << caseNum << std::endl;
        out << "Case #" << caseNum << ":\n";

        in >> n;
        std::vector<Point> points(n);
        for(int i = 0; i < n; ++i)
        {
            double x, y;
            in >> x >> y;
            points[i] = Point(x, y);
        }

        for(auto &point : points)
        {
            std::vector<std::pair<int, double>> dists(n-1);

            for(int i = 0; i < n; ++i)
            {
                if(points[i] == point) continue;
                dists.push_back(std::make_pair(i, std::sqrt(std::pow(point.y - points[i].y, 2) + std::pow(point.x - points[i].x,2))));
            }
            std::sort(dists.begin(), dists.end(), [](const std::pair<int, double> &lhs, const std::pair<int, double> &rhs)
            {
                return lhs.second < rhs.second;
            });

            std::vector<std::pair<int, double>> angles;
            for(int i = 0; i < n; ++i)
            {
                if(points[i] == point) continue;
                for(int j = 0; j < dists.size(); ++j)
                {
                    if(i == dists[j].first)
                    {
                        angles.push_back(std::make_pair(i, std::atan2((point.y - points[j].y)/dists[j].second, (point.x - points[j].x)/dists[j].second) * 180 / 3.14159265359));
                        break;
                    }
                }
            }
            std::sort(angles.begin(), angles.end(), [](const std::pair<int, double> &lhs, const std::pair<int, double> &rhs)
            {
                return lhs.second < rhs.second;
            });

            std::cout << std::atan2(0,-10) * 180 / 3.14159265359 << std::endl;

            if(angles.back().second - angles.front().second <= 180)
            {
                out << 0 << '\n';
            }
            else
            {


                int numRemoved = 0;
                while(true)
                {

                    for(int i = 0; i < angles.size(); ++i)
                    {
                        if(angles[i].first == dists.front().first)
                        {
                            angles.erase(angles.begin()+i);
                        }
                    }

                    dists.erase(dists.begin());
                    ++numRemoved;

                    if(angles.back().second - angles.front().second <= 180)
                    {
                        out << numRemoved << '\n';
                        break;
                    }
                }
            }
        }
    }

    return 0;
}


