#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the minimumPasses function below.
long minimumPasses(long m, long w, long p, long n) {
    if(m > w) {
        swap(m, w);
    }
    
    auto Ceil = [](long n, long m, long w) -> long {
        if(n <= 0) return 0;
        return (n+m-1)/m <= w ? 1 : (n+m*w-1) / (m*w);
    };
    
    long ans = Ceil(n, m, w), steps = 0;
    long upp = 1e13;
    long candies = 0;
    while(true) {
        long fwd = max(long(1), min(Ceil(p-candies, m, w), Ceil(n-candies, m, w)));
        
        steps += fwd;
        if(upp/(fwd*m) <= w) {
            ans = min(ans, steps);
            break;
        }
        
        candies += fwd*m*w;
        
        long buy = w-m;
        buy = min(buy, candies/p);
        m += buy;
        candies -= buy*p;
        buy = candies/(p*2LL);
        m += buy;
        w += buy;
        candies -= 2LL*p*buy;
        buy = candies/p;
        w += buy;
        candies -= buy*p;
        
        ans = min(ans, steps + Ceil(n-candies, m, w));
        
    }

    return ans;
}