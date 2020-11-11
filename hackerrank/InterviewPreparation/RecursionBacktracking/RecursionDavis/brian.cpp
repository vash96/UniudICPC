#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */ 
    vector<long long> dp(40);
    dp[0] = 1;
    dp[1] = 1;
    dp[2] = 2;
    for(int s=3; s<(int)dp.size(); ++s)
        dp[s] = dp[s-1]+dp[s-2]+dp[s-3];
    
    int s;
    cin >> s;
    for(int i=0; i<s; ++i) {
        int n;
        cin >> n;
        cout << dp[n] << endl;
    }
    
    return 0;
}
