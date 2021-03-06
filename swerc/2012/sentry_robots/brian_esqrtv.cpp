/*
Testo: https://open.kattis.com/problems/sentryrobots
Tecnica: Max bipartite matching
Complessità: O(sqrt(Y) * X * Y)

Idea:
  - Prima risolviamo il caso senza ostacoli
  - L'osservazione chiave è notare come sia sempre possibile avere una soluzione ottima
    in cui ogni robot guarda verso destra o verso il basso:
        * Supponiamo che un robot R in [i, j] guardi verso sinistra, definiamo j' la minima
          colonna libera in riga i. Ovviamente j'<=j.
        * Spostiamo R in [i, j'] e facciamolo guardare verso destra.
        * La soluzione è ancora ottima, ma c'è un robot in meno che guarda verso sinistra.
        * Stesso discorso per trasformare quelli che guardano verso l'alto.
    È facile notare che grazie a questa costruzione ogni robot riesce a osservare tutta
    una riga oppure tutta una colonna (ad esclusioni di alcune celle alle sue spalle in cui
    però sono già presenti altri robot, dalla minimalità di j')
  - Dato che ogni robot è come se guardasse tutta una riga oppure tutta una colonna, dobbiamo
    trovare il minimo numero di righe e colonne da coprire.
  - Definiamo un grafo bipartito Righe -> Colonne in cui esiste un arco (i, j) per ogni punto di
    interesse [i, j]
  - Il problema diventa quindi determinare la cardinalità di minimum vertex cover del grafo che,
    per il teorema di Konig, è equivalente alla cardinalità di un maximum bipartite matching
  - Max bipartite matching risolvibile in svariati modi (Ford-fulkerson, Dinic, HopcroftKarp, ...)
    tutti vanno bene come complessità essendo il grafo piccolo
  
  - Adesso dobbiamo risolverlo con gli ostacoli: notiamo che presa una riga in cui vi è un
    ostacolo che divide due punti di interesse, possiamo creare una nuova riga per ottenere
    una griglia equivalente
                    . . * . # . . * . .   ==>   . . * . . . . . . .
                                          ==>   . . . . . . . * . .
  - Applico la trasformazione prima alle righe, poi alle colonne ottenendo un nuovo set di
    coordinate che posso risolvere come se fosse una griglia senza ostacoli.
    La griglia risultante può avere fino al doppio di righe e colonne, quindi ancora piccola.

*/

#include <bits/stdc++.h>
using namespace std;

const int maxn = 1 << 14;
const int oo = 1e9;

int n;

vector<int> dist, match;
vector<vector<int>> graph;


bool bfs()
{
    queue<int> q;
    for(int u=1; u<=n; ++u) {
        if(match[u] == 0) {
            q.push(u);
            dist[u] = 0;
        }else {
            dist[u] = oo;
        }
    }
    dist[0] = oo;

    while(not q.empty()) {
        int u = q.front(); q.pop();
        if(u != 0) {
            for(auto v : graph[u]) {
                if(dist[ match[v] ] == oo) {
                    dist[ match[v] ] = dist[u] + 1;
                    q.push( match[v] );
                }
            }
        }
    }

    return dist[0] != oo;
}

bool dfs(int u)
{
    if(u != 0) {
        for(auto v : graph[u]) {
            if(dist[ match[v] ] == dist[u]+1) {
                if(dfs(match[v])) {
                    match[u] = v;
                    match[v] = u;
                    return true;
                }
            }
        }
        dist[u] = oo;
        return false;
    }
    return true;
}

int hopcroftKarp(int a, int b)
{
    dist.resize(graph.size());
    match.resize(1 + a + b, 0);

    int ans = 0;
    while(bfs()) {
        for(int u=1; u<=n; ++u) {
            ans += match[u]==0 and dfs(u);
        }
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    short c;
    cin >> c;
    while(c--) {
        short row, col;
        cin >> row >> col;
        int grid[row+1][col+1];
        memset(grid, 0, sizeof(grid));
        
        short p;
        cin >> p;
        for(short i=0, x, y; i<p; ++i) {
            cin >> x >> y;
            grid[x][y] = 1;
        }

        short w;
        cin >> w;
        for(short i=0, x, y; i<w; ++i) {
            cin >> x >> y;
            grid[x][y] = 2;
        }

        pair<int, int> newGrid[row+1][col+1];

        // Stretch rows
        int ii=1;
        for(int i=1; i<=row; i++, ii++) {
            for(int j=1; j<=col; ++j) {
                if(grid[i][j] == 2) {
                    ++ii;
                }
                newGrid[i][j].first = ii;
            }
        }
        ii--;

        // Stretch cols
        int jj=1;
        for(int j=1; j<=col; j++, ++jj) {
            for(int i=1; i<=row; ++i) {
                if(grid[i][j] == 2) {
                    ++jj;
                }
                newGrid[i][j].second = jj;
            }
        }
        jj--;

        // Make bipartite graph
        n = ii;
        graph.resize(n+1);
        for(int i=1; i<=row; ++i) {
            for(int j=1; j<=col; ++j) {
                if(grid[i][j] == 1) {
                    graph[ newGrid[i][j].first ].push_back( n + newGrid[i][j].second );
                }
            }
        }

        cout << hopcroftKarp(ii, jj) << "\n";
        graph.clear();
        dist.clear();
        match.clear();
    }

    return 0;
}