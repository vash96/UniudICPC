#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    int n, m;
    cin >> n >> m;
    
    vector<vector<int>> graph(n);
    for(int i=0, u, v; i<m; ++i) {
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    
    int best = n+1;
    for(int i=0; i<n; ++i) {
        int dist[n]; fill_n(dist, n, n+1);
        queue<pair<int, pair<int, int>>> q;
        q.push({i, {0, i}});
        while(not q.empty()) {
            int u = q.front().first;
            int d = q.front().second.first;
            int p = q.front().second.second;
            q.pop();
            if(2*d > best) break;

            if(dist[u] == n+1) {
                dist[u] = d;
                for(auto v : graph[u]) {
                    if(v != p) {
                        q.push({v, {d+1, u}});
                    }
                }
            }else {
                best = min(best, d+dist[u]);
            }
        }
    }
    
    if(best <= n) {
        cout << best << "\n";
    }else {
        cout << "impossible\n";
    }
    
    
    return 0;
}