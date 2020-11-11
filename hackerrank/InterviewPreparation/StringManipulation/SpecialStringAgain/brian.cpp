#include <bits/stdc++.h>

using namespace std;

// Complete the substrCount function below.
long substrCount(int n, string s) {
    vector<pair<char, long>> block;
    s += '$';
    for(int i=1, last=0; i<=n; ++i) {
        if(s[i] != s[last]) {
            block.emplace_back(s[last], i-last);
            last = i;
        }
    }
    
    long ans = 0;
    for(int i=0; i<block.size(); ++i) {
        ans += (block[i].second) * (block[i].second+1LL) / 2LL;
        if(block[i].second == 1 and 
            0<i and i+1<block.size() and 
            block[i-1].first == block[i+1].first) {
            
            ans += min(block[i-1].second, block[i+1].second);
        }
    }
    return ans;
}