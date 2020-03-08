#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>
#include <vector>
#include "hex.h"

#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> pii;

const int maxn = 11;

bool board[maxn][maxn];

int n;
pii top, bottom;

void init(int _n) {
    n = _n;
    memset(board, 0, sizeof board);
    srand(12345);
}

pii decide(pii p) {
    // cout << "n =" << n << endl;
    cout << "top =" << top.first << " " << top.second << endl;
    cout << "bottom =" << bottom.first << " " << bottom.second << endl;

    pii res, tmp;
    int x = ceil((n - 1) / 2.0);
    int y = floor((n - 1) / 2.0);

    // first step
    if (p != make_pair(-1, -1)) {
        board[p.first][p.second] = 2;
    } else {
        board[x][y] = 1;
        // cout << "x =" << x << endl;
        // cout << "y =" << y << endl;
        top = make_pair(x, y);
        bottom = make_pair(x, y);
        return make_pair(x, y);
    }
    // while (n == 4) {
    //     cout << "n==4" << endl;
    //     if (board[0][2] == 2 and board[0][1] == 0) {
    //         board[0][1] = true;
    //         res = make_pair(0, 1);
    //         return res;
    //     }
    //     if (board[0][1] == 2 and board[0][2] == 0) {
    //         board[0][2] = true;
    //         res = make_pair(0, 2);
    //         return res;
    //     }
    //     break;
    // }
    

    if (top.first > 0) {
        if (board[top.first - 1][top.second] == true and board[top.first - 1][top.second + 1] == 0) {
            top.first--;
            top.second++;
            board[top.first][top.second] = true;
            res = top;
            return res;
        }
        if (board[top.first - 1][top.second + 1] == true and board[top.first - 1][top.second] == 0) {
            top.first--;
            board[top.first][top.second] = true;
            res = top;
            return res;
        }
    }
    if (bottom.first < n - 1) {
        if (board[bottom.first + 1][bottom.second] == true and board[bottom.first + 1][bottom.second - 1] == 0) {
            bottom.first++;
            bottom.second--;
            board[bottom.first][bottom.second] = true;
            res = bottom;
            return res;
        }
        if (board[bottom.first + 1][bottom.second - 1] == true and board[bottom.first + 1][bottom.second] == 0) {
            bottom.first++;
            board[bottom.first][bottom.second] = true;
            res = bottom;
            return res;
        }
    }

    // AI up

    if (p.first==0 and p.second==2 and board[1][0]==false){
        board[1][0] = true;
        return make_pair(1, 0);
    }
    if (p.first==1 and p.second==1 and board[2][0]==false and  board[1][0] == true and board[1][1]== true){
        board[2][0] = true;
        return make_pair(2, 0);
    }
    if (x - p.first >= 0 and top.first > 0 and top.second < n - 1) {
        tmp = top;
        top.first--;
        if (top.second - p.second >= 0) {
            top.second++;
        }  //else top.second no change

        if (!board[top.first][top.second]) {
            board[top.first][top.second] = true;
            res = top;
            return res;
        } else {
            top = tmp;
        }
    }

    // AI down
    if (x - p.first < 0 and bottom.first < n - 1 and bottom.second > 0) {
        tmp = bottom;
        bottom.first++;
        if (bottom.second - p.second <= 0) {
            bottom.second--;
        }  //else bottom.second no change

        if (!board[bottom.first][bottom.second]) {
            board[bottom.first][bottom.second] = true;
            res = bottom;
            return res;
        } else {
            bottom = tmp;
        }
    }

    vector<pii> unused;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!board[i][j])
                unused.push_back({i, j});
        }
    }

    res = unused[rand() % unused.size()];
    board[res.first][res.second] = true;
    return res;
}
