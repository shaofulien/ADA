#include <iostream>
#include <bits/stdc++.h> 
using namespace std; 
int ans = 0 ;
struct node 
{ 
   int minimum; 
   int maximum; 
}; 

int A[100000];
// A utility function to get the middle index from corner indexes. 
int getMid(int s, int e) {  return s + (e -s)/2;  } 
  
/*  A recursive function to get the minimum and maximum value in 
     a given range of A indexes. The following are parameters 
     for this function. 
  
    st    --> Pointer to segment tree 
    index --> Index of current node in the segment tree. Initially 
              0 is passed as root is always at index 0 
    ss & se  --> Starting and ending indexes of the segment 
                  represented  by current node, i.e., st[index] 
    qs & qe  --> Starting and ending indexes of query range */
struct node MaxMinUntill(struct node *st, int ss, int se, int qs, 
                         int qe, int index) 
{ 
    // If segment of this node is a part of given range, then return 
    //  the minimum and maximum node of the segment 
    struct node tmp,left,right; 
    if (qs <= ss && qe >= se) 
        return st[index]; 
  
    // If segment of this node is outside the given range 
    if (se < qs || ss > qe) 
    { 
       tmp.minimum = INT_MAX; 
       tmp.maximum = INT_MIN; 
       return tmp; 
     } 
  
    // If a part of this segment overlaps with the given range 
    int mid = getMid(ss, se); 
    left = MaxMinUntill(st, ss, mid, qs, qe, 2*index+1); 
    right = MaxMinUntill(st, mid+1, se, qs, qe, 2*index+2); 
    tmp.minimum = min(left.minimum, right.minimum); 
    tmp.maximum = max(left.maximum, right.maximum); 
    return tmp; 
} 
  
// Return minimum and maximum of elements in range from index 
// qs (quey start) to qe (query end).  It mainly uses 
// MaxMinUtill() 
struct node MaxMin(struct node *st, int n, int qs, int qe) 
{ 
    struct node tmp; 
  
    // Check for erroneous input values 
    if (qs < 0 || qe > n-1 || qs > qe) 
    { 
        printf("Invalid Input"); 
        tmp.minimum = INT_MIN; 
        tmp.minimum = INT_MAX; 
        return tmp; 
    } 
  
    return MaxMinUntill(st, 0, n-1, qs, qe, 0); 
} 
  
// A recursive function that constructs Segment Tree for A[ss..se]. 
// si is index of current node in segment tree st 
void constructSTUtil( int ss, int se, struct node *st, 
                     int si) 
{ 
    // If there is one element in A, store it in current node of 
    // segment tree and return 
    if (ss == se) 
    { 
        st[si].minimum = A[ss]; 
        st[si].maximum = A[ss]; 
        return ; 
    } 
  
    // If there are more than one elements, then recur for left and 
    // right subtrees and store the minimum and maximum of two values 
    // in this node 
    int mid = getMid(ss, se); 
    constructSTUtil(ss, mid, st, si*2+1); 
    constructSTUtil(mid+1, se, st, si*2+2); 
  
    st[si].minimum = min(st[si*2+1].minimum, st[si*2+2].minimum); 
    st[si].maximum = max(st[si*2+1].maximum, st[si*2+2].maximum); 
} 
  
/* Function to construct segment tree from given A. This function 
   allocates memory for segment tree and calls constructSTUtil() to 
   fill the allocated memory */
struct node *constructST(int n) 
{ 
    // Allocate memory for segment tree 
  
    // Height of segment tree 
    int x = (int)(ceil(log2(n))); 
  
    // Maximum size of segment tree 
    int max_size = 2*(int)pow(2, x) - 1; 
  
    struct node *st = new struct node[max_size]; 
  
    // Fill the allocated memory st 
    constructSTUtil(0, n-1, st, 0); 
  
    // Return the constructed segment tree 
    return st; 
} 


void merge( struct node *st ,int start,int mid, int end,int n){
 
    int required_number=1 ;
    int MAX = A[mid+1];
    int MIN = A[mid+1];
    for(int i=mid+1; i<=end;i++){

            //i += required_number-1;

        std::cout<<MAX<<"/"<<MIN<<"/"<<"\n";
        MAX = max(MAX,A[i]);
        MIN = min(MIN,A[i]);

        if ((MAX-MIN > i-start)){
            std::cout<<"Ccccccc"<<endl;
            continue;
        }
        for (int j=mid;j>=start;j--){

            int total_member =  i-j+1;
            struct node result =  MaxMin(st, n, j, i); 

            MAX = result.maximum;

            MIN = result.minimum;

            //std::cout<<MAX<<"/"<<MIN<<"/"<<total_member<<"\n";
            if (MAX-MIN == total_member-1){
                ans++;
             }
             else {
                required_number = MAX-MIN-total_member+1;
                //j -= required_number-1;
             }

            
        }
        //std::cout<<required_number;
    }

}

int  goodsegment(struct node *st,int start, int end,int n){

    if (start==end){
        ans++;
        return 0 ;
    }
    int mid = (start+end)/2;
    
    goodsegment( st,start,mid,n);
    goodsegment( st,mid+1,end,n);
    merge(st, start,mid,end,n);
    return 0;

}
int main(){
    std::ios_base::sync_with_stdio(false);  
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;  


    for(int i = 0; i < n; i++){   
        std::cin >> A[i];
    }
    struct node *st = constructST( n); 

    goodsegment(st, 0,n-1,n);

    std::cout<<ans;

    return 0;


}

/*
5  
1 2 3 4 5 
*/



