#include <bits/stdc++.h>

using namespace std;

// Complete the sherlockAndAnagrams function below.
int sherlockAndAnagrams(string s) {
    int n = s.length();
    vector<array<int, 26>> freq(n+1);
    for(int i=0; i<26; ++i) {
        freq[0][i] = 0;
    }
    
    for(int i=0; i<n; ++i) {
        for(int j=0; j<26; ++j) {
            freq[i+1][j] = freq[i][j];
        }
        
        ++freq[i+1][s[i]-'a'];
    }

    auto Freq = [&](int i, int j, int c) {
        return freq[i+1][c]-freq[j+1][c];
    };
    
    auto Check = [&](int i, int j, int len) {
        bool check = true;
        for(int k=0; check and k<26; ++k) {
            check &= Freq(i, i-len, k) == Freq(j, j-len, k);
        }
        return check;
    };
    
    int ans = 0;
    for(int len=1; len<=n; ++len) {
        for(int i=len-1; i<n; ++i) {
            for(int j=i+1; j<n; ++j) {
                ans += Check(i, j, len);
            }
        }
    }
    return ans;
}