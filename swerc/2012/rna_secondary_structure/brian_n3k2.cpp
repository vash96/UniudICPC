/*
Testo: https://open.kattis.com/problems/rnasecondarystructure
Tecnica: DP, constraints
Complessità: O(n^3 * k^2) con n<=150

Idea:
  - Da notare che la descrizione dei matching implica che due match non
    possano intersecarsi, quindi un match s[i]--s[j] è tale che le sottostringhe
    s[1..i-1] s[i+1..j-1] s[j+1..N] si potranno considerare come disgiunte
    le une dalle altre
    ==> Questo è sinonimo di DP
  - dp[i][j][k] = massimo numero di matching posso effettuare sulla sottostringa s[i..j]
                    avendo k mosse per le CG/GC
  - Ho due scelte su s[i]:
      * lo scarto e ricorro su [i+1..j] con k mosse
      * lo matcho con un qualche i < t <= j e ricorro su [i+1..t-1] e [t+1..j]
          avendo rispettivamente k1 e k2 mosse per k1+k2=k'
          dove k' = k se ho matchato AU/UA, k' = k-1 altrimenti
  - Soluzione costosa:
      * O(N^2 * K) stati
      * O(N * K) per ogni stato
  - Osservare che posso matchare finché posso prima e ultima base e una volta
    fatto posso accorciare il primo e l'ultimo blocco per avere <= 50 basi
    ==> In questo modo avrò una stringa di <= 150 basi su cui fare DP

*/

#include <bits/stdc++.h>
using namespace std;

int readInt(char& c)
{
    cin.get(c);
    int n=0;
    while('0'<= c and c <= '9') {
        n = 10*n + (c-'0');
        cin.get(c);
    }
    return n;
}

int check[4][4] = {
    {0, 0, 0, 1},
    {0, 0, 1, 0},
    {0, 1, 0, 0},
    {1, 0, 0, 0}
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    map<char, int> base;
    base['A'] = 0;
    base['C'] = 1;
    base['G'] = 2;
    base['U'] = 3;
    
    int T;
    cin >> T;
    for(int t=1; t<=T; ++t) {
        char c;
        int K;
        cin >> c;

        vector<pair<int, int>> b;
        while(c != '\n') {
            b.push_back({base[c], 0});
            b.back().second = readInt(c);
        }
        cin >> K;

        int ans = 0;
        pair<int, int> &f=b.front(), &l=b.back();
        if(check[f.first][l.first]) {
            while(f.second>0 and l.second>0 and K>=(f.first==1 or f.first==2)) {
                f.second--;
                l.second--;
                ans++;
                K -= f.first==1 or f.first==2;
            }
        }

        f.second = min(f.second, 50);
        l.second = min(l.second, 50);
        
        vector<int> s;
        for(auto & p : b) {
            for(int i=0; i<p.second; ++i) {
                s.push_back(p.first);
            }
        }

        int sz = s.size(); assert(sz <= 150);
        int dp[sz+1][sz][K+1];
        memset(dp, 0, sizeof(dp));

        for(int i=sz-2; i>=0; --i) {
            for(int j=i+1; j<sz; ++j) {
                for(int k=0; k<=K; ++k) {
                    int & curr = dp[i][j][k];
                    curr = dp[i+1][j][k]; // Skip

                    // Fast
                    if((s[i]==1 or s[i]==2) and k==0)
                        continue;
                    if(check[s[i]][s[j]]) {
                        curr = 1 + dp[i+1][j-1][k - (s[i]==1 or s[i]==2)];
                        continue;
                    }
                    
                    // Find best split
                    for(int t=i+1; t<=j; ++t) {
                        if(check[s[i]][s[t]]) {
                            int kk = k - (s[i]==1 or s[i]==2);

                            for(int k1=0; k1<=kk; ++k1) {
                                curr = max(curr, 1 + dp[i+1][t-1][k1] + dp[t+1][j][kk-k1]);
                            }
                        }
                    }
                }
            }
        }

        cout << "Case " << t << ": " << (ans + dp[0][sz-1][K]) << "\n";
    }

    return 0;
}