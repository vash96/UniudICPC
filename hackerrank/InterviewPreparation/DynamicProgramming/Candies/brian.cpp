#include <bits/stdc++.h>

using namespace std;

// Complete the candies function below.
long candies(int n, vector<int> arr) {
    vector<long> candies(n, 0);
    candies[0] = 1;
    for(int i=1; i<n; ++i) {
        if(arr[i-1]<arr[i]) {
            candies[i] = candies[i-1]+1;
        }else {
            candies[i] = 1;
        }
    }
    
    for(int i=n-2; i>=0; --i) {
        if(arr[i+1] < arr[i]) {
            candies[i] = max(candies[i], 1+candies[i+1]);
        }
    }
    
    
    for(auto c : arr) {
        cerr << c << " ";
    }cerr << "\n";
    
    for(auto c : candies) {
        cerr << c << " ";
    }cerr << "\n";
    return accumulate(candies.begin(), candies.end(), long(0));
}