#include <fstream>
#include <iomanip>
#include <iostream>

int main()
{
    std::ifstream in("in");
    std::ofstream out("out");

    int T;
    in >> T;

    double c, f, x;
    for(int caseNum = 1; caseNum <= T; ++caseNum)
    {
        out << "Case #" << caseNum << ": ";

        in >> c >> f >> x;
        double prodPerSec = 2.;
        double answer = 0.;
        double timeSpent = 0.;
        while(!answer)
        {
            double newProd = prodPerSec + f;
            double timeToFarmAndGoal = c / prodPerSec + (x / newProd);
            double timeToGoal = x / prodPerSec;

            if(timeToGoal <= timeToFarmAndGoal) answer = timeToGoal + timeSpent;
            else
            {
                timeSpent += c / prodPerSec;
                prodPerSec = newProd;
            }
        }

        out << std::fixed << std::setprecision(7) << answer << std::endl;
    }

    return 0;
}

