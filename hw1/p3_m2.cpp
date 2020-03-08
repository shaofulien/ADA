// O(n Log n) extra space and O(n Log n) preprocessing time 
#include<bits/stdc++.h> 
using namespace std; 
#define MM 100000

// lookup[i][j] is going to store index of minimum value in 
// arr[i..j]. Ideally lookup table size should not be fixed and 
// should be determined using n Log n. It is kept constant to 
// keep code simple. 
//short int lookup[2*MM][MM]; 
//short int * lookup = new short int[2*MM][MM];

int** lookup = new int*[2*MM];

int ans=0;

// Fills lookup array lookup[][] in bottom up manner. 
void preprocess(int arr[], int n) 
{ 
    // Initialize M for the intervals with length 1 
    for (int i = 0; i < n; i++) 
        lookup[i][0] = i; 

    // Compute values from smaller to bigger intervals 
    for (int j=1; (1<<j)<=n; j++) 
    { 
        // Compute minimum value for all intervals with size 2^j 
        for (int i=0; (i+(1<<j)-1) < n; i++) 
        { 
            // For arr[2][10], we compare arr[lookup[0][3]] and 
            // arr[lookup[3][3]] 
            if (arr[lookup[i][j-1]] < arr[lookup[i + (1<<(j-1))][j-1]]) 
                lookup[i][j] = lookup[i][j-1]; 
            else
                lookup[i][j] = lookup[i + (1 << (j-1))][j-1];    
        } 
    } 
} 

// Returns minimum of arr[L..R] 
int query(int arr[], int L, int R) 
{ 
    // For [2,10], j = 3 
    int j = (int)log2(R-L+1); 

    // For [2,10], we compare arr[lookup[0][3]] and 
    // arr[lookup[3][3]], 
    if (arr[lookup[L][j]] <= arr[lookup[R - (1<<j) + 1][j]]) 
        return arr[lookup[L][j]]; 

else return arr[lookup[R - (1<<j) + 1][j]]; 
} 


void preprocess_max(int arr[], int n) 
{ 
    // Initialize M for the intervals with length 1 
    for (int i = 0; i < n; i++) 
        lookup[i+MM][0] = i; 

    // Compute values from smaller to bigger intervals 
    for (int j=1; (1<<j)<=n; j++) 
    { 
        // Compute minimum value for all intervals with size 2^j 
        for (int i=0; (i+(1<<j)-1) < n; i++) 
        { 
            // For arr[2][10], we compare arr[lookup[0][3]] and 
            // arr[lookup[3][3]] 
            if (arr[lookup[i+MM][j-1]] > arr[lookup[i+MM + (1<<(j-1))][j-1]]) 
                lookup[i+MM][j] = lookup[i+MM][j-1]; 
            else
                lookup[i+MM][j] = lookup[i+MM + (1 << (j-1))][j-1];    
        } 
    } 
} 

// Returns minimum of arr[L..R] 
int query_max(int arr[], int L, int R) 
{ 
    // For [2,10], j = 3 
    int j = (int)log2(R-L+1); 

    // For [2,10], we compare arr[lookup[0][3]] and 
    // arr[lookup[3][3]], 
    if (arr[lookup[L+MM][j]] >= arr[lookup[R - (1<<j) + 1+MM][j]]) 
        return arr[lookup[L+MM][j]]; 

else return arr[lookup[R - (1<<j) + 1+MM][j]]; 
} 




void merge(int* array,int start,int mid, int end,int n){
 
    for(int i=mid+1; i<=end;i++){

            //std::cout<<"sdasd";

            int required_number = 1;
            int MAX,MIN;
        for (int j=mid;j>=start;j--){


            int total_member =  i-j+1; 
            MAX = query_max(array, j, i);
        
            //std::cout<<j;
            MIN = query(array, j, i);


            //std::cout<<MAX<<"/"<<MIN<<"/"<<total_member<<"\n";
            if (MAX-MIN == total_member-1){
                ans++;
                required_number = 1;
             }
             else {
                required_number = MAX-MIN-total_member+1;
                 j -= required_number-1;
             }

            
        }
    }

}

int goodsegment(int* array,int start, int end,int n){

    if (start==end){
        ans++;
        return 0 ;
    }
    int mid = (start+end)/2;
    
    goodsegment(array,start,mid,n);
    goodsegment(array,mid+1,end,n);
    merge(array,start,mid,end,n);
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
    for(int i = 0; i < 2*MM; ++i){
        lookup[i] = new int[MM];
    }
// Fills table lookup[n][Log n] 
    preprocess(array, n); 
    preprocess_max(array, n);
    goodsegment(array,0,n-1,n);

    std::cout<<ans;

    return 0;


}

/*
5  
1 2 3 4 5 
*/



