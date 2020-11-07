/*
Testo: https://open.kattis.com/problems/shoppingmalls
Tecnica: All-pairs shortest paths
Complessità: O(N^3 + Q*N)

Idea:
  - Il centro commerciale può essere rappresentato da un grafo orientato e pesato
  - Ogni arco ha un peso che dipende dal tipo di collegamento (walking, lift, stairs, escalator)
    Ricordarsi che la distanza euclidea in 3D è praticamente uguale a quella in 2D (sqrt(deltaX^2 + deltaY^2 + deltaZ^2))
  - Una volta costruito il grafo, si precomputa con FloydWarshall le distanze ottime e il predecessore ottimo di ogni coppia
  - In query si ricostruisce il path ottimo scorrendo

*/

#include <bits/stdc++.h>
using namespace std;

struct Place {
    int f, x, y;

    Place(int f, int x, int y)
    : f(f), x(x), y(y) { }
};

float graph[201][201];
vector<Place> places;
pair<float, int> fw[201][201];

int N, M;

auto Square = [](int x) { return x*x; };
auto Eucledian = [](int x, int y, int z) { return sqrtf(Square(5*x)+Square(y)+Square(z)); };

void AddEdge(int u, int v, string& t)
{
    float dist = Eucledian(places[u].f-places[v].f, places[u].x-places[v].x, places[u].y-places[v].y);

    if(t == "walking" or t == "stairs") {
        graph[u][v] = min(graph[u][v], dist);
        graph[v][u] = min(graph[v][u], dist);

    }else if(t == "lift") {
        graph[u][v] = 1;
        graph[v][u] = 1;
    }else {
        graph[u][v] = 1;
        graph[v][u] = min(graph[v][u], 3.0f * dist);
    }
};

void FloydWarshall()
{
    for(int i=0; i<N; ++i) {
        for(int j=0; j<N; ++j) {
            fw[i][j].first = graph[i][j];
            fw[i][j].second = i;
        }
    }
    
    for(int k=0; k<N; ++k) {
        for(int i=0; i<N; ++i) {
            for(int j=0; j<N; ++j) {
                float & dist = fw[i][j].first;
                int & pred = fw[i][j].second;

                if(dist > fw[i][k].first+fw[k][j].first) {
                    dist = fw[i][k].first+fw[k][j].first;
                    pred = fw[k][j].second;
                }
            }
        }
    }
}

void Print(int u, int v)
{
    stack<int> path;
    do {
        path.emplace(v);
        v = fw[u][v].second;
    }while (u != v);

    cout << u << " ";
    while(not path.empty()) {
        cout << path.top() << " ";
        path.pop();
    }
    cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> M;
    for(int i=0; i<N; ++i) {
        for(int j=0; j<N; ++j) {
            graph[i][j] = numeric_limits<float>::max() / 2.0;
        }
        graph[i][i] = 0;
    }

    for(int i=0; i<N; ++i) {
        int f, x, y;
        cin >> f >> x >> y;
        places.emplace_back(f, x, y);
    }

    for(int i=0; i<M; ++i) {
        int u, v;
        string type;
        cin >> u >> v >> type;
        AddEdge(u, v, type);
    }

    FloydWarshall();

    for(int u=0; u<N; ++u) {
        for(int v=0; v<N; ++v) {
            cerr << fw[u][v].first << " ";
        }cerr << "\n";
    }

    int Q;
    cin >> Q;
    while(Q--) {
        int u, v;
        cin >> u >> v;
        Print(u, v);
    }


    return 0;
}