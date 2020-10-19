/*
Testo: https://open.kattis.com/problems/shares
Tecnica: DP, testcase deboli
Complessità: abbastanza ignota, sicuramente O(C * P)

Idea:
  - Una volta determinato il peso e il guadagno di ogni pack si ha un knapsack
  - Risolvendo top down non si ha la necessità di riempire tutta la tabella DP, quindi a causa
    di testcase deboli possiamo cavarcela con una tabella di P hashmap in cui salvare lo stato (indice, peso)

*/


#include <bits/stdc++.h>
using namespace std;

unordered_map<long long, long long> dp[50001];
vector<pair<long long, long long>> packs;

long long solve(int i, long long w)
{
    if(i<0 or w==0LL) return 0LL;
    if(dp[i].find(w) != dp[i].end()) return dp[i][w];

    long long ans = solve(i-1, w);
    if(packs[i].first <= w) ans = max(ans, packs[i].second + solve(i-1, w - packs[i].first));
    return dp[i][w] = ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    long long C;
    cin >> C;

    int N, P;
    cin >> N >> P;

    pair<long long, long long> share[N];
    for(int i=0; i<N; ++i) {
        cin >> share[i].first >> share[i].second;
    }

    pair<long long, long long> pack[P];
    for(int i=0, r; i<P; ++i) {
        cin >> r;
        pack[i] = {0, 0};
        for(long long j=0, s, q; j<r; ++j) {
            cin >> s >> q; --s;
            pack[i].first += q * share[s].first;
            pack[i].second += q * (share[s].second - share[s].first);
        }
        if(pack[i].first <= C and pack[i].second > 0) {
            packs.push_back(pack[i]);
        }
    }
    cout << solve(packs.size()-1, C) << endl;

    return 0;
}