/*
Testo: https://open.kattis.com/problems/cheatingbooleantree
Tecnica: Programmazione Dinamica
Complessità: O(N)

Idea:
 - Diciamo f(t, v) il minimo costo per ottenere il valore v=0/1 dal sottoalbero
   radicato in t (con infinito quando non e' possibile ottenerlo)
 - E' ovvio che f(t, v) dipende dagli f(t', v') con t' figlio di t e v'=0/1
 - Si calcolano ricorsivamente gli f(t', v') e si combinano le soluzioni
   avendo accortezza di quando t e' un AND o un OR
 - Infine, si considera anche il caso in cui 't' si puo' cambiare
 - Nel codice, ans[i][j] e' il costo minimo di ottenere valore j quando il gate e' i
*/

#include <bits/stdc++.h>
using namespace std;

#define Left(t) (2*(t))
#define Right(t) (2*(t)+1)

const int oo = 1e9;

int M, V;

vector<int> tree, change;
vector<array<int, 2>> dp;

int f(int t, int v)
{
    if(dp[t][v] != -1)
        return dp[t][v];
    if(t > (M-1)/2)
        return dp[t][v] = (v == tree[t] ? 0 : oo);
    int rec[2][2];
    rec[0][0] = f(Left(t), 0);
    rec[0][1] = f(Left(t), 1);
    rec[1][0] = f(Right(t), 0);
    rec[1][1] = f(Right(t), 1);
    
    int ans[2][2];
    ans[0][0] = rec[0][0] + rec[1][0];
    ans[0][1] = min(min(rec[0][1] + rec[1][0], rec[0][1] + rec[1][1]),
                    rec[0][0] + rec[1][1]);
    ans[1][0] = min(min(rec[0][0] + rec[1][0], rec[0][0] + rec[1][1]),
                    rec[0][1] + rec[1][0]);
    ans[1][1] = rec[0][1] + rec[1][1];
    for(int i=0; i<2; ++i)
        for(int j=0; j<2; ++j)
            ans[i][j] = min(ans[i][j], oo);
            
    dp[t][v] = ans[tree[t]][v];
    if(change[t] == 1)
        dp[t][v] = min(dp[t][v], 1 + ans[1 - tree[t]][v]);
    
    return dp[t][v];
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    
    int N;
    cin >> N;
    
    for(int t=1; t<=N; ++t) {
        tree.clear();
        change.clear();
        dp.clear();
        
        cin >> M >> V;
        tree.resize(M+1, 0);
        change.resize(M+1, 0);
        dp.resize(M+1, {{-1, -1}});
        for(int i=1; i<=(M-1)/2; ++i)
            cin >> tree[i] >> change[i];
        for(int i=(M-1)/2+1; i<=M; ++i)
            cin >> tree[i];
        int ans = f(1, V);
        
        cout << "Case #" << t << ": " << (ans == oo ? "IMPOSSIBLE" : to_string(ans)) << endl;
    }
}
