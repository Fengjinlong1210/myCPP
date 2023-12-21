// 岛屿数量
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution
{
public:
    vector<vector<char>> grid;
    int col;
    int row;
    int ret = 0;
    void bfs(int i, int j)
    {
        queue<pair<int, int>> q;
        q.push(make_pair(i, j));
        while (!q.empty())
        {
            int r = q.front().first;
            int c = q.front().second;
            q.pop();

                if (r + 1 < row && grid[r + 1][c] == '1')
                {
                    grid[r + 1][c] = '0';
                    q.emplace(r + 1, c);
                }
                if (r - 1 >= 0 && grid[r - 1][c] == '1')
                {
                    grid[r - 1][c] = '0';
                    q.emplace(r - 1, c);
                }
                if (c + 1 < col && grid[r][c + 1] == '1')
                {
                    grid[r][c + 1] = '0';
                    q.emplace(r, c + 1);
                }
                if (c - 1 >= 0 && grid[r][c- 1] == '1')
                {
                    grid[r][c - 1] = '0';
                    q.emplace(r, c - 1);
                }
            
        }
    }

    int numIslands(vector<vector<char>> &_grid)
    {
        grid = _grid;
        row = grid.size();
        col = grid[0].size();

        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                if(grid[i][j] == '1')
                {
                bfs(i, j);
                ret++;
                }
            }
        }
        return ret;
    }
};


class Solution {
public:
    vector<vector<char>> grid;
    int row;
    int col;
    int cnt = 0;

    void dfs(int i, int j)
    {
        if(grid[i][j] == '0') return;
        grid[i][j] = '0';
        if(i + 1 >= 0 && i + 1 < row && j >= 0 && j < col)
            dfs(i + 1, j);
        if(i - 1 >= 0 && i - 1 < row && j >= 0 && j < col)
            dfs(i - 1, j);
        if(i >= 0 && i < row && j + 1 >= 0 && j + 1 < col)
            dfs(i, j + 1);
        if(i >= 0 && i < row && j - 1 >= 0 && j - 1 < col)
            dfs(i, j - 1);
    }

    int numIslands(vector<vector<char>>& _grid) 
    {
        grid = _grid;
        row = _grid.size();
        col = _grid[0].size();
        for(int i = 0; i < row; ++i)
        {
            for(int j = 0; j < col; ++j)
            {
                if(grid[i][j] == '1')
                {
                    dfs(i, j);
                    cnt++;
                }
            }
        }
        return cnt;
    }
};