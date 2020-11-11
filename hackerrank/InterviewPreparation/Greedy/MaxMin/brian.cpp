#include <bits/stdc++.h>

using namespace std;

// Complete the maxMin function below.
int maxMin(int k, vector<int> arr) {
    sort(arr.begin(), arr.end());
    int ans = arr[k-1] - arr[0];
    for(int i=k; i<arr.size(); ++i) {
        ans = min(ans, arr[i]-arr[i-k+1]);
    }
    return ans;
}