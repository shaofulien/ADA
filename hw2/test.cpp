#include <array>
#include <iostream>
#include <random>
#include <algorithm>
#include <time.h>
#include <climits>
#include <numeric>  
#include <string>
#include <bits/stdc++.h> 
#include <tuple>
#include <set>
using namespace std;

bool sortbyfirst(const tuple<float, int, int>& a,  
               const tuple<float, int, int>& b) 
{ 
    return (get<0>(a) < get<0>(b)); 
}  

int power(const vector<tuple<float, int, int>> vector) 
{   
    int sum = 0;
    int length = vector.size();
    int b=0,sum_a=0;
    for (int i=0 ; i<length-1;i++){
        b = get<2>(vector[i]);
        for (int j=i+1;j<length;j++){
            sum_a+=get<1>(vector[j]);
        }
        sum += b*sum_a;
        sum_a = 0;
    }
    return sum; 
} 

int recur_power(int k, vector<tuple<float, int, int>> v, int index)
{       if (index>=0){
            v.erase(v.begin()+index);
        }
      
        if (k==0){
            return power(v);
        }
        int res,temp;
        res = INT_MIN;
    
        for (int j = 0 ;j<v.size() ;j++){
                        
        
            temp = recur_power(k-1,v,j);
            if (temp>res){
                res = temp;
                }
                
            
        }
        //cout<<com<<"/"<<res<<endl;
        //dp[com] = res;            

       
        return  res;
}


int predict(vector<tuple<float, int, int>> v,int N,int K){
    
    int max_b = 100*N;
    int dp[2][K+1][max_b];
    for (int i=0;i<2;i++){
        for(int j=0;j<=K;j++){
            for (int b=0;b<max_b;b++){
                dp[i][j][b]=-1;
            }
        }
    }
    
    dp[0][1][get<2>(v[0])]=0;
     
    
    int pre,now;
    for (int i=1;i<N;i++){  
        if (i%2==1){
             now = 1;
             pre = 0;
        }
        else{
             now = 0;
             pre = 1;
        }      
        for (int j=0;j<=i;j++){
            dp[now][1][get<2>(v[j])]=0;
        } 
        for(int k=2;k<=K;k++){
            if(i<k-1) continue;
            for(int b=0;b<max_b;b++){
                //i is not chosen
                int not_chosen = dp[pre][k][b];
                int chosen =-1;
                //i is chosen
                if (b-get<2>(v[i])>=0){
                    if (dp[pre][k-1][b-get<2>(v[i])]!=-1){
                        chosen = dp[pre][k-1][b-get<2>(v[i])]+(b-get<2>(v[i]))*get<1>(v[i]);
                        
                             }
                }
                if (not_chosen>=chosen){
                    dp[now][k][b] = not_chosen;

                }
                else{
                    dp[now][k][b] = chosen;

                }
                if (i==1 and k==2){
                 //cout<<"b:"<<b<<" selfb:"<<get<2>(v[i])<<"chosen:"<<chosen<<"not chosen:"<<not_chosen<<"values:"<<dp[i][2][b]<<endl;
              
                }
                if(k==3 and i==3){
                    //cout<<"b:"<<b<<" selfb:"<<get<2>(v[i])<<"chosen:"<<chosen<<"not chosen:"<<not_chosen<<"values:"<<dp[i][k][b]<<endl;
              
                }

            }
            //cout<<dp[i][i]<<endl;
        }   
    }   
    int last_row = (N-1)%2;
    int ans=INT_MIN;
    for (int i=0;i<max_b;i++){
        if(dp[last_row][K][i]>ans) ans=dp[last_row][K][i];
    }

    return ans;
    //return 0;
 
}


void print_vector( vector<tuple<float, int, int>> v){
	for (int i =0 ; i<v.size();i++){
		cout<<get<1>(v[i])<<" ";
	}
	cout<<endl;
	for (int i =0 ; i<v.size();i++){
		cout<<get<2>(v[i])<<" ";
	}
}
int main() {
    ios_base::sync_with_stdio(false);  
    cin.tie(nullptr);

    int N=10,K=5;
    srand( time(NULL) );
    int flag =1;
     while(flag){

 		
    vector<tuple<float, int, int>> v; 
    vector<tuple<float, int, int>> v2; 
    for (int i =0; i<N;i++){    
      int A,B;
      float ratio;
      A=rand()%5;
      B=rand()%5;
      //cin>>A;
      //cin>>B;
      if (B==0){
        ratio =  std::numeric_limits<float>::infinity();
      }
      else{
        ratio = A/(float)B;
      } 
      v.push_back(make_tuple(ratio,A,B));
      v2.push_back(make_tuple(ratio,A,B));
    }
    sort(v.begin(), v.end(), sortbyfirst);
    sort(v2.begin(), v2.end(), sortbyfirst);

    if (K==1 or N==1){
        std::cout<<0;
        return 0;
    }

        print_vector(v);
 		if (predict(v,N,K)!=recur_power(N-K, v,-1)){
 			flag=0;
 			cout<<"A:"<<recur_power(N-K, v,-1)<<"P:"<<predict(v,N,K)<<endl;
 			
 		}else{
 			cout<<"A:"<<recur_power(N-K, v,-1)<<"P:"<<predict(v,N,K)<<endl;
 		}


 	}
    //}
    return 0;
}
