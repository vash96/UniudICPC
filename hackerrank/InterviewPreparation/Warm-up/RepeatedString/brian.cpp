#include <bits/stdc++.h>

using namespace std;

// Complete the repeatedString function below.
long repeatedString(string s, long n) {
    long ans = n / (long(s.size())) * count_if(s.begin(), s.end(), [](char c){ return c == 'a'; });
    
    for(int i=0; i<n%(long(s.size())); ++i) {
        ans += long(s[i] == 'a');
    }
    
    return ans;
}