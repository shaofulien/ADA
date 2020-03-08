#include <iostream>
#include <vector> 
#include <stdlib.h>    
unsigned long long ans = 0;

int leastgreater(int *a, int low, int high, int key) 
{   
    int ret = high+1; 
    while (low <= high) { 
        int mid = low + (high - low ) / 2; 
        int midVal = a[mid]; 
  
        if (midVal <= key) { 

            low = mid + 1; 
        } 
        else if (midVal > key) { 

            ret = mid; 
            high = mid - 1; 
        } 
    } 
    return ret; 
} 


int leastsmaller(int *a, int low, int high, int key) 
{   
    int ret = low-1; 
    while (low <= high) { 
        int mid = low + (high - low + 1) / 2; 
        int midVal = a[mid]; 
  
        if (midVal < key) { 

            ret = mid; 
            low = mid + 1; 
        } 
        else if (midVal >= key) { 
  
            
            high = mid - 1; 
        } 

    } 
    return ret; 
} 
//using namespace std;
void merges(int *a, int lef, int righ,int *b) {

    if(lef == righ) {
        return ;
    }
    int center = lef + (righ - lef) / 2;

    merges(a, lef, center,b);

    merges(a, center + 1, righ,b);

    int totalSize = righ - lef + 1;
    int tmp[totalSize];
    int btmp[totalSize];
    int n = lef;
    int m = center + 1;
    int i = 0;

    while(n <= center || m <= righ) {
        if(m > righ || (n <= center && a[n] <= a[m])) {

            btmp[i] = b[n];
            tmp[i++] = a[n++];
        } 

        else {
            int j,k;
            j = leastgreater(a, lef, center, a[m]+b[m]);

            k = leastsmaller(a, lef, center, a[m]-b[m]);

            ans += j-k-1;

            btmp[i] = b[m];
            tmp[i++] = a[m++];
        }
    }

    n = lef;
    for(int i = 0; i < totalSize; i++) {

        b[n] = btmp[i];
        a[n++] = tmp[i];

    }
}


void mergeSort(int *a, int n,int *b) {
    merges(a, 0, n - 1,b);
}

int main(){
    //vector <int> preference;
    //vector <int> friendliness;
    std::ios_base::sync_with_stdio(false);  
    std::cin.tie(nullptr);
    int n;
    //scanf("%d", &n);
    std::cin >> n;
    int preference[n],friendliness[n];

    for(int i = 0; i < n; i++){   
        //int x;     
        //scanf("%d", &preference[i]);
        std::cin >> preference[i];
        //preference.push_back(x);
    }

    for(int i = 0; i < n; i++){   
        //int x;     
        std::cin >> friendliness[i];
        //friendliness.push_back(x);
    }

    mergeSort(preference, n,friendliness);
    std::cout << ans;

    return 0;


}




