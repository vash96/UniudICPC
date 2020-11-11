#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the maximumToys function below.
int maximumToys(vector<int> prices, int k) {
    sort(prices.begin(), prices.end());
    int ans = 0;
    for(auto x : prices) {
        if(x <= k) {
            ++ans;
            k-=x;
        }
    }
    return ans;
}