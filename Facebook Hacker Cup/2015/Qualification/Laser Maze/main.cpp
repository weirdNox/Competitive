#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;
typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef float r32;
typedef double r64;

#define minimum(a, b) ((a < b) ? (a) : (b))
#define maximum(a, b) ((a > b) ? (a) : (b))

int dRow[] = {0, -1, 0, 1};
int dCol[] = {1, 0, -1, 0};
char dTur[] = {'>', '^', '<', 'v'};

bool visited[100][100][4];
int M, N;
int sRow, sCol, gRow, gCol;
string maze[100];

bool inside(int row, int col) { return (row >= 0 && col >= 0 && row < M && col < N); }

struct State
{
    int row, col;
    int dist;
    int rot;

    bool hasLaser()
    {
        for(int i = 0; i < 4; ++i)
        {
            int testRow = row;
            int testCol = col;
            while(inside(testRow, testCol) && maze[testRow][testCol] == '.')
            {
                testRow += dRow[i];
                testCol += dCol[i];
            }
            if(!inside(testRow, testCol)) continue;
            if(maze[testRow][testCol] == dTur[(i+2+rot)%4])
            {
                return true;
            }
        }
        return false;
    }

    bool wasVisited() { return visited[row][col][rot]; }
    void setVisited() { visited[row][col][rot] = true; }
    bool isValid() { return inside(row, col) && maze[row][col] == '.' && !hasLaser(); }
};

int main()
{
    ifstream in("in");
    ofstream out("out");

    int T;
    in >> T;

    for(int caseNum = 1; caseNum <= T; ++caseNum)
    {
        cout << "Case #" << caseNum << endl;
        out << "Case #" << caseNum << ":";

        in >> M >> N;

        for(int i = 0; i < M; ++i)
        {
            in >> maze[i];
            for(int j = 0; j < N; ++j)
            {
                if(maze[i][j] == 'G')
                {
                    gRow = i; gCol = j; maze[i][j] = '.';
                }
                if(maze[i][j] == 'S')
                {
                    sRow = i; sCol = j; maze[i][j] = '.';
                }
            }
        }

        memset(visited, 0, sizeof(visited));
        State st = {sRow, sCol, 0, 0};
        queue<State> q;
        q.push(st);
        int dist = -1;
        while(!q.empty())
        {
            st = q.front();
            q.pop();

            if(st.wasVisited()) continue;
            if(st.row == gRow && st.col == gCol)
            {
                dist = st.dist;
                break;
            }
            st.setVisited();

            for(int i = 0; i < 4; ++i)
            {
                State newSt;
                newSt.row = st.row + dRow[i];
                newSt.col = st.col + dCol[i];
                newSt.dist = st.dist + 1;
                newSt.rot = (st.rot + 1) % 4;
                if(newSt.isValid())
                {
                    q.push(newSt);
                }
            }
        }

        if(dist == -1)
        {
            out << " impossible" << '\n';
        }
        else
        {
            out << " " << dist << '\n';
        }
    }

    return 0;
}
