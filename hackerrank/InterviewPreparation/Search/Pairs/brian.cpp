#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the pairs function below.
int pairs(int k, vector<int> arr) {
    sort(arr.begin(), arr.end());
    int ans = 0;
    for(int i=0; i<arr.size(); ++i) {
        ans += binary_search(arr.begin(), arr.end(), k+arr[i]);
    }
    return ans;
}