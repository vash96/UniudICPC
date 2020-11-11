#include <bits/stdc++.h>
using namespace std;

const int mv=1e7+5;

int t, n, fenwick[mv];

void update(int pos)
{
    while(pos<mv){
        ++fenwick[pos];
        pos += (pos & -pos);
    }
}

unsigned long long query(int pos)
{
    unsigned long long sol=0;
    while(pos>0){
        sol+=fenwick[pos];
        pos -= (pos & -pos);
    }
    return sol;
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin >> t;
    for(int x=0; x<t; ++x){
        unsigned long long sol=0;
        for(int y=0; y<mv; ++y)
            fenwick[y]=0;
        cin >> n;
        for(int y=0, z; y<n; ++y){
            cin >> z;
            sol += (y-query(z));
            update(z);
        }
        cout << sol << "\n";
    }
    
    return 0;
}
