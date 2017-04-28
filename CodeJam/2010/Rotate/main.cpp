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

    short n, k;
    for(int caseNum = 1; caseNum <= T; ++caseNum)
    {
        std::cout << "Case #" << caseNum << std::endl;
        out << "Case #" << caseNum << ": ";

        in >> n >> k;

        std::vector<char> board(n*n);
        for(int i = 0; i < n*n; ++i)
        {
            in >> board[i];
        }

        for(int c = n-1; c >= 0; --c)
        {
            for(int r = n-1; r >= 0; --r)
            {
                if(board[r*n + c] == '.')
                {
                    for(int i = c-1; i >= 0; --i)
                    {
                        if(board[r*n + i] != '.')
                        {
                            std::swap(board[r*n + c], board[r*n + i]);
                            break;
                        }
                    }
                }
            }
        }

        for(int r = 0; r < n; ++r)
        {
            for(int c = 0; c < n; ++c)
            {
                std::cout << board[r*n + c];
            }
            std::cout << std::endl;
        }

        bool redWin = false;
        bool blueWin = false;
        for(int r = 0; r < n; ++r)
        {
            int currentStrike = 0;
            char currentColor = '.';
            for(int c = 0; c < n; ++c)
            {
                if(board[r*n + c] != '.')
                {
                    if(currentColor == board[r*n + c])
                    {
                        ++currentStrike;
                        if(currentStrike >= k)
                        {
                            if(currentColor == 'R') redWin = true;
                            else blueWin = true;
                        }
                    }
                    else
                    {
                        currentStrike = 1;
                        currentColor = board[r*n + c];
                    }
                }
                else
                {
                    currentColor = '.';
                }
            }
        }

        for(int c = 0; c < n; ++c)
        {
            int currentStrike = 0;
            char currentColor = '.';
            for(int r = 0; r < n; ++r)
            {
                if(board[r*n + c] != '.')
                {
                    if(currentColor == board[r*n + c])
                    {
                        ++currentStrike;
                        if(currentStrike >= k)
                        {
                            if(currentColor == 'R') redWin = true;
                            else blueWin = true;
                        }
                    }
                    else
                    {
                        currentStrike = 1;
                        currentColor = board[r*n + c];
                    }
                }
                else
                {
                    currentColor = '.';
                }
            }
        }

        for(int i = 0; i < n*2-1; ++i)
        {
            int r = std::min(i, n-1);
            int c = std::max(i-n+1, 0);
            int currentStrike = 0;
            char currentColor = '.';
            while(r > 0 && c < n)
            {
                if(board[r*n + c] != '.')
                {
                    if(currentColor == board[r*n + c])
                    {
                        ++currentStrike;
                        if(currentStrike >= k)
                        {
                            if(currentColor == 'R') redWin = true;
                            else blueWin = true;
                        }
                    }
                    else
                    {
                        currentStrike = 1;
                        currentColor = board[r*n + c];
                    }
                }
                else
                {
                    currentColor = '.';
                }

                --r;
                ++c;
            }
        }

        for(int i = n-1; i >= 1-n; --i)
        {
            int r = std::abs(std::min(i, 0));
            int c = std::max(i, 0);
            int currentStrike = 0;
            char currentColor = '.';
            while(r < n && c < n)
            {
                if(board[r*n + c] != '.')
                {
                    if(currentColor == board[r*n + c])
                    {
                        ++currentStrike;
                        if(currentStrike >= k)
                        {
                            if(currentColor == 'R') redWin = true;
                            else blueWin = true;
                        }
                    }
                    else
                    {
                        currentStrike = 1;
                        currentColor = board[r*n + c];
                    }
                }
                else
                {
                    currentColor = '.';
                }

                ++r;
                ++c;
            }
        }

        if(blueWin && redWin) out << "Both" << '\n';
        else if(blueWin) out << "Blue" << '\n';
        else if(redWin) out << "Red" << '\n';
        else out << "Neither" << '\n';
    }

    return 0;
}


