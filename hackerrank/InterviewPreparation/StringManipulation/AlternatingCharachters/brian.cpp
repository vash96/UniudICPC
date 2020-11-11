#include <bits/stdc++.h>

using namespace std;

// Complete the alternatingCharacters function below.
int alternatingCharacters(string s) {
    int ans = 0;
    for(int i=1; i<s.length(); ++i) {
        ans += s[i-1] == s[i];
    }
    return ans;
}