#include <iostream>
#include <bits/stdc++.h> 
using namespace std; 
  
#define inf 0x3f3f  
struct Node { 
    long long maxPrefixSum; 
    long long maxSuffixSum; 
    long long totalSum; 
    long long maxSubarraySum; 
   
    Node() 
    { 
        maxPrefixSum = maxSuffixSum = maxSubarraySum = -inf; 
        totalSum = -inf; 
    } 
}; 
   
// Returns Parent Node after merging its left and right child 
Node merge(Node leftChild, Node rightChild) 
{ 
    Node parentNode; 
    parentNode.maxPrefixSum = max(leftChild.maxPrefixSum, 
                                  leftChild.totalSum +  
                                  rightChild.maxPrefixSum); 
   
    parentNode.maxSuffixSum = max(rightChild.maxSuffixSum, 
                                  rightChild.totalSum + 
                                  leftChild.maxSuffixSum); 
   
    parentNode.totalSum = leftChild.totalSum + 
                          rightChild.totalSum; 
   
    parentNode.maxSubarraySum = max(leftChild.maxSubarraySum, 
                                    max(rightChild.maxSubarraySum,
                                        leftChild.maxSuffixSum +rightChild.maxPrefixSum)); 
   
    return parentNode; 
} 
   
// Builds the Segment tree recursively 
void constructTreeUtil(Node* tree, int arr[], int start, 
                                    int end, int index) 
{ 
   
    /* Leaf Node */
    if (start == end) { 
   
        // single element is covered under this range 
        tree[index].totalSum = arr[start]; 
        tree[index].maxSuffixSum = arr[start]; 
        tree[index].maxPrefixSum = arr[start]; 
        tree[index].maxSubarraySum = arr[start]; 
        return; 
    } 
   
    // Recursively Build left and right children 
    int mid = (start + end) / 2; 
    constructTreeUtil(tree, arr, start, mid, 2 * index); 
    constructTreeUtil(tree, arr, mid + 1, end, 2 * index + 1); 
   
    // Merge left and right child into the Parent Node 
    tree[index] = merge(tree[2 * index], tree[2 * index + 1]); 
} 
   
Node* constructTree(int arr[], int n) 
{ 
    // Allocate memory for segment tree 
    int x = (int)(ceil(log2(n))); // Height of the tree 
   
    // Maximum size of segment tree  
    int max_size = 2 * (int)pow(2, x) - 1;  
    Node* tree = new Node[max_size]; 
   
    // Fill the allocated memory tree 
    constructTreeUtil(tree, arr, 0, n - 1, 1); 
   
    // Return the constructed segment tree 
    return tree; 
} 
void update(Node* tree, int arr[], int index, int low, int high,  
            int idx, int value) 
{ 
    // the node to be updated 
    if (low == high) { 
        tree[index].totalSum = value; 
        tree[index].maxPrefixSum = value; 
        tree[index].maxSuffixSum = value; 
        tree[index].maxSubarraySum = value; 
    } 
    else { 
  
        int mid = (low + high) / 2; 
  
        // if node to be updated is in left subtree 
        if (idx <= mid) 
            update(tree,arr, 2 * index , low, mid, idx, value); 
          
        else
            update(tree,arr, 2 * index + 1, mid + 1,  
                   high, idx, value); 
  

        tree[index].totalSum = tree[2 * index ].totalSum +  
                          tree[2 * index + 1].totalSum; 
  

        tree[index].maxPrefixSum =  
                    max(tree[2 * index ].maxPrefixSum, 
                    tree[2 * index ].totalSum +  
                    tree[2 * index + 1].maxPrefixSum); 

        tree[index].maxSuffixSum =  
                    max(tree[2 * index + 1].maxSuffixSum, 
                    tree[2 * index + 1].totalSum +  
                    tree[2 * index ].maxSuffixSum); 

        tree[index].maxSubarraySum =  
                    max(tree[index].maxPrefixSum, 
                    max(tree[index].maxSuffixSum, 
                    max(tree[2 * index ].maxSubarraySum, 
                    max(tree[2 * index + 1].maxSubarraySum, 
                    tree[2 * index ].maxSuffixSum +  
                    tree[2 * index + 1].maxPrefixSum)))); 
    } 
} 


Node queryUtil(Node* tree, int ss, int se, int qs, 
                               int qe, int index) 
{ 
    
    if (ss > qe || se < qs) { 
   
        
        Node nullNode; 
        return nullNode; 
    } 
   
    // Complete overlap 
    if (ss >= qs && se <= qe) { 
        return tree[index]; 
    } 
   
    // Partial Overlap Merge results of Left  
    // and Right subtrees 
    int mid = (ss + se) / 2; 
    Node left = queryUtil(tree, ss, mid, qs, qe,  
                                     2 * index); 
    Node right = queryUtil(tree, mid + 1, se, qs,  
                              qe, 2 * index + 1); 
   
    // merge left and right subtree query results 
    Node res = merge(left, right); 
    return res; 
} 
   
int query(Node* tree, int start, int end, int n) 
{ 
    Node res = queryUtil(tree, 0, n - 1, start, end, 1); 
    return res.maxSubarraySum; 
} 
   

int main(){
    std::ios_base::sync_with_stdio(false);  
    std::cin.tie(nullptr);
    int n,q;
    std::cin >> n;
    std::cin >> q;   

    int array[n],update_i[q],update_v[q];

    for(int i = 0; i < n; i++){   
        std::cin >> array[i];
    }

    for(int i = 0; i < q; i++){   
        std::cin >> update_i[i];   
        std::cin >> update_v[i];
    }
    
    Node* Tree = constructTree(array, n); 
    int start, end, maxSubarraySum; 

    //std::cout << ans;
    start = 0; 
    end = n; 
    long long answer;
    answer = Tree[1].maxSubarraySum;
    if (answer <0){
        answer=0;
    }
    cout << answer <<"\n"; 

    for(int i = 0; i < q; i++){       
        update(Tree,array, 1, 0, n - 1, update_i[i]-1, update_v[i]); 
        answer = Tree[1].maxSubarraySum;
        if (answer<0){
            answer=0;
        }
        cout << answer<<"\n"; 

    }
    return 0;


}

/*
10 10
-1 -5 -10 0 7 -1 4 -6 -3 -4
5 -4
3 10
5 -5
10 8
3 -2 
8 1 
10 7  
1 -7 
3 4  
4 9
*/
/*
10 9
-1 -5 -10 0 7 -1 4 -6 -3 -4
5 -4
3 10
5 -5
10 8
3 -2 
8 1 
10 7  
1 -7 
3 4  
*/



