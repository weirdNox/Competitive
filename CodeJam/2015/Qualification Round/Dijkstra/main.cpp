#include <algorithm>
#include <cmath>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <unordered_map>
#include <vector>

const char getMult(const char &x, const char &y)
{
    if(x == 'i')
    {
        if(y == 'i') return 'm';
        if(y == 'j') return 'k';
        if(y == 'k') return 'b';
        if(y == 'a') return 'l';
        if(y == 'b') return 'c';
        if(y == 'c') return 'j';
        if(y == 'l') return 'i';
        if(y == 'm') return 'a';
    }

    if(x == 'j')
    {
        if(y == 'i') return 'c';
        if(y == 'j') return 'm';
        if(y == 'k') return 'i';
        if(y == 'a') return 'k';
        if(y == 'b') return 'l';
        if(y == 'c') return 'a';
        if(y == 'l') return 'j';
        if(y == 'm') return 'b';
    }

    if(x == 'k')
    {
        if(y == 'i') return 'j';
        if(y == 'j') return 'a';
        if(y == 'k') return 'm';
        if(y == 'a') return 'b';
        if(y == 'b') return 'i';
        if(y == 'c') return 'l';
        if(y == 'l') return 'k';
        if(y == 'm') return 'c';
    }

    if(x == 'a')
    {
        if(y == 'i') return 'l';
        if(y == 'j') return 'c';
        if(y == 'k') return 'j';
        if(y == 'a') return 'm';
        if(y == 'b') return 'k';
        if(y == 'c') return 'b';
        if(y == 'l') return 'a';
        if(y == 'm') return 'i';
    }

    if(x == 'b')
    {
        if(y == 'i') return 'k';
        if(y == 'j') return 'l';
        if(y == 'k') return 'a';
        if(y == 'a') return 'c';
        if(y == 'b') return 'm';
        if(y == 'c') return 'i';
        if(y == 'l') return 'b';
        if(y == 'm') return 'j';
    }

    if(x == 'c')
    {
        if(y == 'i') return 'b';
        if(y == 'j') return 'i';
        if(y == 'k') return 'l';
        if(y == 'a') return 'j';
        if(y == 'b') return 'a';
        if(y == 'c') return 'm';
        if(y == 'l') return 'c';
        if(y == 'm') return 'k';
    }

    if(x == 'l')
    {
        if(y == 'i') return 'i';
        if(y == 'j') return 'j';
        if(y == 'k') return 'k';
        if(y == 'a') return 'a';
        if(y == 'b') return 'b';
        if(y == 'c') return 'c';
        if(y == 'l') return 'l';
        if(y == 'm') return 'm';
    }

    if(x == 'm')
    {
        if(y == 'i') return 'a';
        if(y == 'j') return 'b';
        if(y == 'k') return 'c';
        if(y == 'a') return 'i';
        if(y == 'b') return 'j';
        if(y == 'c') return 'k';
        if(y == 'l') return 'm';
        if(y == 'm') return 'l';
    }
}

int main()
{
    auto initTime = std::chrono::steady_clock::now();
    std::ifstream in("in");
    std::ofstream out("out");

    int T = 0;
    in >> T;

    int l, x;
    std::string initialString;
    std::string string;
    for(int caseNum = 1; caseNum <= T; ++caseNum)
    {
        out << "Case #" << caseNum << ": ";

        in >> l >> x >> initialString;
        string = initialString;


        for(int i = 1; i < x; ++i)
        {
            string += initialString;
        }

        if(initialString.length() == 1)
        {
            out << "NO" << '\n';
        }

        else if(string.length() < 3)
        {
            out << "NO" << '\n';
        }

        else if(string.length() == 3)
        {
            if(string == "ijk") out << "YES" << '\n';
            else out << "NO" << '\n';
        }

        else
        {
            auto cstr = string.c_str();
            char first = cstr[0];
            char second;
            char third;
            for(int i = 0; i < string.length() - 2; ++i)
            {
                if(i > 0)
                {
                    first = getMult(first, cstr[i]);
                }
                if(first != 'i') continue;

                second = cstr[i+1];
                for(int j = i+1; j < string.length() - 1; ++j)
                {
                    if(j > i+1)
                    {
                        second = getMult(second, cstr[j]);
                    }
                    if(second != 'j') continue;

                    third = cstr[j+1];
                    for(int a = j+2; a < string.length(); ++a)
                    {
                        third = getMult(third, cstr[a]);
                    }
                    if(third != 'k') goto endBad;
                    else goto endGood;
                }
            }

endBad:
            out << "NO" << '\n';
            continue;

endGood:
            out << "YES" << '\n';
        }
    }

    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now()-initTime).count() << " microsecs" << std::endl;

    return 0;
}

