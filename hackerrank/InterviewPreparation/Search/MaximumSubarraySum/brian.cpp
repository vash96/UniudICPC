#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);
typedef vector<long>::iterator It;

long MOD;

long Center(It beg, It mid, It end)
{
    set<long> mods;
    long partialMod = 0;
    for(It it = mid; it != end; ++it) {
        partialMod = (partialMod + *it) % MOD;
        mods.insert(partialMod);
    }
    
    partialMod = 0;
    long ans = 0;
    for(It it = mid-1; it >= beg; --it) {
        partialMod = (partialMod + *it) % MOD;
        auto candidate = mods.lower_bound(MOD-1LL-partialMod);
        if(candidate != mods.end()) {
            ans = max(ans, (partialMod + *candidate) % MOD);
        }
        if(candidate != mods.begin()) {
            --candidate;
            ans = max(ans, (partialMod + *candidate) % MOD);
        }
    }
    
    return ans;
}

long Solve(It beg, It end)
{
    if(distance(beg, end) <= 1) {
        return beg != end ? *beg : 0;
    }else {
        It mid = beg + distance(beg, end)/2;
        return max(Center(beg, mid, end), max(Solve(beg, mid), Solve(mid, end)));
    }
}

// Complete the maximumSum function below.
long maximumSum(vector<long> a, long m) {
    for(auto & x : a) {
        x %= m;
    }
    MOD = m;
    
    cerr << "Solving...\n";
    
    return Solve(a.begin(), a.end());
}