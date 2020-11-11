#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the minTime function below.
long minTime(vector<long> machines, long goal) {
    long lft = 0, rgt = *min_element(machines.begin(), machines.end()) * goal;
    long mid;
    
    auto Check = [&](const long T) {
        long prod = 0;
        for(auto m : machines) {
            prod += T / m;
        }
        
        return prod >= goal;
    };
    
    while(rgt-lft > 1) {
        mid = lft + (rgt-lft)/2LL;
        if(Check(mid)) {
            rgt = mid;
        }else {
            lft = mid;
        }
    }
    
    return rgt;

}