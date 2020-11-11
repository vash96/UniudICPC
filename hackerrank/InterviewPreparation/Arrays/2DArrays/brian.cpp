#include <bits/stdc++.h>

using namespace std;

// Complete the hourglassSum function below.
int hourglassSum(vector<vector<int>> a) {
    auto HSum = [&a](int i, int j) {
        return a[i-1][j-1] + a[i-1][j] + a[i-1][j+1]
                           + a[i][j]   +
               a[i+1][j-1] + a[i+1][j] + a[i+1][j+1];
    };
    
    int ans = -1e9;
    for(int i=1; i+1<a.size(); ++i) {
        for(int j=1; j+1<a[i].size(); ++j) {
            ans = max(ans, HSum(i, j));
        }
    }
    
    return ans;

}