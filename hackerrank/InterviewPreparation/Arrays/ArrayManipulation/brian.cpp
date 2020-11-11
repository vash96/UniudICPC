#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

vector<long long> mem;

int main()
{
    int n, m, a, b;
    long long k;
    cin >> n >> m;
    mem.resize(n+2, 0);
    
    for(int i=0; i<m; ++i) {
        cin >> a >> b >> k;
        mem[a] += k;
        mem[b+1] -= k;
    }
    
    long long ans = 0, current = 0;
    for(int i=1; i<=n; ++i) {
        current += mem[i];
        ans = max(ans, current);
    }
    
    cout << ans << "\n";
    
    return 0;
}
