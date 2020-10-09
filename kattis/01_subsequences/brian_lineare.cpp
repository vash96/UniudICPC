/*
Testo: https://open.kattis.com/problems/sequences
Tecnica: Programmazione dinamica, combinatoria
Complessità: O(|S|)

Idea:
 - Per ogni posizione si sommano tutte le inversioni che produce quella posizione
    tra tutte le combinazioni di '?'
 - Il calcolo può essere svolto manipolando una sommatoria e pre-calcolando in DP alcuni valori
 -  .... da finire
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    string S;
    cin >> S;

    int N = S.size();
    long long p2[N+1], s[N+1];
    long long MOD = 1e9+7;

    long long q = 0;
    for(auto c : S)
        q += c == '?';
    
    p2[0] = 1;
    for(int i=1; i<=N; ++i) {
        p2[i] = ((2LL)*p2[i-1]) % MOD;
    }

    s[0] = 0;
    for(int i=1; i<=N; ++i) {
        s[i] = ((2LL)*s[i-1] + p2[i-1]) % MOD;
    }

    long long ans = 0;
    for(long long i=0, n=0, m=0; i<N; ++i) {
        if(S[i] == '0') {
            ans = (ans + (((m * p2[n])%MOD + s[n]) * p2[q-n])%MOD) % MOD;
        }
        if(S[i] == '1') {
            ++m;
        }
        if(S[i] == '?') {
            ans = (ans + (((m * p2[n])%MOD + s[n]) * p2[q-n-1])%MOD) % MOD;
            ++n;
        }
    }

    cout << ans << "\n";

    return 0;
}