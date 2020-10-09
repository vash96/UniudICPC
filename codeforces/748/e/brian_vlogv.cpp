#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int v = 1e7+1;

ll n, k;
ll a[v];

bool check(ll m)
{
    ll b[v], ans = 0;
    for(int i=0; i<v; ++i) {
        b[i] = a[i];
        if(i >= m) ans += a[i];
    }
    
    
    for(int i=v-1; i>=2*m and ans<k; --i) {
        ans += b[i];
        ll x = i/2;
        b[x] += b[i];
        b[i-x] += b[i];
    }
    
    return ans >= k;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    cin >> n >> k;
    ll tot=0;
    for(int i=0, x; i<n; ++i) {
        cin >> x;
        a[x]++;
        tot += x;
    }
    
    if(tot < k) {
        cout << "-1\n";
        return 0;
    }
    
    ll low = 0, hi = v, mid;
    while(hi-low>1) {
        mid = (low+hi) / 2;
        if(check(mid)) {
            low = mid;
        }else {
            hi = mid;
        }
    }
    
    cout << low << "\n";
    
    return 0;
}