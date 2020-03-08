#include <array>
#include <iostream>
#include <climits>
#include <numeric>  
#include <vector>
#include <memory>
#include <queue>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);  
    cin.tie(nullptr);
    int N,Q;
    cin>>N;
    int idol[N+1];
    int in_degree[N+1];
    int A[N+1];
    int D[N+1];
    int Destination[N+1];
    for (int i=1; i<N+1;i++) in_degree[i]=0;
    

    for (int i=1; i<N+1;i++){
        int temp;
        cin>>temp;
        idol[i]=temp;
        in_degree[temp]++;
    }
    cin>>Q;
    vector<int> v[Q];
    for (int i=0; i<Q;i++){
      int N_deleted;
      cin>>N_deleted;
      for (int j=0 ;j<N_deleted;j++){
        int temp;
        cin>>temp;
        v[i].push_back(temp);
      }
    }
    //cout<<in_degree[4];
    for (int i=1; i<N+1; i++){    
          int visit = 0;
          int temp = 0;
          int papa = i ;
          int character = i;
          // 檢查自我循環或in_degree==1
          if( character == idol[character] or in_degree[i]==1 ){
            A[i]=-1;
            D[i]=-1;
          }
          else {
            while (in_degree[idol[character]]==1 and visit<N){        
              visit++;
              temp++;
              character = idol[character];
              if (papa == idol[character] ){
                temp=-1;
                break;
              }
            }
            A[i] = temp;
            D[i] = idol[character];
            }
    }
    /*
    for (int i =1; i<N+1;i++){
      cout<<A[i]<<" ";
    } 
    cout<<endl;
    for (int i =1; i<N+1;i++){
      cout<<D[i]<<" ";
    }*/
  
    for(int i =0; i<N+1;i++){
          Destination[i] = 0;
      }
    


    int ch;
    vector<int> deleteQ;
    for(int i=0;i<Q;i++){
      int ans=0;

      while (v[i].size()!=0){
        ch=v[i].back();
        v[i].pop_back();
        if(A[ch]>=0){
          ans+=A[ch]+1;
          Destination[D[ch]]++;
          deleteQ.push_back(D[ch]);
          if (Destination[D[ch]] == in_degree[D[ch]]){
            v[i].push_back(D[ch]);
          }
        }

      }
      cout<<ans<<"\n";

      while(deleteQ.size()!=0){
        Destination[deleteQ.back()]=0;
        deleteQ.pop_back();
      }



    }
    return 0;
}
