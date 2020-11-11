#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the findShortest function below.

/*
 * For the unweighted graph, <name>:
 *
 * 1. The number of nodes is <name>_nodes.
 * 2. The number of edges is <name>_edges.
 * 3. An edge exists between <name>_from[i] to <name>_to[i].
 *
 */
int findShortest(int graph_nodes, vector<int> graph_from, vector<int> graph_to, vector<long> ids, int val) {
    // solve here
    vector<vector<int>> graph(graph_nodes+1);
    vector<int> target;
    for(int i=0; i<graph_from.size(); ++i) {
        graph[graph_from[i]].emplace_back(graph_to[i]);
        graph[graph_to[i]].emplace_back(graph_from[i]);
    }
    for(int i=0; i<ids.size(); ++i) {
        if(ids[i] == val) {
            target.emplace_back(i+1);
        }
    }
    
    if(target.size() < 2) {
        return -1;
    }
    
    int ans = 1e9;
    vector<int> dist(graph_nodes+1, 1e9);
    vector<bool> vis(graph_nodes+1, false);
    queue<pair<int, int>> q;
    for(auto u : target) {
        q.emplace(u, 0);
    }
    
    while(not q.empty()) {
        auto [u, d] = q.front();
        q.pop();
        
        if(not vis[u]) {
            dist[u] = d;
            vis[u] = true;
            for(auto v : graph[u]) {
                if(not vis[v]) {
                    q.emplace(v, d+1);
                }
            }
        }else {
            ans = min(ans, dist[u]+d);
            if(dist[u]+d+1 > ans) {
                break;
            }
        }
        
    }
    
    return ans;
}