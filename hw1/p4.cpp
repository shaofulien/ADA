#include <iostream>
#include <string>
#include <bits/stdc++.h> 
#include<algorithm>
using namespace std; 

int mini(int a,int b){
    if(a<=b){
        return a;
    }
    else
    {
        return b;
    }
}
int edit_distance_d(string a,  string b)
{
    int lena = a.length();
    int lenb = b.length();
    int d[lena+1][lenb+1];
    int i, j;
    
    for (i = 0; i<= lena; i++) {
        d[i][0] = 0;
    }
    for (j = 0; j<= lenb; j++) {
        d[0][j] = 0;
    }

    for (i = 1; i <= lena; i++) {
        for (j = 1; j <= lenb; j++) {
            if (a[i-1] != b[j-1]) {
                d[i][j] = d[i-1][j-1];
            } else {
                
                d[i][j] = mini(mini(d[i-1][j]+1, d[i][j-1]+1),d[i-1][j-1]+1);
            }
            
        }
    }

    return d[lena][lenb];
}

int main(){
    std::ios_base::sync_with_stdio(false);  
    std::cin.tie(nullptr);
    string s1,s2;
    std::cin >> s1;
    std::cin >> s2;  

    //int ans = edit_distance(s1, s2, s1.length()-1, s2.length()-1);
    reverse(s1.begin(),s1.end());    
    reverse(s2.begin(),s2.end());
    int ans = edit_distance_d(s1, s2);
    std::cout<<ans;
    

    return 0;


}

/*

*/



