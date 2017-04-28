#include <algorithm>
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

    short n;
    for(int caseNum = 1; caseNum <= T; ++caseNum)
    {
        out << "Case #" << caseNum << ": ";

        in >> n;
        std::vector<double> naomiInitial(n);
        std::vector<double> kenInitial(n);
        for(short i = 0; i < n; ++i)
        {
            in >> naomiInitial[i];
        }
        for(short i = 0; i < n; ++i)
        {
            in >> kenInitial[i];
        }

        std::sort(naomiInitial.begin(), naomiInitial.end(), std::less<double>());
        std::sort(kenInitial.begin(), kenInitial.end(), std::less<double>());

        // Deceitful War
        auto naomi = naomiInitial;
        auto ken = kenInitial;
        for(auto kItr = ken.end() - 1; kItr >= ken.begin(); --kItr)
        {
            for(auto nItr = naomi.begin(); nItr != naomi.end(); ++nItr)
            {
                if(*nItr > *kItr)
                {
                    nItr = naomi.erase(nItr) - 1;
                    kItr = ken.erase(kItr);
                    break;
                }
            }
        }
        out << n - naomi.size() << ' ';

        // War
        naomi = naomiInitial;
        ken = kenInitial;
        for(auto nItr = naomi.begin(); nItr != naomi.end(); ++nItr)
        {
            for(auto kItr = ken.begin(); kItr != ken.end(); ++kItr)
            {
                if(*kItr > *nItr)
                {
                    nItr = naomi.erase(nItr) - 1;
                    kItr = ken.erase(kItr) - 1;
                    break;
                }
            }
        }

        out << naomi.size();


        out << '\n';
    }

    return 0;
}

