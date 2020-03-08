#include <iostream>
#include <vector>
#include <functional>
#include <cstdlib>
#include <cstring>
#include "hex.h"

using namespace std;
typedef pair<int, int> pii;

const int maxn = 11;

int board[maxn][maxn];
pii up,down;

int n;
void init(int _n) {
    n = _n;
    memset(board, 0, sizeof board);
    srand(12345);
    up.first=-100;
    up.second=-100;
    down.first=-100;
    down.second=-100;
}
pii decide(pii p) {

    cout<<"up:"<<up.first<<" "<<up.second<<endl;
    cout<<"down"<<down.first<<" "<<down.second<<endl;
    //label oponent's position

    
    if (p != make_pair(-1, -1)){
        board[p.first][p.second] = 2; 
    }
    else
    {   
        if (n%2==1)
        {   
            int mid = n/2;
            board[mid][mid] = 1;
            up = make_pair(mid,mid);
            down = make_pair(mid,mid);
            return make_pair(mid,mid);    
        }
        else
        {
            int mid = n/2;
            board[mid][mid-1] = 1;
            up = make_pair(mid,mid-1);
            down = make_pair(mid,mid-1);
            return make_pair(mid,mid-1);  

        }
    }
    pii select;
    if(up.first>0 and board[up.first-1][up.second]==2 and board[up.first-1][up.second+1] == 0){
        up.first = up.first-1;
        up.second = up.second+1;
        select = up;
        board[select.first][select.second] = 1;
        return select;
    }
    else if(up.first>0 and board[up.first-1][up.second+1]==2 and board[up.first-1][up.second] == 0){
        up.first = up.first-1;
        select = up;
        board[select.first][select.second] = 1;
        return select;

    }
    else if(down.first<n-1 and board[down.first+1][down.second]==2 and board[down.first+1][down.second-1]==0){
        down.first = down.first+1;
        down.second = down.second-1;
        select = down;
        board[select.first][select.second] = 1;
        return select;
    }
    else if(down.first<n-1 and board[down.first+1][down.second]==0 and board[down.first+1][down.second-1]==2){
        down.first = down.first+1;
        select = down;
        board[select.first][select.second] = 1;
        return select;

    }
    else if(p.first>n/2 and down.first<(n-1) and down.second>0){
        if(p.second >= down.second)
        {   if (board[down.first + 1][down.second -1]==0)
            {
                down.first = down.first + 1;
                down.second = down.second -1;
                select = down; 
                board[select.first][select.second] = 1;
                return select;
            }
            
        }
        else
        {   if(board[down.first + 1][down.second]==0)
            {
                down.first = down.first + 1;
                select = down;   
                board[select.first][select.second] = 1;
                return select; 
            }          
        }
    }
    else if(p.first<=n/2 and up.first>0 and up.second<(n-1))
    {
        if(p.second > up.second)
        {   if(board[up.first-1][up.second]==0)
            {
                up.first = up.first-1;
                select = up;   
                board[select.first][select.second] = 1;
                return select; 
            }

        }
        else
        {   /*
            up.first = up.first - 1; 
            if (up.second+1  == n-1){

            }
            else{
                up.second = up.second + 1;
            }
            select = up;*/
            if(board[up.first-1][up.second+1]==0)
            {   
                up.first = up.first-1;
                up.second = up.second+1;
                select = up;   
                board[select.first][select.second] = 1;
                return select; 

            }
        }
    }

    vector<pii> unused;


    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (!board[i][j])
                unused.push_back(make_pair(i, j));
        }
    }
    select = unused[rand() % unused.size()];
    board[select.first][select.second] = 1;


    return select;
}
