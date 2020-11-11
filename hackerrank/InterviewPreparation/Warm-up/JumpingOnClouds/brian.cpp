#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the jumpingOnClouds function below.
int jumpingOnClouds(vector<int> c) {
    int n = c.size();
    vector<int> ans(n);
    ans[n-1] = 0;
    ans[n-2] = c[n-2] ? 1e9 : 1;
    for(int i=n-3; i>=0; --i) {
        if(c[i]) {
            ans[i] = 1e9;
        }else {
            ans[i] = 1+min(ans[i+1], ans[i+2]);
        }
    }
    
    return ans[0];
}