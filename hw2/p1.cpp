#include <array>
#include <iostream>
#include <random>
#include <algorithm>    // std::max
#include <time.h>
#include <climits>
#include <numeric>  
int leastgreater(long long int *a, int low, int high, long long int key) 
{   
    int ret = high+1; 
    while (low <= high) { 
        int mid = low + (high - low ) / 2; 
        long long int midVal = a[mid]; 
  
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
int fast_mod(const int input, const int ceil) {
    // apply the modulo operator only when needed
    // (i.e. when the input is greater than the ceiling)
    return input >= ceil ? input % ceil : input;
    // NB: the assumption here is that the numbers are positive
}

namespace ada {

class Xoroshiro128 {
 public:
  using result_type = uint32_t;
  static constexpr result_type(min)() { return 0; }
  static constexpr result_type(max)() { return UINT32_MAX; }
  static inline result_type rotl(const result_type x, int k) {
    return (x << k) | (x >> (32 - k));
  }
  Xoroshiro128() : Xoroshiro128(1, 2, 3, 4) {}
  Xoroshiro128(result_type a, result_type b, result_type c, result_type d)
      : s{a, b, c, d} {}
  result_type operator()() {
    const result_type result = rotl(s[0] + s[3], 7) + s[0];
    const result_type t = s[1] << 9;
    s[2] ^= s[0];
    s[3] ^= s[1];
    s[1] ^= s[2];
    s[0] ^= s[3];
    s[2] ^= t;
    s[3] = rotl(s[3], 11);
    return result;
  }

 private:
  std::array<result_type, 4> s;
};

namespace {
int c_lead, c_team;
Xoroshiro128 rng;
}  // namespace

int Init() {
  int n;
  uint32_t s1, s2, s3, s4;
  std::cin >> n >> c_lead >> c_team >> s1 >> s2 >> s3 >> s4;
  rng = Xoroshiro128(s1, s2, s3, s4);
  return n;
}

int GetLeadership() { return uint64_t(rng()) * c_lead >> 32; }

int GetTeamValue() {
  int tmp = int(uint64_t(rng()) * c_team >> 32) + 1;
  return int(c_team / sqrt(tmp));
}

}  // namespace ada
const int kN = 3000000;

int leadership[kN], team_value[kN];
long long int dp[kN],cul_dp[kN],cul_team_value[kN];

int main() {
    int n = ada::Init(); 
    double START = clock();
    for (int i = 0; i < n; i++) {
      leadership[i] = ada::GetLeadership();
    }
    for (int i = 0; i < n; i++) {
      team_value[i] = ada::GetTeamValue();
    }    
    cul_team_value[0] = team_value[0];
    for (int i = 1; i < n; i++) {
      cul_team_value[i] = cul_team_value[i-1]+team_value[i];
    }

    dp[n] = 1;
    cul_dp[n+1]=0;
    cul_dp[n]=1;
    
    for (int i=n-1 ; i>=0; i--){
      long long larget_index ;
      larget_index = leastgreater(cul_team_value, i+1, n-1, leadership[i]+cul_team_value[i]);


      dp[i] = (cul_dp[i+1]-cul_dp[larget_index+1]);
      dp[i] = dp[i]%1000000007;
      cul_dp[i] = cul_dp[i+1] + dp[i];
      cul_dp[i] = cul_dp[i]%1000000007;

    }
    if (dp[0]<0) {dp[0]+=1000000007;}
    std::cout<<dp[0];
    std::cout<<"time elaspe:"<<clock()-START;
}
