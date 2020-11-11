#include <bits/stdc++.h>

using namespace std;

// Complete the abbreviation function below.
string abbreviation(string a, string b) {
    int n = a.length();
    int m = b.length();
    vector<vector<bool>> dp(n+1, vector<bool>(m+1, false));
    
    auto Equal = [](const char a, const char b) {
        if(islower(a)) {
            return toupper(a) == toupper(b);
        }else {
            return a == b;
        }
    };
    
    dp[0][0] = true;
    
    for(int i=1; i<=n and islower(a[i-1]); ++i) {
        dp[i][0] = true;
    }
    
    for(int i=1; i<=n; ++i) {
        for(int j=1; j<=m; ++j) {
            if(Equal(a[i-1], b[j-1])) {
                dp[i][j] = dp[i-1][j-1];
            }
            if(islower(a[i-1])) {
                dp[i][j] = dp[i][j] or dp[i-1][j];
            }
        }
    }
    
    return dp[n][m] ? "YES" : "NO";
}