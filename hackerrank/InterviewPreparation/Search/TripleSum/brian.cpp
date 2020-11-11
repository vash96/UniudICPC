#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the triplets function below.
long triplets(vector<int> a, vector<int> b, vector<int> c) {
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    sort(c.begin(), c.end());
    
    a.erase(unique(a.begin(), a.end()), a.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    c.erase(unique(c.begin(), c.end()), c.end());

    long ans = 0;
    for(auto q : b) {
        long nump = upper_bound(a.begin(), a.end(), q) - a.begin();
        long numr = upper_bound(c.begin(), c.end(), q) - c.begin();
                    
        ans += nump * numr;
    }
    
    return ans;
}