#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

// Complete the countTriplets function below.
long countTriplets(vector<long> arr, long r) {
    unordered_map<int, long> memoI, memoK;
    int n = arr.size();
    for(auto x : arr) {
        ++memoK[x];
    }
    
    long ans = 0;
    for(int i=0, k=n-1; i<n; ++i, --k) {
// triplets[j] = #(i,k) s.t. i<j<k && r*arr[i]==arr[j] && r*arr[j]==arr[k]
//             = (#i s.t. i<j && r*arr[i]==arr[j]) * (#k s.t. j<k && r*arr[j]==arr[k])
        --memoK[arr[i]];
        if(arr[i]%r == 0) {
            ans += memoI[arr[i]/r] * memoK[r*arr[i]];
        }
        ++memoI[arr[i]];
    }
    
    return ans;

}