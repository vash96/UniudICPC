/*
Testo: https://open.kattis.com/problems/mixingcolours
Tecnica: Programmazione Dinamica, Parsing, approssimazione float
Complessità: O(C^3 * R^2)

Idea:
 - ogni regola del tipo A+B=C può essere rappresentata tramite due
    produzioni C -> AB e C -> BA di una grammatica CF.
 - Il problema diventa quindi determinare il parsing "più probabile"
    della parola in input (parola dove le lettere sono colori)
 - Definisco dp[i,j,k] come la probabilità del parsing più probabile
    per derivare la sottostringa [i..j] a partire dal colore k. Per il calcolo:
        * Fisso una regola di produzione k -> ab
        * ab deve derivare [i..j], quindi devo trovare x tale che a derivi [i..x]
          e b derivi [x+1..j]
        * Cerco la regola e la posizione x che massimizzi la probabilità dp[i,x,a]*dp[x+1,j,b]
 - Per evitare problemi di approssimazione (e tante bestemmie) sfruttare il fatto che
    trovare max(p * q) è equivalente a trovare max(log(p) + log(q))

*/

#include <bits/stdc++.h>
using namespace std;

double MIN = -numeric_limits<double>::max();

int R, ncol;
unordered_map<string, int, hash<string>> umap;
vector<string> imap;
vector<pair<int, int>> prod[300];

void solve()
{
    int C;
    cin >> C;
    
    double cer[C][ncol];
    for(int i=0; i<C; ++i) {
        for(int j=0; j<ncol; ++j) {
            cer[i][j] = MIN;
        }
    }
    
    string color;
    double cc;
    for(int i=0; i<C; ++i) {
        cin >> color;
        while(color != "END") {
            cin >> cc;
            cer[i][umap[color]] = log(cc); // Using log
            cin >> color;
        }
    }
    
    double dp[C][C][ncol]; // Max Probability( word[i..j] is derived from color k )
    for(int i=0; i<C; ++i) {
        for(int j=0; j<C; ++j) {
            for(int k=0; k<ncol; ++k) {
                dp[i][j][k] = MIN;
            }
        }
    }
    
    // Base case
    for(int i=0; i<C; ++i) { // Probability( word[i] is derived from color k is its certainty )
        for(int k=0; k<ncol; ++k) {
            dp[i][i][k] = cer[i][k];
        }
    }
    
    // Inductive step
    for(int len=2; len<=C; ++len) { // For each length
        for(int i=0, j; i<=C-len; ++i) { // For each starting point
            j = i+len-1;
            for(int k=0; k<ncol; ++k) { // For each starting color
                double & ijk = dp[i][j][k];
                for(auto & p : prod[k]) { // For each rule that produces color k
                    for(int x=i; x<j; ++x) { // Take best split among all rules
                        ijk = max(ijk, dp[i][x][p.first] + dp[x+1][j][p.second]);
                    }
                }
            }
        }
    }
    
    int best = 0;
    double pbest = dp[0][C-1][best];
    for(int candidate = 1; candidate<ncol; ++candidate) {
        if(pbest < dp[0][C-1][candidate]) {
            best = candidate;
            pbest = dp[0][C-1][best];
        }
    }
    
    if(pbest > MIN) {
        cout << imap[best] << "\n";
    }else {
        cout << "GAMEOVER" << "\n";
    }
    
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    cin >> R;
    for(int i=0; i<R; ++i) {
        string s1, s2, s3;
        cin >> s1 >> s2 >> s3;
        if(umap.find(s1) == umap.end())
            umap[s1] = ncol++, imap.push_back(s1);
        if(umap.find(s2) == umap.end())
            umap[s2] = ncol++, imap.push_back(s2);
        if(umap.find(s3) == umap.end())
            umap[s3] = ncol++, imap.push_back(s3);
            
        prod[umap[s3]].push_back({umap[s1], umap[s2]});
        prod[umap[s3]].push_back({umap[s2], umap[s1]});
    }
    
    int T;
    cin >> T;
    for(int t=0; t<T; ++t) {
        solve();
    }
    
    return 0;
}