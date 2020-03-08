#include <iostream>
#include <bits/stdc++.h> 
using namespace std; 
int ans = 0 ;
int mini(int a,int b){
    if(a<=b){
        return a;
    }
    else
    {
        return b;
    }
}
int maxi(int a,int b){
    if(a>=b){
        return a;
    }
    else
    {
        return b;
    }
}
void merge(int* array,int start,int mid, int end){

    int MAX[mid+2] ;
    int MIN[mid+2] ;
    int left_array=[mid-start];
    
    int left_array=[end-mid];

    MAX[mid+1] = array[mid+1] ;
    MIN[mid+1] = array[mid+1] ;
    int flag = 1;
    for(int i=mid+1; i<=end;i++){
            int right_edge = *(array+i);

        for (int j=mid;j>=start;j--){
            int total_member =  i-j+1;


            if (flag == 1){
                *(MAX+j)  = maxi(*(MAX+j+1),*(array+j));
                *(MIN+j)  = mini(*(MIN+j+1),*(array+j));
            }
            else {
                *(MAX+j)   = maxi(*(MAX+j),right_edge);
                *(MIN+j)  = mini(*(MIN+j),right_edge);
            }


            if (*(MAX+j)-*(MIN+j) == total_member-1){
                ans++;
                //printf("yes");
             }


        }
        flag = 0;
    }

}

int  goodsegment(int* array,int start, int end){

    if (start==end){
        ans++;
        return 0 ;
    }
    int mid = (start+end)/2;
    
    goodsegment(array,start,mid);
    goodsegment(array,mid+1,end);
    merge(array,start,mid,end);
    return 0;

}
int main(){
    std::ios_base::sync_with_stdio(false);  
    std::cin.tie(nullptr);
    int n,q;
    std::cin >> n;  

    int array[n];

    for(int i = 0; i < n; i++){   
        std::cin >> array[i];
    }

    goodsegment(array,0,n-1);

    std::cout<<ans;

    return 0;


}

/*
5  
1 2 3 4 5 
*/



