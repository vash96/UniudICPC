#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the minimumAbsoluteDifference function below.
int minimumAbsoluteDifference(vector<int> arr) {
    sort(arr.begin(), arr.end());
    int best = arr[1]-arr[0];
    for(int i=2; i<arr.size(); ++i) {
        best = min(best, arr[i]-arr[i-1]);
    }
    return best;
}