#include <iostream>
#include <vector>
using namespace std;

vector<char> target = {
    'W', '.', 'B',
    '.', '.', '.',
    'B', '.', 'W'
};

vector<vector<char>> visited;

bool same(vector<char> a, vector<char> b)
{
    return a == b;
}

bool dfs(vector<char>& board)
{
    if (board == target)
        return true;

    for (auto x : visited)
    {
        if (same(x, board))
            return false;
    }

    visited.push_back(board);

    int dx[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int dy[8] = {-1, 1, -2, 2, -2, 2, -1, 1};

    for (int i = 0; i < 9; i++)
    {
        if (board[i] == '.')
            continue;

        int x = i / 3;
        int y = i % 3;

        for (int k = 0; k < 8; k++)
        {
            int nx = x + dx[k];
            int ny = y + dy[k];

            if (nx < 0 || nx >= 3 || ny < 0 || ny >= 3)
                continue;

            int j = nx * 3 + ny;

            if (board[j] == '.')
            {
                swap(board[i], board[j]);

                if (dfs(board))
                    return true;

                swap(board[i], board[j]);
            }
        }
    }

    return false;
}

int main()
{
    vector<char> board = {
        'W', '.', 'W',
        '.', '.', '.',
        'B', '.', 'B'
    };

    if (dfs(board))
        cout << "可以到达目标状态" << endl;
    else
        cout << "无法到达目标状态" << endl;

    return 0;
}