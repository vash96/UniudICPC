#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);




// Complete the minimumBribes function below.
void minimumBribes(vector<int> v) {
    int n = v.size(), ans = 0;
    
    vector<int> bit(n+1, 0);
    
    auto Update = [&](int pos) {
        while(pos <= n) {
            ++bit[pos];
            pos += pos & -pos;
        }
    };
    auto Query = [&](int pos) {
        int ans = 0;
        while(pos > 0) {
            ans += bit[pos];
            pos -= pos & -pos;
        }
        return ans;
    };
    
    bool control = true;
    for(int i=0; i<n; ++i) {
        control &= v[i]<=i+1 || v[i]-(i+1)<=2;
        Update(v[i]);
        ans += v[i] - Query(v[i]);
    }
    
    if(control)
        cout << ans << "\n";
    else
        cout << "Too chaotic\n";
        
    cerr << "-----------------------\n\n";
}