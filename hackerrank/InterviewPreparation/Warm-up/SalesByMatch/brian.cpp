#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the sockMerchant function below.
int sockMerchant(int n, vector<int> ar) {
    vector<int> col(101, 0);
    for(auto x : ar) {
        ++col[x];
    }
    
    return accumulate(col.begin(), col.end(), 0, [](int acc, int col) {
        return acc + col/2;
    });

}