#include <fstream>
#include <ios>
#include <vector>

int main()
{
    std::ifstream in("in");
    std::ofstream out("out");

    int T;
    in >> T;

    short n;
    for(int caseNum = 1; caseNum <= T; ++caseNum)
    {
        out << "Case #" << caseNum << ": ";

        in >> n;
        std::vector<int> a(n);
        std::vector<int> b(n);
        int sum = 0;
        for(size_t i = 0; i < a.size(); ++i)
        {
            in >> a[i] >> b[i];

            for(size_t j = 0; j < i; ++j)
            {
                sum += (a[i] > a[j]) != (b[i] > b[j]);
            }
        }

        out << sum << '\n';
    }
}


// Cool stuff but the above solution is better for this

//#include <algorithm>
//#include <fstream>
//#include <iomanip>
//#include <iostream>
//#include <vector>

//struct Point
//{
//    Point()
//    {}
//    Point(double x, double y) :
//        x(x),
//        y(y)
//    {}
//    double x = 0;
//    double y = 0;
//};

//int main()
//{
//    std::ifstream in("in");
//    std::ofstream out("out");

//    int T;
//    in >> T;

//    short n;
//    for(int caseNum = 1; caseNum <= T; ++caseNum)
//    {
//        out << "Case #" << caseNum << ": ";

//        in >> n;
//        int numberOfIntersect = 0;
//        std::vector<Point> pointsA(n);
//        std::vector<Point> pointsB(n);
//        for(short i = 0; i < n; ++i)
//        {
//            Point a, b;
//            b.x = 1;
//            in >> a.y;
//            in >> b.y;

//            pointsA[i] = a;
//            pointsB[i] = b;

//            for(size_t j = 0; j < i; ++j)
//            {
//                auto &c = pointsA[j];
//                auto &d = pointsB[j];

//                Point CmP(c.x - a.x, c.y - a.y);
//                Point r(b.x - a.x, b.y - a.y);
//                Point s(d.x - c.x, d.y - c.y);

//                double CmPxr = CmP.x * r.y - CmP.y * r.x;
//                double CmPxs = CmP.x * s.y - CmP.y * s.x;
//                double rxs = r.x * s.y - r.y * s.x;

//                if(CmPxr == 0.)
//                {
//                    continue;
//                }

//                if (rxs == 0.)
//                    continue; // Lines are parallel.

//                float rxsr = 1. / rxs;
//                float t = CmPxs * rxsr;
//                float u = CmPxr * rxsr;

//                if((t >= 0.) && (t <= 1.) && (u >= 0.) && (u <= 1.)) ++numberOfIntersect;
//            }
//        }

//        out << numberOfIntersect << '\n';
//    }

//    return 0;
//}

