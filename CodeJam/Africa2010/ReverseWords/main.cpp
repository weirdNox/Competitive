#include <algorithm>
#include <array>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

int main()
{
    std::ifstream in("in");
    std::ofstream out("out");

    int T;
    in >> T;

    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for(int caseNum = 1; caseNum <= T; ++caseNum)
    {
        out << "Case #" << caseNum << ": ";

        std::string line;
        std::getline(in, line);

        std::vector<std::string> words;
        std::string word;
        std::stringstream stream(line);
        while(std::getline(stream, word, ' '))
        {
            words.push_back(word);
        }

        if(words.size())
        {
            auto itr = (words.end() - 1);
            for(; itr > words.begin(); --itr)
            {
                out << *itr << ' ';
            }
            out << *itr;
        }

        out << '\n';
    }

    return 0;
}

