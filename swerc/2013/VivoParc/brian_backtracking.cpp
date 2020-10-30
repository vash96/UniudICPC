/*
Testo: https://open.kattis.com/problems/vivoparc
Tecnica: Backtracking
Complessità: boh

Idea:
  - I limiti sono abbastanza bassi e possiamo procedere per backtracking
  - Ad ogni passo decidiamo il colore da assegnare ad un nodo, ricorrendo sui successivi
  - Scegliamo un colore da provare tra i soli colori disponibili per quel nodo
  - Se troviamo una soluzione return true e ci fermiamo

*/


#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> graph;
vector<int> colors;
int n;

bool backtrack(int u, int colored)
{
    if(colored==n) return true;
    array<bool, 5> can = {true, true, true, true, true};
    for(auto v : graph[u]) {
        can[colors[v]] = false;
    }
    for(int c=1; c<=4; ++c) {
        if(can[c]) {
            colors[u] = c;
            if(backtrack(u+1, colored+1))
                return true;
            colors[u] = 0;
        }
    }
    return false;
}

int main()
{
    scanf("%d\n", &n);

    vector<vector<bool>> adj(n, vector<bool>(n, false));
    int a, b;
    while(scanf("%d-%d\n", &a, &b) != EOF) {
        --a; --b;
        adj[a][b] = adj[b][a] = true;
    }

    graph.resize(n);
    colors.resize(n, 0);
    for(int u=0; u<n-1; ++u) {
        for(int v=u+1; v<n; ++v) {
            if(adj[u][v]) {
                graph[u].push_back(v);
                graph[v].push_back(u);
            }
        }
    }

    backtrack(0, 0);

    for(int i=0; i<n; ++i) {
        printf("%d %d\n", i+1, colors[i]);
    }

    return 0;
}