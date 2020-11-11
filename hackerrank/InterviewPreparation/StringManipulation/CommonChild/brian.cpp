#include <bits/stdc++.h>

using namespace std;

// Complete the commonChild function below.
int commonChild(string s1, string s2) {
    int n = s1.length(), m = s2.length();
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
    
    for(int i=1; i<=n; ++i) {
        for(int j=1; j<=m; ++j) {
            int & d = dp[i][j];
            d = max(dp[i-1][j], dp[i][j-1]);
            if(s1[i-1] == s2[j-1])
                d = max(d, 1+dp[i-1][j-1]);
        }
    }
    
    return dp[n][m];
}