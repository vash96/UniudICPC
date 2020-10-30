#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;
typedef pair<ll,ll> LL;
ll sign;

vector<ll> base5(ll N){
    vector<ll> v;

    while(N != 0){
        v.push_back(N % 5);
        N /= 5;
    }

    return v;
}

ll power(ll e){
    if(e == 0)
        return 1;

    ll p = power(e/2);

    return (e % 2 == 1 ? 5 : 1)*p*p;
}

LL rate(ll e){      //the rate for 5^e
    ll p = power(e/2);

    return LL(p/2+1, p);
}

ll computeAddend(ll e, ll times){
    LL t = rate(e);
    ll p = power(e);
    ll res = 0;

    for(ll i = 0; i < times; i++){
        res += (p / t.second) * (sign ? t.first : t.second - t.first);

        if(e % 2)
            sign = 1 - sign;
    }

    return res;
}

ll f(ll n){
    vector<ll> v = base5(n);
    sign = 1;
    ll res = 0;

    for(ll i = v.size(); i > 0; i--)
        res += computeAddend(i-1, v[i-1]);

    return res;
}

int main(){
    ll N;
    cin>>N;

    while(N != -1){
        cout<<f(N+1)<<endl;
        cin>>N;
    }

    return 0;
}
