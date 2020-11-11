#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the minimumSwaps function below.
int minimumSwaps(vector<int> arr) {
    int n = arr.size();
    
    long long ans = 0;
    int i=0;
    while(i < n) {
        while(i < n and arr[i]-1 > i) {
            ++ans;
            swap(arr[i], arr[arr[i]-1]);
        }
        ++i;
    }

    return ans;
}