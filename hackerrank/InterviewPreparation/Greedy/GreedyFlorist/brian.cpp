#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the getMinimumCost function below.
int getMinimumCost(int k, vector<int> c) {
    sort(c.rbegin(), c.rend());
    int ans = 0;
    for(int i=0; i*k<c.size(); ++i) {
        for(int j=0; j<k and i*k+j<c.size(); ++j) {
            ans += c[i*k+j]*(i+1);
        }
    }
    return ans;
}