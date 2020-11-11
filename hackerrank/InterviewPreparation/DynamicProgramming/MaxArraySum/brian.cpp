#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the maxSubsetSum function below.
int maxSubsetSum(vector<int> arr) {
    int n = arr.size();
    if(n == 1) {
        return max(0, arr[0]);
    }
    vector<int> dp(n, 0);
    
    dp[0] = max(0, arr[0]);
    for(int i=1; i<n; ++i) {
        dp[i] = max(arr[i] + dp[i-2], dp[i-1]);
    }

    return dp[n-1];
}