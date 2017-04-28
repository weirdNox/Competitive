#include <cmath>
#include <fstream>
#include <iostream>

int main()
{
    std::ifstream in("in");
    std::ofstream out("out");

    int t;
    in >> t;

    for(int caseNum = 1; caseNum <= t; ++caseNum)
    {
        out << "Case #" << caseNum << ":\n";

        short r, c, m;
        in >> r >> c >> m;

        int area = r * c;
        int clearTiles = area - m;

        if(clearTiles == 1)
        {
            for(short i = 0; i < r; ++i)
            {
                for(short j = 0; j < c; ++j)
                {
                    if(i == r - 1 && j == c - 1) out << 'c';
                    else out << '*';
                }
                out << '\n';
            }
        }

        else if((r == 1 || c == 1) && clearTiles >= 2)
        {
            for(short i = 0; i < r; ++i)
            {
                for(short j = 0; j < c; ++j)
                {
                    if(i == r - 1 && j == c - 1) out << 'c';
                    else if(m)
                    {
                        out << '*';
                        --m;
                    }
                    else out << '.';
                }
                out << '\n';
            }
        }

        else if(clearTiles >= 4 && clearTiles % 2 == 0)
        {
            int baseWidth = 2;
            int height = std::ceil(clearTiles / (float)baseWidth);
            int topWidth = clearTiles % baseWidth == 0 ? baseWidth : clearTiles % baseWidth;
            bool removeFromPenult = false;
            while(height > r)
            {
                ++baseWidth;
                height = std::ceil(clearTiles / (float)baseWidth);
                topWidth = clearTiles % baseWidth == 0 ? baseWidth : clearTiles % baseWidth;
            }
            if(topWidth == 1)
            {
                removeFromPenult = true;
            }

            for(short i = 0; i < r; ++i)
            {
                for(short j = 0; j < c; ++j)
                {
                    if(i == r - 1 && j == c - 1) out << 'c';
                    else
                    {
                        if(r - i == height)
                        {
                            if(removeFromPenult && j == c - 2) out << '.';
                            else if(j >= c - topWidth) out << '.';
                            else
                            {
                                out << '*';
                                --m;
                            }
                        }
                        else if(r - i < height)
                        {
                            if(removeFromPenult && r - i == height - 1 && j == c - baseWidth)
                            {
                                out << '*';
                                --m;
                            }
                            else if(j >= c - baseWidth) out << '.';
                            else
                            {
                                out << '*';
                                --m;
                            }
                        }
                        else
                        {
                            if(m)
                            {
                                out << '*';
                                --m;
                            }
                            else out << '.';
                        }
                    }
                }
                out << '\n';
            }
        }
        else if(clearTiles >= 9 && clearTiles % 2 != 0 && r >= 3 && c >= 3)
        {
            int baseWidth = 3;
            int height = std::ceil(clearTiles / (float)baseWidth);
            int topWidth = clearTiles % baseWidth == 0 ? baseWidth : clearTiles % baseWidth;
            bool removeFromPenult = false;
            while(height > r)
            {
                ++baseWidth;
                height = std::ceil(clearTiles / (float)baseWidth);
                topWidth = clearTiles % baseWidth == 0 ? baseWidth : clearTiles % baseWidth;
            }
            if(topWidth == 1)
            {
                removeFromPenult = true;
            }

            for(short i = 0; i < r; ++i)
            {
                for(short j = 0; j < c; ++j)
                {
                    if(i == r - 1 && j == c - 1) out << 'c';
                    else
                    {
                        if(r - i == height)
                        {
                            if(removeFromPenult && j == c - 2) out << '.';
                            else if(j >= c - topWidth) out << '.';
                            else
                            {
                                out << '*';
                                --m;
                            }
                        }
                        else if(r - i < height)
                        {
                            if(removeFromPenult && r - i == height - 1 && j == c - baseWidth)
                            {
                                out << '*';
                                --m;
                            }
                            else if(j >= c - baseWidth) out << '.';
                            else
                            {
                                out << '*';
                                --m;
                            }
                        }
                        else
                        {
                            if(m)
                            {
                                out << '*';
                                --m;
                            }
                            else out << '.';
                        }
                    }
                }
                out << '\n';
            }
        }
        else out << "Impossible\n";
    }

    return 0;
}
