#include <array>
#include <iostream>
#include <climits>
#include <numeric>  
int main() {
    std::ios_base::sync_with_stdio(false);  
    std::cin.tie(nullptr);
    int n,m,max_move;
    std::cin>>n;
    std::cin>>m;
    std::cin>>max_move;
    int dp[n][m];
    int notes[n];
    for (int i =0; i<n;i++){
      std::cin>>notes[i]; 
    }
    int pre;
    
    for(int i=0;i<n;i++){
        int temp[m];
        int tempB[m];
        for (int p=0; p<=m;p++) {
            temp[p] = INT_MAX;
            tempB[p] = INT_MAX;
        } 
        int note = notes[i];
        int MINB = INT_MAX;
        int cur_value=-1;
        int start=0,end=-1;
        int penalty = std::max(abs(pre-note)-max_move,0);
        for(int k=0;k<m;k++){
            if(i==0){
              dp[i][k] = 0;
            }
            else{
              if (cur_value == dp[i-1][k] and k!=m-1) {
                end  = std::min(k+max_move,m-1);
              }
              else{
                for (int a=start; a<=end; a++){
                     if (cur_value + penalty < temp[a]){
                        temp[a] = cur_value + penalty;
                     }
                }
                cur_value  = dp[i-1][k];
                start = std::max(k-max_move,0);
                end = std::min(k+max_move,m-1);
              }

              if (dp[i-1][k]+std::max(abs(k-note)-max_move,0) < MINB){
                  MINB = dp[i-1][k]+std::max(abs(k-note)-max_move,0);
              } 
            }
        }
  
        for (int b = std::max(pre-max_move,0); b<=std::min(pre+max_move,m-1);b++){
          tempB[b] = MINB;
        }
        if (i!=0){
          for (int j=0; j<m;j++ ){
              dp[i][j] = std::min(temp[j],tempB[j]);
          }
        }
    pre = notes[i];
    }

    int MIN = INT_MAX;
    for (int i =0;i<m;i++){
        if (dp[n-1][i]<MIN) MIN = dp[n-1][i];
    }    
      
    std::cout<<MIN;
    return 0;
}
