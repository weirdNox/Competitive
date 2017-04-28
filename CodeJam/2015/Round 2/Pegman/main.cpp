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
    char map[100*100];

    for(int caseNum = 1; caseNum <= T; ++caseNum)
    {
        std::cout << "Case #" << caseNum << std::endl;
        out << "Case #" << caseNum << ": ";

        int r, c;
        in >> r >> c;

        for(int i = 0; i < r*c; ++i)
        {
            in >> map[i];
        }

        int answer = 0;

        for(int y = 0; y < r; ++y)
        {
            for(int x = 0; x < c; ++x)
            {
                char symbol = map[y*c + x];
                if(symbol != '.')
                {
                    bool hasArrow = false;
                    int tries = 0;

                    while(!hasArrow && tries < 4)
                    {
                        switch(symbol)
                        {
                            case '>':
                            {
                                for(int testX = x+1; testX < c; ++testX)
                                {
                                    if(map[y*c + testX] != '.')
                                    {
                                        hasArrow = true;
                                        break;
                                    }
                                }
                            } break;

                            case '<':
                            {
                                for(int testX = x-1; testX >= 0; --testX)
                                {
                                    if(map[y*c + testX] != '.')
                                    {
                                        hasArrow = true;
                                        break;
                                    }
                                }
                            } break;

                            case '^':
                            {
                                for(int testY = y-1; testY >= 0; --testY)
                                {
                                    if(map[testY*c + x] != '.')
                                    {
                                        hasArrow = true;
                                        break;
                                    }
                                }
                            } break;

                            case 'v':
                            {
                                for(int testY = y+1; testY < r; ++testY)
                                {
                                    if(map[testY*c + x] != '.')
                                    {
                                        hasArrow = true;
                                        break;
                                    }
                                }
                            } break;

                            default:
                            {
                            } break;
                        }

                        if(!hasArrow)
                        {
                            switch(symbol)
                            {
                                case '>':
                                {
                                    map[y*c + x] = 'v';
                                } break;

                                case '<':
                                {
                                    map[y*c + x] = '>';
                                } break;

                                case '^':
                                {
                                    map[y*c + x] = '<';
                                } break;

                                case 'v':
                                {
                                    map[y*c + x] = '^';
                                } break;

                                default:
                                {
                                } break;
                            }
                            symbol = map[y*c + x];
                        }

                        ++tries;
                    }

                    if(!hasArrow)
                    {
                        answer = -1;
                        goto exit;
                    }

                    if(tries > 1)
                    {
                        ++answer;
                    }
                }
            }
        }

exit:
        if(answer >= 0)
        {
            out << answer << '\n';
        }
        else
        {
            out << "IMPOSSIBLE" << '\n';
        }
    }

    return 0;
}


