#include <iostream>
#include <bits/stdc++.h> 
using namespace std; 
int ans = 0 ;
int main(){
    std::ios_base::sync_with_stdio(false);  
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;  

    int array[n];
    int DP[n+2];//number of good permutaion ended in i
    int position[n+1]; // 

    for(int i = 0; i < n; i++){   
        std::cin >> array[i];
        position[array[i]] = i;
        DP[i]=1;
    }

    for (int i = 2 ; i <=n; i++){
        std::cout<<"end element:"<<i-1<<"    count:"<<DP[i-2]<<"\n";
  
        int cur_element = i;
        int cur_index = position[cur_element];

        int pre_element = cur_element-1;
        int pre_index = position[pre_element];
        int maxi,mini,total_number,max_index,min_index;
        int next_index;
        max_index = max(cur_index,pre_index);
        min_index = min(cur_index,pre_index);
    
      
        maxi = *std::max_element(array+min_index, array+max_index+1);
        mini = *std::min_element(array+min_index, array+max_index+1);
        total_number = max_index - min_index +1; 
        
        std::cout<<cur_element<<"/"<<maxi<<"/"<<mini<<"/"<<total_number<<"\n";
        if (maxi-mini == total_number-1 && cur_element>=maxi){
                std::cout<<"before:"<<DP[array[cur_index]-1]<<endl;
                DP[array[cur_index]-1] = DP[array[cur_index]-1] + DP[array[pre_index]-1]-abs(cur_index-pre_index)+1;
                std::cout<<"after:"<<DP[array[cur_index]-1]<<endl;
                
                if (mini==1){
                    continue;
                }
                next_index = position[mini-1];

             }

        else{
            if (array[pre_index]-1==0){

                std::cout<<"break form reaching 1"<<endl;
                continue;
            }

            next_index = position[array[pre_index]-1];
        }

        while(1){

            std::cout<<"pre_element"<<array[pre_index]<<endl;
            std::cout<<"next_element"<<array[next_index]<<endl;
            /*

            if ((next_index-pre_index)*(pre_index-cur_index)>=0)
            {   
                std::cout<<(next_index)<<endl;
                std::cout<<(pre_index)<<endl;
                std::cout<<(cur_index)<<endl;

                std::cout<<"break form in the same side"<<endl;
                break;
            }*/

            //pre_index = position[mini-1];
            //pre_element = array[pre_index];
            max_index = max(max_index,next_index);
            min_index = min(min_index,next_index);
            maxi = *std::max_element(array+min_index, array+max_index+1);
            mini = *std::min_element(array+min_index, array+max_index+1);
            
            total_number = max_index - min_index +1;            
           
            if (maxi>cur_element){

                std::cout<<"break form reaching all element"<<endl;
                break;
            }

            if (maxi-mini == total_number-1){
                std::cout<<"hey++"<<endl;
                DP[array[cur_index]-1]++;//+=DP[array[next_index]-1];
      
            }

            if ( total_number == cur_element  ){
                
                std::cout<<"break form total_number == cur_element  1"<<endl;
                break;
            }

            pre_index = next_index;

            if (array[pre_index]<=1  ){
                std::cout<<"break form reaching 1"<<endl;
                break;
            }      
            next_index = position[array[pre_index]-1];

        }
  std::cout<<"end element:"<<i<<"/    count:"<<DP[i-1]<<"\n";   
  }
    for (int i =1;i<=n;i++){
        ans+=DP[i-1];
    }
    std::cout<<ans;
    return 0;


}

/*
5  
1 2 3 4 5 
*/



