#include <bits/stdc++.h>

using namespace std;

// Complete the twoStrings function below.
string twoStrings(string s1, string s2) {
    vector<bool> has1(26, false);
    vector<bool> has2(26, false);
    
    for(auto c : s1) {
        has1[c-'a'] = true;
    }
    for(auto c : s2) {
        has2[c-'a'] = true;
    }
    
    for(int i=0; i<26; ++i) {
        if(has1[i] and has2[i]) {
            return "YES";
        }
    }
    return "NO";
}